#ifndef _SKILL_H_
#define _SKILL_H_

#define MAX_SKILL_DB			350
#define MAX_SKILL_PRODUCE_DB	 100

// �X�L���f�[�^�x�[�X
struct skill_db {
	int range,hit,inf,pl,nk,max;
	int sp[10],num[10];
	int cast[10],delay[10];
	int inf2;
};
extern struct skill_db skill_db[MAX_SKILL_DB];

// �A�C�e���쐬�f�[�^�x�[�X
struct skill_produce_db {
	int nameid, trigger;
	int req_skill,itemlv;
	int mat_id[5],mat_amount[5];
};
extern struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

struct block_list;
struct map_session_data;
struct skill_unit;
struct skill_unit_group;

int do_init_skill(void);

// �X�L���f�[�^�x�[�X�ւ̃A�N�Z�T
int skill_get_range( int id );
int	skill_get_hit( int id );
int	skill_get_inf( int id );
int	skill_get_pl( int id );
int	skill_get_nk( int id );
int	skill_get_max( int id );
int	skill_get_sp( int id ,int lv );
int	skill_get_num( int id ,int lv );
int	skill_get_cast( int id ,int lv );
int	skill_get_delay( int id ,int lv );
int skill_get_unit_id(int id,int flag);
int	skill_get_inf2( int id );

// �X�L���̎g�p
int skill_use_id( struct map_session_data *sd, int target_id,
	int skill_num,int skill_lv);
int skill_use_pos( struct map_session_data *sd,
	int skill_x, int skill_y, int skill_num, int skill_lv);

int skill_castend_map( struct map_session_data *sd,int skill_num, const char *map);

// �ǉ�����
int skill_additional_effect( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick);

// ���j�b�g�X�L��
struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y);
int skill_delunit(struct skill_unit *unit);
struct skill_unit_group *skill_initunitgroup(struct block_list *src,
	int count,int skillid,int skilllv,int unit_id);
int skill_delunitgroup(struct skill_unit_group *group);
struct skill_unit_group_tickset *skill_unitgrouptickset_search(
	struct block_list *bl,int group_id);
int skill_unitgrouptickset_delete(struct block_list *bl,int group_id);
int skill_clear_unitgroup(struct block_list *src);

int skill_unit_ondamaged(struct skill_unit *src,struct block_list *bl,
	int damage,unsigned int tick);

int skill_unit_move( struct block_list *bl,unsigned int tick,int range);

// �r���L�����Z��
int skill_castcancel( struct block_list *sd );

#define skill_calc_heal(bl,skill_lv)	\
	(( battle_get_lv(bl)+battle_get_int(bl) )/8 *(4+ skill_lv*8))

// ���̑�
int skill_check_cloaking(struct block_list *bl);

// �X�e�[�^�X�ُ�
int skill_status_change_start(struct block_list *bl,int type,int val1,int val2);
int skill_status_change_timer(int tid, unsigned int tick, int id, int data);
int skill_status_change_end( struct block_list* bl , int type,int tid );
int skill_status_change_clear(struct block_list *bl);


// �A�C�e���쐬
int skill_can_produce_mix( struct map_session_data *sd, int nameid, int trigger );
int skill_produce_mix( struct map_session_data *sd,
	int nameid, int slot1, int slot2, int slot3 );

// mob�X�L���̂���
int skill_castend_nodamage_id( struct block_list *src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );
int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );
int skill_castend_pos2( struct block_list *src, int x,int y,int skillid,int skilllv,unsigned int tick,int flag);

// �X�L���U���ꊇ����
int skill_attack( int attack_type, struct block_list* src, struct block_list *dsrc,
	 struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );


enum {	// struct map_session_data �� status_change�̔ԍ��e�[�u��
// 64�����N���C�A���g�ւ̒ʒm����A64�ȏ�ʒm�����B�ԍ��̕ύX�\������
// 2-2���E�̒l�͂Ȃ񂩂߂��Ⴍ������ۂ��̂Ŏb��B���Ԃ�ύX����܂��B

