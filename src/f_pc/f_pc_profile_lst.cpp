#include "f_pc/f_pc_profile_lst.h"
#include "REL/executor.h"
#include "global.h"

extern process_profile_definition g_profile_OVERLAP0;
extern process_profile_definition g_profile_OVERLAP1;
extern process_profile_definition g_profile_OVERLAP6;
extern process_profile_definition g_profile_OVERLAP7;
extern process_profile_definition g_profile_OVERLAP8;
extern process_profile_definition g_profile_LOGO_SCENE;
extern process_profile_definition g_profile_MENU_SCENE;
extern process_profile_definition g_profile_PLAY_SCENE;
extern process_profile_definition g_profile_OPENING_SCENE;
extern process_profile_definition g_profile_OPENING2_SCENE;
extern process_profile_definition g_profile_TITLE_SCENE;
extern process_profile_definition g_profile_ENDING_SCENE;
extern process_profile_definition g_profile_NAME_SCENE;
extern process_profile_definition g_profile_NAMEEX_SCENE;
extern process_profile_definition g_profile_OPEN_SCENE;
extern process_profile_definition g_profile_OPEN2_SCENE;
extern process_profile_definition g_profile_OVERLAP2;
extern process_profile_definition g_profile_OVERLAP3;
extern process_profile_definition g_profile_OVERLAP4;
extern process_profile_definition g_profile_OVERLAP5;
extern process_profile_definition g_profile_ROOM_SCENE;
extern process_profile_definition g_profile_KANKYO;
extern process_profile_definition g_profile_ALLDIE;
extern process_profile_definition g_profile_ENVSE;
extern process_profile_definition g_profile_WIND_ARROW;
extern process_profile_definition g_profile_WPOT_WATER;
extern process_profile_definition g_profile_LEVEL_SE;
extern process_profile_definition g_profile_THROWSTONE;
extern process_profile_definition g_profile_TAG_EVSW;
extern process_profile_definition g_profile_Obj_Swpush;
extern process_profile_definition g_profile_Obj_Swheavy;
extern process_profile_definition g_profile_Obj_Swflat;
extern process_profile_definition g_profile_Obj_Swlight;
extern process_profile_definition g_profile_Obj_Swhammer;
extern process_profile_definition g_profile_Obj_Quake;
extern process_profile_definition g_profile_Obj_Drift;
extern process_profile_definition g_profile_Tag_Volcano;
extern process_profile_definition g_profile_TAG_SO;
extern process_profile_definition g_profile_Obj_Pbco;
extern process_profile_definition g_profile_SEATAG;
extern process_profile_definition g_profile_SEA;
extern process_profile_definition g_profile_Obj_Tide;
extern process_profile_definition g_profile_Hmlif;
extern process_profile_definition g_profile_SCENECHG;
extern process_profile_definition g_profile_Obj_Magmarock;
extern process_profile_definition g_profile_Obj_Movebox;
extern process_profile_definition g_profile_Obj_Tribox;
extern process_profile_definition g_profile_Obj_Shelf;
extern process_profile_definition g_profile_Obj_Hlift;
extern process_profile_definition g_profile_Obj_Hami2;
extern process_profile_definition g_profile_Obj_Hami3;
extern process_profile_definition g_profile_Obj_Hami4;
extern process_profile_definition g_profile_Obj_Hbrf1;
extern process_profile_definition g_profile_Obj_Volcano;
extern process_profile_definition g_profile_Obj_Vmc;
extern process_profile_definition g_profile_Obj_Usovmc;
extern process_profile_definition g_profile_Obj_Vfan;
extern process_profile_definition g_profile_Obj_Iceisland;
extern process_profile_definition g_profile_Obj_Dragonhead;
extern process_profile_definition g_profile_Obj_Pirateship;
extern process_profile_definition g_profile_Obj_Tousekiki;
extern process_profile_definition g_profile_Tag_Ret;
extern process_profile_definition g_profile_Kaji;
extern process_profile_definition g_profile_Canon;
extern process_profile_definition g_profile_MGBOARD;
extern process_profile_definition g_profile_OBJ_CANON;
extern process_profile_definition g_profile_OBJ_OTBLE;
extern process_profile_definition g_profile_OBJ_WARPT;
extern process_profile_definition g_profile_OBJ_SEARCH;
extern process_profile_definition g_profile_OBJ_TORIPOST;
extern process_profile_definition g_profile_OBJ_IKADA;
extern process_profile_definition g_profile_OBJ_MJDOOR;
extern process_profile_definition g_profile_OBJ_PFALL;
extern process_profile_definition g_profile_OBJ_HOLE;
extern process_profile_definition g_profile_Obj_Stair;
extern process_profile_definition g_profile_Obj_Lpalm;
extern process_profile_definition g_profile_Obj_Mtest;
extern process_profile_definition g_profile_Obj_Mkie;
extern process_profile_definition g_profile_Obj_Mkiek;
extern process_profile_definition g_profile_Obj_MknjD;
extern process_profile_definition g_profile_Obj_Msdan;
extern process_profile_definition g_profile_Obj_MsdanSub;
extern process_profile_definition g_profile_Obj_Msdan2;
extern process_profile_definition g_profile_Obj_MsdanSub2;
extern process_profile_definition g_profile_Obj_Nest;
extern process_profile_definition g_profile_Obj_Ojtree;
extern process_profile_definition g_profile_Obj_Ospbox;
extern process_profile_definition g_profile_Obj_Ladder;
extern process_profile_definition g_profile_Obj_Smplbg;
extern process_profile_definition g_profile_Obj_Akabe;
extern process_profile_definition g_profile_Obj_Ashut;
extern process_profile_definition g_profile_BRIDGE;
extern process_profile_definition g_profile_MSW;
extern process_profile_definition g_profile_MFLFT;
extern process_profile_definition g_profile_KLFT;
extern process_profile_definition g_profile_ICE_LIFT;
extern process_profile_definition g_profile_AMI_PROP;
extern process_profile_definition g_profile_PEDESTAL;
extern process_profile_definition g_profile_FLOOR;
extern process_profile_definition g_profile_KITA;
extern process_profile_definition g_profile_KOKIIE;
extern process_profile_definition g_profile_SHAND;
extern process_profile_definition g_profile_BITA;
extern process_profile_definition g_profile_SK;
extern process_profile_definition g_profile_SK2;
extern process_profile_definition g_profile_SSK;
extern process_profile_definition g_profile_WARPFLOWER;
extern process_profile_definition g_profile_WARPFOUT;
extern process_profile_definition g_profile_WARPLIGHT;
extern process_profile_definition g_profile_WARPHYRULE;
extern process_profile_definition g_profile_WARPDEMO20;
extern process_profile_definition g_profile_WARPGANON;
extern process_profile_definition g_profile_WARPMAJYUU;
extern process_profile_definition g_profile_Balancelift;
extern process_profile_definition g_profile_SHUTTER;
extern process_profile_definition g_profile_SHUTTER2;
extern process_profile_definition g_profile_WINDMILL;
extern process_profile_definition g_profile_MBDOOR;
extern process_profile_definition g_profile_NPC_DE1;
extern process_profile_definition g_profile_NPC_NZ;
extern process_profile_definition g_profile_NPC_SO;
extern process_profile_definition g_profile_FM;
extern process_profile_definition g_profile_LEAF_LIFT;
extern process_profile_definition g_profile_Obj_Roten;
extern process_profile_definition g_profile_TOGE;
extern process_profile_definition g_profile_Obj_Ferris;
extern process_profile_definition g_profile_Obj_Xfuta;
extern process_profile_definition g_profile_Obj_Gaship;
extern process_profile_definition g_profile_Obj_Rforce;
extern process_profile_definition g_profile_Obj_Gaship2;
extern process_profile_definition g_profile_Obj_Light;
extern process_profile_definition g_profile_Obj_Homen;
extern process_profile_definition g_profile_Obj_Homensmk;
extern process_profile_definition g_profile_Obj_Ftree;
extern process_profile_definition g_profile_Obj_Vds;
extern process_profile_definition g_profile_Obj_Vyasi;
extern process_profile_definition g_profile_Obj_Ajav;
extern process_profile_definition g_profile_Obj_Trap;
extern process_profile_definition g_profile_Obj_Hha;
extern process_profile_definition g_profile_Obj_Htetu1;
extern process_profile_definition g_profile_Obj_Gnntakis;
extern process_profile_definition g_profile_Obj_Gnntakie;
extern process_profile_definition g_profile_Obj_Gnnbtaki;
extern process_profile_definition g_profile_Obj_Rcloud;
extern process_profile_definition g_profile_Obj_Gryw00;
extern process_profile_definition g_profile_Obj_AjavW;
extern process_profile_definition g_profile_Obj_Leaves;
extern process_profile_definition g_profile_Obj_YLzou;
extern process_profile_definition g_profile_Obj_Gbed;
extern process_profile_definition g_profile_Obj_Vteng;
extern process_profile_definition g_profile_Obj_Hfuck1;
extern process_profile_definition g_profile_Obj_Ohatch;
extern process_profile_definition g_profile_Obj_Hcbh;
extern process_profile_definition g_profile_Obj_Ygush00;
extern process_profile_definition g_profile_Obj_Bscurtain;
extern process_profile_definition g_profile_Obj_Shmrgrd;
extern process_profile_definition g_profile_Obj_Eayogn;
extern process_profile_definition g_profile_Obj_Vmsms;
extern process_profile_definition g_profile_Obj_Vmsdz;
extern process_profile_definition g_profile_Ygcwp;
extern process_profile_definition g_profile_Obj_Vgnfd;
extern process_profile_definition g_profile_Obj_Kanoke;
extern process_profile_definition g_profile_Obj_Eskban;
extern process_profile_definition g_profile_Obj_Ekskz;
extern process_profile_definition g_profile_Obj_Ebomzo;
extern process_profile_definition g_profile_Obj_Kanat;
extern process_profile_definition g_profile_Obj_Aygr;
extern process_profile_definition g_profile_SHIP;
extern process_profile_definition g_profile_Obj_Jump;
extern process_profile_definition g_profile_PLAYER;
extern process_profile_definition g_profile_HOOKSHOT;
extern process_profile_definition g_profile_NPC_MK;
extern process_profile_definition g_profile_GRID;
extern process_profile_definition g_profile_SAIL;
extern process_profile_definition g_profile_PIRATE_FLAG;
extern process_profile_definition g_profile_MAJUU_FLAG;
extern process_profile_definition g_profile_Tori_Flag;
extern process_profile_definition g_profile_Sie_Flag;
extern process_profile_definition g_profile_SYAN;
extern process_profile_definition g_profile_AYUSH;
extern process_profile_definition g_profile_OSHIP;
extern process_profile_definition g_profile_RECTANGLE;
extern process_profile_definition g_profile_BB;
extern process_profile_definition g_profile_KANBAN;
extern process_profile_definition g_profile_HITOBJ;
extern process_profile_definition g_profile_KT;
extern process_profile_definition g_profile_EP;
extern process_profile_definition g_profile_LAMP;
extern process_profile_definition g_profile_FF;
extern process_profile_definition g_profile_MO2;
extern process_profile_definition g_profile_BK;
extern process_profile_definition g_profile_ST;
extern process_profile_definition g_profile_TN;
extern process_profile_definition g_profile_MANT;
extern process_profile_definition g_profile_KANTERA;
extern process_profile_definition g_profile_KAMOME;
extern process_profile_definition g_profile_NPC_KAM;
extern process_profile_definition g_profile_WBIRD;
extern process_profile_definition g_profile_DEMO_KMM;
extern process_profile_definition g_profile_NZ;
extern process_profile_definition g_profile_NZG;
extern process_profile_definition g_profile_KN;
extern process_profile_definition g_profile_DEMO_DK;
extern process_profile_definition g_profile_AM;
extern process_profile_definition g_profile_AM2;
extern process_profile_definition g_profile_GM;
extern process_profile_definition g_profile_KS;
extern process_profile_definition g_profile_CC;
extern process_profile_definition g_profile_BL;
extern process_profile_definition g_profile_WZ;
extern process_profile_definition g_profile_PH;
extern process_profile_definition g_profile_PZ;
extern process_profile_definition g_profile_BPW;
extern process_profile_definition g_profile_PW;
extern process_profile_definition g_profile_JBO;
extern process_profile_definition g_profile_BO;
extern process_profile_definition g_profile_KI;
extern process_profile_definition g_profile_MT;
extern process_profile_definition g_profile_BWD;
extern process_profile_definition g_profile_BWDS;
extern process_profile_definition g_profile_BWDG;
extern process_profile_definition g_profile_KB;
extern process_profile_definition g_profile_ESA;
extern process_profile_definition g_profile_DR;
extern process_profile_definition g_profile_DR2;
extern process_profile_definition g_profile_RD;
extern process_profile_definition g_profile_DAIOCTA;
extern process_profile_definition g_profile_DAIOCTA_EYE;
extern process_profile_definition g_profile_OQ;
extern process_profile_definition g_profile_GY;
extern process_profile_definition g_profile_GY_CTRL;
extern process_profile_definition g_profile_GY_CTRLB;
extern process_profile_definition g_profile_Hot_Floor;
extern process_profile_definition g_profile_Beam;
extern process_profile_definition g_profile_Bemos;
extern process_profile_definition g_profile_BTD;
extern process_profile_definition g_profile_BMD;
extern process_profile_definition g_profile_BMDHAND;
extern process_profile_definition g_profile_BMDFOOT;
extern process_profile_definition g_profile_DK;
extern process_profile_definition g_profile_BDK;
extern process_profile_definition g_profile_BDKOBJ;
extern process_profile_definition g_profile_BST;
extern process_profile_definition g_profile_FGANON;
extern process_profile_definition g_profile_FGMAHOU;
extern process_profile_definition g_profile_BGN;
extern process_profile_definition g_profile_BGN2;
extern process_profile_definition g_profile_BGN3;
extern process_profile_definition g_profile_GND;
extern process_profile_definition g_profile_PT;
extern process_profile_definition g_profile_SWTDOOR;
extern process_profile_definition g_profile_MOZO;
extern process_profile_definition g_profile_KUI;
extern process_profile_definition g_profile_SS;
extern process_profile_definition g_profile_SSS;
extern process_profile_definition g_profile_SITEM;
extern process_profile_definition g_profile_MACHINE;
extern process_profile_definition g_profile_ITEM;
extern process_profile_definition g_profile_BOSSITEM;
extern process_profile_definition g_profile_Demo_Item;
extern process_profile_definition g_profile_RACEITEM;
extern process_profile_definition g_profile_ShopItem;
extern process_profile_definition g_profile_DEKU_ITEM;
extern process_profile_definition g_profile_SPC_ITEM01;
extern process_profile_definition g_profile_Obj_Paper;
extern process_profile_definition g_profile_Obj_Demo_Barrel;
extern process_profile_definition g_profile_Obj_Dmgroom;
extern process_profile_definition g_profile_Obj_Doguu;
extern process_profile_definition g_profile_Obj_Wood;
extern process_profile_definition g_profile_Obj_Flame;
extern process_profile_definition g_profile_Obj_Buoyrace;
extern process_profile_definition g_profile_Obj_Coming;
extern process_profile_definition g_profile_Coming2;
extern process_profile_definition g_profile_Coming3;
extern process_profile_definition g_profile_Obj_Mmrr;
extern process_profile_definition g_profile_Obj_Pbka;
extern process_profile_definition g_profile_Obj_Plant;
extern process_profile_definition g_profile_Obj_Gtaki;
extern process_profile_definition g_profile_Obj_Yboil;
extern process_profile_definition g_profile_Obj_Rflw;
extern process_profile_definition g_profile_Obj_Table;
extern process_profile_definition g_profile_Obj_Tenmado;
extern process_profile_definition g_profile_Obj_Cafelmp;
extern process_profile_definition g_profile_Obj_Apzl;
extern process_profile_definition g_profile_Obj_Adnno;
extern process_profile_definition g_profile_Obj_Auzu;
extern process_profile_definition g_profile_Obj_Gong;
extern process_profile_definition g_profile_Obj_Barrier;
extern process_profile_definition g_profile_Obj_Firewall;
extern process_profile_definition g_profile_Obj_TnTrap;
extern process_profile_definition g_profile_Obj_Monument;
extern process_profile_definition g_profile_Obj_Tapestry;
extern process_profile_definition g_profile_Obj_HSH;
extern process_profile_definition g_profile_Goal_Flag;
extern process_profile_definition g_profile_TBOX;
extern process_profile_definition g_profile_SBOX;
extern process_profile_definition g_profile_BOMB;
extern process_profile_definition g_profile_Bomb2;
extern process_profile_definition g_profile_BOMB_FLOWER;
extern process_profile_definition g_profile_ACORN_LEAF;
extern process_profile_definition g_profile_SWC00;
extern process_profile_definition g_profile_FAN;
extern process_profile_definition g_profile_DOOR10;
extern process_profile_definition g_profile_DOOR12;
extern process_profile_definition g_profile_ATDOOR;
extern process_profile_definition g_profile_MDOOR;
extern process_profile_definition g_profile_KDDOOR;
extern process_profile_definition g_profile_KNOB00;
extern process_profile_definition g_profile_MTOGE;
extern process_profile_definition g_profile_ANDSW0;
extern process_profile_definition g_profile_ANDSW2;
extern process_profile_definition g_profile_DAI;
extern process_profile_definition g_profile_SW_ATTACK;
extern process_profile_definition g_profile_SW_ITEM;
extern process_profile_definition g_profile_SW_TACT;
extern process_profile_definition g_profile_NH;
extern process_profile_definition g_profile_NPC_OS;
extern process_profile_definition g_profile_NPC_YM1;
extern process_profile_definition g_profile_NPC_YM2;
extern process_profile_definition g_profile_NPC_YW1;
extern process_profile_definition g_profile_NPC_JI1;
extern process_profile_definition g_profile_NPC_KO1;
extern process_profile_definition g_profile_NPC_KO2;
extern process_profile_definition g_profile_NPC_LS1;
extern process_profile_definition g_profile_NPC_P1;
extern process_profile_definition g_profile_NPC_P2;
extern process_profile_definition g_profile_NPC_SARACE;
extern process_profile_definition g_profile_NPC_TC;
extern process_profile_definition g_profile_NPC_BM1;
extern process_profile_definition g_profile_NPC_BM2;
extern process_profile_definition g_profile_NPC_BM3;
extern process_profile_definition g_profile_NPC_BM4;
extern process_profile_definition g_profile_NPC_BM5;
extern process_profile_definition g_profile_NPC_OB1;
extern process_profile_definition g_profile_NPC_AJ1;
extern process_profile_definition g_profile_NPC_KM1;
extern process_profile_definition g_profile_NPC_CB1;
extern process_profile_definition g_profile_NPC_BA1;
extern process_profile_definition g_profile_NPC_BJ1;
extern process_profile_definition g_profile_NPC_BJ2;
extern process_profile_definition g_profile_NPC_BJ3;
extern process_profile_definition g_profile_NPC_BJ4;
extern process_profile_definition g_profile_NPC_BJ5;
extern process_profile_definition g_profile_NPC_BJ6;
extern process_profile_definition g_profile_NPC_BJ7;
extern process_profile_definition g_profile_NPC_BJ8;
extern process_profile_definition g_profile_NPC_BJ9;
extern process_profile_definition g_profile_NPC_BS1;
extern process_profile_definition g_profile_NPC_BMCON1;
extern process_profile_definition g_profile_NPC_BMS1;
extern process_profile_definition g_profile_NPC_BMSW;
extern process_profile_definition g_profile_NPC_BTSW;
extern process_profile_definition g_profile_NPC_BTSW2;
extern process_profile_definition g_profile_NPC_DS1;
extern process_profile_definition g_profile_NPC_RSH1;
extern process_profile_definition g_profile_NPC_KK1;
extern process_profile_definition g_profile_NPC_PM1;
extern process_profile_definition g_profile_NPC_KP1;
extern process_profile_definition g_profile_NPC_PF1;
extern process_profile_definition g_profile_NPC_GP1;
extern process_profile_definition g_profile_NPC_JB1;
extern process_profile_definition g_profile_NPC_KF1;
extern process_profile_definition g_profile_NPC_FA1;
extern process_profile_definition g_profile_NPC_AUCTION;
extern process_profile_definition g_profile_NPC_KG1;
extern process_profile_definition g_profile_NPC_KG2;
extern process_profile_definition g_profile_NPC_TT;
extern process_profile_definition g_profile_NPC_HR;
extern process_profile_definition g_profile_NPC_HO;
extern process_profile_definition g_profile_NPC_MD;
extern process_profile_definition g_profile_NPC_UK;
extern process_profile_definition g_profile_BIGELF;
extern process_profile_definition g_profile_NPC_CO1;
extern process_profile_definition g_profile_NPC_ZK1;
extern process_profile_definition g_profile_NPC_ROTEN;
extern process_profile_definition g_profile_NPC_PEOPLE;
extern process_profile_definition g_profile_NPC_GK1;
extern process_profile_definition g_profile_NPC_PHOTO;
extern process_profile_definition g_profile_NPC_AC1;
extern process_profile_definition g_profile_NPC_HI1;
extern process_profile_definition g_profile_NPC_SV;
extern process_profile_definition g_profile_NPC_MT;
extern process_profile_definition g_profile_NPC_MN;
extern process_profile_definition g_profile_NPC_AH;
extern process_profile_definition g_profile_AUCTION;
extern process_profile_definition g_profile_KYTAG00;
extern process_profile_definition g_profile_KYTAG01;
extern process_profile_definition g_profile_KYTAG02;
extern process_profile_definition g_profile_KYTAG03;
extern process_profile_definition g_profile_KYTAG04;
extern process_profile_definition g_profile_KYTAG05;
extern process_profile_definition g_profile_KYTAG06;
extern process_profile_definition g_profile_KYTAG07;
extern process_profile_definition g_profile_WindTag;
extern process_profile_definition g_profile_YOUGAN;
extern process_profile_definition g_profile_Mmusic;
extern process_profile_definition g_profile_Komore;
extern process_profile_definition g_profile_Tpota;
extern process_profile_definition g_profile_Obj_Itnak;
extern process_profile_definition g_profile_Obj_Zouk;
extern process_profile_definition g_profile_Ykgr;
extern process_profile_definition g_profile_SAKU;
extern process_profile_definition g_profile_Iball;
extern process_profile_definition g_profile_DISAPPEAR;
extern process_profile_definition g_profile_Salvage;
extern process_profile_definition g_profile_SALVAGE_TBOX;
extern process_profile_definition g_profile_Kmon;
extern process_profile_definition g_profile_OBJ_FIGURE;
extern process_profile_definition g_profile_OBJ_HAT;
extern process_profile_definition g_profile_DEMO00;
extern process_profile_definition g_profile_Lwood;
extern process_profile_definition g_profile_Dummy;
extern process_profile_definition g_profile_TAG_EVENT;
extern process_profile_definition g_profile_TAG_HINT;
extern process_profile_definition g_profile_TAG_MSG;
extern process_profile_definition g_profile_TAG_ETC;
extern process_profile_definition g_profile_TAG_ISLAND;
extern process_profile_definition g_profile_TAG_KF1;
extern process_profile_definition g_profile_TAG_KK1;
extern process_profile_definition g_profile_TAG_PHOTO;
extern process_profile_definition g_profile_TAG_KB_ITEM;
extern process_profile_definition g_profile_TAG_MK;
extern process_profile_definition g_profile_TAG_MDCB;
extern process_profile_definition g_profile_TAG_BA1;
extern process_profile_definition g_profile_TagRock;
extern process_profile_definition g_profile_FallRock;
extern process_profile_definition g_profile_SteamTag;
extern process_profile_definition g_profile_Fire;
extern process_profile_definition g_profile_BRANCH;
extern process_profile_definition g_profile_NPC_ZL1;
extern process_profile_definition g_profile_WATERFALL;
extern process_profile_definition g_profile_LIGHTBRIDGE;
extern process_profile_definition g_profile_LIGHTSTAIR;
extern process_profile_definition g_profile_WALL;
extern process_profile_definition g_profile_SW_PROPELLER;
extern process_profile_definition g_profile_IKARI;
extern process_profile_definition g_profile_BOOMERANG;
extern process_profile_definition g_profile_AGB;
extern process_profile_definition g_profile_AGBSW0;
extern process_profile_definition g_profile_MAGMA;
extern process_profile_definition g_profile_GRASS;
extern process_profile_definition g_profile_KY_THUNDER;
extern process_profile_definition g_profile_VRBOX;
extern process_profile_definition g_profile_VRBOX2;
extern process_profile_definition g_profile_BG;
extern process_profile_definition g_profile_Obj_Tower;
extern process_profile_definition g_profile_Obj_DoguuD;
extern process_profile_definition g_profile_SPOTBOX;
extern process_profile_definition g_profile_TORNADO;
extern process_profile_definition g_profile_TITLE;
extern process_profile_definition g_profile_MP;
extern process_profile_definition g_profile_LODBG;
extern process_profile_definition g_profile_HIMO2;
extern process_profile_definition g_profile_HIMO3;
extern process_profile_definition g_profile_ATT;
extern process_profile_definition g_profile_WPILLAR;
extern process_profile_definition g_profile_Hys;
extern process_profile_definition g_profile_SWHIT0;
extern process_profile_definition g_profile_TAG_GSHIP;
extern process_profile_definition g_profile_TSUBO;
extern process_profile_definition g_profile_STONE;
extern process_profile_definition g_profile_Stone2;
extern process_profile_definition g_profile_Obj_Barrel;
extern process_profile_definition g_profile_Obj_Barrel2;
extern process_profile_definition g_profile_Obj_Try;
extern process_profile_definition g_profile_Obj_Vtil;
extern process_profile_definition g_profile_Obj_Ice;
extern process_profile_definition g_profile_Obj_Mshokki;
extern process_profile_definition g_profile_STANDITEM;
extern process_profile_definition g_profile_BOKO;
extern process_profile_definition g_profile_TAMA;
extern process_profile_definition g_profile_Obj_Buoyflag;
extern process_profile_definition g_profile_Obj_Correct;
extern process_profile_definition g_profile_Obj_Eff;
extern process_profile_definition g_profile_WATER_MARK;
extern process_profile_definition g_profile_Tag_Light;
extern process_profile_definition g_profile_Tag_Attention;
extern process_profile_definition g_profile_Tag_Waterlevel;
extern process_profile_definition g_profile_ARROW;
extern process_profile_definition g_profile_ARROW_ICEEFF;
extern process_profile_definition g_profile_ARROW_LIGHTEFF;
extern process_profile_definition g_profile_Obj_Timer;
extern process_profile_definition g_profile_CAMERA;
extern process_profile_definition g_profile_CAMERA2;
extern process_profile_definition g_profile_KYEFF;
extern process_profile_definition g_profile_KYEFF2;
extern process_profile_definition g_profile_MESG;
extern process_profile_definition g_profile_MSG;
extern process_profile_definition g_profile_MSG2;
extern process_profile_definition g_profile_MSG3;
extern process_profile_definition g_profile_MENUWINDOW;
extern process_profile_definition g_profile_Menu_Cloth;
extern process_profile_definition g_profile_TIMER;
extern process_profile_definition g_profile_AUCTION_SCREEN;
extern process_profile_definition g_profile_PLACE_NAME;
extern process_profile_definition g_profile_MINIGAME_STARTER;
extern process_profile_definition g_profile_MINIGAME_TERMINATER;
extern process_profile_definition g_profile_METER;
extern process_profile_definition g_profile_OPERATE_WIND;
extern process_profile_definition g_profile_SCP;
extern process_profile_definition g_profile_PB;
extern process_profile_definition g_profile_GAMEOVER;

