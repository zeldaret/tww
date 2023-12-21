//
// Generated by dtk
// Translation Unit: c_dylink.o
//

#include "c/c_dylink.h"
#include "d/d_com_lib_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_printf.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JKernel/JKRFileCache.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "DynamicLink.h"
#include "dolphin/os/OS.h"
#include "MSL_C/string.h"

DynamicModuleControlBase * DMC[PROC_COUNT_e];
bool DMC_initialized = false;
BOOL cDyl_Initialized = false;
mDoDvdThd_callback_c * cDyl_DVD = NULL;

const DynamicNameTableEntry DynamicNameTable[] = {
    {PROC_ALLDIE,         "d_a_alldie"},
    {PROC_TAG_EVSW,       "d_a_tag_evsw"},
    {PROC_Obj_Swpush,     "d_a_obj_swpush"},
    {PROC_Obj_Swheavy,    "d_a_obj_swheavy"},
    {PROC_Obj_Swflat,     "d_a_obj_swflat"},
    {PROC_Obj_Swlight,    "d_a_obj_swlight"},
    {PROC_Obj_Swhammer,   "d_a_obj_swhammer"},
    {PROC_Obj_Quake,      "d_a_obj_quake"},
    {PROC_Obj_Drift,      "d_a_obj_drift"},
    {PROC_Tag_Volcano,    "d_a_tag_volcano"},
    {PROC_TAG_SO,         "d_a_tag_so"},
    {PROC_Obj_Pbco,       "d_a_obj_pbco"},
    {PROC_SEATAG,         "d_a_seatag"},
    {PROC_Obj_Tide,       "d_a_obj_tide"},
    {PROC_Hmlif,          "d_a_hmlif"},
    {PROC_SCENECHG,       "d_a_scene_change"},
    {PROC_Obj_Magmarock,  "d_a_obj_magmarock"},
    {PROC_Obj_Movebox,    "d_a_obj_movebox"},
    {PROC_Obj_Tribox,     "d_a_obj_tribox"},
    {PROC_Obj_Shelf,      "d_a_obj_shelf"},
    {PROC_Obj_Hlift,      "d_a_obj_hlift"},
    {PROC_Obj_Hami2,      "d_a_obj_hami2"},
    {PROC_Obj_Hami3,      "d_a_obj_hami3"},
    {PROC_Obj_Hami4,      "d_a_obj_hami4"},
    {PROC_Obj_Hbrf1,      "d_a_obj_hbrf1"},
    {PROC_Obj_Volcano,    "d_a_obj_volcano"},
    {PROC_Obj_Vmc,        "d_a_obj_vmc"},
    {PROC_Obj_Usovmc,     "d_a_obj_usovmc"},
    {PROC_Obj_Vfan,       "d_a_obj_vfan"},
    {PROC_Obj_Iceisland,  "d_a_obj_iceisland"},
    {PROC_Obj_Dragonhead, "d_a_obj_dragonhead"},
    {PROC_Obj_Pirateship, "d_a_obj_pirateship"},
    {PROC_Obj_Tousekiki,  "d_a_obj_tousekiki"},
    {PROC_Tag_Ret,        "d_a_tag_ret"},
    {PROC_Kaji,           "d_a_kaji"},
    {PROC_Canon,          "d_a_canon"},
    {PROC_MGBOARD,        "d_a_mgameboard"},
    {PROC_OBJ_CANON,      "d_a_obj_canon"},
    {PROC_OBJ_OTBLE,      "d_a_obj_otble"},
    {PROC_OBJ_WARPT,      "d_a_obj_warpt"},
    {PROC_OBJ_TORIPOST,   "d_a_obj_toripost"},
    {PROC_OBJ_IKADA,      "d_a_obj_ikada"},
    {PROC_OBJ_MJDOOR,     "d_a_obj_majyuu_door"},
    {PROC_OBJ_PFALL,      "d_a_obj_pfall"},
    {PROC_OBJ_HOLE,       "d_a_obj_hole"},
    {PROC_Obj_Stair,      "d_a_obj_stair"},
    {PROC_Obj_Lpalm,      "d_a_obj_lpalm"},
    {PROC_Obj_Mtest,      "d_a_obj_mtest"},
    {PROC_Obj_Mkie,       "d_a_obj_mkie"},
    {PROC_Obj_Mkiek,      "d_a_obj_mkiek"},
    {PROC_Obj_MknjD,      "d_a_obj_mknjd"},
    {PROC_Obj_Msdan,      "d_a_obj_msdan"},
    {PROC_Obj_MsdanSub,   "d_a_obj_msdan_sub"},
    {PROC_Obj_Msdan2,     "d_a_obj_msdan2"},
    {PROC_Obj_MsdanSub2,  "d_a_obj_msdan_sub2"},
    {PROC_Obj_Nest,       "d_a_obj_nest"},
    {PROC_Obj_Ojtree,     "d_a_obj_ojtree"},
    {PROC_Obj_Ospbox,     "d_a_obj_ospbox"},
    {PROC_Obj_Ladder,     "d_a_obj_ladder"},
    {PROC_Obj_Smplbg,     "d_a_obj_smplbg"},
    {PROC_Obj_Akabe,      "d_a_obj_akabe"},
    {PROC_Obj_Ashut,      "d_a_obj_ashut"},
    {PROC_BRIDGE,         "d_a_bridge"},
    {PROC_MSW,            "d_a_msw"},
    {PROC_MFLFT,          "d_a_mflft"},
    {PROC_KLFT,           "d_a_klft"},
    {PROC_ICE_LIFT,       "d_a_icelift"},
    {PROC_AMI_PROP,       "d_a_amiprop"},
    {PROC_PEDESTAL,       "d_a_pedestal"},
    {PROC_FLOOR,          "d_a_floor"},
    {PROC_KITA,           "d_a_kita"},
    {PROC_KOKIIE,         "d_a_kokiie"},
    {PROC_SHAND,          "d_a_shand"},
    {PROC_BITA,           "d_a_bita"},
    {PROC_SK,             "d_a_sk"},
    {PROC_SK2,            "d_a_sk2"},
    {PROC_SSK,            "d_a_ssk"},
    {PROC_WARPFLOWER,     "d_a_warpf"},
    {PROC_WARPFOUT,       "d_a_warpfout"},
    {PROC_WARPLIGHT,      "d_a_warpls"},
    {PROC_WARPHYRULE,     "d_a_warphr"},
    {PROC_WARPDEMO20,     "d_a_warpdm20"},
    {PROC_WARPGANON,      "d_a_warpgn"},
    {PROC_WARPMAJYUU,     "d_a_warpmj"},
    {PROC_Balancelift,    "d_a_obj_balancelift"},
    {PROC_SHUTTER,        "d_a_shutter"},
    {PROC_SHUTTER2,       "d_a_shutter2"},
    {PROC_WINDMILL,       "d_a_windmill"},
    {PROC_MBDOOR,         "d_a_mbdoor"},
    {PROC_NPC_DE1,        "d_a_npc_de1"},
    {PROC_NPC_NZ,         "d_a_npc_nz"},
    {PROC_NPC_SO,         "d_a_npc_so"},
    {PROC_FM,             "d_a_fm"},
    {PROC_LEAF_LIFT,      "d_a_leaflift"},
    {PROC_Obj_Roten,      "d_a_obj_roten"},
    {PROC_TOGE,           "d_a_toge"},
    {PROC_Obj_Ferris,     "d_a_obj_ferris"},
    {PROC_Obj_Xfuta,      "d_a_obj_xfuta"},
    {PROC_Obj_Gaship,     "d_a_obj_gaship"},
    {PROC_Obj_Rforce,     "d_a_obj_rforce"},
    {PROC_Obj_Gaship2,    "d_a_obj_gaship2"},
    {PROC_Obj_Light,      "d_a_obj_light"},
    {PROC_Obj_Homen,      "d_a_obj_homen"},
    {PROC_Obj_Homensmk,   "d_a_obj_homensmoke"},
    {PROC_Obj_Ftree,      "d_a_obj_ftree"},
    {PROC_Obj_Vds,        "d_a_obj_Vds"},
    {PROC_Obj_Vyasi,      "d_a_obj_vyasi"},
    {PROC_Obj_Ajav,       "d_a_obj_ajav"},
    {PROC_Obj_Trap,       "d_a_obj_trap"},
    {PROC_Obj_Hha,        "d_a_obj_hha"},
    {PROC_Obj_Htetu1,     "d_a_obj_htetu1"},
    {PROC_Obj_Gnntakis,   "d_a_obj_gnndemotakis"},
    {PROC_Obj_Gnntakie,   "d_a_obj_gnndemotakie"},
    {PROC_Obj_Gnnbtaki,   "d_a_obj_gnnbtltaki"},
    {PROC_Obj_Rcloud,     "d_a_obj_rcloud"},
    {PROC_Obj_Gryw00,     "d_a_obj_gryw00"},
    {PROC_Obj_AjavW,      "d_a_obj_AjavW"},
    {PROC_Obj_Leaves,     "d_a_obj_leaves"},
    {PROC_Obj_YLzou,      "d_a_obj_YLzou"},
    {PROC_Obj_Gbed,       "d_a_obj_ganonbed"},
    {PROC_Obj_Vteng,      "d_a_obj_Vteng"},
    {PROC_Obj_Hfuck1,     "d_a_obj_hfuck1"},
    {PROC_Obj_Ohatch,     "d_a_obj_ohatch"},
    {PROC_Obj_Hcbh,       "d_a_obj_hcbh"},
    {PROC_Obj_Ygush00,    "d_a_obj_Ygush00"},
    {PROC_Obj_Bscurtain,  "d_a_obj_bscurtain"},
    {PROC_Obj_Shmrgrd,    "d_a_obj_shmrgrd"},
    {PROC_Obj_Eayogn,     "d_a_obj_eayogn"},
    {PROC_Obj_Vmsms,      "d_a_obj_vmsms"},
    {PROC_Obj_Vmsdz,      "d_a_obj_vmsdz"},
    {PROC_Ygcwp,          "d_a_ygcwp"},
    {PROC_Obj_Vgnfd,      "d_a_obj_vgnfd"},
    {PROC_Obj_Kanoke,     "d_a_obj_kanoke"},
    {PROC_Obj_Eskban,     "d_a_obj_eskban"},
    {PROC_Obj_Ekskz,      "d_a_obj_ekskz"},
    {PROC_Obj_Ebomzo,     "d_a_obj_ebomzo"},
    {PROC_Obj_Kanat,      "d_a_obj_kanat"},
    {PROC_Obj_Aygr,       "d_a_obj_aygr"},
    {PROC_SHIP,           "d_a_ship"},
    {PROC_Obj_Jump,       "d_a_obj_jump"},
    {PROC_NPC_MK,         "d_a_npc_mk"},
    {PROC_SAIL,           "d_a_sail"},
    {PROC_PIRATE_FLAG,    "d_a_pirate_flag"},
    {PROC_MAJUU_FLAG,     "d_a_majuu_flag"},
    {PROC_Tori_Flag,      "d_a_tori_flag"},
    {PROC_Sie_Flag,       "d_a_sie_flag"},
    {PROC_SYAN,           "d_a_syan"},
    {PROC_AYUSH,          "d_a_ghostship"},
    {PROC_OSHIP,          "d_a_oship"},
    {PROC_RECTANGLE,      "d_a_rectangle"},
    {PROC_BB,             "d_a_bb"},
    {PROC_KANBAN,         "d_a_kanban"},
    {PROC_HITOBJ,         "d_a_hitobj"},
    {PROC_KT,             "d_a_kt"},
    {PROC_EP,             "d_a_ep"},
    {PROC_LAMP,           "d_a_lamp"},
    {PROC_FF,             "d_a_ff"},
    {PROC_MO2,            "d_a_mo2"},
    {PROC_BK,             "d_a_bk"},
    {PROC_ST,             "d_a_st"},
    {PROC_TN,             "d_a_tn"},
    {PROC_MANT,           "d_a_mant"},
    {PROC_KANTERA,        "d_a_kantera"},
    {PROC_KAMOME,         "d_a_kamome"},
    {PROC_NPC_KAM,        "d_a_npc_kamome"},
    {PROC_WBIRD,          "d_a_wbird"},
    {PROC_DEMO_KMM,       "d_a_demo_kmm"},
    {PROC_NZ,             "d_a_nz"},
    {PROC_NZG,            "d_a_nzg"},
    {PROC_KN,             "d_a_kn"},
    {PROC_DEMO_DK,        "d_a_demo_dk"},
    {PROC_AM,             "d_a_am"},
    {PROC_AM2,            "d_a_am2"},
    {PROC_GM,             "d_a_gm"},
    {PROC_KS,             "d_a_ks"},
    {PROC_CC,             "d_a_cc"},
    {PROC_BL,             "d_a_bl"},
    {PROC_WZ,             "d_a_wz"},
    {PROC_PH,             "d_a_ph"},
    {PROC_PZ,             "d_a_pz"},
    {PROC_BPW,            "d_a_bpw"},
    {PROC_PW,             "d_a_pw"},
    {PROC_JBO,            "d_a_jbo"},
    {PROC_BO,             "d_a_bo"},
    {PROC_KI,             "d_a_ki"},
    {PROC_MT,             "d_a_mt"},
    {PROC_BWD,            "d_a_bwd"},
    {PROC_BWDS,           "d_a_bwds"},
    {PROC_BWDG,           "d_a_bwdg"},
    {PROC_KB,             "d_a_kb"},
    {PROC_DR,             "d_a_dr"},
    {PROC_DR2,            "d_a_dr2"},
    {PROC_RD,             "d_a_rd"},
    {PROC_DAIOCTA,        "d_a_daiocta"},
    {PROC_DAIOCTA_EYE,    "d_a_daiocta_eye"},
    {PROC_OQ,             "d_a_oq"},
    {PROC_GY,             "d_a_gy"},
    {PROC_GY_CTRL,        "d_a_gy_ctrl"},
    {PROC_GY_CTRLB,       "d_a_gy_ctrl"},
    {PROC_Hot_Floor,      "d_a_hot_floor"},
    {PROC_Beam,           "d_a_beam"},
    {PROC_Bemos,          "d_a_obj_bemos"},
    {PROC_BTD,            "d_a_btd"},
    {PROC_BMD,            "d_a_bmd"},
    {PROC_BMDHAND,        "d_a_bmdhand"},
    {PROC_BMDFOOT,        "d_a_bmdfoot"},
    {PROC_DK,             "d_a_dk"},
    {PROC_BDK,            "d_a_bdk"},
    {PROC_BDKOBJ,         "d_a_bdkobj"},
    {PROC_BST,            "d_a_bst"},
    {PROC_FGANON,         "d_a_fganon"},
    {PROC_FGMAHOU,        "d_a_fgmahou"},
    {PROC_BGN,            "d_a_bgn"},
    {PROC_BGN2,           "d_a_bgn2"},
    {PROC_BGN3,           "d_a_bgn3"},
    {PROC_GND,            "d_a_gnd"},
    {PROC_PT,             "d_a_pt"},
    {PROC_SWTDOOR,        "d_a_swtdoor"},
    {PROC_MOZO,           "d_a_mozo"},
    {PROC_KUI,            "d_a_kui"},
    {PROC_SS,             "d_a_ss"},
    {PROC_SSS,            "d_a_sss"},
    {PROC_SITEM,          "d_a_sitem"},
    {PROC_MACHINE,        "d_a_machine"},
    {PROC_BOSSITEM,       "d_a_boss_item"},
    {PROC_Demo_Item,      "d_a_demo_item"},
    {PROC_RACEITEM,       "d_a_race_item"},
    {PROC_ShopItem,       "d_a_shop_item"},
    {PROC_DEKU_ITEM,      "d_a_deku_item"},
    {PROC_Obj_Paper,      "d_a_obj_paper"},
    {PROC_Obj_Demo_Barrel,"d_a_obj_demo_barrel"},
    {PROC_Obj_Dmgroom,    "d_a_obj_dmgroom"},
    {PROC_Obj_Doguu,      "d_a_obj_doguu"},
    {PROC_Obj_Wood,       "d_a_obj_wood"},
    {PROC_Obj_Flame,      "d_a_obj_flame"},
    {PROC_Obj_Buoyrace,   "d_a_obj_buoyrace"},
    {PROC_Obj_Coming,     "d_a_obj_coming"},
    {PROC_Coming2,        "d_a_coming2"},
    {PROC_Coming3,        "d_a_coming3"},
    {PROC_Obj_Mmrr,       "d_a_obj_mmrr"},
    {PROC_Obj_Pbka,       "d_a_obj_pbka"},
    {PROC_Obj_Plant,      "d_a_obj_plant"},
    {PROC_Obj_Gtaki,      "d_a_obj_gtaki"},
    {PROC_Obj_Yboil,      "d_a_obj_Yboil"},
    {PROC_Obj_Rflw,       "d_a_obj_rflw"},
    {PROC_Obj_Table,      "d_a_obj_table"},
    {PROC_Obj_Tenmado,    "d_a_obj_tenmado"},
    {PROC_Obj_Cafelmp,    "d_a_obj_cafelmp"},
    {PROC_Obj_Apzl,       "d_a_obj_apzl"},
    {PROC_Obj_Adnno,      "d_a_obj_adnno"},
    {PROC_Obj_Auzu,       "d_a_obj_auzu"},
    {PROC_Obj_Gong,       "d_a_obj_gong"},
    {PROC_Obj_Barrier,    "d_a_obj_barrier"},
    {PROC_Obj_Firewall,   "d_a_obj_firewall"},
    {PROC_Obj_TnTrap,     "d_a_obj_tntrap"},
    {PROC_Obj_Monument,   "d_a_obj_monument"},
    {PROC_Obj_Tapestry,   "d_a_obj_tapestry"},
    {PROC_Obj_HSH,        "d_a_obj_hsehi1"},
    {PROC_Goal_Flag,      "d_a_goal_flag"},
    {PROC_TBOX,           "d_a_tbox"},
    {PROC_SBOX,           "d_a_sbox"},
    {PROC_BOMB_FLOWER,    "d_a_bflower"},
    {PROC_ACORN_LEAF,     "d_a_acorn_leaf"},
    {PROC_SWC00,          "d_a_swc00"},
    {PROC_FAN,            "d_a_fan"},
    {PROC_DOOR10,         "d_a_door10"},
    {PROC_DOOR12,         "d_a_door12"},
    {PROC_ATDOOR,         "d_a_atdoor"},
    {PROC_MDOOR,          "d_a_mdoor"},
    {PROC_KDDOOR,         "d_a_kddoor"},
    {PROC_KNOB00,         "d_a_knob00"},
    {PROC_MTOGE,          "d_a_mtoge"},
    {PROC_ANDSW0,         "d_a_andsw0"},
    {PROC_ANDSW2,         "d_a_andsw2"},
    {PROC_DAI,            "d_a_dai"},
    {PROC_SW_ATTACK,      "d_a_swattack"},
    {PROC_SW_ITEM,        "d_a_switem"},
    {PROC_SW_TACT,        "d_a_swtact"},
    {PROC_NPC_OS,         "d_a_npc_os"},
    {PROC_NPC_YM1,        "d_a_npc_ym1"},
    {PROC_NPC_YM2,        "d_a_npc_ym1"},
    {PROC_NPC_YW1,        "d_a_npc_yw1"},
    {PROC_NPC_JI1,        "d_a_npc_ji1"},
    {PROC_NPC_KO1,        "d_a_npc_ko1"},
    {PROC_NPC_KO2,        "d_a_npc_ko1"},
    {PROC_NPC_LS1,        "d_a_npc_ls1"},
    {PROC_NPC_P1,         "d_a_npc_p1"},
    {PROC_NPC_P2,         "d_a_npc_p2"},
    {PROC_NPC_SARACE,     "d_a_npc_sarace"},
    {PROC_NPC_TC,         "d_a_npc_tc"},
    {PROC_NPC_BM1,        "d_a_npc_bm1"},
    {PROC_NPC_BM2,        "d_a_npc_bm1"},
    {PROC_NPC_BM3,        "d_a_npc_bm1"},
    {PROC_NPC_BM4,        "d_a_npc_bm1"},
    {PROC_NPC_BM5,        "d_a_npc_bm1"},
    {PROC_NPC_OB1,        "d_a_npc_ob1"},
    {PROC_NPC_AJ1,        "d_a_npc_aj1"},
    {PROC_NPC_KM1,        "d_a_npc_km1"},
    {PROC_NPC_CB1,        "d_a_npc_cb1"},
    {PROC_NPC_BA1,        "d_a_npc_ba1"},
    {PROC_NPC_BJ1,        "d_a_npc_bj1"},
    {PROC_NPC_BJ2,        "d_a_npc_bj1"},
    {PROC_NPC_BJ3,        "d_a_npc_bj1"},
    {PROC_NPC_BJ4,        "d_a_npc_bj1"},
    {PROC_NPC_BJ5,        "d_a_npc_bj1"},
    {PROC_NPC_BJ6,        "d_a_npc_bj1"},
    {PROC_NPC_BJ7,        "d_a_npc_bj1"},
    {PROC_NPC_BJ8,        "d_a_npc_bj1"},
    {PROC_NPC_BJ9,        "d_a_npc_bj1"},
    {PROC_NPC_BS1,        "d_a_npc_bs1"},
    {PROC_NPC_BMCON1,     "d_a_npc_bmcon1"},
    {PROC_NPC_BMS1,       "d_a_npc_bms1"},
    {PROC_NPC_BMSW,       "d_a_npc_bmsw"},
    {PROC_NPC_BTSW,       "d_a_npc_btsw"},
    {PROC_NPC_BTSW2,      "d_a_npc_btsw2"},
    {PROC_NPC_DS1,        "d_a_npc_ds1"},
    {PROC_NPC_RSH1,       "d_a_npc_rsh1"},
    {PROC_NPC_KK1,        "d_a_npc_kk1"},
    {PROC_NPC_PM1,        "d_a_npc_pm1"},
    {PROC_NPC_KP1,        "d_a_npc_kp1"},
    {PROC_NPC_PF1,        "d_a_npc_pf1"},
    {PROC_NPC_GP1,        "d_a_npc_gp1"},
    {PROC_NPC_JB1,        "d_a_npc_jb1"},
    {PROC_NPC_KF1,        "d_a_npc_kf1"},
    {PROC_NPC_AUCTION,    "d_a_npc_auction"},
    {PROC_NPC_KG1,        "d_a_npc_kg1"},
    {PROC_NPC_KG2,        "d_a_npc_kg2"},
    {PROC_NPC_TT,         "d_a_npc_tt"},
    {PROC_NPC_HR,         "d_a_npc_hr"},
    {PROC_NPC_HO,         "d_a_npc_ho"},
    {PROC_NPC_MD,         "d_a_npc_md"},
    {PROC_NPC_UK,         "d_a_npc_uk"},
    {PROC_BIGELF,         "d_a_bigelf"},
    {PROC_NPC_CO1,        "d_a_npc_co1"},
    {PROC_NPC_ZK1,        "d_a_npc_zk1"},
    {PROC_NPC_ROTEN,      "d_a_npc_roten"},
    {PROC_NPC_PEOPLE,     "d_a_npc_people"},
    {PROC_NPC_GK1,        "d_a_npc_gk1"},
    {PROC_NPC_PHOTO,      "d_a_npc_photo"},
    {PROC_NPC_AC1,        "d_a_npc_ac1"},
    {PROC_NPC_HI1,        "d_a_npc_hi1"},
    {PROC_NPC_SV,         "d_a_npc_sv"},
    {PROC_NPC_MT,         "d_a_npc_mt"},
    {PROC_NPC_MN,         "d_a_npc_mn"},
    {PROC_NPC_AH,         "d_a_npc_ah"},
    {PROC_AUCTION,        "d_a_auction"},
    {PROC_KYTAG00,        "d_a_kytag00"},
    {PROC_KYTAG01,        "d_a_kytag01"},
    {PROC_KYTAG02,        "d_a_kytag02"},
    {PROC_KYTAG03,        "d_a_kytag03"},
    {PROC_KYTAG04,        "d_a_kytag04"},
    {PROC_KYTAG05,        "d_a_kytag05"},
    {PROC_KYTAG06,        "d_a_kytag06"},
    {PROC_KYTAG07,        "d_a_kytag07"},
    {PROC_WindTag,        "d_a_wind_tag"},
    {PROC_YOUGAN,         "d_a_yougan"},
    {PROC_Mmusic,         "d_a_mmusic"},
    {PROC_Komore,         "d_a_komore"},
    {PROC_Tpota,          "d_a_tpota"},
    {PROC_Obj_Itnak,      "d_a_obj_Itnak"},
    {PROC_Obj_Zouk,       "d_a_obj_zouK"},
    {PROC_Ykgr,           "d_a_ykgr"},
    {PROC_SAKU,           "d_a_saku"},
    {PROC_Salvage,        "d_a_salvage"},
    {PROC_SALVAGE_TBOX,   "d_a_salvage_tbox"},
    {PROC_Kmon,           "d_a_kmon"},
    {PROC_OBJ_FIGURE,     "d_a_obj_figure"},
    {PROC_OBJ_HAT,        "d_a_obj_hat"},
    {PROC_Lwood,          "d_a_lwood"},
    {PROC_Dummy,          "d_a_dummy"},
    {PROC_TAG_EVENT,      "d_a_tag_event"},
    {PROC_TAG_HINT,       "d_a_tag_hint"},
    {PROC_TAG_MSG,        "d_a_tag_msg"},
    {PROC_TAG_ETC,        "d_a_tag_etc"},
    {PROC_TAG_ISLAND,     "d_a_tag_island"},
    {PROC_TAG_KF1,        "d_a_tag_kf1"},
    {PROC_TAG_KK1,        "d_a_tag_kk1"},
    {PROC_TAG_PHOTO,      "d_a_tag_photo"},
    {PROC_TAG_KB_ITEM,    "d_a_tag_kb_item"},
    {PROC_TAG_MK,         "d_a_tag_mk"},
    {PROC_TAG_MDCB,       "d_a_tag_md_cb"},
    {PROC_TAG_BA1,        "d_a_tag_ba1"},
    {PROC_TagRock,        "d_a_fallrock_tag"},
    {PROC_FallRock,       "d_a_fallrock"},
    {PROC_SteamTag,       "d_a_steam_tag"},
    {PROC_Fire,           "d_a_fire"},
    {PROC_BRANCH,         "d_a_branch"},
    {PROC_NPC_ZL1,        "d_a_npc_zl1"},
    {PROC_WATERFALL,      "d_a_waterfall"},
    {PROC_LIGHTBRIDGE,    "d_a_lbridge"},
    {PROC_LIGHTSTAIR,     "d_a_lstair"},
    {PROC_WALL,           "d_a_wall"},
    {PROC_SW_PROPELLER,   "d_a_swpropeller"},
    {PROC_IKARI,          "d_a_ikari"},
    {PROC_AGBSW0,         "d_a_agbsw0"},
    {PROC_MAGMA,          "d_a_magma"},
    {PROC_GRASS,          "d_a_grass"},
    {PROC_Obj_Tower,      "d_a_obj_tower"},
    {PROC_Obj_DoguuD,     "d_a_obj_doguu_demo"},
    {PROC_SPOTBOX,        "d_a_spotbox"},
    {PROC_TORNADO,        "d_a_tornado"},
    {PROC_TITLE,          "d_a_title"},
    {PROC_MP,             "d_a_movie_player"},
    {PROC_LODBG,          "d_a_lod_bg"},
    {PROC_HIMO3,          "d_a_himo3"},
    {PROC_ATT,            "d_a_att"},
    {PROC_Hys,            "d_a_hys"},
    {PROC_SWHIT0,         "d_a_swhit0"},
    {PROC_TAG_GSHIP,      "d_a_tag_ghostship"},
    {PROC_TSUBO,          "d_a_tsubo"},
    {PROC_STONE,          "d_a_stone"},
    {PROC_Stone2,         "d_a_stone2"},
    {PROC_Obj_Barrel,     "d_a_obj_barrel"},
    {PROC_Obj_Barrel2,    "d_a_obj_barrel2"},
    {PROC_Obj_Try,        "d_a_obj_try"},
    {PROC_Obj_Vtil,       "d_a_obj_vtil"},
    {PROC_Obj_Ice,        "d_a_obj_ice"},
    {PROC_Obj_Mshokki,    "d_a_obj_mshokki"},
    {PROC_BOKO,           "d_a_boko"},
    {PROC_TAMA,           "d_a_tama"},
    {PROC_Obj_Buoyflag,   "d_a_obj_buoyflag"},
    {PROC_Obj_Correct,    "d_a_obj_correct"},
    {PROC_Obj_Eff,        "d_a_obj_eff"},
    {PROC_Tag_Light,      "d_a_tag_light"},
    {PROC_Tag_Attention,  "d_a_tag_attention"},
    {PROC_Tag_Waterlevel, "d_a_tag_waterlevel"},
    {PROC_ARROW_ICEEFF,   "d_a_arrow_iceeff"},
    {PROC_ARROW_LIGHTEFF, "d_a_arrow_lighteff"},
    {PROC_Obj_Timer,      "d_a_obj_timer"},

    {0xFFFF, NULL},
};

