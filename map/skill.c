/* �X�L���֌W */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timer.h"

#include "skill.h"
#include "map.h"
#include "clif.h"
#include "pc.h"
#include "mob.h"
#include "battle.h"
#include "party.h"
#include "itemdb.h"

#define SKILLUNITTIMER_INVERVAL	100


/* �X�L���ԍ������X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable[]={	/* skill.h��enum��SC_***�Ƃ��킹�邱�� */
/* 0- */
	-1,-1,-1,-1,-1,-1,
	SC_PROVOKE,			/* �v���{�b�N */
	-1, 1,-1,
/* 10- */
	SC_SIGHT,			/* �T�C�g */
	-1,-1,-1,-1,
	SC_FREEZE,			/* �t���X�g�_�C�o�[ */
	SC_STONE,			/* �X�g�[���J�[�X */
	-1,-1,-1,
/* 20- */
	-1,-1,-1,-1,
	SC_RUWACH,			/* ���A�t */
	-1,-1,-1,-1,
	SC_INCREASEAGI,		/* ���x���� */
/* 30- */
	SC_DECREASEAGI,		/* ���x���� */
	-1,
	SC_SIGNUMCRUCIS,	/* �V�O�i���N���V�X */
	SC_ANGELUS,			/* �G���W�F���X */
	SC_BLESSING,		/* �u���b�V���O */
	-1,-1,-1,-1,-1,
/* 40- */
	-1,-1,-1,-1,-1,
	SC_CONCENTRATE,		/* �W���͌��� */
	-1,-1,-1,-1,
/* 50- */
	-1,
	SC_HIDDING,			/* �n�C�f�B���O */
	-1,-1,-1,-1,-1,-1,-1,-1,
/* 60- */
	SC_TWOHANDQUICKEN,	/* 2HQ */
	-1,-1,-1,-1,-1,
	SC_IMPOSITIO,		/* �C���|�V�e�B�I�}�k�X */
	SC_SUFFRAGIUM,		/* �T�t���M�E�� */
	SC_ASPERSIO,		/* �A�X�y���V�I */
	SC_BENEDICTIO,		/* ���̍~�� */
/* 70- */
	-1,-1,-1,
	SC_KYRIE,			/* �L���G�G���C�\�� */
	SC_MAGNIFICAT,		/* �}�O�j�t�B�J�[�g */
	SC_GLORIA,			/* �O�����A */
	SC_DIVINA,			/* ���b�N�X�f�B�r�[�i */
	-1,
	SC_AETERNA,			/* ���b�N�X�G�[�e���i */
	-1,
/* 80- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 90- */
	-1,-1,
	SC_QUAGMIRE,		/* �N�@�O�}�C�A */
	-1,-1,-1,-1,-1,-1,-1,
/* 100- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 110- */
	-1,
	SC_ADRENALINE,		/* �A�h���i�������b�V�� */
	SC_WEAPONPERFECTION,/* �E�F�|���p�[�t�F�N�V���� */
	SC_OVERTHRUST,		/* �I�[�o�[�g���X�g */
	SC_MAXIMIZEPOWER,	/* �}�L�V�}�C�Y�p���[ */
	-1,-1,-1,-1,-1,
/* 120- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 130- */
	-1,-1,-1,-1,-1,
	SC_CLOAKING,		/* �N���[�L���O */
	SC_STAN,			/* �\�j�b�N�u���[ */
	-1,
	SC_ENCPOISON,		/* �G���`�����g�|�C�Y�� */
	SC_POISONREACT,		/* �|�C�Y�����A�N�g */
/* 140- */
	SC_POISON,			/* �x�m���_�X�g */
	-1,-1,
	SC_TRICKDEAD,		/* ���񂾂ӂ� */
	-1,-1,-1,-1,-1,-1,
/* 150- */
	-1,-1,-1,-1,-1,
	SC_LOUD,			/* ���E�h�{�C�X */
	-1,
	SC_ENERGYCOAT,		/* �G�i�W�[�R�[�g */
	-1,-1,
/* 160- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 210- */
	-1,-1,-1,-1,-1,
	SC_STRIPWEAPON,
	SC_STRIPSHIELD,
	SC_STRIPARMOR,
	SC_STRIPHELM,
	-1,
/* 220- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 230- */
	-1,-1,-1,-1,
	SC_CP_WEAPON,
	SC_CP_SHIELD,
	SC_CP_ARMOR,
	SC_CP_HELM,
	-1,-1,
/* 240- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,
	SC_AUTOGUARD,
/* 250- */
	-1,
	SC_REFLECTSHIELD,
	-1,-1,-1,
	SC_DEVOTION,
	SC_PROVIDENCE,
	SC_DEFENDER,
	SC_SPEARSQUICKEN,
	-1,
/* 260- */
	-1,-1,-1,-1,-1,-1,-1,-1,
	SC_STEELBODY,
	-1,
/* 270- */
	SC_EXPLOSIONSPIRITS,-1,-1,-1,-1,
	SC_CASTCANCEL,
	-1,
	SC_SPELLBREAKER,
	SC_FREECAST,
	-1,
/* 280- */
	SC_FLAMELAUNCHER,
	SC_FROSTWEAPON,
	SC_LIGHTNINGLOADER,
	SC_SEISMICWEAPON,
	-1,
	SC_VOLCANO,
	SC_DELUGE,
	-1,-1,-1,
/* 290- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
/* 300- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,
	SC_DRUMBATTLE,
/* 310- */
	-1,-1,-1,
	SC_SIEGFRIED,
	-1,-1,-1,-1,-1,
	SC_WHISTLE,
/* 320- */
	SC_ASSNCROS,
	SC_POEMBRAGI,
	SC_APPLEIDUN,
	-1,-1,-1,-1,-1,-1,
	SC_FORTUNE,
/* 330- */
	SC_SERVICE4U,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

/* �X�L���f�[�^�x�[�X */
struct skill_db skill_db[MAX_SKILL_DB];

/* �A�C�e���쐬�f�[�^�x�[�X */
struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

int skill_get_range( int id ){ return skill_db[id].range; }
int	skill_get_hit( int id ){ return skill_db[id].hit; }
int	skill_get_inf( int id ){ return skill_db[id].inf; }
int	skill_get_pl( int id ){ return skill_db[id].pl; }
int	skill_get_nk( int id ){ return skill_db[id].nk; }
int	skill_get_max( int id ){ return skill_db[id].max; }
int	skill_get_sp( int id ,int lv ){ return skill_db[id].sp[lv-1]; }
int	skill_get_num( int id ,int lv ){ return skill_db[id].num[lv-1]; }
int	skill_get_cast( int id ,int lv ){ return skill_db[id].cast[lv-1]; }
int	skill_get_delay( int id ,int lv ){ return skill_db[id].delay[lv-1]; }
int	skill_get_inf2( int id ){ return skill_db[id].inf2; }


/* �v���g�^�C�v */
struct skill_unit_group *skill_unitsetting( struct block_list *src, int skillid,int skilllv,int x,int y,int flag);

/* �X�L�����j�b�gID��Ԃ��i������f�[�^�x�[�X�ɓ��ꂽ���ȁj */
int skill_get_unit_id(int id,int flag)
{
	switch(id){
	case MG_SAFETYWALL:		return 0x7e;				/* �Z�C�t�e�B�E�H�[�� */
	case MG_FIREWALL:		return 0x7f;				/* �t�@�C�A�[�E�H�[�� */
	case AL_WARP:			return (flag==0)?0x81:0x80;	/* ���[�v�|�[�^�� */
	case PR_BENEDICTIO:		return 0x82;				/* ���̍~�� */
	case PR_SANCTUARY:		return 0x83;				/* �T���N�`���A�� */
	case PR_MAGNUS:			return 0x84;				/* �}�O�k�X�G�N�\�V�Y�� */
	case AL_PNEUMA:			return 0x85;				/* �j���[�} */
	case WZ_METEOR:			return 0x86;				/* ���e�I�X�g�[�� */
	case WZ_VERMILION:		return 0x86;				/* ���[�h�I�u���@�[�~���I�� */
	case WZ_STORMGUST:		return 0x86;				/* �X�g�[���K�X�g(�Ƃ肠����LoV�Ɠ����ŏ���) */
	case CR_GRANDCROSS:		return 0x86;				/* �O�����h�N���X */
	case WZ_FIREPILLAR:		return (flag==0)?0x87:0x88;	/* �t�@�C�A�[�s���[ */
	case HT_TALKIEBOX:		return (flag==0)?0x99:0x8c;	/* �g�[�L�[�{�b�N�X */
	case WZ_ICEWALL:		return 0x8d;				/* �A�C�X�E�H�[�� */
	case WZ_QUAGMIRE:		return 0x8e;				/* �N�@�O�}�C�A */
	case HT_BLASTMINE:		return 0x8f;				/* �u���X�g�}�C�� */
	case HT_SKIDTRAP:		return 0x90;				/* �X�L�b�h�g���b�v */
	case HT_ANKLESNARE:		return 0x91;				/* �A���N���X�l�A */
	case AS_VENOMDUST:		return 0x92;				/* �x�m���_�X�g */
	case HT_LANDMINE:		return 0x93;				/* �����h�}�C�� */
	case HT_SHOCKWAVE:		return 0x94;				/* �V���b�N�E�F�[�u�g���b�v */
	case HT_SANDMAN:		return 0x95;				/* �T���h�}�� */
	case HT_FLASHER:		return 0x96;				/* �t���b�V���[ */
	case HT_FREEZINGTRAP:	return 0x97;				/* �t���[�W���O�g���b�v */
	case HT_CLAYMORETRAP:	return 0x98;				/* �N���C���A�[�g���b�v */
	case SA_DELUGE:			return 0x9b;				/* �f�����[�W */
	case BD_LULLABY:		return 0x9e;				/* �q��� */
	case BD_RICHMANKIM:		return 0x9f;				/* �j�����h�̉� */
	case BD_ETERNALCHAOS:	return 0xa0;				/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:return 0xa1;					/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:	return 0xa2;				/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:		return 0xa3;				/* ���L�̋��� */
	case BD_INTOABYSS:		return 0xa4;				/* �[���̒��� */
	case BD_SIEGFRIED:		return 0xa5;				/* �s���g�̃W�[�N�t���[�h */
	case BA_DISSONANCE:		return 0xa6;				/* �s���a�� */
	case BA_WHISTLE:		return 0xa7;				/* ���J */
	case BA_ASSASSINCROSS:	return 0xa8;				/* �[�z�̃A�T�V���N���X */
	case BA_POEMBRAGI:		return 0xa9;				/* �u���M�̎� */
	case BA_APPLEIDUN:		return 0xaa;				/* �C�h�D���̗ь� */
	case DC_UGLYDANCE:		return 0xab;				/* ��������ȃ_���X */
	case DC_HUMMING:		return 0xac;				/* �n�~���O */
	case DC_DONTFORGETME:	return 0xad;				/* ����Y��Ȃ��Łc */
	case DC_FORTUNEKISS:	return 0xae;				/* �K�^�̃L�X */
	case DC_SERVICEFORYOU:	return 0xaf;				/* �T�[�r�X�t�H�[���[ */
	case RG_GRAFFITI:		return 0xb0;				/* �O���t�B�e�B */
	}
	return 0;
	/*
	0x89,0x8a,0x8b �\������
	0x9a �������̉r���݂����ȃG�t�F�N�g
	0x9b �������̉r���݂����ȃG�t�F�N�g
	0x9c �������̉r���݂����ȃG�t�F�N�g
	0x9d ���������ȃG�t�F�N�g
	*/
}



int skill_check_condition( struct map_session_data *sd );

int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );


/*==========================================
 * �X�L���ǉ�����
 *------------------------------------------
 */
int skill_additional_effect( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick)
{
	struct map_session_data *sd=NULL;
	struct map_session_data *sd2=NULL;
	int skill;
	int rate;
	
	if(src->type==BL_PC)
		sd=(struct map_session_data *)src;
	if(bl->type==BL_PC)
		sd2=(struct map_session_data *)bl;

	switch(skillid){
	case 0:					/* �ʏ�U�� */
		/* ������ */
		if( sd && pc_isfalcon(sd) && (skill=pc_checkskill(sd,HT_BLITZBEAT))>0 &&
			rand()%1000 <= sd->paramc[5]*10/3+1 ) {
			int lv=(sd->status.job_level+9)/10;
			skill_castend_damage_id(src,bl,HT_BLITZBEAT,(skill<lv)?skill:lv,tick,0xf00000);
		}
		// �X�i�b�`���[
		if(sd && (skill=pc_checkskill(sd,RG_SNATCHER)) > 0)
			if((skill*15 + 55) + pc_checkskill(sd,TF_STEAL)*10 > rand()%1000)
				if(pc_steal_item(sd,bl))
					clif_skill_nodamage(src,bl,TF_STEAL,0,1);
		break;

	case SM_BASH:			/* �o�b�V���i�}���U���j */
		if( sd && (skill=pc_checkskill(sd,SM_FATALBLOW))>0 ){
			if( rand()%100 < 6*(skilllv-5) )
				skill_status_change_start(bl,SC_STAN,skilllv,5000);
		}
		break;

	case TF_POISON:			/* �C���x�i�� */
		if(battle_get_elem_type(bl)!=9 && rand()%100< 2*skilllv+10 )
			skill_status_change_start(bl,SC_POISON,skilllv,0);
		break;

	case AS_SONICBLOW:		/* �\�j�b�N�u���[ */
		if( rand()%100 < 2*skilllv+10 )
			skill_status_change_start(bl,SC_STAN,skilllv,5000);
		break;

	case MG_FROSTDIVER:		/* �t���X�g�_�C�o�[ */
	case WZ_FROSTNOVA:		/* �t���X�g�m���@ */
	case WZ_STORMGUST:		/* �X�g�[���K�X�g */
	case HT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
	case BA_FROSTJOKE:		/* �����W���[�N */
/*
		rate=battle_get_lv(src)/2 +battle_get_int(src)/3+ skilllv*2 +15 -battle_get_mdef(bl);
		if(rate>95)rate=95;
*/
		rate=skilllv*3+35;
		if( rand()%100 < rate )
			skill_status_change_start(bl,SC_FREEZE,skilllv,0);
		break;

	case HT_LANDMINE:		/* �����h�}�C�� */
		if( rand()%100 < 5*skilllv+30 ){
			skill_status_change_start(bl,SC_STAN,skilllv,skilllv*500+1000);
		}
		break;

	case HT_ANKLESNARE:		/* �A���N���X�l�A */
		{
			int sec=(battle_get_mode(bl)&0x20)?1000:5000;
			skill_status_change_start(bl,SC_ANKLE,skilllv,skilllv*sec);
		}
		break;

	case HT_SANDMAN:		/* �T���h�}�� */
		if( rand()%100 < 5*skilllv+30 ){
			skill_status_change_start(bl,SC_SLEEP,skilllv,30000);
		}
		break;

	case TF_SPRINKLESAND:	/* ���܂� */
		if( rand()%100 < 15 )
			skill_status_change_start(bl,SC_BLIND,1,0);
		break;

	case TF_THROWSTONE:		/* �Γ��� */
		if( rand()%100 < 5 )
			skill_status_change_start(bl,SC_STAN,1,3000);
		break;

	case CR_HOLYCROSS:		/* ���܂� */
		if( rand()%100 < 3*skilllv )
			skill_status_change_start(bl,SC_BLIND,1,0);
		break;

#if 0
	case BA_FROSTJOKE:		/* �����W���[�N */
		if( rand()%100 < 15+5*skilllv )
			skill_status_change_start(bl,SC_FREEZE,1,0);
		break;
#endif

	/* MOB�̒ǉ����ʕt���X�L�� */
	case NPC_POISON:
	case NPC_BLINDATTACK:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	case NPC_PETRIFYATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
		{
			const int sc[]={
				SC_POISON,	SC_BLIND,	SC_SILENCE,	SC_STAN,
				SC_STONE,	SC_CURSE,	SC_SLEEP	};
			const int sc2[]={
				6000,		0,			6000,			1000,
				1000,		0,			6000	};
			skill_status_change_start(bl,
				sc[skillid-NPC_POISON],skilllv,sc2[skillid-NPC_POISON]*skilllv);
		}
		break;
	}

	if(sd){	/* �J�[�h�ɂ��ǉ����� */
		int i;
		for(i=SC_STONE;i<=SC_BLIND;i++){
			if( sd->addeff[i-SC_STONE]>0 && rand()%100<sd->addeff[i-SC_STONE] ){
				printf("skill_addeff: card�ɂ��ُ픭�� %d %d\n",i,sd->addeff[i-SC_STONE]);
				skill_status_change_start(bl,i,1,5);
			}
		}
	}

	return 0;
}

/*=========================================================================
 �X�L���U��������΂�����
-------------------------------------------------------------------------*/
int skill_blown( struct block_list *src, struct block_list *target,int count)
{
	static const int dirx[8]={0,-1,-1,-1,0,1,1,1};
	static const int diry[8]={1,1,0,-1,-1,-1,0,1};
	int dx=0,dy=0,nx,ny;
	int x=target->x,y=target->y;
	int ret;
	int moveblock;
	struct map_session_data *sd=NULL;
	struct mob_data *md=NULL;
	
	if(target->type==BL_PC)
		sd=(struct map_session_data *)target;
	else if(target->type==BL_MOB)
		md=(struct mob_data *)target;

	if(!(count&0x10000 && (sd||md))){	/* �w��Ȃ��Ȃ�ʒu�֌W������������߂� */
		dx=target->x-src->x; dx=(dx>0)?1:((dx<0)?-1: 0);
		dy=target->y-src->y; dy=(dy>0)?1:((dy<0)?-1: 0);
	}
	if(dx==0 && dy==0){
		int dir=(sd)?sd->dir:md->dir;
		if(dir>=0 && dir<8){
			dx=-dirx[dir];
			dy=-diry[dir];
		}
	}

	ret=path_blownpos(target->m,x,y,dx,dy,count&0xff);
	nx=ret>>16;
	ny=ret&0xffff;
	moveblock=( x/BLOCK_SIZE != nx/BLOCK_SIZE || y/BLOCK_SIZE != ny/BLOCK_SIZE);

	if(sd){
		sd->to_x=nx;
		sd->to_y=ny;
	}else if(md){
		md->to_x=nx;
		md->to_y=ny;
	}
	if(count&0x20000){
		if(sd){
			clif_walkok(sd);
			clif_movechar(sd);
		}
		if(md)
			clif_fixmobpos(md);
	}

	if(sd)	/* ��ʊO�ɏo���̂ŏ��� */
		map_foreachinmovearea(clif_pcoutsight,
			target->m,x-AREA_SIZE,y-AREA_SIZE,
			x+AREA_SIZE,y+AREA_SIZE,dx,dy,0,sd);
	if(md)
		map_foreachinmovearea(clif_moboutsight,
			target->m,x-AREA_SIZE,y-AREA_SIZE,
			x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,md);

	if(moveblock) map_delblock(target);
	target->x=nx;
	target->y=ny;
	if(moveblock) map_addblock(target);


	skill_unit_move(target,gettick(),count+2);	/* �X�L�����j�b�g�̔��� */

	if(sd)	/* ��ʓ��ɓ����Ă����̂ŕ\�� */
		map_foreachinmovearea(clif_pcinsight,
			target->m,nx-AREA_SIZE,ny-AREA_SIZE,
			nx+AREA_SIZE,ny+AREA_SIZE,-dx,-dy,0,sd);
	if(md)
		map_foreachinmovearea(clif_mobinsight,
			target->m,nx-AREA_SIZE,ny-AREA_SIZE,
			nx+AREA_SIZE,ny+AREA_SIZE,-dx,-dy,BL_PC,md);
	return 0;
}


