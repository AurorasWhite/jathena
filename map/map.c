// $Id: map.c,v 1.11 2003/06/29 05:56:44 lemit Exp $
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "core.h"
#include "timer.h"
#include "db.h"
#include "grfio.h"
#include "map.h"
#include "chrif.h"
#include "clif.h"
#include "intif.h"
#include "npc.h"
#include "pc.h"
#include "mob.h"
#include "chat.h"
#include "itemdb.h"
#include "storage.h"
#include "skill.h"
#include "trade.h"
#include "party.h"
#include "battle.h"
#include "script.h"
#include "guild.h"
#include "pet.h"
#include "atcommand.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

// �ɗ� static�Ń��[�J���Ɏ��߂�
static struct dbt * id_db;
static struct dbt * map_db;
static struct dbt * nick_db;
static struct dbt * charid_db;

static int users;
static struct block_list *object[MAX_FLOORITEM];
static int first_free_object_id,last_object_id;

#define block_free_max 16000
static void *block_free[block_free_max];
static int block_free_count=0,block_free_lock=0;

struct map_data map[MAX_MAP_PER_SERVER];
int map_num=0;

int autosave_interval=DEFAULT_AUTOSAVE_INTERVAL;

struct charid2nick {
	char nick[24];
	int req_id;
};

/*==========================================
 * �Smap�I���v�ł̐ڑ����ݒ�
 * (char�I���瑗���Ă���)
 *------------------------------------------
 */
void map_setusers(int n)
{
	users=n;
}

/*==========================================
 * �Smap�I���v�ł̐ڑ����擾 (/w�ւ̉����p)
 *------------------------------------------
 */
int map_getusers(void)
{
	return users;
}

//
// block�폜�̈��S���m�ۏ���
//

/*==========================================
 * block��free����Ƃ�free�̕ς��ɌĂ�
 * ���b�N����Ă���Ƃ��̓o�b�t�@�ɂ��߂�
 *------------------------------------------
 */
int map_freeblock( void *bl )
{
	if(block_free_lock==0)
		free(bl);
	else{
		if( block_free_count>=block_free_max )
			printf("map_freeblock: *WARNING* too many free block! %d %d\n",
				block_free_count,block_free_lock);
		else
			block_free[block_free_count++]=bl;
	}
	return block_free_lock;
}
/*==========================================
 * block��free���ꎞ�I�ɋ֎~����
 *------------------------------------------
 */
int map_freeblock_lock(void)
{
	return ++block_free_lock;
}
/*==========================================
 * block��free�̃��b�N����������
 * ���̂Ƃ��A���b�N�����S�ɂȂ��Ȃ��
 * �o�b�t�@�ɂ��܂��Ă���block��S���폜
 *------------------------------------------
 */
int map_freeblock_unlock(void)
{
	if( (--block_free_lock)==0 ){
		int i;
//		if(block_free_count>0)
//			printf("map_freeblock_unlock: free %d object\n",block_free_count);
		for(i=0;i<block_free_count;i++)
			free(block_free[i]);
		block_free_count=0;
	}else if(block_free_lock<0){
		printf("map_freeblock_unlock: lock count < 0 !\n");
	}
	return block_free_lock;
}


//
// block������
//
/*==========================================
 * map[]��block_list����q�����Ă���ꍇ��
 * bl->prev��bl_head�̃A�h���X�����Ă���
 *------------------------------------------
 */
static struct block_list bl_head;

/*==========================================
 * map[]��block_list�ɒǉ�
 * mob�͐��������̂ŕʃ��X�g
 *
 * ����link�ς݂��̊m�F�������B�댯����
 *------------------------------------------
 */
int map_addblock(struct block_list *bl)
{
	int m,x,y;

	m=bl->m;
	x=bl->x;
	y=bl->y;
	if(m<0 || m>=map_num ||
	   x<0 || x>=map[m].xs ||
	   y<0 || y>=map[m].ys)
		return 1;

	if(bl->type==BL_MOB){
		bl->next = map[m].block_mob[x/BLOCK_SIZE+(y/BLOCK_SIZE)*map[m].bxs];
		bl->prev = &bl_head;
		if(bl->next) bl->next->prev = bl;
		map[m].block_mob[x/BLOCK_SIZE+(y/BLOCK_SIZE)*map[m].bxs] = bl;
	} else {
		bl->next = map[m].block[x/BLOCK_SIZE+(y/BLOCK_SIZE)*map[m].bxs];
		bl->prev = &bl_head;
		if(bl->next) bl->next->prev = bl;
		map[m].block[x/BLOCK_SIZE+(y/BLOCK_SIZE)*map[m].bxs] = bl;
		if(bl->type==BL_PC)
			map[m].users++;
	}

	return 0;
}