/* 800227A0-800229E0       .text cCc_Init__Fv */
s32 cCc_Init() {
    JUT_ASSERT(0x2a, !DMC_initialized);

    JKRSolidHeap * pHeap = JKRSolidHeap::create(0x5648, mDoExt_getArchiveHeap(), false);
    JKRHeap * pOldHeap = pHeap->becomeCurrentHeap();
    memset(DMC, 0, sizeof(DMC));

    for (int i = 0; i < ARRAY_SIZE(DynamicNameTable); i++) {
        const DynamicNameTableEntry & d = DynamicNameTable[i];
        if (d.name == NULL)
            continue;

        JUT_ASSERT(0x39, d.mKey < (sizeof(DMC) / sizeof(DMC[0])));
        JUT_ASSERT(0x3a, DMC[d.mKey] == 0);

        for (int j = 0; j < ARRAY_SIZE(DMC); j++) {
            if (DMC[j] != NULL) {
                if (!strcmp(d.name, DMC[j]->getModuleName())) {
                    DMC[d.mKey] = DMC[j];
                    break;
                }
            }
        }

        if (DMC[d.mKey] == NULL)
            DMC[d.mKey] = new DynamicModuleControl(d.name);
    }

    pHeap->adjustSize();
    pOldHeap->becomeCurrentHeap();
    DMC_initialized = TRUE;
    return TRUE;
}