	SC_STONE				=64,
	SC_FREEZE				=65,
	SC_STAN					=66,
	SC_SLEEP				=67,
	SC_POISON				=68,
	SC_CURSE				=69,
	SC_SILENCE				=70,
	SC_CONFUSION			=71,
	SC_BLIND				=72,
	
	SC_TRICKDEAD			=29,
	SC_PROVOKE				= 0,
	SC_ENDURE				= 1,
	SC_SIGHT				=75,
	SC_ENERGYCOAT			=31,
	SC_CONCENTRATE			= 3,
	SC_HIDDING				= 4,
	SC_LOUD					=30,
	SC_RUWACH				=76,
	SC_INCREASEAGI			=12,
	SC_DECREASEAGI			=13,
	SC_SIGNUMCRUCIS			=11,
	SC_ANGELUS				= 9,
	SC_BLESSING				=10,
	SC_TWOHANDQUICKEN		= 2,
	SC_AUTOCOUNTER			=77,
	SC_IMPOSITIO			=15,
	SC_SUFFRAGIUM			=16,
	SC_ASPERSIO				=17,
	SC_BENEDICTIO			=18,
	SC_KYRIE				=19,
	SC_MAGNIFICAT			=20,
	SC_GLORIA				=21,
	SC_DIVINA				= SC_SILENCE,
	SC_AETERNA				=22,
	SC_QUAGMIRE				= 8,
	SC_ADRENALINE			=23,
	SC_WEAPONPERFECTION		=24,
	SC_OVERTHRUST			=25,
	SC_MAXIMIZEPOWER		=26,
	SC_CLOAKING				= 5,
	SC_ENCPOISON			= 6,
	SC_POISONREACT			= 7,
	SC_FLAMELAUNCHER		=98,
	SC_FROSTWEAPON			=95,
	SC_LIGHTNINGLOADER		=96,
	SC_SEISMICWEAPON		=97,
	SC_ASSNCROS				=100,
	SC_POEMBRAGI			=101,
	SC_FREECAST				=102,
	SC_STRIPWEAPON			=50,
	SC_STRIPSHIELD			=51,
	SC_STRIPARMOR			=52,
	SC_STRIPHELM			=53,
	SC_CP_WEAPON			=54,
	SC_CP_SHIELD			=55,
	SC_CP_ARMOR				=56,
	SC_CP_HELM				=57,
	SC_AUTOGUARD			=58,
	SC_REFLECTSHIELD		=59,
	SC_PROVIDENCE			=61,
	SC_DEFENDER				=62,
	SC_DEVOTION				=60,
	SC_SPEARSQUICKEN		=99,
	SC_DRUMBATTLE			=78,
	SC_SIEGFRIED			=79,
	SC_WHISTLE				=80,
	SC_APPLEIDUN			=81,
	SC_FORTUNE				=82,
	SC_SERVICE4U			=83,
	SC_NIBELUNGEN			=103,
	SC_HUMMING				=104,
	SC_ETERNALCHAOS			=105,
	SC_DONTFORGETME			=106,
	SC_STEELBODY			=84,
	SC_VOLCANO				=85,
	SC_DELUGE				=86,
	SC_CASTCANCEL			=87,
	SC_SPELLBREAKER			=88,
	SC_EXPLOSIONSPIRITS		=89,
	
	SC_RIDING				=27,
	SC_FALCON				=28,
	SC_WEIGHT50				=35,
	SC_WEIGHT90				=36,
	SC_SPEEDPOTION0			=37,
	SC_SPEEDPOTION1			=38,
	SC_SPEEDPOTION2			=39,
	
	SC_SAFETYWALL			=90,
	SC_PNEUMA				=91,
	SC_WATERBALL			=92,
	SC_METEOSTORM			=93,
	SC_ANKLE				=94,
};
extern int SkillStatusChangeTable[];