/*==========================================
 * map[]��block_list����O��
 * prev��NULL�̏ꍇlist�Ɍq�����ĂȂ�
 *------------------------------------------
 */
int map_delblock(struct block_list *bl)
{
	// ����blocklist���甲���Ă���
	if(bl->prev==NULL){
		if(bl->next!=NULL){
			// prev��NULL��next��NULL�łȂ��̂͗L���Ă͂Ȃ�Ȃ�
			printf("map_delblock error : bl->next!=NULL\n");
		}
		return 0;
	}

	if(bl->type==BL_PC)
		map[bl->m].users--;
	if(bl->next) bl->next->prev = bl->prev;
	if(bl->prev==&bl_head){
		// ���X�g�̓��Ȃ̂ŁAmap[]��block_list���X�V����
		if(bl->type==BL_MOB){
			map[bl->m].block_mob[bl->x/BLOCK_SIZE+(bl->y/BLOCK_SIZE)*map[bl->m].bxs] = bl->next;
		} else {
			map[bl->m].block[bl->x/BLOCK_SIZE+(bl->y/BLOCK_SIZE)*map[bl->m].bxs] = bl->next;
		}
	} else {
		bl->prev->next = bl->next;
	}
	bl->next = NULL;
	bl->prev = NULL;

	return 0;
}

/*==========================================
 * ���͂�PC�l���𐔂��� (���ݖ��g�p)
 *------------------------------------------
 */
int map_countnearpc(int m,int x,int y)
{
	int bx,by,c=0;
	struct block_list *bl;

	if(map[m].users==0)
		return 0;
	for(by=y/BLOCK_SIZE-AREA_SIZE/BLOCK_SIZE-1;by<=y/BLOCK_SIZE+AREA_SIZE/BLOCK_SIZE+1;by++){
		if(by<0 || by>=map[m].bys)
			continue;
		for(bx=x/BLOCK_SIZE-AREA_SIZE/BLOCK_SIZE-1;bx<=x/BLOCK_SIZE+AREA_SIZE/BLOCK_SIZE+1;bx++){
			if(bx<0 || bx>=map[m].bxs)
				continue;
			bl = map[m].block[bx+by*map[m].bxs];
			for(;bl;bl=bl->next){
				if(bl->type==BL_PC)
					c++;
			}
		}
	}
	return c;
}

/*==========================================
 * map m (x0,y0)-(x1,y1)���̑Sobj�ɑ΂���
 * func���Ă�
 * type!=0 �Ȃ炻�̎�ނ̂�
 *------------------------------------------
 */
void map_foreachinarea(int (*func)(struct block_list*,va_list),int m,int x0,int y0,int x1,int y1,int type,...)
{
	int bx,by;
	struct block_list *bl;
	va_list ap;
	const size_t blockmax=4096;
	struct block_list *list[blockmax];
	int blockcount=0,i;

	va_start(ap,type);
	if(x0<0) x0=0;
	if(y0<0) y0=0;
	if(x1>=map[m].xs) x1=map[m].xs-1;
	if(y1>=map[m].ys) y1=map[m].ys-1;
	if(type==0 || type!=BL_MOB)
		for(by=y0/BLOCK_SIZE;by<=y1/BLOCK_SIZE;by++){
			for(bx=x0/BLOCK_SIZE;bx<=x1/BLOCK_SIZE;bx++){
				bl = map[m].block[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(type && bl->type!=type)
						continue;
					if(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1 && blockcount<blockmax)
						list[blockcount++]=bl;
				}
			}
		}
	if(type==0 || type==BL_MOB)
		for(by=y0/BLOCK_SIZE;by<=y1/BLOCK_SIZE;by++){
			for(bx=x0/BLOCK_SIZE;bx<=x1/BLOCK_SIZE;bx++){
				bl = map[m].block_mob[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1 && blockcount<blockmax)
						list[blockcount++]=bl;
				}
			}
		}
	
	if(blockcount>=blockmax)
		printf("map_foreachinarea: *WARNING* block count too many!\n");
	
	map_freeblock_lock();	// ����������̉�����֎~����
		
	for(i=0;i<blockcount;i++)
		if(list[i]->prev)	// �L�����ǂ����`�F�b�N
			func(list[i],ap);

	map_freeblock_unlock();	// �����������
	
	va_end(ap);
}