/* 800229E0-80022A80       .text cDyl_IsLinked__Fs */
s32 cDyl_IsLinked(s16 i_ProfName) {
    JUT_ASSERT(0xae, cDyl_Initialized);

    if (DMC[i_ProfName] != NULL)
        return DMC[i_ProfName]->isLinked();

    return TRUE;
}

/* 80022A80-80022B58       .text cDyl_Unlink__Fs */
s32 cDyl_Unlink(s16 i_ProfName) {
    JUT_ASSERT(0xc5, cDyl_Initialized);
    JUT_ASSERT(0xc6, i_ProfName < (sizeof(DMC) / sizeof(DMC[0])));

    if (DMC[i_ProfName] != NULL)
        return DMC[i_ProfName]->unlink();

    return 0;
}

static void dummy(s16 i_ProfName) {
    OSReport_Error("cDyl_Link i_ProfName=%d\n", i_ProfName);
    OSReport_Error("cDyl_LinkASync: リンクに失敗しました。諦めます\n");
}

/* 80022B58-80022CEC       .text cDyl_LinkASync__Fs */
s32 cDyl_LinkASync(s16 i_ProfName) {
    JUT_ASSERT(0x101, DMC_initialized);

    if (!cDyl_Initialized)
        return cPhs_INIT_e;

    if (i_ProfName >= ARRAY_SIZE(DMC)) {
        OSReport_Error("cDyl_Link i_ProfName=%d\n", i_ProfName);
        return cPhs_ERROR_e;
    }

    JUT_ASSERT(0x111, i_ProfName < (sizeof(DMC) / sizeof(DMC[0])));
    DynamicModuleControlBase * d = DMC[i_ProfName];
    if (d != NULL) {
        JUT_ASSERT(0x115, cDyl_Initialized);
        if (d->load_async()) {
            if (d->link()) {
                return cPhs_COMPLEATE_e;
            } else {
                OSReport_Error("cDyl_LinkASync: リンクに失敗しました。諦めます\n");
                return cPhs_ERROR_e;
            }
        }

        return cPhs_INIT_e;
    }

    return cPhs_COMPLEATE_e;
}