enum {
	NV_BASIC = 1,

	SM_SWORD,
	SM_TWOHAND,
	SM_RECOVERY,
	SM_BASH,
	SM_PROVOKE,
	SM_MAGNUM,
	SM_ENDURE,

	MG_SRECOVERY,
	MG_SIGHT,
	MG_NAPALMBEAT,
	MG_SAFETYWALL,
	MG_SOULSTRIKE,
	MG_COLDBOLT,
	MG_FROSTDIVER,
	MG_STONECURSE,
	MG_FIREBALL,
	MG_FIREWALL,
	MG_FIREBOLT,
	MG_LIGHTNINGBOLT,
	MG_THUNDERSTORM,

	AL_DP,
	AL_DEMONBANE,
	AL_RUWACH,
	AL_PNEUMA,
	AL_TELEPORT,
	AL_WARP,
	AL_HEAL,
	AL_INCAGI,
	AL_DECAGI,
	AL_HOLYWATER,
	AL_CRUCIS,
	AL_ANGELUS,
	AL_BLESSING,
	AL_CURE,

	MC_INCCARRY,
	MC_DISCOUNT,
	MC_OVERCHARGE,
	MC_PUSHCART,
	MC_IDENTIFY,
	MC_VENDING,
	MC_MAMMONITE,

	AC_OWL,
	AC_VULTURE,
	AC_CONCENTRATION,
	AC_DOUBLE,
	AC_SHOWER,

	TF_DOUBLE,
	TF_MISS,
	TF_STEAL,
	TF_HIDING,
	TF_POISON,
	TF_DETOXIFY,

	ALL_RESURRECTION,

	KN_SPEARMASTERY,
	KN_PIERCE,
	KN_BRANDISHSPEAR,
	KN_SPEARSTAB,
	KN_SPEARBOOMERANG,
	KN_TWOHANDQUICKEN,
	KN_AUTOCOUNTER,
	KN_BOWLINGBASH,
	KN_RIDING,
	KN_CAVALIERMASTERY,

	PR_MACEMASTERY,
	PR_IMPOSITIO,
	PR_SUFFRAGIUM,
	PR_ASPERSIO,
	PR_BENEDICTIO,
	PR_SANCTUARY,
	PR_SLOWPOISON,
	PR_STRECOVERY,
	PR_KYRIE,
	PR_MAGNIFICAT,
	PR_GLORIA,
	PR_LEXDIVINA,
	PR_TURNUNDEAD,
	PR_LEXAETERNA,
	PR_MAGNUS,

	WZ_FIREPILLAR,
	WZ_SIGHTRASHER,
	WZ_FIREIVY,
	WZ_METEOR,
	WZ_JUPITEL,
	WZ_VERMILION,
	WZ_WATERBALL,
	WZ_ICEWALL,
	WZ_FROSTNOVA,
	WZ_STORMGUST,
	WZ_EARTHSPIKE,
	WZ_HEAVENDRIVE,
	WZ_QUAGMIRE,
	WZ_ESTIMATION,

	BS_IRON,
	BS_STEEL,
	BS_ENCHANTEDSTONE,
	BS_ORIDEOCON,
	BS_DAGGER,
	BS_SWORD,
	BS_TWOHANDSWORD,
	BS_AXE,
	BS_MACE,
	BS_KNUCKLE,
	BS_SPEAR,
	BS_HILTBINDING,
	BS_FINDINGORE,
	BS_WEAPONRESEARCH,
	BS_REPAIRWEAPON,
	BS_SKINTEMPER,
	BS_HAMMERFALL,
	BS_ADRENALINE,
	BS_WEAPONPERFECT,
	BS_OVERTHRUST,
	BS_MAXIMIZE,