/*
 * =========================================================================
 * �X�L���U�����ʏ����܂Ƃ�
 * flag�̐����B16�i�}
 * 	00XRTTff
 *  ff	= magic�Ōv�Z�ɓn�����j
 *	TT	= �p�P�b�g��type����(0�Ńf�t�H���g�j
 *  X   = �p�P�b�g�̃X�L��Lv
 *  R	= �\��iskill_area_sub�Ŏg�p����j
 *-------------------------------------------------------------------------
 */
int skill_attack( int attack_type, struct block_list* src, struct block_list *dsrc,
	 struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct Damage dmg;
	int type=-1,lv=(flag>>20)&0xf;
	dmg=battle_calc_attack(attack_type, src,bl, skillid,skilllv, flag&0xff );
	
	if(lv==15)lv=-1;
	
	
	if( flag&0xff00 )
		type=(flag&0xff00)>>8;

	if( dmg.blewcount ){	/* ������΂������Ƃ��̃p�P�b�g */
		skill_blown(dsrc,bl,dmg.blewcount);
		clif_skill_damage2(dsrc,bl,tick,dmg.amotion,dmg.dmotion,
			dmg.damage, dmg.div_, skillid, (lv!=0)?lv:skilllv, type );
	} else			/* �X�L���̃_���[�W�p�P�b�g */
		clif_skill_damage(dsrc,bl,tick,dmg.amotion,dmg.dmotion,
			dmg.damage, dmg.div_, skillid, (lv!=0)?lv:skilllv, type );

	/* ���ۂɃ_���[�W�������s�� */
	battle_damage(src,bl,(dmg.damage+dmg.damage2));
	/* �_���[�W������Ȃ�ǉ����ʔ��� */
	if((dmg.damage+dmg.damage2)>0)
		skill_additional_effect(src,bl,skillid,skilllv,tick);
	
	if(bl->type==BL_MOB && src!=bl)	/* �X�L���g�p������MOB�X�L�� */
		mobskill_use((struct mob_data *)bl,tick,MSC_SKILLUSED|(skillid<<16));
	
	return (dmg.damage+dmg.damage2);	/* �^�_����Ԃ� */
}


/*==========================================
 * �X�L���͈͍U���p(map_foreachinarea����Ă΂��)
 * flag�ɂ��āF16�i�}���m�F
 * MSB <- 00fTffff ->LSB
 *	T	=�^�[�Q�b�g�I��p(BCT_*)
 *  ffff=���R�Ɏg�p�\
 *  0	=�\��B0�ɌŒ�
 *------------------------------------------
 */
static int skill_area_temp[8];	/* �ꎞ�ϐ��B�K�v�Ȃ�g���B */
typedef int (*SkillFunc)(struct block_list *,struct block_list *,int,int,unsigned int,int);
int skill_area_sub( struct block_list *bl,va_list ap )
{
	struct block_list *src;
	int skill_id,skill_lv,flag;
	unsigned int tick;
	SkillFunc func;
	
	if(bl->type!=BL_PC && bl->type!=BL_MOB)
		return 0;

	src=va_arg(ap,struct block_list *);
	skill_id=va_arg(ap,int);
	skill_lv=va_arg(ap,int);
	tick=va_arg(ap,unsigned int);
	flag=va_arg(ap,int);
	func=va_arg(ap,SkillFunc);

	if(battle_check_target(src,bl,flag))
		func(src,bl,skill_id,skill_lv,tick,flag);
	return 0;
}
/*=========================================================================
 * �͈̓X�L���g�p������������������
 */
/* �Ώۂ̐����J�E���g����B�iskill_area_temp[0]�����������Ă������Ɓj */
int skill_area_sub_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	skill_area_temp[0]++;
	return 0;
}


/* �͈̓X�L���g�p���������������܂�
 * -------------------------------------------------------------------------
 */


/*==========================================
 * �X�L���g�p�i�r�������AID�w��U���n�j
 * �i�X�p�Q�b�e�B�Ɍ����ĂP���O�i�I(�_���|)�j
 *------------------------------------------
 */
int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd=NULL;
	
	if(src->type==BL_PC)
		sd=(struct map_session_data *)src;

	switch(skillid)
	{
	/* ����U���n�X�L�� */
	case SM_BASH:			/* �o�b�V�� */
	case MC_MAMMONITE:		/* ���}�[�i�C�g */
	case AC_DOUBLE:			/* �_�u���X�g���C�t�B���O */
	case AS_SONICBLOW:		/* �\�j�b�N�u���[ */
	case AS_GRIMTOOTH:		/* �O�����g�D�[�X */
	case KN_PIERCE:			/* �s�A�[�X */
	case KN_SPEARBOOMERANG:	/* �X�s�A�u�[������ */
	case TF_POISON:			/* �C���x�i�� */
	case TF_SPRINKLESAND:	/* ���܂� */
	case AC_CHARGEARROW:	/* �`���[�W�A���[ */
	case KN_SPEARSTAB:		/* �X�s�A�X�^�u */
	case RG_INTIMIDATE:		/* �C���e�B�~�f�C�g */
	case BA_MUSICALSTRIKE:	/* �~���[�W�J���X�g���C�N */
	case DC_THROWARROW:		/* ��� */
	case BA_DISSONANCE:		/* �s���a�� */
	case MO_INVESTIGATE:	/* ���� */
	case MO_FINGEROFFENSIVE:	/* �w�e */
	case MO_EXTREMITYFIST:	/* ���C���e�P�� */
	case MO_CHAINCOMBO:		/* �A�ŏ� */
	case MO_COMBOFINISH:	/* �җ��� */
	case CR_HOLYCROSS:		/* �z�[���[�N���X */
	/* �ȉ�MOB��p */
	/* �P�̍U���ASP�����U���A�������U���A�h�䖳���U���A���i�U�� */
	case NPC_PIERCINGATT:
	case NPC_MENTALBREAKER:
	case NPC_RANGEATTACK:
	case NPC_CRITICALSLASH:
	case NPC_COMBOATTACK:
	/* �K���U���A�ōU���A�Í��U���A���ٍU���A�X�^���U�� */
	case NPC_GUIDEDATTACK:
	case NPC_POISON:
	case NPC_BLINDATTACK:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	/* �Ή��U���A�􂢍U���A�����U���A�����_��ATK�U�� */
	case NPC_PETRIFYATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
	case NPC_RANDOMATTACK:
	/* �������U���A�n�����U���A�Α����U���A�������U�� */
	case NPC_WATERATTACK:
	case NPC_GROUNDATTACK:
	case NPC_FIREATTACK:
	case NPC_WINDATTACK:
	/* �ő����U���A�������U���A�ő����U���A�O�����U���ASP�����U�� */
	case NPC_POISONATTACK:
	case NPC_HOLYATTACK:
	case NPC_DARKNESSATTACK:
	case NPC_TELEKINESISATTACK:
	case NPC_LICK:
		skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;

	/* ����n�͈͍U���X�L�� */
	case AC_SHOWER:			/* �A���[�V�����[ */
	case SM_MAGNUM:			/* �}�O�i���u���C�N */
	case KN_BOWLINGBASH:	/* �{�E�����O�o�b�V�� */
	case MC_CARTREVOLUTION:	/* �J�[�g�����H�����[�V���� */
	case NPC_SPLASHATTACK:	/* �X�v���b�V���A�^�b�N */
		if(flag&3){
			/* �ʂɃ_���[�W��^���� */
			if(bl->id!=skill_area_temp[1]){
				int dist=0;
				if(skillid==SM_MAGNUM){	/* �}�O�i���u���C�N�Ȃ璆�S����̋������v�Z */
					int dx=abs( bl->x - skill_area_temp[2] );
					int dy=abs( bl->y - skill_area_temp[3] );
					dist=((dx>dy)?dx:dy);
				}
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,
					0x0500|dist  );
			}
		}else{
			int ar=1;
			int x=bl->x,y=bl->y;
			if( skillid==SM_MAGNUM ){
				x=src->x;
				y=src->y;
			}else if(skillid==NPC_SPLASHATTACK)	/* �X�v���b�V���A�^�b�N�͔͈�7*7 */
				ar=3;
			else if(skillid==KN_BOWLINGBASH){/*�{�E�����O�o�b�V�������������Ă݂�i������΂��͂����ł��j */
				int i;	/* ���l���畷���������Ȃ̂ŊԈ���Ă�\���偕������������������ */
				for(i=0;i<4;i++){
					skill_blown(src,bl,1|0x20000);
					skill_area_temp[0]=0;
					map_foreachinarea(skill_area_sub,
						bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,0,
						src,skillid,skilllv,tick, flag|BCT_ENEMY ,
						skill_area_sub_count);
					if(skill_area_temp[0]>1)break;
				}
			/*	if(i==4)break; */
				x=bl->x;y=bl->y;
			}
			skill_area_temp[1]=bl->id;
			skill_area_temp[2]=x;
			skill_area_temp[3]=y;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,x-ar,y-ar,x+ar,y+ar,0,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	/* ���@�n�X�L�� */
	case MG_SOULSTRIKE:			/* �\�E���X�g���C�N */
	case MG_COLDBOLT:			/* �R�[���h�{���g */
	case MG_FIREBOLT:			/* �t�@�C�A�[�{���g */
	case MG_LIGHTNINGBOLT:		/* ���C�g�j���O�{���g */
	case WZ_EARTHSPIKE:			/* �A�[�X�X�p�C�N */
	case AL_HEAL:				/* �q�[�� */
	case AL_HOLYLIGHT:			/* �z�[���[���C�g */
	case ALL_RESURRECTION:		/* ���U���N�V���� */
	case PR_TURNUNDEAD:			/* �^�[���A���f�b�h */
	case MG_FROSTDIVER:			/* �t���X�g�_�C�o�[ */
	case WZ_JUPITEL:			/* ���s�e���T���_�[ */
	case NPC_MAGICALATTACK:		/* MOB:���@�Ō��U�� */
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	case WZ_WATERBALL:			/* �E�H�[�^�[�{�[�� */
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(skilllv>1)
			skill_status_change_start(src,SC_WATERBALL,skilllv,bl->id);
		break;

	case PR_BENEDICTIO:			/* ���̍~�� */
		if(battle_get_race(bl)==1 || battle_get_race(bl)==6)
			skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	/* ���@�n�͈͍U���X�L�� */
	case MG_NAPALMBEAT:			/* �i�p�[���r�[�g */
	case MG_FIREBALL:			/* �t�@�C���[�{�[�� */
	case MG_THUNDERSTORM:		/* �T���_�[�X�g�[��(flag=2�̂�) */
	case WZ_HEAVENDRIVE:		/* �w�u���Y�h���C�u(flag=2�̂�) */
		if(flag&3){
			/* �ʂɃ_���[�W��^���� */
			if(bl->id!=skill_area_temp[1]){
				if(skillid==MG_FIREBALL){	/* �t�@�C���[�{�[���Ȃ璆�S����̋������v�Z */
					int dx=abs( bl->x - skill_area_temp[2] );
					int dy=abs( bl->y - skill_area_temp[3] );
					skill_area_temp[0]=((dx>dy)?dx:dy);
				}
				skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,
					skill_area_temp[0]| ((flag&2)?0:0x0500)  );
			}
		}else{
			int ar=(skillid==MG_NAPALMBEAT)?1:2;
			skill_area_temp[1]=bl->id;
			if(skillid==MG_NAPALMBEAT){	/* �i�p�[���ł͐�ɐ����� */
				skill_area_temp[0]=0;
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,0,
					src,skillid,skilllv,tick, flag|BCT_ENEMY ,
					skill_area_sub_count);
			}else{
				skill_area_temp[2]=bl->x;
				skill_area_temp[3]=bl->y;
			}
			/* �܂��^�[�Q�b�g�ɍU���������� */
			skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,
					skill_area_temp[0] );
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,0,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			break;
		}
		break;

	case WZ_FROSTNOVA:			/* �t���X�g�m���@ */
		/* �ʂɃ_���[�W��^���� */
		if(bl->id!=skill_area_temp[1] &&
			(bl->x!=skill_area_temp[2] || bl->y!=skill_area_temp[3]) )
			skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0 );
		break;


	/* ���̑� */
	case HT_BLITZBEAT:			/* �u���b�c�r�[�g */
		if(flag&1){
			/* �ʂɃ_���[�W��^���� */
			if(bl->id!=skill_area_temp[1])
				skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag&0xf00000 );
		}else{
			skill_area_temp[1]=bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag&0xf00000 );
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,0,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			break;
		}
		break;

	case TF_THROWSTONE:			/* �Γ��� */
	case NPC_SMOKING:			/* �X���[�L���O */
		skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0 );
		break;

	case NPC_SELFDESTRUCTION:	/* ���� */
		if(flag&1){
			/* �ʂɃ_���[�W��^���� */
			if(src->type==BL_MOB){
				struct mob_data *md=(struct mob_data *)src;
				md->hp=skill_area_temp[0];
				if(bl->id!=skill_area_temp[1])
					skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag );
				md->hp=1;
			}
		}else{
			skill_area_temp[0]=battle_get_hp(src);
			skill_area_temp[1]=bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag );
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-5,bl->y-5,bl->x+5,bl->y+5,0,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_damage_id);
			battle_damage(src,src,1);
			break;
		}
		break;

	/* HP�z��/HP�z�����@ */
	case NPC_BLOODDRAIN:
	case NPC_ENERGYDRAIN:
		battle_heal(NULL,src,
			skill_attack( (skillid==NPC_BLOODDRAIN)?BF_WEAPON:BF_MAGIC,
				src,src,bl,skillid,skilllv,tick,flag), 0 );
		break;
	}

	return 0;
}



/*==========================================
 * �X�L���g�p�i�r�������AID�w��x���n�j
 *------------------------------------------
 */
int skill_castend_nodamage_id( struct block_list *src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd=NULL;
	struct map_session_data *dstsd=NULL;
	struct mob_data *md=NULL;
	int i;

	if(src->type==BL_PC)
		sd=(struct map_session_data *)src;
	else if(src->type==BL_MOB)
		md=(struct mob_data *)src;

	if(bl->type==BL_PC)
		dstsd=(struct map_session_data *)bl; 

	switch(skillid)
	{
#if 0
	case SM_RECOVERY:			/* SP�񕜌��� */
		{
        int a=0,i,bonus,c=0;
		bonus=100+(skilllv*10);
        if(skilllv==1){a=500 > 550;}
        else if(skilllv==2){a=500 > 551;}
        else if(skilllv==3){a=500 > 551;}
        else if(skilllv==4){a=500 > 551;}
		else if(skilllv==5){a=500 > 551;}
		else if(skilllv==6){a=500 > 551;}
		else if(skilllv==7){a=500 > 551;}
		else if(skilllv==8){a=500 > 551;}
		else if(skilllv==9){a=500 > 551;}
        else if(skilllv==10){a=500 > 551;}
        if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_delitem(sd,i,1,0);
                 c=1;
                 if(skilllv==1){a=rand()%15+30;}
                 else if(skilllv==2){a=rand()%20+70;}
                 else if(skilllv==3){a=rand()%60+175;}
                 else if(skilllv==4){a=rand()%80+350;}
                 else if(skilllv==5){a=rand()%80+350;}
				 else if(skilllv==6){a=rand()%80+350;}
				 else if(skilllv==7){a=rand()%80+350;}
				 else if(skilllv==8){a=rand()%80+350;}
				 else if(skilllv==9){a=rand()%80+350;}
				 else if(skilllv==10){a=rand()%80+350;}
                 if(a>1){
                    clif_skill_nodamage(src,bl,skillid,(bonus*a)/100,1);
                    battle_heal(NULL,bl,(bonus*a)/100,0);
                 }
          }
       }
       if(c==0){clif_displaymessage(sd->fd,"Potions.");}
#endif

	case AL_HEAL:				/* �q�[�� */
		{
			int heal=skill_calc_heal( src, skilllv );
			if( bl->type==BL_PC &&
				pc_check_equip_dcard((struct map_session_data *)bl,4128) )
				heal=0;	/* ����峃J�[�h�i�q�[���ʂO�j */
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0);
		}
		break;

	case ALL_RESURRECTION:		/* ���U���N�V���� */
		if(bl->type==BL_PC){
			int per=0;
			struct map_session_data *tsd=(struct map_session_data*)bl;

			if( (map[bl->m].flag&MF_PVP) && tsd->pvp_point<=0 )
				break;			/* PVP�ŕ����s�\��� */

			if(pc_isdead(tsd)){	/* ���S���� */
				clif_skill_nodamage(src,bl,skillid,0,1);
				switch(skilllv){
				case 2: per=15; break;
				case 3: per=30; break;
				case 4: per=50; break;
				}
				tsd->status.hp=tsd->status.max_hp*per/100;
				if(tsd->status.hp<=0) tsd->status.hp=1;
				if( pc_check_equip_dcard(tsd,4144) ){	/* �I�V���X�J�[�h */
					tsd->status.hp=tsd->status.max_hp;
					tsd->status.sp=tsd->status.max_sp;
				}
				pc_setstand(tsd);
				if(battle_config.ghost_time > 0)
					pc_setghosttimer(tsd,battle_config.ghost_time);
				clif_updatestatus(tsd,SP_HP);
				clif_resurrection(&tsd->bl,1);
			}
		}
		break;

	case AL_INCAGI:			/* ���x���� */
	case AL_DECAGI:			/* ���x���� */
	case AL_BLESSING:		/* �u���b�V���O */
	case KN_TWOHANDQUICKEN:	/* �c�[�n���h�N�C�b�P�� */
	case CR_SPEARQUICKEN:	/* �X�s�A�N�C�b�P�� */
	case PR_IMPOSITIO:		/* �C���|�V�e�B�I�}�k�X */
	case PR_ASPERSIO:		/* �A�X�y���V�I */
	case PR_KYRIE:			/* �L���G�G���C�\�� */
	case PR_LEXDIVINA:		/* ���b�N�X�f�B�r�[�i */
	case PR_LEXAETERNA:		/* ���b�N�X�G�[�e���i */
	case AS_ENCHANTPOISON:	/* �G���`�����g�|�C�Y�� */
	case AS_POISONREACT:	/* �|�C�Y�����A�N�g */
	case AC_CONCENTRATION:	/* �W���͌��� */
	case MC_LOUD:			/* ���E�h�{�C�X */
	case MG_ENERGYCOAT:		/* �G�i�W�[�R�[�g */
	case SM_PROVOKE:		/* �v���{�b�N */
	case SM_ENDURE:			/* �C���f���A */
	case PR_SUFFRAGIUM:		/* �T�t���M�E�� */
	case MG_SIGHT:			/* �T�C�g */
	case AL_RUWACH:			/* ���A�t */
	case PR_BENEDICTIO:		/* ���̍~�� */
	case CR_PROVIDENCE:		/* �v�����B�f���X */
	case SA_FLAMELAUNCHER:	/* �t���C�������`���[ */
	case SA_FROSTWEAPON:	/* �t���X�g�E�F�|�� */
	case SA_LIGHTNINGLOADER:/* ���C�g�j���O���[�_�[ */
	case SA_SEISMICWEAPON:	/* �T�C�Y�~�b�N�E�F�|�� */
	case MO_EXPLOSIONSPIRITS:	// �����g��
	case MO_STEELBODY:		// ����
#if 0
	case CR_AUTOGUARD:		/* �I�[�g�K�[�h */
	case CR_DEFENDER:		/* �f�B�t�F���_�[ */
	case SA_CASTCANCEL:		/* �L���X�g�L�����Z�� */
	case SA_FREECAST:		/* �t���[�L���X�g */
	case SA_VOLCANO:		/* �{���P�[�m */
	case SA_DELUGE:			/* �f�����[�W */
	case SA_VIOLENTGALE:	/* �o�C�I�����g�Q�C�� */
	case SA_LANDPROTECTOR:	/* �����h�v���e�N�^�[ */
	case BA_FROSTJOKE:		/* �����W���[�N */
#endif
		clif_skill_nodamage( (skillid==PR_KYRIE)?bl:src,bl,skillid,0,1);
		skill_status_change_start( bl,
			SkillStatusChangeTable[skillid], skilllv, 0 );
		if(skillid==SM_PROVOKE && bl->type==BL_MOB)
			mob_target((struct mob_data *)bl,src,skill_get_range(skillid));
		break;
	case MO_CALLSPIRITS:	// �C��
		clif_skill_nodamage(src,bl,skillid,0,1);
		pc_addspiritball(sd,60*10*1000,skilllv);
		break;
	case MO_ABSORBSPIRITS:	// �C�D
		if(sd && dstsd) {
			if(sd == dstsd || map[sd->bl.m].flag&MF_PVP) {
				if(dstsd->spiritball > 0) {
					clif_skill_nodamage(src,bl,skillid,0,1);
					i = dstsd->spiritball * 7;
					pc_delspiritball(dstsd,dstsd->spiritball,0);
					if(i > 0x7FFF)
						i = 0x7FFF;
					if(sd->status.sp + i > sd->status.max_sp) {
						i = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					}
					else
						sd->status.sp += i;
					clif_heal(sd->fd,SP_SP,i);
				}
				else
					clif_skill_nodamage(src,bl,skillid,0,0);
			}
			else
				clif_skill_nodamage(src,bl,skillid,0,0);
		}
		break;

	case BS_HAMMERFALL:		/* �n���}�[�t�H�[�� */
		clif_skill_nodamage(src,bl,skillid,0,1);
		if( rand()%100 < (20+ 10*skilllv) ) {
			skill_status_change_start(bl,SC_STAN,skilllv,10000);
		}
		break;

	/* �p�[�e�B�X�L�� */
	case AL_ANGELUS:		/* �G���W�F���X */
	case PR_MAGNIFICAT:		/* �}�O�j�t�B�J�[�g */
	case PR_GLORIA:			/* �O�����A */
	case BS_ADRENALINE:		/* �A�h���i�������b�V�� */
	case BS_WEAPONPERFECT:	/* �E�F�|���p�[�t�F�N�V���� */
	case BS_OVERTHRUST:		/* �I�[�o�[�g���X�g */
		if( sd==NULL || sd->status.party_id==0 || (flag&1) ){
			/* �ʂ̏��� */
			clif_skill_nodamage(bl,bl,skillid,0,1);
			skill_status_change_start( bl,
				SkillStatusChangeTable[skillid], skilllv, 0 );
		}else{
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,1,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;

	/*�i�t���Ɖ������K�v�j */
	case BS_MAXIMIZE:		/* �}�L�V�}�C�Y�p���[ */
	case NV_TRICKDEAD:		/* ���񂾂ӂ� */
	case TF_HIDING:			/* �n�C�f�B���O */
	case AS_CLOAKING:		/* �N���[�L���O */
		clif_skill_nodamage(src,bl,skillid,0,1);
		{
			int sc=SkillStatusChangeTable[skillid];
			if( (battle_get_sc_data(bl))[sc].timer==-1 )
				/* �t������ */
				skill_status_change_start(bl, sc, skilllv, 0);
			else
				/* �������� */
				skill_status_change_end(bl, sc, -1);

			if(skillid==AS_CLOAKING)
				skill_check_cloaking(bl);
		}
		break;

	/* �Βn�X�L�� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
	case BA_WHISTLE:			/* ���J */
	case BA_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
#if 0
	case BD_LULLABY:			/* �q��S */
	case BD_RICHMANKIM:			/* �j�����h�̉� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:			/* ���L�̋��� */
	case BD_INTOABYSS:			/* �[���̒��� */
	case BD_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
	case BA_DISSONANCE:			/* �s���a�� */
	case BA_WHISTLE:			/* ���J */
	case BA_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
	case BA_POEMBRAGI:			/* �u���M�̎� */
	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
	case DC_UGLYDANCE:			/* ��������ȃ_���X */
	case DC_HUMMING:			/* �n�~���O */
	case DC_DONTFORGETME:		/* ����Y��Ȃ��Łc */
	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
#endif
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;

	case TF_STEAL:			// �X�e�B�[��
		if(pc_steal_item(sd,bl)) {
			clif_skill_nodamage(src,bl,skillid,0,1);
			mob_target((struct mob_data *)bl,src,skill_get_range(skillid));
		}
		else
			clif_skill_nodamage(src,bl,skillid,0,0);
		break;

	case RG_STEALCOIN:		// �X�e�B�[���R�C��
		if(pc_steal_coin(sd,bl)) {
			clif_skill_nodamage(src,bl,skillid,0,1);
			mob_target((struct mob_data *)bl,src,skill_get_range(skillid));
		}
		else
			clif_skill_nodamage(src,bl,skillid,0,0);
		break;

	case MG_STONECURSE:			/* �X�g�[���J�[�X */
		clif_skill_nodamage(src,bl,skillid,0,1);
		if( rand()%100 < skilllv*4+20 )
			skill_status_change_start(bl,SC_STONE,skilllv,0);
		break;

	case NV_FIRSTAID:			/* ���}�蓖 */
		clif_skill_nodamage(src,bl,skillid,5,1);
		battle_heal(NULL,bl,5,0);
		break;

	case AL_CURE:				/* �L���A�[ */
		clif_skill_nodamage(src,bl,skillid,0,1);
		skill_status_change_end(bl, SC_SILENCE	, -1 );
		skill_status_change_end(bl, SC_BLIND	, -1 );
		skill_status_change_end(bl, SC_CONFUSION, -1 );
		break;

	case TF_DETOXIFY:			/* ��� */
		clif_skill_nodamage(src,bl,skillid,0,1);
		skill_status_change_end(bl, SC_POISON	, -1 );
		break;

	case PR_STRECOVERY:			/* ���J�o���[ */
		clif_skill_nodamage(src,bl,skillid,0,1);
		skill_status_change_end(bl, SC_FREEZE	, -1 );
		skill_status_change_end(bl, SC_STONE	, -1 );
		skill_status_change_end(bl, SC_SLEEP	, -1 );
		skill_status_change_end(bl, SC_STAN		, -1 );
		break;

	case WZ_ESTIMATION:			/* �����X�^�[��� */
		if(src->type==BL_PC){
			clif_skill_nodamage(src,bl,skillid,0,1);
			clif_skill_estimation((struct map_session_data *)src,bl);
		}
		break;

	case MC_IDENTIFY:			/* �A�C�e���Ӓ� */
		if(sd!=NULL)
			clif_item_identify_list(sd);
		break;

	case MC_VENDING:			/* �I�X�J�� */
		if(sd!=NULL)
			clif_openvendingreq(sd,2+sd->skilllv);
		break;

	case AL_TELEPORT:			/* �e���|�[�g */
		clif_skill_nodamage(src,bl,skillid,0,1);
		if( sd ){
			if(map[sd->bl.m].flag&MF_NOTELEPORT)	/* �e���|�֎~ */
				break;
			if( sd->skilllv==1 )
				pc_randomwarp(sd,3);
			else{
				clif_skill_warppoint(sd,sd->skillid,"Random",
					sd->status.save_point.map,"","");
			}
		}else if( bl->type==BL_MOB )
			mob_warp((struct mob_data *)bl,-1,-1,3);
		break;

	case WZ_FROSTNOVA:			/* �t���X�g�m���@ */
		skill_area_temp[1]=bl->id;
		skill_area_temp[2]=bl->x;
		skill_area_temp[3]=bl->y;
		/* �܂��^�[�Q�b�g�ɃG�t�F�N�g���o�� */
/*		clif_skill_nodamage(src,bl,skillid,0,1);
		clif_skill_damage(src,bl,tick,battle_get_amotion(src),0,-1,1,skillid,skilllv,6);
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick, ); */
		/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
		map_foreachinarea(skill_area_sub,
			bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,0,
			src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
			skill_castend_damage_id);
		break;

	case RG_STRIPWEAPON:		/* �X�g���b�v�E�F�|�� */
		/*{
		int i,a=0,b=0;
		if(skilllv==1){a=1100 > 2000;}
        else if(skilllv==2){a=1100 > 2000;}
        else if(skilllv==3){a=1100 > 2000;}
        else if(skilllv==4){a=1100 > 2000;}
        else if(skilllv==5){a=1100 > 2000;}
		if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_unequipitem(sd,i);
                 b=1;
                 if(skilllv==1){a=rand()%7;}
                 else if(skilllv==2){a=rand()%9;}
                 else if(skilllv==3){a=rand()%11;}
                 else if(skilllv==4){a=rand()%13;}
                 else if(skilllv==5){a=rand()%15;}
		}
       if(b==0){clif_displaymessage(sd->fd,"Nothing Equiped.");}*/
		break;

	case RG_STRIPSHIELD:		/* �X�g���b�v�V�[���h */
		/*{
		int i,a=0,b=0;
		if(skilllv==1){a=2100 > 2200;}
        else if(skilllv==2){a=2100 > 2200;}
        else if(skilllv==3){a=2100 > 2200;}
        else if(skilllv==4){a=2100 > 2200;}
        else if(skilllv==5){a=2100 > 2200;}
		if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_unequipitem(sd,i);
                 b=1;
                 if(skilllv==1){a=rand()%7;}
                 else if(skilllv==2){a=rand()%9;}
                 else if(skilllv==3){a=rand()%11;}
                 else if(skilllv==4){a=rand()%13;}
                 else if(skilllv==5){a=rand()%15;}
		}
       if(b==0){clif_displaymessage(sd->fd,"Nothing Equiped.");}*/
		break;
	case RG_STRIPARMOR:			/* �X�g���b�v�A�[�}�[ */
		/*{
		int i,a=0,b=0;
		if(skilllv==1){a=2300 > 2400;}
        else if(skilllv==2){a=2300 > 2400;}
        else if(skilllv==3){a=2300 > 2400;}
        else if(skilllv==4){a=2300 > 2400;}
        else if(skilllv==5){a=2300 > 2400;}
		if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_unequipitem(sd,i);
                 b=1;
                 if(skilllv==1){a=rand()%7;}
                 else if(skilllv==2){a=rand()%9;}
                 else if(skilllv==3){a=rand()%11;}
                 else if(skilllv==4){a=rand()%13;}
                 else if(skilllv==5){a=rand()%15;}
		}
       if(b==0){clif_displaymessage(sd->fd,"Nothing Equiped.");}*/
		break;
	case RG_STRIPHELM:			/* �X�g���b�v�w���� */
		/*{
		int i,a=0,b=0;
		if(skilllv==1){a=2200 > 2300;}
        else if(skilllv==2){a=2200 > 2300;}
        else if(skilllv==3){a=2200 > 2300;}
        else if(skilllv==4){a=2200 > 2300;}
        else if(skilllv==5){a=2200 > 2300;}
		if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_unequipitem(sd,i);
                 b=1;
                 if(skilllv==1){a=rand()%7;}
                 else if(skilllv==2){a=rand()%9;}
                 else if(skilllv==3){a=rand()%11;}
                 else if(skilllv==4){a=rand()%13;}
                 else if(skilllv==5){a=rand()%15;}
		}
       if(b==0){clif_displaymessage(sd->fd,"Nothing Equiped.");}*/
		break;
	case RG_INTIMIDATE:			/* �C���e�B�~�f�C�g */
		if( sd ){
			if(map[sd->bl.m].flag&MF_NOTELEPORT)	/* �e���|�֎~ */
				break;
			if( sd->skilllv==1 )
				pc_randomwarp(sd,3);
			else{
				clif_skill_warppoint(sd,sd->skillid,"Random",
					sd->status.save_point.map,"","");
			}
		}else if( bl->type==BL_MOB )
			mob_warp((struct mob_data *)bl,-1,-1,3);
		break;
	/* PotionPitcher added by Tato [17/08/03] */
	case AM_POTIONPITCHER:		/* �|�[�V�����s�b�`���[ */
		{
        int a=0,i,bonus,c=0;
        bonus=100+(skilllv*10);
        if(skilllv==1){a=501;}
        else if(skilllv==2){a=500 > 503;}
        else if(skilllv==3){a=500 > 504;}
        else if(skilllv==4){a=500 > 506;}
        else if(skilllv==5){a=500 > 507;}
        if(a>0){
           for(i=0;i<MAX_INVENTORY;i++){
          if(sd->status.inventory[i].nameid==a){
                 pc_delitem(sd,i,1,0);
                 c=1;
                 if(a==501){a=rand()%15+30;}
                 else if(a==502){a=rand()%20+70;}
                 else if(a==503){a=rand()%60+175;}
                 else if(a==504){a=rand()%80+350;}
                 else if(a==506){a=1;}
                 if(a>1){
                    clif_skill_nodamage(src,bl,skillid,(bonus*a)/100,1);
                    battle_heal(NULL,bl,(bonus*a)/100,0);
                 }else{
                    skill_status_change_end(bl, SC_POISON , -1 );
                    skill_status_change_end(bl, SC_SILENCE , -1 );
                    skill_status_change_end(bl, SC_BLIND , -1 );
                    skill_status_change_end(bl, SC_CONFUSION , -1 );
                 }
          }
       }
       if(c==0){clif_displaymessage(sd->fd,"Not enough Potions.");}
        }
	}
		break;
	case AM_CP_WEAPON:
		break;
	case AM_CP_SHIELD:
		break;
	case AM_CP_ARMOR:
		break;
	case AM_CP_HELM:
		break;
	case SA_DISPELL:			/* �f�B�X�y�� */
		clif_skill_nodamage(src,bl,skillid,0,1);
		skill_status_change_end(bl, SC_SILENCE	, -1 );
		skill_status_change_end(bl, SC_BLIND	, -1 );
		skill_status_change_end(bl, SC_CONFUSION, -1 );
		skill_status_change_end(bl, SC_FREEZE	, -1 );
		skill_status_change_end(bl, SC_STONE	, -1 );
		skill_status_change_end(bl, SC_SLEEP	, -1 );
		skill_status_change_end(bl, SC_STAN		, -1 );
		skill_status_change_end(bl, SC_POISON	, -1 );
		break;

	case TF_BACKSLIDING:		/* �o�b�N�X�e�b�v */
		if(sd)
			pc_stop_walking(sd);
		skill_blown(src,bl,5|0x10000);
		clif_skill_nodamage(src,bl,skillid,0,1);
		clif_fixpos(src);
		break;

	/* �����_�������ω��A�������ω��A�n�A�΁A�� */
	case NPC_ATTRICHANGE:
	case NPC_CHANGEWATER:
	case NPC_CHANGEGROUND:
	case NPC_CHANGEFIRE:
	case NPC_CHANGEWIND:
	/* �ŁA���A�O�A�� */
	case NPC_CHANGEPOISON:
	case NPC_CHANGEHOLY:
	case NPC_CHANGEDARKNESS:
	case NPC_CHANGETELEKINESIS:
		if(md){
			clif_skill_nodamage(src,bl,skillid,0,1);
			md->def_ele=skill_get_pl(skillid);
			if(md->def_ele==0)			/* �����_���ω��A�������A*/
				md->def_ele=rand()%9;	/* �s�������͏��� */
			md->def_ele+=(1+rand()%4)*20;	/* �������x���̓����_�� */
		}
		break;

	case NPC_SUICIDE:			/* ���� */
		if(md){
			clif_skill_nodamage(src,bl,skillid,0,1);
			mob_damage(NULL,md,md->hp);
		}
		break;

	case NPC_SUMMONSLAVE:		/* �艺���� */
	case NPC_SUMMONMONSTER:		/* MOB���� */
		if(md)
			mob_summonslave(md,mob_db[md->class].skill[md->skillidx].val1,
				skilllv,(skillid==NPC_SUMMONSLAVE)?1:0);
		break;

	case NPC_EMOTION:			/* �G���[�V���� */
		clif_emotion(&md->bl,mob_db[md->class].skill[md->skillidx].val1);
		break;
	}
	return 0;
}


/*==========================================
 * �X�L���g�p�i�r�������AID�w��j
 *------------------------------------------
 */