process_profile_definition* g_fpcPfLst_ProfileList[] = {
    &g_profile_OVERLAP0,
    &g_profile_OVERLAP1,
    &g_profile_OVERLAP6,
    &g_profile_OVERLAP7,
    &g_profile_OVERLAP8,
    &g_profile_LOGO_SCENE,
    &g_profile_MENU_SCENE,
    &g_profile_PLAY_SCENE,
    &g_profile_OPENING_SCENE,
    &g_profile_OPENING2_SCENE,
    &g_profile_TITLE_SCENE,
    &g_profile_ENDING_SCENE,
    &g_profile_NAME_SCENE,
    &g_profile_NAMEEX_SCENE,
    &g_profile_OPEN_SCENE,
    &g_profile_OPEN2_SCENE,
    &g_profile_OVERLAP2,
    &g_profile_OVERLAP3,
    &g_profile_OVERLAP4,
    &g_profile_OVERLAP5,
    &g_profile_ROOM_SCENE,
    &g_profile_KANKYO,
    &g_profile_ALLDIE,
    &g_profile_ENVSE,
    &g_profile_WIND_ARROW,
    &g_profile_WPOT_WATER,
    &g_profile_LEVEL_SE,
    &g_profile_THROWSTONE,
    &g_profile_TAG_EVSW,
    &g_profile_Obj_Swpush,
    &g_profile_Obj_Swheavy,
    &g_profile_Obj_Swflat,
    &g_profile_Obj_Swlight,
    &g_profile_Obj_Swhammer,
    &g_profile_Obj_Quake,
    &g_profile_Obj_Drift,
    &g_profile_Tag_Volcano,
    &g_profile_TAG_SO,
    &g_profile_Obj_Pbco,
    &g_profile_SEATAG,
    &g_profile_SEA,
    &g_profile_Obj_Tide,
    &g_profile_Hmlif,
    &g_profile_SCENECHG,
    &g_profile_Obj_Magmarock,
    &g_profile_Obj_Movebox,
    &g_profile_Obj_Tribox,
    &g_profile_Obj_Shelf,
    &g_profile_Obj_Hlift,
    &g_profile_Obj_Hami2,
    &g_profile_Obj_Hami3,
    &g_profile_Obj_Hami4,
    &g_profile_Obj_Hbrf1,
    &g_profile_Obj_Volcano,
    &g_profile_Obj_Vmc,
    &g_profile_Obj_Usovmc,
    &g_profile_Obj_Vfan,
    &g_profile_Obj_Iceisland,
    &g_profile_Obj_Dragonhead,
    &g_profile_Obj_Pirateship,
    &g_profile_Obj_Tousekiki,
    &g_profile_Tag_Ret,
    &g_profile_Kaji,
    &g_profile_Canon,
    &g_profile_MGBOARD,
    &g_profile_OBJ_CANON,
    &g_profile_OBJ_OTBLE,
    &g_profile_OBJ_WARPT,
    &g_profile_OBJ_SEARCH,
    &g_profile_OBJ_TORIPOST,
    &g_profile_OBJ_IKADA,
    &g_profile_OBJ_MJDOOR,
    &g_profile_OBJ_PFALL,
    &g_profile_OBJ_HOLE,
    &g_profile_Obj_Stair,
    &g_profile_Obj_Lpalm,
    &g_profile_Obj_Mtest,
    &g_profile_Obj_Mkie,
    &g_profile_Obj_Mkiek,
    &g_profile_Obj_MknjD,
    &g_profile_Obj_Msdan,
    &g_profile_Obj_MsdanSub,
    &g_profile_Obj_Msdan2,
    &g_profile_Obj_MsdanSub2,
    &g_profile_Obj_Nest,
    &g_profile_Obj_Ojtree,
    &g_profile_Obj_Ospbox,
    &g_profile_Obj_Ladder,
    &g_profile_Obj_Smplbg,
    &g_profile_Obj_Akabe,
    &g_profile_Obj_Ashut,
    &g_profile_BRIDGE,
    &g_profile_MSW,
    &g_profile_MFLFT,
    &g_profile_KLFT,
    &g_profile_ICE_LIFT,
    &g_profile_AMI_PROP,
    &g_profile_PEDESTAL,
    &g_profile_FLOOR,
    &g_profile_KITA,
    &g_profile_KOKIIE,
    &g_profile_SHAND,
    &g_profile_BITA,
    &g_profile_SK,
    &g_profile_SK2,
    &g_profile_SSK,
    &g_profile_WARPFLOWER,
    &g_profile_WARPFOUT,
    &g_profile_WARPLIGHT,
    &g_profile_WARPHYRULE,
    &g_profile_WARPDEMO20,
    &g_profile_WARPGANON,
    &g_profile_WARPMAJYUU,
    &g_profile_Balancelift,
    &g_profile_SHUTTER,
    &g_profile_SHUTTER2,
    &g_profile_WINDMILL,
    &g_profile_MBDOOR,
    &g_profile_NPC_DE1,
    &g_profile_NPC_NZ,
    &g_profile_NPC_SO,
    &g_profile_FM,
    &g_profile_LEAF_LIFT,
    &g_profile_Obj_Roten,
    &g_profile_TOGE,
    &g_profile_Obj_Ferris,
    &g_profile_Obj_Xfuta,
    &g_profile_Obj_Gaship,
    &g_profile_Obj_Rforce,
    &g_profile_Obj_Gaship2,
    &g_profile_Obj_Light,
    &g_profile_Obj_Homen,
    &g_profile_Obj_Homensmk,
    &g_profile_Obj_Ftree,
    &g_profile_Obj_Vds,
    &g_profile_Obj_Vyasi,
    &g_profile_Obj_Ajav,
    &g_profile_Obj_Trap,
    &g_profile_Obj_Hha,
    &g_profile_Obj_Htetu1,
    &g_profile_Obj_Gnntakis,
    &g_profile_Obj_Gnntakie,
    &g_profile_Obj_Gnnbtaki,
    &g_profile_Obj_Rcloud,
    &g_profile_Obj_Gryw00,
    &g_profile_Obj_AjavW,
    &g_profile_Obj_Leaves,
    &g_profile_Obj_YLzou,
    &g_profile_Obj_Gbed,
    &g_profile_Obj_Vteng,
    &g_profile_Obj_Hfuck1,
    &g_profile_Obj_Ohatch,
    &g_profile_Obj_Hcbh,
    &g_profile_Obj_Ygush00,
    &g_profile_Obj_Bscurtain,
    &g_profile_Obj_Shmrgrd,
    &g_profile_Obj_Eayogn,
    &g_profile_Obj_Vmsms,
    &g_profile_Obj_Vmsdz,
    &g_profile_Ygcwp,
    &g_profile_Obj_Vgnfd,
    &g_profile_Obj_Kanoke,
    &g_profile_Obj_Eskban,
    &g_profile_Obj_Ekskz,
    &g_profile_Obj_Ebomzo,
    &g_profile_Obj_Kanat,
    &g_profile_Obj_Aygr,
    &g_profile_SHIP,
    &g_profile_Obj_Jump,
    &g_profile_PLAYER,
    &g_profile_HOOKSHOT,
    &g_profile_NPC_MK,
    &g_profile_GRID,
    &g_profile_SAIL,
    &g_profile_PIRATE_FLAG,
    &g_profile_MAJUU_FLAG,
    &g_profile_Tori_Flag,
    &g_profile_Sie_Flag,
    &g_profile_SYAN,
    &g_profile_AYUSH,
    &g_profile_OSHIP,
    &g_profile_RECTANGLE,
    &g_profile_BB,
    &g_profile_KANBAN,
    &g_profile_HITOBJ,
    &g_profile_KT,
    &g_profile_EP,
    &g_profile_LAMP,
    &g_profile_FF,
    &g_profile_MO2,
    &g_profile_BK,
    &g_profile_ST,
    &g_profile_TN,
    &g_profile_MANT,
    &g_profile_KANTERA,
    &g_profile_KAMOME,
    &g_profile_NPC_KAM,
    &g_profile_WBIRD,
    &g_profile_DEMO_KMM,
    &g_profile_NZ,
    &g_profile_NZG,
    &g_profile_KN,
    &g_profile_DEMO_DK,
    &g_profile_AM,
    &g_profile_AM2,
    &g_profile_GM,
    &g_profile_KS,
    &g_profile_CC,
    &g_profile_BL,
    &g_profile_WZ,
    &g_profile_PH,
    &g_profile_PZ,
    &g_profile_BPW,
    &g_profile_PW,
    &g_profile_JBO,
    &g_profile_BO,
    &g_profile_KI,
    &g_profile_MT,
    &g_profile_BWD,
    &g_profile_BWDS,
    &g_profile_BWDG,
    &g_profile_KB,
    &g_profile_ESA,
    &g_profile_DR,
    &g_profile_DR2,
    &g_profile_RD,
    &g_profile_DAIOCTA,
    &g_profile_DAIOCTA_EYE,
    &g_profile_OQ,
    &g_profile_GY,
    &g_profile_GY_CTRL,
    &g_profile_GY_CTRLB,
    &g_profile_Hot_Floor,
    &g_profile_Beam,
    &g_profile_Bemos,
    &g_profile_BTD,
    &g_profile_BMD,
    &g_profile_BMDHAND,
    &g_profile_BMDFOOT,
    &g_profile_DK,
    &g_profile_BDK,
    &g_profile_BDKOBJ,
    &g_profile_BST,
    &g_profile_FGANON,
    &g_profile_FGMAHOU,
    &g_profile_BGN,
    &g_profile_BGN2,
    &g_profile_BGN3,
    &g_profile_GND,
    &g_profile_PT,
    &g_profile_SWTDOOR,
    &g_profile_MOZO,
    &g_profile_KUI,
    &g_profile_SS,
    &g_profile_SSS,
    &g_profile_SITEM,
    &g_profile_MACHINE,
    &g_profile_ITEM,
    &g_profile_BOSSITEM,
    &g_profile_Demo_Item,
    &g_profile_RACEITEM,
    &g_profile_ShopItem,
    &g_profile_DEKU_ITEM,
    &g_profile_SPC_ITEM01,
    &g_profile_Obj_Paper,
    &g_profile_Obj_Demo_Barrel,
    &g_profile_Obj_Dmgroom,
    &g_profile_Obj_Doguu,
    &g_profile_Obj_Wood,
    &g_profile_Obj_Flame,
    &g_profile_Obj_Buoyrace,
    &g_profile_Obj_Coming,
    &g_profile_Coming2,
    &g_profile_Coming3,
    &g_profile_Obj_Mmrr,
    &g_profile_Obj_Pbka,
    &g_profile_Obj_Plant,
    &g_profile_Obj_Gtaki,
    &g_profile_Obj_Yboil,
    &g_profile_Obj_Rflw,
    &g_profile_Obj_Table,
    &g_profile_Obj_Tenmado,
    &g_profile_Obj_Cafelmp,
    &g_profile_Obj_Apzl,
    &g_profile_Obj_Adnno,
    &g_profile_Obj_Auzu,
    &g_profile_Obj_Gong,
    &g_profile_Obj_Barrier,
    &g_profile_Obj_Firewall,
    &g_profile_Obj_TnTrap,
    &g_profile_Obj_Monument,
    &g_profile_Obj_Tapestry,
    &g_profile_Obj_HSH,
    &g_profile_Goal_Flag,
    &g_profile_TBOX,
    &g_profile_SBOX,
    &g_profile_BOMB,
    &g_profile_Bomb2,
    &g_profile_BOMB_FLOWER,
    &g_profile_ACORN_LEAF,
    &g_profile_SWC00,
    &g_profile_FAN,
    &g_profile_DOOR10,
    &g_profile_DOOR12,
    &g_profile_ATDOOR,
    &g_profile_MDOOR,
    &g_profile_KDDOOR,
    &g_profile_KNOB00,
    &g_profile_MTOGE,
    &g_profile_ANDSW0,
    &g_profile_ANDSW2,
    &g_profile_DAI,
    &g_profile_SW_ATTACK,
    &g_profile_SW_ITEM,
    &g_profile_SW_TACT,
    &g_profile_NH,
    &g_profile_NPC_OS,
    &g_profile_NPC_YM1,
    &g_profile_NPC_YM2,
    &g_profile_NPC_YW1,
    &g_profile_NPC_JI1,
    &g_profile_NPC_KO1,
    &g_profile_NPC_KO2,
    &g_profile_NPC_LS1,
    &g_profile_NPC_P1,
    &g_profile_NPC_P2,
    &g_profile_NPC_SARACE,
    &g_profile_NPC_TC,
    &g_profile_NPC_BM1,
    &g_profile_NPC_BM2,
    &g_profile_NPC_BM3,
    &g_profile_NPC_BM4,
    &g_profile_NPC_BM5,
    &g_profile_NPC_OB1,
    &g_profile_NPC_AJ1,
    &g_profile_NPC_KM1,
    &g_profile_NPC_CB1,
    &g_profile_NPC_BA1,
    &g_profile_NPC_BJ1,
    &g_profile_NPC_BJ2,
    &g_profile_NPC_BJ3,
    &g_profile_NPC_BJ4,
    &g_profile_NPC_BJ5,
    &g_profile_NPC_BJ6,
    &g_profile_NPC_BJ7,
    &g_profile_NPC_BJ8,
    &g_profile_NPC_BJ9,
    &g_profile_NPC_BS1,
    &g_profile_NPC_BMCON1,
    &g_profile_NPC_BMS1,
    &g_profile_NPC_BMSW,
    &g_profile_NPC_BTSW,
    &g_profile_NPC_BTSW2,
    &g_profile_NPC_DS1,
    &g_profile_NPC_RSH1,
    &g_profile_NPC_KK1,
    &g_profile_NPC_PM1,
    &g_profile_NPC_KP1,
    &g_profile_NPC_PF1,
    &g_profile_NPC_GP1,
    &g_profile_NPC_JB1,
    &g_profile_NPC_KF1,
    &g_profile_NPC_FA1,
    &g_profile_NPC_AUCTION,
    &g_profile_NPC_KG1,
    &g_profile_NPC_KG2,
    &g_profile_NPC_TT,
    &g_profile_NPC_HR,
    &g_profile_NPC_HO,
    &g_profile_NPC_MD,
    &g_profile_NPC_UK,
    &g_profile_BIGELF,
    &g_profile_NPC_CO1,
    &g_profile_NPC_ZK1,
    &g_profile_NPC_ROTEN,
    &g_profile_NPC_PEOPLE,
    &g_profile_NPC_GK1,
    &g_profile_NPC_PHOTO,
    &g_profile_NPC_AC1,
    &g_profile_NPC_HI1,
    &g_profile_NPC_SV,
    &g_profile_NPC_MT,
    &g_profile_NPC_MN,
    &g_profile_NPC_AH,
    &g_profile_AUCTION,
    &g_profile_KYTAG00,
    &g_profile_KYTAG01,
    &g_profile_KYTAG02,
    &g_profile_KYTAG03,
    &g_profile_KYTAG04,
    &g_profile_KYTAG05,
    &g_profile_KYTAG06,
    &g_profile_KYTAG07,
    &g_profile_WindTag,
    &g_profile_YOUGAN,
    &g_profile_Mmusic,
    &g_profile_Komore,
    &g_profile_Tpota,
    &g_profile_Obj_Itnak,
    &g_profile_Obj_Zouk,
    &g_profile_Ykgr,
    &g_profile_SAKU,
    &g_profile_Iball,
    &g_profile_DISAPPEAR,
    &g_profile_Salvage,
    &g_profile_SALVAGE_TBOX,
    &g_profile_Kmon,
    &g_profile_OBJ_FIGURE,
    &g_profile_OBJ_HAT,
    &g_profile_DEMO00,
    &g_profile_Lwood,
    &g_profile_Dummy,
    &g_profile_TAG_EVENT,
    &g_profile_TAG_HINT,
    &g_profile_TAG_MSG,
    &g_profile_TAG_ETC,
    &g_profile_TAG_ISLAND,
    &g_profile_TAG_KF1,
    &g_profile_TAG_KK1,
    &g_profile_TAG_PHOTO,
    &g_profile_TAG_KB_ITEM,
    &g_profile_TAG_MK,
    &g_profile_TAG_MDCB,
    &g_profile_TAG_BA1,
    &g_profile_TagRock,
    &g_profile_FallRock,
    &g_profile_SteamTag,
    &g_profile_Fire,
    &g_profile_BRANCH,
    &g_profile_NPC_ZL1,
    &g_profile_WATERFALL,
    &g_profile_LIGHTBRIDGE,
    &g_profile_LIGHTSTAIR,
    &g_profile_WALL,
    &g_profile_SW_PROPELLER,
    &g_profile_IKARI,
    &g_profile_BOOMERANG,
    &g_profile_AGB,
    &g_profile_AGBSW0,
    &g_profile_MAGMA,
    &g_profile_GRASS,
    &g_profile_KY_THUNDER,
    &g_profile_VRBOX,
    &g_profile_VRBOX2,
    &g_profile_BG,
    &g_profile_Obj_Tower,
    &g_profile_Obj_DoguuD,
    &g_profile_SPOTBOX,
    &g_profile_TORNADO,
    &g_profile_TITLE,
    &g_profile_MP,
    &g_profile_LODBG,
    &g_profile_HIMO2,
    &g_profile_HIMO3,
    &g_profile_ATT,
    &g_profile_WPILLAR,
    &g_profile_Hys,
    &g_profile_SWHIT0,
    &g_profile_TAG_GSHIP,
    &g_profile_TSUBO,
    &g_profile_STONE,
    &g_profile_Stone2,
    &g_profile_Obj_Barrel,
    &g_profile_Obj_Barrel2,
    &g_profile_Obj_Try,
    &g_profile_Obj_Vtil,
    &g_profile_Obj_Ice,
    &g_profile_Obj_Mshokki,
    &g_profile_STANDITEM,
    &g_profile_BOKO,
    &g_profile_TAMA,
    &g_profile_Obj_Buoyflag,
    &g_profile_Obj_Correct,
    &g_profile_Obj_Eff,
    &g_profile_WATER_MARK,
    &g_profile_Tag_Light,
    &g_profile_Tag_Attention,
    &g_profile_Tag_Waterlevel,
    &g_profile_ARROW,
    &g_profile_ARROW_ICEEFF,
    &g_profile_ARROW_LIGHTEFF,
    &g_profile_Obj_Timer,
    &g_profile_CAMERA,
    &g_profile_CAMERA2,
    &g_profile_KYEFF,
    &g_profile_KYEFF2,
#if VERSION == VERSION_PAL
    &g_profile_MSG3,
#endif
    &g_profile_MESG,
    &g_profile_MSG,
    &g_profile_MSG2,
#if VERSION != VERSION_PAL
    &g_profile_MSG3,
#endif
    &g_profile_MENUWINDOW,
    &g_profile_Menu_Cloth,
    &g_profile_TIMER,
    &g_profile_AUCTION_SCREEN,
    &g_profile_PLACE_NAME,
    &g_profile_MINIGAME_STARTER,
    &g_profile_MINIGAME_TERMINATER,
    &g_profile_METER,
    &g_profile_OPERATE_WIND,
    &g_profile_SCP,
    &g_profile_PB,
    &g_profile_GAMEOVER,
    NULL,
};

/* 00000078-0000008C       .text ModuleProlog */
void ModuleProlog() {
    g_fpcPf_ProfileList_p = g_fpcPfLst_ProfileList;
}

/* 0000008C-0000009C       .text ModuleEpilog */
void ModuleEpilog() {
    g_fpcPf_ProfileList_p = NULL;
}