/*==========================================
 * ��`(x0,y0)-(x1,y1)��(dx,dy)�ړ���������
 * �̈�O�ɂȂ�̈�(��`��L���`)����obj��
 * �΂���func���Ă�
 *
 * dx,dy��-1,0,1�݂̂Ƃ���i�ǂ�Ȓl�ł��������ۂ��H�j
 *------------------------------------------
 */
void map_foreachinmovearea(int (*func)(struct block_list*,va_list),int m,int x0,int y0,int x1,int y1,int dx,int dy,int type,...)
{
	int bx,by;
	struct block_list *bl;
	va_list ap;

	const size_t blockmax=4096;
	struct block_list *list[blockmax];
	int blockcount=0,i;

	va_start(ap,type);
	if(dx==0 || dy==0){
		// ��`�̈�̏ꍇ
		if(dx==0){
			if(dy<0){
				y0=y1+dy+1;
			} else {
				y1=y0+dy-1;
			}
		} else if(dy==0){
			if(dx<0){
				x0=x1+dx+1;
			} else {
				x1=x0+dx-1;
			}
		}
		if(x0<0) x0=0;
		if(y0<0) y0=0;
		if(x1>=map[m].xs) x1=map[m].xs-1;
		if(y1>=map[m].ys) y1=map[m].ys-1;
		for(by=y0/BLOCK_SIZE;by<=y1/BLOCK_SIZE;by++){
			for(bx=x0/BLOCK_SIZE;bx<=x1/BLOCK_SIZE;bx++){
				bl = map[m].block[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(type && bl->type!=type)
						continue;
					if(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1 && blockcount<blockmax)
						list[blockcount++]=bl;
				}
				bl = map[m].block_mob[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(type && bl->type!=type)
						continue;
					if(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1 && blockcount<blockmax)
						list[blockcount++]=bl;
				}
			}
		}
	}else{
		// L���̈�̏ꍇ
		
		if(x0<0) x0=0;
		if(y0<0) y0=0;
		if(x1>=map[m].xs) x1=map[m].xs-1;
		if(y1>=map[m].ys) y1=map[m].ys-1;
		for(by=y0/BLOCK_SIZE;by<=y1/BLOCK_SIZE;by++){
			for(bx=x0/BLOCK_SIZE;bx<=x1/BLOCK_SIZE;bx++){
				bl = map[m].block[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(type && bl->type!=type)
						continue;
					if(!(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1))
						continue;
					if(((dx>0 && bl->x<x0+dx) || (dx<0 && bl->x>x1+dx) ||
						(dy>0 && bl->y<y0+dy) || (dy<0 && bl->y>y1+dy)) &&
						blockcount<blockmax)
							list[blockcount++]=bl;
				}
				bl = map[m].block_mob[bx+by*map[m].bxs];
				for(;bl;bl=bl->next){
					if(type && bl->type!=type)
						continue;
					if(!(bl->x>=x0 && bl->x<=x1 && bl->y>=y0 && bl->y<=y1))
						continue;
					if(((dx>0 && bl->x<x0+dx) || (dx<0 && bl->x>x1+dx) ||
						(dy>0 && bl->y<y0+dy) || (dy<0 && bl->y>y1+dy)) &&
						blockcount<blockmax)
							list[blockcount++]=bl;
				}
			}
		}

	}

	if(blockcount>=blockmax)
		printf("map_foreachinarea: *WARNING* block count too many!\n");
	
	map_freeblock_lock();	// ����������̉�����֎~����
		
	for(i=0;i<blockcount;i++)
		if(list[i]->prev)	// �L�����ǂ����`�F�b�N
			func(list[i],ap);

	map_freeblock_unlock();	// �����������
	

	va_end(ap);
}

/*==========================================
 * ���A�C�e����G�t�F�N�g�p�̈ꎞobj���蓖��
 * object[]�ւ̕ۑ���id_db�o�^�܂�
 *
 * bl->id�����̒��Őݒ肵�Ė�薳��?
 *------------------------------------------
 */
int map_addobject(struct block_list *bl)
{
	int i;
	if(first_free_object_id<2 || first_free_object_id>=MAX_FLOORITEM)
		first_free_object_id=2;
	for(i=first_free_object_id;i<MAX_FLOORITEM;i++)
		if(object[i]==NULL)
			break;
	if(i>=MAX_FLOORITEM){
		printf("no free object id\n");
		return 0;
	}
	first_free_object_id=i;
	if(last_object_id<i)
		last_object_id=i;
	object[i]=bl;
	numdb_insert(id_db,i,bl);
	return i;
}