/* 80022CEC-80022DF8       .text cDyl_InitCallback__FPv */
BOOL cDyl_InitCallback(void*) {
    JUT_ASSERT(0x12f, !cDyl_Initialized);
    JKRFileLoader * pFileLoader = JKRFileCache::mount("/", mDoExt_getArchiveHeap(), NULL);
    DynamicModuleControl::initialize();
    void * pData = JKRFileLoader::getGlbResource("/dvd/framework.str");
    JKRFileLoader::detachResource(pData, pFileLoader);
    pFileLoader->unmount();
    OSSetStringTable(pData);

    DynamicModuleControl dmc("f_pc_profile_lst");
    dmc.link();
    cDyl_Initialized = TRUE;
    return TRUE;
}

/* 80022DF8-80022E70       .text cDyl_InitAsync__Fv */
void cDyl_InitAsync() {
    cCc_Init();

    JUT_ASSERT(0x145, cDyl_DVD == 0);
    cDyl_DVD = mDoDvdThd_callback_c::create((mDoDvdThd_callback_func) cDyl_InitCallback, NULL);
}

/* 80022E70-80022EDC       .text cDyl_InitAsyncIsDone__Fv */
int cDyl_InitAsyncIsDone() {
    if (cDyl_DVD == NULL)
        return TRUE;

    if (cDyl_DVD->sync()) {
        cDyl_DVD->destroy();
        cDyl_DVD = NULL;
        return TRUE;
    }

    return FALSE;
}