	HT_SKIDTRAP,
	HT_LANDMINE,
	HT_ANKLESNARE,
	HT_SHOCKWAVE,
	HT_SANDMAN,
	HT_FLASHER,
	HT_FREEZINGTRAP,
	HT_BLASTMINE,
	HT_CLAYMORETRAP,
	HT_REMOVETRAP,
	HT_TALKIEBOX,
	HT_BEASTBANE,
	HT_FALCON,
	HT_STEELCROW,
	HT_BLITZBEAT,
	HT_DETECTING,
	HT_SPRINGTRAP,

	AS_RIGHT,
	AS_LEFT,
	AS_KATAR,
	AS_CLOAKING,
	AS_SONICBLOW,
	AS_GRIMTOOTH,
	AS_ENCHANTPOISON,
	AS_POISONREACT,
	AS_VENOMDUST,
	AS_SPLASHER,

	NV_FIRSTAID,
	NV_TRICKDEAD,
	SM_MOVINGRECOVERY,
	SM_FATALBLOW,
	SM_AUTOBERSERK,
	AC_MAKINGARROW,
	AC_CHARGEARROW,
	TF_SPRINKLESAND,
	TF_BACKSLIDING,
	TF_PICKSTONE,
	TF_THROWSTONE,
	MC_CARTREVOLUTION,
	MC_CHANGECART,
	MC_LOUD,
	AL_HOLYLIGHT,
	MG_ENERGYCOAT,

	NPC_PIERCINGATT,
	NPC_MENTALBREAKER,
	NPC_RANGEATTACK,
	NPC_ATTRICHANGE,
	NPC_CHANGEWATER,
	NPC_CHANGEGROUND,
	NPC_CHANGEFIRE,
	NPC_CHANGEWIND,
	NPC_CHANGEPOISON,
	NPC_CHANGEHOLY,
	NPC_CHANGEDARKNESS,
	NPC_CHANGETELEKINESIS,
	NPC_CRITICALSLASH,
	NPC_COMBOATTACK,
	NPC_GUIDEDATTACK,
	NPC_SELFDESTRUCTION,
	NPC_SPLASHATTACK,
	NPC_SUICIDE,
	NPC_POISON,
	NPC_BLINDATTACK,
	NPC_SILENCEATTACK,
	NPC_STUNATTACK,
	NPC_PETRIFYATTACK,
	NPC_CURSEATTACK,
	NPC_SLEEPATTACK,
	NPC_RANDOMATTACK,
	NPC_WATERATTACK,
	NPC_GROUNDATTACK,
	NPC_FIREATTACK,
	NPC_WINDATTACK,
	NPC_POISONATTACK,
	NPC_HOLYATTACK,
	NPC_DARKNESSATTACK,
	NPC_TELEKINESISATTACK,
	NPC_MAGICALATTACK,
	NPC_METAMORPHOSIS,
	NPC_PROVOCATION,
	NPC_SMOKING,
	NPC_SUMMONSLAVE,
	NPC_EMOTION,
	NPC_TRANSFORMATION,
	NPC_BLOODDRAIN,
	NPC_ENERGYDRAIN,
	NPC_KEEPING,
	NPC_DARKBREATH,
	NPC_DARKBLESSING,
	NPC_BARRIER,
	NPC_DEFENDER,
	NPC_LICK,
	NPC_HALLUCINATION,
	NPC_REBIRTH,
	NPC_SUMMONMONSTER,

	RG_SNATCHER,
	RG_STEALCOIN,
	RG_BACKSTAP,
	RG_TUNNELDRIVE,
	RG_RAID,
	RG_STRIPWEAPON,
	RG_STRIPSHIELD,
	RG_STRIPARMOR,
	RG_STRIPHELM,
	RG_INTIMIDATE,
	RG_GRAFFITI,
	RG_FLAGGRAFFITI,
	RG_CLEANER,
	RG_GANGSTER,
	RG_COMPULSION,
	RG_PLAGIARISM,