/*==========================================
 * �ꎞobject�̉��
 *	map_delobject��free���Ȃ��o�[�W����
 *------------------------------------------
 */
int map_delobjectnofree(int id)
{
	if(object[id]==NULL)
		return 0;

	map_delblock(object[id]);
	numdb_erase(id_db,id);
//	map_freeblock(object[id]);
	object[id]=NULL;

	if(first_free_object_id>id)
		first_free_object_id=id;

	while(last_object_id>2 && object[last_object_id]==NULL)
		last_object_id--;

	return 0;
}

/*==========================================
 * �ꎞobject�̉��
 * block_list����̍폜�Aid_db����̍폜
 * object data��free�Aobject[]�ւ�NULL���
 *
 * add�Ƃ̑Ώ̐��������̂��C�ɂȂ�
 *------------------------------------------
 */
int map_delobject(int id)
{
	struct block_list *obj=object[id];

	if(obj==NULL)
		return 0;

	map_delobjectnofree(id);	
	map_freeblock(obj);

	return 0;
}

/*==========================================
 * �S�ꎞobj�����func���Ă�
 *
 *------------------------------------------
 */
void map_foreachobject(int (*func)(struct block_list*,va_list),int type,...)
{
	int i;
	static const int block_list_max=4096;
	struct block_list *list[block_list_max];
	int block_list_count=0;
	va_list ap;

	va_start(ap,type);


	for(i=2;i<=last_object_id;i++){
		if(object[i]){
			if(type && object[i]->type!=type)
				continue;
			if(block_list_count>=block_list_max)
				printf("map_foreachobject: too many block !\n");
			else
				list[block_list_count++]=object[i];
		}
	}
	
	map_freeblock_lock();
	
	for(i=0;i<block_list_count;i++)
		if( list[i]->prev || list[i]->next )
			func(list[i],ap);

	map_freeblock_unlock();

	va_end(ap);
}

/*==========================================
 * ���A�C�e��������
 *
 * data==0�̎���timer�ŏ�������
 * data!=0�̎��͏E�����ŏ��������Ƃ��ē���
 *
 * ��҂́Amap_clearflooritem(id)��
 * map.h����#define���Ă���
 *------------------------------------------
 */
int map_clearflooritem_timer(int tid,unsigned int tick,int id,int data)
{
	struct flooritem_data *fitem;

	fitem = (struct flooritem_data *)object[id];
	if(fitem==NULL || fitem->bl.type!=BL_ITEM || (!data && fitem->cleartimer != tid)){
		printf("map_clearflooritem_timer : error\n");
		return 1;
	}
	if(data)
		delete_timer(fitem->cleartimer,map_clearflooritem_timer);
	else if(fitem->item_data.card[0] == (short)0xff00)
		intif_delete_petdata(*((long *)(&fitem->item_data.card[2])));
	clif_clearflooritem(fitem,0);
	map_delobject(fitem->bl.id);

	return 0;
}

/*==========================================
 * (m,x,y)�̎���range�}�X���̋�(=�N���\)cell��
 * ������K���ȃ}�X�ڂ̍��W��x+(y<<16)�ŕԂ�
 *
 * ����range=1�ŃA�C�e���h���b�v�p�r�̂�
 *------------------------------------------
 */
int map_searchrandfreecell(int m,int x,int y,int range)
{
	int free_cell,i,j,c;

	for(free_cell=0,i=-range;i<=range;i++){
		if(i+y<0 || i+y>=map[m].ys)
			continue;
		for(j=-range;j<=range;j++){
			if(j+x<0 || j+x>=map[m].xs)
				continue;
			if((c=read_gat(m,j+x,i+y))==1 || c==5)
				continue;
			free_cell++;
		}
	}
	if(free_cell==0)
		return -1;
	free_cell=rand()%free_cell;
	for(i=-range;i<=range;i++){
		if(i+y<0 || i+y>=map[m].ys)
			continue;
		for(j=-range;j<=range;j++){
			if(j+x<0 || j+x>=map[m].xs)
				continue;
			if((c=read_gat(m,j+x,i+y))==1 || c==5)
				continue;
			if(free_cell==0){
				x+=j;
				y+=i;
				i=range+1;
				break;
			}
			free_cell--;
		}
	}

	return x+(y<<16);
}