int skill_castend_id( int tid, unsigned int tick, int id,int data )
{
	struct map_session_data* sd=NULL/*,*target_sd=NULL*/;
	struct block_list *bl;
	
	if( (sd=map_id2sd(id))==NULL )
		return 0;
	
	if( sd->skilltimer != tid )	/* �^�C�}ID�̊m�F */
		return 0;
	sd->skilltimer=-1;
	
	bl=map_id2bl(sd->skilltarget);
	if(bl==NULL || bl->prev==NULL)
		return 0;
	if(sd->bl.m != bl->m || pc_isdead(sd))
		return 0;
	
	if(!skill_check_condition( sd ))		/* �g�p�����`�F�b�N */
		return 0;
		
	printf("skill castend skill=%d\n",sd->skillid);

	if( (skill_get_inf(sd->skillid)&1) &&	// �މ�G�Ί֌W�`�F�b�N
		battle_check_target(&sd->bl,bl, BCT_ENEMY)<=0 )
		return 0;

	switch( skill_get_nk(sd->skillid) )
	{
	/* �U���n/������΂��n */
	case 0:	case 2:
		skill_castend_damage_id(&sd->bl,bl,sd->skillid,sd->skilllv,tick,0);
		break;
	case 1:/* �x���n */
		if( (sd->skillid==AL_HEAL || sd->skillid==ALL_RESURRECTION)&& battle_get_elem_type(bl)==9 )
			skill_castend_damage_id(&sd->bl,bl,sd->skillid,sd->skilllv,tick,0);
		else
			skill_castend_nodamage_id(&sd->bl,bl,sd->skillid,sd->skilllv,tick,0);
		break;
	}
	

	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������A�ꏊ�w��̎��ۂ̏����j
 *------------------------------------------
 */
int skill_castend_pos2( struct block_list *src, int x,int y,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct map_session_data *sd=NULL;
	int i,tmpx,tmpy;
	
	if(src->type==BL_PC)
		sd=(struct map_session_data *)src;
	if(skillid != WZ_METEOR)
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);

	switch(skillid)
	{
	case MG_THUNDERSTORM:		/* �T���_�[�X�g�[�� */
	case WZ_HEAVENDRIVE:		/* �w�����Y�h���C�u */
		skill_area_temp[1]=src->id;
		skill_area_temp[2]=x;
		skill_area_temp[3]=y;
		map_foreachinarea(skill_area_sub,
			src->m,x-2,y-2,x+2,y+2,0,
			src,skillid,skilllv,tick, flag|BCT_ENEMY|2,
			skill_castend_damage_id);
		break;

	case PR_BENEDICTIO:			/* ���̍~�� */
		skill_area_temp[1]=src->id;
		map_foreachinarea(skill_area_sub,
			src->m,x-1,y-1,x+1,y+1,0,
			src,skillid,skilllv,tick, flag|BCT_NOENEMY|1,
			skill_castend_nodamage_id);
		map_foreachinarea(skill_area_sub,
			src->m,x-1,y-1,x+1,y+1,0,
			src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
			skill_castend_damage_id);
		break;

	case BS_HAMMERFALL:			/* �n���}�[�t�H�[�� */
		skill_area_temp[1]=src->id;
		skill_area_temp[2]=x;
		skill_area_temp[3]=y;
		map_foreachinarea(skill_area_sub,
			src->m,x-2,y-2,x+2,y+2,0,
			src,skillid,skilllv,tick, flag|BCT_ENEMY|2,
			skill_castend_nodamage_id);
		break;

	case MG_SAFETYWALL:			/* �Z�C�t�e�B�E�H�[�� */
	case MG_FIREWALL:			/* �t�@�C���[�E�H�[�� */
	case AL_PNEUMA:				/* �j���[�} */
	case WZ_ICEWALL:			/* �A�C�X�E�H�[�� */
	case WZ_FIREPILLAR:			/* �t�@�C�A�s���[ */
	case WZ_QUAGMIRE:			/* �N�@�O�}�C�A */
	case WZ_VERMILION:			/* ���[�h�I�u���@�[�~���I�� */
	case WZ_STORMGUST:			/* �X�g�[���K�X�g */
	case PR_SANCTUARY:			/* �T���N�`���A�� */
	case PR_MAGNUS:				/* �}�O�k�X�G�N�\�V�Y�� */
	case HT_SKIDTRAP:			/* �X�L�b�h�g���b�v */
	case HT_LANDMINE:			/* �����h�}�C�� */
	case HT_ANKLESNARE:			/* �A���N���X�l�A */
	case HT_SHOCKWAVE:			/* �V���b�N�E�F�[�u�g���b�v */
	case HT_SANDMAN:			/* �T���h�}�� */
	case HT_FLASHER:			/* �t���b�V���[ */
	case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
	case HT_BLASTMINE:			/* �u���X�g�}�C�� */
	case HT_CLAYMORETRAP:		/* �N���C���A�[�g���b�v */
	case AS_VENOMDUST:			/* �x�m���_�X�g */
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case WZ_METEOR:				//���e�I�X�g�[��
		for(i=1;i<=2+(skilllv>>1);i++) {
			tmpx=x + (rand()%7 - 3);
			tmpy=y + (rand()%7 - 3);
			clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
			skill_unitsetting(src,skillid,skilllv,tmpx,tmpy,0);
		}
		break;


	case AL_WARP:				/* ���[�v�|�[�^�� */
		if(map[sd->bl.m].flag&MF_NOTELEPORT)	/* �e���|�֎~ */
			break;
		clif_skill_warppoint(sd,sd->skillid,sd->status.save_point.map,
			(sd->skilllv>1)?sd->status.memo_point[0].map:"",
			(sd->skilllv>2)?sd->status.memo_point[1].map:"",
			(sd->skilllv>3)?sd->status.memo_point[2].map:"");
		break;
	case MO_BODYRELOCATION:
		pc_movepos(sd,x,y);
		break;
	}
	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������Amap�w��j
 *------------------------------------------
 */
int skill_castend_map( struct map_session_data *sd,int skill_num, const char *map)
{
	int x=0,y=0;
	
	if( sd==NULL || pc_isdead(sd))
		return 0;

	if( sd->opt1>0 || sd->status.option&6 || sd->sc_data[SC_DIVINA].timer!=-1 )
		return 0;	/* �ُ�Ⓘ�قȂ� */
	
	if( skill_num != sd->skillid)	/* �s���p�P�b�g�炵�� */
		return 0;

	pc_stopattack(sd);

	printf("skill castend skill =%d map=%s\n",skill_num,map);

	if(strcmp(map,"cancel")==0)
		return 0;

	switch(skill_num){
	case AL_TELEPORT:		/* �e���|�[�g */
		if(strcmp(map,"Random")==0)
			pc_randomwarp(sd,3);
		else
			pc_setpos(sd,sd->status.save_point.map,
				sd->status.save_point.x,sd->status.save_point.y,3);
		break;

	case AL_WARP:			/* ���[�v�|�[�^�� */
		{
			const struct point *p[]={
				&sd->status.save_point,&sd->status.memo_point[0],
				&sd->status.memo_point[1],&sd->status.memo_point[2],
			};
			struct skill_unit_group *group;
			int i;
			for(i=0;i<sd->skilllv;i++){
				if(strcmp(map,p[i]->map)==0){
					x=p[i]->x;
					y=p[i]->y;
					break;
				}
			}
			if(x==0 || y==0)	/* �s���p�P�b�g�H */
				return 0;

			group=skill_unitsetting(&sd->bl,sd->skillid,sd->skilllv,sd->skillx,sd->skilly,0);
			group->valstr=malloc(16);
			if(group->valstr==NULL){
				printf("skill_castend_map: out of memory !\n");
				exit(0);
			}
			memcpy(group->valstr,map,16);
			group->val2=(x<<16)|y;
		}
		break;

	case RG_INTIMIDATE:			/* �C���e�B�~�f�C�g */
		if(strcmp(map,"Random")==0)
			pc_randomwarp(sd,3);
		else
			pc_setpos(sd,sd->status.save_point.map,
				sd->status.save_point.x,sd->status.save_point.y,3);
		break;
	}

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�ݒ菈��
 *------------------------------------------
 */
struct skill_unit_group *skill_unitsetting( struct block_list *src, int skillid,int skilllv,int x,int y,int flag)
{
	struct skill_unit_group *group;
	int i,count=1,limit=10000,val1=skilllv,val2=0;
	int target=BCT_ENEMY,interval=1000,range=0;
	int dir=0;

	switch(skillid){	/* �ݒ� */

	case MG_SAFETYWALL:			/* �Z�C�t�e�B�E�H�[�� */
		limit=5000*skilllv;
		val2=skilllv+1;
		target=(battle_config.defnotenemy)?BCT_NOENEMY:BCT_ALL;
		break;

	case MG_FIREWALL:			/* �t�@�C���[�E�H�[�� */
		dir=map_calc_dir(src,x,y);
		if(dir&1) count=5;
		else count=3;
		limit=1000*(val2=(4+skilllv));
		interval=250;
		break;

	case AL_PNEUMA:				/* �j���[�} */
		target=(battle_config.defnotenemy)?BCT_NOENEMY:BCT_ALL;
		range=1;
		break;

	case AL_WARP:				/* ���[�v�|�[�^�� */
		target=BCT_ALL;
		val1=skillid+6;
		if(flag==0)
			limit=2000;
		else
			limit=5000*(1+skilllv);
		break;

	case PR_SANCTUARY:			/* �T���N�`���A�� */
		count=21;
		limit=1000*(3*skilllv+1);
		val1=skilllv+3;
		val2=(skilllv>6)?777:skilllv*100;
		target=BCT_ALL;
		range=1;
		break;

	case PR_MAGNUS:				/* �}�O�k�X�G�N�\�V�Y�� */
		count=33;
		limit=1000*(skilllv+4);
		interval=3000;
		break;

	case WZ_FIREPILLAR:			/* �t�@�C�A�[�s���[ */
		if(flag==0)
			limit=30000;
		else
			limit=1000;
		interval=2000;
		val1=skilllv+2;
		range=1;
		break;
	case WZ_METEOR:				/* ���e�I�X�g�[�� */
		limit=500;
		interval=500;
		range=4;
		count=2*(skilllv);
		break;

	case WZ_VERMILION:			/* ���[�h�I�u���@�[�~���I�� */
		limit=3500;
		interval=1500;
		range=4;
		break;

	case WZ_ICEWALL:			/* �A�C�X�E�H�[�� */
		limit=4000*(1+skilllv);
		count=5;
		break;

	case WZ_STORMGUST:			/* �X�g�[���K�X�g */
		limit=2000+skilllv*300;
		interval=450;
		range=4;
		break;

	case WZ_QUAGMIRE:			/* �N�@�O�}�C�A */
		limit=5000*skilllv;
		interval=200;
		count=25;
		break;

	case HT_SKIDTRAP:			/* �X�L�b�h�g���b�v */
		limit=60000*(6-skilllv);
		range=1;
		break;

	case HT_LANDMINE:			/* �����h�}�C�� */
		limit=40000*(6-skilllv);
		range=1;
		break;

	case HT_ANKLESNARE:			/* �A���N���X�l�A */
		limit=50000*(6-skilllv);
		range=1;
		val1=skilllv*5000;
		interval=val1+5000;
		break;

	case HT_SHOCKWAVE:			/* �V���b�N�E�F�[�u�g���b�v */
		limit=40000*(6-skilllv);
		range=1;
		val1=skilllv*15+10;
		break;

	case HT_SANDMAN:			/* �T���h�}�� */
		limit=30000*(6-skilllv);
		range=1;
		break;

	case HT_FLASHER:			/* �t���b�V���[ */
		limit=30000*(6-skilllv);
		range=1;
		break;

	case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
		limit=30000*(6-skilllv);
		range=1;
		break;

	case HT_BLASTMINE:			/* �u���X�g�}�C�� */
		limit=5000*(6-skilllv);
		interval=3000;
		range=1;
		break;

	case HT_CLAYMORETRAP:		/* �N���C���A�[�g���b�v */
		limit=20000*(skilllv);
		interval=3000;
		range=1;
		break;

	case AS_VENOMDUST:			/* �x�m���_�X�g */
		limit=5000*skilllv;
		interval=1000;
		count=5;
		break;

	case CR_GRANDCROSS:			/* �O�����h�N���X */
		count=33;
		limit=1000*(skilllv+4);
		interval=3000;
		break;

	case SA_VOLCANO:			/* �{���P�[�m */
		range=skilllv+4;
		target=BCT_ALL;
		break;

	case SA_DELUGE:				/* �f�����[�W */
		range=skilllv+4;
		target=BCT_ALL;
		break;

	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
		count=81;
		limit=40000*(6-skilllv);
		val1=skilllv*15+10;
		target=BCT_ALL;
		break;

	case BD_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
		count=81;
		target=BCT_ALL;
		break;

	case BA_DISSONANCE:			/* �s���a�� */
		count=81;
		target=BCT_ENEMY;
		break;

	case BA_WHISTLE:			/* ���J */
		count=81;
		limit=40000*(6-skilllv);
		range=9;
		val1=skilllv*15+10;
		target=BCT_ALL;
		break;

	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
		count=81;
		target=BCT_ALL;
		break;

	case DC_UGLYDANCE:			/* ��������ȃ_���X */
		count=81;
		limit=40000*(6-skilllv);
		range=5;
		val1=skilllv*15+10;
		target=BCT_ALL;
		break;

	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
		count=81;
		limit=40000*(6-skilllv);
		val1=skilllv*15+10;
		target=BCT_ALL;
		break;

	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
		count=81;
		limit=40000*(6-skilllv);
		val1=skilllv*15+10;
		target=BCT_ALL;
		break;
	};

	group=skill_initunitgroup(src,count,skillid,skilllv,
		skill_get_unit_id(skillid,flag&1));
	group->limit=limit;
	group->val1=val1;
	group->val2=val2;
	group->target_flag=target;
	group->interval=interval;
	group->range=range;

	for(i=0;i<count;i++){
		struct skill_unit *unit;
		int ux=x,uy=y,val1=skilllv,val2=0,limit=group->limit,alive=1;
		int range=0;
		switch(skillid){	/* �ݒ� */
		case MG_FIREWALL:		/* �t�@�C���[�E�H�[�� */
		{
				if(dir&1){	/* �΂ߔz�u */
					static const int dx[][5]={
						{ 1,1,0,0,-1 }, { -1,-1,0,0,1 },
					},dy[][5]={
						{ 1,0,0,-1,-1 }, { 1,0,0,-1,-1 },
					};
					ux+=dx[(dir>>1)&1][i];
					uy+=dy[(dir>>1)&1][i];
				}else{	/* �㉺�z�u */
					if(dir%4==0)	/* �㉺ */
						ux+=i-1;
					else			/* ���E */
						uy+=i-1;
				}
				val2=group->val2;
			}
			break;

		case PR_SANCTUARY:		/* �T���N�`���A�� */
			{
				static const int dx[]={
					-1,0,1, -2,-1,0,1,2, -2,-1,0,1,2, -2,-1,0,1,2, -1,0,1 };
				static const int dy[]={
					-2,-2,-2, -1,-1,-1,-1,-1, 0,0,0,0,0, 1,1,1,1,1, 2,2,2, };
				ux+=dx[i];
				uy+=dy[i];
			}
			break;

		case PR_MAGNUS:			/* �}�O�k�X�G�N�\�V�Y�� */
			{
				static const int dx[]={ -1,0,1, -1,0,1, -3,-2,-1,0,1,2,3,
					-3,-2,-1,0,1,2,3, -3,-2,-1,0,1,2,3, -1,0,1, -1,0,1, };
				static const int dy[]={
					-3,-3,-3, -2,-2,-2, -1,-1,-1,-1,-1,-1,-1,
					0,0,0,0,0,0,0, 1,1,1,1,1,1,1, 2,2,2, 3,3,3 };
				ux+=dx[i];
				uy+=dy[i];
			}
			break;

		case WZ_ICEWALL:		/* �A�C�X�E�H�[�� */
			{
				static const int dirx[8]={0,-1,-1,-1,0,1,1,1};
				static const int diry[8]={1,1,0,-1,-1,-1,0,1};
				dir=map_calc_dir(src,x,y);
				ux+=(2-i)*diry[dir];
				uy+=(i-2)*dirx[dir];
				val2=map_getcell(src->m,ux,uy);
				if(val2==5 || val2==1)
					alive=0;
				else
					map_setcell(src->m,ux,uy,5);
			}
			break;

		case WZ_QUAGMIRE:		/* �N�@�O�}�C�A */
			ux+=(i%5-2);
			uy+=(i/5-2);
			break;

		case AS_VENOMDUST:		/* �x�m���_�X�g */
			{
				static const int dx[]={-1,0,0,0,1};
				static const int dy[]={0,-1,0,1,0};
				ux+=dx[i];
				uy+=dy[i];
			}
			break;

		/* �_���X�Ȃ� */
		case BD_LULLABY:		/* �q��� */
		case BD_RICHMANKIM:		/* �j�����h�̉� */
		case BD_ETERNALCHAOS:	/* �i���̍��� */
		case BD_DRUMBATTLEFIELD:/* �푾�ۂ̋��� */
		case BD_RINGNIBELUNGEN:	/* �j�[�x�����O�̎w�� */
		case BD_ROKISWEIL:		/* ���L�̋��� */
		case BD_INTOABYSS:		/* �[���̒��� */
		case BD_SIEGFRIED:		/* �s���g�̃W�[�N�t���[�h */
		case BA_DISSONANCE:		/* �s���a�� */
		case BA_WHISTLE:		/* ���J */
		case BA_ASSASSINCROSS:	/* �[�z�̃A�T�V���N���X */
		case BA_POEMBRAGI:		/* �u���M�̎� */
		case BA_APPLEIDUN:		/* �C�h�D���̗ь� */
		case DC_UGLYDANCE:		/* ��������ȃ_���X */
		case DC_HUMMING:		/* �n�~���O */
		case DC_DONTFORGETME:	/* ����Y��Ȃ��Łc */
		case DC_FORTUNEKISS:	/* �K�^�̃L�X */
		case DC_SERVICEFORYOU:	/* �T�[�r�X�t�H�[���[ */
			ux+=(i%9-4);
			uy+=(i/9-4);
			if(i==40)
				range=4;	/* ���S�̏ꍇ�͔͈͂�4�ɃI�[�o�[���C�h */
			else
				range=-1;	/* ���S����Ȃ��ꍇ�͔͈͂�-1�ɃI�[�o�[���C�h */
			break;
		}
		if(alive){
			unit=skill_initunit(group,i,ux,uy);
			unit->val1=val1;
			unit->val2=val2;
			unit->limit=limit;
			unit->range=range;
		}
	}
	return group;
}



/*==========================================
 * �X�L�����j�b�g�̔����C�x���g
 *------------------------------------------
 */
int skill_unit_onplace(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg= src->group;
	struct block_list *ss=map_id2bl(sg->src_id);
	struct skill_unit_group_tickset *ts;
	int diff,goflag;
	
	
	if( bl->prev==NULL || !src->alive)
		return 0;
	if( bl->type!=BL_PC && bl->type!=BL_MOB )
		return 0;

	if(ss==NULL)
		return 0;

	ts=skill_unitgrouptickset_search( bl, sg->group_id);
	diff=DIFF_TICK(tick,ts->tick);
	goflag=(diff>sg->interval || diff<0);
	if(!goflag)
		return 0;
	ts->tick=tick;
	ts->group_id=sg->group_id;

	switch(sg->unit_id){
	case 0x83:	/* �T���N�`���A�� */
		{
			int *list=sg->vallist;
			int i,ei=0;
			
			if( battle_get_hp(bl)>=battle_get_max_hp(bl) &&
				battle_get_elem_type(bl)!=9 )
				break;

			for(i=0;i<16;i++)	/* �l�������̌v�Z */
				if(list[i]==0)
					ei=i;
				else if(list[i]==bl->id)
					break;
			if(i==16){
				list[ei]=bl->id;
				if((sg->val1--)<=0){
					skill_delunitgroup(sg);
					return 0;
				}
			}
			if( battle_get_elem_type(bl)!=9){
				int heal=sg->val2;
				if( bl->type==BL_PC &&
					pc_check_equip_dcard((struct map_session_data *)bl,4128) )
					heal=0;	/* ����峃J�[�h�i�q�[���ʂO�j */
				clif_skill_nodamage(&src->bl,bl,/*sg->skill_id*/28,heal,1);
				battle_heal(NULL,bl,heal,0);
			}else
				skill_attack(BF_MAGIC,ss,&src->bl,bl,
					sg->skill_id,sg->skill_lv,tick,0);
		}
		break;

	case 0x84:	/* �}�O�k�X�G�N�\�V�Y�� */
		{
			int race=battle_get_race(bl);
			if( race!=1 && race!=6 )
				return 0;
			skill_attack(BF_MAGIC,ss,&src->bl,bl,
				sg->skill_id,sg->skill_lv,tick,0);
		}
		break;

	case 0x85:	/* �j���[�} */
	case 0x7e:	/* �Z�C�t�e�B�E�H�[�� */
		{
			struct skill_unit *unit2;
			struct status_change *sc_data=battle_get_sc_data(bl);
			int type=(sg->unit_id==0x85)?SC_PNEUMA:SC_SAFETYWALL;
			if(sc_data[type].timer==-1)
				skill_status_change_start(bl,type,src->group->val1,(int)src);
			else if((unit2=(struct skill_unit *)sc_data[type].val2)!=src){
				if( sg->unit_id==0x85 && DIFF_TICK(sg->tick,unit2->group->tick)>0 )
					skill_status_change_start(bl,type,src->group->val1,(int)src);
				if( sg->unit_id==0x7e && sg->val1 < unit2->group->val1 )
					skill_status_change_start(bl,type,src->group->val1,(int)src);
				ts->tick-=sg->interval;
			}
		} break;

	case 0x86:	/* ���[�h�I�u���@�[�~���I��(���X�g�[���K�X�g) */
		skill_attack(BF_MAGIC,ss,&src->bl,bl,
			sg->skill_id,sg->skill_lv,tick,0);
		break;

	case 0x7f:	/* �t�@�C���[�E�H�[�� */
		if( (src->val2--)>0)
			skill_attack(BF_MAGIC,ss,&src->bl,bl,
				sg->skill_id,sg->skill_lv,tick,0);
		if( src->val2<=0 )
			skill_delunit(src);
		break;

	case 0x87:	/* �t�@�C�A�[�s���[(�����O) */
		skill_delunit(src);
		skill_unitsetting(ss,sg->skill_id,sg->skill_lv,src->bl.x,src->bl.y,1);
		break;

	case 0x88:	/* �t�@�C�A�[�s���[(������) */
		skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;

	case 0x90:	/* �X�L�b�h�g���b�v */
		if(sg->val2==0){
			battle_stopwalking(bl);
			skill_blown(&src->bl,bl,sg->skill_lv|0x30000);
			sg->limit=DIFF_TICK(tick,sg->tick)+3000;
			sg->val2=bl->id;
		}break;

	case 0x93:	/* �����h�}�C�� */
		skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		skill_delunit(src);
		break;

	case 0x8f:	/* �u���X�g�}�C�� */
	case 0x97:	/* �t���[�W���O�g���b�v */
	case 0x98:	/* �N���C���A�[�g���b�v */
		skill_attack((sg->unit_id==0x97)?BF_WEAPON:BF_MISC,
			ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
		if(sg->val2==0){
			sg->limit=DIFF_TICK(tick,sg->tick)+500;
			sg->val2=bl->id;
		}
		break;

	case 0x95:	/* �T���h�}�� */
	case 0x96:	/* �t���b�V���[ */
	case 0x94:	/* �V���b�N�E�F�[�u�g���b�v */
	case 0x91:	/* �A���N���X�l�A */
		skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,tick);
		if(sg->val2==0){
			sg->limit=DIFF_TICK(tick,sg->tick)
				+((sg->unit_id==0x91)?sg->val1/((battle_get_mode(bl)&0x20)?5:1):500);
			sg->val2=bl->id;
		}
		break;

	case 0x80:	/* ���[�v�|�[�^��(������) */
		if(bl->type==BL_PC){
			if((sg->val1--)>0){
				pc_setpos((struct map_session_data *)bl,
					sg->valstr,sg->val2>>16,sg->val2&0xffff,0);
			}else
				skill_delunitgroup(sg);
		}
		break;

	case 0x8e:	/* �N�@�O�}�C�A */
	case 0x92:	/* �x�m���_�X�g */
		{
			int type=SkillStatusChangeTable[sg->skill_id];
			if( battle_get_sc_data(bl)[type].timer==-1 )
				skill_status_change_start(bl,type,src->group->val1,(int)src);
		}
		break;

	case 0x9e:	/* �q��S */
	case 0x9f:	/* �j�����h�̉� */
	case 0xa0:	/* �i���̍��� */
	case 0xa1:	/* �푾�ۂ̋��� */
	case 0xa2:	/* �j�[�x�����O�̎w�� */
	case 0xa3:	/* ���L�̋��� */
	case 0xa4:	/* �[���̒��� */
	case 0xa5:	/* �s���g�̃W�[�N�t���[�h */
	case 0xa6:	/* �s���a�� */
	case 0xa7:	/* ���J */
	case 0xa8:	/* �[�z�̃A�T�V���N���X */
	case 0xa9:	/* �u���M�̎� */
	case 0xaa:	/* �C�h�D���̗ь� */
	case 0xab:	/* ��������ȃ_���X */
	case 0xac:	/* �n�~���O */
	case 0xad:	/* ����Y��Ȃ��Łc */
	case 0xae:	/* �K�^�̃L�X */
	case 0xaf:	/* �T�[�r�X�t�H�[���[ */
		{
			struct skill_unit *unit2;
			struct status_change *sc_data=battle_get_sc_data(bl);
			int type=SkillStatusChangeTable[sg->skill_id];
			if(sc_data[type].timer==-1)
				skill_status_change_start(bl,type,src->group->val1,(int)src);
			else if((unit2=(struct skill_unit *)sc_data[type].val4)!=src){
				if( DIFF_TICK(sg->tick,unit2->group->tick)>0 )
					skill_status_change_start(bl,type,0,(int)src);
/*				if( sg->unit_id==0x7e && sg->val1 < unit2->group->val1 )
					skill_status_change_start(bl,type,0,(int)src);*/
				ts->tick-=sg->interval;
			}
		} break;

/*	default:
		printf("skill_unit_onplace: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}
	return 0;
}
/*==========================================
 * �X�L�����j�b�g���痣�E����(�������͂��Ă���)�ꍇ
 *------------------------------------------
 */
int skill_unit_onout(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg= src->group;

	if( bl->prev==NULL || !src->alive)
		return 0;
	if( bl->type!=BL_PC && bl->type!=BL_MOB )
		return 0;

	switch(sg->unit_id){
	case 0x83:	/* �T���N�`���A�� */
		{
			int i,*list=sg->vallist;
			for(i=0;i<list[i];i++)
				if(list[i]==bl->id)
					list[i]=0;
		}
		break;

	case 0x7e:	/* �Z�C�t�e�B�E�H�[�� */
	case 0x85:	/* �j���[�} */
	case 0x8e:	/* �N�@�O�}�C�A */
		{
			struct skill_unit *unit2;
			struct status_change *sc_data=battle_get_sc_data(bl);
			int type=
				(sg->unit_id==0x85)?SC_PNEUMA:
				((sg->unit_id==0x7e)?SC_SAFETYWALL:
				 SC_QUAGMIRE);
			if(sc_data[type].timer!=-1 && (unit2=(struct skill_unit *)sc_data[type].val2)==src){
				skill_status_change_end(bl,type,-1);
			}
		} break;

	case 0x91:	/* �A���N���X�l�A */
		{
			struct block_list *target=map_id2bl(sg->val2);
			if( target==bl )
				skill_status_change_end(bl,SC_ANKLE,-1);
			sg->limit=DIFF_TICK(tick,sg->tick)+1000;
		}
		break;

	case 0x9e:	/* �q��S */
	case 0x9f:	/* �j�����h�̉� */
	case 0xa0:	/* �i���̍��� */
#if 0
	case 0xa1:	/* �푾�ۂ̋��� */
#endif
	case 0xa2:	/* �j�[�x�����O�̎w�� */
	case 0xa3:	/* ���L�̋��� */
#if 0
	case 0xa4:	/* �[���̒��� */
#endif
	case 0xa5:	/* �s���g�̃W�[�N�t���[�h */
#if 0
	case 0xa6:	/* �s���a�� */
	case 0xa7:	/* ���J */
#endif
	case 0xa8:	/* �[�z�̃A�T�V���N���X */
#if 0
	case 0xa9:	/* �u���M�̎� */
#endif
	case 0xaa:	/* �C�h�D���̗ь� */
#if 0
	case 0xab:	/* ��������ȃ_���X */
	case 0xac:	/* �n�~���O */
#endif
	case 0xad:	/* ����Y��Ȃ��Łc */
	case 0xae:	/* �K�^�̃L�X */
#if 0
	case 0xaf:	/* �T�[�r�X�t�H�[���[ */
#endif
		{
			struct skill_unit *unit2;
			struct status_change *sc_data=battle_get_sc_data(bl);
			int type=SkillStatusChangeTable[sg->skill_id];
			if(sc_data[type].timer!=-1 && (unit2=(struct skill_unit *)sc_data[type].val4)==src){
				skill_status_change_end(bl,type,-1);
			}
		}
		break;

/*	default:
		printf("skill_unit_onout: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}
	skill_unitgrouptickset_delete(bl,sg->group_id);
	return 0;
}
/*==========================================
 * �X�L�����j�b�g�̍폜�C�x���g
 *------------------------------------------
 */
int skill_unit_ondelete(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg= src->group;
	
	if( bl->prev==NULL || !src->alive)
		return 0;
	if( bl->type!=BL_PC && bl->type!=BL_MOB )
		return 0;

	switch(sg->unit_id){
	case 0x85:	/* �j���[�} */
	case 0x7e:	/* �Z�C�t�e�B�E�H�[�� */
	case 0x8e:	/* �N�@�O�}�C�� */
	case 0x9e:	/* �q��S */
	case 0x9f:	/* �j�����h�̉� */
	case 0xa0:	/* �i���̍��� */
	case 0xa1:	/* �푾�ۂ̋��� */
	case 0xa2:	/* �j�[�x�����O�̎w�� */
	case 0xa3:	/* ���L�̋��� */
	case 0xa4:	/* �[���̒��� */
	case 0xa5:	/* �s���g�̃W�[�N�t���[�h */
	case 0xa6:	/* �s���a�� */
	case 0xa7:	/* ���J */
	case 0xa8:	/* �[�z�̃A�T�V���N���X */
	case 0xa9:	/* �u���M�̎� */
	case 0xaa:	/* �C�h�D���̗ь� */
	case 0xab:	/* ��������ȃ_���X */
	case 0xac:	/* �n�~���O */
	case 0xad:	/* ����Y��Ȃ��Łc */
	case 0xae:	/* �K�^�̃L�X */
	case 0xaf:	/* �T�[�r�X�t�H�[���[ */
		return skill_unit_onout(src,bl,tick);

/*	default:
		printf("skill_unit_ondelete: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}
	skill_unitgrouptickset_delete(bl,sg->group_id);
	return 0;
}
/*==========================================
 * �X�L�����j�b�g�̌��E�C�x���g
 *------------------------------------------
 */
int skill_unit_onlimit(struct skill_unit *src,unsigned int tick)
{
	struct skill_unit_group *sg= src->group;
	

	switch(sg->unit_id){
	case 0x81:	/* ���[�v�|�[�^��(�����O) */
		{
			struct skill_unit_group *group=
				skill_unitsetting(map_id2bl(sg->src_id),sg->skill_id,sg->skill_lv,
					src->bl.x,src->bl.y,1);
			group->valstr=malloc(16);
			if(group->valstr==NULL){
				printf("skill_unit_ondelete: out of memory !\n");
				exit(0);
			}
			memcpy(group->valstr,sg->valstr,16);
			group->val2=sg->val2;
		}
		break;

	case 0x8d:	/* �A�C�X�E�H�[�� */
		map_setcell(src->bl.m,src->bl.x,src->bl.y,src->val2);
		break;
			
	}
	return 0;
}
/*==========================================
 * �X�L�����j�b�g�̃_���[�W�C�x���g
 *------------------------------------------
 */
int skill_unit_ondamaged(struct skill_unit *src,struct block_list *bl,
	int damage,unsigned int tick)
{
	struct skill_unit_group *sg= src->group;
	
	switch(sg->unit_id){
	case 0x8d:	/* �A�C�X�E�H�[�� */
		sg->limit-=damage;
		break;
	}
	return 0;
}


/*---------------------------------------------------------------------------- */



/*==========================================
 * �X�L���g�p�i�r�������A�ꏊ�w��j
 *------------------------------------------
 */
int skill_castend_pos( int tid, unsigned int tick, int id,int data )
{
	struct map_session_data* sd=NULL/*,*target_sd=NULL*/;
	
	if( (sd=map_id2sd(id))==NULL )
		return 0;
	
	if( sd->skilltimer != tid )	/* �^�C�}ID�̊m�F */
		return 0;
	sd->skilltimer=-1;

	if(pc_isdead(sd))
		return 0;
	
	if(!skill_check_condition( sd ))		/* �g�p�����`�F�b�N */
		return 0;

	printf("skill castend skill=%d\n",sd->skillid);

	skill_castend_pos2(&sd->bl,sd->skillx,sd->skilly,sd->skillid,sd->skilllv,tick,0);

	return 0;
}

/*==========================================
 * �X�L���g�p�����i�U�Ŏg�p���s�j
 *------------------------------------------
 */
int skill_check_condition( struct map_session_data *sd )
{
	int j=0,sp=0,zeny=0,spiritball=0;
	int	i[3]={0,0,0},
		item_id[3]={0,0,0},
		item_amount[3]={0,0,0};

	if(sd->sc_data[SC_STEELBODY].timer!=-1) {
		clif_skill_fail(sd,sd->skillid,0,0);
		return 0;
	}

	if(sd->skillitem==sd->skillid) {	/* �A�C�e���̏ꍇ���������� */
		sd->skillitem = sd->skillitemlv = -1;
	}else{

		sp=skill_get_sp(sd->skillid, sd->skilllv);	/* ����SP */
		if(sd->dsprate!=100)
			sp=sp*sd->dsprate/100;	/* ����SP�C�� */
		
		/* �X�L�����Ƃ̎g�p���� */
		switch(sd->skillid)
		{
		case SA_ABRACADABRA:
			item_amount[0]+=1;
		case SA_VOLCANO:
		case SA_DELUGE:
		case SA_VIOLENTGALE:
			item_id[0]=715;		//	ygem = 715;
			item_amount[0]+=1;
			break;

		case SA_DISPELL:
			item_id[1]=715;		//	ygem = 715;
			item_amount[1]+=1;
		case MG_STONECURSE:		// �X�g�[���J�[�X
		case AS_VENOMDUST:		// �x�i���_�X�g
			item_id[0]=716;		//	rgem = 716;
			item_amount[0]+=1;
			break;

		case SA_LANDPROTECTOR:
			item_id[1]=715;
			item_amount[1]+=1;
		case MG_SAFETYWALL:		// �Z�C�t�e�B�E�H�[��
		case AL_WARP:			// ���[�v�|�[�^��
		case ALL_RESURRECTION:	// ���U���N�V����
		case PR_SANCTUARY:		// �T���N�`���A��
		case PR_MAGNUS:			// �}�O�k�X�G�N�\�V�Y��
		case WZ_FIREPILLAR:		// �t�@�C�A�[�s���[
			item_id[0]=717;		//	bgem = 717;
			item_amount[0]+=1;
			break;

		case SA_FROSTWEAPON:
			item_id[0]=991;
			item_amount[0]+=1;
			break;

		case SA_LIGHTNINGLOADER:
			item_id[0]=992;
			item_amount[0]+=1;
			break;

		case SA_SEISMICWEAPON:
			item_id[0]=993;
			item_amount[0]+=1;
			break;

		case MC_MAMMONITE:		/* ���}�[�i�C�g */
			zeny = sd->skilllv*100;
			if( sd->status.zeny<zeny ) {
				clif_skill_fail(sd,sd->skillid,5,0);	/* Zeny�s���F���s�ʒm */
				return 0;
			}
			break;

		case MC_VENDING:		// �I�X�J��	
			if(!pc_iscarton(sd)) {
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;
			}
			break;


		case AC_DOUBLE:		// �_�u���X�g���C�t�B���O
		case AC_SHOWER:		// �A���[�V�����[
		case AC_CHARGEARROW:		// �`���[�W�A���[
			if( sd->status.weapon != 11) {
				clif_skill_fail(sd,sd->skillid,6,0);	// �|
			     	return 0; 
			}
			break;

		case KN_BRANDISHSPEAR:	// �u�����f�B�b�V���X�s�A
			if(!pc_isriding(sd)) {
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;		// ,�y�R�y�R���		
			}
		case KN_PIERCE:			// �s�A�[�X
		case KN_SPEARSTAB:		// �X�s�A�X�^�u
		case KN_SPEARBOOMERANG:	// �X�s�A�u�[������
			if(sd->status.weapon != 4 && sd->status.weapon != 5) {
				clif_skill_fail(sd,sd->skillid,6,0);	// ��
				return 0; 
			}
			break;

		case KN_TWOHANDQUICKEN:	// �c�[�n���h�N�C�b�P��
			if( sd->status.weapon != 3) {
				clif_skill_fail(sd,sd->skillid,6,0);	// ���茕
				return 0;
			}
			break;
			
		case BS_ADRENALINE:		// �A�h���i�������b�V��
		case BS_HAMMERFALL:		// �n���}�[�t�H�[��
			if( sd->status.weapon != 6 && sd->status.weapon != 7 && sd->status.weapon != 8) {
				clif_skill_fail(sd,sd->skillid,6,0);	// ���E�Ń��C�X
				return 0;
			}
			break;

		case BS_MAXIMIZE:		/* �}�L�V�}�C�Y�p���[ */
		case NV_TRICKDEAD:		/* ���񂾂ӂ� */
		case TF_HIDING:			/* �n�C�f�B���O */
		case AS_CLOAKING:		/* �N���[�L���O */
			if(sd->sc_data[SkillStatusChangeTable[sd->skillid]].timer!=-1)
				sp=0;			/* ��������ꍇ��SP����Ȃ� */
			break;

		case HT_BLITZBEAT:		/* �u���b�c�r�[�g */
			if(!pc_isfalcon(sd)) {		/* �邪���Ȃ� */
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;
			}
			break;

		case AS_GRIMTOOTH:		/* �O�����g�D�[�X */
			if(!pc_ishiding(sd)) {		// �n�C�f�B���O���
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;
			}
			if( sd->status.weapon != 16)  {
				clif_skill_fail(sd,sd->skillid,6,0);    	// �J�^�[������
				return 0; 
			}
			break;

		case CR_SPEARQUICKEN:	// �X�s�A�N�C�b�P��
			if( sd->status.weapon != 5) {
				clif_skill_fail(sd,sd->skillid,6,0);	// ���葄
				return 0;
			}
			break;

		case MO_EXTREMITYFIST:					// ���C���e�P��
			if( sd->sc_data[SC_EXPLOSIONSPIRITS].timer == -1) {
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;
			} else {
				delete_timer(sd->sc_data[SC_EXPLOSIONSPIRITS].timer,skill_status_change_timer);
				sd->sc_data[SC_EXPLOSIONSPIRITS].timer = -1;	// �����g������
				spiritball = 5;									// ����
			}
			break;

		case MO_FINGEROFFENSIVE:	//�w�e
				spiritball = sd->skilllv;							// ����
				if (sd->spiritball != 0 && sd->spiritball < spiritball) {
					spiritball = sd->spiritball;
					sd->spiritball_old = sd->spiritball;	
				}
				else sd->spiritball_old = sd->skilllv;	
			break;
		case MO_INVESTIGATE:		//����
		case MO_COMBOFINISH:
				spiritball = 1;									// ����
			break;

		case MO_BODYRELOCATION:
			if(!pc_can_reach(sd,sd->skillx,sd->skilly)) {
				clif_skill_fail(sd,sd->skillid,0,0);
				return 0;
			} else
				spiritball = 1;									// ����
			break;

		
		case MO_STEELBODY:						// ����
		case MO_EXPLOSIONSPIRITS:				// �����g��
				spiritball = 5;									// ����
			break;
		}

		if( sp>0 && sd->status.sp < sp) {			/* SP�`�F�b�N */
			clif_skill_fail(sd,sd->skillid,1,0);		/* SP�s���F���s�ʒm */
			return 0;
		}
		
		if( spiritball > 0 && sd->spiritball < spiritball) {
			clif_skill_fail(sd,sd->skillid,0,0);		// �����s��
			return 0;
		}

		if(!pc_check_equip_dcard(sd,4132) && 
			(item_id[0] || item_id[1] || item_id[2])) {	// �~�X�g���X�J�[�h
			for(j=0;j<3;j++) {
				if(item_id[j] == 0 || item_amount[j] == 0)
					continue;
				if((i[j]=pc_search_inventory(sd,item_id[j])) == -1 ||
					sd->status.inventory[i[j]].amount < item_amount[j]) {	// �W�F���X�g�[���Ȃ�
					if(item_id[j] == 716 || item_id[j] == 717)
						clif_skill_fail(sd,sd->skillid,(6+(item_id[j]-715)),0);
					else
						clif_skill_fail(sd,sd->skillid,0,0);
					return 0;
				}
			}
			for(j=0;j<3;j++) {
				if(i[j] == 0)
					continue;
				pc_delitem(sd,i[j],item_amount[j],0);		// �W�F���X�g�[������
			}
		}

		if(sp) {					/* SP���� */
			sd->status.sp-=sp;
			clif_updatestatus(sd,SP_SP);
		}
		if(zeny) {					/* Zeny���� */
			sd->status.zeny -= zeny;
			clif_updatestatus(sd,SP_ZENY);
		}
		if(spiritball)			// ��������
			pc_delspiritball(sd,spiritball,0);
	}
	return 1;
}


/*==========================================
 * �r�����Ԍv�Z
 *------------------------------------------
 */
int skill_castfix( struct block_list *bl, int time )
{
	struct status_change *sc_data;
	int dex=battle_get_dex(bl);
	int castrate=100;
	if(time==0)
		return 0;
	if(bl->type==BL_PC)
		castrate=((struct map_session_data *)bl)->castrate;
	
	time=time*castrate*(150- dex)/15000;
	time=time*battle_config.cast_rate/100;
	
	if( (sc_data = battle_get_sc_data(bl))[SC_SUFFRAGIUM].timer!=-1 ){
		/* �T�t���M�E�� */
		time=time*(100-sc_data[SC_SUFFRAGIUM].val1*15)/100;
		skill_status_change_end( bl, SC_SUFFRAGIUM, -1);
	}
	return (time>0)?time:0;
}
/*==========================================
 * �f�B���C�v�Z
 *------------------------------------------
 */
int skill_delayfix( struct block_list *bl, int time )
{
	if(time<=0)
		return 0;
	
	if( battle_config.delay_dependon_dex )	/* dex�̉e�����v�Z���� */
		time=time*(150- battle_get_dex(bl))/150;

	time=time*battle_config.delay_rate/100;
	
	return (time>0)?time:0;
}
/*==========================================
 * �X�L���g�p�iID�w��j
 *------------------------------------------
 */
int skill_use_id( struct map_session_data *sd, int target_id,
	int skill_num, int skill_lv)
{
	int casttime=0,delay=0,tick;
	struct map_session_data* target_sd=NULL;
	int target_fd=-1;
	int forcecast=0;
	struct block_list *bl;

	bl=map_id2bl(target_id);
	if(bl==NULL){
/*		printf("skill target not found %d\n",target_id); */
		return 0;
	}
	if(sd->bl.m != bl->m || pc_isdead(sd))
		return 0;

	/* ���ق�ُ�i�������A�O�����Ȃǂ̔��������j */
	if( sd->opt1>0 || sd->status.option&6 || sd->sc_data[SC_DIVINA].timer!=-1 ){
		if( (sd->status.option&4) && skill_num==AS_CLOAKING );	/* �N���[�L���O�� */
		else if( (sd->status.option&2) && (skill_num==TF_HIDING || skill_num==AS_GRIMTOOTH) );	/* �n�C�f�B���O�� */
		else
			return 0;
	}

	if( skill_num==HT_BLITZBEAT && !(sd->status.option&0x10) ){	/* �邪���Ȃ� */
		return 0;
	}

	/* �˒��Ə�Q���`�F�b�N */
	if(!battle_check_range(&sd->bl,bl->x,bl->y,skill_get_range(skill_num)))
		return 0;

	if(bl->type==BL_PC){
		target_sd=(struct map_session_data*)bl;
		target_fd=target_sd->fd;
	}
	pc_stopattack(sd);

	casttime=skill_castfix(&sd->bl, skill_get_cast( skill_num,skill_lv) );
	delay=skill_delayfix(&sd->bl, skill_get_delay( skill_num,skill_lv) );

	sd->skillcastcancel=1;

	switch(skill_num){	/* ��������ȏ������K�v */
	case AL_HEAL:	/* �q�[�� */
		if( battle_get_elem_type(bl)==9)
			forcecast=1;	/* �q�[���A�^�b�N�Ȃ�r���G�t�F�N�g�L�� */
		break;
	case ALL_RESURRECTION:	/* ���U���N�V���� */
		if( battle_get_elem_type(bl)==9){	/* �G���A���f�b�h�Ȃ� */
			forcecast=1;	/* �^�[���A���f�b�g�Ɠ����r������ */
			casttime=skill_castfix(&sd->bl, skill_get_cast(PR_TURNUNDEAD,skill_lv) );
		}
		break;
	/* �r���L�����Z������Ȃ����� */
	case KN_BRANDISHSPEAR:	/* �u�����f�B�b�V���X�s�A */
	case KN_BOWLINGBASH:	/* �{�E�����O�o�b�V�� */
	case AC_CHARGEARROW:	/* �`���[�W�A���[ */
	case RG_STRIPWEAPON:	/* �X�g���b�v�E�G�|�� */
	case RG_STRIPSHIELD:	/* �X�g���b�v�V�[���h */
	case RG_STRIPARMOR:	/* �X�g���b�v�A�[�}�[ */
	case RG_STRIPHELM:	/* �X�g���b�v�w���� */
	case CR_GRANDCROSS:	/* �O�����h�N���X */
	case MO_CALLSPIRITS:	// �C��
	case MO_INVESTIGATE:	/* ���� */
	case MO_FINGEROFFENSIVE:	/* �w�e */
	case MO_STEELBODY:	/* ����*/
		sd->skillcastcancel=0;
		break;
	}

	printf("skill use target_id=%d skill=%d lv=%d cast=%d\n"
		,target_id,skill_num,skill_lv,casttime);

	if(sd->skillitem == skill_num)
		casttime = delay = 0;

	if( casttime>0 || forcecast ){ /* �r�����K�v */
		struct mob_data *md;
		clif_skillcasting( &sd->bl,
			sd->bl.id, target_id, 0,0, skill_num,casttime);

		/* �r�����������X�^�[ */
		if( bl->type==BL_MOB && mob_db[(md=(struct mob_data *)bl)->class].mode&0x10 &&
			md->state.state!=MS_ATTACK && sd->ghost_timer == -1){
				md->target_id=sd->bl.id;
				md->state.targettype = ATTACKABLE;
				md->min_chase=13;
		}
	}

	if( casttime==0 )	/* �r���̖������̂̓L�����Z������Ȃ� */
		sd->skillcastcancel=0;

	sd->skilltarget	= target_id;
/*	sd->cast_target_bl	= bl; */
	sd->skillx		= 0;
	sd->skilly		= 0;
	sd->skillid		= skill_num;
	sd->skilllv		= skill_lv;
	tick=gettick();
	sd->canmove_tick = tick + casttime + delay;
	if(casttime > 0)
		sd->skilltimer = add_timer( tick+casttime, skill_castend_id, sd->bl.id, 0 );
	else {
		sd->skilltimer = 0;
		skill_castend_id(sd->skilltimer,tick,sd->bl.id,0);
	}

	return 0;
}

/*==========================================
 * �X�L���g�p�i�ꏊ�w��j
 *------------------------------------------
 */
int skill_use_pos( struct map_session_data *sd,
	int skill_x, int skill_y, int skill_num, int skill_lv)
{
	int casttime=0,delay=0,tick;
	
	if(pc_isdead(sd))
		return 0;

	if( sd->opt1>0 || sd->status.option&6 || sd->sc_data[SC_DIVINA].timer!=-1 )
		return 0;	/* �ُ�Ⓘ�قȂ� */

	/* �˒��Ə�Q���`�F�b�N */
	if(!battle_check_range(&sd->bl,skill_x,skill_y,skill_get_range(skill_num)))
		return 0;
	
	pc_stopattack(sd);

	casttime=skill_castfix(&sd->bl, skill_get_cast( skill_num,skill_lv) );
	delay=skill_delayfix(&sd->bl, skill_get_delay( skill_num,skill_lv) );

	sd->skillcastcancel=1;

	printf("skill use target_pos=(%d,%d) skill=%d lv=%d cast=%d\n",
		skill_x,skill_y,skill_num,skill_lv,casttime);

	if(sd->skillitem == skill_num)
		casttime = delay = 0;

	if( casttime>0 )	/* �r�����K�v */
		clif_skillcasting( &sd->bl,
			sd->bl.id, 0, skill_x,skill_y, skill_num,casttime);

	if( casttime==0 )	/* �r���̖������̂̓L�����Z������Ȃ� */
		sd->skillcastcancel=0;


	sd->skillx			= skill_x;
	sd->skilly			= skill_y;
	sd->skilltarget	= 0;
/*	sd->cast_target_bl	= NULL; */
	sd->skillid		= skill_num;
	sd->skilllv			= skill_lv;
	tick=gettick();
	sd->canmove_tick = tick + casttime + delay;
	if(casttime > 0)
		sd->skilltimer = add_timer( tick+casttime, skill_castend_pos, sd->bl.id, 0 );
	else {
		sd->skilltimer = 0;
		skill_castend_pos(sd->skilltimer,tick,sd->bl.id,0);
	}

	return 0;
}



/*==========================================
 * �X�L���r���L�����Z��
 *------------------------------------------
 */
int skill_castcancel( struct block_list *bl )
{
	if(bl->type==BL_PC){
		struct map_session_data *sd=(struct map_session_data *)bl;
		sd->canmove_tick=gettick();
		if( sd->skilltimer!=-1){
			if( skill_get_inf( sd->skillid )&2 )
				delete_timer( sd->skilltimer, skill_castend_pos );
			else
				delete_timer( sd->skilltimer, skill_castend_id );
			sd->skilltimer=-1;
			clif_skillcasting( bl, bl->id, 0, 0,0, sd->skillid,0);	/* �L�����Z���p�P */
		}

		return 0;
	}else if(bl->type==BL_MOB){
		struct mob_data *md=(struct mob_data *)bl;
		if( md->skilltimer!=-1 ){
			if( skill_get_inf( md->skillid )&2 )
				delete_timer( md->skilltimer, mobskill_castend_pos );
			else
				delete_timer( md->skilltimer, mobskill_castend_id );
			md->skilltimer=-1;
			clif_skillcasting( bl, bl->id, 0, 0,0, md->skillid,0);	/* �L�����Z���p�P */
		}
		return 0;
	}
	return 1;
}




/*----------------------------------------------------------------------------
 * �X�e�[�^�X�ُ�
 *----------------------------------------------------------------------------
 */

/*==========================================
 * �X�e�[�^�X�ُ�^�C�}�[�͈͏���
 *------------------------------------------
 */
int skill_status_change_timer_sub(struct block_list *bl, va_list ap )
{
	struct block_list *src;
	int type;
	unsigned int tick;
	src=va_arg(ap,struct block_list*);
	type=va_arg(ap,int);
	tick=va_arg(ap,unsigned int);
	
	if(bl->type!=BL_PC && bl->type!=BL_MOB)
		return 0;
	
	switch( type ){
	case SC_SIGHT:	/* �T�C�g */
	case SC_RUWACH:	/* ���A�t */
		if( (*battle_get_option(bl))&6 ){
			skill_status_change_end( bl, SC_HIDDING, -1);
			skill_status_change_end( bl, SC_CLOAKING, -1);
			if( type==SC_RUWACH && battle_check_target( src,bl, BCT_ENEMY ))
				skill_attack(BF_MAGIC,src,src,bl,(type==SC_SIGHT)?10:24,1,tick,0);
		}

		break;
	}
	return 0;
}

/*==========================================
 * �X�e�[�^�X�ُ�I��
 *------------------------------------------
 */
int skill_status_change_end( struct block_list* bl , int type,int tid )
{
	struct status_change* sc_data;
	int opt_flag=0;
	short *sc_count, *option, *opt1, *opt2;
	
	sc_data=battle_get_sc_data(bl);
	sc_count=battle_get_sc_count(bl);
	option=battle_get_option(bl);
	opt1=battle_get_opt1(bl);
	opt2=battle_get_opt2(bl);
	
	if(bl->type!=BL_PC && bl->type!=BL_MOB) {
		printf("skill_status_change_end: neither MOB nor PC !\n");
		return 0;
	}
	
	
	if((*sc_count)>0 && sc_data[type].timer!=-1 &&
		(sc_data[type].timer==tid || tid==-1) ){
		
		if(tid==-1)	/* �^�C�}����Ă΂�Ă��Ȃ��Ȃ�^�C�}�폜������ */
			delete_timer(sc_data[type].timer,skill_status_change_timer);
	
		/* �Y���ُ̈�𐳏�ɖ߂� */
		sc_data[type].timer=-1;
		(*sc_count)--;

		if(bl->type==BL_PC && type<64)	/* �A�C�R������ */
			clif_status_change(bl,type,0);

		
		switch(type){	/* ����ɖ߂�Ƃ��Ȃɂ��������K�v */
		case SC_STONE:
		case SC_FREEZE:
		case SC_STAN:
		case SC_SLEEP:
			*opt1=0;
			opt_flag=1;
			break;

		case SC_POISON:
		case SC_CURSE:
		case SC_SILENCE:
		case SC_BLIND:
			*opt2&=~(1<<(type-SC_POISON));
			opt_flag=1;
			break;

		case SC_HIDDING:
		case SC_CLOAKING:
			*option&=~((type==SC_HIDDING)?2:4);
			opt_flag =1 ;
			break;

		case SC_SIGHT:
		case SC_RUWACH:
			*option&=~1;
			opt_flag=1;
			break;
		}
		
		if(opt_flag)	/* option�̕ύX��`���� */
			clif_changeoption(bl);

		if(bl->type==BL_PC)
			pc_calcstatus((struct map_session_data *)bl,0);	/* �X�e�[�^�X�Čv�Z */
	}

	return 0;
}
/*==========================================
 * �X�e�[�^�X�ُ�I���^�C�}�[
 *------------------------------------------
 */
int skill_status_change_timer(int tid, unsigned int tick, int id, int data)
{
	int type=data;
	struct block_list *bl;
	struct map_session_data *sd=NULL;
	struct status_change *sc_data;
	short *sc_count;
	
	bl=map_id2bl(id);
	if(bl==NULL)
		return 0;
	
	if(bl->type==BL_PC)
		sd=(struct map_session_data *)bl;

	sc_data=battle_get_sc_data(bl);
	sc_count=battle_get_sc_count(bl);
	
	switch(type){	/* ����ȏ����ɂȂ�ꍇ */
	case SC_MAXIMIZEPOWER:	/* �}�L�V�}�C�Y�p���[ */
	case SC_CLOAKING:		/* �N���[�L���O */
		if(sd){
			if( sd->status.sp > 0 ){	/* SP�؂��܂Ŏ��� */
				sd->status.sp--;
				clif_updatestatus(sd,SP_SP);
				sc_data[type].timer=add_timer(	/* �^�C�}�[�Đݒ� */
					sc_data[type].val2+tick, skill_status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_HIDDING:		/* �n�C�f�B���O */
		if(sd){		/* SP�������āA���Ԑ����̊Ԃ͎��� */
			if( sd->status.sp > 0 && (--sc_data[type].val2)>0 ){
				if(sc_data[type].val2 % (sc_data[type].val1+3) ==0 ){
					sd->status.sp--;
					clif_updatestatus(sd,SP_SP);
				}
				sc_data[type].timer=add_timer(	/* �^�C�}�[�Đݒ� */
					1000+tick, skill_status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_SIGHT:	/* �T�C�g */
	case SC_RUWACH:	/* ���A�t */
		{
			const int range=AREA_SIZE;
			map_foreachinarea( skill_status_change_timer_sub,
				bl->m, bl->x-range, bl->y-range, bl->x+range,bl->y+range,0,
				bl,type,tick);
	
			if( (--sc_data[type].val2)>0 ){
				sc_data[type].timer=add_timer(	/* �^�C�}�[�Đݒ� */
					250+tick, skill_status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_PROVOKE:	/* �v���{�b�N/�I�[�g�o�[�T�[�N */
		if(sc_data[type].val2!=0){	/* �I�[�g�o�[�T�[�N�i�P�b���Ƃ�HP�`�F�b�N�j */
			if(sd!=NULL && sd->status.hp>sd->status.max_hp/4)	/* ��~ */
				break;
			if(sc_data[type].timer==tid)
				sc_data[type].timer=add_timer( 1000+tick,
					skill_status_change_timer, bl->id, data );
		}
		break;

	case SC_WATERBALL:	/* �E�H�[�^�[�{�[�� */
		{
			struct block_list *target=map_id2bl(sc_data[type].val2);
			if(target==NULL || target->prev==NULL)
				break;
			skill_attack(BF_MAGIC,bl,bl,target,86,sc_data[type].val1,tick,0);
			if((--sc_data[type].val3)>0)
				sc_data[type].timer=add_timer( 100+tick,
					skill_status_change_timer, bl->id, data );
		}
		break;

	/* ���Ԑ؂ꖳ���H�H */
	case SC_AETERNA:
	case SC_TRICKDEAD:
	case SC_STONE:
	case SC_BLIND:
	case SC_RIDING:
	case SC_FALCON:
	case SC_WEIGHT50:
	case SC_WEIGHT90:
		if(sc_data[type].timer==tid)
			sc_data[type].timer=add_timer( 1000*600+tick,
				skill_status_change_timer, bl->id, data );
		return 0;
	}

	return skill_status_change_end( bl,type,tid );
}
/*==========================================
 * �X�e�[�^�X�ُ�J�n
 *------------------------------------------
 */
int skill_status_change_start(struct block_list *bl,int type,int val1,int val2)
{
	struct map_session_data *sd = NULL;
	struct mob_data *md = NULL;
	struct status_change* sc_data;
	int tick = 0;
	short *sc_count, *option, *opt1, *opt2;
	int opt_flag = 0;
	int val3=0,val4=val2;
	
	sc_data=battle_get_sc_data(bl);
	sc_count=battle_get_sc_count(bl);
	option=battle_get_option(bl);
	opt1=battle_get_opt1(bl);
	opt2=battle_get_opt2(bl);
	
	
	if(bl->type==BL_MOB){
		md=(struct mob_data *)bl;
		if(mob_db[md->class].mode & 0x20 &&
			(type==SC_STONE || type==SC_FREEZE || type==SC_STAN || type==SC_SLEEP)){
			/* �{�X�ɂ͌����Ȃ� */
			return 0;
		}
	}else if(bl->type==BL_PC){
		sd=(struct map_session_data *)bl;
		
		if(SC_STONE<=type && type<=SC_BLIND){	/* �J�[�h�ɂ��ϐ� */
			if(sd->reseff[type-SC_STONE] && rand()%100<sd->reseff[type-SC_STONE]){
				printf("skill_sc_start: card�ɂ��ُ�ϐ�����\n");
				return 0;
			}
		}
	}else{
		printf("skill_status_change_start: neither MOB nor PC !\n");
		return 0;
	}
	
	
	if(sc_data[type].timer != -1){	/* ���łɓ����ُ�ɂȂ��Ă���ꍇ�^�C�}���� */
		(*sc_count)--;
		delete_timer(sc_data[type].timer, skill_status_change_timer);
		sc_data[type].timer = -1;
	}
	
	switch(type){	/* �ُ�̎�ނ��Ƃ̏��� */
		case SC_PROVOKE:			/* �v���{�b�N */
			if(val2==0)	tick = 1000 * 30;
			else		tick = 1000;/* (�I�[�g�o�[�T�[�N) */
			break;
		case SC_ENDURE:				/* �C���f���A */
			tick = 1000 * (7 + val1*3);
			break;
		case SC_CONCENTRATE:		/* �W���͌��� */
			tick = 1000 * (40 + val1 * 20);
			break;
		case SC_BLESSING:			/* �u���b�V���O */
			tick = 1000 * (40 + val1 * 20);
			break;
		case SC_ANGELUS:			/* �A���[���X */
			tick = 1000 * (30 * val1);
			break;
		case SC_INCREASEAGI:		/* ���x�㏸ */
			tick = 1000 * (40 + val1 * 20);
			break;
		case SC_DECREASEAGI:		/* ���x���� */
			tick = 1000 * (30 + val1 * 10);
			break;
		case SC_TWOHANDQUICKEN:		/* 2HQ */
			tick = 1000 * (30 * val1);
			break;
		case SC_ADRENALINE:			/* �A�h���i�������b�V�� */
			tick = 1000 * (30 * val1);
			break;
		case SC_WEAPONPERFECTION:	/* �E�F�|���p�[�t�F�N�V���� */
			tick = 1000 * (30 * val1);
			break;
		case SC_OVERTHRUST:			/* �I�[�o�[�X���X�g */
			tick = 1000 * (20 * val1);
			break;
		case SC_MAXIMIZEPOWER:		/* �}�L�V�}�C�Y�p���[(SP��1���鎞��,val2�ɂ�) */
			tick = 1000 * val1;
			val2 = tick;
			break;
		case SC_ENCPOISON:			/* �G���`�����g�|�C�Y�� */
			tick = 1000 * (15 + val1 * 15);
			val2=((val1 - 1) / 2) + 3;	/* �ŕt�^�m�� */
			if( sc_data[SC_ASPERSIO].timer!=-1 )	/* �A�X�y���� */
				skill_status_change_end(bl,SC_ASPERSIO,-1);
			break;
		case SC_IMPOSITIO:			/* �C���|�V�e�B�I�}�k�X */
			tick = 1000 * 60;
			break;
		case SC_SUFFRAGIUM:			/* �T�t���M�� */
			tick = 1000 * (40 - val1 * 10);
			break;
		case SC_ASPERSIO:			/* �A�X�y���V�I */
			tick = 1000 * (30 + val1 * 30);
			if( sc_data[SC_ENCPOISON].timer!=-1 )	/* EP���� */
				skill_status_change_end(bl,SC_ENCPOISON,-1);
			break;
		case SC_BENEDICTIO:			/* ���� */
			tick = 1000 * 40 * val1;
			break;
		case SC_KYRIE:				/* �L���G�G���C�\�� */
			tick = 1000 * 120;
			val2 = ((sd)?sd->status.max_hp:mob_db[md->class].max_hp) *
				 (val1 * 2 + 10) / 100;/* �ϋv�x */
			val1 = (val1 / 2 + 5);	/* �� */
			break;
		case SC_MAGNIFICAT:			/* �}�O�j�t�B�J�[�g */
			tick = 1000 * 20 * val1;
			break;
		case SC_GLORIA:				/* �O�����A */
			tick = 1000 * (5 + val1 * 5);
			break;
		case SC_AETERNA:			/* �G�[�e���i */
			tick = 1000 * 600;		/* �Ƃ肠����10���ɂ��Ă݂�i��̓^�C�}�����ŉ�������j */
			break;
		case SC_ENERGYCOAT:			/* �G�i�W�[�R�[�g */
			tick = 1000 * 6 * 50;
			break;
		case SC_LOUD:				/* ���E�h�{�C�X */
			tick = 1000 * 60 * 5;
			break;
		case SC_TRICKDEAD:			/* ���񂾂ӂ� */
			tick = 1000 * 600;		/* �Ƃ肠����10���ɂ��Ă݂�i��̓^�C�}�����ŉ�������j */
			break;
		case SC_QUAGMIRE:			/* �N�@�O�}�C�A */
			tick = 5000 * val1;
			break;
		case SC_SIGNUMCRUCIS:		/* �V�O�i���N���V�X */
			tick = 5000 * 60 * 25;
			break;
		case SC_FLAMELAUNCHER:		/* �t���[�������`���[ */
			tick = 1000 * (15 + val1 * 15);
			break;
		case SC_FROSTWEAPON:		/* �t���X�g�E�F�|�� */
			tick = 1000 * (15 + val1 * 15);
			break;
		case SC_LIGHTNINGLOADER:	/* ���C�g�j���O���[�_�[ */
			tick = 1000 * (15 + val1 * 15);
			break;
		case SC_SEISMICWEAPON:		/* �T�C�Y�~�b�N�E�F�|�� */
			tick = 1000 * (15 + val1 * 15);
			break;
		case SC_PROVIDENCE:			/* �v�����B�f���X */
			tick = 1000 * 180;
			val2=val1*5;
			break;
		case SC_DEFENDER:			/* �f�B�t�F���_�[ */
			tick = 1000 * 180;
			val2=val1*15+5;
			break;
		case SC_SPEARSQUICKEN:		/* �X�s�A�N�C�b�P�� */
			tick = 1000 * 300;
			val2=80-val1;
			break;
		case SC_ASSNCROS:			/* �[�z�̃A�T�V���N���X */
			tick = 1000 * 120;
			val2=90-val1;
			break;
		case SC_WHISTLE:			/* ���J */
			tick = 1000 * 60;
			break;
		case SC_APPLEIDUN:			/* �C�h�D���̗ь� */
			tick = 1000 * 60 * 3;
			val2 = val1*2+5;
			break;
		case SC_SERVICE4U:			/* �T�[�r�X�t�H�[���[ */
			tick = 1000 * 60 * 3;
			val2 = val1+10;
			break;
		case SC_HUMMING:			/* �n�~���O */
			tick = 1000 * 60;
			val2 = val1*2;
			break;
		case SC_DONTFORGETME:		/* ����Y��Ȃ��� */
			tick = 1000 * 180;
			val2 = 100+val1*3;
			val3 = 100+val1*2;
			break;
		case SC_FORTUNE:			/* �K�^�̃L�X */
			tick = 1000 * 60 * 2;
			break;
		case SC_DRUMBATTLE:			/* �푾�ۂ̋��� */
			tick = 1000 * 60;
			val2 = (val1+1)*25;
			val3 = (val1+1)*2;
			break;
		case SC_ETERNALCHAOS:		/* �G�^�[�i���J�I�X */
			tick = 1000* 60;
			break;
		case SC_NIBELUNGEN:			/* �j�[�x�����O�̎w�� */
			tick = 1000 * 60;
			val2 = (val1+2)*50;
			break;
		case SC_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
			tick = 1000 * 60;
			val2 = (val1+3)*10;
			break;
		case SC_EXPLOSIONSPIRITS:	// �����g��
			tick = 1000 * 60 * 3;
			val2 = 75 + 25*val1;
			break;
		case SC_STEELBODY:			// ����
			tick = 1000 * 30 * val1;
			break;

		/* option1 */
		case SC_SPEEDPOTION0:		/* �����|�[�V���� */
		case SC_SPEEDPOTION1:
		case SC_SPEEDPOTION2:
			tick = 1000 * 60 * 30;
			val2 = 100- 5*(2+type-SC_SPEEDPOTION0);
			break;

		case SC_STONE:				/* �Ή� */
			if( (tick=val2)<=0 )
				tick = 1000 * 600;		/* �Ƃ肠����10���ɂ��Ă݂�i��̓^�C�}�����ŉ�������j */
			break;
		case SC_SLEEP:				/* ���� */
			tick = val2;
			break;
		case SC_FREEZE:				/* ���� */
			if( (tick=val2)<=0 )
				tick = 1000 * 3 * val1;
			break;
		case SC_STAN:				/* �X�^���ival2�Ƀ~���b�Z�b�g�j */
			tick = val2;
			break;

		/* option2 */
		case SC_POISON:				/* �� */
			if( (tick=val2)<=0 )
				tick = 1000 * (10 + rand()%50);	/* �K���Ȓ��� */
			break;
		case SC_SILENCE:			/* ���فi���b�N�X�f�r�[�i�j */
			if( (tick=val2)<=0 )
				tick = 1000 * ( (val1>6)?60: 25 + val1 * 5);
			break;
		case SC_BLIND:				/* �Í� */
			if( (tick=val2)<=0 )
				tick = 1000*600;
			break;
			
		/* option */
		case SC_HIDDING:		/* �n�C�f�B���O */
			tick = 1000;			/* �P�b�����ԃ`�F�b�N */
			val2 = 30 * val1;		/* �������� */
			break;
		case SC_CLOAKING:		/* �N���[�L���O */
			tick = 1000 * (3 + val1 );	/* SP��1���鎞��(val2�ɂ��Z�b�g) */
			val2 = tick;
			break;
		case SC_SIGHT:			/* �T�C�g/���A�t */
		case SC_RUWACH:
			tick=10;
			val2=40;	/* 250*40=10�b */
			break;

		/* �Z�[�t�e�B�E�H�[���A�j���[�} */
		case SC_SAFETYWALL:	case SC_PNEUMA:
			tick=((struct skill_unit *)val2)->group->limit;
			break;

		/* �A���N�� */
		case SC_ANKLE:
			tick=val2;
			break;

		/* �E�H�[�^�[�{�[�� */
		case SC_WATERBALL:
			tick=100;
			val3= (val1|1)*(val1|1)-1;
			break;

		/* �X�L������Ȃ�/���ԂɊ֌W���Ȃ� */
		case SC_RIDING:	case SC_FALCON:	case SC_WEIGHT50:	case SC_WEIGHT90:
			tick=600*1000;
			break;

		default:
			printf("UnknownStatusChange [%d]\n", type);
			return 0;
	}

	if(bl->type==BL_PC && type<64)	/* �A�C�R���\���p�P�b�g */
		clif_status_change(bl,type,1);

	/* option�̕ύX */
	switch(type){
		case SC_STONE:	case SC_FREEZE:	case SC_STAN:	case SC_SLEEP:
			battle_stopattack(bl);	/* �U����~ */
			{
				/* �����Ɋ|����Ȃ��X�e�[�^�X�ُ������ */
				int i;
				for(i = SC_STONE; i <= SC_SLEEP; i++){
					if(sc_data[i].timer != -1){
						(*sc_count)--;
						delete_timer(sc_data[i].timer, skill_status_change_timer);
						sc_data[i].timer = -1;
					}
				}
			}
			*opt1 = type - SC_STONE + 1;
			opt_flag = 1;
			break;
		case SC_POISON:	case SC_CURSE:	case SC_SILENCE:	case SC_BLIND:
			*opt2|= 1<<(type-SC_POISON);
			opt_flag = 1;
			break;
		case SC_HIDDING:	case SC_CLOAKING:
			battle_stopattack(bl);	/* �U����~ */
			*option|= ((type==SC_HIDDING)?2:4);
			opt_flag =1 ;
			break;
		case SC_SIGHT:	case SC_RUWACH:
			*option|=1;
			opt_flag=1;
			break;
	}

	if(opt_flag)	/* option�̕ύX */
		clif_changeoption(bl);

	(*sc_count)++;	/* �X�e�[�^�X�ُ�̐� */

	sc_data[type].val1 = val1;
	sc_data[type].val2 = val2;
	sc_data[type].val3 = val3;
	sc_data[type].val4 = val4;
	/* �^�C�}�[�ݒ� */
	sc_data[type].timer = add_timer(
		gettick() + tick, skill_status_change_timer, bl->id, type);

	if(bl->type==BL_PC)
		pc_calcstatus(sd,0);	/* �X�e�[�^�X�Čv�Z */

	return 0;
}
/*==========================================
 * �X�e�[�^�X�ُ�S����
 *------------------------------------------
 */
int skill_status_change_clear(struct block_list *bl)
{
	struct status_change* sc_data;
	short *sc_count, *option, *opt1, *opt2;
	int i;
	
	sc_data=battle_get_sc_data(bl);
	sc_count=battle_get_sc_count(bl);
	option=battle_get_option(bl);
	opt1=battle_get_opt1(bl);
	opt2=battle_get_opt2(bl);
	
	if(*sc_count == 0)
		return 0;
	for(i = 0; i < MAX_STATUSCHANGE; i++){
		if(sc_data[i].timer != -1){	/* �ُ킪����Ȃ�^�C�}�[���폜���� */
			delete_timer(sc_data[i].timer, skill_status_change_timer);
			sc_data[i].timer = -1;
			if( bl->type==BL_PC && i<64 )
				clif_status_change(bl,i,0);
		}
	}
	*sc_count = 0;
	*opt1 = 0;
	*opt2 = 0;
	*option &= 0xfff8;

	if( bl->type==BL_PC )
		clif_changeoption(bl);

	return 0;
}


/* �N���[�L���O�����i����Ɉړ��s�\�n�т����邩�j */
int skill_check_cloaking(struct block_list *bl)
{
	static int dx[]={-1, 0, 1,-1, 1,-1, 0, 1};
	static int dy[]={-1,-1,-1, 0, 0, 1, 1, 1};
	int end=1,i;
	for(i=0;i<sizeof(dx)/sizeof(dx[0]);i++){
		int c=map_getcell(bl->m,bl->x+dx[i],bl->y+dy[i]);
		if(c==1 || c==5) end=0;
	}
	if(end){
		skill_status_change_end(bl, SC_CLOAKING, -1);
		*battle_get_option(bl)&=~4;	/* �O�̂��߂̏��� */
	}
	return end;
}





/*
 *----------------------------------------------------------------------------
 * �X�L�����j�b�g
 *----------------------------------------------------------------------------
 */


/*==========================================
 * �X�L�����j�b�g������
 *------------------------------------------
 */
struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y)
{
	struct skill_unit *unit=&group->unit[idx];
	
	if(!unit->alive)
		group->alive_count++;
	
	unit->bl.id=map_addobject(&unit->bl);
	unit->bl.type=BL_SKILL;
	unit->bl.m=group->map;
	unit->bl.x=x;
	unit->bl.y=y;
	unit->group=group;
	unit->val1=unit->val2=0;
	unit->alive=1;

	map_addblock(&unit->bl);
	clif_skill_setunit(unit);
	return unit;
}

int skill_unit_timer_sub_ondelete( struct block_list *bl, va_list ap );
/*==========================================
 * �X�L�����j�b�g�폜
 *------------------------------------------
 */
int skill_delunit(struct skill_unit *unit)
{
	struct skill_unit_group *group=unit->group;
	int range;
/*	printf("delunit %d\n",unit->bl.id); */

	if(!unit->alive || group==NULL)
		return 0;

	/* onlimit�C�x���g�Ăяo�� */
	skill_unit_onlimit( unit,gettick() );

	/* ondelete�C�x���g�Ăяo�� */
	range=unit->group->range;
	map_foreachinarea( skill_unit_timer_sub_ondelete, unit->bl.m,
		unit->bl.x-range,unit->bl.y-range,unit->bl.x+range,unit->bl.y+range,0,
		&unit->bl,gettick() );

	clif_skill_delunit(unit);
	
	
	unit->group=NULL;
	unit->alive=0;
	map_delobjectnofree(unit->bl.id);
	if(group->alive_count>0 && (--group->alive_count)<=0)
		skill_delunitgroup(group);
	
	return 0;
}
/*==========================================
 * �X�L�����j�b�g�O���[�v������
 *------------------------------------------
 */
static int skill_unit_group_newid=10;
struct skill_unit_group *skill_initunitgroup(struct block_list *src,
	int count,int skillid,int skilllv,int unit_id)
{
	int i;
	struct skill_unit_group *group=NULL, *list=NULL;
	int maxsug=0;
	
	if(src->type==BL_PC){
		list=((struct map_session_data *)src)->skillunit;
		maxsug=MAX_SKILLUNITGROUP;
	}else if(src->type==BL_MOB){
		list=((struct mob_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	}
	if(list){
		for(i=0;i<maxsug;i++)	/* �󂢂Ă�����̌��� */
			if(list[i].group_id==0){
				group=&list[i];
				break;
			}

		if(group==NULL){	/* �󂢂ĂȂ��̂ŌÂ����̌��� */
			int j=0;
			unsigned maxdiff=0,x,tick=gettick();
			for(i=0;i<maxsug;i++)
				if((x=DIFF_TICK(tick,list[i].tick))>maxdiff){
					maxdiff=x;
					j=i;
				}
			skill_delunitgroup(&list[j]);
			group=&list[j];
		}
	}

	if(group==NULL){
		printf("skill_initunitgroup: error unit group !\n");
		exit(0);
	}

	group->src_id=src->id;
	group->party_id=battle_get_party_id(src);
	group->guild_id=battle_get_guild_id(src);
	group->group_id=skill_unit_group_newid++;
	if(skill_unit_group_newid<=0)
		skill_unit_group_newid=10;

	group->unit=malloc(sizeof(struct skill_unit)*count);
	if(group->unit==NULL){
		printf("skill_initunitgroup: out of memory! \n");
		exit(0);
	}
	memset(group->unit,0,sizeof(struct skill_unit)*count);

	group->unit_count=count;
	group->val1=group->val2=0;
	group->skill_id=skillid;
	group->skill_lv=skilllv;
	group->unit_id=unit_id;
	group->map=src->m;
	group->range=0;
	group->limit=10000;
	group->interval=1000;
	group->tick=gettick();
	memset(group->vallist,0,sizeof(group->vallist));
	group->valstr=NULL;

	return group;
}


/*==========================================
 * �X�L�����j�b�g�O���[�v�폜
 *------------------------------------------
 */
int skill_delunitgroup(struct skill_unit_group *group)
{
	int i;
	if(group->unit_count<=0)
		return 0;

/*	printf("delunitgroup %d\n",group->group_id); */

	group->alive_count=-1;
	if(group->unit!=NULL){
		for(i=0;i<group->unit_count;i++)
			if(group->unit[i].alive)
				skill_delunit(&group->unit[i]);
	}
	if(group->valstr!=NULL){
		map_freeblock(group->valstr);
		group->valstr=NULL;
	}
	
	map_freeblock(group->unit);	/* free()�̑ւ�� */
	group->unit=NULL;
	group->src_id=0;
	group->group_id=0;
	group->unit_count=0;
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�O���[�v�S�폜
 *------------------------------------------
 */
int skill_clear_unitgroup(struct block_list *src)
{
	struct skill_unit_group *group=NULL;
	int maxsug=0;
	if(src->type==BL_PC){
		group=((struct map_session_data *)src)->skillunit;
		maxsug=MAX_SKILLUNITGROUP;
	}else if(src->type==BL_MOB){
		group=((struct mob_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	}
	if(group){
		int i;
		for(i=0;i<maxsug;i++)
			if(group[i].group_id>0)
				skill_delunitgroup(&group[i]);
	}
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�O���[�v�̔�e��tick����
 *------------------------------------------
 */
struct skill_unit_group_tickset *skill_unitgrouptickset_search(
	struct block_list *bl,int group_id)
{
	int i,j=0,k,s=group_id%MAX_SKILLUNITGROUPTICKSET;
	struct skill_unit_group_tickset *set=NULL;
	if(bl->type==BL_PC){
		set=((struct map_session_data *)bl)->skillunittick;
	}else{
		set=((struct mob_data *)bl)->skillunittick;
	}
	if(set==NULL)
		return 0;
	for(i=0;i<MAX_SKILLUNITGROUPTICKSET;i++)
		if( set[(k=(i+s)%MAX_SKILLUNITGROUPTICKSET)].group_id == group_id )
			return &set[k];
		else if( set[k].group_id==0 )
			j=k;

	return &set[j];
}


/*==========================================
 * �X�L�����j�b�g�O���[�v�̔�e��tick�폜
 *------------------------------------------
 */
int skill_unitgrouptickset_delete(struct block_list *bl,int group_id)
{
	int i,s=group_id%MAX_SKILLUNITGROUPTICKSET;
	struct skill_unit_group_tickset *set=NULL,*ts;
	if(bl->type==BL_PC){
		set=((struct map_session_data *)bl)->skillunittick;
	}else{
		set=((struct mob_data *)bl)->skillunittick;
	}
	
	if(set!=NULL){
	
		for(i=0;i<MAX_SKILLUNITGROUPTICKSET;i++)
			if( (ts=&set[(i+s)%MAX_SKILLUNITGROUPTICKSET])->group_id == group_id )
				ts->group_id=0;

	}
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�^�C�}�[���������p(foreachinarea)
 *------------------------------------------
 */
int skill_unit_timer_sub_onplace( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	unsigned int tick;
	src=va_arg(ap,struct block_list*);
	tick=va_arg(ap,unsigned int);


	if( ((struct skill_unit *)src)->alive &&
		battle_check_target(src,bl,((struct skill_unit *)src)->group->target_flag )>0 )
			skill_unit_onplace( (struct skill_unit *)src, bl, tick );
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�^�C�}�[�폜�����p(foreachinarea)
 *------------------------------------------
 */
int skill_unit_timer_sub_ondelete( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	unsigned int tick;
	src=va_arg(ap,struct block_list*);
	tick=va_arg(ap,unsigned int);

	if( ((struct skill_unit *)src)->alive &&
		battle_check_target(src,bl,((struct skill_unit *)src)->group->target_flag )>0 )
			skill_unit_ondelete( (struct skill_unit *)src, bl, tick );
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�^�C�}�[�����p(foreachobject)
 *------------------------------------------
 */
int skill_unit_timer_sub( struct block_list *bl, va_list ap )
{
	struct skill_unit *unit=(struct skill_unit *)bl;
	struct skill_unit_group *group;
	int range;
	unsigned int tick;
	tick=va_arg(ap,unsigned int);

	if(!unit->alive)
		return 0;

	group=unit->group;
	range=(unit->range!=0)?unit->range:group->range;

	/* onplace�C�x���g�Ăяo�� */
	if(unit->alive && unit->range>=0)
		map_foreachinarea( skill_unit_timer_sub_onplace, bl->m,
			bl->x-range,bl->y-range,bl->x+range,bl->y+range,0,
			bl,tick );

	/* ���Ԑ؂�폜 */
	if(unit->alive &&
		(DIFF_TICK(tick,group->tick)>=group->limit ||
		 DIFF_TICK(tick,group->tick)>=unit->limit) ){
		skill_delunit(unit);
	}

	return 0;
}


/*==========================================
 * �X�L�����j�b�g�^�C�}�[����
 *------------------------------------------
 */
int skill_unit_timer( int tid,unsigned int tick,int id,int data)
{
	map_foreachobject( skill_unit_timer_sub, BL_SKILL, tick );
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�ړ��������p(foreachinarea)
 *------------------------------------------
 */
int skill_unit_move_sub( struct block_list *bl, va_list ap )
{
	struct skill_unit *unit=(struct skill_unit *)bl;
	struct skill_unit_group *group;
	struct block_list *src;
	int range;
	unsigned int tick;
	src=va_arg(ap,struct block_list*);
	tick=va_arg(ap,unsigned int);

	if(!unit->alive || src->prev==NULL)
		return 0;

	group=unit->group;
	range=(unit->range!=0)?unit->range:group->range;

	if( range<0 || battle_check_target(bl,src,group->target_flag )<=0 )
		return 0;

	if( src->x >= bl->x-range && src->x <= bl->x+range &&
		src->y >= bl->y-range && src->y <= bl->y+range )
		skill_unit_onplace( unit, src, tick );
	else
		skill_unit_onout( unit, src, tick );

	return 0;
}


/*==========================================
 * �X�L�����j�b�g�ړ�������
 *------------------------------------------
 */
int skill_unit_move( struct block_list *bl,unsigned int tick,int range)
{
	if(bl->prev==NULL)
		return 0;

	if(range<5)range=5;
	map_foreachinarea( skill_unit_move_sub,
		bl->m,bl->x-range,bl->y-range,bl->x+range,bl->y+range,BL_SKILL,
		bl,tick );

	return 0;
}


/*----------------------------------------------------------------------------
 * �A�C�e������
 *----------------------------------------------------------------------------
 */

/*==========================================
 * �A�C�e�������\����
 *------------------------------------------
 */
int skill_can_produce_mix( struct map_session_data *sd, int nameid, int trigger )
{
	int i,j,equip;

	if(nameid<=0)
		return 0;

	for(i=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if(skill_produce_db[i].nameid == nameid )
			break;
	}
	if( i == MAX_SKILL_PRODUCE_DB )	/* �f�[�^�x�[�X�ɂȂ� */
		return 0;

	if(trigger>=0){
		equip = itemdb_isequip(nameid);
		if(trigger==16){
			if(equip)	/* �n�z�F������͂��� */
				return 0;
		}else{
			if(!equip)		/* �ȁ��S�z�n�͂��� */
				return 0;
			if( itemdb_wlv(nameid) > trigger )	/* ����Lv���� */
				return 0;
		}
	}
	if( (j=skill_produce_db[i].req_skill)>0 && pc_checkskill(sd,j)<=0 )
		return 0;		/* �X�L��������Ȃ� */

	for(j=0;j<5;j++){
		int id,x,y;
		if( (id=skill_produce_db[i].mat_id[j])==0 )	/* ����ȏ�͍ޗ��v��Ȃ� */
			break;
		for(y=0,x=0;y<MAX_INVENTORY;y++)
			if( sd->status.inventory[y].nameid == id )
				x+=sd->status.inventory[y].amount;
		if(x<skill_produce_db[i].mat_amount[j])	/* �A�C�e��������Ȃ� */
			return 0;
	}
	return i+1;
}


/*==========================================
 * �A�C�e�������\����
 *------------------------------------------
 */
int skill_produce_mix( struct map_session_data *sd,
	int nameid, int slot1, int slot2, int slot3 )
{
	int slot[3];
	int i,sc,ele,idx,equip,wlv,make_per;

	if( !(idx=skill_can_produce_mix(sd,nameid,-1)) )	/* �����s�� */
		return 0;
	idx--;
	slot[0]=slot1;
	slot[1]=slot2;
	slot[2]=slot3;

	/* ���ߍ��ݏ��� */
	for(i=0,sc=0,ele=0;i<3;i++){
		int j;
		if( slot[i]<=0 )
			continue;
		j = pc_search_inventory(sd,slot[i]);
		if(j < 0)	/* �s���p�P�b�g(�A�C�e������)�`�F�b�N */
			continue;
		if(slot[i]==1000){	/* ���̂����� */
			pc_delitem(sd,j,1,1);
			sc++;
		}
		if(slot[i]>=994 && slot[i]<=997 && ele==0){	/* ������ */
			static const int ele_table[4]={3,1,4,2};
			pc_delitem(sd,j,1,1);
			ele=ele_table[slot[i]-994];
		}
	}

	/* �ޗ����� */
	for(i=0;i<5;i++){
		int j,id,x;
		if( (id=skill_produce_db[idx].mat_id[i])<=0 )
			break;
		x=skill_produce_db[idx].mat_amount[i];	/* �K�v�Ȍ� */
		do{	/* �Q�ȏ�̃C���f�b�N�X�ɂ܂������Ă��邩������Ȃ� */
			int y=0;
			j = pc_search_inventory(sd,id);
			
			if(j >= 0){
				y = sd->status.inventory[j].amount;
				if(y>x)y=x;	/* ����Ă��� */
				pc_delitem(sd,j,y,0);
			}else
				printf("skill_produce_mix: material item error\n");

			x-=y;	/* �܂�����Ȃ������v�Z */
		}while( j>=0 && x>0 );	/* �ޗ�������邩�A�G���[�ɂȂ�܂ŌJ��Ԃ� */
	}

	/* �m������ */
	equip = itemdb_isequip(nameid);
	if(!equip) {
		if(nameid == 998)
			make_per = 2000 + sd->status.base_level*30 + sd->paramc[4]*20 + sd->paramc[5]*10 + pc_checkskill(sd,skill_produce_db[idx].req_skill)*600;
		else if(nameid == 985)
			make_per = 1000 + sd->status.base_level*30 + sd->paramc[4]*20 + sd->paramc[5]*10 + (pc_checkskill(sd,skill_produce_db[idx].req_skill)-1)*500;
		else
			make_per = 1000 + sd->status.base_level*30 + sd->paramc[4]*20 + sd->paramc[5]*10 + pc_checkskill(sd,skill_produce_db[idx].req_skill)*500;
	}
	else {
		int add_per;
		if(pc_search_inventory(sd,989) >= 0) add_per = 750;
		else if(pc_search_inventory(sd,988) >= 0) add_per = 500;
		else if(pc_search_inventory(sd,987) >= 0) add_per = 250;
		else if(pc_search_inventory(sd,986) >= 0) add_per = 0;
		else add_per = -500;
		if(ele) add_per -= 500;
		add_per -= sc*500;
		wlv = itemdb_wlv(nameid);
		make_per = ((250 + sd->status.base_level*15 + sd->paramc[4]*10 + sd->paramc[5]*5 + pc_checkskill(sd,skill_produce_db[idx].req_skill)*500 +
			add_per) * (100 - (wlv - 1)*20))/100 + pc_checkskill(sd,107)*100 + ((wlv >= 3)? pc_checkskill(sd,97)*100 : 0);
	}

	if( battle_config.wp_rate!=100 )	/* �m���␳ */
		make_per=make_per*battle_config.wp_rate/100;

	if(make_per < 10) make_per = 10;
	/* debug code */
	/*printf("make success percent = %.2lf\n",(double)make_per/100.); */
	
	if(rand()%10000 < make_per){
		/* ���� */
		struct item tmp_item;
		memset(&tmp_item,0,sizeof(tmp_item));
		tmp_item.nameid=nameid;
		tmp_item.amount=1;
		tmp_item.identify=1;
		if(equip){	/* ����̏ꍇ */
			tmp_item.card[0]=0x00ff; /* ��������t���O */
			tmp_item.card[1]=((sc*5)<<8)+ele;	/* �����Ƃ悳 */
			*((unsigned long *)(&tmp_item.card[2]))=sd->char_id;	/* �L����ID */
		}
		clif_produceeffect(sd,0,nameid);/* �����G�t�F�N�g�p�P�b�g */
		clif_misceffect(&sd->bl,3); /* ���l�ɂ�������ʒm�i���B�����G�t�F�N�g�Ɠ����ł����́H�j */
		if(pc_additem(sd,&tmp_item,1))
			map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y);
	}
	else {
		/* ���s */
		clif_produceeffect(sd,1,nameid);/* �����G�t�F�N�g�p�P�b�g */
		clif_misceffect(&sd->bl,2); /* ���l�ɂ����s��ʒm */
	}
	return 0;
}


/*----------------------------------------------------------------------------
 * �������n
 */

/*==========================================
 * �X�L���֌W�t�@�C���ǂݍ���
 * skill_db.txt �X�L���f�[�^
 * cast_db.txt �X�L���̉r�����Ԃƃf�B���C�f�[�^
 * produce_db.txt �A�C�e���쐬�X�L���p�f�[�^
 *------------------------------------------
 */
int skill_readdb(void)
{
	int i,j,k;
	FILE *fp;
	char line[1024],*p;

	/* �X�L���f�[�^�x�[�X */
	memset(skill_db,0,sizeof(skill_db));
	fp=fopen("db/skill_db.txt","r");
	if(fp==NULL){
		printf("can't read db/skill_db.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)){
		char *split[50], *split2[16];
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<10 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[9]==NULL || j<10)
			continue;

		i=atoi(split[0]);
		if(i<0 || i>MAX_SKILL_DB)
			continue;

/*		printf("skill id=%d\n",i); */
		skill_db[i].range=atoi(split[1]);
		skill_db[i].hit=atoi(split[2]);
		skill_db[i].inf=atoi(split[3]);
		skill_db[i].pl=atoi(split[4]);
		skill_db[i].nk=atoi(split[5]);
		skill_db[i].max=atoi(split[6]);

		memset(split2,0,sizeof(split2));
		for(j=0,p=split[7];j<10 && p;j++){
			split2[j]=p;
			p=strchr(p,':');
			if(p) *p++=0;
		}
		for(k=0;k<10;k++)
			skill_db[i].sp[k]=(split2[k]?atoi(split2[k]):atoi(split2[0]));

		memset(split2,0,sizeof(split2));
		for(j=0,p=split[8];j<10 && p;j++){
			split2[j]=p;
			p=strchr(p,':');
			if(p) *p++=0;
		}
		for(k=0;k<10;k++)
			skill_db[i].num[k]=(split2[k]?atoi(split2[k]):atoi(split2[0]));
		
		skill_db[i].inf2=atoi(split[9]);

	}
	fclose(fp);
	printf("read db/skill_db.txt done\n");

	/* �L���X�e�B���O�f�[�^�x�[�X */
/*	for(i=0;i<MAX_SKILL;i++){
		for(j=0;j<10;j++){
			skill_db[i].cast[j]=1000;
			skill_db[i].delay[j]=1000;
		}
	}*/
	fp=fopen("db/cast_db.txt","r");
	if(fp==NULL){
		printf("can't read db/cast_db.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)){
		char *split[50], *split2[16];
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<3 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[2]==NULL || j<3)
			continue;

		i=atoi(split[0]);
		if(i<0 || i>MAX_SKILL_DB)
			continue;

		memset(split2,0,sizeof(split2));
		for(j=0,p=split[1];j<10 && p;j++){
			split2[j]=p;
			p=strchr(p,':');
			if(p) *p++=0;
		}
		for(k=0;k<10;k++)
			skill_db[i].cast[k]=(split2[k]?atoi(split2[k]):atoi(split2[0]));

		memset(split2,0,sizeof(split2));
		for(j=0,p=split[2];j<10 && p;j++){
			split2[j]=p;
			p=strchr(p,':');
			if(p) *p++=0;
		}
		for(k=0;k<10;k++)
			skill_db[i].delay[k]=(split2[k]?atoi(split2[k]):atoi(split2[0]));
	}
	fclose(fp);
	printf("read db/cast_db.txt done\n");

	memset(skill_produce_db,0,sizeof(skill_produce_db));
	fp=fopen("db/produce_db.txt","r");
	if(fp==NULL){
		printf("can't read db/produce_db.txt\n");
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[16];
		int x,y;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;

		skill_produce_db[k].nameid=i;
		skill_produce_db[k].req_skill=atoi(split[2]);

		for(x=3,y=0;split[x] && split[x+1] && y<5;x+=2,y++){
			skill_produce_db[k].mat_id[y]=atoi(split[x]);
			skill_produce_db[k].mat_amount[y]=atoi(split[x+1]);
		}
		k++;
		if(k >= MAX_SKILL_PRODUCE_DB)
			break;
	}
	fclose(fp);
	printf("read db/produce_db.txt done (count=%d)\n",k);

	return 0;
}


/*==========================================
 * �X�L���֌W����������
 *------------------------------------------
 */
int do_init_skill(void)
{
	skill_readdb();

	add_timer_interval(gettick()+1000,skill_unit_timer,0,0,SKILLUNITTIMER_INVERVAL);
	add_timer_func_list(skill_unit_timer,"skill_unit_timer");

	return 0;
}