/* 80022EDC-80022EE4       .text phase_01__7cDylPhsFPv */
int cDylPhs::phase_01(void*) {
    return cPhs_NEXT_e;
}

/* 80022EE4-80022F1C       .text phase_02__7cDylPhsFPs */
int cDylPhs::phase_02(s16* pProf) {
    s32 ret = cDyl_LinkASync(*pProf);
    return ret == cPhs_COMPLEATE_e ? cPhs_NEXT_e : ret;
}

/* 80022F1C-80022F24       .text phase_03__7cDylPhsFPv */
int cDylPhs::phase_03(void*) {
    return cPhs_INIT_e;
}

/* 80022F24-80022F68       .text Link__7cDylPhsFP30request_of_phase_process_classs */
int cDylPhs::Link(request_of_phase_process_class* i_phase, s16 profName) {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler) &cDylPhs::phase_01,
        (cPhs__Handler) &cDylPhs::phase_02,
        (cPhs__Handler) &cDylPhs::phase_03,
    };

    if (i_phase->id == cPhs_NEXT_e)
        return cPhs_COMPLEATE_e;

    return dComLbG_PhaseHandler(i_phase, l_method, &profName);
}

/* 80022F68-80023004       .text Unlink__7cDylPhsFP30request_of_phase_process_classs */
int cDylPhs::Unlink(request_of_phase_process_class* i_phase, s16 profName) {
    JUT_ASSERT(0x1a6, i_phase->id != 1);

    s32 ret;
    if (i_phase->id == cPhs_NEXT_e) {
        ret = cDyl_Unlink(profName);
        i_phase->id = cPhs_INIT_e;
    } else {
        ret = cPhs_INIT_e;
    }
    return ret;
}