/*==========================================
 * (m,x,y)�𒆐S��3x3�ȓ��ɏ��A�C�e���ݒu
 *
 * item_data��amount�ȊO��copy����
 *------------------------------------------
 */
int map_addflooritem(struct item *item_data,int amount,int m,int x,int y)
{
	int xy,r;
	struct flooritem_data *fitem;

	if((xy=map_searchrandfreecell(m,x,y,1))<0)
		return 0;
	r=rand();

	fitem = malloc(sizeof(*fitem));
	if(fitem==NULL){
		printf("out of memory : map_addflooritem\n");
		exit(1);
	}
	fitem->bl.type=BL_ITEM;
	fitem->bl.m=m;
	fitem->bl.x=xy&0xffff;
	fitem->bl.y=(xy>>16)&0xffff;

	fitem->bl.id = map_addobject(&fitem->bl);
	if(fitem->bl.id==0){
		free(fitem);
		return 0;
	}

	memcpy(&fitem->item_data,item_data,sizeof(*item_data));
	fitem->item_data.amount=amount;
	fitem->subx=(r&3)*3+3;
	fitem->suby=((r>>2)&3)*3+3;
	fitem->cleartimer=add_timer(gettick()+battle_config.flooritem_lifetime,map_clearflooritem_timer,fitem->bl.id,0);

	map_addblock(&fitem->bl);
	clif_dropflooritem(fitem);

	return fitem->bl.id;
}

/*==========================================
 * charid_db�֒ǉ�(�ԐM�҂�������ΕԐM)
 *------------------------------------------
 */
void map_addchariddb(int charid,char *name)
{
	struct charid2nick *p;
	int req=0;
	p=numdb_search(charid_db,charid);
	if(p==NULL){	// �f�[�^�x�[�X�ɂȂ�
		p = malloc(sizeof(struct charid2nick));
		if(p==NULL){
			printf("out of memory : map_addchariddb\n");
			exit(1);
		}
		p->req_id=0;
	}else
		numdb_erase(charid_db,charid);
	
	req=p->req_id;
	memcpy(p->nick,name,24);
	p->req_id=0;
	numdb_insert(charid_db,charid,p);
	if(req){	// �ԐM�҂�������ΕԐM
		struct map_session_data *sd = map_id2sd(req);
		if(sd!=NULL)
			clif_solved_charname(sd,charid);
	}
}
/*==========================================
 * charid_db�֒ǉ��i�ԐM�v���̂݁j
 *------------------------------------------
 */
int map_reqchariddb(struct map_session_data * sd,int charid)
{
	struct charid2nick *p;
	p=numdb_search(charid_db,charid);
	if(p!=NULL)	// �f�[�^�x�[�X�ɂ��łɂ���
		return 0;
	p = malloc(sizeof(struct charid2nick));
	if(p==NULL){
		printf("out of memory : map_reqchariddb\n");
		exit(1);
	}
	memset(p->nick,0,24);
	p->req_id=sd->bl.id;
	numdb_insert(charid_db,charid,p);
	return 0;
}

/*==========================================
 * id_db��bl��ǉ�
 *------------------------------------------
 */
void map_addiddb(struct block_list *bl)
{
	numdb_insert(id_db,bl->id,bl);
}

/*==========================================
 * id_db����bl���폜
 *------------------------------------------
 */
void map_deliddb(struct block_list *bl)
{
	numdb_erase(id_db,bl->id);
}

/*==========================================
 * nick_db��sd��ǉ�
 *------------------------------------------
 */
void map_addnickdb(struct map_session_data *sd)
{
	strdb_insert(nick_db,sd->status.name,sd);
}

/*==========================================
 * PC��quit���� map.c����
 *
 * quit�����̎�̂��Ⴄ�悤�ȋC�����Ă���
 *------------------------------------------
 */