	AM_AXEMASTERY,
	AM_LEARNINGPOTION,
	AM_PHARMACY,
	AM_DEMONSTRATION,
	AM_ACIDTERROR,
	AM_POTIONPITCHER,
	AM_CANNIBALIZE,
	AM_SPHEREMINE,
	AM_CP_WEAPON,
	AM_CP_SHIELD,
	AM_CP_ARMOR,
	AM_CP_HELM,
	AM_BIOETHICS,
	AM_BIOTECHNOLOGY,
	AM_CREATECREATURE,
	AM_CULTIVATION,
	AM_FLAMECONTROL,
	AM_CALLHOMUN,
	AM_REST,
	AM_DRILLMASTER,
	AM_HEALHOMUN,
	AM_RESURRECTHOMUN,

	CR_TRUST,
	CR_AUTOGUARD,
	CR_SHIELDCHARGE,
	CR_SHIELDBOOMERANG,
	CR_REFLECTSHIELD,
	CR_HOLYCROSS,
	CR_GRANDCROSS,
	CR_DEVOTION,
	CR_PROVIDENCE,
	CR_DEFENDER,
	CR_SPEARQUICKEN,

	MO_IRONHAND,
	MO_SPIRITSRECOVERY,
	MO_CALLSPIRITS,
	MO_ABSORBSPIRITS,
	MO_TRIPLEATTACK,
	MO_BODYRELOCATION,
	MO_DODGE,
	MO_INVESTIGATE,
	MO_FINGEROFFENSIVE,
	MO_STEELBODY,
	MO_BLADESTOP,
	MO_EXPLOSIONSPIRITS,
	MO_EXTREMITYFIST,
	MO_CHAINCOMBO,
	MO_COMBOFINISH,

	SA_ADVANCEDBOOK,
	SA_CASTCANCEL,
	SA_MAGICROD,
	SA_SPELLBREAKER,
	SA_FREECAST,
	SA_AUTOSPELL,
	SA_FLAMELAUNCHER,
	SA_FROSTWEAPON,
	SA_LIGHTNINGLOADER,
	SA_SEISMICWEAPON,
	SA_DRAGONOLOGY,
	SA_VOLCANO,
	SA_DELUGE,
	SA_VIOLENTGALE,
	SA_LANDPROTECTOR,
	SA_DISPELL,
	SA_ABRACADABRA,
	SA_MONOCELL,
	SA_CLASSCHANGE,
	SA_SUMMONMONSTER,
	SA_REVERSEORCISH,
	SA_DEATH,
	SA_FORTUNE,
	SA_TAMINGMONSTER,
	SA_QUESTION,
	SA_GRAVITY,
	SA_LEVELUP,
	SA_INSTANTDEATH,
	SA_FULLRECOVERY,
	SA_COMA,

	BD_ADAPTATION,
	BD_ENCORE,
	BD_LULLABY,
	BD_RICHMANKIM,
	BD_ETERNALCHAOS,
	BD_DRUMBATTLEFIELD,
	BD_RINGNIBELUNGEN,
	BD_ROKISWEIL,
	BD_INTOABYSS,
	BD_SIEGFRIED,
	BD_RAGNAROK,

	BA_MUSICALLESSON,
	BA_MUSICALSTRIKE,
	BA_DISSONANCE,
	BA_FROSTJOKE,
	BA_WHISTLE,
	BA_ASSASSINCROSS,
	BA_POEMBRAGI,
	BA_APPLEIDUN,

	DC_DANCINGLESSON,
	DC_THROWARROW,
	DC_UGLYDANCE,
	DC_SCREAM,
	DC_HUMMING,
	DC_DONTFORGETME,
	DC_FORTUNEKISS,
	DC_SERVICEFORYOU,

	GD_APPROVAL=10000,
	GD_KAFRACONTACT,
	GD_GUARDIANRESEARCH,
	GD_CHARISMA,
	GD_EXTENSION,
};

#endif