int map_quit(struct map_session_data *sd)
{
	if(sd->chatID)	// �`���b�g����o��
		chat_leavechat(sd);
		
	if(sd->trade_partner)	// ����𒆒f����
		trade_tradecancel(sd);

	if(sd->party_invite>0)	// �p�[�e�B���U�����ۂ���
		party_reply_invite(sd,sd->party_invite_account,0);

	if(sd->guild_invite>0)	// �M���h���U�����ۂ���
		guild_reply_invite(sd,sd->guild_invite,0);
	if(sd->guild_alliance>0)	// �M���h�������U�����ۂ���
		guild_reply_reqalliance(sd,sd->guild_alliance_account,0);

	party_send_logout(sd);	// �p�[�e�B�̃��O�A�E�g���b�Z�[�W���M

	guild_send_memberinfoshort(sd,0);	// �M���h�̃��O�A�E�g���b�Z�[�W���M

	pc_cleareventtimer(sd);	// �C�x���g�^�C�}��j������

	skill_castcancel(&sd->bl);	// �r���𒆒f����
	skill_status_change_clear(&sd->bl);	// �X�e�[�^�X�ُ����������
	skill_clear_unitgroup(&sd->bl);	// �X�L�����j�b�g�O���[�v�̍폜
	pc_stopattack(sd);
	pc_delghosttimer(sd);
	pc_delspiritball(sd,10,1);

	storage_storage_quitsave(sd);	// �q�ɂ��J���Ă�Ȃ�ۑ�����

	clif_clearchar_area(&sd->bl,2);
	map_delblock(&sd->bl);

	numdb_erase(id_db,sd->bl.id);
	strdb_erase(nick_db,sd->status.name);

	return 0;
}

/*==========================================
 * id�ԍ���PC��T���B���Ȃ����NULL
 *------------------------------------------
 */
struct map_session_data * map_id2sd(int id)
{
	struct block_list *bl;

	bl=numdb_search(id_db,id);
	if(bl && bl->type==BL_PC)
		return (struct map_session_data*)bl;
	return NULL;
}

/*==========================================
 * char_id�ԍ��̖��O��T��
 *------------------------------------------
 */
char * map_charid2nick(int id)
{
	struct charid2nick *p=numdb_search(charid_db,id);
	if(p==NULL)
		return NULL;
	if(p->req_id!=0)
		return NULL;
	return p->nick;
}

/*==========================================
 * ���O��nick��PC��T���B���Ȃ����NULL
 *------------------------------------------
 */
struct map_session_data * map_nick2sd(char *nick)
{
	return strdb_search(nick_db,nick);
}

/*==========================================
 * id�ԍ��̕���T��
 * �ꎞobject�̏ꍇ�͔z��������̂�
 *------------------------------------------
 */
struct block_list * map_id2bl(int id)
{
	if(id<sizeof(object)/sizeof(object[0]))
		return object[id];
	return numdb_search(id_db,id);
}

/*==========================================
 * id_db���̑S�Ă�func�����s
 *------------------------------------------
 */
int map_foreachiddb(int (*func)(void*,void*,va_list),...)
{
	va_list ap;

	va_start(ap,func);
	numdb_foreach(id_db,func,ap);
	va_end(ap);
	return 0;
}

/*==========================================
 * map.npc�֒ǉ� (warp���̗̈掝���̂�)
 *------------------------------------------
 */
int map_addnpc(int m,struct npc_data *nd)
{
	int i;
	if(m<0 || m>=map_num)
		return -1;
	for(i=0;i<map[m].npc_num && i<MAX_NPC_PER_MAP;i++)
		if(map[m].npc[i]==NULL)
			break;
	if(i==MAX_NPC_PER_MAP){
		printf("too many NPCs in one map %s\n",map[m].name);
		return -1;
	}
	if(i==map[m].npc_num){
		map[m].npc_num++;
	}
	map[m].npc[i]=nd;
	nd->n = i;
	numdb_insert(id_db,nd->bl.id,nd);

	return i;
}

/*==========================================
 * map������map�ԍ��֕ϊ�
 *------------------------------------------
 */
int map_mapname2mapid(char *name)
{
	struct map_data *md;

	md=strdb_search(map_db,name);
	if(md==NULL || md->gat==NULL)
		return -1;
	return md->m;
}

/*==========================================
 * ���Imap������ip,port�ϊ�
 *------------------------------------------
 */
int map_mapname2ipport(char *name,int *ip,int *port)
{
	struct map_data_other_server *mdos;

	mdos=strdb_search(map_db,name);
	if(mdos==NULL || mdos->gat)
		return -1;
	*ip=mdos->ip;
	*port=mdos->port;
	return 0;
}

/*==========================================
 * �މ�̕������v�Z
 *------------------------------------------
 */
int map_calc_dir( struct block_list *src,int x,int y)
{
	int dir=0;
	int dx=x-src->x,dy=y-src->y;
	if( dx==0 && dy==0 ){	// �މ�̏ꏊ��v
		dir=0;	// ��
	}else if( dx>=0 && dy>=0 ){	// �����I�ɉE��
		dir=7;						// �E��
		if( dx*3-1<dy ) dir=0;		// ��
		if( dx>dy*3 ) dir=6;		// �E
	}else if( dx>=0 && dy<=0 ){	// �����I�ɉE��
		dir=5;						// �E��
		if( dx*3-1<-dy ) dir=4;		// ��
		if( dx>-dy*3 ) dir=6;		// �E
	}else if( dx<=0 && dy<=0 ){ // �����I�ɍ���
		dir=3;						// ����
		if( dx*3+1>dy ) dir=4;		// ��
		if( dx<dy*3 ) dir=2;		// ��
	}else{						// �����I�ɍ���
		dir=1;						// ����
		if( -dx*3-1<dy ) dir=0;		// ��
		if( -dx>dy*3 ) dir=2;		// ��
	}
	return dir;
}

// gat�n
/*==========================================
 * (m,x,y)�̏�Ԃ𒲂ׂ�
 *------------------------------------------
 */
int map_getcell(int m,int x,int y)
{
	if(x<0 || x>=map[m].xs-1 || y<0 || y>=map[m].ys-1)
		return 1;
	return map[m].gat[x+y*map[m].xs];
}

/*==========================================
 * (m,x,y)�̏�Ԃ�t�ɂ���
 *------------------------------------------
 */
int map_setcell(int m,int x,int y,int t)
{
	if(x<0 || x>=map[m].xs || y<0 || y>=map[m].ys)
		return t;
	return map[m].gat[x+y*map[m].xs]=t;
}

/*==========================================
 * ���I�Ǘ��̃}�b�v��db�ɒǉ�
 *------------------------------------------
 */
int map_setipport(char *name,unsigned long ip,int port)
{
	struct map_data *md;
	struct map_data_other_server *mdos;

	md=strdb_search(map_db,name);
	if(md==NULL){ // not exist -> add new data
		mdos=malloc(sizeof(*mdos));
		if(mdos==NULL){
			printf("out of memory : map_setipport\n");
			exit(1);
		}
		memcpy(mdos->name,name,16);
		mdos->gat  = NULL;
		mdos->ip   = ip;
		mdos->port = port;
		strdb_insert(map_db,name,mdos);
	} else {
		if(md->gat){ // local -> check data
			if(ip!=clif_getip() || port!=clif_getport()){
				printf("from char server : %s -> %08lx:%d\n",name,ip,port);
				return 1;
			}
		} else { // update
			mdos=(struct map_data_other_server *)md;
			mdos->ip   = ip;
			mdos->port = port;
		}
	}
	return 0;
}

// ����������
/*==========================================
 * �}�b�v1���ǂݍ���
 *------------------------------------------
 */
static int map_readmap(int m,char *fn)
{
	unsigned char *gat;
	int s;
	int x,y,xs,ys;
	struct gat_1cell {float high[4]; int type;} *p;

	// read & convert fn
	gat=grfio_read(fn);
	if(gat==NULL)
		return -1;

	map[m].m=m;
	xs=map[m].xs=*(int*)(gat+6);
	ys=map[m].ys=*(int*)(gat+10);
	map[m].gat=malloc(s=map[m].xs*map[m].ys);
	if(map[m].gat==NULL){
		printf("out of memory : map_readmap gat\n");
		exit(1);
	}
	map[m].npc_num=0;
	map[m].users=0;
	map[m].flag=0;
	for(y=0;y<ys;y++){
		p=(struct gat_1cell*)(gat+y*xs*20+14);
		for(x=0;x<xs;x++){
			if(p->type==0){
				// ���ꔻ��
				map[m].gat[x+y*xs]=(p->high[0]>3 || p->high[1]>3 || p->high[2]>3 || p->high[3]>3) ? 3 : 0;
			} else {
				map[m].gat[x+y*xs]=p->type;
			}
			p++;
		}
	}
	free(gat);

	map[m].bxs=(xs+BLOCK_SIZE-1)/BLOCK_SIZE;
	map[m].bys=(ys+BLOCK_SIZE-1)/BLOCK_SIZE;

	map[m].block=malloc(map[m].bxs*map[m].bys*sizeof(struct block_list*));
	if(map[m].block==NULL){
		printf("out of memory : map_readmap block\n");
		exit(1);
	}
	memset(map[m].block,0,map[m].bxs*map[m].bys*sizeof(struct block_list*));

	map[m].block_mob=malloc(map[m].bxs*map[m].bys*sizeof(struct block_list*));
	if(map[m].block_mob==NULL){
		printf("out of memory : map_readmap block_mob\n");
		exit(1);
	}
	memset(map[m].block_mob,0,map[m].bxs*map[m].bys*sizeof(struct block_list*));

	strdb_insert(map_db,map[m].name,&map[m]);
	printf("%s read done\n",fn);

	return 0;
}

/*==========================================
 * �S�Ă�map�f�[�^��ǂݍ���
 *------------------------------------------
 */
int map_readallmap(void)
{
	int i;
	char fn[256];

	// ��ɑS���̃}�b�v�̑��݂��m�F
	for(i=0;i<map_num;i++){
		if(strstr(map[i].name,".gat")==NULL)
			continue;
		sprintf(fn,"data\\%s",map[i].name);
		grfio_size(fn);
	}
	for(i=0;i<map_num;i++){
		if(strstr(map[i].name,".gat")==NULL)
			continue;
		sprintf(fn,"data\\%s",map[i].name);
		map_readmap(i,fn);
	}
	return 0;
}

/*==========================================
 * �ǂݍ���map��ǉ�����
 *------------------------------------------
 */
int map_addmap(char *mapname)
{
	if(map_num>=MAX_MAP_PER_SERVER-1){
		printf("too many map\n");
		return 1;
	}
	memcpy(map[map_num].name,mapname,16);
	map_num++;
	return 0;
}

/*==========================================
 * �ݒ�t�@�C����ǂݍ���
 *------------------------------------------
 */
int map_config_read(char *cfgName)
{
	int i;
	char line[1024],w1[1024],w2[1024];
	FILE *fp;

	fp=fopen(cfgName,"r");
	if(fp==NULL){
		printf("file not found: %s\n",cfgName);
		return 1;
	}
	while(fgets(line,1020,fp)){
		if(line[0] == '/' && line[1] == '/')
			continue;
		i=sscanf(line,"%[^:]:%s",w1,w2);
		if(i!=2)
			continue;
		if(strcmpi(w1,"userid")==0){
			chrif_setuserid(w2);
		} else if(strcmpi(w1,"passwd")==0){
			chrif_setpasswd(w2);
		} else if(strcmpi(w1,"char_ip")==0){
			chrif_setip(w2);
		} else if(strcmpi(w1,"char_port")==0){
			chrif_setport(atoi(w2));
		} else if(strcmpi(w1,"map_ip")==0){
			clif_setip(w2);
		} else if(strcmpi(w1,"map_port")==0){
			clif_setport(atoi(w2));
		} else if(strcmpi(w1,"map")==0){
			map_addmap(w2);
		} else if(strcmpi(w1,"npc")==0){
			npc_addsrcfile(w2);
		} else if(strcmpi(w1,"data_grf")==0){
			grfio_setdatafile(w2);
		} else if(strcmpi(w1,"sdata_grf")==0){
			grfio_setsdatafile(w2);
		} else if(strcmpi(w1,"autosave_time")==0){
			autosave_interval=atoi(w2)*1000;
			if(autosave_interval <= 0)
				autosave_interval = DEFAULT_AUTOSAVE_INTERVAL;
		}
	}
	fclose(fp);

	return 0;
}

/*==========================================
 * map�I�I��������
 *------------------------------------------
 */
void do_final(void)
{
	do_final_itemdb();
	do_final_storage();
}

/*==========================================
 * map�I�������̑匳
 *------------------------------------------
 */
int do_init(int argc,char *argv[])
{
	srand(gettick());

	if(argc < 2) argv[1] = MAP_CONF_NAME;
	if(argv[1]){
		if(map_config_read(argv[1]))
			exit(1);
	}
	battle_config_read((argc>2)?argv[2]:BATTLE_CONF_FILENAME);
	atcommand_config_read(ATCOMMAND_CONF_FILENAME);

	atexit(do_final);

	id_db = numdb_init();
	map_db = strdb_init(16);
	nick_db = strdb_init(24);
	charid_db = numdb_init();

	grfio_init();
	map_readallmap();

	add_timer_func_list(map_clearflooritem_timer,"map_clearflooritem_timer");

	do_init_chrif();
	do_init_clif();
	do_init_mob();	// npc�̏�����������mob_spawn���āAmob_db���Q�Ƃ���̂�init_npc����
	do_init_script();
	do_init_npc();
	do_init_pc();
	do_init_itemdb();
	do_init_storage();
	do_init_party();
	do_init_guild();
	do_init_skill();
	do_init_pet();
	npc_event_do_oninit();	// npc��OnInit�C�x���g���s

	return 0;
}

