/**
 * d_meter.cpp
 * HUD (hearts, magic meter, button icons, etc.)
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_meter.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JKernel/JKRExpHeap.h" // IWYU pragma: keep
#include "d/d_camera.h"
#include "d/d_file_error.h"
#include "d/d_kankyo_wether.h"
#include "d/d_priority.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_npc_cb1.h"
#include "d/actor/d_a_npc_ji1.h"
#include "d/actor/d_a_npc_kamome.h"
#include "d/actor/d_a_npc_md.h"
#include "d/actor/d_a_npc_so.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_s_play.h"
#include "f_op/f_op_overlap_mng.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_metronome.h"
#include "d/d_procname.h"
#include "d/d_timer.h"
#include "m_Do/m_Do_lib.h"
#include "stdio.h"

dMeter_info_c dMeter_Info;
fopMsgM_pane_class item_parts;
dMeter_map_HIO_c g_meter_mapHIO;
dMeter_HIO_c g_meterHIO;
dMeter_menuHIO_c g_menuHIO;
dMeter_msg_HIO_c g_msgHIO;
dMeter_message_HIO_c g_messageHIO;
dMetronome_c* dMn_c;
J2DScreen* sMainParts1;
J2DScreen* sMainParts2;
J2DScreen* sMainParts3;
J2DScreen* sScrTimer1;
J2DScreen* sScrTimer2;
J2DScreen* sChoiceRoad;
J2DPicture* moveItemPane;
u8 mapAlpha;
u8 menu_status;
u8 menu_status_old;
u8 dMenu_pause;
int dMenu_frame_timer;
u8 dMenu_menuButton;
bool subWinFlag;
bool dMeter_auctionFlag;
u8 dMeter_itemMoveFlag;
u8 dMeter_btn_chk;
u8 dMeter_itemNum;
s16 dMeter_itemTimer;
f32 texRateX;
f32 texRateY;
f32 texScaleX;
f32 texScaleY;
u8 dMenu_menuFlag;
u8 dMenu_baitNum[8];
u8 dMeter_place_name;
u8 dMeter_itemMode;
u8 dMeter_collectMode;
fpc_ProcID dMeter_windID = fpcM_ERROR_PROCESS_ID_e;
u8 dMeter_windStatus;
u8 rupy_soundSetFlag;
u8 rupy_soundOnFlag;
mapCtrlDisp_c dMeter_mMapCtrlDisp;
dDlst_2DMETER1_c meter1;
dDlst_2DMETER2_c meter2;
dDlst_2Dm_c tekari;
dDlst_2Dm_c clock[3];

static void dummy(f32* m, u32 p2, s32 p3) {
    OSReport("cmap_tri.bti");
    OSReport("cmap_treasure.bti");
    OSReport("cmap_tingle.bti");
    OSReport("cmap_phantomship.bti");
    OSReport("cmap_hint.bti");
    OSReport("f_item_tri.bti");
    OSReport("f_get_rupy.bti");
    OSReport("f_heart_up_02.bti");
    OSReport("f_korog_kare.bti");
    OSReport("f_korog_saki.bti");
    m[0] = 0.8f;
    m[1] = 0.0f;
    m[2] = 1.2f;
    m[3] = 0.1f;
    m[4] = 1.0f;
    m[5] = 1.1f;
    m[6] = 255.0f;
    m[7] = -1.0f;
    m[8] = 452.0f;
    m[9] = p2;
    m[10] = p3;
}

static const char* arrowTexImage[] = {
    "arrow_00.bti",
    "arrow_01.bti",
    "arrow_02.bti",
    "arrow_03.bti",
};

/* 801EEFDC-801EF360       .text __ct__12dMeter_HIO_cFv */
dMeter_HIO_c::dMeter_HIO_c() {
    field_0x6 = 10;
    field_0x62 = 0;
    field_0x63 = 0;
    field_0xc = 1.0f;
    field_0x10 = 1.4f;
    field_0x14 = 0.0f;
    field_0x18 = -29.0f;
    field_0x1c = 1.0f;
    field_0x36 = 0x16;
    field_0x3c = 0.65f;
    field_0x38 = 0;
    field_0x2e = 0;
    field_0x30 = 0;
    field_0x32 = 0;
    field_0x34 = 0;
    field_0x2c = 0xff;
    field_0x20 = 1.5f;
    field_0x24 = 150.0f;
    field_0x2d = 0x8c;
    field_0x40 = 0x5a;
    field_0x42 = 100;
    field_0x44 = 100;
    field_0x46 = 0x5a;
    field_0x50 = 7;
    field_0x52 = 0xfff4;
    field_0x48 = 1.8f;
    field_0x4c = 12.0f;
    field_0x54 = 0;
    field_0x56 = 0xffa8;
    field_0x58 = 2.3f;
    field_0x5c = 12.0f;
    field_0x60 = 0x96;
    field_0x61 = 100;
    field_0x64 = 0;
    field_0x66 = 0;
    field_0x68 = 0;
    field_0x6a = 0;
    field_0x88 = 0xf;
    field_0x8a = 5;
    field_0x8c = 5;
    field_0x8e = 5;
    field_0x90 = 0x14;
    field_0x92 = 0xc;
    field_0x94 = 3;
    field_0x96 = 3;
    field_0x98 = 3;
    field_0x9a = 0;
    field_0x120 = 0x8c;
    field_0x121 = 200;
    field_0x122 = 0x96;
    field_0x126 = 10;
    field_0x128 = 6;
    field_0x12a = 3;
    field_0x12c = 3;
    field_0x12e = 2;
    field_0x130 = 0x14;
    field_0x132 = 0x27;
    field_0x7e = 0x14;
    field_0x136 = 4;
    field_0x138 = 10;
    field_0x13a = 0;
    field_0x13c = 10;
    field_0x142 = 0xb4;
    field_0x143 = 0;
    field_0x144 = 0;
    field_0x145 = 0xff;
    field_0x146 = 0;
    field_0x147 = 0;
    field_0x148 = 0;
    field_0x149 = 0;
    field_0x123 = 1;
    field_0x134 = 3;
    field_0x13e = 0;
    field_0x14a = 0xff;
    field_0x14b = 0x32;
    field_0x14c = 0x32;
    field_0x14e = 10;
    field_0x150 = 0x14;
    field_0x152 = 4;
    field_0x154 = 0x32;
    field_0x28 = 2.1f;
    field_0x124 = 5;
    field_0x140 = 0;
    field_0xa0 = 0;
    field_0xa8 = 0;
    field_0xa2 = 0x3c;
    field_0xaa = 0xffc4;
    field_0xa4 = 0;
    field_0xac = 0;
    field_0xa6 = 0;
    field_0xae = 0;
    field_0xb0 = 0x19;
    field_0xb8 = 0xffe2;
    field_0xb2 = 0x23;
    field_0xba = 0xffea;
    field_0xb4 = 0xffdf;
    field_0xbc = 0xfffb;
    field_0xb6 = 0xfffa;
    field_0xbe = 0;
    field_0xc0 = 0;
    field_0xc8 = 0xffec;
    field_0xc2 = 0;
    field_0xca = 0xffec;
    field_0xc4 = 0;
    field_0xcc = 0xffec;
    field_0xc6 = 0;
    field_0xce = 0;
    field_0xd0 = 0x28;
    field_0xd8 = 0xffc4;
    field_0xd2 = 0x28;
    field_0xda = 0xffc4;
    field_0xd4 = 0;
    field_0xdc = 0;
    field_0xd6 = 0;
    field_0xde = 0;
    field_0xe0 = 0x19;
    field_0xe8 = 0xffe2;
    field_0xe2 = 0x23;
    field_0xea = 0xffea;
    field_0xe4 = 0;
    field_0xec = 0xffc4;
    field_0xe6 = 0xfffa;
    field_0xee = 0;
    field_0xf0 = 0;
    field_0xf8 = 0;
    field_0xf2 = 0;
    field_0xfa = 0;
    field_0xf4 = 0;
    field_0xfc = 0;
    field_0xf6 = 0;
    field_0xfe = 0;
    field_0x100 = 0;
    field_0x108 = 0xffc4;
    field_0x102 = 0;
    field_0x10a = 0xffc4;
    field_0x104 = 0x32;
    field_0x10c = 0xffb8;
    field_0x106 = 0x32;
    field_0x10e = 0xffaf;
    field_0x110 = 0;
    field_0x118 = 0xffeb;
    field_0x112 = 0x11;
    field_0x11a = 0xfff4;
    field_0x114 = 0xffe2;
    field_0x11c = 0xfff5;
    field_0x116 = 0xff9e;
    field_0x11e = 7;
    field_0x9c = 0;
    field_0x9e = 0;
    field_0x6c[0] = 0xffea;
    field_0x72[0] = 0xffd5;
    field_0x78[0] = 0x8c;
    field_0x6c[1] = 0xffdd;
    field_0x72[1] = 0xfffd;
    field_0x78[1] = 0x82;
    field_0x6c[2] = 0xfffa;
    field_0x72[2] = 0xfff3;
    field_0x78[2] = 0x8c;
}

/* 801EF360-801EF57C       .text __ct__16dMeter_menuHIO_cFv */
dMeter_menuHIO_c::dMeter_menuHIO_c() {
    field_0x8 = 1.4f;
    field_0xbe = 0;
    field_0xc = 18.0f;
    field_0x10 = 28.0f;
    field_0x7e = 3;
    field_0x80 = 3;
    field_0xc0 = 1;
    field_0x7c = 0;
    field_0xc1 = 0;
    field_0xc2 = 10;
    field_0xc3 = 4;
    field_0xc4 = 0;
    field_0x3c = 0.0f;
    field_0x40 = -50.0f;
    field_0x44 = 1100.0f;
    field_0x70 = 0xff;
    field_0x71 = 0xff;
    field_0x72 = 0xff;
    field_0x73 = 0xff;
    field_0x6c = 0x32;
    field_0x6d = 0x32;
    field_0x6e = 0x32;
    field_0x6f = 0xff;
    field_0x48 = 0.0f;
    field_0x4c = 0.0f;
    field_0x50 = -1200.0f;
    field_0x74 = 0xff;
    field_0x75 = 0xff;
    field_0x76 = 0xff;
    field_0x77 = 0xff;
    field_0x54 = -1500.0f;
    field_0x58 = 1000.0f;
    field_0x5c = 500.0f;
    field_0x60 = 1.0f;
    field_0x64 = -1.0f;
    field_0x68 = -1.0f;
    field_0x78 = 200;
    field_0x79 = 200;
    field_0x7a = 200;
    field_0x7b = 0xff;
    field_0x18 = 0.25f;
    field_0xbf = 0;
    field_0x1c = 2.5f;
    field_0xc5 = 2;
    field_0x82 = 8;
    field_0x84 = 5;
    field_0xc6 = 0;
    field_0xc7 = 1;
    field_0x20 = 0.5f;
    field_0xc8 = 9;
    field_0xc9 = 0;
    field_0xca = 0;
    field_0x28 = 0xffec;
    field_0x36 = 7;
    field_0x32 = 8;
    field_0x34 = 5;
    field_0x38 = 0x1a;
    field_0x3a = 0xfffd;
    field_0x88 = 3;
    field_0x8a = 0;
    field_0x14 = 1.3f;
    field_0x8c = 0xff38;
    field_0xb4 = 6;
    field_0x90 = 3;
    field_0x92 = 7;
    field_0x94 = 1.0f;
    field_0x98 = 0xff;
    field_0x99 = 0xff;
    field_0x9a = 0;
    field_0x9a = 0;
    field_0xa0 = 1.0f;
    field_0xb6 = 0x46;
    field_0xba = 5;
    field_0xbc = 3;
    field_0x24 = 1.4f;
    field_0xa4 = 6;
    field_0xa6 = 2;
    field_0xa8 = 2;
    field_0xaa = 2;
    field_0xac = 2;
    field_0xae = 0x1e;
    field_0xb0 = 0x3c;
    field_0xb2 = 0;
    field_0x8e = 0x15e;
    field_0xb8 = 0x96;
    field_0x2a = 0x10;
    field_0x2c = 0x18;
    field_0x2e = 0x17;
    field_0x30 = 0;
}

/* 801EF57C-801EF75C       .text __ct__16dMeter_msg_HIO_cFv */
dMeter_msg_HIO_c::dMeter_msg_HIO_c() {
    field_0x5.r = 0x1e;
    field_0x5.g = 0x1e;
    field_0x5.b = 0x1e;
    field_0x5.a = 0xd7;
    field_0x9.r = 0x1e;
    field_0x9.g = 0x1e;
    field_0x9.b = 0x4b;
    field_0x9.a = 0;
    field_0x5a = 0;
    field_0x5c = 0;
    field_0x5e = 0x1e;
    field_0x66 = 0;
    field_0x68 = 0xf;
    field_0xd = 0x1e;
    field_0xe = 0x1e;
    field_0xf = 0x1e;
    field_0x10 = 0xdc;
    field_0x11 = 0x1e;
    field_0x12 = 0x1e;
    field_0x13 = 0xb4;
    field_0x14 = 0;
    field_0x15 = 0;
    field_0x16 = 0xff;
    field_0x17 = 0;
    field_0x18 = 0xff;
    field_0x19 = 0x78;
    field_0x1a = 0x78;
    field_0x1b = 0xff;
    field_0x1c = 0xff;
    field_0x1d = 0xff;
    field_0x1e = 0xff;
    field_0x1f = 0x3c;
    field_0x20 = 0xff;
    field_0x21 = 0;
    field_0x22 = 0xff;
    field_0x23 = 0xff;
    field_0x24 = 0xff;
    field_0x25 = 0xff;
    field_0x26 = 0;
    field_0x27 = 0xff;
    field_0x28 = 0xff;
    field_0x6a = 0;
    field_0x72 = 0;
    field_0x6c = 0;
    field_0x83 = 0;
    field_0x84 = 1;
    field_0x85 = 0;
    field_0x86 = 0;
    field_0x87 = 10;
    field_0x88 = 0;
    field_0x89 = 0;
    field_0x8a = 0;
    field_0x64 = 0;
    field_0x82 = 2;
    field_0x58 = 0x1d;
    field_0x70 = 0x17;
    field_0x62 = 0;
    field_0x60 = 0xd;
    field_0x6e = 0xf0;
    field_0x50 = 0.6f;
    field_0x54 = 1.1f;
    field_0x4a = 2;
    field_0x4c = 4;
    field_0x7e = 10;
    field_0x80 = 0xb4;
    field_0x74 = 0x80;
    field_0x7f = 0xaa;
    field_0x81 = 0x46;
    field_0x76 = 10;
    field_0x78 = 0;
    field_0x7a = 0;
    field_0x7c = 0x46;
    field_0x44 = 5;
    field_0x46 = 3;
    field_0x48 = 4;
    field_0x38 = -40.0f;
    field_0x3c = 0.96f;
    field_0x40 = 0.5f;
    field_0x29 = 0xff;
    field_0x2a = 0x50;
    field_0x2b = 0x50;
    field_0x2c = 0x96;
    field_0x2d = 0xff;
    field_0x2e = 0x96;
    field_0x2f = 0x96;
    field_0x30 = 0xff;
}

/* 801EF75C-801EF924       .text __ct__20dMeter_message_HIO_cFv */
dMeter_message_HIO_c::dMeter_message_HIO_c() {
    field_0x5 = 0;
    field_0x6 = 0;
    field_0x7 = 0;
    field_0x8 = 0xff;
    field_0x9 = 0xff;
    field_0xa = 0xff;
    field_0xb = 0xff;
    field_0xc = 0xff;
    field_0xd = 0xff;
    field_0xe = 0xff;
    field_0xf = 0xff;
    field_0x10 = 0;
    field_0x11 = 0xff;
    field_0x12 = 0xff;
    field_0x13 = 0xff;
    field_0x14 = 0xff;
    field_0x15 = 0xff;
    field_0x16 = 0xff;
    field_0x17 = 0xff;
    field_0x18 = 0xff;
    field_0x19 = 0xff;
    field_0x1a = 0xff;
    field_0x1b = 0xff;
    field_0x1c = 0;
    field_0x1d = 0;
    field_0x1e = 0;
    field_0x1f = 0;
    field_0x20 = 0xff;
    field_0x21 = 0xff;
    field_0x22 = 0xff;
    field_0x23 = 0xff;
    field_0x24 = 0xff;
    field_0x25 = 0xff;
    field_0x26 = 0xff;
    field_0x27 = 0xff;
    field_0x28 = 0;
    field_0x29 = 0x80;
    field_0x2a = 0xff;
    field_0x2b = 0xff;
    field_0x2c = 0xff;
    field_0x2d = 0xff;
    field_0x2e = 0xb4;
    field_0x2f = 0xa0;
    field_0x30 = 0x4b;
    field_0x31 = 0;
    field_0x32 = 0x1b;
    field_0x34 = 0xfffe;
    field_0x36 = 0x2a;
    field_0x38 = 0xf;
    field_0x3a = 1;
    field_0x3b = 10;
    field_0x3c = 0x16;
    field_0x40 = 0.7f;
    field_0x44 = 0;
    field_0x46 = 1;
    field_0x48 = 0;
    field_0x4a = 0;
    field_0x4b = 1;
    field_0x4c = 0xff;
    field_0x4d = 0xff;
    field_0x4e = 0xff;
    field_0x4f = 0xff;
    field_0x50 = 0;
    field_0x51 = 0;
    field_0x52 = 0;
    field_0x53 = 0;
    field_0x54 = 0;
    field_0x56 = 0;
    field_0x58 = 0;
    field_0x5a = 0;
    field_0x5b = 0xff;
    field_0x5c = 0;
    field_0x60 = 0;
    field_0x66 = 0;
    field_0x6c = 1;
    field_0x72 = 1;
    field_0x5d = 0;
    field_0x62 = 0;
    field_0x68 = 0;
    field_0x6e = 1;
    field_0x74 = 1;
    field_0x5e = 0;
    field_0x64 = 0;
    field_0x6a = 0;
    field_0x70 = 1;
    field_0x76 = 1;
    field_0x78 = 0;
    field_0x7a = 4;
    field_0x7c = 4;
    field_0x7e = 2;
    field_0x80 = 600;
    field_0x82 = 0x18c;
}

/* 801EF924-801EF938       .text dMeter_mtrShow__Fv */
void dMeter_mtrShow() {
    dComIfGp_2dShowOn();
}

/* 801EF938-801EF94C       .text dMeter_mtrHide__Fv */
void dMeter_mtrHide() {
    dComIfGp_2dShowOff();
}

/* 801EF94C-801EF954       .text dMenu_setMenuStatus__FUc */
void dMenu_setMenuStatus(u8 param_1) {
    menu_status = param_1;
}

/* 801EF954-801EF95C       .text dMenu_setMenuStatusOld__FUc */
void dMenu_setMenuStatusOld(u8 param_1) {
    menu_status_old = param_1;
}

/* 801EF95C-801EF964       .text dMenu_getMenuStatus__Fv */
u8 dMenu_getMenuStatus() {
    return menu_status;
}

/* 801EF964-801EF96C       .text dMenu_getCollectMode__Fv */
u8 dMenu_getCollectMode() {
    return dMeter_collectMode;
}

/* 801EF96C-801EF974       .text dMenu_setCollectMode__FUc */
void dMenu_setCollectMode(u8 param_1) {
    dMeter_collectMode = param_1;
}

/* 801EF974-801EF97C       .text dMenu_getItemMode__Fv */
u8 dMenu_getItemMode() {
    return dMeter_itemMode;
}

/* 801EF97C-801EF984       .text dMenu_setItemMode__FUc */
void dMenu_setItemMode(u8 param_1) {
    dMeter_itemMode = param_1;
}

/* 801EF984-801EF98C       .text dMeter_subWinFlag__Fv */
bool dMeter_subWinFlag() {
    return subWinFlag;
}

/* 801EF98C-801EF998       .text dMeter_subWinFlagOn__Fv */
void dMeter_subWinFlagOn() {
    subWinFlag = true;
}

/* 801EF998-801EF9A4       .text dMeter_subWinFlagOff__Fv */
void dMeter_subWinFlagOff() {
    subWinFlag = false;
}

/* 801EF9A4-801EF9AC       .text dMeter_isAuctionFlag__Fv */
bool dMeter_isAuctionFlag() {
    return dMeter_auctionFlag;
}

/* 801EF9AC-801EF9B8       .text dMeter_onAuctionFlag__Fv */
void dMeter_onAuctionFlag() {
    dMeter_auctionFlag = true;
}

/* 801EF9B8-801EF9C4       .text dMeter_offAuctionFlag__Fv */
void dMeter_offAuctionFlag() {
    dMeter_auctionFlag = false;
}

/* 801EF9C4-801EFA38       .text dMeter_itemMoveSet__FP18fopMsgM_pane_classUcUc */
void dMeter_itemMoveSet(fopMsgM_pane_class* pane, u8 btn, u8 item) {
    dMeter_itemMoveFlag = 1;
    dMeter_btn_chk = btn;
    dMeter_itemNum = item;
    item_parts.mPosTopLeftOrig = pane->mPosTopLeft;
    item_parts.mPosTopLeft = item_parts.mPosTopLeftOrig;
    item_parts.mPosCenterOrig = pane->mPosCenter;
    item_parts.mPosCenter = item_parts.mPosCenterOrig;
    item_parts.mSizeOrig = pane->mSizeOrig;
    item_parts.mSize = pane->mSize;
    dMeter_itemTimer = 0;
}

/* 801EFA38-801EFA40       .text dMeter_itemMoveFlagCheck__Fv */
u8 dMeter_itemMoveFlagCheck() {
    return dMeter_itemMoveFlag;
}

/* 801EFA40-801EFA48       .text dMenu_flag__Fv */
u8 dMenu_flag() {
    return dMenu_pause;
}

/* 801EFA48-801EFA50       .text dMenu_flagSet__FUc */
void dMenu_flagSet(u8 param_1) {
    dMenu_pause = param_1;
}

/* 801EFA50-801EFA58       .text dMenu_timer__Fv */
int dMenu_timer() {
    return dMenu_frame_timer;
}

/* 801EFA58-801EFA60       .text dMenu_getPushMenuButton__Fv */
u8 dMenu_getPushMenuButton() {
    return dMenu_menuButton;
}

/* 801EFA60-801EFA68       .text dMenu_setPushMenuButton__FUc */
void dMenu_setPushMenuButton(u8 param_1) {
    dMenu_menuButton = param_1;
}

/* 801EFA68-801EFA78       .text dMeter_PaneHide__FP18fopMsgM_pane_class */
void dMeter_PaneHide(fopMsgM_pane_class* pane) {
    pane->pane->hide();
}

/* 801EFA78-801EFA90       .text dMeter_isBit8__FPUcUc */
bool dMeter_isBit8(u8* flag, u8 bit) {
    return (*flag & bit) != 0;
}

/* 801EFA90-801EFAA4       .text dMeter_onBit8__FPUcUc */
void dMeter_onBit8(u8* flag, u8 bit) {
    *flag |= bit & 0xFF;
}

/* 801EFAA4-801EFAB8       .text dMeter_offBit8__FPUcUc */
void dMeter_offBit8(u8* flag, u8 bit) {
    *flag &= ~(bit & 0xFF);
}

/* 801EFAB8-801EFAC8       .text dMeter_PaneShow__FP18fopMsgM_pane_class */
void dMeter_PaneShow(fopMsgM_pane_class* pane) {
    pane->pane->show();
}

/* 801EFAC8-801EFC40       .text dMeter_alphaControl__FP15sub_meter_class */
void dMeter_alphaControl(sub_meter_class* i_Meter) {
    if (!dComIfGp_2dShowCheck()) {
        if (i_Meter->field_0x2f6c > 0.0f) {
            i_Meter->field_0x2f6c = fopMsgM_valueIncrease(g_meterHIO.field_0x6, (int)i_Meter->field_0x2fd8, 0);
            i_Meter->field_0x2fd8--;
        } else {
            i_Meter->field_0x2f6c = 0.0f;
            i_Meter->field_0x2fd8 = 0;
        }
    } else if (dMenu_flag()) {
        if (dMenu_timer() <= 5) {
            f32 dVar3 = fopMsgM_valueIncrease(5, dMenu_timer(), 0);
            if (dMenu_getMenuStatus() != 3) {
                dVar3 = ((1.0f - dVar3) * 0.5f + 0.5f);
            }
            if (i_Meter->field_0x2f6c > dVar3) {
                i_Meter->field_0x2f6c = dVar3;
            }
        } else if (dMenu_getMenuStatus() == 3) {
            i_Meter->field_0x2f6c = 0.0f;
        } else {
            i_Meter->field_0x2f6c = 0.5f;
        }
    } else if (i_Meter->field_0x2f6c < 1.0f) {
        i_Meter->field_0x2f6c = fopMsgM_valueIncrease(g_meterHIO.field_0x6, (int)i_Meter->field_0x2fd8, 0);
        i_Meter->field_0x2fd8++;
    } else {
        i_Meter->field_0x2f6c = 1.0f;
        i_Meter->field_0x2fd8 = g_meterHIO.field_0x6;
    }
}

/* 801EFC40-801F01C0       .text dMeter_statusCheck__FP15sub_meter_class */
void dMeter_statusCheck(sub_meter_class* i_Meter) {
    /* Nonmatching */
    i_Meter->mStatusFlags = 0;
    if ((!dComIfGp_2dShowCheck()) || (dCam_getBody()->chkFlag(0x2000000))) {
        i_Meter->mStatusFlags |= dMtrStts_UNK4000_e;
    } else if (((dMeter_isAuctionFlag()) && (dComIfGp_getMesgStatus() == 0)) ||
               (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0408) && (dComIfGp_getMesgStatus() == 0)) ||
               (dComIfGp_evmng_startCheck("PUZZLE_GAME") || dComIfGp_evmng_startCheck("PUZZLE_RUPEE")))
    {
        i_Meter->mStatusFlags |= dMtrStts_UNK80000_e;
        dComIfGp_setAStatus(dActStts_BLANK_e);
        dComIfGp_setDoStatus(dActStts_BLANK_e);
    } else if (dComIfGp_getOperateWind() == 2) {
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        i_Meter->mStatusFlags |= dMtrStts_UNK400000_e;
    } else if ((dComIfGp_getMiniGameType() == 8) && (!(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)))) {
        dComIfGp_setDoStatusForce(dActStts_bow_01);
        dComIfGp_setAStatusForce(dActStts_HIDDEN_e);
        i_Meter->mStatusFlags |= dMtrStts_UNK80000_e;
    } else if ((dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e)) && (dComIfGp_getAStatus() == dActStts_RETURN_e)) {
        i_Meter->mStatusFlags |= dMtrStts_UNK200000_e;
    } else if ((dComIfGp_event_runCheck()) && (dMenu_getMenuStatus() != 4)) {
        if (((dComIfGp_demo_mode() != 1) && (dComIfGp_getMesgStatus() != 0)) && !dComIfGp_getMetronome()) {
            i_Meter->mStatusFlags |= dMtrStts_UNK100_e;
        } else if ((dComIfGp_demo_mode() != 1) && dComIfGp_getMetronome()) {
            i_Meter->mStatusFlags |= dMtrStts_UNK200000_e;
            dComIfGp_setAStatusForce(dActStts_HIDDEN_e);
        } else {
            i_Meter->mStatusFlags |= dMtrStts_UNK40_e;
        }
    }
    if (dMenu_flag() != 0) {
        if (((dComIfGp_checkPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e)) || (dComIfGp_getPictureStatus() == 2)) ||
            (dComIfGp_getPictureStatus() == 3 || (dComIfGp_isHeapLockFlag() == 6)))
        {
            i_Meter->mStatusFlags |= dMtrStts_UNK20000_e;
            dComIfGp_setAStatus(dActStts_BLANK_e);
            dComIfGp_setDoStatus(dActStts_BLANK_e);
            dComIfGp_setRStatus(dActStts_BLANK_e);
        } else if (dMenu_getMenuStatus() == 1) {
            i_Meter->mStatusFlags |= dMtrStts_UNK8_e;
        } else if (dMenu_getMenuStatus() == 2) {
            i_Meter->mStatusFlags |= dMtrStts_UNK10_e;
        } else if (dMenu_getMenuStatus() == 4) {
            i_Meter->mStatusFlags |= dMtrStts_UNK800000_e;
        } else {
            i_Meter->mStatusFlags |= dMtrStts_UNK20_e;
        }
    } else {
        if (dComIfGp_getCb1Player() == daPy_getPlayerActorClass() || (daNpc_kam_c::m_hyoi_kamome != 0)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK40000_e;
            if (dComIfGp_getAStatus() == dActStts_sword_01) {
                dComIfGp_setAStatus(dActStts_BLANK_e);
            }
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK100000_e;
        }
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK100_e;
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK80_e;
        } else if (((dComIfGp_checkPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e)) || (dComIfGp_getPictureStatus() == 2)) || (dComIfGp_getPictureStatus() == 3) ||
                   (dComIfGp_isHeapLockFlag() == 6))
        {
            i_Meter->mStatusFlags |= dMtrStts_UNK20000_e;
            dComIfGp_setAStatus(dActStts_BLANK_e);
            dComIfGp_setRStatus(dActStts_BLANK_e);
            dComIfGp_setDoStatus(dActStts_BLANK_e);
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK400_e;
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_CRAWL_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK200_e;
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK800000_e)) {
            if (daPy_getPlayerActorClass()->checkRopeTag()) {
                i_Meter->mStatusFlags |= dMtrStts_UNK800_e;
            } else {
                i_Meter->mStatusFlags |= dMtrStts_UNK1000_e;
            }
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK2000_e;
        } else if (dComIfGp_checkPlayerStatus0(0, (daPyStts0_UNK100_e | daPyStts0_UNK2000000_e))) {
            i_Meter->mStatusFlags |= dMtrStts_UNK8000_e;
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK4000000_e)) {
            i_Meter->mStatusFlags |= dMtrStts_UNK10000_e;
        }
    }
    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_DUNGEON_e) {
        i_Meter->mStatusFlags |= dMtrStts_UNK4_e;
    } else {
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_MISC_e) {
            i_Meter->mStatusFlags |= dMtrStts_UNK2_e;
        } else {
            i_Meter->mStatusFlags |= dMtrStts_UNK1_e;
        }
    }
}

/* 801F01C0-801F0258       .text dMeter_alphaClose__FPsPs */
f32 dMeter_alphaClose(s16* timer, s16* value) {
    f32 ret;
    if (*timer == 8) {
        *timer = 9;
        ret = 1.0f;
        *value = 1;
    } else if (*timer == 9) {
        if (*value < 6) {
            ret = 1.0f - fopMsgM_valueIncrease(6, *value, 1);
            (*value)++;
        } else {
            ret = 0.0f;
            *timer = 0;
        }
    } else {
        ret = 0.0f;
    }
    return ret;
}

/* 801F0258-801F02E8       .text dMeter_alphaOpen__FPsPs */
f32 dMeter_alphaOpen(s16* timer, s16* value) {
    f32 ret;
    if (*timer == 0) {
        *timer = 7;
        ret = 0.0f;
        *value = 0;
    } else if (*timer == 7) {
        if (*value < 6) {
            ret = fopMsgM_valueIncrease(6, *value, 1);
            (*value)++;
        } else {
            ret = 1.0f;
            *timer = 8;
        }
    } else {
        ret = 1.0f;
    }
    return ret;
}

/* 801F02E8-801F0320       .text dMeter_rupy_num__FPcs */
void dMeter_rupy_num(char* buf, s16 num) {
    sprintf(buf, "rupy_num_%02d.bti", num);
}

/* 801F0320-801F0378       .text dMeter_actionTex__Fs */
const char* dMeter_actionTex(s16 id) {
    static const struct {
        u8 id;
        const char* filename;
    } act[] = {
        {dActStts_BLANK_e, "ba_shiraberu.bti"},
        {dActStts_LOOK_e, "ba_miru.bti"},
        {dActStts_SPEAK_e, "ba_syaberu.bti"},
        {dActStts_CHARTS_e, "ba_shiraberu.bti"},
        {dActStts_LIFT_e, "ba_motu.bti"},
        {dActStts_CLIMB_e, "ba_noru.bti"},
        {dActStts_LET_GO_e, "ba_oriru.bti"},
        {dActStts_RETURN_e, "ba_modoru.bti"},
        {dActStts_PUT_AWAY_e, "ba_shimau.bti"},
        {dActStts_DROP_e, "ba_oku.bti"},
        {dActStts_CHECK_e, "ba_chekku.bti"},
        {dActStts_OPEN_e, "ba_hiraku.bti"},
        {dActStts_ATTACK_e, "ba_attack.bti"},
        {dActStts_ba_osu, "ba_osu.bti"},
        {dActStts_THROW_e, "ba_nageru.bti"},
        {dActStts_CROUCH_e, "ba_shagamu.bti"},
        {dActStts_SIDLE_e, "ba_harituku.bti"},
        {dActStts_GRAB_e, "ba_tukamu.bti"},
        {dActStts_JUMP_e, "ba_jump.bti"},
        {dActStts_STOP_e, "ba_tomeru.bti"},
        {dActStts_ba_haru, "ba_haru.bti"},
        {dActStts_ba_tatamu, "ba_tatamu.bti"},
        {dActStts_LET_GO_ROPE_e, "ba_hanasu.bti"},
        {dActStts_CHOOSE_e, "ba_kettei.bti"},
        {dActStts_ba_kogu, "ba_kogu.bti"},
        {dActStts_NEXT_e, "ba_tugihe.bti"},
        {dActStts_PARRY_e, "ba_sake.bti"},
        {dActStts_PICK_UP_e, "ba_motu_buki.bti"},
        {dActStts_GET_IN_SHIP_e, "ba_noru_hune.bti"},
        {dActStts_GET_OUT_SHIP_e, "ba_oriru_hune.bti"},
        {dActStts_ba_save, "ba_save.bti"},
        {dActStts_ba_option, "ba_option.bti"},
        {dActStts_TAKE_PHOTO_e, "ba_toru.bti"},
        {dActStts_INFO_e, "ba_setumei.bti"},
        {dActStts_SWAP_MODES_e, "ba_kirikae.bti"},
        {dActStts_FLY_e, "ba_tobu.bti"},
        {dActStts_CALL_e, "ba_yobu.bti"},
        {dActStts_BID_e, "ba_hoshii.bti"},
        {dActStts_READ_e, "ba_yomu.bti"},
        {dActStts_CANCEL_e, "ba_yameru.bti"},
        {dActStts_ba_kakudai, "ba_kakudai.bti"},
        {dActStts_ba_hikaku, "ba_hikaku.bti"},
        {dActStts_ba_zoom01, "ba_zoom01.bti"},
        {dActStts_ba_zoom02, "ba_zoom02.bti"},
        {dActStts_CRUISE_e, "ba_susumu.bti"},
        {dActStts_ba_nageru__dupe_2D, "ba_nageru.bti"},
        {dActStts_ba_motu__dupe_2E, "ba_motu.bti"},
        {dActStts_SWING_e, "ba_huru.bti"},
        {dActStts_SEA_CHART_e, "ba_kaizuhe.bti"},
        {dActStts_ba_sake__dupe_31, "ba_sake.bti"},
        {dActStts_ba_modoru__dupe_32, "ba_modoru.bti"},
        {dActStts_ba_save__dupe_33, "ba_save.bti"},
        {dActStts_ba_save__dupe_34, "ba_save.bti"},
        {dActStts_sword_01, "sword_01.bti"},
        {dActStts_DEFEND_e, "ba_husegu.bti"},
        {dActStts_boko_stick, "boko_stick.bti"},
        {dActStts_hatchet, "hatchet.bti"},
        {dActStts_iron_club, "iron_club.bti"},
        {dActStts_longsword, "longsword.bti"},
        {dActStts_spear, "spear.bti"},
        {dActStts_spear__dupe_3C, "spear.bti"},
        {dActStts_bow_01, "bow_01.bti"},
        {dActStts_HIDDEN_e, "ba_modoru.bti"},
    };
    int found = 0;
    for (int i = 0; i < ARRAY_SIZE(act); i++) {
        if (id == act[i].id) {
            found = i;
            break;
        }
    }
    return act[found].filename;
}

/* 801F0378-801F041C       .text dMeter_weponTex__Fv */
const char* dMeter_weponTex() {
    static const char* wepon[] = {
        "sword_00.bti",
        "sword_01.bti",
        "sword_02.bti",
        "sword_03.bti",
    };
    int var1;
    if (dComIfGs_isCollect(0, 3)) {
        var1 = 3;
    } else if (dComIfGs_isCollect(0, 2)) {
        var1 = 2;
    } else if (dComIfGs_isCollect(0, 1)) {
        var1 = 1;
    } else {
        var1 = 0;
    }
    return wepon[var1];
}

/* 801F041C-801F0434       .text dMeter_heartTex__Fs */
const char* dMeter_heartTex(s16 param_1) {
    static const char* ht[] = {
        "heart.bti",
        "heart_03.bti",
        "heart_02.bti",
        "heart_01.bti",
        "heart_04.bti",
    };
    return ht[param_1];
}

/* 801F0434-801F0608       .text dMeter_recollect_boss_data__Fv */
void dMeter_recollect_boss_data() {
    if ((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_BOSS_e) && (dComIfGs_isStageBossEnemy())) {
        if ((dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_DRC) && (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D80))) {
            dComIfGs_copyPlayerRecollectionData();
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D80);
        } else if ((dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_FW) && (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D40))) {
            dComIfGs_copyPlayerRecollectionData();
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D40);
        } else if ((dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_ET) && (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D20))) {
            dComIfGs_copyPlayerRecollectionData();
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D20);
        } else if ((dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_WT) && (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D10))) {
            dComIfGs_copyPlayerRecollectionData();
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D10);
        }
    }
}

/* 801F0608-801F06CC       .text draw__16dDlst_2DMETER1_cFv */
void dDlst_2DMETER1_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    sMainParts3->draw(0.0f, 0.0f, graf);
    sMainParts1->draw(0.0f, 0.0f, graf);
    if (sScrTimer1 != NULL) {
        sScrTimer1->setScissor(true);
        sScrTimer1->draw(0.0f, 0.0f, graf);
    }
    if (sScrTimer2 != NULL) {
        sScrTimer2->draw(0.0f, 0.0f, graf);
    }
    sChoiceRoad->draw(0.0f, 0.0f, graf);
}

/* 801F06CC-801F0724       .text draw__16dDlst_2DMETER2_cFv */
void dDlst_2DMETER2_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    sMainParts2->draw(0.0f, 0.0f, graf);
}

void dMeter_setNowHeartScaleXY(fopMsgM_pane_class*);

/* 801F0724-801F07D4       .text dMeter_heart_data_set__FP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_class */
void dMeter_heart_data_set(fopMsgM_pane_class* pane1, fopMsgM_pane_class* pane2, fopMsgM_pane_class* pane3) {
    dMeter_setNowHeartScaleXY(pane2);
    dMeter_setNowHeartScaleXY(pane3);
    pane1->mPosTopLeft = pane2->mPosTopLeft;
    pane1->mSize = pane2->mSize;
    pane1->mPosCenter = pane2->mPosCenter;
    pane1->pane->move(pane1->mPosTopLeft.x, pane1->mPosTopLeft.y);
    pane1->pane->resize(pane1->mSize.x, pane1->mSize.y);
}

/* 801F07D4-801F0820       .text dMeter_paneBottomScaleY__FP18fopMsgM_pane_classf */
void dMeter_paneBottomScaleY(fopMsgM_pane_class* pane, f32 scale) {
    f32 oldBottom = (pane->mPosTopLeft.y + pane->mSize.y);
    pane->mSize.y = pane->mSizeOrig.y * scale;
    pane->mPosCenter.y = oldBottom - (pane->mSize.y / 2.0f);
    fopMsgM_cposMove(pane);
}

/* 801F0820-801F08DC       .text dMeter_parentPaneTrans__FP18fopMsgM_pane_classf */
void dMeter_parentPaneTrans(fopMsgM_pane_class* pane, f32 scale) {
    pane->mPosCenter.x += g_meterHIO.field_0x50;
    pane->mPosCenter.y += g_meterHIO.field_0x52;
    fopMsgM_paneScaleXY(pane, scale);
    J2DPane* j2dPane = pane->pane;
    j2dPane->rotate(pane->mSize.x / 2.0f, pane->mSize.y / 2.0f, ROTATE_Z, j2dPane->getRotate());
}

/* 801F08DC-801F09D8       .text dMeter_childPaneTrans__FP18fopMsgM_pane_classP18fopMsgM_pane_classf */
void dMeter_childPaneTrans(fopMsgM_pane_class* pane, fopMsgM_pane_class* parent, f32 scale) {
    f32 x = pane->mPosCenterOrig.x - parent->mPosCenterOrig.x;
    f32 y = pane->mPosCenterOrig.y - parent->mPosCenterOrig.y;
    pane->mPosCenter.x += x * (scale - 1.0f);
    pane->mPosCenter.y += y * (scale - 1.0f);
    pane->mPosCenter.x += g_meterHIO.field_0x50;
    pane->mPosCenter.y += g_meterHIO.field_0x52;
    fopMsgM_paneScaleXY(pane, scale);
    J2DPane* j2dPane = pane->pane;
    j2dPane->rotate(pane->mSize.x / 2.0f, pane->mSize.y / 2.0f, ROTATE_Z, j2dPane->getRotate());
}

/* 801F09D8-801F0AD8       .text dMeter_childPaneTransOnly__FP18fopMsgM_pane_classP18fopMsgM_pane_classff */
void dMeter_childPaneTransOnly(fopMsgM_pane_class* pane, fopMsgM_pane_class* parent, f32 transScale, f32 scale) {
    f32 x = pane->mPosCenterOrig.x - parent->mPosCenterOrig.x;
    f32 y = pane->mPosCenterOrig.y - parent->mPosCenterOrig.y;
    pane->mPosCenter.x += x * (transScale - 1.0f);
    pane->mPosCenter.y += y * (transScale - 1.0f);
    pane->mPosCenter.x += g_meterHIO.field_0x50;
    pane->mPosCenter.y += g_meterHIO.field_0x52;
    fopMsgM_paneScaleXY(pane, scale);
    J2DPane* j2dPane = pane->pane;
    j2dPane->rotate(pane->mSize.x / 2.0f, pane->mSize.y / 2.0f, ROTATE_Z, j2dPane->getRotate());
}

/* 801F0AD8-801F0C10       .text dMeter_childPaneTransChildTrans__FP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classff */
void dMeter_childPaneTransChildTrans(fopMsgM_pane_class* param_1, fopMsgM_pane_class* param_2, fopMsgM_pane_class* param_3, f32 param_4, f32 param_5) {
    f32 x = param_1->mPosCenterOrig.x - param_2->mPosCenterOrig.x;
    f32 y = param_1->mPosCenterOrig.y - param_2->mPosCenterOrig.y;
    param_1->mPosCenter.x += x * (param_4 - 1.0f);
    param_1->mPosCenter.y += y * (param_4 - 1.0f);
    x = param_1->mPosCenter.x - param_3->mPosCenter.x;
    y = param_1->mPosCenter.y - param_3->mPosCenter.y;
    param_1->mPosCenter.x += x * (param_5 - 1.0f);
    param_1->mPosCenter.y += y * (param_5 - 1.0f);
    param_1->mPosCenter.x += g_meterHIO.field_0x50;
    param_1->mPosCenter.y += g_meterHIO.field_0x52;
    fopMsgM_paneScaleXY(param_1, param_5);
    J2DPane* j2dPane = param_1->pane;
    f32 tmp = 0.5f;
    j2dPane->rotate(param_1->mSize.x * tmp, param_1->mSize.y * tmp, ROTATE_Z, j2dPane->getRotate());
}

/* 801F0C10-801F0D0C       .text dMeter_childPaneTransChildTransOnly__FP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classff */
void dMeter_childPaneTransChildTransOnly(fopMsgM_pane_class* param_1, fopMsgM_pane_class* param_2, fopMsgM_pane_class* param_3, f32 param_4, f32 param_5) {
    f32 x = param_1->mPosCenterOrig.x - param_2->mPosCenterOrig.x;
    f32 y = param_1->mPosCenterOrig.y - param_2->mPosCenterOrig.y;
    param_1->mPosCenter.x += x * (param_4 - 1.0f);
    param_1->mPosCenter.y += y * (param_4 - 1.0f);
    param_1->mPosCenter.x += g_meterHIO.field_0x50;
    param_1->mPosCenter.y += g_meterHIO.field_0x52;
    fopMsgM_cposMove(param_1);
    J2DPane* j2dPane = param_1->pane;
    f32 tmp = 0.5f;
    j2dPane->rotate(param_1->mSize.x * tmp, param_1->mSize.y * tmp, ROTATE_Z, j2dPane->getRotate());
}

/* 801F0D0C-801F0D64       .text dMeter_setHeartScaleXY__FP18fopMsgM_pane_classs */
void dMeter_setHeartScaleXY(fopMsgM_pane_class* pane, s16 scale) {
    f32 scaleX, scaleY;
    if (scale != 4) {
        scaleX = 1.0f;
        scaleY = 1.0f;
    } else {
        scaleX = texRateX;
        scaleY = texRateY;
    }
    pane->mSize.x = pane->mSizeOrig.x * scaleX;
    pane->mSize.y = pane->mSizeOrig.y * scaleY;
    fopMsgM_cposMove(pane);
}

/* 801F0D64-801F0DD4       .text dMeter_setHeartScaleXY2__FP18fopMsgM_pane_classs */
void dMeter_setHeartScaleXY2(fopMsgM_pane_class* pane, s16 scale) {
    f32 scaleX, scaleY;
    if (scale != 4) {
        scaleX = 1.0f;
        scaleY = 1.0f;
    } else {
        scaleX = texRateX;
        scaleY = texRateY;
    }
    pane->mSize.x = pane->mSizeOrig.x * scaleX * g_meterHIO.field_0x48;
    pane->mSize.y = pane->mSizeOrig.y * scaleY * g_meterHIO.field_0x48;
    fopMsgM_cposMove(pane);
}

/* 801F0DD4-801F0E1C       .text dMeter_setNowHeartScaleXY__FP18fopMsgM_pane_class */
void dMeter_setNowHeartScaleXY(fopMsgM_pane_class* pane) {
    pane->mSize.x = pane->mSizeOrig.x * g_meterHIO.field_0x10;
    pane->mSize.y = pane->mSizeOrig.y * g_meterHIO.field_0x10;
    fopMsgM_cposMove(pane);
}

/* 801F0E1C-801F0E74       .text dMeter_setNowHeartScaleXY2__FP18fopMsgM_pane_class */
void dMeter_setNowHeartScaleXY2(fopMsgM_pane_class* pane) {
    pane->mSize.x = pane->mSizeOrig.x * g_meterHIO.field_0x10 * g_meterHIO.field_0x48;
    pane->mSize.y = pane->mSizeOrig.y * g_meterHIO.field_0x10 * g_meterHIO.field_0x48;
    fopMsgM_cposMove(pane);
}

/* 801F0E74-801F0EE4       .text dMeter_heartChangeTexture__FP15sub_meter_classPCci */
void dMeter_heartChangeTexture(sub_meter_class* i_Meter, const char* textureName, int no) {
    ((J2DPicture*)i_Meter->mHeart[no].pane)->changeTexture(textureName, 0);
    ((J2DPicture*)i_Meter->mHeartShadow[no].pane)->changeTexture(textureName, 0);
    dMeter_PaneShow(&i_Meter->mHeart[no]);
    dMeter_PaneShow(&i_Meter->mHeartShadow[no]);
}

/* 801F0EE4-801F10B0       .text dMeter_heartScaleInit__FP15sub_meter_class */
void dMeter_heartScaleInit(sub_meter_class* i_Meter) {
    int uVar1;
    int uVar2;
    int iVar9;

    uVar1 = i_Meter->mMaxHP / 4;
    uVar2 = i_Meter->mCurrHP - 1;
    iVar9 = uVar2 / 4;
    for (s32 i = 0; i < 20; i++) {
        if (uVar1 == 0) {
            i_Meter->mHeart[i].mUserArea = 5;
        } else if (i_Meter->mCurrHP == 0) {
            if (i < uVar1) {
                i_Meter->mHeart[i].mUserArea = 4;
            } else {
                i_Meter->mHeart[i].mUserArea = 5;
            }
        } else if (i == iVar9) {
            i_Meter->mHeart[i].mUserArea = i_Meter->mCurrHP % 4;
        } else if (i < iVar9) {
            i_Meter->mHeart[i].mUserArea = 0;
        } else if (i < uVar1) {
            i_Meter->mHeart[i].mUserArea = 4;
        } else {
            i_Meter->mHeart[i].mUserArea = 5;
        }
        dMeter_setHeartScaleXY(&i_Meter->mHeart[i], i_Meter->mHeart[i].mUserArea);
        dMeter_setHeartScaleXY(&i_Meter->mHeartShadow[i], i_Meter->mHeart[i].mUserArea);
        if (i_Meter->mHeart[i].mUserArea != 5) {
            dMeter_heartChangeTexture(i_Meter, dMeter_heartTex(i_Meter->mHeart[i].mUserArea), i);
        } else {
            dMeter_PaneHide(&i_Meter->mHeart[i]);
            dMeter_PaneHide(&i_Meter->mHeartShadow[i]);
        }
        fopMsgM_paneTrans(&i_Meter->mHeart[i], 0.0f, 0.0f);
        fopMsgM_paneTrans(&i_Meter->mHeartShadow[i], 0.0f, 0.0f);
        uVar2 = i_Meter->mCurrHP - 1;
        if ((i == uVar2 / 4) && (i_Meter->mCurrHP != 0)) {
            ((J2DPicture*)i_Meter->field_0x0f00.pane)->changeTexture(dMeter_heartTex(i_Meter->mHeart[i].mUserArea), 0);
            dMeter_heart_data_set(&i_Meter->field_0x0f00, &i_Meter->mHeart[i], &i_Meter->mHeartShadow[i]);
        }
    }
}

/* 801F10B0-801F10FC       .text dMeter_maxLifeChange__FP15sub_meter_class */
void dMeter_maxLifeChange(sub_meter_class* i_Meter) {
    if (i_Meter->field_0x300c > 0) {
        i_Meter->mMaxHP++;
        i_Meter->field_0x300c--;
        return;
    }
    if (i_Meter->field_0x300c >= 0) {
        return;
    }
    i_Meter->mMaxHP--;
    i_Meter->field_0x300c++;
}

/* 801F10FC-801F11F8       .text dMeter_lifeChange__FP15sub_meter_classPb */
void dMeter_lifeChange(sub_meter_class* i_Meter, bool* param_2) {
    if (i_Meter->mAdjustHp > 0) {
        i_Meter->mCurrHP++;
        i_Meter->mAdjustHp--;
        if (*param_2 != false) {
            if ((i_Meter->mCurrHP % 4) == 0) {
                mDoAud_seStart(JA_SE_HP_GAUGE_INC);
            }
            if (i_Meter->mAdjustHp == 0) {
                *param_2 = false;
            }
        }
    } else if (i_Meter->mAdjustHp < 0) {
        i_Meter->mCurrHP--;
        i_Meter->mAdjustHp++;
    }
    i_Meter->field_0x0f00.mUserArea = 0;
    g_dComIfG_gameInfo.play.mItemNowLife = i_Meter->mCurrHP;
}

/* 801F11F8-801F13A4       .text dMeter_heartLightMove__FP15sub_meter_class */
void dMeter_heartLightMove(sub_meter_class* i_Meter) {
    uint hp;
    int iVar1;
    u32 uVar2;
    f32 dVar3;
    f32 dVar4;
    f32 dVar5;

    hp = dComIfGs_getLife() - 1;
    if ((int)hp / 4) {
        iVar1 = 22;
    } else {
        iVar1 = 12;
    }
    i_Meter->field_0x0f00.mUserArea++;
    if (iVar1 < i_Meter->field_0x0f00.mUserArea) {
        i_Meter->field_0x0f00.mUserArea = 0;
    }
    dVar3 = fopMsgM_valueIncrease(iVar1, (int)i_Meter->field_0x0f00.mUserArea, 0);
    uVar2 = (int)(dVar3 * 255.0f);
    dVar4 = (g_meterHIO.field_0x3c * dVar3) + 1.0f;
    fopMsgM_setNowAlpha(&i_Meter->field_0x0f00, 1.0f - dVar3);
    ((J2DPicture*)i_Meter->field_0x0f00.pane)->setBlack((GXColor){uVar2, uVar2, uVar2, 0});
    dVar3 = i_Meter->field_0x0f00.mSize.x * dVar4;
    dVar5 = i_Meter->field_0x0f00.mSize.y * dVar4;
    f32 tmp = 0.5f;
    i_Meter->field_0x0f00.mPosTopLeft.x = i_Meter->field_0x0f00.mPosCenter.x - (dVar3 * tmp);
    i_Meter->field_0x0f00.mPosTopLeft.y = i_Meter->field_0x0f00.mPosCenter.y - (dVar5 * tmp);
    i_Meter->field_0x0f00.pane->move(i_Meter->field_0x0f00.mPosTopLeft.x, i_Meter->field_0x0f00.mPosTopLeft.y);
    i_Meter->field_0x0f00.pane->resize(dVar3, dVar5);
}

/* 801F13A4-801F153C       .text dMeter_heartAlpha__FP15sub_meter_class */
void dMeter_heartAlpha(sub_meter_class* i_Meter) {
    f32 dVar5;

    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(0x10)) && (!(dComIfGp_checkPlayerStatus1(0, daPyStts1_UNK2000_e)))) ||
        (dMenu_getCollectMode() == 4) || (i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK100000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80000_e)) || (dMeter_isAuctionFlag()) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK400000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e)))
    {
        if (i_Meter->field_0x3014 > 0) {
            i_Meter->field_0x3014--;
        } else {
            i_Meter->field_0x3014 = 0;
        }
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK8_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10_e)) {
        if (i_Meter->field_0x3014 < 3) {
            i_Meter->field_0x3014++;
        } else if (i_Meter->field_0x3014 > 3) {
            i_Meter->field_0x3014--;
        } else {
            i_Meter->field_0x3014 = 3;
        }
    } else {
        if (i_Meter->field_0x3014 < 5) {
            i_Meter->field_0x3014++;
        } else {
            i_Meter->field_0x3014 = 5;
        }
        if (dComIfGp_getMiniGameType() != 6) {
            mDoAud_heartGaugeOn();
        }
    }
    dVar5 = fopMsgM_valueIncrease(5, i_Meter->field_0x3014, 0);
    i_Meter->field_0x2fbc = dVar5;
}

/* 801F153C-801F15EC       .text dMeter_heartInit__FP15sub_meter_class */
void dMeter_heartInit(sub_meter_class* i_Meter) {
    texScaleX = i_Meter->mHeart[0].mSizeOrig.x / 40.0f;
    texScaleY = i_Meter->mHeart[0].mSizeOrig.y / 32.0f;
    texRateX = 0.4f;
    texRateY = 0.5f;
    i_Meter->field_0x2f70 = 1.0f;
    i_Meter->field_0x2fbc = 0.0f;
    i_Meter->mMaxHP = dComIfGs_getMaxLife();
    i_Meter->mCurrHP = dComIfGs_getLife();
    i_Meter->field_0x3014 = 5;
    i_Meter->field_0x0f00.mUserArea = 0;
    i_Meter->field_0x0f00.mUserArea = 0;
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x0f00);
    dMeter_heartScaleInit(i_Meter);
    dComIfGp_setItemNowLife(i_Meter->mCurrHP);
}

/* 801F15EC-801F17F0       .text dMeter_LifeMove__FP15sub_meter_classb */
void dMeter_LifeMove(sub_meter_class* i_Meter, bool bForce) {
    /* Nonmatching */
    int iVar1;
    bool bVar2;
    s16 maxHP;
    s16 newHP;
    int uVar3;

    static bool soundOnFlag = false;
    bVar2 = false;
    if (dComIfGp_getItemMaxLifeCount() != 0 || ((s16)dComIfGp_getItemLifeCount() != 0) || (bForce)) {
        maxHP = dComIfGs_getMaxLife() + dComIfGp_getItemMaxLifeCount();
        uVar3 = (s16)maxHP;
        if (dComIfGp_getItemMaxLifeCount() > 0) {
            newHP = ((int)uVar3 / 4) * 4;
        } else {
            newHP = dComIfGs_getLife() + (int)dComIfGp_getItemLifeCount();
        }
        if (dComIfGp_getItemMaxLifeCount() != 0) {
            if ((int)uVar3 > 0x50) {
                maxHP = 0x50;
            } else if (maxHP < 0) {
                maxHP = 0;
            }
            i_Meter->field_0x300c = maxHP - i_Meter->mMaxHP;
            dComIfGs_setMaxLife(maxHP);
            g_dComIfG_gameInfo.play.mItemMaxLifeCount = 0;
            i_Meter->field_0x0f38[5].mUserArea = 1;
        }
        uVar3 = (s16)maxHP;
        iVar1 = ((int)uVar3 / 4) * 4;
        if (newHP > iVar1) {
            newHP = iVar1;
        } else if (newHP < 0) {
            newHP = 0;
        }
        i_Meter->mAdjustHp = newHP - i_Meter->mCurrHP;
        dComIfGs_setLife(newHP);
        g_dComIfG_gameInfo.play.mItemLifeCount = 0.0f;
        if (i_Meter->mAdjustHp >= 4) {
            soundOnFlag = true;
        }
    }
    if ((i_Meter->field_0x300c != 0) || (bForce)) {
        dMeter_maxLifeChange(i_Meter);
        bVar2 = true;
    }
    if ((i_Meter->mAdjustHp != 0) || (bForce)) {
        dMeter_lifeChange(i_Meter, &soundOnFlag);
        bVar2 = true;
    }
    if (bVar2) {
        dMeter_heartScaleInit(i_Meter);
    }
    if (dComIfGs_getLife() != 0) {
        dMeter_heartLightMove(i_Meter);
    } else {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0f00);
    }
}

/* 801F17F0-801F1A48       .text dMeter_BattleLifeMove__FP15sub_meter_classb */
void dMeter_BattleLifeMove(sub_meter_class* i_Meter, bool param_2) {
    /* Nonmatching */
    const char* pFilename;
    f32 dVar4;

    static u8 point = 0;
    dVar4 = (i_Meter->mHeart[1].mPosCenterOrig.x - i_Meter->mHeart[0].mPosCenterOrig.x);
    if ((point != daNpc_Ji1_c::game_life_point) || (!param_2)) {
        for (s32 i = 0; i < 20; i++) {
            point = daNpc_Ji1_c::game_life_point;
            if ((i == 1) || (i == 2)) {
                i_Meter->mHeart[i].mPosCenter.x = (s32)(g_meterHIO.field_0x4c + i_Meter->mHeart[i].mPosCenterOrig.x) * (g_meterHIO.field_0x58 * dVar4);
                i_Meter->mHeartShadow[i].mPosCenter.x =
                    (s32)(g_meterHIO.field_0x4c + i_Meter->mHeartShadow[i].mPosCenterOrig.x) * (g_meterHIO.field_0x58 * dVar4);
                i_Meter->mHeart[i].mPosCenter.y = i_Meter->mHeart[i].mPosCenterOrig.y + g_meterHIO.field_0x5c;
                i_Meter->mHeartShadow[i].mPosCenter.y = i_Meter->mHeartShadow[i].mPosCenterOrig.y + g_meterHIO.field_0x5c;
            } else if (i == 0) {
                i_Meter->mHeart[i].mPosCenter.x = i_Meter->mHeart[i].mPosCenterOrig.x + g_meterHIO.field_0x4c;
                i_Meter->mHeartShadow[i].mPosCenter.x = i_Meter->mHeartShadow[i].mPosCenterOrig.x + g_meterHIO.field_0x4c;
                i_Meter->mHeart[i].mPosCenter.y = i_Meter->mHeart[i].mPosCenterOrig.y + g_meterHIO.field_0x5c;
                i_Meter->mHeartShadow[i].mPosCenter.y = i_Meter->mHeartShadow[i].mPosCenterOrig.y + g_meterHIO.field_0x5c;
            }
            if (i < point) {
                pFilename = dMeter_heartTex(0);
                dMeter_heartChangeTexture(i_Meter, pFilename, i);
                if (i == point - 1) {
                    dMeter_setNowHeartScaleXY2(&i_Meter->mHeart[i]);
                    dMeter_setNowHeartScaleXY2(&i_Meter->mHeartShadow[i]);
                } else {
                    dMeter_setHeartScaleXY2(&i_Meter->mHeart[i], 0);
                    dMeter_setHeartScaleXY2(&i_Meter->mHeartShadow[i], 0);
                }
            } else if (i < 3) {
                pFilename = dMeter_heartTex(4);
                dMeter_heartChangeTexture(i_Meter, pFilename, i);
                dMeter_setHeartScaleXY2(&i_Meter->mHeart[i], 4);
                dMeter_setHeartScaleXY2(&i_Meter->mHeartShadow[i], 4);
            } else {
                dMeter_PaneHide(&i_Meter->mHeart[i]);
                dMeter_PaneHide(&i_Meter->mHeartShadow[i]);
            }
        }
    }
}

/* 801F1A48-801F1DB8       .text dMeter_heartColor__FP15sub_meter_class */
void dMeter_heartColor(sub_meter_class* i_Meter) {
    f32 dVar8;
    JUtility::TColor white(0xFF, 0xFF, 0xFF, 0xFF);
    JUtility::TColor black(0x00, 0x00, 0x00, 0x00);

    if ((daPy_getPlayerActorClass()->checkSoupPowerUp()) && (dComIfGp_getMiniGameType() != 6)) {
        JUtility::TColor white2 = -1;
        JUtility::TColor black2 = -1;
        if (i_Meter->mHeartShadow[0].mUserArea == 0) {
            i_Meter->mHeartShadow[0].mUserArea = 1;
        }
        if (i_Meter->mHeartShadow[1].mUserArea < 0x1d) {
            i_Meter->mHeartShadow[1].mUserArea++;
        } else {
            i_Meter->mHeartShadow[1].mUserArea = 0;
        }
        if (i_Meter->mHeartShadow[1].mUserArea < 0xf) {
            dVar8 = fopMsgM_valueIncrease(0xf, i_Meter->mHeartShadow[1].mUserArea, 0);
        } else {
            dVar8 = fopMsgM_valueIncrease(0xf, 0x1e - i_Meter->mHeartShadow[1].mUserArea, 0);
        }
        white2.r = ((f32)white.r - (((f32)white.r - 255.0f) * dVar8));
        white2.g = ((f32)white.g - (((f32)white.g - 255.0f) * dVar8));
        white2.b = ((f32)white.b - (((f32)white.b - 255.0f) * dVar8));
        white2.a = 0xFF;
        black2.r = ((f32)black.r - (((f32)black.r - 255.0f) * dVar8));
        black2.g = ((f32)black.g - (((f32)black.g - 255.0f) * dVar8));
        black2.b = ((f32)black.b - (((f32)black.b - 255.0f) * dVar8));
        black2.a = 0x00;
        for (s32 i = 0; i < 20; i++) {
            ((J2DPicture*)i_Meter->mHeart[i].pane)->setWhite(white2);
            ((J2DPicture*)i_Meter->mHeart[i].pane)->setBlack(black2);
        }
    } else {
        if (i_Meter->mHeartShadow[0].mUserArea == 1) {
            for (s32 i = 0; i < 20; i++) {
                ((J2DPicture*)i_Meter->mHeart[i].pane)->setWhite(white);
                ((J2DPicture*)i_Meter->mHeart[i].pane)->setBlack(black);
            }
            i_Meter->mHeartShadow[0].mUserArea = 0;
        }
    }
}

/* 801F1DB8-801F1E60       .text dMeter_heartMove__FP15sub_meter_class */
void dMeter_heartMove(sub_meter_class* i_Meter) {
    static bool flag = 0;

    if (dComIfGp_getMiniGameType() == 6) {
        dMeter_BattleLifeMove(i_Meter, flag);
        flag = true;
    } else if (flag) {
        dMeter_heartInit(i_Meter);
        flag = false;
    } else {
        dMeter_LifeMove(i_Meter, flag);
    }

    dMeter_heartColor(i_Meter);
    dMeter_heartAlpha(i_Meter);
}

/* 801F1E60-801F1EBC       .text dMeter_heartDraw__FP15sub_meter_class */
void dMeter_heartDraw(sub_meter_class* i_Meter) {
    for (int i = 0; i < 20; i++) {
        fopMsgM_setAlpha(&i_Meter->mHeart[i]);
        fopMsgM_setAlpha(&i_Meter->mHeartShadow[i]);
    }
}

/* 801F1EBC-801F1F8C       .text dMeter_weponInit__FP15sub_meter_class */
void dMeter_weponInit(sub_meter_class* i_Meter) {
    JKRArchive* pArc;
    const char* pFilename;

    i_Meter->field_0x28d0.mUserArea = 0;
    i_Meter->field_0x301a = 0;
    dComIfGp_setAStatus(dActStts_BLANK_e);
    if ((dComIfGp_getAStatus() == dActStts_RETURN_e) || (dComIfGp_getAStatus() == dActStts_RETURN_e)) {
        pArc = dComIfGp_getMenuArchive();
    } else {
        pArc = dComIfGp_getActionIconArchive();
    }
    pFilename = dMeter_actionTex(dActStts_BLANK_e);
    JKRArchive::readTypeResource(i_Meter->actionTex[0], 0xc00, 'TIMG', pFilename, pArc);
    DCStoreRangeNoSync(i_Meter->actionTex[0], 0xc00);
    ((J2DPicture*)i_Meter->field_0x2828.pane)->changeTexture(i_Meter->actionTex[0], 0);
    ((J2DPicture*)i_Meter->field_0x2860.pane)->changeTexture(i_Meter->actionTex[0], 0);
    ((J2DPicture*)i_Meter->field_0x1d00.pane)->changeTexture(i_Meter->actionTex[0], 0);
    i_Meter->field_0x2828.mUserArea = 0;
}

/* 801F1F8C-801F23B8       .text dMeter_weponMove__FP15sub_meter_class */
void dMeter_weponMove(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 sVar1;
    u8 uVar2;
    int iVar3;
    f32 dVar5;

    if (dComIfGp_getAStatusForce() != dActStts_BLANK_e) {
        dComIfGp_setAStatus(dComIfGp_getAStatusForce());
    }
    dMeter_weponChange(i_Meter);
    if (dComIfGp_getDoStatus() == dActStts_BID_e) {
        JUtility::TColor white = -1;
        JUtility::TColor black = -1;
        black.a = 0xFF;
        black.b = 0xFF;
        black.g = 0xFF;
        black.r = 0xFF;
        white.b = 0xFF;
        white.a = 0x00;
        i_Meter->field_0x1d38.mUserArea++;
        if (i_Meter->field_0x1d38.mUserArea >= 0x14) {
            i_Meter->field_0x1d38.mUserArea = 0;
        }
        iVar3 = (int)i_Meter->field_0x1d38.mUserArea;
        if (iVar3 < 10) {
            dVar5 = fopMsgM_valueIncrease(10, iVar3, 0);
        } else {
            dVar5 = fopMsgM_valueIncrease(10, 0x14 - iVar3, 0);
        }
        uVar2 = -(f32)(dVar5 * -255.0f);
        white.g = uVar2;
        white.r = uVar2;
        ((J2DPicture*)i_Meter->field_0x1d38.pane)->setWhite(black);
        ((J2DPicture*)i_Meter->field_0x1d38.pane)->setBlack(white);
        i_Meter->field_0x1d38.mNowAlpha = (i_Meter->field_0x1d00.mInitAlpha) - (i_Meter->field_0x1d00.mInitAlpha - 0x78) * dVar5;
    } else if (i_Meter->field_0x1d38.mUserArea != 0) {
        JUtility::TColor white2(0xFF, 0xFF, 0xFF, 0xFF);
        ((J2DPicture*)i_Meter->field_0x1d38.pane)->setWhite(white2);
        JUtility::TColor black2(0x00, 0x00, 0xFF, 0x00);
        ((J2DPicture*)i_Meter->field_0x1d38.pane)->setBlack(black2);
        i_Meter->field_0x1d38.mNowAlpha = i_Meter->field_0x1d00.mInitAlpha;
        i_Meter->field_0x1d38.mUserArea = 0;
    }
    if (((dComIfGp_getDoStatus() == dActStts_ba_sake__dupe_31) || (dComIfGp_getDoStatus() == dActStts_ba_nageru__dupe_2D)) ||
        (dComIfGp_getDoStatus() == dActStts_ba_motu__dupe_2E))
    {
        JUtility::TColor white = -1;
        white.a = 0x00;
        i_Meter->field_0x1e18[1].mUserArea++;
        if (i_Meter->field_0x1e18[1].mUserArea >= 0x14) {
            i_Meter->field_0x1e18[1].mUserArea = 0;
            if (dComIfGp_getDoStatus() == dActStts_ba_nageru__dupe_2D) {
                mDoAud_seStart(JA_SE_SEED_OK_BLINK);
            } else if (dComIfGp_getDoStatus() == dActStts_ba_motu__dupe_2E) {
                mDoAud_seStart(JA_SE_MD_HARP_INDICATOR);
            } else {
                mDoAud_seStart(JA_SE_ITM_OMAMORI_BLINK);
            }
        }
        iVar3 = (int)i_Meter->field_0x1e18[1].mUserArea;
        if (iVar3 < 10) {
            dVar5 = fopMsgM_valueIncrease(10, iVar3, 0);
        } else {
            dVar5 = fopMsgM_valueIncrease(10, 0x14 - iVar3, 0);
        }
        uVar2 = (dVar5 * 255.0f);
        white.b = uVar2;
        white.g = uVar2;
        white.r = uVar2;
        ((J2DPicture*)i_Meter->field_0x1e18[1].pane)->setBlack(white);
    } else if (dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        ((J2DPicture*)i_Meter->field_0x1e18[1].pane)->setBlack(0x00000000);
    }
    sVar1 = i_Meter->field_0x28d0.mUserArea;
    if ((sVar1 != 0) && (sVar1 <= 0xc)) {
        dMeter_weponAnime(i_Meter);
        i_Meter->field_0x28d0.mUserArea++;
        if (i_Meter->field_0x28d0.mUserArea > 0xc) {
            i_Meter->field_0x28d0.mUserArea = 0;
        }
    }
    dMeter_weponTrans(i_Meter);
    dMeter_weponAlpha(i_Meter);
    dComIfGp_setAStatusForce(dActStts_BLANK_e);
}

/* 801F23B8-801F2408       .text dMeter_weponDraw__FP15sub_meter_class */
void dMeter_weponDraw(sub_meter_class* i_Meter) {
    fopMsgM_setAlpha(&i_Meter->field_0x1d00);
    fopMsgM_setAlpha(&i_Meter->field_0x2828);
    fopMsgM_setAlpha(&i_Meter->field_0x2860);
    fopMsgM_setAlpha(&i_Meter->field_0x2898);
    fopMsgM_setAlpha(&i_Meter->field_0x28d0);
}

/* 801F2408-801F2688       .text dMeter_weponChange__FP15sub_meter_class */
void dMeter_weponChange(sub_meter_class* i_Meter) {
    const char* pFilename;
    JKRArchive* pArc;

    if (i_Meter->field_0x2828.mUserArea != 0) {
        if (i_Meter->field_0x301a == 0x25) {
            i_Meter->field_0x1d00.mUserArea = 0;
            ((J2DPicture*)i_Meter->field_0x1d00.pane)->setWhite(0xFFFFFFFF);
            ((J2DPicture*)i_Meter->field_0x1d00.pane)->setBlack(0x0000FF00);
        }
        if (dComIfGp_getAStatus() != dActStts_BLANK_e) {
            if (dComIfGp_getAStatus() == dActStts_sword_01) {
                pArc = dComIfGp_getItemIconArchive();
                pFilename = dMeter_weponTex();
                JKRArchive::readTypeResource(i_Meter->actionTex[0], 0xc00, 'TIMG', pFilename, pArc);
                DCStoreRangeNoSync(i_Meter->actionTex[0], 0xc00);
                ((J2DPicture*)i_Meter->field_0x2828.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x2860.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x1d00.pane)->changeTexture(i_Meter->actionTex[0], 0);
            } else if (((((dComIfGp_getAStatus() == dActStts_boko_stick) || (dComIfGp_getAStatus() == dActStts_hatchet)) ||
                         (dComIfGp_getAStatus() == dActStts_iron_club)) ||
                        (dComIfGp_getAStatus() == dActStts_longsword || (dComIfGp_getAStatus() == dActStts_spear))) ||
                       (dComIfGp_getAStatus() == dActStts_spear__dupe_3C))
            {
                pArc = dComIfGp_getItemIconArchive();
                pFilename = dMeter_actionTex(dComIfGp_getAStatus());
                JKRArchive::readTypeResource(i_Meter->actionTex[0], 0xc00, 'TIMG', pFilename, pArc);
                DCStoreRangeNoSync(i_Meter->actionTex[0], 0xc00);
                ((J2DPicture*)i_Meter->field_0x2828.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x2860.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x1d00.pane)->changeTexture(i_Meter->actionTex[0], 0);
            } else {
                if ((dComIfGp_getAStatus() == dActStts_RETURN_e) || (dComIfGp_getAStatus() == dActStts_RETURN_e)) {
                    pArc = dComIfGp_getMenuArchive();
                } else {
                    pArc = dComIfGp_getActionIconArchive();
                }
                pFilename = dMeter_actionTex(dComIfGp_getAStatus());
                JKRArchive::readTypeResource(i_Meter->actionTex[0], 0xc00, 'TIMG', pFilename, pArc);
                DCStoreRangeNoSync(i_Meter->actionTex[0], 0xc00);
                ((J2DPicture*)i_Meter->field_0x2828.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x2860.pane)->changeTexture(i_Meter->actionTex[0], 0);
                ((J2DPicture*)i_Meter->field_0x1d00.pane)->changeTexture(i_Meter->actionTex[0], 0);
            }
        }
        i_Meter->field_0x2828.mUserArea = 0;
    }
    if (i_Meter->field_0x301a != dComIfGp_getAStatus()) {
        i_Meter->field_0x2828.mUserArea = 1;
        i_Meter->field_0x28d0.mUserArea = 1;
        i_Meter->field_0x301a = dComIfGp_getAStatus();
    }
}

/* 801F2688-801F2818       .text dMeter_weponAnime__FP15sub_meter_class */
void dMeter_weponAnime(sub_meter_class* i_Meter) {
    s32 uVar1;
    f32 dVar2;

    uVar1 = i_Meter->field_0x28d0.mUserArea;
    if (uVar1 <= 7) {
        dVar2 = (((s32)(uVar1) * 5.0f) / 7.0f);
    } else if (uVar1 <= 10) {
        dVar2 = (5.0f - ((s32)(uVar1 - 7) * 13.0f) / 3.0f);
    } else {
        f32 tmp = 0.5f;
        dVar2 = -8.0f + (8.0f * (s32)(uVar1 - 10) * tmp);
    }
    i_Meter->field_0x1d00.pane->move(i_Meter->field_0x1d00.mPosTopLeft.x, i_Meter->field_0x1d00.mPosTopLeft.y + dVar2);
    i_Meter->field_0x2828.pane->move(i_Meter->field_0x2828.mPosTopLeft.x, i_Meter->field_0x2828.mPosTopLeft.y + dVar2);
    i_Meter->field_0x2860.pane->move(i_Meter->field_0x2860.mPosTopLeft.x, i_Meter->field_0x2860.mPosTopLeft.y + dVar2);
    i_Meter->field_0x2898.pane->move(i_Meter->field_0x2898.mPosTopLeft.x, i_Meter->field_0x2898.mPosTopLeft.y + dVar2);
    i_Meter->field_0x28d0.pane->move(i_Meter->field_0x28d0.mPosTopLeft.x, i_Meter->field_0x28d0.mPosTopLeft.y + dVar2);
}

/* 801F2818-801F337C       .text dMeter_weponTrans__FP15sub_meter_class */
void dMeter_weponTrans(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    static s16 moveNowFrame = 0;
    static s16 moveFlag = 0;
    static s16 moveStatus = 0;
    static f32 nowX = 0.0f;
    static f32 nowY = 0.0f;
    static f32 expX = 0.0f;
    static f32 expY = 0.0f;
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && ((dComIfGp_event_checkHind(4)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e)))) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK80_e) && (dComIfGp_getScopeMesgStatus() != fopMsgStts_UNKB_e)) ||
        (((i_Meter->mStatusFlags & dMtrStts_UNK100_e) && (dComIfGp_getAStatus() != dActStts_CANCEL_e)) || (dComIfGp_getAStatus() == dActStts_HIDDEN_e)))
    {
        if (moveStatus != 1) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 1;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK80000_e) {
        if (moveStatus != 0xb) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 0xb;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK20_e) {
        if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) {
            if (moveStatus != 9) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 2);
            }
            moveStatus = 9;
        } else if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0) {
            if ((((dMeter_Info.field_0x1 == 0) || (dMeter_Info.field_0x1 == 1)) || (dMeter_Info.field_0x1 == 2)) || (dMeter_Info.field_0x1 == 3)) {
                if (moveStatus != 8) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 2);
                }
                moveStatus = 8;
            } else if (((dMeter_Info.field_0x1 == 7) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9 || (dMeter_Info.field_0x1 == 10))) {
                if (moveStatus != 10) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 2);
                }
                moveStatus = 10;
            } else if (dMeter_Info.field_0x1 == 6) {
                if (moveStatus != 1) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 2);
                }
                moveStatus = 1;
            } else {
                if (moveStatus != 9) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 2);
                }
                moveStatus = 9;
            }
        }
    } else if (((i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e)) ||
               ((i_Meter->mStatusFlags & dMtrStts_UNK200000_e) && (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e))))
    {
        if (moveStatus != 2) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 2;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) {
        if (moveStatus != 3) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 3;
    } else if ((dMenu_flag()) && (dMenu_getPushMenuButton() == 1 || (dMenu_getMenuStatus() == 1 && (dMenu_getPushMenuButton() == 0)))) {
        if (dMenu_getItemMode() == 0) {
            if (moveStatus != 4) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 2);
            }
            moveStatus = 4;
        } else {
            if (moveStatus != 5) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 2);
            }
            moveStatus = 5;
        }
    } else if ((dMenu_flag()) && (dMenu_getPushMenuButton() == 2 || (dMenu_getMenuStatus() == 2 && (dMenu_getPushMenuButton() == 0)))) {
        if (moveStatus != 5) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 5;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) {
        if (moveStatus != 5) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 5;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK40000_e) {
        if (moveStatus != 6) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 6;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK400000_e) {
        if (moveStatus != 5) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 5;
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK100_e) && (dComIfGp_getAStatus() == dActStts_CANCEL_e)) {
        if (moveStatus != 7) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 7;
    } else {
        if (moveStatus != 0) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 2);
        }
        moveStatus = 0;
    }
    if (i_Meter->field_0x3026 != 0xf) {
        if (dMeter_isBit8(&i_Meter->field_0x3026, 2) == 0) {
            if (moveNowFrame >= 5) {
                moveNowFrame = 5;
                moveFlag = 0;
                dMeter_onBit8(&i_Meter->field_0x3026, 2);
                switch (moveStatus) {
                case 1:
                    nowX = 0.0f;
                    nowY = -200.0f;
                    break;
                case 2:
                    nowX = g_meterHIO.field_0xa2;
                    nowY = g_meterHIO.field_0xaa;
                    break;
                case 3:
                    nowX = g_meterHIO.field_0xb2;
                    nowY = g_meterHIO.field_0xba;
                    break;
                case 4:
                    nowX = g_meterHIO.field_0xc2;
                    nowY = g_meterHIO.field_0xca;
                    break;
                case 5:
                    nowX = g_meterHIO.field_0xd2;
                    nowY = g_meterHIO.field_0xda;
                    break;
                case 6:
                    nowX = g_meterHIO.field_0xe2;
                    nowY = g_meterHIO.field_0xea;
                    break;
                case 7:
                    nowX = g_meterHIO.field_0x102;
                    nowY = g_meterHIO.field_0x10a;
                    break;
                case 8:
                    nowX = g_meterHIO.field_0x112;
                    nowY = g_meterHIO.field_0x11a;
                    break;
                case 9:
                    if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) {
                        nowX = g_meterHIO.field_0x106;
                        nowY = g_meterHIO.field_0x10e;
                    } else if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0) {
                        nowX = g_meterHIO.field_0x106 - 0x21;
                        nowY = g_meterHIO.field_0x10e - 4;
                    }
                    break;
                case 10:
                    nowX = g_meterHIO.field_0x112 + 0x12;
                    nowY = g_meterHIO.field_0x11a + 3;
                    break;
                case 0xb:
                    nowX = g_meterHIO.field_0xf2;
                    nowY = g_meterHIO.field_0xfa - 0x3c;
                    break;
                default:
                    nowX = g_meterHIO.field_0xf2;
                    nowY = g_meterHIO.field_0xfa;
                    break;
                }
            } else {
                moveNowFrame++;
            }
        }
    } else {
        if ((s32)moveNowFrame <= 0) {
            moveNowFrame = 0;
        } else {
            moveNowFrame--;
        }
    }

    f32 dVar6 = fopMsgM_valueIncrease(5, moveNowFrame, 0);
    f32 x = nowX;
    f32 dVar7 = (nowY + (dVar6 * (-200.0f - nowY)));
    if (moveStatus == 10) {
        fopMsgM_paneTrans(&i_Meter->field_0x1d00, (x + expX) + 57.0f, (dVar7 + expY) + 9.0f);
    } else {
        fopMsgM_paneTrans(&i_Meter->field_0x1d00, x + expX, dVar7 + expY);
    }
    fopMsgM_paneTrans(&i_Meter->field_0x2828, x, dVar7);
    fopMsgM_paneTrans(&i_Meter->field_0x2860, x, dVar7);
    fopMsgM_paneTrans(&i_Meter->field_0x2898, x, dVar7);
    fopMsgM_paneTrans(&i_Meter->field_0x28d0, x, dVar7);
}

/* 801F337C-801F36C0       .text dMeter_weponAlpha__FP15sub_meter_class */
void dMeter_weponAlpha(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    f32 dVar4;

    static s16 alphaNowFrame = 0;
    if (((i_Meter->mStatusFlags & dMtrStts_UNK400_e) && (dComIfGp_getAStatus() == dActStts_sword_01)) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK2000_e) && (dComIfGp_getAStatus() != dActStts_SPEAK_e)) ||
        (((i_Meter->mStatusFlags & dMtrStts_UNK2_e) && (dComIfGp_getAStatus() == dActStts_sword_01)) &&
         (strcmp(dComIfGp_getStartStageName(), "Ojhous") && strcmp(dComIfGp_getStartStageName(), "Orichh"))) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK8000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10000_e)))
    {
        if (alphaNowFrame > 3) {
            alphaNowFrame--;
        } else {
            if (alphaNowFrame < 3) {
                alphaNowFrame++;
            } else {
                alphaNowFrame = 3;
            }
        }
    } else {
        if ((!(i_Meter->mStatusFlags & dMtrStts_UNK2_e)) ||
            ((dComIfGp_getAStatus() != dActStts_sword_01 && (dComIfGp_getAStatus() != dActStts_BLANK_e)) && (!dMenu_flag())) ||
            (!strcmp(dComIfGp_getStartStageName(), "Ojhous") || (!strcmp(dComIfGp_getStartStageName(), "Orichh"))))
        {
            i_Meter->field_0x3024 |= 2;
        }
        if (alphaNowFrame < 5) {
            alphaNowFrame++;
        } else {
            alphaNowFrame = 5;
        }
    }
    dVar4 = fopMsgM_valueIncrease(5, alphaNowFrame, 0);
    if (dComIfGp_getAStatus() == dActStts_BLANK_e) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1d00);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2828);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2860);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2898, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x28d0, dVar4);
    } else if ((dComIfGp_getAStatus() == dActStts_sword_01) || (dComIfGp_getAStatus() == dActStts_boko_stick) || (dComIfGp_getAStatus() == dActStts_hatchet) ||
               (dComIfGp_getAStatus() == dActStts_iron_club) || (dComIfGp_getAStatus() == dActStts_longsword) || (dComIfGp_getAStatus() == dActStts_spear) ||
               (dComIfGp_getAStatus() == dActStts_spear__dupe_3C))
    {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1d00);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2828, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2860, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2898, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x28d0, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2908, dVar4);
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1d00, dVar4);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2828);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2860);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2898, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x28d0, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2908, dVar4);
    }
    if ((dMeter_isBit8(&i_Meter->field_0x3026, 2) != 0) && (i_Meter->field_0x2828.mUserArea == 0)) {
        i_Meter->field_0x1d00.pane->show();
        i_Meter->field_0x2828.pane->show();
        i_Meter->field_0x2860.pane->show();
    } else {
        i_Meter->field_0x1d00.pane->hide();
        i_Meter->field_0x2828.pane->hide();
        i_Meter->field_0x2860.pane->hide();
    }
}

/* 801F36C0-801F3770       .text dMeter_actionInit__FP15sub_meter_class */
void dMeter_actionInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x1e18[0].mUserArea = 0;
    i_Meter->field_0x27b8.mUserArea = 0;
    i_Meter->field_0x301b = 0;
    dComIfGp_setDoStatus(dActStts_BLANK_e);
    JKRArchive* pArc = dComIfGp_getActionIconArchive();
    const char* pFilename = dMeter_actionTex(dActStts_BLANK_e);
    JKRArchive::readTypeResource(i_Meter->actionTex[1], 0xc00, 'TIMG', pFilename, pArc);
    DCStoreRangeNoSync(i_Meter->actionTex[1], 0xc00);
    ((J2DPicture*)i_Meter->field_0x27b8.pane)->changeTexture(i_Meter->actionTex[1], 0);
    ((J2DPicture*)i_Meter->field_0x27f0.pane)->changeTexture(i_Meter->actionTex[1], 0);
    ((J2DPicture*)i_Meter->field_0x1d38.pane)->changeTexture(i_Meter->actionTex[1], 0);
}

/* 801F3770-801F37E0       .text dMeter_actionMove__FP15sub_meter_class */
void dMeter_actionMove(sub_meter_class* i_Meter) {
    if (dComIfGp_getDoStatusForce() != dActStts_BLANK_e) {
        dComIfGp_setDoStatus(dComIfGp_getDoStatusForce());
    } else {
        dMeter_actionForce(i_Meter);
    }
    dMeter_actionChange(i_Meter);
    dMeter_actionTrans(i_Meter);
    dMeter_actionAlpha(i_Meter);
    dComIfGp_setDoStatusForce(dActStts_BLANK_e);
}

/* 801F37E0-801F386C       .text dMeter_actionDraw__FP15sub_meter_class */
void dMeter_actionDraw(sub_meter_class* i_Meter) {
    fopMsgM_setAlpha(&i_Meter->field_0x1d38);
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x1e18[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x1da8[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x2748);
    fopMsgM_setAlpha(&i_Meter->field_0x2780);
    fopMsgM_setAlpha(&i_Meter->field_0x27b8);
    fopMsgM_setAlpha(&i_Meter->field_0x27f0);
    fopMsgM_setAlpha(&i_Meter->field_0x2908);
}

/* 801F386C-801F3B60       .text dMeter_actionForce__FP15sub_meter_class */
void dMeter_actionForce(sub_meter_class* i_Meter) {
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(4)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e))))
    {
        dComIfGp_setDoStatus(dActStts_BLANK_e);
        return;
    }

    if ((((i_Meter->mStatusFlags & dMtrStts_UNK8_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10_e)) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK20_e))
    {
        if (dMenu_getCollectMode() != 5) {
            dComIfGp_setAStatus(dActStts_RETURN_e);
        }
        if ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) {
            if (((dMeter_Info.field_0x1 == 0) || (dMeter_Info.field_0x1 == 1 || (dMeter_Info.field_0x1 == 2))) || (dMeter_Info.field_0x1 == 3)) {
                if (dMeter_Info.field_0x1 == 0) {
                    dComIfGp_setDoStatus(dActStts_ba_zoom01);
                } else if (dMeter_Info.field_0x1 == 1) {
                    dComIfGp_setDoStatus(dActStts_ba_zoom02);
                } else if ((dMeter_Info.field_0x1 == 2) || (dMeter_Info.field_0x1 == 3)) {
                    dComIfGp_setDoStatus(dActStts_BLANK_e);
                }
                dComIfGp_setRStatus(dActStts_CHARTS_e);
                return;
            }
            if ((((dMeter_Info.field_0x1 == 7) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9)) || (dMeter_Info.field_0x1 == 10)) {
                if (dMeter_Info.field_0x1 == 10) {
                    dComIfGp_setDoStatus(dActStts_OPEN_e);
                } else {
                    dComIfGp_setDoStatus(dActStts_BLANK_e);
                }
                dComIfGp_setRStatus(dActStts_SEA_CHART_e);
                return;
            }
            if (dMeter_Info.field_0x1 == 4) {
                dComIfGp_setDoStatus(dActStts_CHOOSE_e);
                dComIfGp_setRStatus(dActStts_BLANK_e);
                return;
            }
            dComIfGp_setDoStatus(dActStts_BLANK_e);
            dComIfGp_setRStatus(dActStts_BLANK_e);
            return;
        }
        if (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) {
            dComIfGp_setDoStatus(dActStts_CHOOSE_e);
        }
        return;
    }
    if (!(i_Meter->mStatusFlags & dMtrStts_UNK100_e)) {
        return;
    }
    if (dMeter_Info.field_0x0 == 1) {
        dComIfGp_setDoStatus(dActStts_NEXT_e);
    } else if (dMeter_Info.field_0x0 == 3) {
        dComIfGp_setDoStatus(dActStts_CHOOSE_e);
    } else if (dMeter_Info.field_0x0 == 4) {
        dComIfGp_setDoStatus(dActStts_RETURN_e);
    } else {
        dComIfGp_setDoStatus(dActStts_BLANK_e);
    }
    if (dComIfGp_getDoStatusForce() != dActStts_BLANK_e) {
        dComIfGp_setDoStatusForce(dActStts_BLANK_e);
    }
    if (dComIfGp_getAStatusForce() == dActStts_BLANK_e) {
        return;
    }
    dComIfGp_setAStatus(dComIfGp_getDoStatusForce());
    dComIfGp_setAStatusForce(dActStts_BLANK_e);
}

/* 801F3B60-801F3CFC       .text dMeter_actionChange__FP15sub_meter_class */
void dMeter_actionChange(sub_meter_class* i_Meter) {
    const char* pFilename;
    JKRArchive* pArc;

    if (i_Meter->field_0x27b8.mUserArea != 0) {
        if (dComIfGp_getDoStatus() == dActStts_BLANK_e) {
            i_Meter->field_0x1e18[0].mUserArea = 1;
        } else if (dComIfGp_getDoStatus() == dActStts_PARRY_e) {
            mDoAud_seStart(JA_SE_SP_ATTACK_ON);
        } else if (((dComIfGp_getDoStatus() != dActStts_ba_sake__dupe_31) && (dComIfGp_getDoStatus() != dActStts_ba_nageru__dupe_2D)) &&
                   (dComIfGp_getDoStatus() != dActStts_ba_motu__dupe_2E))
        {
            if (dComIfGp_getDoStatus() == dActStts_bow_01) {
                pArc = dComIfGp_getItemIconArchive();
                pFilename = dMeter_actionTex(dComIfGp_getDoStatus());
                JKRArchive::readTypeResource(i_Meter->actionTex[1], 0xc00, 'TIMG', pFilename, pArc);
                DCStoreRangeNoSync(i_Meter->actionTex[1], 0xc00);
                ((J2DPicture*)i_Meter->field_0x27b8.pane)->changeTexture(i_Meter->actionTex[1], 0);
                ((J2DPicture*)i_Meter->field_0x27f0.pane)->changeTexture(i_Meter->actionTex[1], 0);
            } else {
                if ((dComIfGp_getDoStatus() == dActStts_RETURN_e) || (dComIfGp_getDoStatus() == dActStts_RETURN_e)) {
                    pArc = dComIfGp_getMenuArchive();
                } else {
                    pArc = dComIfGp_getActionIconArchive();
                }
                pFilename = dMeter_actionTex(dComIfGp_getDoStatus());
                JKRArchive::readTypeResource(i_Meter->actionTex[1], 0xc00, 'TIMG', pFilename, pArc);
                DCStoreRangeNoSync(i_Meter->actionTex[1], 0xc00);
                ((J2DPicture*)i_Meter->field_0x1d38.pane)->changeTexture(i_Meter->actionTex[1], 0);
                i_Meter->field_0x1e18[0].mUserArea = 1;
            }
        }
        i_Meter->field_0x301b = dComIfGp_getDoStatus();
        i_Meter->field_0x27b8.mUserArea = 0;
    }
    if (i_Meter->field_0x301b != dComIfGp_getDoStatus()) {
        i_Meter->field_0x27b8.mUserArea = 1;
    }
}

/* 801F3CFC-801F489C       .text dMeter_actionTrans__FP15sub_meter_class */
void dMeter_actionTrans(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    f32 dVar7;
    f32 x;

    static s16 moveNowFrame = 0;
    static s16 moveFlag = 0;
    static s16 moveStatus = 0;
    static f32 nowX = 0.0f;
    static f32 nowY = 0.0f;
    static f32 expX = 0.0f;
    static f32 expY = 0.0f;
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(2)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e))) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e)) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK200000_e) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e))) ||
        (dComIfGp_getDoStatus() == dActStts_HIDDEN_e))
    {
        if (moveStatus != 1) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 1;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK20_e) {
        if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) {
            if (moveStatus != 9) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 1);
            }
            moveStatus = 9;
        } else {
            if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0) {
                if ((((dMeter_Info.field_0x1 == 0) || (dMeter_Info.field_0x1 == 1)) || (dMeter_Info.field_0x1 == 2)) || (dMeter_Info.field_0x1 == 3)) {
                    if (moveStatus != 8) {
                        moveFlag = 1;
                        dMeter_offBit8(&i_Meter->field_0x3026, 1);
                    }
                    moveStatus = 8;
                } else if (((dMeter_Info.field_0x1 == 7) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9 || (dMeter_Info.field_0x1 == 10))) {
                    if (moveStatus != 0xb) {
                        moveFlag = 1;
                        dMeter_offBit8(&i_Meter->field_0x3026, 1);
                    }
                    moveStatus = 0xb;
                } else if ((dMeter_Info.field_0x1 == 0xb) || (dMeter_Info.field_0x1 == 6)) {
                    if (moveStatus != 1) {
                        moveFlag = 1;
                        dMeter_offBit8(&i_Meter->field_0x3026, 1);
                    }
                    moveStatus = 1;
                } else {
                    if (moveStatus != 9) {
                        moveFlag = 1;
                        dMeter_offBit8(&i_Meter->field_0x3026, 1);
                    }
                    moveStatus = 9;
                }
            }
        }
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) {
        if (moveStatus != 2) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 2;
    } else if ((dMenu_flag()) && (dMenu_getPushMenuButton() == 1 || (dMenu_getMenuStatus() == 1 && (dMenu_getPushMenuButton() == 0)))) {
        if (dMenu_getItemMode() == 0) {
            if (moveStatus != 3) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 1);
            }
            moveStatus = 3;
        } else {
            if (moveStatus != 4) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 1);
            }
            moveStatus = 4;
        }
    } else if ((dMenu_flag()) && (dMenu_getPushMenuButton() == 2 || (dMenu_getMenuStatus() == 2 && (dMenu_getPushMenuButton() == 0)))) {
        if (moveStatus != 4) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 4;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) {
        if (moveStatus != 4) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 4;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK40000_e) {
        if (moveStatus != 5) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 5;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK100_e) {
        if (moveStatus != 7) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 7;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK80000_e) {
        if (moveStatus != 6) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 6;
    } else if (i_Meter->mStatusFlags & dMtrStts_UNK400000_e) {
        if (moveStatus != 4) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 4;
    } else {
        if (moveStatus != 0) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 1);
        }
        moveStatus = 0;
    }
    if (i_Meter->field_0x3026 != 0xf) {
        if (dMeter_isBit8(&i_Meter->field_0x3026, 1) == 0) {
            if (moveNowFrame >= 5) {
                moveNowFrame = 5;
                moveFlag = 0;
                dMeter_onBit8(&i_Meter->field_0x3026, 1);
                switch (moveStatus) {
                case 1:
                    nowX = 0.0f;
                    nowY = -200.0f;
                    break;
                case 2:
                    nowX = g_meterHIO.field_0xb0;
                    nowY = g_meterHIO.field_0xb8;
                    break;
                case 3:
                    nowX = g_meterHIO.field_0xc0;
                    nowY = g_meterHIO.field_0xc8;
                    break;
                case 4:
                    nowX = g_meterHIO.field_0xd0;
                    nowY = g_meterHIO.field_0xd8;
                    break;
                case 5:
                    nowX = g_meterHIO.field_0xe0;
                    nowY = g_meterHIO.field_0xe8;
                    break;
                case 6:
                    nowX = g_meterHIO.field_0xe4;
                    nowY = g_meterHIO.field_0xec;
                    break;
                case 7:
                    nowX = g_meterHIO.field_0x100;
                    nowY = g_meterHIO.field_0x108;
                    break;
                case 8:
                    nowX = g_meterHIO.field_0x110;
                    nowY = g_meterHIO.field_0x118;
                    break;
                case 9:
                    if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) {
                        nowX = g_meterHIO.field_0x104;
                        nowY = g_meterHIO.field_0x10c;
                    } else {
                        if (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0) {
                            nowX = g_meterHIO.field_0x104 - 10;
                            nowY = g_meterHIO.field_0x10c - 3;
                        }
                    }
                    break;
                case 10:
                    nowX = g_meterHIO.field_0x110 + 0x2e;
                    nowY = g_meterHIO.field_0x118 - 0x17;
                    break;
                case 0xb:
                    nowX = g_meterHIO.field_0x110 + 0x2a;
                    nowY = g_meterHIO.field_0x118 - 3;
                    break;
                default:
                    nowX = g_meterHIO.field_0xf0;
                    nowY = g_meterHIO.field_0xf8;
                    break;
                }
                if (moveStatus == 2) {
                    expX = g_meterHIO.field_0xb4;
                    expY = g_meterHIO.field_0xbc;
                } else {
                    expX = 0.0f;
                    expY = 0.0f;
                }
            } else {
                moveNowFrame++;
            }
        }
    } else {
        if ((s32)moveNowFrame <= 0) {
            moveNowFrame = 0;
        } else {
            moveNowFrame--;
        }
    }
    dVar7 = fopMsgM_valueIncrease(5, moveNowFrame, 0);
    x = nowX;
    f32 dVar8 = (nowY + (dVar7 * (-200.0f - nowY)));
    if (moveStatus == 10) {
        fopMsgM_paneTrans(&i_Meter->field_0x1d38, (x + 27.0f), (dVar8 + 14.0f));
    } else {
        fopMsgM_paneTrans(&i_Meter->field_0x1d38, x, dVar8);
    }
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_paneTrans(&i_Meter->field_0x1e18[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x1da8[i], x, dVar8);
    }
    fopMsgM_paneTrans(&i_Meter->field_0x2748, x, dVar8);
    fopMsgM_paneTrans(&i_Meter->field_0x2780, x, dVar8);
    fopMsgM_paneTrans(&i_Meter->field_0x27b8, x, dVar8);
    fopMsgM_paneTrans(&i_Meter->field_0x27f0, x, dVar8);
    fopMsgM_paneTrans(&i_Meter->field_0x2908, x, dVar8);
}

/* 801F489C-801F4C80       .text dMeter_actionAlpha__FP15sub_meter_class */
void dMeter_actionAlpha(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    int iVar1;
    daNpc_So_c* pfVar2;
    f32 dVar2;

    static s16 alphaNowFrame = 0;
    if (((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) &&
        (dMeter_Info.field_0x1 == 2 ||
         (((dMeter_Info.field_0x1 == 3 || (dMeter_Info.field_0x1 == 7)) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9))))
    {
        if (alphaNowFrame > 3) {
            alphaNowFrame--;
        } else if (alphaNowFrame < 3) {
            alphaNowFrame++;
        } else {
            alphaNowFrame = 3;
        }
    } else {
        i_Meter->field_0x3024 |= 1;
        if (alphaNowFrame < 5) {
            alphaNowFrame++;
        } else {
            alphaNowFrame = 5;
        }
    }
    dVar2 = fopMsgM_valueIncrease(5, (int)alphaNowFrame, 0);
    if (dComIfGp_getMiniGameType() == 8) {
        pfVar2 = (daNpc_So_c*)fopAcM_SearchByName(PROC_NPC_SO);
        if (pfVar2 != NULL) {
            iVar1 = pfVar2->getMiniGameRestArrow();
            if (iVar1 < 10) {
                dMeter_PaneHide(&i_Meter->field_0x2748);
            } else {
                dMeter_PaneShow(&i_Meter->field_0x2748);
                dMeter_numberSet(i_Meter->field_0x2748.pane, iVar1 / 10 & 0xff);
            }
            dMeter_PaneShow(&i_Meter->field_0x2780);
            dMeter_numberSet(i_Meter->field_0x2780.pane, iVar1 % 10 & 0xff);
        }
    } else {
        i_Meter->field_0x2748.pane->hide();
        i_Meter->field_0x2780.pane->hide();
    }
    if (dComIfGp_getDoStatus() == dActStts_BLANK_e) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1d38);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1e18[1]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1da8[1]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2748);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2780);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27b8);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27f0);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1e18[0], dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1da8[0], dVar2);
    } else if (((dComIfGp_getDoStatus() == dActStts_PARRY_e) || (dComIfGp_getDoStatus() == dActStts_ba_sake__dupe_31)) ||
               (dComIfGp_getDoStatus() == dActStts_ba_nageru__dupe_2D || (dComIfGp_getDoStatus() == dActStts_ba_motu__dupe_2E)))
    {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1d38);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1e18[1], dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1da8[1], dVar2);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1e18[0]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1da8[0]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2748);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2780);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27b8);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27f0);
    } else if (dComIfGp_getDoStatus() == dActStts_bow_01) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1d38);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1e18[1]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1da8[1]);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1e18[0], dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1da8[0], dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2748, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2780, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x27b8, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x27f0, dVar2);
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1d38, dVar2);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1e18[1]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1da8[1]);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1e18[0], dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1da8[0], dVar2);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2748);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2780);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27b8);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x27f0);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x2908, dVar2);
    if ((dMeter_isBit8(&i_Meter->field_0x3026, 1) != 0) && (i_Meter->field_0x27b8.mUserArea == 0)) {
        i_Meter->field_0x1d38.pane->show();
        i_Meter->field_0x27b8.pane->show();
        i_Meter->field_0x27f0.pane->show();
    } else {
        i_Meter->field_0x1d38.pane->hide();
        i_Meter->field_0x2748.pane->hide();
        i_Meter->field_0x2780.pane->hide();
        i_Meter->field_0x27b8.pane->hide();
        i_Meter->field_0x27f0.pane->hide();
    }
}

/* 801F4C80-801F4CC4       .text dMeter_numberSet__FP7J2DPaneUc */
void dMeter_numberSet(J2DPane* param_1, u8 param_2) {
    static const char* number[] = {
        "count_num_0.bti",
        "count_num_1.bti",
        "count_num_2.bti",
        "count_num_3.bti",
        "count_num_4.bti",
        "count_num_5.bti",
        "count_num_6.bti",
        "count_num_7.bti",
        "count_num_8.bti",
        "count_num_9.bti",
    };

    if (param_2 >= 10) {
        param_2 = 0;
    }
    ((J2DPicture*)param_1)->changeTexture(number[param_2], 0);
}

/* 801F4CC4-801F4E04       .text dMeter_numberColor__FP7J2DPaneUcUc */
void dMeter_numberColor(J2DPane* param_1, u8 param_2, u8 param_3) {
    if (param_2 == 0) {
        ((J2DPicture*)param_1)->setWhite(0xb4b4b4ff);
        ((J2DPicture*)param_1)->setBlack(0x1e1e1e00);
    } else if (param_2 == param_3) {
        ((J2DPicture*)param_1)->setWhite(0xffc832ff);
        ((J2DPicture*)param_1)->setBlack(0x1e1e1e00);
    } else {
        ((J2DPicture*)param_1)->setWhite(0xffffffff);
        ((J2DPicture*)param_1)->setBlack(0x00000000);
    }
}

/* 801F4E04-801F4FEC       .text dMeter_xyInit__FP15sub_meter_class */
void dMeter_xyInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x2550[0].mUserArea = 0;
    i_Meter->field_0x2f2c[0] = NULL;
    i_Meter->field_0x2f2c[1] = NULL;
    for (s32 i = 0; i < 8; i++) {
        dMenu_baitNum[i] = dComIfGs_getBaitNum(i);
    }
    for (int i = 0; i < 3; i++) {
        dComIfGp_setSelectItem(i);
        i_Meter->field_0x3021[i] = dComIfGp_getSelectItem(i);
        dMeter_xyItemChange(i_Meter, i);
    }
}

/* 801F4FEC-801F5248       .text dMeter_xyMove__FP15sub_meter_class */
void dMeter_xyMove(sub_meter_class* i_Meter) {
    u8 dVar1;
    bool bVar2;
    bool bVar3;
    cXyz local_38;

    bVar2 = true;
    bVar3 = false;
    for (s32 i = 0; i < 3; i++) {
        if (i_Meter->field_0x3021[i] != dComIfGp_getSelectItem(i)) {
            dMeter_xyItemChange(i_Meter, i);
            bVar2 = false;
            if ((dComIfGp_getSelectItem(i) != dItem_MAGIC_ARROW_e) && (dComIfGp_getSelectItem(i) != dItem_LIGHT_ARROW_e)) {
                i_Meter->field_0x2320[i].pane->hide();
                i_Meter->field_0x23c8[i].pane->hide();
                i_Meter->field_0x2470[i].pane->hide();
                i_Meter->field_0x2320[i].mUserArea = 0;
            }
            i_Meter->field_0x3021[i] = dComIfGp_getSelectItem(i);
        }
    }
    if (bVar2) {
        dMeter_xyItemCountUp(i_Meter);
    }
    dMeter_xyTrans(i_Meter);
    for (s32 i = 0; i < 3; i++) {
        dVar1 = g_dComIfG_gameInfo.play.mSelectItem[i];
        if ((dVar1 == dItem_MAGIC_ARROW_e) || (dVar1 == dItem_LIGHT_ARROW_e)) {
            dMeter_xyBowLightAnime(i_Meter, i);
        } else if (dVar1 == dItem_FOREST_WATER_e) {
            bVar3 = true;
            local_38.set(i_Meter->field_0x2080[i].mPosCenter.x - 320.0f, i_Meter->field_0x2080[i].mPosCenter.y - 240.0f, 0.0f);
            for (s32 j = 0; j < 2; j++) {
                if (i_Meter->field_0x2f2c[j] != NULL) {
                    i_Meter->field_0x2f2c[j]->setGlobalTranslation(local_38.x, local_38.y, local_38.z);
                    i_Meter->field_0x2f2c[j]->playDrawParticle();
                    i_Meter->field_0x2f2c[j]->setGlobalAlpha(i_Meter->field_0x2080[i].mNowAlpha);
                } else {
                    i_Meter->field_0x2f2c[j] = dComIfGp_particle_set2DmenuFore(dPa_name::ID_COMMON_002D, &local_38);
                }
            }
        }
    }
    if (!bVar3) {
        for (s32 i = 0; i < 2; i++) {
            if (i_Meter->field_0x2f2c[i] != NULL) {
                i_Meter->field_0x2f2c[i]->becomeInvalidEmitter();
                i_Meter->field_0x2f2c[i]->quitImmortalEmitter();
                i_Meter->field_0x2f2c[i] = NULL;
            }
        }
    }
    dMeter_xyAlpha(i_Meter);
}

/* 801F5248-801F5308       .text dMeter_xyDraw__FP15sub_meter_class */
void dMeter_xyDraw(sub_meter_class* i_Meter) {
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x1fd8[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x1f30[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2080[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2128[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2320[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x23c8[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2470[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x2518);
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x2550[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x25c0[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2630[i]);
    }
}

/* 801F5308-801F543C       .text dMeter_xyEquipItem__Fi */
int dMeter_xyEquipItem(int param_1) {
    u8 dVar2;
    u8 uVar3;

    param_1 = dComIfGs_getSelectItem(param_1);
    if (param_1 < dInvSlot_ItemLast_e) {
        dVar2 = g_dComIfG_gameInfo.save.getPlayer().getItem().getItem(param_1);
    } else if (param_1 < dInvSlot_BeastFirst_e) {
        dVar2 = dItem_NONE_e;
    } else if (param_1 < dInvSlot_BeastLast_e) {
        dVar2 = dComIfGs_getItemBeast(param_1 - dInvSlot_BeastFirst_e);
    } else if (param_1 < dInvSlot_BaitFirst_e) {
        dVar2 = dItem_NONE_e;
    } else if (param_1 < dInvSlot_BaitLast_e) {
        dVar2 = dComIfGs_getItemBait(param_1 - dInvSlot_BaitFirst_e);
    } else if (param_1 < dInvSlot_ReserveFirst_e) {
        dVar2 = dItem_NONE_e;
    } else if (param_1 < dInvSlot_ReserveLast_e) {
        dVar2 = dComIfGs_getItemReserve(param_1 - dInvSlot_ReserveFirst_e);
    } else {
        dVar2 = dItem_NONE_e;
    }
    uVar3 = 0;
    switch (dVar2) {
    case dItem_SKULL_NECKLACE_e:
        uVar3 = 0;
        break;
    case dItem_BOKOBABA_SEED_e:
        uVar3 = 1;
        break;
    case dItem_GOLDEN_FEATHER_e:
        uVar3 = 2;
        break;
    case BOKO_BELT:
        uVar3 = 3;
        break;
    case dItem_RED_JELLY_e:
        uVar3 = 4;
        break;
    case dItem_GREEN_JELLY_e:
        uVar3 = 5;
        break;
    case dItem_BLUE_JELLY_e:
        uVar3 = 6;
        break;
    case dItem_JOY_PENDANT_e:
        uVar3 = 7;
        break;
    }
    return uVar3;
}

/* 801F543C-801F57B0       .text dMeter_xyItemNumberSet__FP15sub_meter_classi */
void dMeter_xyItemNumberSet(sub_meter_class* i_Meter, int param_2) {
    if ((dComIfGp_getSelectItem(param_2) == CAMERA) || (dComIfGp_getSelectItem(param_2) == CAMERA2)) {
        dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
        dMeter_PaneShow(&i_Meter->field_0x1fd8[param_2]);
        dMeter_numberSet(i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getPictureNum());
        dMeter_numberColor((J2DPicture*)i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getPictureNum(), 3);
    } else if ((dComIfGp_getSelectItem(param_2) == dItem_BOW_e) ||
               (dComIfGp_getSelectItem(param_2) == dItem_MAGIC_ARROW_e || (dComIfGp_getSelectItem(param_2) == dItem_LIGHT_ARROW_e)))
    {
        dMeter_PaneShow(&i_Meter->field_0x1f30[param_2]);
        dMeter_PaneShow(&i_Meter->field_0x1fd8[param_2]);
        if (dComIfGs_getArrowNum() < 10) {
            dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
        } else {
            dMeter_numberSet(i_Meter->field_0x1f30[param_2].pane, dComIfGs_getArrowNum() / 10);
            dMeter_numberColor((J2DPicture*)i_Meter->field_0x1f30[param_2].pane, dComIfGs_getArrowNum(), dComIfGs_getArrowMax());
        }
        dMeter_numberSet(i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getArrowNum() % 10);
        dMeter_numberColor((J2DPicture*)i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getArrowNum(), dComIfGs_getArrowMax());
    } else if (dComIfGp_getSelectItem(param_2) == dItem_BOMB_BAG_e) {
        dMeter_PaneShow(&i_Meter->field_0x1f30[param_2]);
        dMeter_PaneShow(&i_Meter->field_0x1fd8[param_2]);
        if (dComIfGs_getBombNum() < 10) {
            dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
        } else {
            dMeter_numberSet(i_Meter->field_0x1f30[param_2].pane, dComIfGs_getBombNum() / 10);
            dMeter_numberColor((J2DPicture*)i_Meter->field_0x1f30[param_2].pane, dComIfGs_getBombNum(), dComIfGs_getBombMax());
        }
        dMeter_numberSet(i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBombNum() % 10);
        dMeter_numberColor((J2DPicture*)i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBombNum(), dComIfGs_getBombMax());
    } else {
        if ((dComIfGs_getSelectItem(param_2) >= dInvSlot_BeastFirst_e) && (dComIfGs_getSelectItem(param_2) <= dInvSlot_BeastLast_e - 1)) {
            dMeter_PaneShow(&i_Meter->field_0x1f30[param_2]);
            dMeter_PaneShow(&i_Meter->field_0x1fd8[param_2]);
            int iVar3 = dMeter_xyEquipItem(param_2);
            if (dComIfGs_getBeastNum(iVar3) < 10) {
                dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
            } else {
                dMeter_numberSet(i_Meter->field_0x1f30[param_2].pane, dComIfGs_getBeastNum(iVar3) / 10);
                dMeter_numberColor((J2DPicture*)i_Meter->field_0x1f30[param_2].pane, dComIfGs_getBeastNum(iVar3), 99);
            }
            dMeter_numberSet(i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBeastNum(iVar3) % 10);
            dMeter_numberColor((J2DPicture*)i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBeastNum(iVar3), 99);
        } else {
            if ((dComIfGs_getSelectItem(param_2) >= dInvSlot_BaitFirst_e) && (dComIfGs_getSelectItem(param_2) <= dInvSlot_BaitLast_e - 1)) {
                if (dComIfGp_getSelectItem(param_2) == dItem_HYOI_PEAR_e) {
                    dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
                    dMeter_PaneHide(&i_Meter->field_0x1fd8[param_2]);
                } else {
                    dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
                    dMeter_PaneShow(&i_Meter->field_0x1fd8[param_2]);
                    dMeter_numberSet(i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBaitNum(dComIfGs_getSelectItem(param_2) - dInvSlot_BaitFirst_e));
                    dMeter_numberColor(
                        (J2DPicture*)i_Meter->field_0x1fd8[param_2].pane, dComIfGs_getBaitNum(dComIfGs_getSelectItem(param_2) - dInvSlot_BaitFirst_e), 3
                    );
                }
            } else {
                dMeter_PaneHide(&i_Meter->field_0x1f30[param_2]);
                dMeter_PaneHide(&i_Meter->field_0x1fd8[param_2]);
            }
        }
    }
}

/* 801F57B0-801F58E4       .text dMeter_xyBowLightAnime__FP15sub_meter_classi */
void dMeter_xyBowLightAnime(sub_meter_class* i_Meter, int param_2) {
    /* Nonmatching */
    int iVar2;
    f32 dVar4;
    f32 dVar5;
    f32 lVar6;

    i_Meter->field_0x2320[0].mUserArea++;
    if (i_Meter->field_0x2320[param_2].mUserArea >= 0x78) {
        i_Meter->field_0x2320[param_2].mUserArea = 0;
    }
    iVar2 = (int)i_Meter->field_0x2320[param_2].mUserArea;
    if (iVar2 < 0x3c) {
        dVar4 = fopMsgM_valueIncrease(0x3c, iVar2, 0);
    } else {
        dVar4 = fopMsgM_valueIncrease(0x3c, 0x78 - iVar2, 0);
    }
    dVar5 = (1.0f - (dVar4 * 0.39999998f));
    lVar6 = ((i_Meter->field_0x2320[0].mInitAlpha) - ((i_Meter->field_0x2320[0].mInitAlpha - 50.0f) * dVar4));
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_paneScaleXY(&(&i_Meter->field_0x2320[param_2])[i], dVar5);
        (&i_Meter->field_0x2320[param_2].mNowAlpha)[i] = lVar6;
    }
}

/* 801F58E4-801F5C98       .text dMeter_xyItemCountUp__FP15sub_meter_class */
void dMeter_xyItemCountUp(sub_meter_class* i_Meter) {
    /* Nonmatching */
    u8 uVar2;
    bool bVar3;
    s16 sVar4;
    s16 uVar5;
    s32 uVar8;

    bVar3 = false;
    static u8 arrowMax = dComIfGs_getArrowMax();
    static u8 bombMax = dComIfGs_getBombMax();
    if (g_dComIfG_gameInfo.play.field_0x48de != 0) {
        sVar4 = dComIfGs_getPictureNum() + g_dComIfG_gameInfo.play.field_0x48de;
        g_dComIfG_gameInfo.play.field_0x48de = 0;
        if (sVar4 < 0) {
            sVar4 = 0;
        }
        if (sVar4 > 3) {
            sVar4 = 3;
        }
        dComIfGs_setPictureNum(sVar4);
        bVar3 = true;
    }
    if ((((dComIfGs_checkGetItem(dItem_BOW_e)) || (dComIfGs_checkGetItem(dItem_MAGIC_ARROW_e)) || (dComIfGs_checkGetItem(dItem_LIGHT_ARROW_e))) &&
         (dComIfGp_getItemArrowNumCount() != 0)) ||
        (arrowMax != dComIfGs_getArrowMax()))
    {
        if (g_meterHIO.field_0x62 != 0) {
            g_dComIfG_gameInfo.play.mItemArrowNumCount = 0;
        }
        uVar5 = dComIfGs_getArrowNum() + dComIfGp_getItemArrowNumCount();
        g_dComIfG_gameInfo.play.mItemArrowNumCount = 0;
        if (uVar5 < 0) {
            uVar5 = 0;
        }
        if (uVar5 > dComIfGs_getArrowMax()) {
            uVar5 = dComIfGs_getArrowMax();
        }
        dComIfGs_setArrowNum(uVar5);
        arrowMax = dComIfGs_getArrowMax();
        bVar3 = 1;
    }
    if (((dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) && (dComIfGp_getItemBombNumCount() != 0)) || (bombMax != dComIfGs_getBombMax())) {
        if (g_meterHIO.field_0x63 != 0) {
            g_dComIfG_gameInfo.play.mItemBombNumCount = 0;
        }
        s16 uVar5_2 = dComIfGs_getBombNum() + dComIfGp_getItemBombNumCount();
        g_dComIfG_gameInfo.play.mItemBombNumCount = 0;
        if (uVar5_2 < 0) {
            uVar5_2 = 0;
        }
        if (uVar5_2 > dComIfGs_getBombMax()) {
            uVar5_2 = dComIfGs_getBombMax();
        }
        dComIfGs_setBombNum(uVar5_2);
        bombMax = dComIfGs_getBombMax();
        bVar3 = 1;
    }
    for (s32 i = 0; i < 8; i++) {
        if (g_dComIfG_gameInfo.play.mItemBeastNumCounts[i] != 0) {
            sVar4 = dComIfGs_getBeastNum(i) + g_dComIfG_gameInfo.play.mItemBeastNumCounts[i];
            g_dComIfG_gameInfo.play.mItemBeastNumCounts[i] = 0;
            if (sVar4 <= 0) {
                dComIfGs_setBeastNum(i, 0);
                for (s32 j = 0; j < 3; j++) {
                    if (dComIfGp_getSelectItem(j) == fopMsgM_itemNumIdx(i + 0x18)) {
                        dMeter_PaneHide(&i_Meter->field_0x2080[j]);
                        dMeter_PaneHide(&i_Meter->field_0x2128[j]);
                        dMeter_PaneHide(&i_Meter->field_0x1f30[j]);
                        dMeter_PaneHide(&i_Meter->field_0x1fd8[j]);
                    }
                }
                uVar8 = fopMsgM_itemNumIdx(i + 0x18);
                g_dComIfG_gameInfo.save.mSavedata.mPlayer.mBagItem.setBeastItemEmpty(uVar8);
                bVar3 = true;
            } else {
                if (sVar4 > 99) {
                    sVar4 = 99;
                }
                dComIfGs_setBeastNum(i, sVar4);
                bVar3 = true;
            }
        }
        uVar2 = dComIfGs_getBaitNum(i);
        if (dMenu_baitNum[i] != uVar2) {
            dMenu_baitNum[i] = uVar2;
            bVar3 = true;
        }
    }
    for (s32 i = 0; i < 3; i++) {
        if (dComIfGp_getSelectItem(i) == dItem_BIRD_BAIT_5_e) {
            bVar3 = true;
        }
    }
    if (bVar3) {
        for (s32 i = 0; i < 3; i++) {
            dMeter_xyItemNumberSet(i_Meter, i);
        }
    }
}

/* 801F5C98-801F5FDC       .text dMeter_xyItemChange__FP15sub_meter_classi */
void dMeter_xyItemChange(sub_meter_class* i_Meter, int param_2) {
    JKRArchive* pArc;
    const char* pFilename;

    if (dComIfGp_getSelectItem(param_2) != dItem_NONE_e) {
        if (dComIfGs_getSelectItem(param_2) >= dInvSlot_ReserveFirst_e) {
            dMeter_PaneShow(&i_Meter->field_0x2080[param_2]);
            dMeter_PaneShow(&i_Meter->field_0x2128[param_2]);
            pArc = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGp_getSelectItem(param_2));
            JKRArchive::readTypeResource(i_Meter->xyIconTex[param_2], 0xc00, 'TIMG', pFilename, pArc);
            DCStoreRangeNoSync(i_Meter->xyIconTex[param_2], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2080[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
            ((J2DPicture*)i_Meter->field_0x2128[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
        } else if (dComIfGs_getSelectItem(param_2) >= dInvSlot_BaitFirst_e) {
            dMeter_PaneShow(&i_Meter->field_0x2080[param_2]);
            dMeter_PaneShow(&i_Meter->field_0x2128[param_2]);
            pArc = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGp_getSelectItem(param_2));
            JKRArchive::readTypeResource(i_Meter->xyIconTex[param_2], 0xc00, 'TIMG', pFilename, pArc);
            DCStoreRangeNoSync(i_Meter->xyIconTex[param_2], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2080[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
            ((J2DPicture*)i_Meter->field_0x2128[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
        } else if (dComIfGs_getSelectItem(param_2) >= dInvSlot_BeastFirst_e) {
            dMeter_PaneShow(&i_Meter->field_0x2080[param_2]);
            dMeter_PaneShow(&i_Meter->field_0x2128[param_2]);
            pArc = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGp_getSelectItem(param_2));
            JKRArchive::readTypeResource(i_Meter->xyIconTex[param_2], 0xc00, 'TIMG', pFilename, pArc);
            DCStoreRangeNoSync(i_Meter->xyIconTex[param_2], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2080[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
            ((J2DPicture*)i_Meter->field_0x2128[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
        } else {
            dMeter_PaneShow(&i_Meter->field_0x2080[param_2]);
            dMeter_PaneShow(&i_Meter->field_0x2128[param_2]);
            u8 uVar2 = dComIfGp_getSelectItem(param_2);
            u8 var_r4 = uVar2;
            if (uVar2 == dItem_MAGIC_ARROW_e) {
                i_Meter->field_0x2320[param_2].pane->show();
                i_Meter->field_0x23c8[param_2].pane->show();
                i_Meter->field_0x2470[param_2].pane->hide();
                var_r4 = dItem_BOW_e;
            } else if (uVar2 == dItem_LIGHT_ARROW_e) {
                i_Meter->field_0x2320[param_2].pane->show();
                i_Meter->field_0x23c8[param_2].pane->show();
                i_Meter->field_0x2470[param_2].pane->show();
                var_r4 = dItem_BOW_e;
            }
            if ((var_r4 == dItem_MAGIC_ARROW_e) || (var_r4 == dItem_LIGHT_ARROW_e)) {
                var_r4 = dItem_BOW_e;
            }
            pArc = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(var_r4);
            JKRArchive::readTypeResource(i_Meter->xyIconTex[param_2], 0xc00, 'TIMG', pFilename, pArc);
            DCStoreRangeNoSync(i_Meter->xyIconTex[param_2], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2080[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
            ((J2DPicture*)i_Meter->field_0x2128[param_2].pane)->changeTexture(i_Meter->xyIconTex[param_2], 0);
        }
    } else {
        dMeter_PaneHide(&i_Meter->field_0x2080[param_2]);
        dMeter_PaneHide(&i_Meter->field_0x2128[param_2]);
    }
    dMeter_xyItemNumberSet(i_Meter, param_2);
}

/* 801F5FDC-801F6084       .text dMeter_xyRotateZ__FP18fopMsgM_pane_classff */
void dMeter_xyRotateZ(fopMsgM_pane_class* param_1, f32 param_2, f32 param_3) {
    s32 x = param_1->mSize.x * 0.5f;
    s32 y = param_1->mSize.y * 0.5f;
    param_1->pane->rotate(x, y, ROTATE_Z, param_2 + param_3);
}

/* 801F6084-801F69A0       .text dMeter_xyAlpha__FP15sub_meter_class */
void dMeter_xyAlpha(sub_meter_class* i_Meter) {
    u8 dVar2;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;

    static s16 alphaNowFrame[] = {0x0000, 0x0000, 0x0000};

    if ((!(i_Meter->mStatusFlags & dMtrStts_UNK4000_e)) && ((!(i_Meter->mStatusFlags & dMtrStts_UNK40_e)) || (!(dComIfGp_event_checkHind(1))))) {
        if ((((((!(i_Meter->mStatusFlags & dMtrStts_UNK100_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e))) &&
               (!(i_Meter->mStatusFlags & dMtrStts_UNK800000_e))) &&
              (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e) || (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) != 1))) &&
             (!(i_Meter->mStatusFlags & dMtrStts_UNK80_e) &&
              (!(i_Meter->mStatusFlags & dMtrStts_UNK100000_e) && (!(i_Meter->mStatusFlags & dMtrStts_UNK200000_e))))) &&
            (!(i_Meter->mStatusFlags & dMtrStts_UNK20000_e) &&
             ((!(i_Meter->mStatusFlags & dMtrStts_UNK40000_e) && (!(i_Meter->mStatusFlags & dMtrStts_UNK80000_e))) &&
              (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e)))))
        {
            if (i_Meter->mStatusFlags & dMtrStts_UNK8_e) {
                for (s32 i = 0; i < 3; i++) {
                    if (alphaNowFrame[i] < 5) {
                        alphaNowFrame[i]++;
                    } else {
                        alphaNowFrame[i] = 5;
                    }
                }
            } else if ((!(i_Meter->mStatusFlags & dMtrStts_UNK8_e)) &&
                       (((i_Meter->mStatusFlags & dMtrStts_UNK800_e) || (i_Meter->mStatusFlags & dMtrStts_UNK2000_e)) ||
                        ((i_Meter->mStatusFlags & dMtrStts_UNK8000_e) ||
                         ((i_Meter->mStatusFlags & dMtrStts_UNK200_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10000_e)))))
            {
                for (s32 i = 0; i < 3; i++) {
                    if (alphaNowFrame[i] > 3) {
                        alphaNowFrame[i]--;
                    } else {
                        if (alphaNowFrame[i] < 3) {
                            alphaNowFrame[i]++;
                        } else {
                            alphaNowFrame[i] = 3;
                        }
                    }
                }
            } else {
                if ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) {
                    for (s32 i = 0; i < 3; i++) {
                        if (i == 1) {
                            if (alphaNowFrame[i] < 5) {
                                alphaNowFrame[i]++;
                            } else {
                                alphaNowFrame[i] = 5;
                            }
                        } else if ((s32)alphaNowFrame[i] > 0) {
                            alphaNowFrame[i] = alphaNowFrame[i] + -1;
                        } else {
                            alphaNowFrame[i] = 0;
                        }
                    }
                } else {
                    for (s32 i = 0; i < 3; i++) {
                        if (((i_Meter->mStatusFlags & dMtrStts_UNK1000_e) && (dComIfGp_getSelectItem(i) != dItem_GRAPPLING_HOOK_e)) ||
                            ((i_Meter->mStatusFlags & dMtrStts_UNK80_e) && (dComIfGp_getSelectItem(i) != dItem_TELESCOPE_e)) ||
                            ((i_Meter->mStatusFlags & dMtrStts_UNK20000_e) &&
                             ((dVar2 = dComIfGp_getSelectItem(i), ((dVar2 == CAMERA) == 0)) || (dVar2 != CAMERA2))) ||
                            ((i_Meter->mStatusFlags & dMtrStts_UNK400_e) && (dComIfGp_getMiniGameType() != 1) &&
                             (dVar2 = dComIfGp_getSelectItem(i), ((dVar2 == NORMAL_SAIL) == 0)) && (dVar2 != dItem_TELESCOPE_e) &&
                             (dVar2 != dItem_WIND_WAKER_e) && (dVar2 != dItem_GRAPPLING_HOOK_e) && (dVar2 != dItem_BOOMERANG_e) &&
                             (dVar2 != dItem_TINGLE_TUNER_e) && (dVar2 != CAMERA) && (dVar2 != CAMERA2) && (dVar2 != dItem_MAGIC_ARMOR_e) &&
                             (dVar2 != dItem_BAIT_BAG_e) && (dVar2 != dItem_HYOI_PEAR_e) && (dVar2 != dItem_BIRD_BAIT_5_e) && (dVar2 != dItem_BOW_e) &&
                             (dVar2 != dItem_MAGIC_ARROW_e) && (dVar2 != dItem_LIGHT_ARROW_e) && (dVar2 != dItem_BOMB_BAG_e) && (dVar2 != dItem_HOOKSHOT_e) &&
                             (dVar2 != dItem_EMPTY_BOTTLE_e) && (dVar2 != dItem_RED_POTION_e) && (dVar2 != dItem_GREEN_POTION_e) &&
                             (dVar2 != dItem_BLUE_POTION_e) && (dVar2 != dItem_HALF_SOUP_BOTTLE_e) && (dVar2 != dItem_SOUP_BOTTLE_e) &&
                             (dVar2 != dItem_WATER_BOTTLE_e) && (dVar2 != dItem_FAIRY_BOTTLE_e) && (dVar2 != dItem_FIREFLY_BOTTLE_e) &&
                             (dVar2 != dItem_FOREST_WATER_e)) ||
                            ((dComIfGp_getMiniGameType() == 1) && (dVar2 = dComIfGp_getSelectItem(i), ((dVar2 == NORMAL_SAIL) == 0)) &&
                             (dVar2 != dItem_TELESCOPE_e)) ||
                            ((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_BOSS_e) &&
                             ((strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0) || (strcmp(dComIfGp_getStartStageName(), "Xboss1") == 0) ||
                              (strcmp(dComIfGp_getStartStageName(), "Xboss2") == 0) || (strcmp(dComIfGp_getStartStageName(), "Xboss3") == 0)) &&
                             ((dVar2 = dComIfGp_getSelectItem(i), (dVar2 == dItem_WATER_BOTTLE_e)) || ((u8)dVar2 == dItem_FIREFLY_BOTTLE_e) ||
                              (dVar2 == dItem_FOREST_WATER_e))) ||
                            ((i_Meter->mStatusFlags & dMtrStts_UNK2_e) && (dVar2 = dComIfGp_getSelectItem(i), (dVar2 == dItem_TINGLE_TUNER_e) == 0) &&
                             ((dVar2 != dItem_WIND_WAKER_e) || (strcmp(dComIfGp_getStartStageName(), "Otkura") != 0)) &&
                             ((dComIfGp_getSelectItem(i) != dItem_GRAPPLING_HOOK_e) || (strcmp(dComIfGp_getStartStageName(), "Abesso") != 0)) &&
                             (dVar2 = dComIfGp_getSelectItem(i), ((dVar2 == CAMERA) == 0)) && (dVar2 != CAMERA2) && (dVar2 != dItem_SPOILS_BAG_e) &&
                             (dVar2 != dItem_SKULL_NECKLACE_e) && (dVar2 != dItem_BOKOBABA_SEED_e) && (dVar2 != dItem_GOLDEN_FEATHER_e) &&
                             (dVar2 != BOKO_BELT) && (dVar2 != dItem_RED_JELLY_e) && (dVar2 != dItem_GREEN_JELLY_e) && (dVar2 != dItem_BLUE_JELLY_e) &&
                             (dVar2 != dItem_JOY_PENDANT_e) && (dVar2 != dItem_BAIT_BAG_e) && (dVar2 != dItem_BIRD_BAIT_5_e) && (dVar2 != dItem_HYOI_PEAR_e) &&
                             (dVar2 != dItem_EMPTY_BOTTLE_e) && (dVar2 != dItem_RED_POTION_e) && (dVar2 != dItem_GREEN_POTION_e) &&
                             (dVar2 != dItem_BLUE_POTION_e) && (dVar2 != dItem_HALF_SOUP_BOTTLE_e) && (dVar2 != dItem_SOUP_BOTTLE_e) &&
                             (dVar2 != dItem_WATER_BOTTLE_e) && (dVar2 != dItem_FAIRY_BOTTLE_e) && (dVar2 != dItem_FIREFLY_BOTTLE_e) &&
                             (dVar2 != dItem_FOREST_WATER_e) && (dVar2 != dItem_DELIVERY_BAG_e) && (dVar2 != FLOWER_1) && (dVar2 != FLOWER_2) &&
                             (dVar2 != FLOWER_3) && (dVar2 != HEROS_FLAG) && (dVar2 != TAIRYO_FLAG) && (dVar2 != SALES_FLAG) && (dVar2 != WIND_FLAG) &&
                             (dVar2 != RED_FLAG) && (dVar2 != FOSSIL_HEAD) && (dVar2 != WATER_STATUE) && (dVar2 != POSTMAN_STATUE) &&
                             (dVar2 != PRESIDENT_STATUE) && (dVar2 != dItem_FATHER_LETTER_e) && (dVar2 != dItem_NOTE_TO_MOM_e) && (dVar2 != MAGYS_LETTER) &&
                             (dVar2 != MO_LETTER) && (dVar2 != COTTAGE_PAPER) && (dVar2 != KAISEN_PRESENT1) && (dVar2 != KAISEN_PRESENT2)))
                        {
                            if (alphaNowFrame[i] > 3) {
                                alphaNowFrame[i]--;
                            } else {
                                if (alphaNowFrame[i] < 3) {
                                    alphaNowFrame[i]++;
                                } else {
                                    alphaNowFrame[i] = 3;
                                }
                            }
                        } else {
                            if (alphaNowFrame[i] < 5) {
                                alphaNowFrame[i]++;
                            } else {
                                alphaNowFrame[i] = 5;
                            }
                            switch (i) {
                            case 0:
                                i_Meter->field_0x3024 |= 4;
                                break;
                            case 1:
                                i_Meter->field_0x3024 |= 8;
                                break;
                            case 2:
                                i_Meter->field_0x3024 |= 0x20;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    dVar10 = fopMsgM_valueIncrease(5, alphaNowFrame[0], 0);
    dVar11 = fopMsgM_valueIncrease(5, alphaNowFrame[1], 0);
    dVar12 = fopMsgM_valueIncrease(5, alphaNowFrame[2], 0);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1fd8[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1f30[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2080[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2128[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2550[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x25c0[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2630[0], dVar10);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2550[1], dVar11);
    fopMsgM_setNowAlpha(&i_Meter->field_0x25c0[1], dVar11);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2630[1], dVar11);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1fd8[2], dVar12);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1f30[2], dVar12);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2080[2], dVar12);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2128[2], dVar12);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2518, dVar12);
    if ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1fd8[1], dVar10);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1f30[1], dVar10);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2080[1], dVar10);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2128[1], dVar10);
        for (s32 i = 0; i < 3; i++) {
            fopMsgM_setNowAlphaZero(&i_Meter->field_0x2320[i]);
            fopMsgM_setNowAlphaZero(&i_Meter->field_0x23c8[i]);
            fopMsgM_setNowAlphaZero(&i_Meter->field_0x2470[i]);
        }
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1fd8[1], dVar11);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1f30[1], dVar11);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2080[1], dVar11);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2128[1], dVar11);
    }
}

/* 801F69A0-801F7034       .text dMeter_xyTrans__FP15sub_meter_class */
void dMeter_xyTrans(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    static s16 moveNowFrame = 0;
    static s16 moveFlag = 0;
    static s16 moveStatus = 0;
    static f32 nowX = 0.0f;
    static f32 nowY = 0.0f;
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && dComIfGp_event_checkHind(1)) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK100_e) ||
        (((dMenu_flag() && (dMenu_getPushMenuButton() == 2 || (dMenu_getMenuStatus() == 2 && (dMenu_getPushMenuButton() == 0)))) ||
          (i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) ||
         (((((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1)) ||
            (i_Meter->mStatusFlags & dMtrStts_UNK80_e)) ||
           (((i_Meter->mStatusFlags & dMtrStts_UNK100000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK200000_e)) ||
            ((i_Meter->mStatusFlags & dMtrStts_UNK20000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80000_e))))
          ) ||
          (i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
    {
        if (moveStatus != 1) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 4);
        }
        moveStatus = 1;
    } else if ((dMenu_flag()) && (dMenu_getPushMenuButton() == 1 || (dMenu_getMenuStatus() == 1 && (dMenu_getPushMenuButton() == 0)))) {
        if (dMenu_getItemMode() == 0) {
            if (moveStatus != 2) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 4);
            }
            moveStatus = 2;
        } else {
            if (moveStatus != 1) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 4);
            }
            moveStatus = 1;
        }
    } else {
        if (i_Meter->mStatusFlags & dMtrStts_UNK20_e) {
            if ((((dMeter_Info.field_0x1 == 0) || (dMeter_Info.field_0x1 == 1)) || (dMeter_Info.field_0x1 == 2)) || (dMeter_Info.field_0x1 == 3)) {
                if (moveStatus != 3) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 4);
                }
                moveStatus = 3;
            } else if (((dMeter_Info.field_0x1 == 7) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9 || (dMeter_Info.field_0x1 == 10))) {
                if (moveStatus != 4) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 4);
                }
                moveStatus = 4;
            } else {
                if (moveStatus != 1) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 4);
                }
                moveStatus = 1;
            }
        } else {
            if (moveStatus != 0) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 4);
            }
            moveStatus = 0;
        }
    }
    if (i_Meter->field_0x3026 != 0xf) {
        if (dMeter_isBit8(&i_Meter->field_0x3026, 4) == 0) {
            if (moveNowFrame >= 5) {
                moveNowFrame = 5;
                moveFlag = 0;
                dMeter_onBit8(&i_Meter->field_0x3026, 4);
                switch (moveStatus) {
                case 1:
                    nowX = 0.0f;
                    nowY = -200.0f;
                    break;
                case 2:
                    nowX = g_meterHIO.field_0xc4;
                    nowY = g_meterHIO.field_0xcc;
                    break;
                case 3:
                    nowX = g_meterHIO.field_0x114;
                    nowY = g_meterHIO.field_0x11c;
                    break;
                case 4:
                    nowX = (f32)(g_meterHIO.field_0x114 + 0x28);
                    nowY = g_meterHIO.field_0x11c;
                    break;
                default:
                    nowX = g_meterHIO.field_0xf4;
                    nowY = g_meterHIO.field_0xfc;
                    break;
                }
            } else {
                moveNowFrame++;
            }
        }
    } else {
        if ((s32)moveNowFrame <= 0) {
            moveNowFrame = 0;
        } else {
            moveNowFrame--;
        }
    }
    f32 dVar7 = fopMsgM_valueIncrease(5, moveNowFrame, 0);
    f32 x = nowX;
    f32 dVar8 = (nowY + (dVar7 * (-200.0f - nowY)));
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_paneTrans(&i_Meter->field_0x1fd8[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x1f30[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x2080[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x2128[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x2320[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x23c8[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x2470[i], x, dVar8);
    }
    fopMsgM_paneTrans(&i_Meter->field_0x2518, x, dVar8);
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_paneTrans(&i_Meter->field_0x2550[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x25c0[i], x, dVar8);
        fopMsgM_paneTrans(&i_Meter->field_0x2630[i], x, dVar8);
    }
}

/* 801F7034-801F70E0       .text dMeter_rInit__FP15sub_meter_class */
void dMeter_rInit(sub_meter_class* i_Meter) {
    JKRArchive* pArc;
    const char* pFilename;

    i_Meter->field_0x26d8.mUserArea = 0;
    i_Meter->field_0x1cc8.mUserArea = 0;
    i_Meter->field_0x301c = 0;
    dComIfGp_setRStatus(dActStts_BLANK_e);
    if ((dComIfGp_getRStatus() == dActStts_RETURN_e) || (dComIfGp_getRStatus() == dActStts_RETURN_e)) {
        pArc = dComIfGp_getMenuArchive();
    } else {
        pArc = dComIfGp_getActionIconArchive();
    }
    pFilename = dMeter_actionTex(dActStts_BLANK_e);
    JKRArchive::readTypeResource(i_Meter->actionTex[2], 0xc00, 'TIMG', pFilename, pArc);
    DCStoreRangeNoSync(i_Meter->actionTex[2], 0xc00);
    ((J2DPicture*)i_Meter->field_0x1cc8.pane)->changeTexture(i_Meter->actionTex[2], 0);
}

/* 801F70E0-801F71F4       .text dMeter_rMove__FP15sub_meter_class */
void dMeter_rMove(sub_meter_class* i_Meter) {
    const char* pFilename;
    JKRArchive* pArc;

    if (dComIfGp_getRStatusForce() != dActStts_BLANK_e) {
        dComIfGp_setRStatus(dComIfGp_getRStatusForce());
    }
    if (i_Meter->field_0x1cc8.mUserArea != 0) {
        if (dComIfGp_getRStatus() != dActStts_BLANK_e) {
            if ((dComIfGp_getRStatus() == dActStts_RETURN_e) || (dComIfGp_getRStatus() == dActStts_RETURN_e)) {
                pArc = dComIfGp_getMenuArchive();
            } else {
                pArc = dComIfGp_getActionIconArchive();
            }
            pFilename = dMeter_actionTex(dComIfGp_getRStatus());
            JKRArchive::readTypeResource(i_Meter->actionTex[2], 0xc00, 'TIMG', pFilename, pArc);
            DCStoreRangeNoSync(i_Meter->actionTex[2], 0xc00);
            ((J2DPicture*)i_Meter->field_0x1cc8.pane)->changeTexture(i_Meter->actionTex[2], 0);
        }
        i_Meter->field_0x301c = dComIfGp_getRStatus();
        i_Meter->field_0x26d8.mUserArea = 1;
        i_Meter->field_0x1cc8.mUserArea = 0;
    }
    if (i_Meter->field_0x301c != dComIfGp_getRStatus()) {
        i_Meter->field_0x1cc8.mUserArea = 1;
    }
    dMeter_rTrans(i_Meter);
    dMeter_rAlpha(i_Meter);
    dComIfGp_setRStatusForce(dActStts_BLANK_e);
}

/* 801F71F4-801F7234       .text dMeter_rDraw__FP15sub_meter_class */
void dMeter_rDraw(sub_meter_class* i_Meter) {
    fopMsgM_setAlpha(&i_Meter->field_0x1cc8);
    fopMsgM_setAlpha(&i_Meter->field_0x26a0);
    fopMsgM_setAlpha(&i_Meter->field_0x26d8);
}

/* 801F7234-801F749C       .text dMeter_rAlpha__FP15sub_meter_class */
void dMeter_rAlpha(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    s16 sVar2;
    f32 dVar5;
    f32 dVar6;

    static s16 alphaNowFrame = 0;
    if (((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(8)))) ||
        (((((i_Meter->mStatusFlags & dMtrStts_UNK100_e) || (i_Meter->mStatusFlags & dMtrStts_UNK200_e)) || (i_Meter->mStatusFlags & dMtrStts_UNK8_e)) ||
          ((i_Meter->mStatusFlags & dMtrStts_UNK10_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e))) ||
         ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e)))) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK200000_e) ||
         (((i_Meter->mStatusFlags & dMtrStts_UNK40000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80000_e)) || (i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
    {
        if (alphaNowFrame < 5) {
            alphaNowFrame++;
        } else {
            alphaNowFrame = 5;
        }
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK2000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK8000_e)) {
        if (alphaNowFrame > 3) {
            alphaNowFrame--;
        } else if (alphaNowFrame < 3) {
            alphaNowFrame++;
        } else {
            alphaNowFrame = 3;
        }
    } else {
        if (alphaNowFrame < 5) {
            sVar2 = alphaNowFrame + 1;
        } else {
            sVar2 = 5;
        }
        alphaNowFrame = sVar2;
        i_Meter->field_0x3024 |= 0x10;
    }
    dVar5 = fopMsgM_valueIncrease(5, alphaNowFrame, 0);
    if (dComIfGp_getRStatus() == dActStts_BLANK_e) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x1cc8);
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1cc8, dVar5);
    }
    if ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) {
        dVar6 = 1.0f - dVar5;
        fopMsgM_setNowAlpha(&i_Meter->field_0x26a0, 1.0f - dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x26d8, dVar6);
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x26a0, dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x26d8, dVar5);
    }
    if ((dMeter_isBit8(&i_Meter->field_0x3026, 8) != 0) && (i_Meter->field_0x1cc8.mUserArea == 0)) {
        i_Meter->field_0x1cc8.pane->show();
    } else {
        i_Meter->field_0x1cc8.pane->hide();
    }
}

/* 801F749C-801F7B0C       .text dMeter_rTrans__FP15sub_meter_class */
void dMeter_rTrans(sub_meter_class* i_Meter) {
    /* Nonmatching - dMeter_isBit8 */
    static s16 moveNowFrame = 0;
    static s16 moveFlag = 0;
    static s16 moveStatus = 0;
    static f32 nowX = 0.0f;
    static f32 nowY = 0.0f;
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(8))) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK100_e) || (dComIfGp_getRStatus() == dActStts_HIDDEN_e)))
    {
        if (moveStatus != 1) {
            moveFlag = 1;
            dMeter_offBit8(&i_Meter->field_0x3026, 8);
        }
        moveStatus = 1;
    } else {
        if (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) {
            if (moveStatus != 2) {
                moveFlag = 1;
                dMeter_offBit8(&i_Meter->field_0x3026, 8);
            }
            moveStatus = 2;
        } else {
            if (i_Meter->mStatusFlags & dMtrStts_UNK40000_e) {
                if (moveStatus != 4) {
                    moveFlag = 1;
                    dMeter_offBit8(&i_Meter->field_0x3026, 8);
                }
                moveStatus = 4;
            } else {
                if (((dMenu_flag()) && (dComIfGp_getPictureStatus() != 2) &&
                     ((dMenu_getPushMenuButton() == 1) || ((dMenu_getMenuStatus() == 1) && (dMenu_getPushMenuButton() == 0)))) ||
                    ((dMenu_flag()) && ((dMenu_getPushMenuButton() == 2) || ((dMenu_getMenuStatus() == 2) && (dMenu_getPushMenuButton() == 0)))) ||
                    (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) ||
                    ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1)) ||
                    (i_Meter->mStatusFlags & dMtrStts_UNK80_e) ||
                    ((i_Meter->mStatusFlags & dMtrStts_UNK100000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK200000_e)) ||
                    (i_Meter->mStatusFlags & dMtrStts_UNK80000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK400000_e))
                {
                    if (moveStatus != 1) {
                        moveFlag = 1;
                        dMeter_offBit8(&i_Meter->field_0x3026, 8);
                    }
                    moveStatus = 1;
                } else {
                    if (i_Meter->mStatusFlags & dMtrStts_UNK20_e) {
                        if (((dMeter_Info.field_0x1 == 0) || (dMeter_Info.field_0x1 == 1)) || (dMeter_Info.field_0x1 == 2 || (dMeter_Info.field_0x1 == 3))) {
                            if (moveStatus != 3) {
                                moveFlag = 1;
                                dMeter_offBit8(&i_Meter->field_0x3026, 8);
                            }
                            moveStatus = 3;
                        } else if ((((dMeter_Info.field_0x1 == 7) || (dMeter_Info.field_0x1 == 8)) || (dMeter_Info.field_0x1 == 9)) ||
                                   (dMeter_Info.field_0x1 == 10))
                        {
                            if (moveStatus != 5) {
                                moveFlag = 1;
                                dMeter_offBit8(&i_Meter->field_0x3026, 8);
                            }
                            moveStatus = 5;
                        } else {
                            if (moveStatus != 1) {
                                moveFlag = 1;
                                dMeter_offBit8(&i_Meter->field_0x3026, 8);
                            }
                            moveStatus = 1;
                        }

                    } else {
                        if (moveStatus != 0) {
                            moveFlag = 1;
                            dMeter_offBit8(&i_Meter->field_0x3026, 8);
                        }
                        moveStatus = 0;
                    }
                }
            }
        }
    }
    if (i_Meter->field_0x3026 != 0xf) {
        if (dMeter_isBit8(&i_Meter->field_0x3026, 8) == 0) {
            if (moveNowFrame >= 5) {
                moveNowFrame = 5;
                moveFlag = 0;
                dMeter_onBit8(&i_Meter->field_0x3026, 8);
                switch (moveStatus) {
                case 1:
                    nowX = 0.0f;
                    nowY = -200.0f;
                    break;
                case 2:
                    nowX = g_meterHIO.field_0xb6;
                    nowY = g_meterHIO.field_0xbe;
                    break;
                case 3:
                    nowX = g_meterHIO.field_0x116;
                    nowY = g_meterHIO.field_0x11e;
                    break;
                case 4:
                    nowX = g_meterHIO.field_0xe6;
                    nowY = g_meterHIO.field_0xee;
                    break;
                case 5:
                    nowX = (f32)(g_meterHIO.field_0x116 + 0x21);
                    nowY = (f32)(g_meterHIO.field_0x11e - 5);
                    break;
                default:
                    nowX = g_meterHIO.field_0xf6;
                    nowY = g_meterHIO.field_0xfe;
                    break;
                }
            } else {
                moveNowFrame++;
            }
        }
    } else {
        if ((s32)moveNowFrame <= 0) {
            moveNowFrame = 0;
        } else {
            moveNowFrame--;
        }
    }
    f32 dVar6 = fopMsgM_valueIncrease(5, moveNowFrame, 0);
    f32 x = nowX;
    f32 dVar7 = (nowY + (dVar6 * (-200.0f - nowY)));
    fopMsgM_paneTrans(&i_Meter->field_0x1cc8, x, dVar7);
    fopMsgM_paneTrans(&i_Meter->field_0x26a0, x, dVar7);
    fopMsgM_paneTrans(&i_Meter->field_0x26d8, x, dVar7);
}

/* 801F7B0C-801F7B90       .text dMeter_enemyInit__FP15sub_meter_class */
void dMeter_enemyInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x0448[1].mUserArea = 0;
    i_Meter->field_0x0560.mUserArea = 0;
    i_Meter->field_0x03d8.mUserArea = 0;
    i_Meter->field_0x0410.mUserArea = (cM_rndF(200.0f) + 300.0f);
    i_Meter->field_0x0368.mUserArea = 0;
    i_Meter->field_0x03a0.mUserArea = ((int)(cM_rndF(18.0f) + 40.0f) << 1);
}

/* 801F7B90-801F80C4       .text dMeter_enemyMove__FP15sub_meter_class */
void dMeter_enemyMove(sub_meter_class* i_Meter) {
    dAttention_c* attention = &dComIfGp_getAttention();
    stage_stag_info_class* stage_info = dComIfGp_getStageStagInfo();
    JUT_ASSERT(7176, stage_info != NULL);
    if (attention != NULL) {
        if (((!dMenu_flag()) && (!dComIfGp_event_runCheck())) && (attention->LockonTarget(0) != NULL) &&
            ((((((attention->LockonTarget(0)->max_health > 0.0f) && (dComIfGs_isCollect(4, 1) != 0)) &&
                ((attention->LockonTruth() & 0xff) != 0 &&
                 (attention->LockonTarget(0)->group == fopAc_ENEMY_e && (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BTD)))) &&
               (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BMD)) &&
              (((fopAcM_GetName(attention->LockonTarget(0)) != PROC_BDK && (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BPW)) &&
                (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BGN)) &&
               (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BGN2 && (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BGN3)))) &&
             ((fopAcM_GetName(attention->LockonTarget(0)) != PROC_GND &&
               (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BST || ((fopAcM_GetParam(attention->LockonTarget(0)) & 0xfU) != 0))) &&
              (fopAcM_GetName(attention->LockonTarget(0)) != PROC_BWD))))
        {
            dMeter_zakoEnemyMove(i_Meter);
        } else {
            dMeter_zakoEnemyHide(i_Meter);
        }
    }
    if ((((!dMenu_flag()) && (dComIfGs_isCollect(4, 1) != 0)) && (!dComIfGp_event_runCheck())) &&
        ((!(i_Meter->mStatusFlags & dMtrStts_UNK80_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20000_e))) &&
        ((dStage_stagInfo_GetSTType(stage_info) == dStageType_BOSS_e) || (fopAcM_SearchByName(PROC_BDK) != NULL)))
    {
        if (((dComIfGs_isStageBossDemo() != 0) && (dComIfGs_isStageBossEnemy() == 0)) ||
            (strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0 ||
             ((strcmp(dComIfGp_getStartStageName(), "Xboss1") == 0 || (strcmp(dComIfGp_getStartStageName(), "Xboss2") == 0)) ||
              (strcmp(dComIfGp_getStartStageName(), "Xboss3") == 0))))
        {
            fopAc_ac_c* pfVar3;
            if (fopAcM_SearchByName(PROC_BTD) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BTD);
            } else if (fopAcM_SearchByName(PROC_BMD) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BMD);
            } else if (fopAcM_SearchByName(PROC_BDK) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BDK);
            } else if (fopAcM_SearchByName(PROC_BST) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BST);
            } else if (fopAcM_SearchByName(PROC_BWD) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BWD);
            } else if (fopAcM_SearchByName(PROC_BPW) != NULL) {
                pfVar3 = fopAcM_SearchByName(PROC_BPW);
            } else {
                pfVar3 = NULL;
            }
            if (pfVar3 != NULL) {
                dMeter_bossEnemyMove(i_Meter, pfVar3);
                return;
            }
            dMeter_bossEnemyHide(i_Meter);
            return;
        }
    }
    dMeter_bossEnemyHide(i_Meter);
}

/* 801F80C4-801F842C       .text dMeter_zakoEnemyMove__FP15sub_meter_class */
void dMeter_zakoEnemyMove(sub_meter_class* i_Meter) {
    f32 fVar1;
    f32 fVar2;
    fopAc_ac_c* pfVar4;
    f32 dVar5;
    cXyz local_38;

    pfVar4 = dComIfGp_getAttention().LockonTarget(0);
    mDoLib_project(&pfVar4->attention_info.position, &local_38);
    if (local_38.x > 320.0f) {
        i_Meter->field_0x0560.mPosTopLeft.x = (local_38.x - i_Meter->field_0x0560.mSizeOrig.x) - 50.0f;
    } else {
        i_Meter->field_0x0560.mPosTopLeft.x = local_38.x + 50.0f;
    }
    i_Meter->field_0x0560.mPosTopLeft.y = local_38.y;
    dVar5 = ((f32)(pfVar4->health / (f32)(pfVar4->max_health)));
    fVar1 = i_Meter->field_0x0528.mPosTopLeftOrig.x - i_Meter->field_0x0560.mPosTopLeftOrig.x;
    fVar2 = i_Meter->field_0x0528.mPosTopLeftOrig.y - i_Meter->field_0x0560.mPosTopLeftOrig.y;
    i_Meter->field_0x0528.mPosTopLeft.x = i_Meter->field_0x0560.mPosTopLeft.x + fVar1;
    i_Meter->field_0x0528.mPosTopLeft.y = i_Meter->field_0x0560.mPosTopLeft.y + fVar2;
    i_Meter->field_0x0528.mSize.x = i_Meter->field_0x0528.mSizeOrig.x;
    i_Meter->field_0x0528.mSize.y = i_Meter->field_0x0528.mSizeOrig.y;
    i_Meter->field_0x0528.pane->move(i_Meter->field_0x0528.mPosTopLeft.x, i_Meter->field_0x0528.mPosTopLeft.y);
    i_Meter->field_0x0528.pane->resize(i_Meter->field_0x0528.mSize.x, i_Meter->field_0x0528.mSize.y);
    fVar1 = i_Meter->field_0x0598.mPosTopLeftOrig.x - i_Meter->field_0x0560.mPosTopLeftOrig.x;
    fVar2 = i_Meter->field_0x0598.mPosTopLeftOrig.y - i_Meter->field_0x0560.mPosTopLeftOrig.y;
    i_Meter->field_0x0598.mPosTopLeft.x = i_Meter->field_0x0560.mPosTopLeft.x + fVar1;
    i_Meter->field_0x0598.mPosTopLeft.y = i_Meter->field_0x0560.mPosTopLeft.y + fVar2;
    i_Meter->field_0x0598.mSize.x = i_Meter->field_0x0598.mSizeOrig.x;
    i_Meter->field_0x0598.mSize.y = i_Meter->field_0x0598.mSizeOrig.y;
    i_Meter->field_0x0598.pane->move(i_Meter->field_0x0598.mPosTopLeft.x, i_Meter->field_0x0598.mPosTopLeft.y);
    i_Meter->field_0x0598.pane->resize(i_Meter->field_0x0598.mSize.x, i_Meter->field_0x0598.mSize.y);
    fVar1 = i_Meter->field_0x0608.mPosTopLeftOrig.x - i_Meter->field_0x0560.mPosTopLeftOrig.x;
    fVar2 = i_Meter->field_0x0608.mPosTopLeftOrig.y - i_Meter->field_0x0560.mPosTopLeftOrig.y;
    i_Meter->field_0x0608.mPosTopLeft.x = i_Meter->field_0x0560.mPosTopLeft.x + fVar1;
    i_Meter->field_0x0608.mPosTopLeft.y = i_Meter->field_0x0560.mPosTopLeft.y + fVar2;
    i_Meter->field_0x0608.mSize.x = i_Meter->field_0x0608.mSizeOrig.x;
    i_Meter->field_0x0608.mSize.y = i_Meter->field_0x0608.mSizeOrig.y;
    i_Meter->field_0x0608.pane->move(i_Meter->field_0x0608.mPosTopLeft.x, i_Meter->field_0x0608.mPosTopLeft.y);
    i_Meter->field_0x0608.pane->resize(i_Meter->field_0x0608.mSize.x, i_Meter->field_0x0608.mSize.y);
    i_Meter->field_0x05d0.mPosTopLeft.x = i_Meter->field_0x05d0.mPosTopLeftOrig.x;
    i_Meter->field_0x05d0.mPosTopLeft.y = i_Meter->field_0x05d0.mPosTopLeftOrig.y;
    i_Meter->field_0x05d0.mSize.x = i_Meter->field_0x05d0.mSizeOrig.x;
    i_Meter->field_0x05d0.mSize.y = i_Meter->field_0x05d0.mSizeOrig.y;
    i_Meter->field_0x05d0.pane->move(i_Meter->field_0x05d0.mPosTopLeft.x, i_Meter->field_0x05d0.mPosTopLeft.y);
    i_Meter->field_0x05d0.pane->resize(i_Meter->field_0x05d0.mSize.x, i_Meter->field_0x05d0.mSize.y);
    i_Meter->field_0x0560.mSize.x = i_Meter->field_0x0560.mSizeOrig.x * dVar5;
    i_Meter->field_0x0560.mSize.y = i_Meter->field_0x0560.mSizeOrig.y;
    i_Meter->field_0x0560.pane->move(i_Meter->field_0x0560.mPosTopLeft.x, i_Meter->field_0x0560.mPosTopLeft.y);
    i_Meter->field_0x0560.pane->resize(i_Meter->field_0x0560.mSize.x, i_Meter->field_0x0560.mSize.y);
    if (i_Meter->field_0x0560.mUserArea < 10) {
        i_Meter->field_0x0560.mUserArea++;
        dVar5 = fopMsgM_valueIncrease(10, i_Meter->field_0x0560.mUserArea, 0);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0528, dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0560, dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0598, dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0608, dVar5);
    } else {
        fopMsgM_setInitAlpha(&i_Meter->field_0x0528);
        fopMsgM_setInitAlpha(&i_Meter->field_0x0560);
        fopMsgM_setInitAlpha(&i_Meter->field_0x0598);
        fopMsgM_setInitAlpha(&i_Meter->field_0x0608);
    }
}

/* 801F842C-801F86E4       .text dMeter_bossEnemyMove__FP15sub_meter_classP10fopAc_ac_c */
void dMeter_bossEnemyMove(sub_meter_class* i_Meter, fopAc_ac_c* param_2) {
    f32 fVar2;
    f32 dVar5;

    if (param_2->max_health != 0) {
        fVar2 = (f32)(param_2->health) / (f32)(param_2->max_health);
    } else {
        fVar2 = g_meterHIO.field_0xc;
    }
    if (i_Meter->field_0x0448[0].mUserArea < 0x1e) {
        i_Meter->field_0x0448[0].mUserArea++;
        if (i_Meter->field_0x0448[0].mUserArea <= 0xa) {
            fVar2 = fopMsgM_valueIncrease(10, 10 - i_Meter->field_0x0448[0].mUserArea, 0) * 80.0f;
            fopMsgM_paneScaleX(&i_Meter->field_0x0448[2], 0.0f);
            fopMsgM_paneScaleX(&i_Meter->field_0x0448[3], 0.0f);
            fopMsgM_paneTrans(&i_Meter->field_0x0368, 0.0f, fVar2);
            fopMsgM_paneTrans(&i_Meter->field_0x03a0, 0.0f, fVar2);
            fopMsgM_paneTrans(&i_Meter->field_0x03d8, 0.0f, fVar2);
            fopMsgM_paneTrans(&i_Meter->field_0x0410, 0.0f, fVar2);
            for (s32 i = 0; i < 4; i++) {
                fopMsgM_paneTrans(&i_Meter->field_0x0448[i], 0.0f, fVar2);
            }
        } else {
            dVar5 = fopMsgM_valueIncrease(0x14, i_Meter->field_0x0448[0].mUserArea + -10, 2);
            fopMsgM_paneScaleX(&i_Meter->field_0x0448[2], fVar2 * dVar5);
            fopMsgM_paneScaleX(&i_Meter->field_0x0448[3], fVar2 * dVar5);
        }
    } else {
        fopMsgM_paneScaleX(&i_Meter->field_0x0448[2], fVar2);
        fopMsgM_paneScaleX(&i_Meter->field_0x0448[3], fVar2);
    }
    i_Meter->field_0x0448[2].pane->move(
        ((i_Meter->field_0x0448[2].mPosTopLeftOrig.x + i_Meter->field_0x0448[2].mSizeOrig.x) - i_Meter->field_0x0448[2].mSize.x),
        i_Meter->field_0x0448[2].mPosTopLeftOrig.y
    );
    i_Meter->field_0x0448[3].pane->move(
        ((i_Meter->field_0x0448[3].mPosTopLeftOrig.x + i_Meter->field_0x0448[3].mSizeOrig.x) - i_Meter->field_0x0448[3].mSize.x),
        i_Meter->field_0x0448[3].mPosTopLeftOrig.y
    );
    if (i_Meter->field_0x0448[1].mUserArea < 10) {
        i_Meter->field_0x0448[1].mUserArea++;
        fVar2 = fopMsgM_valueIncrease(10, i_Meter->field_0x0448[1].mUserArea, 0);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0368, fVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x03a0, fVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x03d8, fVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0410, fVar2);
        for (s32 i = 0; i < 4; i++) {
            fopMsgM_setNowAlpha(&i_Meter->field_0x0448[i], fVar2);
        }
    } else {
        dMeter_bossAnime(i_Meter);
        fopMsgM_setInitAlpha(&i_Meter->field_0x03d8);
        fopMsgM_setInitAlpha(&i_Meter->field_0x0410);
        for (s32 i = 0; i < 4; i++) {
            fopMsgM_setInitAlpha(&i_Meter->field_0x0448[i]);
        }
    }
}

/* 801F86E4-801F878C       .text dMeter_zakoEnemyHide__FP15sub_meter_class */
void dMeter_zakoEnemyHide(sub_meter_class* i_Meter) {
    if (i_Meter->field_0x0560.mUserArea > 0) {
        i_Meter->field_0x0560.mUserArea--;
        f32 dVar2 = fopMsgM_valueIncrease(10, i_Meter->field_0x0560.mUserArea, 0);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0528, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0560, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0598, dVar2);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0608, dVar2);
    } else {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0528);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0560);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0598);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0608);
    }
}

/* 801F878C-801F8888       .text dMeter_bossEnemyHide__FP15sub_meter_class */
void dMeter_bossEnemyHide(sub_meter_class* i_Meter) {
    if (i_Meter->field_0x0448[1].mUserArea > 0) {
        i_Meter->field_0x0448[1].mUserArea--;
        f32 dVar4 = fopMsgM_valueIncrease(10, i_Meter->field_0x0448[1].mUserArea, 0);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0368, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x03a0, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x03d8, dVar4);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0410, dVar4);
        for (s32 i = 0; i < 4; i++) {
            fopMsgM_setNowAlpha(&i_Meter->field_0x0448[i], dVar4);
        }
    } else {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0368);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x03a0);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x03d8);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0410);
        for (s32 i = 0; i < 4; i++) {
            fopMsgM_setNowAlphaZero(&i_Meter->field_0x0448[i]);
        }
    }
}

/* 801F8888-801F8BA8       .text dMeter_bossAnime__FP15sub_meter_class */
void dMeter_bossAnime(sub_meter_class* i_Meter) {
    f32 dVar9 = 0.0f;
    const s16 unk_9010[] = {0x04, 0x0A, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02};
    s16 unk_array[15];
    unk_array[0] = unk_9010[0];
    for (s32 i = 1; i < 15; i++) {
        unk_array[i] = unk_array[i - 1] + unk_9010[i];
    };
    i_Meter->field_0x03d8.mUserArea++;
    if (i_Meter->field_0x03d8.mUserArea >= i_Meter->field_0x0410.mUserArea) {
        i_Meter->field_0x03d8.mUserArea = 0;
        i_Meter->field_0x0410.mUserArea = cM_rndF(200.0f) + 300.0f;
    } else {
        if (i_Meter->field_0x03d8.mUserArea < unk_array[10]) {
            if (i_Meter->field_0x03d8.mUserArea < unk_array[0]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[0], i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[1]) {
                dVar9 = 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[2]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[2], unk_array[2] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[3]) {
                dVar9 = 0.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[4]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[4], unk_array[4] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[5]) {
                dVar9 = 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[6]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[6], unk_array[6] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[7]) {
                dVar9 = 0.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[8]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[8], unk_array[8] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[9]) {
                dVar9 = 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[10]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[10], unk_array[10] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[11]) {
                dVar9 = 0.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[12]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[12], unk_array[12] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[13]) {
                dVar9 = 2.0f;
            } else if (i_Meter->field_0x03d8.mUserArea < unk_array[14]) {
                dVar9 = fopMsgM_valueIncrease(unk_9010[14], unk_array[14] - i_Meter->field_0x03d8.mUserArea, 0) * 2.0f;
            }
        }
    }
    fopMsgM_paneTrans(&i_Meter->field_0x03d8, 0.0f, -dVar9);
    fopMsgM_paneTrans(&i_Meter->field_0x0368, 0.0f, -dVar9);
    fopMsgM_paneTrans(&i_Meter->field_0x03a0, 0.0f, -dVar9);
    fopMsgM_paneTrans(&i_Meter->field_0x0410, 0.0f, dVar9);
    dMeter_bossEyeAnime(i_Meter);
}

/* 801F8BA8-801F8CD0       .text dMeter_bossEyeAnime__FP15sub_meter_class */
void dMeter_bossEyeAnime(sub_meter_class* i_Meter) {
    int iVar2;
    f32 dVar4;

    static bool bossEyeFlag = false;
    iVar2 = (s16)(i_Meter->field_0x03a0.mUserArea / 2);
    i_Meter->field_0x0368.mUserArea++;
    if (bossEyeFlag != false) {
        if (i_Meter->field_0x0368.mUserArea < iVar2) {
            dVar4 = fopMsgM_valueIncrease(iVar2, i_Meter->field_0x0368.mUserArea, 2);
        } else {
            dVar4 = fopMsgM_valueIncrease(iVar2, i_Meter->field_0x03a0.mUserArea - i_Meter->field_0x0368.mUserArea, 2);
        }
    } else {
        dVar4 = 0.0f;
    }
    if (i_Meter->field_0x0368.mUserArea == i_Meter->field_0x03a0.mUserArea) {
        i_Meter->field_0x0368.mUserArea = 0;
        i_Meter->field_0x03a0.mUserArea = ((int)(cM_rndF(18.0f) + 40.0f) * 2);
        if (bossEyeFlag != false) {
            bossEyeFlag = false;
        } else {
            bossEyeFlag = true;
        }
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x0368, dVar4);
    fopMsgM_setNowAlpha(&i_Meter->field_0x03a0, dVar4);
}

/* 801F8CD0-801F8F28       .text dMeter_magicInit__FP15sub_meter_class */
void dMeter_magicInit(sub_meter_class* i_Meter) {
    if ((g_dComIfG_gameInfo.play.field_0x4965 >> 1 & 1) != 0) {
        i_Meter->field_0x3018 = dComIfGs_getMaxMagic();
        i_Meter->field_0x3016 = (i_Meter->field_0x0f38[0].mSizeOrig.x * dComIfGs_getMagic() * 25.0f);
    } else {
        i_Meter->field_0x3018 = 0;
        i_Meter->field_0x3016 = 0;
        g_dComIfG_gameInfo.play.field_0x4965 |= 2;
    }
    i_Meter->field_0x3019 = 0;
    i_Meter->field_0x0f38[0].mUserArea = 0;
    i_Meter->field_0x0f38[1].mUserArea = 0;
    i_Meter->field_0x0f38[2].mUserArea = 0;
    i_Meter->field_0x0f38[3].mUserArea = 0;
    i_Meter->field_0x0f38[4].mUserArea = 0;
    i_Meter->field_0x0f38[5].mUserArea = 1;
    i_Meter->field_0x10f8.mUserArea = 0;
    i_Meter->field_0x11a0.mUserArea = 0;
    i_Meter->field_0x1130.mUserArea = 0;
    i_Meter->field_0x11d8.mUserArea = 0;
    i_Meter->field_0x2fc0 = 0.0f;
    f32 tmp = 0.03125f;
    dMeter_magicLength(i_Meter, i_Meter->field_0x3018 * tmp);
    dMeter_magicChange(i_Meter, i_Meter->field_0x3016 / 100.0f);
    i_Meter->field_0x2f08.set(((J2DPicture*)i_Meter->field_0x11a0.pane)->getWhite());
    i_Meter->field_0x2f0c.set(((J2DPicture*)i_Meter->field_0x11a0.pane)->getBlack());
    i_Meter->field_0x2f10.set(((J2DPicture*)i_Meter->field_0x0f38[0].pane)->getWhite());
    i_Meter->field_0x2f14.set(((J2DPicture*)i_Meter->field_0x0f38[0].pane)->getBlack());
    i_Meter->field_0x2f18.set(((J2DPicture*)i_Meter->field_0x0f38[1].pane)->getWhite());
    i_Meter->field_0x2f1c.set(((J2DPicture*)i_Meter->field_0x0f38[1].pane)->getBlack());
    dMeter_magicTransNowInit(i_Meter);
    fopMsgM_setInitAlpha(&i_Meter->field_0x10f8);
    fopMsgM_setInitAlpha(&i_Meter->field_0x11a0);
    fopMsgM_setInitAlpha(&i_Meter->field_0x11d8);
}

/* 801F8F28-801F9048       .text dMeter_magicMove__FP15sub_meter_class */
void dMeter_magicMove(sub_meter_class* i_Meter) {
    if (i_Meter->mStatusFlags & dMtrStts_UNK40000_e) {
        if (dComIfGp_getCb1Player() == fopAcM_SearchByName(PROC_NPC_CB1)) {
            int iVar4 = daNpc_Cb1_c::m_flyingTimer;
            u8 uVar2 = daNpc_Cb1_c::m_flying;
            s16 uVar3 = daNpc_Cb1_c::getMaxFlyingTimer();
            dMeter_flyGaugeMove(i_Meter, uVar2, uVar3, iVar4);
        } else if (dComIfGp_getCb1Player() == fopAcM_SearchByName(PROC_NPC_MD)) {
            int iVar4 = daNpc_Md_c::m_flyingTimer;
            u8 uVar2 = daNpc_Md_c::m_flying;
            s16 uVar3 = daNpc_Md_c::getMaxFlyingTimer();
            dMeter_flyGaugeMove(i_Meter, uVar2, uVar3, iVar4);
        } else {
            dMeter_flyGaugeMove(i_Meter, 0, 1, 1);
        }
        if (i_Meter->field_0x0f38[2].mUserArea == 1) {
            i_Meter->field_0x0f38[2].mUserArea = 0;
        }
        i_Meter->field_0x0f38[5].mUserArea = 1;
    } else {
        dMeter_magicGaugeMove(i_Meter);
        if (i_Meter->field_0x11d8.mUserArea != 0) {
            i_Meter->field_0x11d8.mUserArea = 0;
        }
    }
}

/* 801F9048-801F961C       .text dMeter_magicGaugeMove__FP15sub_meter_class */
void dMeter_magicGaugeMove(sub_meter_class* i_Meter) {
    uint uVar2;
    s16 sVar4;
    u16 uVar5;
    uint uVar7;
    u16 uVar8;

    static bool soundOnFlag = false;
    if (i_Meter->field_0x0f38[0].mUserArea == 1) {
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setWhite(i_Meter->field_0x2f08);
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setBlack(i_Meter->field_0x2f0c);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setWhite(i_Meter->field_0x2f08);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setBlack(i_Meter->field_0x2f0c);
        for (s32 i = 0; i < 4; i++) {
            ((J2DPicture*)i_Meter->field_0x0f38[0 + i * 2].pane)->setWhite(i_Meter->field_0x2f10);
            ((J2DPicture*)i_Meter->field_0x0f38[0 + i * 2].pane)->setBlack(i_Meter->field_0x2f14);
            ((J2DPicture*)i_Meter->field_0x0f38[1 + i * 2].pane)->setWhite(i_Meter->field_0x2f18);
            ((J2DPicture*)i_Meter->field_0x0f38[1 + i * 2].pane)->setBlack(i_Meter->field_0x2f1c);
        }
        i_Meter->field_0x0f38[0].mUserArea = 0;
        dMeter_magicTransScale(i_Meter, 0.0f, 0.0f, 1.0f);
        dMeter_magicInitTrans(i_Meter);
        dMeter_magicChange(i_Meter, i_Meter->field_0x3016 / 100.0f);
    }
    if (dComIfGp_getItemMaxMagicCount() != 0) {
        sVar4 = dComIfGs_getMaxMagic() + dComIfGp_getItemMaxMagicCount();
        if (sVar4 > 0x20) {
            sVar4 = 0x20;
        }
        dComIfGs_setMaxMagic(sVar4);
        g_dComIfG_gameInfo.play.mItemMaxMagicCount = 0;
    }
    if ((i_Meter->field_0x3018 != dComIfGs_getMaxMagic()) || (i_Meter->field_0x0f38[2].mUserArea == 0)) {
        if (i_Meter->field_0x3018 < dComIfGs_getMaxMagic()) {
            i_Meter->field_0x3018++;
        } else if (i_Meter->field_0x3018 > dComIfGs_getMaxMagic()) {
            i_Meter->field_0x3018--;
        }
        f32 tmp = 0.03125f;
        dMeter_magicLength(i_Meter, i_Meter->field_0x3018 * tmp);
        if (i_Meter->field_0x3018 == dComIfGs_getMaxMagic()) {
            if (dComIfGs_getMaxMagic() <= 0x10) {
                dMeter_magicLength(i_Meter, 0.5f);
            } else {
                dMeter_magicLength(i_Meter, 1.0f);
            }
            i_Meter->field_0x0f38[2].mUserArea = 1;
        }
    }
    if (dComIfGs_getMaxMagic() != 0) {
        if (dComIfGp_getItemMagicCount() != 0) {
            sVar4 = dComIfGs_getMagic() + dComIfGp_getItemMagicCount();
            if (sVar4 < 0) {
                sVar4 = 0;
            }
            dComIfGs_setMagic(sVar4);
            g_dComIfG_gameInfo.play.mItemMagicCount = 0;
        }
    }
    if (dComIfGs_getMagic() > dComIfGs_getMaxMagic()) {
        dComIfGs_setMagic(dComIfGs_getMaxMagic());
    }
    if (!(fopOvlpM_IsDoingReq()) &&
        (!(i_Meter->mStatusFlags & dMtrStts_UNK40_e) ||
         (!(dComIfGp_event_checkHind(0x20)) || (!(dComIfGp_evmng_checkStartDemo()) || (dComIfGp_checkPlayerStatus1(0, daPyStts1_UNK2000_e))))))
    {
        uVar8 = (i_Meter->field_0x0f38[0].mSizeOrig.x * (f32)(dComIfGs_getMagic()) * 25.0f);
        uVar5 = i_Meter->field_0x3016;
        uVar7 = uVar5;
        uVar2 = uVar8 & 0xffff;
        if (uVar7 < uVar2) {
            if ((int)(uVar2 - uVar7) < 0x271) {
                i_Meter->field_0x3016 = uVar8;
            } else {
                i_Meter->field_0x3016 = uVar5 + 0x271;
            }
            if ((i_Meter->field_0x3016 % 1250) == 0) {
                mDoAud_seStart(JA_SE_MP_GAUGE_INC, NULL, i_Meter->field_0x3016 / 1250);
            }
            dMeter_magicChange(i_Meter, i_Meter->field_0x3016 / 100.0f);
            i_Meter->field_0x0f38[5].mUserArea = 1;
        } else if (uVar7 > uVar2) {
            if ((int)(uVar7 - uVar2) < 0x271) {
                i_Meter->field_0x3016 = 0;
            } else {
                i_Meter->field_0x3016 = uVar5 - 0x271;
            }
            if ((i_Meter->field_0x3016 % 1250) == 0) {
                mDoAud_seStart(JA_SE_MP_GAUGE_DEC);
            }
            if (i_Meter->field_0x3016 == 0) {
                mDoAud_seStart(JA_SE_MP_GAUGE_DEC_FIN);
            }
            dMeter_magicChange(i_Meter, i_Meter->field_0x3016 / 100.0f);
            i_Meter->field_0x0f38[5].mUserArea = 1;
        } else if (i_Meter->field_0x0f38[5].mUserArea != 0) {
            dMeter_magicChange(i_Meter, uVar7 / 100.0f);
            i_Meter->field_0x0f38[5].mUserArea = 0;
        }
    } else {
        i_Meter->field_0x0f38[5].mUserArea = 1;
    }
    dMeter_magicColor(i_Meter);
    dMeter_magicAlpha(i_Meter);
}

/* 801F961C-801F9A24       .text dMeter_flyGaugeMove__FP15sub_meter_classUcss */
void dMeter_flyGaugeMove(sub_meter_class* i_Meter, u8 param_2, s16 param_3, s16 param_4) {
    f32 dVar8;
    f32 dVar9;
    f32 dVar10;
    cXyz local_50;
    JUtility::TColor color1(0x64, 0x64, 0xFF, 0xFF);
    JUtility::TColor color2(0x64, 0x64, 0xFF, 0x00);
    JUtility::TColor color3(0x96, 0x96, 0xE6, 0xFF);
    JUtility::TColor color4(0x96, 0x96, 0xE6, 0x00);
    JUtility::TColor color5(0xB4, 0xB4, 0xFF, 0xFF);
    JUtility::TColor color6(0xB4, 0xB4, 0xFF, 0x00);

    if (param_2 != 0) {
        dMeter_magicInitTrans(i_Meter);
        dMeter_magicChange(i_Meter, (((f32)(param_4)) / (f32)(param_3) * 25.0f * 8.0f));
        if (i_Meter->field_0x0f38[0].mUserArea == 0) {
            ((J2DPicture*)i_Meter->field_0x11a0.pane)->setWhite(color1);
            ((J2DPicture*)i_Meter->field_0x11a0.pane)->setBlack(color2);
            ((J2DPicture*)i_Meter->field_0x1130.pane)->setWhite(color1);
            ((J2DPicture*)i_Meter->field_0x1130.pane)->setBlack(color2);
            for (s32 i = 0; i < 4; i++) {
                ((J2DPicture*)i_Meter->field_0x0f38[0 + i * 2].pane)->setWhite(color3);
                ((J2DPicture*)i_Meter->field_0x0f38[0 + i * 2].pane)->setBlack(color4);
                ((J2DPicture*)i_Meter->field_0x0f38[1 + i * 2].pane)->setWhite(color5);
                ((J2DPicture*)i_Meter->field_0x0f38[1 + i * 2].pane)->setBlack(color6);
            }
            i_Meter->field_0x0f38[0].mUserArea = 1;
            i_Meter->field_0x0f38[1].mUserArea = 0x14;
            i_Meter->field_0x1130.mUserArea = 0;
        }
        if (i_Meter->field_0x11a0.mUserArea < 5) {
            i_Meter->field_0x11a0.mUserArea++;
            dVar8 = fopMsgM_valueIncrease(5, (int)i_Meter->field_0x11a0.mUserArea, 0);
        } else {
            dVar8 = 1.0f;
        }
        if (i_Meter->field_0x1130.mUserArea < 0x32) {
            i_Meter->field_0x1130.mUserArea++;
            mDoLib_project(&dComIfGp_getCb1Player()->eyePos, &local_50);
            if (i_Meter->field_0x1130.mUserArea > 0x1e) {
                dVar9 = fopMsgM_valueIncrease(0x14, 0x32 - i_Meter->field_0x1130.mUserArea, 0);
                dVar10 = fopMsgM_valueIncrease(0x14, i_Meter->field_0x1130.mUserArea + -0x1e, 0);
                dMeter_magicTransScale(
                    i_Meter,
                    dVar9 * (local_50.x - i_Meter->field_0x11a0.mPosCenter.x),
                    dVar9 * (local_50.y - i_Meter->field_0x11a0.mPosCenter.y),
                    (dVar10 * 0.5f) + 0.5f
                );
            } else {
                dMeter_magicTransScale(i_Meter, local_50.x - i_Meter->field_0x11a0.mPosCenter.x, local_50.y - i_Meter->field_0x11a0.mPosCenter.y, 0.5f);
            }
        }
    } else {
        if (i_Meter->field_0x11a0.mUserArea > 0) {
            i_Meter->field_0x11a0.mUserArea--;
            dVar8 = fopMsgM_valueIncrease(5, i_Meter->field_0x11a0.mUserArea, 0);
        } else {
            dVar8 = 0.0f;
            i_Meter->field_0x11a0.mUserArea = 0;
            dMeter_magicTransNowInit(i_Meter);
        }
        if (i_Meter->field_0x1130.mUserArea != 0) {
            i_Meter->field_0x1130.mUserArea = 0;
        }
    }
    i_Meter->field_0x2fc0 = dVar8;
}

/* 801F9A24-801F9B3C       .text dMeter_magicChange__FP15sub_meter_classf */
void dMeter_magicChange(sub_meter_class* i_Meter, f32 param_2) {
    g_dComIfG_gameInfo.play.field_0x48da = (param_2 / i_Meter->field_0x0f38[0].mSizeOrig.x) * 4.0f;
    dMeter_magicTransNowInit(i_Meter);
    for (s32 i = 0; i < 8; i++) {
        if (param_2 >= i_Meter->field_0x0f38[i].mSizeOrig.x) {
            fopMsgM_paneScaleXY(&i_Meter->field_0x0f38[i], 1.0f);
            i_Meter->field_0x0f38[i].pane->show();
            param_2 = param_2 - i_Meter->field_0x0f38[i].mSizeOrig.x;
        } else {
            if (param_2 <= 0.0f) {
                fopMsgM_paneScaleXY(&i_Meter->field_0x0f38[i], 1.0f);
                i_Meter->field_0x0f38[i].pane->hide();
            } else {
                i_Meter->field_0x0f38[i].pane->resize(param_2, i_Meter->field_0x0f38[i].mSizeOrig.y);
                i_Meter->field_0x0f38[i].pane->show();
                param_2 = 0.0f;
            }
        }
    }
}

/* 801F9B3C-801F9C14       .text dMeter_magicTransNowInit__FP15sub_meter_class */
void dMeter_magicTransNowInit(sub_meter_class* i_Meter) {
    f32 fVar1;

    if (dComIfGs_getMaxLife() <= 0x2B) {
        fVar1 = -22.0f;
    } else {
        fVar1 = 0.0f;
    }
    f32 y = fVar1;
    f32 fVar2 = i_Meter->field_0x10f8.mPosCenter.x - i_Meter->field_0x10f8.mPosCenterOrig.x;
    fopMsgM_paneTrans(&i_Meter->field_0x10f8, fVar2, y);
    fVar2 = i_Meter->field_0x11a0.mPosCenter.x - i_Meter->field_0x11a0.mPosCenterOrig.x;
    fopMsgM_paneTrans(&i_Meter->field_0x11a0, fVar2, y);
    fVar2 = i_Meter->field_0x11d8.mPosCenter.x - i_Meter->field_0x11d8.mPosCenterOrig.x;
    fopMsgM_paneTrans(&i_Meter->field_0x11d8, fVar2, y);
    for (s32 i = 0; i < 8; i++) {
        fVar2 = i_Meter->field_0x0f38[i].mPosCenter.x - i_Meter->field_0x0f38[i].mPosCenterOrig.x;
        fopMsgM_paneTrans(&i_Meter->field_0x0f38[i], fVar2, y);
    }
}

/* 801F9C14-801F9CCC       .text dMeter_magicInitTrans__FP15sub_meter_class */
void dMeter_magicInitTrans(sub_meter_class* i_Meter) {
    f32 fVar1;

    if (dComIfGs_getMaxLife() <= 0x2B) {
        fVar1 = -22.0f;
    } else {
        fVar1 = 0.0f;
    }
    f32 y = fVar1;
    fopMsgM_paneTrans(&i_Meter->field_0x10f8, 0.0f, y);
    fopMsgM_paneTrans(&i_Meter->field_0x11a0, 0.0f, y);
    fopMsgM_paneTrans(&i_Meter->field_0x11d8, 0.0f, y);
    for (s32 i = 0; i < 8; i++) {
        fopMsgM_paneTrans(&i_Meter->field_0x0f38[i], 0.0f, y);
    }
}

/* 801F9CCC-801F9F18       .text dMeter_magicTransScale__FP15sub_meter_classfff */
void dMeter_magicTransScale(sub_meter_class* i_Meter, f32 param_2, f32 param_3, f32 param_4) {
    /* Nonmatching */
    f32 fVar1;
    f32 dVar5;

    if (dComIfGs_getMaxLife() <= 0x2b) {
        param_3 += -22.0f;
    }
    fopMsgM_paneScaleXY(&i_Meter->field_0x11a0, param_4);
    fopMsgM_paneTrans(&i_Meter->field_0x11a0, param_2, param_3);
    i_Meter->field_0x1130.mPosCenter.x = (i_Meter->field_0x1130.mPosCenterOrig.x * param_4);
    i_Meter->field_0x1130.mPosCenter.y = (i_Meter->field_0x1130.mPosCenterOrig.y * param_4);
    fopMsgM_paneScaleXY(&i_Meter->field_0x1130, param_4);
    fVar1 = i_Meter->field_0x11a0.mPosCenterOrig.x;
    i_Meter->field_0x10f8.mPosCenter.x = (param_2 + (fVar1 + (param_4 * (i_Meter->field_0x10f8.mPosCenterOrig.x - fVar1))));
    fVar1 = i_Meter->field_0x11a0.mPosCenterOrig.y;
    i_Meter->field_0x10f8.mPosCenter.y = (param_3 + (fVar1 + (param_4 * (i_Meter->field_0x10f8.mPosCenterOrig.y - fVar1))));
    fopMsgM_paneScaleXY(&i_Meter->field_0x10f8, param_4);
    fVar1 = i_Meter->field_0x11a0.mPosCenterOrig.x;
    i_Meter->field_0x11d8.mPosCenter.x = (param_2 + (fVar1 + (param_4 * (i_Meter->field_0x11d8.mPosCenterOrig.x - fVar1))));
    fVar1 = i_Meter->field_0x11a0.mPosCenterOrig.y;
    i_Meter->field_0x11d8.mPosCenter.y = (param_3 + (fVar1 + (param_4 * (i_Meter->field_0x11d8.mPosCenterOrig.y - fVar1))));
    fopMsgM_paneScaleXY(&i_Meter->field_0x11d8, param_4);
    i_Meter->field_0x1168.mPosCenter.x = (i_Meter->field_0x1168.mPosCenterOrig.x * param_4);
    i_Meter->field_0x1168.mPosCenter.y = (i_Meter->field_0x1168.mPosCenterOrig.y * param_4);
    fopMsgM_paneScaleXY(&i_Meter->field_0x1168, param_4);
    for (s32 i = 0; i < 8; i++) {
        dVar5 = 0.5f;
        i_Meter->field_0x0f38[i].mPosCenter.x =
            (param_2 +
             (i_Meter->field_0x11a0.mPosCenterOrig.x + (param_4 * (i_Meter->field_0x0f38[i].mPosCenterOrig.x - i_Meter->field_0x11a0.mPosCenterOrig.x))));
        i_Meter->field_0x0f38[i].mPosCenter.y =
            (param_3 +
             (i_Meter->field_0x11a0.mPosCenterOrig.y + (param_4 * (i_Meter->field_0x0f38[i].mPosCenterOrig.y - i_Meter->field_0x11a0.mPosCenterOrig.y))));
        i_Meter->field_0x0f38[i].mPosCenter.x -= ((i_Meter->field_0x0f38[i].mSizeOrig.x * param_4) * dVar5);
        i_Meter->field_0x0f38[i].mSize.x = (param_4 * (i_Meter->field_0x0f38[i].pane->mBounds.f.x - i_Meter->field_0x0f38[i].pane->mBounds.i.x));
        i_Meter->field_0x0f38[i].mSize.y = (param_4 * (i_Meter->field_0x0f38[i].pane->mBounds.f.y - i_Meter->field_0x0f38[i].pane->mBounds.i.y));
        i_Meter->field_0x0f38[i].mPosCenter.x += (i_Meter->field_0x0f38[i].mSize.x * dVar5);
        fopMsgM_cposMove(&i_Meter->field_0x0f38[i]);
        i_Meter->field_0x0f38[i].mSize.x = i_Meter->field_0x0f38[i].mSizeOrig.x;
        i_Meter->field_0x0f38[i].mSize.y = i_Meter->field_0x0f38[i].mSizeOrig.y;
    }
}

/* 801F9F18-801FA378       .text dMeter_magicColor__FP15sub_meter_class */
void dMeter_magicColor(sub_meter_class* i_Meter) {
    f32 dVar12;

    if ((!(i_Meter->mStatusFlags & dMtrStts_UNK8_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) &&
        (!(i_Meter->mStatusFlags & dMtrStts_UNK100_e)) &&
        ((daPy_getPlayerActorClass()->checkEquipDragonShield()) || (g_dComIfG_gameInfo.play.field_0x4965 & 1) ||
         (daPy_getPlayerLinkActorClass()->checkCutRollChange() || (dComIfGp_checkPlayerStatus1(0, daPyStts1_DEKU_LEAF_FLY_e))) ||
         ((dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e)) && (daArrow_c::getKeepType() != 0) && (daPy_getPlayerActorClass()->getItemID() != -1))))
    {
        JUtility::TColor color1;
        JUtility::TColor color2;
        if (i_Meter->field_0x0f38[4].mUserArea == 0) {
            i_Meter->field_0x0f38[4].mUserArea = 1;
        }
        if (i_Meter->field_0x0f38[3].mUserArea < 0x1d) {
            i_Meter->field_0x0f38[3].mUserArea++;
        } else {
            i_Meter->field_0x0f38[3].mUserArea = 0;
        }
        if (i_Meter->field_0x0f38[3].mUserArea < 0xf) {
            dVar12 = fopMsgM_valueIncrease(0xf, i_Meter->field_0x0f38[3].mUserArea, 0);
        } else {
            dVar12 = fopMsgM_valueIncrease(0xf, 0x1e - i_Meter->field_0x0f38[3].mUserArea, 0);
        }
        color1.r = i_Meter->field_0x2f08.r - ((i_Meter->field_0x2f08.r - 255.0f) * dVar12);
        color1.g = i_Meter->field_0x2f08.g - ((i_Meter->field_0x2f08.g - 255.0f) * dVar12);
        color1.b = i_Meter->field_0x2f08.b - ((i_Meter->field_0x2f08.b - 255.0f) * dVar12);
        color1.a = 0xFF;
        color2.r = i_Meter->field_0x2f0c.r - ((i_Meter->field_0x2f0c.r - 255.0f) * dVar12);
        color2.g = i_Meter->field_0x2f0c.g - ((i_Meter->field_0x2f0c.g - 255.0f) * dVar12);
        color2.b = i_Meter->field_0x2f0c.b - ((i_Meter->field_0x2f0c.b - 255.0f) * dVar12);
        color2.a = 0x00;
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setWhite(color1);
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setBlack(color2);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setWhite(color1);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setBlack(color2);
        g_dComIfG_gameInfo.play.field_0x4965 = g_dComIfG_gameInfo.play.field_0x4965 & 0xfe;
        return;
    }
    if (i_Meter->field_0x0f38[4].mUserArea == 1) {
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setWhite(i_Meter->field_0x2f08);
        ((J2DPicture*)i_Meter->field_0x11a0.pane)->setBlack(i_Meter->field_0x2f0c);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setWhite(i_Meter->field_0x2f08);
        ((J2DPicture*)i_Meter->field_0x1130.pane)->setBlack(i_Meter->field_0x2f0c);
        i_Meter->field_0x0f38[4].mUserArea = 0;
    }
}

/* 801FA378-801FA53C       .text dMeter_magicAlpha__FP15sub_meter_class */
void dMeter_magicAlpha(sub_meter_class* i_Meter) {
    if ((dComIfGs_getMaxMagic() == 0) || (i_Meter->mStatusFlags & dMtrStts_UNK4000_e) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && ((dComIfGp_event_checkHind(0x20)) && (!(dComIfGp_checkPlayerStatus1(0, daPyStts1_UNK2000_e))))) ||
        (dMenu_getCollectMode() == 4) || (i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK100000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK80000_e) || (dMeter_isAuctionFlag()) || (i_Meter->mStatusFlags & dMtrStts_UNK400000_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) || ((strcmp(dComIfGp_getStartStageName(), "Ojhous") == 0) && (dComIfGp_getMiniGameType() == 6)))
    {
        if (i_Meter->field_0x10f8.mUserArea > 0) {
            i_Meter->field_0x10f8.mUserArea--;
        } else {
            i_Meter->field_0x10f8.mUserArea = 0;
        }
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK8_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10_e)) {
        if (i_Meter->field_0x10f8.mUserArea < 3) {
            i_Meter->field_0x10f8.mUserArea++;
        } else if (i_Meter->field_0x10f8.mUserArea > 3) {
            i_Meter->field_0x10f8.mUserArea--;
        } else {
            i_Meter->field_0x10f8.mUserArea = 3;
        }
    } else {
        if (i_Meter->field_0x10f8.mUserArea < 5) {
            i_Meter->field_0x10f8.mUserArea++;
        } else {
            i_Meter->field_0x10f8.mUserArea = 5;
        }
    }
    i_Meter->field_0x2fc0 = fopMsgM_valueIncrease(5, i_Meter->field_0x10f8.mUserArea, 0);
}

/* 801FA53C-801FA670       .text dMeter_gaugeAlpha__FP15sub_meter_class */
void dMeter_gaugeAlpha(sub_meter_class* i_Meter) {
    f32 dVar4 = i_Meter->field_0x2fbc;
    f32 dVar3 = i_Meter->field_0x2fc0;
    for (s32 i = 0; i < 20; i++) {
        fopMsgM_setNowAlpha(&i_Meter->mHeart[i], dVar4);
        fopMsgM_setNowAlpha(&i_Meter->mHeartShadow[i], dVar4);
    }
    i_Meter->field_0x0f00.mNowAlpha = i_Meter->field_0x0f00.mNowAlpha * dVar4;
    i_Meter->field_0x0f00.pane->mAlpha = i_Meter->field_0x0f00.mNowAlpha * dVar4;
    for (s32 i = 0; i < 8; i++) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x0f38[i], dVar3);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x10f8, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x11a0, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x11d8, dVar3);
}

/* 801FA670-801FA6C4       .text dMeter_menuInit__FP15sub_meter_class */
void dMeter_menuInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x0250.mUserArea = 10;
    i_Meter->field_0x0288.mUserArea = 0;
    i_Meter->field_0x02c0.mUserArea = 0;
    i_Meter->field_0x0100[0].mUserArea = dComIfGs_isDungeonItemCompass();
}

/* 801FA6C4-801FA6F8       .text dMeter_menuMove__FP15sub_meter_class */
void dMeter_menuMove(sub_meter_class* i_Meter) {
    dMeter_menuLRMove(i_Meter);
    dMeter_menuPlusMove(i_Meter);
}

/* 801FA6F8-801FA918       .text dMeter_menuLRMove__FP15sub_meter_class */
void dMeter_menuLRMove(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 iVar3;
    s16 iVar4;
    s16 sVar5;
    f32 dVar6;
    f32 dVar7;

    static u8 frame = dMenu_getPushMenuButton();
    if ((i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (dMenu_getCollectMode() == 5)) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0250);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x0288);
    } else {
        sVar5 = 0x14;
        if (frame != dMenu_getPushMenuButton()) {
            if ((frame != 0) && (dMenu_getPushMenuButton() != 0)) {
                sVar5 = g_menuHIO.field_0x92 * 2;
                i_Meter->field_0x0250.mUserArea = sVar5;
                i_Meter->field_0x0288.mUserArea = 1;
            } else {
                i_Meter->field_0x0288.mUserArea = 0;
            }
            frame = dMenu_getPushMenuButton();
        }
        iVar4 = sVar5 / 2;
        if (dMenu_getPushMenuButton() != 0) {
            if (i_Meter->field_0x0250.mUserArea != 0) {
                i_Meter->field_0x0250.mUserArea--;
            }
        } else {
            if (i_Meter->field_0x0250.mUserArea < iVar4) {
                i_Meter->field_0x0250.mUserArea++;
            } else if (i_Meter->field_0x0250.mUserArea > iVar4) {
                i_Meter->field_0x0250.mUserArea--;
            }
        }
        iVar3 = (int)i_Meter->field_0x0250.mUserArea;
        int iVar4_2 = iVar4;
        if (iVar3 > iVar4_2) {
            dVar6 = fopMsgM_valueIncrease(iVar4_2, sVar5 - iVar3, 0);
            if (i_Meter->field_0x0288.mUserArea != 0) {
                dVar7 = 1.0f;
            } else {
                dVar7 = fopMsgM_valueIncrease(iVar4_2, i_Meter->field_0x0250.mUserArea - iVar4_2, 0);
            }
        } else {
            dVar6 = fopMsgM_valueIncrease(iVar4_2, iVar3, 0);
            if (i_Meter->field_0x0288.mUserArea != 0) {
                dVar7 = 1.0f;
            } else {
                dVar7 = fopMsgM_valueIncrease(iVar4_2, iVar4_2 - i_Meter->field_0x0250.mUserArea, 0);
            }
        }
        fopMsgM_paneTrans(&i_Meter->field_0x0250, dVar6 * 20.0f, 0.0f);
        fopMsgM_paneTrans(&i_Meter->field_0x0288, dVar6 * -20.0f, 0.0f);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0250, dVar7);
        fopMsgM_setNowAlpha(&i_Meter->field_0x0288, dVar7);
    }
}

/* 801FA918-801FBB28       .text dMeter_menuPlusMove__FP15sub_meter_class */
void dMeter_menuPlusMove(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 fVar1;
    int iVar3;
    f32 x;
    f32 y;
    f32 dVar13;
    f32 dVar12;

    static s16 moveFlag = 0;
    static s16 moveStatus = 0;
    f32 local_98_x[] = {0.0f, 0.0f, 0.0f};
    f32 local_98_y[] = {0.0f, 0.0f, 0.0f};
    if (i_Meter->field_0x0100[0].mUserArea != (s16)dComIfGs_isDungeonItemCompass()) {
        if ((s32)dMeter_mMapCtrlDisp.field_0x0 == 0x0) {
            if (dMap_isEnableDispMap()) {
                dMeter_mMapCtrlDisp.field_0x0 = 0x1;
                dMeter_mMapCtrlDisp.field_0x1 = 0;
            }
            i_Meter->field_0x3029 = 1;
        }
        i_Meter->field_0x3027 = 0;
        i_Meter->field_0x0100[0].mUserArea = dComIfGs_isDungeonItemCompass();
    }
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || (fopOvlpM_IsDoingReq()) ||
        ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(0x100))) ||
        (((((((((i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100_e)) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e)) ||
              ((i_Meter->mStatusFlags & dMtrStts_UNK100000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20000_e))) ||
             (i_Meter->mStatusFlags & dMtrStts_UNK8_e)) ||
            (((i_Meter->mStatusFlags & dMtrStts_UNK10_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) ||
             ((i_Meter->mStatusFlags & dMtrStts_UNK20_e) || (((i_Meter->mStatusFlags & dMtrStts_UNK80000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800_e)) ||
                                                             (i_Meter->mStatusFlags & dMtrStts_UNK1000_e))))) ||
           (((!(i_Meter->mStatusFlags & dMtrStts_UNK400_e)) && (strcmp(dComIfGp_getNextStageName(), "MajyuE") == 0)) &&
            (!(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0801))))) ||
          ((!(i_Meter->mStatusFlags & dMtrStts_UNK400_e)) &&
           ((strcmp(dComIfGp_getNextStageName(), "Hyrule") == 0 || (strcmp(dComIfGp_getNextStageName(), "Hyroom") == 0)) ||
            (strcmp(dComIfGp_getNextStageName(), "kenroom") == 0)))) ||
         (dComIfGp_getMiniGameType() == 1 || (dComIfGp_getMiniGameType() == 6))))
    {
        if (moveStatus != 1) {
            moveFlag = 1;
        }
        moveStatus = 1;
    } else {
        if ((i_Meter->field_0x3020 == 1) || (i_Meter->field_0x3020 == 2)) {
            if (((s32)dMeter_mMapCtrlDisp.field_0x0 != 0x0) && (dMap_isEnableDispMap())) {
                if (moveStatus != 2) {
                    moveFlag = 1;
                }
                moveStatus = 2;
            } else if (dMap_isEnableDispMap()) {
                if (moveStatus != 3) {
                    moveFlag = 1;
                }
                moveStatus = 3;
            } else if ((i_Meter->mStatusFlags & dMtrStts_UNK400_e) && (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) != dSv_save_c::STAGE_TOTG)) {
                if (moveStatus != 7) {
                    moveFlag = 1;
                }
                moveStatus = 7;
            } else {
                if (moveStatus != 6) {
                    moveFlag = 1;
                }
                moveStatus = 6;
            }
        } else if (((i_Meter->field_0x3020 == 5) || (i_Meter->field_0x3020 == 9)) || (i_Meter->field_0x3020 == 3)) {
            if (moveStatus != 4) {
                moveFlag = 1;
            }
            moveStatus = 4;
        } else {
            if (moveStatus != 5) {
                moveFlag = 1;
            }
            moveStatus = 5;
        }
    }
    if (moveFlag != 0) {
        if (i_Meter->field_0x02c0.mUserArea >= 5) {
            i_Meter->field_0x02c0.mUserArea = 5;
        } else {
            i_Meter->field_0x02c0.mUserArea++;
        }
        switch (moveStatus) {
        case 2:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            i_Meter->field_0x02c0.pane->hide();
            sMainParts1->search('cry1')->hide();
            sMainParts1->search('cry3')->hide();
            i_Meter->field_0x0100[0].pane->show();
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                i_Meter->field_0x0100[1].pane->show();
            } else {
                i_Meter->field_0x0100[1].pane->hide();
            }
            i_Meter->field_0x0100[2].pane->show();
            moveFlag = 0;
            break;
        case 3:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            i_Meter->field_0x02c0.pane->show();
            sMainParts1->search('cry1')->show();
            i_Meter->field_0x0100[0].pane->hide();
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                i_Meter->field_0x0100[1].pane->show();
                sMainParts1->search('cry3')->show();
            } else {
                i_Meter->field_0x0100[1].pane->hide();
                sMainParts1->search('cry3')->hide();
            }
            i_Meter->field_0x0100[2].pane->hide();
            moveFlag = 0;
            break;
        case 4:
            x = g_meterHIO.field_0x9c + 0x52;
            y = g_meterHIO.field_0x9e;
            i_Meter->field_0x02c0.pane->show();
            sMainParts1->search('cry1')->show();
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                sMainParts1->search('cry3')->show();
            } else {
                sMainParts1->search('cry3')->hide();
            }
            i_Meter->field_0x0100[0].pane->hide();
            i_Meter->field_0x0100[1].pane->hide();
            i_Meter->field_0x0100[2].pane->hide();
            moveFlag = 0;
            break;
        case 5:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            i_Meter->field_0x02c0.pane->hide();
            sMainParts1->search('cry1')->hide();
            sMainParts1->search('cry3')->hide();
            i_Meter->field_0x0100[0].pane->hide();
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                i_Meter->field_0x0100[1].pane->show();
            } else {
                i_Meter->field_0x0100[1].pane->hide();
            }
            i_Meter->field_0x0100[2].pane->show();
            moveFlag = 0;
            break;
        case 6:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                i_Meter->field_0x02c0.pane->show();
                sMainParts1->search('cry1')->hide();
                sMainParts1->search('cry3')->show();
            } else {
                i_Meter->field_0x02c0.pane->hide();
                sMainParts1->search('cry1')->hide();
                sMainParts1->search('cry3')->hide();
            }
            i_Meter->field_0x0100[0].pane->hide();
            i_Meter->field_0x0100[1].pane->hide();
            i_Meter->field_0x0100[2].pane->hide();
            moveFlag = 0;
            break;
        case 7:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_0908)) && (dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 0)) ||
                ((dStage_stagInfo_GetUpButton(dComIfGp_getStageStagInfo()) == 1) && (!(i_Meter->mStatusFlags & dMtrStts_UNK400000_e))))
            {
                i_Meter->field_0x02c0.pane->show();
                sMainParts1->search('cry1')->show();
                sMainParts1->search('cry3')->show();
            } else {
                i_Meter->field_0x02c0.pane->hide();
                sMainParts1->search('cry1')->show();
                sMainParts1->search('cry3')->hide();
            }
            i_Meter->field_0x0100[0].pane->hide();
            i_Meter->field_0x0100[1].pane->hide();
            i_Meter->field_0x0100[2].pane->hide();
            moveFlag = 0;
            break;
        default:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            break;
        }
    } else {
        if (i_Meter->field_0x02c0.mUserArea <= 0) {
            i_Meter->field_0x02c0.mUserArea = 0;
        } else {
            i_Meter->field_0x02c0.mUserArea--;
        }
        switch (moveStatus) {
        case 2:
        case 3:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            break;
        case 4:
        case 6:
        case 7:
            x = g_meterHIO.field_0x9c + 0x52;
            y = g_meterHIO.field_0x9e;
            break;
        case 5:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            break;
        default:
            x = g_meterHIO.field_0x9c;
            y = g_meterHIO.field_0x9e;
            break;
        }
    }
    if ((moveStatus == 4) || (moveStatus == 5)) {
        f32 tmp = 0.5f;
        local_98_x[0] = ((i_Meter->field_0x12f0.mPosCenter.x + i_Meter->field_0x12f0.mSize.x * tmp) - i_Meter->field_0x0100[0].mPosCenterOrig.x) -
                        i_Meter->field_0x0100[0].mSizeOrig.x * tmp;
        fVar1 = i_Meter->field_0x12f0.mPosCenter.y;
        local_98_y[0] = fVar1 - i_Meter->field_0x0100[0].mPosCenterOrig.y;
        local_98_x[1] = i_Meter->field_0x12f0.mPosCenter.x - i_Meter->field_0x0100[1].mPosCenterOrig.x;
        local_98_y[1] =
            ((fVar1 - i_Meter->field_0x12f0.mSize.y * tmp) - i_Meter->field_0x0100[1].mPosCenterOrig.y) - i_Meter->field_0x0100[1].mSizeOrig.y * tmp;
        local_98_x[2] = i_Meter->field_0x0100[2].mSizeOrig.x * tmp +
                        ((i_Meter->field_0x1948.mPosCenter.x + i_Meter->field_0x16e0.mSize.x * tmp) - i_Meter->field_0x0100[2].mPosCenterOrig.x);
        local_98_y[2] = i_Meter->field_0x1948.mPosCenter.y - i_Meter->field_0x0100[2].mPosCenterOrig.y;
    } else {
        s16 tmp3 = dMap_c::mDispSizeX;
        s16 tmp2 = dMap_getMapDispPosLeftUpX();
        f32 tmp = 0.5f;
        local_98_x[2] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[1].mPosCenterOrig.x;
        local_98_x[1] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[1].mPosCenterOrig.x;
        local_98_x[0] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[1].mPosCenterOrig.x;
        tmp3 = dMap_c::mDispSizeY;
        tmp2 = dMap_getMapDispPosLeftUpY();
        tmp = 0.5f;
        local_98_y[2] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[0].mPosCenterOrig.y;
        local_98_y[1] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[0].mPosCenterOrig.y;
        local_98_y[0] = (tmp2 + tmp3 * tmp) - i_Meter->field_0x0100[0].mPosCenterOrig.y;
    }
    dVar13 = dMap_getMapDispPosLeftUpX() - 0x19;
    dVar12 = dMap_getMapDispPosLeftUpY() - 0x152;
    cXyz* pcVar4 = dKyw_get_wind_vec();
    iVar3 = cM_atan2s(pcVar4->x, pcVar4->z);
    f32 tmp = 0.5f;
    i_Meter->field_0x02f8.pane->rotate(
        i_Meter->field_0x02f8.mSizeOrig.x, i_Meter->field_0x02f8.mSizeOrig.y * tmp, ROTATE_Z, (iVar3 * 180.0f) / 32768.0f - 180.0f
    );
    fopMsgM_paneTrans(&i_Meter->field_0x02c0, x, y);
    fopMsgM_paneTrans(&i_Meter->field_0x02f8, (dVar13 - 7.0f) + g_meterHIO.field_0x64, (dVar12 + 9.0f) + g_meterHIO.field_0x66);
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_paneTrans(&i_Meter->field_0x0100[i], x + local_98_x[i], y + local_98_y[i]);
    }
    dVar13 = fopMsgM_valueIncrease(5, 5 - i_Meter->field_0x02c0.mUserArea, 0);
    fopMsgM_setNowAlpha(&i_Meter->field_0x02c0, dVar13);
    dMap_c::mAlpha = dVar13 * 255.0f;
    if (!(dKyw_gbwind_use_check()) || (dMenu_flag())) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x02f8);
    } else {
        fopMsgM_setNowAlpha(&i_Meter->field_0x02f8, dVar13);
    }

    for (s32 i = 0; i < 3; i++) {
        if (!dMenu_flag()) {
            fopMsgM_setNowAlpha(&i_Meter->field_0x0100[i], dVar13);
        } else {
            fopMsgM_setNowAlphaZero(&i_Meter->field_0x0100[i]);
        }
    }
}

/* 801FBB28-801FBC70       .text dMeter_magicLength__FP15sub_meter_classf */
void dMeter_magicLength(sub_meter_class* i_Meter, f32 param_2) {
    f32 dVar1 = (i_Meter->field_0x0f38[0].mSizeOrig.x * 8.0f);
    f32 tmp = 0.5f;
    i_Meter->field_0x10f8.mSize.x = (dVar1 * param_2) + (i_Meter->field_0x10f8.mSizeOrig.x - dVar1);
    i_Meter->field_0x10f8.mPosCenter.x = i_Meter->field_0x10f8.mPosTopLeftOrig.x + i_Meter->field_0x10f8.mSize.x * tmp;
    fopMsgM_cposMove(&i_Meter->field_0x10f8);
    ((MyPicture*)i_Meter->field_0x11a0.pane)->m134 = 1;
    ((MyPicture*)i_Meter->field_0x11a0.pane)->m124 = 0.0f;
    ((MyPicture*)i_Meter->field_0x11a0.pane)->m128 = 0.0f;
    ((MyPicture*)i_Meter->field_0x11a0.pane)->m12C = 1.6875f;
    ((MyPicture*)i_Meter->field_0x11a0.pane)->m130 = 0.8125f;
    i_Meter->field_0x11a0.mSize.x = i_Meter->field_0x10f8.mSize.x + (i_Meter->field_0x11a0.mSizeOrig.x - i_Meter->field_0x10f8.mSizeOrig.x);
    i_Meter->field_0x11a0.mPosCenter.x = i_Meter->field_0x11a0.mPosTopLeftOrig.x + i_Meter->field_0x11a0.mSize.x * tmp;
    fopMsgM_cposMove(&i_Meter->field_0x11a0);
    ((MyPicture*)i_Meter->field_0x1130.pane)->m134 = 1;
    ((MyPicture*)i_Meter->field_0x1130.pane)->m124 = 0.0f;
    ((MyPicture*)i_Meter->field_0x1130.pane)->m128 = 0.0f;
    ((MyPicture*)i_Meter->field_0x1130.pane)->m12C = 1.6875f;
    ((MyPicture*)i_Meter->field_0x1130.pane)->m130 = 0.8125f;
    i_Meter->field_0x1130.mSize.x = i_Meter->field_0x10f8.mSize.x + (i_Meter->field_0x1130.mSizeOrig.x - i_Meter->field_0x10f8.mSizeOrig.x);
    i_Meter->field_0x1130.mPosCenter.x = i_Meter->field_0x1130.mPosTopLeftOrig.x + i_Meter->field_0x1130.mSize.x * tmp;
    fopMsgM_cposMove(&i_Meter->field_0x1130);
}

/* 801FBC70-801FBC90       .text dMeter_windInit__FP15sub_meter_class */
void dMeter_windInit(sub_meter_class* i_Meter) {
    dMeter_windID = fpcM_ERROR_PROCESS_ID_e;
    dMeter_windStatus = 0;
    dComIfGp_setOperateWindCancelOff();
}

/* 801FBC90-801FBCEC       .text dMeter_metronomeInit__FP15sub_meter_class */
void dMeter_metronomeInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x3028 = 0;
    if (dMn_c != NULL) {
        dMn_c->_delete();
        delete dMn_c;
        dMn_c = NULL;
    }
}

/* 801FBCEC-801FBD7C       .text dMeter_windMove__FP15sub_meter_class */
void dMeter_windMove(sub_meter_class* i_Meter) {
    if (dMeter_windStatus != dComIfGp_getOperateWind()) {
        if (dComIfGp_getOperateWind() == 2) {
            dMeter_windID = fopMsgM_Create(PROC_OPERATE_WIND, NULL, NULL);
        }
        dMeter_windStatus = dComIfGp_getOperateWind();
    } else {
        if (((dComIfGp_getOperateWind() != 2) && (dMeter_windID != fpcM_ERROR_PROCESS_ID_e)) && (fopMsgM_SearchByID(dMeter_windID) == NULL)) {
            dMeter_windID = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 801FBD7C-801FBF24       .text dMeter_metronomeMove__FP15sub_meter_class */
void dMeter_metronomeMove(sub_meter_class* i_Meter) {
    if (((dComIfGp_getMetronome() && (!(i_Meter->mStatusFlags & dMtrStts_UNK8_e))) && (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e))) &&
        ((!(i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e))))
    {
        if ((i_Meter->field_0x3028 == 0) && (dMn_c == NULL)) {
            dMn_c = new dMetronome_c();
            JUT_ASSERT(9008, dMn_c != NULL);
            dMn_c->_create();
            dMn_c->initialize();
        }
        if ((dMn_c != NULL) && ((u8)dMn_c->_open() != 0)) {
            dMn_c->_move();
        }
        i_Meter->field_0x3028 = 1;
    } else {
        if (i_Meter->field_0x3028 == 1) {
            if (dMn_c != NULL) {
                if ((u8)dMn_c->_close() == 0) {
                    dMn_c->_move();
                } else {
                    i_Meter->field_0x3028 = 2;
                }
            }
        } else if ((i_Meter->field_0x3028 == 2) && (dMn_c != NULL)) {
            i_Meter->field_0x3028 = 0;
            dMn_c->_delete();
            delete dMn_c;
            dMn_c = NULL;
        }
    }
}

/* 801FBF24-801FC190       .text dMeter_rupyAlpha__FP15sub_meter_class */
void dMeter_rupyAlpha(sub_meter_class* i_Meter) {
    f32 dVar7;
    f32 fVar8;
    cXyz local_2c;
    cXyz local_38;

    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(0x80))) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK400000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK8_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK10_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20_e) ||
        (dComIfGp_getMiniGameType() == 1 || (dComIfGp_getMiniGameType() == 6)))
    {
        dVar7 = dMeter_alphaClose(&i_Meter->field_0x2a20.mUserArea, &i_Meter->field_0x19f0[0].mUserArea);
        if (i_Meter->mpRupyParticle != NULL) {
            i_Meter->mpRupyParticle->stopDrawParticle();
        } else {
            local_2c.set(i_Meter->field_0x2a20.mPosCenter.x - 320.0f, i_Meter->field_0x2a20.mPosCenter.y - 240.0f, 0.0f);
            i_Meter->mpRupyParticle = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_002D, &local_2c);
        }
    } else {
        fVar8 = dMeter_alphaOpen(&i_Meter->field_0x2a20.mUserArea, &i_Meter->field_0x19f0[0].mUserArea);
        dVar7 = fVar8;
        if (i_Meter->mpRupyParticle != NULL) {
            i_Meter->mpRupyParticle->playDrawParticle();
        } else {
            local_38.set(i_Meter->field_0x2a20.mPosCenter.x - 320.0f, i_Meter->field_0x2a20.mPosCenter.y - 240.0f, 0.0f);
            i_Meter->mpRupyParticle = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_002D, &local_38);
        }
    }
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x19f0[i], dVar7);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1b40[i], dVar7);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x2a20, dVar7);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2a58, dVar7);
}

/* 801FC190-801FC2FC       .text dMeter_rupyInit__FP15sub_meter_class */
void dMeter_rupyInit(sub_meter_class* i_Meter) {
    char acStack_3c[16];
    int local_2c[5];
    cXyz local_48;

    i_Meter->field_0x2a20.mUserArea = 0;
    i_Meter->field_0x19f0[0].mUserArea = 0;
    i_Meter->field_0x19f0[0].mUserArea = 1;
    i_Meter->mRupyCount = dComIfGs_getRupee();
    local_2c[0] = i_Meter->mRupyCount / 1000;
    local_2c[1] = (i_Meter->mRupyCount % 1000) / 100;
    local_2c[2] = (i_Meter->mRupyCount % 100) / 10;
    local_2c[3] = i_Meter->mRupyCount % 10;
    for (s32 i = 0; i < 4; i++) {
        dMeter_rupy_num(acStack_3c, local_2c[i]);
        ((J2DPicture*)i_Meter->field_0x19f0[i].pane)->changeTexture(acStack_3c, 0);
        ((J2DPicture*)i_Meter->field_0x1b40[i].pane)->changeTexture(acStack_3c, 0);
    }
    g_dComIfG_gameInfo.play.mItemNowRupee = i_Meter->mRupyCount;
    local_48.set(i_Meter->field_0x2a20.mPosCenter.x - 320.0f, i_Meter->field_0x2a20.mPosCenter.y - 240.0f, 0.0f);
    i_Meter->mpRupyParticle = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_002D, &local_48);
}

/* 801FC2FC-801FC624       .text dMeter_rupyMove__FP15sub_meter_class */
void dMeter_rupyMove(sub_meter_class* i_Meter) {
    int maxRupees;
    int iVar2;
    int uVar3;
    int local_28[4];
    char acStack_38[16];

    if (i_Meter->field_0x19f0[1].mUserArea != dComIfGs_getWalletSize()) {
        dMeter_walletChange(i_Meter);
        i_Meter->field_0x19f0[1].mUserArea = dComIfGs_getWalletSize();
    }
    if (dComIfGp_getItemRupeeCount() != 0) {
        maxRupees = (dComIfGs_getRupee() + dComIfGp_getItemRupeeCount());
        if (dComIfGs_getWalletSize() == 0) {
            iVar2 = 200;
        } else if (dComIfGs_getWalletSize() == 1) {
            iVar2 = 1000;
        } else {
            iVar2 = 5000;
        }
        if (maxRupees > iVar2) {
            maxRupees = iVar2;
        } else if (maxRupees < 0) {
            maxRupees = 0;
        }
        i_Meter->mAdjustRupy = maxRupees - i_Meter->mRupyCount;
        dComIfGs_setRupee(maxRupees);
        g_dComIfG_gameInfo.play.mItemRupeeCount = 0;
        if (labs(i_Meter->mAdjustRupy) >= 5) {
            rupy_soundOnFlag = 1;
        }
    }
    if (i_Meter->mAdjustRupy != 0) {
        if (i_Meter->mAdjustRupy > 0) {
            i_Meter->mRupyCount++;
            i_Meter->mAdjustRupy--;
            if (rupy_soundOnFlag != 0) {
                if (i_Meter->mAdjustRupy != 0) {
                    if (rupy_soundSetFlag == 0) {
                        mDoAud_seStart(JA_SE_LUPY_INC_CNT_1);
                        rupy_soundSetFlag = 1;
                    } else {
                        rupy_soundSetFlag = 0;
                    }
                } else {
                    mDoAud_seStart(JA_SE_LUPY_INC_CNT_2);
                    rupy_soundSetFlag = 0;
                    rupy_soundOnFlag = 0;
                }
            }
        } else {
            if (i_Meter->mAdjustRupy < 0) {
                i_Meter->mRupyCount--;
                i_Meter->mAdjustRupy++;
                if (rupy_soundOnFlag != 0) {
                    if (i_Meter->mAdjustRupy != 0) {
                        if (rupy_soundSetFlag == 0) {
                            mDoAud_seStart(JA_SE_LUPY_DEC_CNT_1);
                            rupy_soundSetFlag = 1;
                        } else {
                            rupy_soundSetFlag = 0;
                        }
                    } else {
                        mDoAud_seStart(JA_SE_LUPY_DEC_CNT_2);
                        rupy_soundSetFlag = 0;
                        rupy_soundOnFlag = 0;
                    }
                }
            }
        }
        uVar3 = i_Meter->mRupyCount;
        local_28[0] = uVar3 / 1000;
        local_28[1] = (uVar3 % 1000) / 100;
        local_28[2] = (uVar3 % 100) / 10;
        local_28[3] = uVar3 % 10;
        for (s32 i = 0; i < 4; i++) {
            dMeter_rupy_num(acStack_38, local_28[i]);
            ((J2DPicture*)(i_Meter->field_0x19f0[i].pane))->changeTexture(acStack_38, 0);
            ((J2DPicture*)(i_Meter->field_0x1b40[i].pane))->changeTexture(acStack_38, 0);
        }
        g_dComIfG_gameInfo.play.mItemNowRupee = i_Meter->mRupyCount;
    }
    dMeter_rupyAlpha(i_Meter);
}

/* 801FC624-801FC85C       .text dMeter_walletChange__FP15sub_meter_class */
void dMeter_walletChange(sub_meter_class* i_Meter) {
    if (dComIfGs_getWalletSize() == 0) {
        f32 x = (i_Meter->field_0x19f0[1].mPosTopLeftOrig.x - i_Meter->field_0x19f0[0].mPosTopLeftOrig.x);
        i_Meter->field_0x19f0[0].pane->hide();
        i_Meter->field_0x1b40[0].pane->hide();
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setBlack(0x0A280A00);
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setWhite(0x28FF28FF);
        fopMsgM_paneTrans(&i_Meter->field_0x2a20, x, 0.0f);
        fopMsgM_paneTrans(&i_Meter->field_0x2a58, x, 0.0f);
    } else if (dComIfGs_getWalletSize() == 1) {
        i_Meter->field_0x19f0[0].pane->show();
        i_Meter->field_0x1b40[0].pane->show();
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setBlack(0x1414A000);
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setWhite(0x32C8FFFF);
        fopMsgM_paneTrans(&i_Meter->field_0x2a20, 0.0f, 0.0f);
        fopMsgM_paneTrans(&i_Meter->field_0x2a58, 0.0f, 0.0f);
    } else {
        i_Meter->field_0x19f0[0].pane->show();
        i_Meter->field_0x1b40[0].pane->show();
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setBlack(0x50280000);
        ((J2DPicture*)(i_Meter->field_0x2a20).pane)->setWhite(0xFF8C00FF);
        fopMsgM_paneTrans(&i_Meter->field_0x2a20, 0.0f, 0.0f);
        fopMsgM_paneTrans(&i_Meter->field_0x2a58, 0.0f, 0.0f);
    }
}

/* 801FC85C-801FCA98       .text dMeter_keyLight__FP18fopMsgM_pane_classPsf */
void dMeter_keyLight(fopMsgM_pane_class* param_1, s16* param_2, f32 param_3) {
    /* Nonmatching */
    f32 dVar6;
    f32 dVar7;
    f32 dVar8;
    f32 dVar10;

    if (param_1->mUserArea < param_2[0]) {
        dVar8 = 0.0f;
        dVar7 = dVar8;
    } else if (param_1->mUserArea < param_2[1]) {
        dVar6 = fopMsgM_valueIncrease(param_2[1] - param_2[0], param_1->mUserArea - param_2[0], 0);
        dVar8 = (dVar6 * 0.8f) + 0.2f;
        dVar7 = dVar6 * 170.0f;
    } else if (param_1->mUserArea < param_2[2]) {
        dVar6 = fopMsgM_valueIncrease(param_2[2] - param_2[1], param_1->mUserArea - param_2[1], 0);
        dVar8 = 1.0f - (dVar6 * 0.2f);
        dVar7 = 170.0f - (dVar6 * 90.0f);
    } else if (param_1->mUserArea < param_2[3]) {
        dVar6 = fopMsgM_valueIncrease(param_2[3] - param_2[2], param_1->mUserArea - param_2[2], 0);
        dVar8 = (dVar6 * 0.2f) + 0.8f;
        dVar7 = (dVar6 * 90.0f) + 80.0f;
    } else {
        dVar6 = fopMsgM_valueIncrease(param_2[4] - param_2[3], param_1->mUserArea - param_2[3], 0);
        dVar8 = 1.0f;
        dVar7 = 170.0f - (dVar6 * 170.0f);
    }
    if (param_1->mUserArea < param_2[4]) {
        param_1->mUserArea++;
    } else {
        param_1->mUserArea = 1;
    }
    f32 tmp = 0.5f;
    dVar10 = param_1->mSizeOrig.x * dVar8;
    f32 dVar9 = param_1->mSizeOrig.y * dVar8;
    f32 x = param_1->mPosTopLeftOrig.x - (dVar10 - param_1->mSizeOrig.x) * tmp;
    f32 y = param_1->mPosTopLeftOrig.y - (dVar9 - param_1->mSizeOrig.y) * tmp;
    param_1->pane->move(x, y);
    param_1->pane->resize(dVar10, dVar9);
    J2DPane* j2dPane = param_1->pane;
    j2dPane->mBasePosition.x = (dVar10 * tmp);
    j2dPane->mBasePosition.y = (dVar9 * tmp);
    j2dPane->mRotationAxis = ROTATE_Z;
    j2dPane->calcMtx();
    param_1->mNowAlpha = dVar7 * param_3;
}

/* 801FCA98-801FCCA8       .text dMeter_keyRndLightFrame__FPs */
void dMeter_keyRndLightFrame(s16* param_1) {
    param_1[0] = g_meterHIO.field_0x90 + cM_rndFX(g_meterHIO.field_0x9a);
    param_1[1] = (param_1[0] + g_meterHIO.field_0x88) + cM_rndFX(g_meterHIO.field_0x92);
    param_1[2] = (param_1[1] + g_meterHIO.field_0x8a) + cM_rndFX(g_meterHIO.field_0x94);
    param_1[3] = (param_1[2] + g_meterHIO.field_0x8c) + cM_rndFX(g_meterHIO.field_0x96);
    param_1[4] = (param_1[3] + g_meterHIO.field_0x8e) + cM_rndFX(g_meterHIO.field_0x98);
}

/* 801FCCA8-801FCE68       .text dMeter_keyAlpha__FP15sub_meter_class */
void dMeter_keyAlpha(sub_meter_class* i_Meter) {
    f32 dVar5;
    s16 local_28[5];

    local_28[0] = 0x1e;
    local_28[1] = 0x28;
    local_28[2] = 0x2d;
    local_28[3] = 0x32;
    local_28[4] = 0x3A;
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(0x40))) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK200000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK400000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK400_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK8_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10_e) || (i_Meter->mStatusFlags & dMtrStts_UNK800000_e) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK20_e))
    {
        dVar5 = dMeter_alphaClose(&i_Meter->field_0x1c90.mUserArea, &i_Meter->field_0x1ad0[0].mUserArea);
    } else if (dStage_stagInfo_ChkKeyDisp(dComIfGp_getStageStagInfo()) != 0) {
        dVar5 = dMeter_alphaOpen(&i_Meter->field_0x1c90.mUserArea, &i_Meter->field_0x1ad0[0].mUserArea);
    } else {
        dVar5 = dMeter_alphaClose(&i_Meter->field_0x1c90.mUserArea, &i_Meter->field_0x1ad0[0].mUserArea);
    }
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1ad0[i], dVar5);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1c20[i], dVar5);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x1c90, dVar5);
    if (i_Meter->field_0x19b8.mUserArea == 1) {
        dMeter_keyRndLightFrame(&i_Meter->field_0x2fda);
    }
    dMeter_keyLight(&i_Meter->field_0x1980, local_28, dVar5);
    dMeter_keyLight(&i_Meter->field_0x19b8, &i_Meter->field_0x2fda, dVar5);
}

/* 801FCE68-801FCF28       .text dMeter_keyInit__FP15sub_meter_class */
void dMeter_keyInit(sub_meter_class* i_Meter) {
    int local_38[2];
    char acStack_30[24];

    i_Meter->field_0x19b8.mUserArea = 1;
    i_Meter->field_0x1980.mUserArea = 1;
    i_Meter->field_0x1c90.mUserArea = 0;
    i_Meter->field_0x1ad0[0].mUserArea = 0;
    i_Meter->field_0x301d = dComIfGs_getKeyNum();
    local_38[0] = i_Meter->field_0x301d / 10;
    local_38[1] = i_Meter->field_0x301d % 10;
    for (s32 i = 0; i < 2; i++) {
        dMeter_rupy_num(acStack_30, local_38[i]);
        fopMsgM_blendInit(&i_Meter->field_0x1ad0[i], acStack_30);
        fopMsgM_blendInit(&i_Meter->field_0x1c20[i], acStack_30);
    }
}

/* 801FCF28-801FD09C       .text dMeter_keyMove__FP15sub_meter_class */
void dMeter_keyMove(sub_meter_class* i_Meter) {
    s16 sVar1;
    int local_38[2];
    char acStack_30[24];

    if (dStage_stagInfo_ChkKeyDisp(dComIfGp_getStageStagInfo())) {
        if (dComIfGp_getItemKeyNumCount() != 0) {
            sVar1 = dComIfGs_getKeyNum() + dComIfGp_getItemKeyNumCount();
            if (sVar1 > 99) {
                sVar1 = 99;
            } else if (sVar1 < 0) {
                sVar1 = 0;
            }
            i_Meter->field_0x300e = sVar1 - (u16)i_Meter->field_0x301d;
            dComIfGs_setKeyNum((u8)sVar1);
            g_dComIfG_gameInfo.play.mItemKeyNumCount = 0;
        }
        sVar1 = i_Meter->field_0x300e;
        if (sVar1 != 0) {
            if (sVar1 > 0) {
                i_Meter->field_0x301d++;
                i_Meter->field_0x300e--;
            } else if (sVar1 < 0) {
                i_Meter->field_0x301d--;
                i_Meter->field_0x300e++;
            }
            local_38[0] = i_Meter->field_0x301d / 10;
            local_38[1] = i_Meter->field_0x301d % 10;
            for (s32 i = 0; i < 2; i++) {
                dMeter_rupy_num(acStack_30, local_38[i]);
                fopMsgM_blendDraw(&i_Meter->field_0x1ad0[i], acStack_30);
                fopMsgM_blendDraw(&i_Meter->field_0x1c20[i], acStack_30);
            }
        }
    }
    dMeter_keyAlpha(i_Meter);
}

/* 801FD09C-801FD104       .text dMeter_compassRotate__FP18fopMsgM_pane_classP18fopMsgM_pane_classf */
void dMeter_compassRotate(fopMsgM_pane_class* param_1, fopMsgM_pane_class* param_2, f32 param_3) {
    /* Nonmatching */
    f32 fVar1 = param_1->pane->mBounds.f.x - param_1->pane->mBounds.i.x;
    f32 fVar2 = param_1->pane->mBounds.f.y - param_1->pane->mBounds.i.y;
    param_1->pane->rotate(fVar2 * 0.5f, fVar1 * 0.5f, ROTATE_Z, param_3);
}

/* 801FD104-801FD410       .text dMeter_compassGetOnProc__FP15sub_meter_class */
void dMeter_compassGetOnProc(sub_meter_class* i_Meter) {
    switch (i_Meter->field_0x3020) {
    case 1:
        if (((s32)dMeter_mMapCtrlDisp.field_0x0 != 0) &&
            ((!(i_Meter->mStatusFlags & dMtrStts_UNK400_e)) || (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_TOTG)))
        {
            i_Meter->field_0x3020 = 2;
            i_Meter->field_0x3029 = 1;
        } else {
            i_Meter->field_0x3020 = 5;
            i_Meter->field_0x12f0.pane->show();
            dMeter_clockShow(i_Meter);
            dMeter_compassDirOpen(i_Meter);
            i_Meter->field_0x3029 = 0;
        }
        break;
    case 2:
        if ((s32)dMeter_mMapCtrlDisp.field_0x0 == 0) {
            i_Meter->field_0x12f0.pane->show();
            dMeter_clockShow(i_Meter);
            i_Meter->field_0x3020 = 5;
            dMeter_compassDirOpen(i_Meter);
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_MAP_SHOW);
        }
        break;
    case 5:
        dMeter_compassDirOpen(i_Meter);
        break;
    case 3:
        if (((CPad_CHECK_TRIG_RIGHT(0) && (!(CPad_CHECK_TRIG_UP(0)))) && (!(CPad_CHECK_TRIG_DOWN(0)))) || (i_Meter->field_0x1948.mUserArea != 0)) {
            i_Meter->field_0x3020 = 6;
            i_Meter->field_0x1948.mUserArea = 1;
            dMeter_compassWindOpen(i_Meter);
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_MAP_SHOW);
        }
        break;
    case 6:
        if ((CPad_CHECK_TRIG_LEFT(0) && (!(CPad_CHECK_TRIG_UP(0)))) && (!(CPad_CHECK_TRIG_DOWN(0)))) {
            i_Meter->field_0x3020 = 8;
            i_Meter->field_0x1948.mUserArea = 0;
            dMeter_compassWindClose(i_Meter);
        } else {
            dMeter_compassWindOpen(i_Meter);
        }
        break;
    case 8:
        if ((CPad_CHECK_TRIG_RIGHT(0) && (!(CPad_CHECK_TRIG_UP(0)))) && (!(CPad_CHECK_TRIG_DOWN(0)))) {
            i_Meter->field_0x3020 = 6;
            i_Meter->field_0x1948.mUserArea = 1;
            dMeter_compassWindOpen(i_Meter);
        } else {
            dMeter_compassWindClose(i_Meter);
        }
        break;
    case 9:
        dMeter_compassDirClose(i_Meter);
        break;
    case 7:
        dMeter_compassAnimeMove(i_Meter);
        break;
    }
    f32 dVar3 = (-(s16)(fopAcM_SearchByName(PROC_SHIP)->shape_angle.y + 0x8000) * 180.0f) / 32768.0f;
    dMeter_compassRotate(&i_Meter->field_0x1670, &i_Meter->field_0x16a8, (-dComIfGs_getTime() - 90.0f));
    dMeter_compassRotate(&i_Meter->field_0x1248, &i_Meter->field_0x12f0, dVar3);
    dMeter_compassRotate(&i_Meter->field_0x1280, &i_Meter->field_0x12f0, dVar3);
    dMeter_clockMove(i_Meter);
}

/* 801FD410-801FD48C       .text dMeter_compassGetOffProc__FP15sub_meter_class */
void dMeter_compassGetOffProc(sub_meter_class* i_Meter) {
    /* Nonmatching */
    switch (i_Meter->field_0x3020) {
    case 3:
        i_Meter->field_0x3020 = 9;
    case 9:
        dMeter_compassDirClose(i_Meter);
        break;
    case 5:
        i_Meter->field_0x3020 = 8;
        i_Meter->field_0x1948.mUserArea = 0;
    case 8:
        dMeter_compassWindClose(i_Meter);
        break;
    default:
        dMeter_compassValueInit(i_Meter);
        break;
    }
}

/* 801FD48C-801FD6C8       .text dMeter_compassDirOpen__FP15sub_meter_class */
void dMeter_compassDirOpen(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 dVar9;
    f32 dVar8;
    f32 dVar7;
    f32 dVar6;
    f32 dVar5;
    f32 fVar1;

    f32 tmp = 0.5f;
    fVar1 = i_Meter->field_0x13d0.pane->mBounds.f.x - i_Meter->field_0x13d0.pane->mBounds.i.x;
    dVar9 = ((i_Meter->field_0x1948.pane->mBounds.f.x - i_Meter->field_0x1948.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar8 = ((i_Meter->field_0x1948.pane->mBounds.f.y - i_Meter->field_0x1948.pane->mBounds.i.y) * tmp);
    dVar7 = ((i_Meter->field_0x16a8.pane->mBounds.f.x - i_Meter->field_0x16a8.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar6 = ((i_Meter->field_0x16a8.pane->mBounds.f.y - i_Meter->field_0x16a8.pane->mBounds.i.y) * tmp);
    i_Meter->field_0x12f0.mUserArea++;
    if (i_Meter->field_0x12f0.mUserArea >= 5) {
        i_Meter->field_0x12f0.mUserArea = 5;
        i_Meter->field_0x3020 = 3;
        dVar5 = 0.0f;
        if (i_Meter->field_0x302a != 0) {
            i_Meter->field_0x302a = 0;
            mDoAud_seStart(JA_SE_MAP_SHOW_END);
        }
    } else {
        dVar5 = fopMsgM_valueIncrease(5, 5 - i_Meter->field_0x12f0.mUserArea, 0);
        dVar5 = (dVar5 * -(i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1948.mSizeOrig.x));
        if (i_Meter->field_0x302a == 0) {
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_COMPASS_MOVE);
        }
    }
    fopMsgM_paneTrans(&i_Meter->field_0x12f0, dVar5, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x16a8, dVar5, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x1948, dVar5, 0.0f);
    i_Meter->field_0x16a8.pane->rotate(dVar7, dVar6, ROTATE_Z, 180.0f);
    i_Meter->field_0x1948.pane->rotate(dVar9, dVar8, ROTATE_Z, 180.0f);
}

/* 801FD6C8-801FD8C0       .text dMeter_compassWindOpen__FP15sub_meter_class */
void dMeter_compassWindOpen(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 dVar9;
    f32 dVar8;
    f32 dVar7;
    f32 dVar6;
    f32 dVar5;
    f32 fVar1;

    f32 tmp = 0.5f;
    fVar1 = i_Meter->field_0x13d0.pane->mBounds.f.x - i_Meter->field_0x13d0.pane->mBounds.i.x;
    dVar9 = ((i_Meter->field_0x1948.pane->mBounds.f.x - i_Meter->field_0x1948.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar8 = ((i_Meter->field_0x1948.pane->mBounds.f.y - i_Meter->field_0x1948.pane->mBounds.i.y) * tmp);
    dVar7 = ((i_Meter->field_0x16a8.pane->mBounds.f.x - i_Meter->field_0x16a8.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar6 = ((i_Meter->field_0x16a8.pane->mBounds.f.y - i_Meter->field_0x16a8.pane->mBounds.i.y) * tmp);
    i_Meter->field_0x12f0.mUserArea++;
    if (i_Meter->field_0x12f0.mUserArea >= 10) {
        i_Meter->field_0x12f0.mUserArea = 10;
        i_Meter->field_0x3020 = 7;
        dVar5 = 0.0f;
        if (i_Meter->field_0x302a != 0) {
            i_Meter->field_0x302a = 0;
            mDoAud_seStart(JA_SE_MAP_SHOW_END);
        }
    } else {
        dVar5 = (fopMsgM_valueIncrease(5, 10 - i_Meter->field_0x12f0.mUserArea, 0) * -180.0f);
        if (i_Meter->field_0x302a == 0) {
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_COMPASS_MOVE);
        }
    }
    i_Meter->field_0x16a8.pane->rotate(dVar7, dVar6, ROTATE_Z, dVar5);
    i_Meter->field_0x1948.pane->rotate(dVar9, dVar8, ROTATE_Z, dVar5);
}

/* 801FD8C0-801FDB64       .text dMeter_compassWindClose__FP15sub_meter_class */
void dMeter_compassWindClose(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 sVar6;
    f32 dVar11;
    f32 dVar10;
    f32 dVar9;
    f32 dVar8;
    f32 dVar7;
    f32 fVar1;

    f32 tmp = 0.5f;
    fVar1 = i_Meter->field_0x13d0.pane->mBounds.f.x - i_Meter->field_0x13d0.pane->mBounds.i.x;
    dVar11 = ((i_Meter->field_0x1948.pane->mBounds.f.x - i_Meter->field_0x1948.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar10 = ((i_Meter->field_0x1948.pane->mBounds.f.y - i_Meter->field_0x1948.pane->mBounds.i.y) * tmp);
    dVar9 = ((i_Meter->field_0x16a8.pane->mBounds.f.x - i_Meter->field_0x16a8.pane->mBounds.i.x) * tmp - (fVar1 * tmp));
    dVar8 = ((i_Meter->field_0x16a8.pane->mBounds.f.y - i_Meter->field_0x16a8.pane->mBounds.i.y) * tmp);
    i_Meter->field_0x12f0.mUserArea--;
    if ((dComIfGs_getTime() >= 90.0f) && (dComIfGs_getTime() < 270.0f)) {
        sVar6 = 0;
    } else {
        sVar6 = 1;
    }
    if (i_Meter->field_0x12f0.mUserArea <= 5) {
        i_Meter->field_0x12f0.mUserArea = 5;
        f32 tmp = 0.0f;
        if ((((dComIfGp_roomControl_getTimePass()) && (i_Meter->field_0x2f68 == tmp)) ||
             (!(dComIfGp_roomControl_getTimePass()) && (i_Meter->field_0x2f68 != tmp))) ||
            (!(dComIfGp_roomControl_getTimePass()) && (i_Meter->field_0x3012 != sVar6)))
        {
            dMeter_clockShow(i_Meter);
            i_Meter->field_0x3020 = 6;
            i_Meter->field_0x1948.mUserArea = 1;
        } else {
            i_Meter->field_0x3020 = 3;
        }
        dVar7 = -180.0f;
        if (i_Meter->field_0x302a != 0) {
            i_Meter->field_0x302a = 0;
            mDoAud_seStart(JA_SE_MAP_SHOW_END);
        }
    } else {
        dVar7 = (fopMsgM_valueIncrease(5, 10 - i_Meter->field_0x12f0.mUserArea, 0) * -180.0f);
        if (i_Meter->field_0x302a == 0) {
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_COMPASS_MOVE);
        }
    }
    i_Meter->field_0x16a8.pane->rotate(dVar9, dVar8, ROTATE_Z, dVar7);
    i_Meter->field_0x1948.pane->rotate(dVar11, dVar10, ROTATE_Z, dVar7);
}

/* 801FDB64-801FDDA4       .text dMeter_compassDirClose__FP15sub_meter_class */
void dMeter_compassDirClose(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 dVar9;
    f32 dVar8;
    f32 dVar7;
    f32 dVar6;
    f32 dVar5;
    f32 fVar2;

    f32 tmp = 0.5f;
    fVar2 = i_Meter->field_0x13d0.pane->mBounds.f.x - i_Meter->field_0x13d0.pane->mBounds.i.x;
    dVar9 = ((i_Meter->field_0x1948.pane->mBounds.f.x - i_Meter->field_0x1948.pane->mBounds.i.x) * tmp - (fVar2 * tmp));
    dVar8 = ((i_Meter->field_0x1948.pane->mBounds.f.y - i_Meter->field_0x1948.pane->mBounds.i.y) * tmp);
    dVar7 = ((i_Meter->field_0x16a8.pane->mBounds.f.x - i_Meter->field_0x16a8.pane->mBounds.i.x) * tmp - (fVar2 * tmp));
    dVar6 = ((i_Meter->field_0x16a8.pane->mBounds.f.y - i_Meter->field_0x16a8.pane->mBounds.i.y) * tmp);
    i_Meter->field_0x12f0.mUserArea = i_Meter->field_0x12f0.mUserArea + -1;
    if (i_Meter->field_0x12f0.mUserArea <= 0) {
        dMeter_compassValueInit(i_Meter);
        i_Meter->field_0x12f0.mUserArea = 0;
        dVar5 = -(i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1948.mSizeOrig.x);
        if (i_Meter->field_0x302a != 0) {
            i_Meter->field_0x302a = 0;
            mDoAud_seStart(JA_SE_MAP_SHOW_END);
        }
    } else {
        dVar5 = fopMsgM_valueIncrease(5, 5 - i_Meter->field_0x12f0.mUserArea, 0);
        dVar5 = (dVar5 * -(i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1948.mSizeOrig.x));
        if (i_Meter->field_0x302a == 0) {
            i_Meter->field_0x302a = 1;
            mDoAud_seStart(JA_SE_COMPASS_MOVE);
        }
    }
    fopMsgM_paneTrans(&i_Meter->field_0x12f0, dVar5, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x16a8, dVar5, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x1948, dVar5, 0.0f);
    i_Meter->field_0x16a8.pane->rotate(dVar7, dVar6, ROTATE_Z, 180.0f);
    i_Meter->field_0x1948.pane->rotate(dVar9, dVar8, ROTATE_Z, 180.0f);
}

/* 801FDDA4-801FDEC4       .text dMeter_compassAnimeMove__FP15sub_meter_class */
void dMeter_compassAnimeMove(sub_meter_class* i_Meter) {
    s16 sVar2;

    if ((dComIfGs_getTime() >= 90.0f) && (dComIfGs_getTime() < 270.0f)) {
        sVar2 = 0;
    } else {
        sVar2 = 1;
    }
    f32 tmp = 0.0f;
    if (((!(CPad_CHECK_TRIG_LEFT(0)) || (CPad_CHECK_TRIG_UP(0))) || (CPad_CHECK_TRIG_DOWN(0))) &&
        (!(dComIfGp_roomControl_getTimePass()) || (i_Meter->field_0x2f68 != tmp)) && (dComIfGp_roomControl_getTimePass() || (i_Meter->field_0x2f68 == tmp)))
    {
        if (dComIfGp_roomControl_getTimePass()) {
            return;
        }
        if (i_Meter->field_0x3012 == sVar2) {
            return;
        }
    }
    i_Meter->field_0x3020 = 8;
    i_Meter->field_0x1948.mUserArea = 0;
    i_Meter->field_0x302a = 1;
    mDoAud_seStart(JA_SE_MAP_CANCEL);
}

/* 801FDEC4-801FE0D0       .text dMeter_compassValueInit__FP15sub_meter_class */
void dMeter_compassValueInit(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 x;
    f32 dVar4;
    f32 dVar5;
    f32 dVar6;
    f32 dVar7;
    f32 dVar8;

    if (dComIfGp_roomControl_getTimePass()) {
        i_Meter->field_0x2f68 = 1.0f;
    } else {
        i_Meter->field_0x2f68 = 0.0f;
    }
    if ((dComIfGs_getTime() >= 90.0f) && (dComIfGs_getTime() < 270.0f)) {
        i_Meter->field_0x3012 = 0;
    } else {
        i_Meter->field_0x3012 = 1;
    }
    i_Meter->field_0x12f0.mUserArea = 0;
    i_Meter->field_0x302a = 0;
    dVar8 = i_Meter->field_0x13d0.pane->mBounds.f.x - i_Meter->field_0x13d0.pane->mBounds.i.x;
    dVar7 = i_Meter->field_0x1948.pane->mBounds.f.x - i_Meter->field_0x1948.pane->mBounds.i.x;
    dVar6 = i_Meter->field_0x1948.pane->mBounds.f.y - i_Meter->field_0x1948.pane->mBounds.i.y;
    dVar5 = i_Meter->field_0x16a8.pane->mBounds.f.x - i_Meter->field_0x16a8.pane->mBounds.i.x;
    dVar4 = i_Meter->field_0x16a8.pane->mBounds.f.y - i_Meter->field_0x16a8.pane->mBounds.i.y;
    x = -(i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1948.mSizeOrig.x);
    fopMsgM_paneTrans(&i_Meter->field_0x12f0, x, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x1948, x, 0.0f);
    f32 tmp = 0.5f;
    i_Meter->field_0x16a8.pane->rotate((dVar5 * tmp) - (dVar8 * tmp), dVar4 * tmp, ROTATE_Z, 180.0f);
    i_Meter->field_0x1948.pane->rotate((dVar7 * tmp) - (dVar8 * tmp), dVar6 * tmp, ROTATE_Z, 180.0f);
    i_Meter->field_0x1210.pane->hide();
    i_Meter->field_0x12f0.pane->hide();
    dMeter_clockHide(i_Meter);
    i_Meter->field_0x3020 = 1;
}

/* 801FE0D0-801FE230       .text dMeter_compassAlpha__FP15sub_meter_class */
void dMeter_compassAlpha(sub_meter_class* i_Meter) {
    f32 dVar3 = i_Meter->field_0x2f6c;
    fopMsgM_setNowAlpha(&i_Meter->field_0x1210, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x12f0, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1398, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x13d0, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1408, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1440, dVar3);
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1478[i], dVar3);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1868[0], dVar3);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x1520, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1558, dVar3);
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setNowAlpha(&i_Meter->field_0x1590[i], dVar3);
        fopMsgM_setNowAlpha(&i_Meter->field_0x1718[0], dVar3);
    }
    fopMsgM_setNowAlpha(&i_Meter->field_0x1670, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x16a8, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x16e0, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x17f8, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1830, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1910, dVar3);
    fopMsgM_setNowAlpha(&i_Meter->field_0x1948, dVar3);
}

/* 801FE230-801FE2EC       .text dMeter_compassInit__FP15sub_meter_class */
void dMeter_compassInit(sub_meter_class* i_Meter) {
    ((MyPicture*)i_Meter->field_0x1248.pane)->m134 = 1;
    ((MyPicture*)i_Meter->field_0x1248.pane)->m124 = -1.0f;
    ((MyPicture*)i_Meter->field_0x1248.pane)->m128 = 0.0f;
    ((MyPicture*)i_Meter->field_0x1248.pane)->m12C = 1.0f;
    ((MyPicture*)i_Meter->field_0x1248.pane)->m130 = 1.0f;
    ((MyPicture*)i_Meter->field_0x1280.pane)->m134 = 1;
    ((MyPicture*)i_Meter->field_0x1280.pane)->m124 = -1.0f;
    ((MyPicture*)i_Meter->field_0x1280.pane)->m128 = 0.0f;
    ((MyPicture*)i_Meter->field_0x1280.pane)->m12C = 1.0f;
    ((MyPicture*)i_Meter->field_0x1280.pane)->m130 = 1.0f;
    if ((s32)dMeter_mMapCtrlDisp.field_0x0 != 0) {
        i_Meter->field_0x3029 = 1;
    } else {
        i_Meter->field_0x3029 = 0;
    }
    i_Meter->field_0x1948.mUserArea = 0;
    dMeter_compassValueInit(i_Meter);
    dMeter_clockMultiInit(i_Meter);
}

/* 801FE2EC-801FE444       .text dMeter_compassMove__FP15sub_meter_class */
void dMeter_compassMove(sub_meter_class* i_Meter) {
    if ((i_Meter->mStatusFlags & dMtrStts_UNK4000_e) || ((i_Meter->mStatusFlags & dMtrStts_UNK40_e) && (dComIfGp_event_checkHind(0x100))) ||
        (i_Meter->mStatusFlags & dMtrStts_UNK200000_e))
    {
        dMeter_compassValueInit(i_Meter);
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK100_e) || (i_Meter->mStatusFlags & dMtrStts_UNK80_e) || (i_Meter->mStatusFlags & dMtrStts_UNK100000_e) ||
               (i_Meter->mStatusFlags & dMtrStts_UNK20000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK8_e) || (i_Meter->mStatusFlags & dMtrStts_UNK10_e) ||
               ((i_Meter->mStatusFlags & dMtrStts_UNK800000_e) || (i_Meter->mStatusFlags & dMtrStts_UNK20_e)) || (dComIfGp_getMiniGameType() == 1) ||
               (dComIfGp_getMiniGameType() == 8))
    {
        dMeter_compassValueInit(i_Meter);
    } else if ((i_Meter->mStatusFlags & dMtrStts_UNK400_e) && (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) != dSv_save_c::STAGE_TOTG)) {
        dMeter_compassGetOnProc(i_Meter);
        dMeter_compassAlpha(i_Meter);
        if (i_Meter->field_0x3027 == 0) {
            dMap_c::mMapDispMode = 1;
        } else {
            dMap_c::mMapDispMode = 0;
        }
    } else {
        dMeter_compassGetOffProc(i_Meter);
        dMeter_compassAlpha(i_Meter);
    }
    dMeter_clockMultiMove(i_Meter);
}

/* 801FE444-801FE8DC       .text dMeter_clockShow__FP15sub_meter_class */
void dMeter_clockShow(sub_meter_class* i_Meter) {
    if (dComIfGp_roomControl_getTimePass()) {
        i_Meter->field_0x2f68 = 1.0f;
    } else {
        i_Meter->field_0x2f68 = 0.0f;
    }
    if ((dComIfGs_getTime() >= 90.0f) && (dComIfGs_getTime() < 270.0f)) {
        i_Meter->field_0x3012 = 0;
    } else {
        i_Meter->field_0x3012 = 1;
    }
    dMeter_clockInit(i_Meter);
    if (dComIfGp_roomControl_getTimePass()) {
        i_Meter->field_0x1398.pane->show();
        i_Meter->field_0x13d0.pane->show();
        i_Meter->field_0x1408.pane->show();
        i_Meter->field_0x1440.pane->show();
        for (s32 i = 0; i < 3; i++) {
            i_Meter->field_0x1478[i].pane->show();
        }
        i_Meter->field_0x1520.pane->show();
        i_Meter->field_0x1558.pane->show();
        for (s32 i = 0; i < 4; i++) {
            i_Meter->field_0x1590[i].pane->show();
        }
        i_Meter->field_0x1670.pane->show();
        i_Meter->field_0x16a8.pane->show();
        i_Meter->field_0x16e0.pane->hide();
        i_Meter->field_0x17f8.pane->hide();
        i_Meter->field_0x1830.pane->hide();
        i_Meter->field_0x1910.pane->hide();
        i_Meter->field_0x1948.pane->hide();
        for (s32 i = 0; i < 3; i++) {
            i_Meter->field_0x1868[i].pane->hide();
        }
        for (s32 i = 0; i < 4; i++) {
            i_Meter->field_0x1718[i].pane->hide();
        }
    } else {
        i_Meter->field_0x1398.pane->hide();
        i_Meter->field_0x13d0.pane->hide();
        i_Meter->field_0x1408.pane->hide();
        i_Meter->field_0x1440.pane->hide();
        for (s32 i = 0; i < 3; i++) {
            i_Meter->field_0x1478[i].pane->hide();
        }
        i_Meter->field_0x1520.pane->hide();
        i_Meter->field_0x1558.pane->hide();
        for (s32 i = 0; i < 4; i++) {
            i_Meter->field_0x1590[i].pane->hide();
        }
        i_Meter->field_0x1670.pane->hide();
        i_Meter->field_0x16a8.pane->hide();
        if ((dComIfGs_getTime() >= 90.0f) && (dComIfGs_getTime() < 270.0f)) {
            i_Meter->field_0x16e0.pane->show();
            i_Meter->field_0x17f8.pane->hide();
            i_Meter->field_0x1830.pane->show();
            i_Meter->field_0x1910.pane->show();
            i_Meter->field_0x1948.pane->show();
            for (s32 i = 0; i < 3; i++) {
                i_Meter->field_0x1868[i].pane->hide();
            }
            for (s32 i = 0; i < 4; i++) {
                i_Meter->field_0x1718[i].pane->hide();
            }
            ((J2DPicture*)i_Meter->field_0x1948.pane)->setCornerColor(0xFFFF00FF, 0xFFFF00FF, 0xFFFF00FF, 0x0000FFFF);
        } else {
            i_Meter->field_0x16e0.pane->show();
            i_Meter->field_0x17f8.pane->show();
            i_Meter->field_0x1830.pane->hide();
            i_Meter->field_0x1910.pane->hide();
            i_Meter->field_0x1948.pane->show();
            for (s32 i = 0; i < 3; i++) {
                i_Meter->field_0x1868[i].pane->hide();
            }
            for (s32 i = 0; i < 4; i++) {
                i_Meter->field_0x1718[i].pane->show();
            }
            ((J2DPicture*)i_Meter->field_0x1948.pane)->setCornerColor(0x0000FFFF, 0x000000FF, 0x000000FF, 0x000000FF);
        }
    }
}

/* 801FE8DC-801FE9A4       .text dMeter_clockHide__FP15sub_meter_class */
void dMeter_clockHide(sub_meter_class* i_Meter) {
    i_Meter->field_0x1398.pane->hide();
    i_Meter->field_0x13d0.pane->hide();
    i_Meter->field_0x1408.pane->hide();
    i_Meter->field_0x1440.pane->hide();
    for (s32 i = 0; i < 3; i++) {
        i_Meter->field_0x1478[i].pane->hide();
        i_Meter->field_0x1868[i].pane->hide();
    }
    i_Meter->field_0x1520.pane->hide();
    i_Meter->field_0x1558.pane->hide();
    for (s32 i = 0; i < 4; i++) {
        i_Meter->field_0x1590[i].pane->hide();
        i_Meter->field_0x1718[i].pane->hide();
    }
    i_Meter->field_0x1670.pane->hide();
    i_Meter->field_0x16a8.pane->hide();
    i_Meter->field_0x16e0.pane->hide();
    i_Meter->field_0x17f8.pane->hide();
    i_Meter->field_0x1830.pane->hide();
    i_Meter->field_0x1910.pane->hide();
    i_Meter->field_0x1948.pane->hide();
}

/* 801FE9A4-801FEA50       .text dMeter_clockInit__FP15sub_meter_class */
void dMeter_clockInit(sub_meter_class* i_Meter) {
    static s16 initPosX[] = {0x0071, 0x0062, 0x009A};
    static s16 initPosY[] = {0x01B3, 0x018C, 0x0194};
    f32 fVar1;
    f32 fVar2;

    fVar1 = i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1830.mPosTopLeftOrig.x;
    fVar2 = i_Meter->field_0x1948.mPosTopLeftOrig.y + i_Meter->field_0x1830.mPosTopLeftOrig.y;
    for (s32 i = 0; i < 3; i++) {
        i_Meter->field_0x1718[i].mUserArea = 1;
        i_Meter->field_0x1478[i].mUserArea = 1;
        i_Meter->field_0x1868[i].mPosCenter.x = fVar1 - initPosX[i];
        i_Meter->field_0x1868[i].mPosCenter.y = fVar2 - initPosY[i];
    }
    i_Meter->field_0x1718[3].mUserArea = 1;
    i_Meter->field_0x1910.mUserArea = 0;
}

/* 801FEA50-801FEC2C       .text dMeter_clockMove__FP15sub_meter_class */
void dMeter_clockMove(sub_meter_class* i_Meter) {
    JUtility::TColor color1;
    JUtility::TColor color2;

    if (i_Meter->field_0x1910.mUserArea <= 0x3c) {
        fopMsgM_valueIncrease(0x3c, i_Meter->field_0x1910.mUserArea, 0);
    } else {
        fopMsgM_valueIncrease(0x3c, 0x78 - i_Meter->field_0x1910.mUserArea, 0);
    }
    if (i_Meter->field_0x1910.mUserArea < 0x78) {
        i_Meter->field_0x1910.mUserArea++;
    } else {
        i_Meter->field_0x1910.mUserArea = 0;
    }
    for (s32 i = 0; i < 3; i++) {
        i_Meter->field_0x1868[i].mPosCenter.x = g_meterHIO.field_0x6c[i];
        i_Meter->field_0x1868[i].mPosCenter.y = g_meterHIO.field_0x72[i];
    }
    if (dComIfGp_roomControl_getTimePass()) {
        if (i_Meter->field_0x1478[0].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fe4);
        }
        if (i_Meter->field_0x1478[1].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fe8);
        }
        if (i_Meter->field_0x1478[2].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fec);
        }
        dMeter_clockStarLight(&i_Meter->field_0x1478[0], &i_Meter->field_0x2fe4);
        dMeter_clockStarLight(&i_Meter->field_0x1478[1], &i_Meter->field_0x2fe8);
        dMeter_clockStarLight(&i_Meter->field_0x1478[2], &i_Meter->field_0x2fec);
    } else {
        if (i_Meter->field_0x1718[0].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fe4);
        }
        if (i_Meter->field_0x1718[1].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fe8);
        }
        if (i_Meter->field_0x1718[2].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2fec);
        }
        if (i_Meter->field_0x1718[3].mUserArea == 1) {
            dMeter_starLightFrame(&i_Meter->field_0x2ff0);
        }
        dMeter_clockStarLight(&i_Meter->field_0x1718[0], &i_Meter->field_0x2fe4);
        dMeter_clockStarLight(&i_Meter->field_0x1718[1], &i_Meter->field_0x2fe8);
        dMeter_clockStarLight(&i_Meter->field_0x1718[2], &i_Meter->field_0x2fec);
        dMeter_clockStarLight(&i_Meter->field_0x1718[3], &i_Meter->field_0x2ff0);
    }
}

/* 801FEC2C-801FED10       .text dMeter_clockStarLight__FP18fopMsgM_pane_classPs */
void dMeter_clockStarLight(fopMsgM_pane_class* param_1, s16* param_2) {
    u8 uVar1;
    f32 dVar4;
    JUtility::TColor black;

    if (param_1->mUserArea < param_2[0]) {
        dVar4 = fopMsgM_valueIncrease(param_2[0], param_1->mUserArea, 0);
    } else {
        dVar4 = fopMsgM_valueIncrease(param_2[1] - param_2[0], param_2[1] - param_1->mUserArea, 0);
    }
    uVar1 = dVar4 * 255.0f;
    black.b = uVar1;
    black.g = uVar1;
    black.r = uVar1;
    black.a = 0x00;
    ((J2DPicture*)param_1->pane)->setBlack(black);
    if (param_1->mUserArea < param_2[1]) {
        param_1->mUserArea++;
    } else {
        param_1->mUserArea = 1;
    }
}

/* 801FED10-801FEE00       .text dMeter_starLightFrame__FPs */
void dMeter_starLightFrame(s16* param_1) {
    param_1[0] = g_meterHIO.field_0x90 + cM_rndFX(g_meterHIO.field_0x9a);
    param_1[1] = (param_1[0] + g_meterHIO.field_0x88) + cM_rndFX(g_meterHIO.field_0x92);
}

/* 801FEE00-801FEF40       .text dMeter_clockMultiInit__FP15sub_meter_class */
void dMeter_clockMultiInit(sub_meter_class* i_Meter) {
    static f32 scaleX[] = {0.813f, 0.75f, 0.5f};
    static f32 scaleY[] = {0.667f, 0.583f, 0.604f};

    JKRArchive* pArchive = dComIfGp_getSwimResArchive();
    ResTIMG* texture1 = (ResTIMG*)JKRArchive::getGlbResource('TIMG', "swimtime_meter_mask.bti", pArchive);
    JKRArchive* pArchive2 = dComIfGp_getMenuArchive();
    ResTIMG* texture2 = (ResTIMG*)JKRArchive::getGlbResource('TIMG', "screw_01.bti", pArchive2);
    JUT_ASSERT(10626, texture1 != NULL && texture2 != NULL);
    for (s32 i = 0; i < 3; i++) {
        clock[i].init(texture1, texture2, 1.0f / scaleX[i], 1.0f / scaleY[i]);
    }
}

/* 801FEF40-801FF184       .text dMeter_clockMultiMove__FP15sub_meter_class */
void dMeter_clockMultiMove(sub_meter_class* i_Meter) {
    /* Nonmatching */
    static f32 scaleX[] = {0.813f, 0.75f, 0.5f};
    static f32 scaleY[] = {0.667f, 0.583f, 0.604f};
    s16 sVar5;
    s16 sVar4;
    s16 fVar2;
    s16 fVar1;

    for (s32 i = 0; i < 3; i++) {
        sVar4 = i_Meter->field_0x1948.mPosTopLeftOrig.x + i_Meter->field_0x1830.mPosTopLeftOrig.x;
        sVar5 = i_Meter->field_0x1948.mPosTopLeftOrig.y + i_Meter->field_0x1830.mPosTopLeftOrig.y;
        fVar1 = i_Meter->field_0x1868[i].mPosCenter.x;
        fVar2 = i_Meter->field_0x1868[i].mPosCenter.y;
        clock[i].setPos(sVar4, sVar5, sVar4 + i_Meter->field_0x1830.mSizeOrig.x, sVar5 + i_Meter->field_0x1830.mSizeOrig.y);
        GXColor color1 = {0xFF, 0XFF, 0XFF, 0XFF};
        clock[i].mC0.r = color1.r;
        clock[i].mC0.g = color1.g;
        clock[i].mC0.b = color1.b;
        clock[i].mC0.a = color1.a;
        GXColor color2 = {0x00, 0x00, 0XFF, 0x00};
        clock[i].mC1.r = color2.r;
        clock[i].mC1.g = color2.g;
        clock[i].mC1.b = color2.b;
        clock[i].mC1.a = color2.a;
        clock[i].setScroll(0, 0, 0);
        clock[i].setScroll(1, fVar1, fVar2);
        clock[i].setScale((100.0f * (1.0f / scaleX[i]) / g_meterHIO.field_0x78[i]), (100.0f * (1.0f / scaleY[i])) / g_meterHIO.field_0x78[i]);
    }
}

/* 801FF184-801FF1F8       .text dMeter_mapInit__FP15sub_meter_class */
void dMeter_mapInit(sub_meter_class* i_Meter) {
    i_Meter->field_0x3027 = 0xFF;
    i_Meter->field_0x0100[0].mUserArea = dComIfGs_isDungeonItemCompass();
    dMeter_mMapCtrlDisp.field_0x0 = 0;
    dMeter_mMapCtrlDisp.field_0x4 = g_meter_mapHIO.field_0xc - g_meter_mapHIO.field_0x8;
    dMeter_mMapCtrlDisp.initMapCtrlDisp();
}

/* 801FF1F8-801FF684       .text dMeter_mapMove__FP15sub_meter_class */
void dMeter_mapMove(sub_meter_class* i_Meter) {
    static s16 mapTimer = 0;
    static u8 stageFlag = false;
    static s32 stayNo = dComIfGp_roomControl_getStayNo();
    if (fopOvlpM_IsDoingReq() == 0) {
        if (i_Meter->field_0x3027 == 0xFF) {
            stageFlag = 1;
        } else {
            if (stayNo != dComIfGp_roomControl_getStayNo()) {
                stageFlag = 2;
                stayNo = dComIfGp_roomControl_getStayNo();
            }
        }
    }
    if ((!(i_Meter->mStatusFlags & dMtrStts_UNK4000_e)) && ((!(i_Meter->mStatusFlags & dMtrStts_UNK40_e)) || (!(dComIfGp_event_checkHind(0x100)))) &&
        (!(i_Meter->mStatusFlags & dMtrStts_UNK200000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK100_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK80_e)) &&
        (!(i_Meter->mStatusFlags & dMtrStts_UNK100000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK8_e)) &&
        (((!(i_Meter->mStatusFlags & dMtrStts_UNK10_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e))) && (dMap_isEnableDispMap())) &&
        ((strcmp(dComIfGp_getNextStageName(), "MajyuE") != 0) || (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0801))))
    {
        if ((i_Meter->mStatusFlags & dMtrStts_UNK400_e) && (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) != dSv_save_c::STAGE_TOTG)) {
            if (((s32)dMeter_mMapCtrlDisp.field_0x0 != 0) && (dMap_isEnableDispMap())) {
                dMeter_mMapCtrlDisp.field_0x0 = 0;
                dMeter_mMapCtrlDisp.field_0x1 = 7;
            }
        } else {
            if (!(CPad_CHECK_TRIG_UP(0)) && !(CPad_CHECK_TRIG_DOWN(0)) && (!(dComIfGp_getMiniGameType() == 1)) &&
                ((CPad_CHECK_TRIG_LEFT(0) != 0) || (CPad_CHECK_TRIG_RIGHT(0))))
            {
                if (CPad_CHECK_TRIG_LEFT(0) != 0) {
                    if ((dMap_c::mAlpha != 0) && ((s32)dMeter_mMapCtrlDisp.field_0x0 != 0)) {
                        if (dMap_isEnableDispMap()) {
                            dMeter_mMapCtrlDisp.field_0x0 = 0;
                            dMeter_mMapCtrlDisp.field_0x1 = 0;
                        }
                        i_Meter->field_0x3029 = 0;
                        mDoAud_seStart(JA_SE_MAP_CANCEL);
                    }
                } else if ((CPad_CHECK_TRIG_RIGHT(0) != 0) && (dMap_c::mAlpha != 0)) {
                    if ((s32)dMeter_mMapCtrlDisp.field_0x0 == 0) {
                        if (dMap_isEnableDispMap()) {
                            dMeter_mMapCtrlDisp.field_0x0 = 1;
                            dMeter_mMapCtrlDisp.field_0x1 = 0;
                        }
                        i_Meter->field_0x3029 = 1;
                        mDoAud_seStart(JA_SE_MAP_SHOW);
                    } else if (i_Meter->field_0x3027 != 0) {
                        i_Meter->field_0x3027 = 0;
                        mDoAud_seStart(JA_SE_MAP_ZOOM);
                    } else {
                        i_Meter->field_0x3027 = 1;
                        mDoAud_seStart(JA_SE_MAP_ZOOM);
                    }
                }
            } else if ((i_Meter->field_0x3029 != 0) && ((i_Meter->field_0x3020 == 1 && ((s32)dMeter_mMapCtrlDisp.field_0x0 == 0)) && (dMap_isEnableDispMap())))
            {
                dMeter_mMapCtrlDisp.field_0x0 = 1;
                dMeter_mMapCtrlDisp.field_0x1 = 7;
            }
            if (stageFlag == 1) {
                stageFlag = 0;
                if ((s32)dMeter_mMapCtrlDisp.field_0x0 == 0) {
                    if (dMap_isEnableDispMap()) {
                        dMeter_mMapCtrlDisp.field_0x0 = 1;
                        dMeter_mMapCtrlDisp.field_0x1 = 0;
                    }
                    i_Meter->field_0x3029 = 1;
                    i_Meter->field_0x3027 = 0;
                }
            } else if (stageFlag == 2) {
                stageFlag = 0;
                i_Meter->field_0x3027 = 0;
            }
            if (i_Meter->field_0x3027 == 0) {
                dMap_c::mMapDispMode = 1;
            } else {
                dMap_c::mMapDispMode = 0;
            }
            if (((s32)dMeter_mMapCtrlDisp.field_0x0 != 0) && (mapTimer != 6)) {
                mapTimer = 6;
            }
        }
    }
    dMeter_mMapCtrlDisp.moveMapCtrlDisp();
    dMeter_recollect_boss_data();
}

/* 801FF684-801FF76C       .text dMeter_arwInit__FP15sub_meter_class */
void dMeter_arwInit(sub_meter_class* i_Meter) {
    u8 bVar2;
    u8 uVar1;

    bVar2 = daArrow_c::getKeepType();
    uVar1 = bVar2;
    if (bVar2 > 3) {
        uVar1 = 0;
    }
    for (s32 i = 0; i < 2; i++) {
        JKRArchive* archive = dComIfGp_getItemIconArchive();
        JKRArchive::readTypeResource(i_Meter->arrowTex[i], 0xc00, 'TIMG', arrowTexImage[uVar1], archive);
        DCStoreRangeNoSync(i_Meter->arrowTex[i], 0xc00);
        ((J2DPicture*)(i_Meter->field_0x2940[i].pane))->changeTexture(i_Meter->arrowTex[i], 0);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2940[i]);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x29b0[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x2940[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x29b0[i]);
        i_Meter->field_0x2f24[i] = 0;
    }
}

/* 801FF76C-801FFEB0       .text dMeter_arwMove__FP15sub_meter_class */
void dMeter_arwMove(sub_meter_class* i_Meter) {
    static const u16 particleName[] = {
        dPa_name::ID_COMMON_02E1,
        dPa_name::ID_COMMON_02E2,
        dPa_name::ID_COMMON_02EF,
    };

    f32 dVar15;
    f32 dVar16;
    cXyz local_6c;
    cXyz local_78;
    JKRArchive* archive;

    static u8 arrowType = daArrow_c::getKeepType();
    static u8 oldType = arrowType;
    dVar16 = (i_Meter->field_0x29b0[0].mPosCenterOrig.x - i_Meter->field_0x29b0[1].mPosCenterOrig.x);
    if (((((dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK4000_e))) &&
          (!(i_Meter->mStatusFlags & dMtrStts_UNK40_e))) &&
         (((!(i_Meter->mStatusFlags & dMtrStts_UNK200000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK80_e))) &&
          ((!(i_Meter->mStatusFlags & dMtrStts_UNK100000_e)) &&
           ((!(i_Meter->mStatusFlags & dMtrStts_UNK20000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK8_e)))))) &&
        ((!(i_Meter->mStatusFlags & dMtrStts_UNK10_e)) &&
         ((((!(i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e))) &&
           (!(i_Meter->mStatusFlags & dMtrStts_UNK100_e))) &&
          (dComIfGp_getMiniGameType() != 8))))
    {
        if (arrowType != daArrow_c::getKeepType()) {
            archive = dComIfGp_getItemIconArchive();
            JKRArchive::readTypeResource(i_Meter->arrowTex[0], 0xc00, 'TIMG', arrowTexImage[arrowType], archive);
            DCStoreRangeNoSync(i_Meter->arrowTex[0], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2940[0].pane)->changeTexture(i_Meter->arrowTex[0], 0);
            oldType = arrowType;
            arrowType = daArrow_c::getKeepType();
            archive = dComIfGp_getItemIconArchive();
            JKRArchive::readTypeResource(i_Meter->arrowTex[1], 0xc00, 'TIMG', arrowTexImage[arrowType], archive);
            DCStoreRangeNoSync(i_Meter->arrowTex[1], 0xc00);
            ((J2DPicture*)i_Meter->field_0x2940[1].pane)->changeTexture(i_Meter->arrowTex[1], 0);
            i_Meter->field_0x29b0[0].mUserArea = 0;
            if (i_Meter->field_0x29b0[1].mUserArea < 2) {
                i_Meter->field_0x29b0[1].mUserArea++;
            }
            for (s32 i = 0; i < 2; i++) {
                if (i_Meter->field_0x2f24[i] != NULL) {
                    i_Meter->field_0x2f24[i]->becomeInvalidEmitter();
                    i_Meter->field_0x2f24[i]->stopDrawParticle();
                    i_Meter->field_0x2f24[i]->quitImmortalEmitter();
                    i_Meter->field_0x2f24[i] = 0;
                }
            }
        }
        if (oldType != 0) {
            if (i_Meter->field_0x2f24[0] == NULL) {
                local_6c.set(i_Meter->field_0x29b0[0].mPosCenter.x - 320.0f, i_Meter->field_0x29b0[0].mPosCenter.y - 240.0f, 0.0f);
                i_Meter->field_0x2f24[0] = dComIfGp_particle_set2Dfore(particleName[oldType * 1 - 1], &local_6c);
            }
        } else {
            if (i_Meter->field_0x2f24[0] != NULL) {
                i_Meter->field_0x2f24[0]->becomeInvalidEmitter();
                i_Meter->field_0x2f24[0]->stopDrawParticle();
                i_Meter->field_0x2f24[0]->quitImmortalEmitter();
                i_Meter->field_0x2f24[0] = NULL;
            }
        }
        if (arrowType != 0) {
            if (i_Meter->field_0x2f24[1] == NULL) {
                local_78.set(i_Meter->field_0x29b0[0].mPosCenter.x - 320.0f, i_Meter->field_0x29b0[1].mPosCenter.y - 240.0f, 0.0f);
                i_Meter->field_0x2f24[1] = dComIfGp_particle_set2Dfore(particleName[arrowType * 1 - 1], &local_78);
            }
        } else {
            if (i_Meter->field_0x2f24[1] != NULL) {
                i_Meter->field_0x2f24[1]->becomeInvalidEmitter();
                i_Meter->field_0x2f24[1]->stopDrawParticle();
                i_Meter->field_0x2f24[1]->quitImmortalEmitter();
                i_Meter->field_0x2f24[1] = NULL;
            }
        }
        if (i_Meter->field_0x29b0[1].mUserArea == 0) {
            i_Meter->field_0x29b0[1].mUserArea = 1;
        }
        if (i_Meter->field_0x29b0[0].mUserArea < 10) {
            i_Meter->field_0x29b0[0].mUserArea++;
            if (i_Meter->field_0x29b0[0].mUserArea == 10) {
                fopMsgM_setNowAlphaZero(&i_Meter->field_0x2940[0]);
                fopMsgM_setNowAlphaZero(&i_Meter->field_0x29b0[0]);
                fopMsgM_setInitAlpha(&i_Meter->field_0x2940[1]);
                fopMsgM_setInitAlpha(&i_Meter->field_0x29b0[1]);
                for (s32 i = 0; i < 2; i++) {
                    fopMsgM_paneTrans(&i_Meter->field_0x2940[i], dVar16, 0.0f);
                    fopMsgM_paneTrans(&i_Meter->field_0x29b0[i], dVar16, 0.0f);
                }
            } else {
                dVar15 = fopMsgM_valueIncrease(10, i_Meter->field_0x29b0[0].mUserArea, 0);
                dVar16 = (f32)(dVar16 * dVar15);
                for (s32 i = 0; i < 2; i++) {
                    fopMsgM_paneTrans(&i_Meter->field_0x2940[i], dVar16, 0.0f);
                    fopMsgM_paneTrans(&i_Meter->field_0x29b0[i], dVar16, 0.0f);
                }
                fopMsgM_setNowAlpha(&i_Meter->field_0x2940[1], dVar15);
                fopMsgM_setNowAlpha(&i_Meter->field_0x29b0[1], dVar15);
                if (i_Meter->field_0x29b0[1].mUserArea == 2) {
                    f32 dVar16_2 = fopMsgM_valueIncrease(10, 10 - i_Meter->field_0x29b0[0].mUserArea, 0);
                    fopMsgM_setNowAlpha(&i_Meter->field_0x2940[0], dVar16_2);
                    fopMsgM_setNowAlpha(&i_Meter->field_0x29b0[0], dVar16_2);
                } else {
                    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2940[0]);
                    fopMsgM_setNowAlphaZero(&i_Meter->field_0x29b0[0]);
                }
            }
        }
        for (s32 i = 0; i < 2; i++) {
            fopMsgM_setAlpha(&i_Meter->field_0x2940[i]);
            fopMsgM_setAlpha(&i_Meter->field_0x29b0[i]);
        }
    } else {
        if (i_Meter->field_0x29b0[1].mUserArea != 0) {
            i_Meter->field_0x29b0[1].mUserArea = 0;
        }
        if (i_Meter->field_0x29b0[0].mUserArea > 0) {
            i_Meter->field_0x29b0[0].mUserArea--;
            if (i_Meter->field_0x29b0[0].mUserArea == 0) {
                for (s32 i = 0; i < 2; i++) {
                    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2940[i]);
                    fopMsgM_setNowAlphaZero(&i_Meter->field_0x29b0[i]);
                    fopMsgM_setAlpha(&i_Meter->field_0x2940[i]);
                    fopMsgM_setAlpha(&i_Meter->field_0x29b0[i]);
                    if (i_Meter->field_0x2f24[i] != NULL) {
                        i_Meter->field_0x2f24[i]->becomeInvalidEmitter();
                        i_Meter->field_0x2f24[i]->stopDrawParticle();
                        i_Meter->field_0x2f24[i]->quitImmortalEmitter();
                        i_Meter->field_0x2f24[i] = NULL;
                    }
                }
            } else {
                dVar16 = fopMsgM_valueIncrease(10, i_Meter->field_0x29b0[0].mUserArea, 0);
                for (s32 i = 0; i < 2; i++) {
                    i_Meter->field_0x2940[i].pane->setAlpha(i_Meter->field_0x2940[i].mNowAlpha * dVar16);
                    i_Meter->field_0x29b0[i].pane->setAlpha(i_Meter->field_0x29b0[i].mNowAlpha * dVar16);
                }
            }
        }
    }
    for (s32 i = 0; i < 2; i++) {
        if (i_Meter->field_0x2f24[i] != NULL) {
            i_Meter->field_0x2f24[i]->playDrawParticle();
            f32 x = i_Meter->field_0x29b0[1].mPosCenter.x - 320.0f;
            f32 y = i_Meter->field_0x29b0[1].mPosCenter.y - 240.0f;
            i_Meter->field_0x2f24[i]->setGlobalTranslation(x, y, 0.0f);
            i_Meter->field_0x2f24[i]->mGlobalPrmColor.a = i_Meter->field_0x2940[i].mNowAlpha;
        }
    }
}

/* 801FFEB0-801FFF30       .text dMeter_moveItemInit__FP15sub_meter_class */
void dMeter_moveItemInit(sub_meter_class* i_Meter) {
    JKRArchive* archive = dComIfGp_getItemIconArchive();
    const char* pFilename = dItem_data::getTexture(0x27);
    JKRArchive::readTypeResource(i_Meter->moveIconTex[0], 0xc00, 'TIMG', pFilename, archive);
    DCStoreRangeNoSync(i_Meter->moveIconTex[0], 0xc00);
    moveItemPane = new J2DPicture(i_Meter->moveIconTex[0]);
}

/* 801FFF30-80200398       .text dMeter_moveItemMove__FP15sub_meter_class */
void dMeter_moveItemMove(sub_meter_class* i_Meter) {
    /* Nonmatching */
    int iVar3;
    f32 dVar4;
    f32 in_f31;
    f32 in_f30;
    const char* pFilename;
    JKRArchive* archive;

    u8 uVar1 = g_menuHIO.field_0xc8;
    if (dMeter_itemTimer == 0) {
        if (dMeter_itemNum >= dInvSlot_ReserveFirst_e) {
            archive = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGs_getItemReserve(dMeter_itemNum - dInvSlot_ReserveFirst_e));
            JKRArchive::readTypeResource(i_Meter->moveIconTex[0], 0xc00, 'TIMG', pFilename, archive);
            DCStoreRangeNoSync(i_Meter->moveIconTex[0], 0xc00);
            moveItemPane->changeTexture(i_Meter->moveIconTex[0], 0);
        } else if (dMeter_itemNum >= dInvSlot_BaitFirst_e) {
            archive = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGs_getItemBait(dMeter_itemNum - dInvSlot_BaitFirst_e));
            JKRArchive::readTypeResource(i_Meter->moveIconTex[0], 0xc00, 'TIMG', pFilename, archive);
            DCStoreRangeNoSync(i_Meter->moveIconTex[0], 0xc00);
            moveItemPane->changeTexture(i_Meter->moveIconTex[0], 0);
        } else if (dMeter_itemNum >= dInvSlot_BeastFirst_e) {
            archive = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(dComIfGs_getItemBeast(dMeter_itemNum - dInvSlot_BeastFirst_e));
            JKRArchive::readTypeResource(i_Meter->moveIconTex[0], 0xc00, 'TIMG', pFilename, archive);
            DCStoreRangeNoSync(i_Meter->moveIconTex[0], 0xc00);
            moveItemPane->changeTexture(i_Meter->moveIconTex[0], 0);
        } else {
            u8 uVar2_2 = dComIfGs_getItem(dMeter_itemNum);
            if ((uVar2_2 == 0x35) || (uVar2_2 == 0x36)) {
                uVar2_2 = 0x27;
            }
            archive = dComIfGp_getItemIconArchive();
            pFilename = dItem_data::getTexture(uVar2_2);
            JKRArchive::readTypeResource(i_Meter->moveIconTex[0], 0xc00, 'TIMG', pFilename, archive);
            DCStoreRangeNoSync(i_Meter->moveIconTex[0], 0xc00);
            moveItemPane->changeTexture(i_Meter->moveIconTex[0], 0);
        }
    }
    if (dMeter_btn_chk == 0) {
        in_f31 = (i_Meter->field_0x2080[0].mPosCenter.x - item_parts.mPosCenterOrig.x);
        in_f30 = (i_Meter->field_0x2080[0].mPosCenter.y - item_parts.mPosCenterOrig.y);
    } else if (dMeter_btn_chk == 1) {
        in_f31 = (i_Meter->field_0x2080[1].mPosCenter.x - item_parts.mPosCenterOrig.x);
        in_f30 = (i_Meter->field_0x2080[1].mPosCenter.y - item_parts.mPosCenterOrig.y);
    } else if (dMeter_btn_chk == 2) {
        in_f31 = (i_Meter->field_0x2080[2].mPosCenter.x - item_parts.mPosCenterOrig.x);
        in_f30 = (i_Meter->field_0x2080[2].mPosCenter.y - item_parts.mPosCenterOrig.y);
    }
    dMeter_itemTimer++;
    iVar3 = (s16)uVar1;
    if (dMeter_itemTimer <= (s16)iVar3) {
        dVar4 = fopMsgM_valueIncrease(iVar3, (s16)dMeter_itemTimer, 2);
        item_parts.mPosCenter.x = item_parts.mPosCenterOrig.x + (in_f31 * dVar4);
        item_parts.mPosCenter.y = item_parts.mPosCenterOrig.y + (in_f30 * dVar4);
        f32 temp_f3 = item_parts.mSizeOrig.x * g_menuHIO.field_0x8;
        f32 temp_f3_2 = temp_f3 - i_Meter->field_0x2080[0].mSizeOrig.x;
        f32 temp_f2 = item_parts.mSizeOrig.y * g_menuHIO.field_0x8;
        f32 temp_f2_2 = temp_f2 - i_Meter->field_0x2080[0].mSizeOrig.y;
        switch (g_menuHIO.field_0xc9) {
        case 1:
            item_parts.mSize.x = temp_f3;
            item_parts.mSize.y = temp_f2;
            break;
        case 2:
            item_parts.mSize.x = temp_f3 - (temp_f3_2 * dVar4);
            item_parts.mSize.y = temp_f2 - (temp_f2_2 * dVar4);
            break;
        default:
            item_parts.mSize.x = item_parts.mSizeOrig.x;
            item_parts.mSize.y = item_parts.mSizeOrig.y;
            break;
        }
        f32 tmp = 0.5f;
        item_parts.mPosTopLeft.x = item_parts.mPosCenter.x - item_parts.mSize.x * tmp;
        item_parts.mPosTopLeft.y = item_parts.mPosCenter.y - item_parts.mSize.y * tmp;
        if (dMeter_itemTimer == iVar3 + -1) {
            dMeter_itemMoveFlag = 2;
        }
    }
}

/* 80200398-8020042C       .text dMeter_moveItemDraw__FP15sub_meter_class */
void dMeter_moveItemDraw(sub_meter_class* i_Meter) {
    s16 uVar1 = g_menuHIO.field_0xc8;
    if (((dMeter_itemMoveFlagCheck()) && (dMeter_itemTimer != 0)) && (moveItemPane != NULL)) {
        moveItemPane->draw(item_parts.mPosTopLeft.x, item_parts.mPosTopLeft.y, item_parts.mSize.x, item_parts.mSize.y, false, false, false);
        if (dMeter_itemTimer >= uVar1) {
            dMeter_itemMoveFlag = 0;
        }
    }
}

/* 8020042C-8020054C       .text dMeter_swimTransY__FP15sub_meter_classf */
void dMeter_swimTransY(sub_meter_class* i_Meter, f32 param_2) {
    f32 fVar1 = 0.5f;
    for (s32 i = 0; i < 9; i++) {
        i_Meter->field_0x2a90[i].mPosCenterOrig.y = param_2 + (i_Meter->field_0x2a90[i].mPosTopLeftOrig.y + i_Meter->field_0x2a90[i].mSizeOrig.y * fVar1);
    }
    i_Meter->field_0x2c88.mPosCenterOrig.y = param_2 + (i_Meter->field_0x2c88.mPosTopLeftOrig.y + i_Meter->field_0x2c88.mSizeOrig.y * fVar1);
    fopMsgM_paneTrans(&i_Meter->field_0x2c88, 0.0f, 0.0f);
    i_Meter->field_0x2cc0.mPosCenterOrig.y = param_2 + (i_Meter->field_0x2cc0.mPosTopLeftOrig.y + i_Meter->field_0x2cc0.mSizeOrig.y * fVar1);
    fopMsgM_paneTrans(&i_Meter->field_0x2cc0, 0.0f, 0.0f);
    i_Meter->field_0x2d30.mPosCenterOrig.y = param_2 + (i_Meter->field_0x2d30.mPosTopLeftOrig.y + i_Meter->field_0x2d30.mSizeOrig.y * fVar1);
    fopMsgM_paneTrans(&i_Meter->field_0x2d30, 0.0f, 0.0f);
    i_Meter->field_0x2dd8.mPosCenterOrig.y = param_2 + (i_Meter->field_0x2dd8.mPosTopLeftOrig.y + i_Meter->field_0x2dd8.mSizeOrig.y * fVar1);
    fopMsgM_paneTrans(&i_Meter->field_0x2dd8, 0.0f, 0.0f);
}

/* 8020054C-8020059C       .text dMeter_swimPaneShow__FP15sub_meter_class */
void dMeter_swimPaneShow(sub_meter_class* i_Meter) {
    fopMsgM_setInitAlpha(&i_Meter->field_0x2cf8);
    fopMsgM_setInitAlpha(&i_Meter->field_0x2da0);
    fopMsgM_setInitAlpha(&i_Meter->field_0x2d30);
    fopMsgM_setInitAlpha(&i_Meter->field_0x2c88);
    fopMsgM_setInitAlpha(&i_Meter->field_0x2dd8);
}

/* 8020059C-80200630       .text dMeter_swimPaneHide__FP15sub_meter_class */
void dMeter_swimPaneHide(sub_meter_class* i_Meter) {
    for (s32 i = 0; i < 9; i++) {
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2a90[i]);
    }
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2c88);
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2cc0);
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2cf8);
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2d30);
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2da0);
    fopMsgM_setNowAlphaZero(&i_Meter->field_0x2dd8);
    tekari.mC0.a = 0;
}

/* 80200630-802006AC       .text dMeter_swimPaneTransY__FP15sub_meter_classf */
void dMeter_swimPaneTransY(sub_meter_class* i_Meter, f32 param_2) {
    fopMsgM_paneTrans(&i_Meter->field_0x2d30, 0.0f, param_2);
    fopMsgM_paneTrans(&i_Meter->field_0x2c88, 0.0f, param_2);
    fopMsgM_paneTrans(&i_Meter->field_0x2cf8, 0.0f, 0.0f);
    fopMsgM_paneTrans(&i_Meter->field_0x2da0, 0.0f, 0.0f);
}

/* 802006AC-8020070C       .text dMeter_swimPaneAlpha__FP15sub_meter_classf */
void dMeter_swimPaneAlpha(sub_meter_class* i_Meter, f32 param_2) {
    fopMsgM_setNowAlpha(&i_Meter->field_0x2cf8, param_2);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2da0, param_2);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2d30, param_2);
    fopMsgM_setNowAlpha(&i_Meter->field_0x2c88, param_2);
}

/* 8020070C-802008F4       .text dMeter_swimInit__FP15sub_meter_class */
void dMeter_swimInit(sub_meter_class* i_Meter) {
    ResTIMG* texture1;
    ResTIMG* texture2;

    dMeter_screenDataTimeSet(i_Meter);
    dMeter_swimPaneHide(i_Meter);
    if (!dStage_stagInfo_ChkKeyDisp(dComIfGp_getStageStagInfo())) {
        dMeter_swimTransY(i_Meter, g_meterHIO.field_0x13a + 32.0f);
    }
    JUtility::TColor black = ((J2DPicture*)i_Meter->field_0x2c88.pane)->getBlack();
    i_Meter->field_0x2ef0 = black;
    JUtility::TColor white = ((J2DPicture*)i_Meter->field_0x2c88.pane)->getWhite();
    i_Meter->field_0x2ef4 = white;
    JUtility::TColor black2 = ((J2DPicture*)i_Meter->field_0x2da0.pane)->getBlack();
    i_Meter->field_0x2f00 = black2;
    i_Meter->field_0x2da0.mUserArea = 0;
    i_Meter->field_0x2c88.mUserArea = 0;
    i_Meter->field_0x2dd8.mUserArea = 0;
    JKRArchive* pArchive = dComIfGp_getSwimResArchive();
    texture1 = (ResTIMG*)JKRArchive::getGlbResource('TIMG', "swimtime_meter_mask.bti", pArchive);
    JKRArchive* pArchive2 = dComIfGp_getSwimResArchive();
    texture2 = (ResTIMG*)JKRArchive::getGlbResource('TIMG', "tekari.bti", pArchive2);
    JUT_ASSERT(11498, texture1 != NULL && texture2 != NULL);
    tekari.init(texture1, texture2, 1.0f, 1.0f);
}

/* 802008F4-80200D7C       .text dMeter_swimMove__FP15sub_meter_class */
void dMeter_swimMove(sub_meter_class* i_Meter) {
    if (dComIfGp_getItemTimeCount() >= (dComIfGp_getItemTimeMax() / 2)) {
        i_Meter->field_0x2f04.r = 200;
        i_Meter->field_0x2f04.g = 200;
        i_Meter->field_0x2f04.b = 0xff;
        i_Meter->field_0x2ef8 = i_Meter->field_0x2ef0;
        i_Meter->field_0x2efc = i_Meter->field_0x2ef4;
        i_Meter->field_0x3000 = g_meterHIO.field_0x130;
    }
    if (i_Meter->field_0x2da0.mUserArea == 0) {
        if (dComIfGp_getItemTimeCount() != 0) {
            if ((sScrTimer1 == NULL) && (sScrTimer2 == NULL)) {
                dMeter_swimInit(i_Meter);
            }
            i_Meter->field_0x2da0.mUserArea = 1;
            i_Meter->field_0x3010 = 0;
            i_Meter->field_0x2c88.mUserArea = 0;
            i_Meter->field_0x2dd8.mUserArea = 0;
            i_Meter->field_0x2cf8.mUserArea = 0;
            i_Meter->field_0x2d30.mUserArea = (s16)dComIfGp_getItemTimeCount();
            dMeter_xyRotateZ(&i_Meter->field_0x2cf8, 0, 0);
            ((J2DPicture*)i_Meter->field_0x2c88.pane)->setBlack(i_Meter->field_0x2ef0);
            ((J2DPicture*)i_Meter->field_0x2c88.pane)->setWhite(i_Meter->field_0x2ef4);
            ((J2DPicture*)i_Meter->field_0x2cf8.pane)->setBlack(i_Meter->field_0x2f00);
            ((J2DPicture*)i_Meter->field_0x2da0.pane)->setBlack(i_Meter->field_0x2f00);
            i_Meter->field_0x2fc4 = 0;
            i_Meter->field_0x2f04.r = 200;
            i_Meter->field_0x2f04.g = 200;
            i_Meter->field_0x2f04.b = 0xff;
            i_Meter->field_0x2ef8 = i_Meter->field_0x2ef0;
            i_Meter->field_0x2efc = i_Meter->field_0x2ef4;
            i_Meter->field_0x3000 = g_meterHIO.field_0x130;
            for (s32 i = 0; i < 9; i++) {
                i_Meter->field_0x2a90[i].mUserArea = 0;
            }
            mDoAud_seStart(JA_SE_SWIM_TIMER_ON);
        }
    } else if (i_Meter->field_0x2da0.mUserArea == 1) {
        if (dComIfGp_getItemTimeCount() != 0) {
            if (((!dMenu_flag()) && (!dComIfGp_event_runCheck())) && (dComIfGp_getItemSwimTimerStatus() != false)) {
                dMeter_swimOpenProc(i_Meter);
            } else {
                dMeter_swimPaneHide(i_Meter);
            }
        } else {
            dMeter_swimPaneHide(i_Meter);
            i_Meter->field_0x2da0.mUserArea = 0;
            if ((sScrTimer1 != NULL) && (sScrTimer2 != NULL)) {
                dComIfGp_getSwimResArchive()->removeResourceAll();
                delete sScrTimer1;
                delete sScrTimer2;
                sScrTimer1 = NULL;
                sScrTimer2 = NULL;
            }
        }
    } else if (i_Meter->field_0x2da0.mUserArea == 2) {
        if (dComIfGp_getItemTimeCount() != 0) {
            if (((!dMenu_flag()) && (!dComIfGp_event_runCheck())) && (dComIfGp_getItemSwimTimerStatus() != false)) {
                dMeter_swimMoveProc(i_Meter);
            } else {
                dMeter_swimPaneHide(i_Meter);
            }
        } else {
            dMeter_swimPaneHide(i_Meter);
            i_Meter->field_0x2da0.mUserArea = 0;
            if ((sScrTimer1 != NULL) && (sScrTimer2 != NULL)) {
                dComIfGp_getSwimResArchive()->removeResourceAll();
                delete sScrTimer1;
                delete sScrTimer2;
                sScrTimer1 = NULL;
                sScrTimer2 = NULL;
            }
        }
    } else if (i_Meter->field_0x2da0.mUserArea == 3) {
        if (!dMenu_flag()) {
            dMeter_swimMoveProc(i_Meter);
        } else {
            dMeter_swimPaneHide(i_Meter);
        }
    }
}

/* 80200D7C-80200E18       .text dMeter_swimDraw__FP15sub_meter_class */
void dMeter_swimDraw(sub_meter_class* i_Meter) {
    if (sScrTimer2 != NULL) {
        for (s32 i = 0; i < 9; i++) {
            fopMsgM_setAlpha(&i_Meter->field_0x2a90[i]);
        }
        fopMsgM_setAlpha(&i_Meter->field_0x2c88);
        fopMsgM_setAlpha(&i_Meter->field_0x2cc0);
    }
    if (sScrTimer1 != NULL) {
        fopMsgM_setAlpha(&i_Meter->field_0x2cf8);
        fopMsgM_setAlpha(&i_Meter->field_0x2da0);
        fopMsgM_setAlpha(&i_Meter->field_0x2d30);
        fopMsgM_setAlpha(&i_Meter->field_0x2dd8);
    }
}

/* 80200E18-802011D0       .text dMeter_swimOpenProc__FP15sub_meter_class */
void dMeter_swimOpenProc(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 sVar1;
    f32 dVar3;

    sVar1 = i_Meter->field_0x2c88.mUserArea + 1;
    i_Meter->field_0x2c88.mUserArea = sVar1;
    static f32 dist_buf = 0.0f;
    if (sVar1 == 1) {
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, 0.1f);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2dd8);
    } else if (sVar1 < 5) {
        dVar3 = fopMsgM_valueIncrease(4, sVar1 - 1, 0);
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, (dVar3 * 0.9f) + 0.1f);
        fopMsgM_setNowAlpha(&i_Meter->field_0x2dd8, dVar3);
    } else if (sVar1 < 8) {
        dVar3 = fopMsgM_valueIncrease(3, sVar1 - 5, 0);
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, 1.0f - (dVar3 * 0.3f));
    } else if (sVar1 < 10) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 8, 0);
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, (dVar3 * 0.3f) + 0.7f);
    } else if (sVar1 < 0xc) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 10, 0);
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, 1.0f - (dVar3 * 0.100000024f));
    } else if (sVar1 < 0xe) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 0xc, 0);
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, (dVar3 * 0.100000024f) + 0.9f);
    } else if (sVar1 == 0xe) {
        fopMsgM_paneScaleXY(&i_Meter->field_0x2dd8, 1.0f);
    }
    if (sVar1 == 1) {
        dMeter_swimPaneTransY(i_Meter, -130.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2cf8, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2da0, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2d30, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2c88, 1.0f);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2cf8);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2da0);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2d30);
        fopMsgM_setNowAlphaZero(&i_Meter->field_0x2c88);
    } else if (sVar1 <= 5) {
        dVar3 = fopMsgM_valueIncrease(4, sVar1 - 1, 0);
        dMeter_swimPaneTransY(i_Meter, -((1.0f - dVar3) * 130.0f));
        dMeter_swimPaneAlpha(i_Meter, dVar3);
    } else if (sVar1 <= 8) {
        dVar3 = fopMsgM_valueIncrease(3, sVar1 - 5, 0);
        dMeter_swimPaneTransY(i_Meter, (-25.0f - (1.0f - dVar3) * -25.0f));
        dMeter_swimPaneShow(i_Meter);
    } else if (sVar1 <= 0xa) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 8, 0);
        dMeter_swimPaneTransY(i_Meter, -((1.0f - dVar3) * 25.0f));
        dMeter_swimPaneShow(i_Meter);
    } else if (sVar1 <= 0xc) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 10, 0);
        dMeter_swimPaneTransY(i_Meter, (-6.0f - (1.0f - dVar3) * -6.0f));
        dMeter_swimPaneShow(i_Meter);
    } else if (sVar1 < 0xe) {
        dVar3 = fopMsgM_valueIncrease(2, sVar1 - 0xc, 0);
        dMeter_swimPaneTransY(i_Meter, -((1.0f - dVar3) * 6.0f));
        dMeter_swimPaneShow(i_Meter);
    } else if (sVar1 == 0xe) {
        dMeter_swimPaneTransY(i_Meter, 0);
        fopMsgM_paneScaleY(&i_Meter->field_0x2cf8, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2da0, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2d30, 1.0f);
        fopMsgM_paneScaleY(&i_Meter->field_0x2c88, 1.0f);
        dMeter_swimPaneShow(i_Meter);
        i_Meter->field_0x2c88.mUserArea = 0;
        i_Meter->field_0x2da0.mUserArea = 2;
    }
}

/* 802011D0-80201224       .text dMeter_swimMoveProc__FP15sub_meter_class */
void dMeter_swimMoveProc(sub_meter_class* i_Meter) {
    dMeter_swimMainRotate(i_Meter);
    dMeter_swimMainBlink(i_Meter);
    dMeter_swimMainDown(i_Meter);
    dMeter_swimTekariScroll(i_Meter);
    dMeter_swimLightMove(i_Meter);
    dMeter_swimPaneShow(i_Meter);
}

/* 80201224-802012CC       .text dMeter_swimMainRotate__FP15sub_meter_class */
void dMeter_swimMainRotate(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 sVar1;
    s16 sVar2;
    int iVar4;
    f32 in_f1;

    sVar1 = g_meterHIO.field_0x132;
    iVar4 = g_meterHIO.field_0x132;
    sVar2 = i_Meter->field_0x2c88.mUserArea + 1;
    i_Meter->field_0x2c88.mUserArea = sVar2;
    if ((int)sVar2 < iVar4) {
        in_f1 = ((sVar2 * 360.0f) / sVar1);
    } else if (sVar2 == (int)sVar1) {
        i_Meter->field_0x2c88.mUserArea = 0;
        in_f1 = 0.0f;
    }
    dMeter_xyRotateZ(&i_Meter->field_0x2cf8, in_f1, 0.0f);
}

/* 802012CC-80201C08       .text dMeter_swimMainBlink__FP15sub_meter_class */
void dMeter_swimMainBlink(sub_meter_class* i_Meter) {
    /* Nonmatching */
    f32 fVar2;
    s32 uVar5;
    int iVar6;
    s16 uVar7;
    f32 dVar8;

    JUtility::TColor local_100 = i_Meter->field_0x2f00;
    JUtility::TColor local_104 = i_Meter->field_0x2ef0;
    JUtility::TColor local_108 = i_Meter->field_0x2ef4;
    uVar7 = i_Meter->field_0x2dd8.mUserArea + 1;
    i_Meter->field_0x2dd8.mUserArea = uVar7;
    uVar5 = i_Meter->field_0x3000;
    if ((int)uVar7 < (int)uVar5) {
        fVar2 = ((f32)uVar7 / (f32)(uVar5));
        local_100.r = (75.0f + (fVar2 * (f32)(i_Meter->field_0x2f04.r - 0x4B)));
        local_100.g = (75.0f + (fVar2 * (f32)(i_Meter->field_0x2f04.g - 0x4B)));
        local_100.b = (255.0f + (fVar2 * (f32)(i_Meter->field_0x2f04.b - 0xFF)));
        local_104.r = (i_Meter->field_0x2ef0.r + fVar2 * (i_Meter->field_0x2ef8.r - i_Meter->field_0x2ef0.r));
        local_104.g = (i_Meter->field_0x2ef0.g + fVar2 * (i_Meter->field_0x2ef8.g - i_Meter->field_0x2ef0.g));
        local_104.b = (i_Meter->field_0x2ef0.b + fVar2 * (i_Meter->field_0x2ef8.b - i_Meter->field_0x2ef0.b));
        local_108.r = (i_Meter->field_0x2ef4.r + fVar2 * (i_Meter->field_0x2efc.r - i_Meter->field_0x2ef4.r));
        local_108.g = (i_Meter->field_0x2ef4.g + fVar2 * (i_Meter->field_0x2efc.g - i_Meter->field_0x2ef4.g));
        local_108.b = ((i_Meter->field_0x2ef4.b) + fVar2 * (i_Meter->field_0x2efc.b - i_Meter->field_0x2ef4.b));
    } else {
        if ((int)uVar7 < (s16)(uVar5 * 2)) {
            fVar2 = ((f32)(uVar7 - (f32)(uVar5)) / (f32)(uVar5));
            local_100.r = (i_Meter->field_0x2f04.r + fVar2 * (0x4b - i_Meter->field_0x2f04.r));
            local_100.g = (i_Meter->field_0x2f04.g + fVar2 * (0x4b - i_Meter->field_0x2f04.g));
            local_100.b = (i_Meter->field_0x2f04.b + fVar2 * (0xff - i_Meter->field_0x2f04.b));
            local_104.r = (i_Meter->field_0x2ef8.r + fVar2 * (i_Meter->field_0x2ef0.r - i_Meter->field_0x2ef8.r));
            local_104.g = (i_Meter->field_0x2ef8.g + fVar2 * (i_Meter->field_0x2ef0.g - i_Meter->field_0x2ef8.g));
            local_104.b = (i_Meter->field_0x2ef8.b + fVar2 * (i_Meter->field_0x2ef0.b - i_Meter->field_0x2ef8.b));
            local_108.r = ((i_Meter->field_0x2efc.r) + fVar2 * (i_Meter->field_0x2ef4.r - i_Meter->field_0x2efc.r));
            local_108.g = ((i_Meter->field_0x2efc.g) + fVar2 * (i_Meter->field_0x2ef4.g - i_Meter->field_0x2efc.g));
            local_108.b = (i_Meter->field_0x2efc.b + fVar2 * (i_Meter->field_0x2ef4.b - i_Meter->field_0x2efc.b));
        } else if ((int)uVar7 >= (s16)(uVar5 * 2)) {
            i_Meter->field_0x2dd8.mUserArea = 0;
            local_100.r = 0x4b;
            local_100.g = 0x4b;
            local_100.b = 0xff;
            local_104 = i_Meter->field_0x2ef0;
            local_108 = i_Meter->field_0x2ef4;
            if (dComIfGp_getItemTimeCount() <= 0) {
                i_Meter->field_0x3000 = 0;
            } else {
                iVar6 = dComIfGp_getItemTimeMax() / 2;
                if (dComIfGp_getItemTimeCount() < iVar6) {
                    dVar8 = fopMsgM_valueIncrease(iVar6, iVar6 - dComIfGp_getItemTimeCount(), 1);
                    i_Meter->field_0x3000 = (s16)(g_meterHIO.field_0x130 + (dVar8 * (g_meterHIO.field_0x134 - g_meterHIO.field_0x130)));
                    i_Meter->field_0x2f04.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2f04.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2f04.b = g_meterHIO.field_0x14c;
                    i_Meter->field_0x2ef8.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2ef8.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2ef8.b = g_meterHIO.field_0x14c;
                    i_Meter->field_0x2efc.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2efc.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2efc.b = g_meterHIO.field_0x14c;
                    if (i_Meter->field_0x2cf8.mUserArea <= 0) {
                        i_Meter->field_0x2cf8.mUserArea = 2;
                        if (!dComIfGp_event_runCheck()) {
                            mDoAud_seStart(JA_SE_SWIM_TIMER_BLINLK);
                        }
                    } else {
                        i_Meter->field_0x2cf8.mUserArea--;
                    }
                } else if (dComIfGp_getItemTimeCount() < 0) {
                    i_Meter->field_0x3000 = g_meterHIO.field_0x134;
                    i_Meter->field_0x2f04.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2f04.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2f04.b = g_meterHIO.field_0x14c;
                    i_Meter->field_0x2ef8.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2ef8.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2ef8.b = g_meterHIO.field_0x14c;
                    i_Meter->field_0x2efc.r = g_meterHIO.field_0x14a;
                    i_Meter->field_0x2efc.g = g_meterHIO.field_0x14b;
                    i_Meter->field_0x2efc.b = g_meterHIO.field_0x14c;
                }
            }
        }
    }
    if (i_Meter->field_0x3000 != 0) {
        ((J2DPicture*)i_Meter->field_0x2c88.pane)->setBlack(local_104);
        ((J2DPicture*)i_Meter->field_0x2c88.pane)->setWhite(local_108);
        ((J2DPicture*)i_Meter->field_0x2cf8.pane)->setBlack(local_100);
        ((J2DPicture*)i_Meter->field_0x2da0.pane)->setBlack(local_100);
    } else {
        ((J2DPicture*)i_Meter->field_0x2c88.pane)->setBlack(i_Meter->field_0x2ef8);
        ((J2DPicture*)i_Meter->field_0x2c88.pane)->setWhite(i_Meter->field_0x2efc);
        ((J2DPicture*)i_Meter->field_0x2cf8.pane)->setBlack(i_Meter->field_0x2f04);
        ((J2DPicture*)i_Meter->field_0x2da0.pane)->setBlack(i_Meter->field_0x2f04);
    }
}

/* 80201C08-80201D2C       .text dMeter_swimMainDown__FP15sub_meter_class */
void dMeter_swimMainDown(sub_meter_class* i_Meter) {
    s16 sVar1;

    sVar1 = (s16)dComIfGp_getItemTimeCount();
    dMeter_paneBottomScaleY(&i_Meter->field_0x2d30, ((f32)(sVar1) / (f32)(i_Meter->field_0x2d30.mUserArea)));
    f32 fVar1 = 0.5f;
    i_Meter->field_0x2da0.mPosTopLeft.y =
        (i_Meter->field_0x2d30.mPosCenterOrig.y - i_Meter->field_0x2d30.mSizeOrig.y * fVar1) - i_Meter->field_0x2d30.mPosTopLeft.y;
    i_Meter->field_0x2da0.mPosCenter.y = i_Meter->field_0x2da0.mPosTopLeft.y + i_Meter->field_0x2da0.mSize.y * fVar1;
    fopMsgM_cposMove(&i_Meter->field_0x2da0);
    i_Meter->field_0x2cf8.mPosCenter.y = i_Meter->field_0x2da0.mPosCenter.y;
    fopMsgM_cposMove(&i_Meter->field_0x2cf8);
    if (sVar1 > 0) {
        if ((!dComIfGp_event_runCheck()) && (dComIfGp_getItemSwimTimerStatus() != false)) {
            g_dComIfG_gameInfo.play.mAirMeter--;
        }
        if (dComIfGp_getItemTimeCount() == 0) {
            i_Meter->field_0x2da0.mUserArea = 3;
            dComIfGp_stopItemSwimTimer();
        }
    }
}

/* 80201D2C-80201FC0       .text dMeter_swimTekariScroll__FP15sub_meter_class */
void dMeter_swimTekariScroll(sub_meter_class* i_Meter) {
    /* Nonmatching */
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r0_3;
    s16 temp_r0_4;
    s16 temp_r0_5;
    s16 temp_r26;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 var_r30;
    s16 temp_r4;
    f32 dVar12;

    temp_r0 = g_meterHIO.field_0x14e + g_meterHIO.field_0x150;
    temp_r0_2 = temp_r0 + g_meterHIO.field_0x14e;
    temp_r0_3 = temp_r0_2 + g_meterHIO.field_0x152;
    temp_r0_4 = temp_r0_3 + g_meterHIO.field_0x14e;
    temp_r0_5 = temp_r0_4 + g_meterHIO.field_0x154;
    f32 tmp = 0.5f;
    temp_r29 = (REG6_F(0) + (i_Meter->field_0x2c88.mPosCenterOrig.x - i_Meter->field_0x2c88.mSizeOrig.x * tmp));
    temp_r28 = (REG6_F(1) + (i_Meter->field_0x2c88.mPosCenterOrig.y - i_Meter->field_0x2c88.mSizeOrig.y * tmp));
    temp_r27 = (REG6_F(0) + (i_Meter->field_0x2c88.mPosCenterOrig.x + i_Meter->field_0x2c88.mSizeOrig.x * tmp));
    temp_r26 = (REG6_F(1) + (i_Meter->field_0x2c88.mPosCenterOrig.y + i_Meter->field_0x2c88.mSizeOrig.y * tmp));
    temp_r4 = i_Meter->field_0x2fc4;
    if (temp_r4 < g_meterHIO.field_0x14e) {
        dVar12 = fopMsgM_valueIncrease(g_meterHIO.field_0x14e, temp_r4, 0);
        var_r30 = (0.5f + (28.0f - (64.0f * dVar12)));
    } else if (temp_r4 < temp_r0) {
        var_r30 = -0x24;
    } else if (temp_r4 < temp_r0_2) {
        dVar12 = fopMsgM_valueIncrease(g_meterHIO.field_0x14e, temp_r4 - temp_r0, 0);
        var_r30 = (0.5f + (28.0f - (64.0f * dVar12)));
    } else if (temp_r4 < temp_r0_3) {
        var_r30 = -0x24;
    } else if (temp_r4 < temp_r0_4) {
        dVar12 = fopMsgM_valueIncrease(g_meterHIO.field_0x14e, temp_r4 - temp_r0_3, 0);
        var_r30 = (0.5f + (28.0f - (64.0f * dVar12)));
    } else if (temp_r4 < temp_r0_5) {
        var_r30 = -0x24;
    }
    i_Meter->field_0x2fc4 += 1;
    if (i_Meter->field_0x2fc4 >= temp_r0_5) {
        i_Meter->field_0x2fc4 = 0;
    }
    tekari.setPos(temp_r29, temp_r28, temp_r27, temp_r26);
    GXColor color1 = {0xFF, 0xFF, 0xFF, 0XFF};
    tekari.mC0.r = color1.r;
    tekari.mC0.g = color1.g;
    tekari.mC0.b = color1.b;
    tekari.mC0.a = color1.a;
    GXColor color2 = {0xFF, 0xFF, 0xFF, 0X00};
    tekari.mC1.r = color2.r;
    tekari.mC1.g = color2.g;
    tekari.mC1.b = color2.b;
    tekari.mC1.a = color2.a;
    tekari.setScroll(0, 0, 0);
    tekari.mC0.a = 0xFF;
    tekari.setScroll(1, var_r30, var_r30);
}

/* 80201FC0-8020205C       .text dMeter_swimLightMove__FP15sub_meter_class */
void dMeter_swimLightMove(sub_meter_class* i_Meter) {
    if (dComIfGp_getItemTimeCount() != 0) {
        if (i_Meter->field_0x3010 == 0) {
            dMeter_swimLightBirth(i_Meter);
        } else {
            i_Meter->field_0x3010--;
        }
    }
    for (s16 i = 0; i < 9; i++) {
        if (i_Meter->field_0x2a90[i].mUserArea != 0) {
            dMeter_swimLightAnime(i_Meter, i);
        }
    }
}

/* 8020205C-802021B4       .text dMeter_swimLightBirth__FP15sub_meter_class */
void dMeter_swimLightBirth(sub_meter_class* i_Meter) {
    s16 sVar1;
    s16 iVar3;

    sVar1 = 0;
    for (s16 i = 0; i < 9; i++) {
        if (i_Meter->field_0x2a90[i].mUserArea == 0) {
            sVar1++;
        }
    }
    iVar3 = cM_rndF(sVar1);
    i_Meter->field_0x2f74[iVar3] = (cM_rndF(3.0f) + 5.0f);
    i_Meter->field_0x2f98[iVar3] = cM_rndFX(5.0f);
    i_Meter->field_0x2a90[iVar3].mUserArea = 1;
    i_Meter->field_0x2a90[iVar3].mPosCenter.y = (i_Meter->field_0x2d30).mPosTopLeft.y + g_meterHIO.field_0x13c;
    fopMsgM_cposMove(&i_Meter->field_0x2a90[iVar3]);
    i_Meter->field_0x3010 = cM_rndF((f32)g_meterHIO.field_0x138);
}

/* 802021B4-8020238C       .text dMeter_swimLightAnime__FP15sub_meter_classs */
void dMeter_swimLightAnime(sub_meter_class* i_Meter, s16 param_2) {
    /* Nonmatching */
    s16 sVar1;
    s16 sVar2;
    s16 iVar3;
    fopMsgM_pane_class* pane2;
    int iVar4;
    int iVar5;
    f32 dVar6;
    s16 iVar7;

    sVar2 = g_meterHIO.field_0x136;
    iVar5 = g_meterHIO.field_0x136;
    iVar4 = (int)(s16)(g_meterHIO.field_0x136 + g_meterHIO.field_0x138);
    sVar1 = i_Meter->field_0x2a90[param_2].mUserArea;
    dVar6 = sin((f32)((int)sVar1 * 0.5235988f));
    i_Meter->field_0x2a90[param_2].mPosCenter.x = i_Meter->field_0x2a90[param_2].mPosCenterOrig.x + i_Meter->field_0x2f98[param_2] * dVar6;
    i_Meter->field_0x2a90[param_2].mPosCenter.y = i_Meter->field_0x2a90[param_2].mPosCenter.y - i_Meter->field_0x2f74[param_2];
    i_Meter->field_0x2a90[param_2].mSize.x = g_meterHIO.field_0x7e;
    i_Meter->field_0x2a90[param_2].mSize.y = g_meterHIO.field_0x7e;
    pane2 = &i_Meter->field_0x2a90[param_2];
    fopMsgM_cposMove(pane2);
    i_Meter->field_0x2f74[param_2] = i_Meter->field_0x2f74[param_2] * (cM_rndF(0.2f) + 0.8f);
    i_Meter->field_0x2f98[param_2] = i_Meter->field_0x2f98[param_2] * (cM_rndF(0.1f) + 0.9f);
    iVar3 = (int)sVar1;
    iVar7 = (int)sVar2;
    if (iVar3 == 1) {
        fopMsgM_setNowAlphaZero(pane2);
    } else if (iVar3 < iVar7) {
        dVar6 = fopMsgM_valueIncrease(iVar5 + -1, iVar3 + -1, 1);
        fopMsgM_setNowAlpha(pane2, dVar6);
    } else if (iVar3 < iVar4) {
        dVar6 = fopMsgM_valueIncrease(iVar4 - iVar5, iVar3 - iVar5, 0);
        fopMsgM_setNowAlpha(pane2, (f32)(1.0f - dVar6));
    } else if (iVar3 == iVar4) {
        fopMsgM_setNowAlphaZero(pane2);
    }
    i_Meter->field_0x2a90[param_2].mUserArea++;
    if (i_Meter->field_0x2a90[param_2].mUserArea > iVar4) {
        i_Meter->field_0x2a90[param_2].mUserArea = 0;
    }
}

/* 8020238C-8020240C       .text dMeter_placeNameMove__Fv */
void dMeter_placeNameMove() {
    if (!dMeter_place_name) {
        if (dComIfGp_checkStageName() == 2) {
            fopMsgM_create(PROC_PLACE_NAME);
            dMeter_place_name = true;
        }
    } else {
        if (dComIfGp_checkStageName() == 0) {
            dMeter_place_name = false;
        }
    }
}

/* 8020240C-80202438       .text dMeter_arrowInit__FP15sub_meter_class */
void dMeter_arrowInit(sub_meter_class* i_Meter) {
    for (int i = 0; i < 4; i++) {
        i_Meter->field_0x2e10[i].mUserArea = 0;
    }
    i_Meter->field_0x3025 = 0;
}

/* 80202438-80202580       .text dMeter_arrowCheckStatus__FP15sub_meter_class */
void dMeter_arrowCheckStatus(sub_meter_class* i_Meter) {
    if ((g_dComIfG_gameInfo.play.getDirection() & 1) != 0) {
        if (i_Meter->field_0x2e10[0].mUserArea == 0) {
            if ((i_Meter->field_0x3025 == 0) || (i_Meter->field_0x3025 == 0x14)) {
                i_Meter->field_0x2e10[0].mUserArea = 1;
            }
        }
    } else {
        dMeter_arrowErase(&i_Meter->field_0x2e10[0]);
    }
    if ((g_dComIfG_gameInfo.play.getDirection() & 2) != 0) {
        if (i_Meter->field_0x2e10[1].mUserArea == 0) {
            if ((i_Meter->field_0x3025 == 0) || (i_Meter->field_0x3025 == 0x14)) {
                i_Meter->field_0x2e10[1].mUserArea = 1;
            }
        }
    } else {
        dMeter_arrowErase(&i_Meter->field_0x2e10[1]);
    }
    if ((g_dComIfG_gameInfo.play.getDirection() & 4) != 0) {
        if (i_Meter->field_0x2e10[2].mUserArea == 0) {
            if ((i_Meter->field_0x3025 == 0) || (i_Meter->field_0x3025 == 0x14)) {
                i_Meter->field_0x2e10[2].mUserArea = 1;
            }
        }
    } else {
        dMeter_arrowErase(&i_Meter->field_0x2e10[2]);
    }
    if ((g_dComIfG_gameInfo.play.getDirection() & 8) != 0) {
        if (i_Meter->field_0x2e10[3].mUserArea == 0) {
            if (i_Meter->field_0x3025 == 0 || (i_Meter->field_0x3025 == 0x14)) {
                i_Meter->field_0x2e10[3].mUserArea = 1;
            }
        }
    } else {
        dMeter_arrowErase(&i_Meter->field_0x2e10[3]);
    }
}

/* 80202580-80202770       .text dMeter_arrowTransScale__FP15sub_meter_classffi */
void dMeter_arrowTransScale(sub_meter_class* i_Meter, f32 param_2, f32 param_3, int param_4) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    f32 dVar4;

    switch (param_4) {
    case 0:
        fVar1 = i_Meter->field_0x2e10[0].mPosTopLeftOrig.x;
        dVar4 = i_Meter->field_0x2e10[0].mSizeOrig.x;
        fVar2 = i_Meter->field_0x2e10[0].mPosTopLeftOrig.y;
        i_Meter->field_0x2e10[0].mSize.x = (f32)(dVar4 * param_3);
        i_Meter->field_0x2e10[0].mSize.y = i_Meter->field_0x2e10[0].mSizeOrig.y;
        i_Meter->field_0x2e10[0].mPosTopLeft.x = (f32)((f32)(fVar1 + dVar4) - param_2) - i_Meter->field_0x2e10[0].mSize.x;
        i_Meter->field_0x2e10[0].mPosTopLeft.y = fVar2;
        break;
    case 1:
        fVar1 = i_Meter->field_0x2e10[1].mPosTopLeftOrig.x;
        fVar2 = i_Meter->field_0x2e10[1].mPosTopLeftOrig.y;
        i_Meter->field_0x2e10[1].mSize.x = i_Meter->field_0x2e10[1].mSizeOrig.x;
        i_Meter->field_0x2e10[1].mSize.y = (f32)(i_Meter->field_0x2e10[1].mSizeOrig.y * param_3);
        i_Meter->field_0x2e10[1].mPosTopLeft.x = fVar1;
        i_Meter->field_0x2e10[1].mPosTopLeft.y = (f32)(fVar2 + param_2);
        break;
    case 2:
        fVar1 = i_Meter->field_0x2e10[2].mPosTopLeftOrig.x;
        fVar2 = i_Meter->field_0x2e10[2].mPosTopLeftOrig.y;
        i_Meter->field_0x2e10[2].mSize.x = (f32)(i_Meter->field_0x2e10[2].mSizeOrig.x * param_3);
        i_Meter->field_0x2e10[2].mSize.y = i_Meter->field_0x2e10[2].mSizeOrig.y;
        i_Meter->field_0x2e10[2].mPosTopLeft.x = (f32)(fVar1 + param_2);
        i_Meter->field_0x2e10[2].mPosTopLeft.y = fVar2;
        break;
    case 3:
        fVar1 = i_Meter->field_0x2e10[3].mPosTopLeftOrig.x;
        fVar2 = i_Meter->field_0x2e10[3].mPosTopLeftOrig.y;
        fVar3 = i_Meter->field_0x2e10[3].mSizeOrig.y;
        i_Meter->field_0x2e10[3].mSize.x = i_Meter->field_0x2e10[3].mSizeOrig.x;
        i_Meter->field_0x2e10[3].mSize.y = (f32)(i_Meter->field_0x2e10[3].mSizeOrig.y * param_3);
        i_Meter->field_0x2e10[3].mPosTopLeft.x = fVar1;
        i_Meter->field_0x2e10[3].mPosTopLeft.y = (f32)((fVar2 + fVar3) - param_2) - i_Meter->field_0x2e10[3].mSize.y;
        break;
    }
    i_Meter->field_0x2e10[param_4].pane->move((int)i_Meter->field_0x2e10[param_4].mPosTopLeft.x, (int)i_Meter->field_0x2e10[param_4].mPosTopLeft.y);
    i_Meter->field_0x2e10[param_4].pane->resize((int)i_Meter->field_0x2e10[param_4].mSize.x, (int)i_Meter->field_0x2e10[param_4].mSize.y);
}

/* 80202770-80203298       .text dMeter_arrowAnime__FP15sub_meter_class */
void dMeter_arrowAnime(sub_meter_class* i_Meter) {
    /* Nonmatching */
    static const f32 scale[] = {1.0f, 1.9f, 1.0f, 1.9f};
    static const s32 trans[] = {0, 30, 0, 30};
    static const u8 white[] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};
    static const u8 black[] = {0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};
    s16 iVar6;
    f32 dVar7;

    for (s32 i = 0; i < 4; i++) {
        if (i_Meter->field_0x2e10[i].mUserArea == 1) {
            iVar6 = i_Meter->field_0x3025;
            if (iVar6 > 0x14) {
                iVar6 = (s16)(i_Meter->field_0x3025 + -0x14);
            }
            dVar7 = fopMsgM_valueIncrease(10, iVar6, 0);
            dMeter_arrowTransScale(i_Meter, (dVar7 * (trans[1] - trans[0])) + trans[0], (dVar7 * (scale[1] - scale[0])) + scale[0], i);
            fopMsgM_setNowAlpha(&i_Meter->field_0x2e10[i], dVar7 * 0.8627451f);
            GXColor color1;
            color1.r = (dVar7 * (black[4] - black[0])) + black[0];
            color1.g = (dVar7 * (black[5] - black[1])) + black[1];
            color1.b = (dVar7 * (black[6] - black[2])) + black[2];
            color1.a = (dVar7 * (black[7] - black[3])) + black[3];
            GXColor color2;
            color2.r = (dVar7 * (white[4] - white[0])) + white[0];
            color2.g = (dVar7 * (white[5] - white[1])) + white[1];
            color2.b = (dVar7 * (white[6] - white[2])) + white[2];
            color2.a = (dVar7 * (white[7] - white[3])) + white[3];
            ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setBlack(color1);
            ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setWhite(color2);
            if ((s16)iVar6 == 10) {
                i_Meter->field_0x2e10[i].mUserArea = 2;
            }
        } else if (i_Meter->field_0x2e10[i].mUserArea == 2) {
            if (i_Meter->field_0x3025 <= 0x14) {
                dVar7 = fopMsgM_valueIncrease(10, (i_Meter->field_0x3025 + -10), 0);
                dMeter_arrowTransScale(i_Meter, (dVar7 * (trans[2] - trans[1])) + trans[1], (dVar7 * (scale[2] - scale[1])) + scale[1], i);
                GXColor color1;
                color1.r = (dVar7 * (black[8] - black[4])) + black[4];
                color1.g = (dVar7 * (black[9] - black[5])) + black[5];
                color1.b = (dVar7 * (black[10] - black[6])) + black[6];
                color1.a = (dVar7 * (black[11] - black[7])) + black[7];
                GXColor color2;
                color2.r = (dVar7 * (white[8] - white[4])) + white[4];
                color2.g = (dVar7 * (white[9] - white[5])) + white[5];
                color2.b = (dVar7 * (white[10] - white[6])) + white[6];
                color2.a = (dVar7 * (white[11] - white[7])) + white[7];
                ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setBlack(color1);
                ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setWhite(color2);
            } else {
                dVar7 = fopMsgM_valueIncrease(10, (i_Meter->field_0x3025 + -0x14), 0);
                dMeter_arrowTransScale(i_Meter, (dVar7 * (trans[3] - trans[2])) + trans[2], (dVar7 * (scale[3] - scale[2])) + scale[2], i);
                GXColor color1;
                color1.r = (dVar7 * (black[12] - black[8])) + black[8];
                color1.g = (dVar7 * (black[13] - black[9])) + black[9];
                color1.b = (dVar7 * (black[14] - black[10])) + black[10];
                color1.a = (dVar7 * (black[15] - black[11])) + black[11];
                GXColor color2;
                color2.r = (dVar7 * (white[12] - white[8])) + white[8];
                color2.g = (dVar7 * (white[13] - white[9])) + white[9];
                color2.b = (dVar7 * (white[14] - white[10])) + white[10];
                color2.a = (dVar7 * (white[15] - white[11])) + white[11];
                ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setBlack(color1);
                ((J2DPicture*)i_Meter->field_0x2e10[i].pane)->setWhite(color2);
            }
        }
    }
}

/* 80203298-80203354       .text dMeter_arrowErase__FP18fopMsgM_pane_class */
void dMeter_arrowErase(fopMsgM_pane_class* param_1) {
    if (param_1->mUserArea != 0) {
        fopMsgM_setNowAlphaZero(param_1);
        fopMsgM_paneTrans(param_1, 0.0f, 0.0f);
        fopMsgM_paneScaleXY(param_1, 1.0f);
        ((J2DPicture*)param_1->pane)->setBlack(0xFF000000);
        ((J2DPicture*)param_1->pane)->setWhite(0xFF0000FF);
        param_1->mUserArea = 0;
    }
}

/* 80203354-80203410       .text dMeter_arrowMove__FP15sub_meter_class */
void dMeter_arrowMove(sub_meter_class* i_Meter) {
    if ((dComIfGp_getAdvanceDirection() != 0) && (!dMenu_flag())) {
        dMeter_arrowCheckStatus(i_Meter);
        i_Meter->field_0x3025++;
        dMeter_arrowAnime(i_Meter);
        if (i_Meter->field_0x3025 < 30) {
            return;
        }
        i_Meter->field_0x3025 = 10;
        return;
    }
    if (i_Meter->field_0x3025 != 0) {
        i_Meter->field_0x3025 = 0;
        for (s32 i = 0; i < 4; i++) {
            dMeter_arrowErase(&i_Meter->field_0x2e10[i]);
        }
    }
}

/* 80203410-80203464       .text dMeter_arrowDraw__FP15sub_meter_class */
void dMeter_arrowDraw(sub_meter_class* i_Meter) {
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x2e10[i]);
    }
}

/* 80203464-8020408C       .text dMeter_screenDataSet__FP15sub_meter_class */
void dMeter_screenDataSet(sub_meter_class* i_Meter) {
    fopMsgM_setPaneData(&i_Meter->field_0x02f8, sMainParts1, 'wiy1');
    fopMsgM_setPaneData(&i_Meter->field_0x0100[0], sMainParts1, 'yrig');
    fopMsgM_setPaneData(&i_Meter->field_0x0100[1], sMainParts1, 'yup');
    fopMsgM_setPaneData(&i_Meter->field_0x0100[2], sMainParts1, 'ylef');
    fopMsgM_setPaneData(&i_Meter->field_0x0250, sMainParts1, 'r');
    fopMsgM_setPaneData(&i_Meter->field_0x0288, sMainParts1, 'l');
    fopMsgM_setPaneData(&i_Meter->field_0x02c0, sMainParts1, 'crs1');
    i_Meter->field_0x0100[0].mPosCenterOrig.x -= 2.0f;
    i_Meter->field_0x0100[1].mPosCenterOrig.y -= 2.0f;
    i_Meter->field_0x0100[2].mPosCenterOrig.x -= 1.0f;
    fopMsgM_setPaneData(&i_Meter->field_0x0368, sMainParts1, 'bey1');
    fopMsgM_setPaneData(&i_Meter->field_0x03a0, sMainParts1, 'bey2');
    fopMsgM_setPaneData(&i_Meter->field_0x03d8, sMainParts1, 'enem');
    fopMsgM_setPaneData(&i_Meter->field_0x0410, sMainParts1, 'enm2');
    fopMsgM_setPaneData(&i_Meter->field_0x0448[0], sMainParts1, 'ben1');
    fopMsgM_setPaneData(&i_Meter->field_0x0448[1], sMainParts1, 'ben2');
    fopMsgM_setPaneData(&i_Meter->field_0x0448[2], sMainParts1, 'ben3');
    fopMsgM_setPaneData(&i_Meter->field_0x0448[3], sMainParts1, 'ben4');
    fopMsgM_setPaneData(&i_Meter->field_0x0528, sMainParts1, 'ene3');
    fopMsgM_setPaneData(&i_Meter->field_0x0560, sMainParts1, 'ene2');
    fopMsgM_setPaneData(&i_Meter->field_0x0598, sMainParts1, 'ene1');
    fopMsgM_setPaneData(&i_Meter->field_0x05d0, sMainParts1, 'enk2');
    fopMsgM_setPaneData(&i_Meter->field_0x0608, sMainParts1, 'enek');
    s32 unk_13361[] = {'ht00', 'ht01', 'ht02', 'ht03', 'ht04', 'ht05', 'ht06', 'ht07', 'ht08', 'ht09',
                       'ht10', 'ht11', 'ht12', 'ht13', 'ht14', 'ht15', 'ht16', 'ht17', 'ht18', 'ht19'};
    s32 unk_13362[] = {'hk00', 'hk01', 'hk02', 'hk03', 'hk04', 'hk05', 'hk06', 'hk07', 'hk08', 'hk09',
                       'hk10', 'hk11', 'hk12', 'hk13', 'hk14', 'hk15', 'hk16', 'hk17', 'hk18', 'hk19'};
    for (s32 i = 0; i < 20; i++) {
        fopMsgM_setPaneData(&i_Meter->mHeart[i], sMainParts1, unk_13361[i]);
        fopMsgM_setPaneData(&i_Meter->mHeartShadow[i], sMainParts1, unk_13362[i]);
    }
    fopMsgM_setPaneData(&i_Meter->field_0x0f00, sMainParts1, 'htfl');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[0], sMainParts1, 'mbr1');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[1], sMainParts1, 'mbr2');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[2], sMainParts1, 'mbr3');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[3], sMainParts1, 'mbr4');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[4], sMainParts1, 'mbr5');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[5], sMainParts1, 'mbr6');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[6], sMainParts1, 'mbr7');
    fopMsgM_setPaneData(&i_Meter->field_0x0f38[7], sMainParts1, 'mbr8');
    fopMsgM_setPaneData(&i_Meter->field_0x10f8, sMainParts1, 'mbb3');
    fopMsgM_setPaneData(&i_Meter->field_0x1130, sMainParts1, 'mbb2');
    fopMsgM_setPaneData(&i_Meter->field_0x11a0, sMainParts1, 'mbb1');
    fopMsgM_setPaneData(&i_Meter->field_0x1168, sMainParts1, 'mbk2');
    fopMsgM_setPaneData(&i_Meter->field_0x11d8, sMainParts1, 'mbk1');
    fopMsgM_setPaneData(&i_Meter->field_0x1210, sMainParts1, 'cmcv');
    fopMsgM_setPaneData(&i_Meter->field_0x1248, sMainParts1, 'cmmg');
    fopMsgM_setPaneData(&i_Meter->field_0x1280, sMainParts1, 'cmmk');
    fopMsgM_setPaneData(&i_Meter->field_0x12b8, sMainParts1, 'cmrg');
    fopMsgM_setPaneData(&i_Meter->field_0x12f0, sMainParts1, 'cmb1');
    fopMsgM_setPaneData(&i_Meter->field_0x1398, sMainParts3, 'bar');
    fopMsgM_setPaneData(&i_Meter->field_0x13d0, sMainParts3, 'rng2');
    fopMsgM_setPaneData(&i_Meter->field_0x1408, sMainParts3, 'hrz1');
    fopMsgM_setPaneData(&i_Meter->field_0x1440, sMainParts3, 'hrz2');
    fopMsgM_setPaneData(&i_Meter->field_0x1478[0], sMainParts3, 'str5');
    fopMsgM_setPaneData(&i_Meter->field_0x1478[1], sMainParts3, 'str6');
    fopMsgM_setPaneData(&i_Meter->field_0x1478[2], sMainParts3, 'str7');
    fopMsgM_setPaneData(&i_Meter->field_0x1520, sMainParts3, 'mon2');
    fopMsgM_setPaneData(&i_Meter->field_0x1558, sMainParts3, 'sun2');
    fopMsgM_setPaneData(&i_Meter->field_0x1590[0], sMainParts3, 'cir1');
    fopMsgM_setPaneData(&i_Meter->field_0x1590[1], sMainParts3, 'cir2');
    fopMsgM_setPaneData(&i_Meter->field_0x1590[2], sMainParts3, 'cir3');
    fopMsgM_setPaneData(&i_Meter->field_0x1590[3], sMainParts3, 'cir4');
    fopMsgM_setPaneData(&i_Meter->field_0x1670, sMainParts3, 'cnt2');
    fopMsgM_setPaneData(&i_Meter->field_0x16a8, sMainParts3, 'cnt1');
    ((J2DPicture*)i_Meter->field_0x16a8.pane)->setWhite(0x00000000);
    fopMsgM_setPaneData(&i_Meter->field_0x16e0, sMainParts3, 'rng1');
    fopMsgM_setPaneData(&i_Meter->field_0x1718[0], sMainParts3, 'str1');
    fopMsgM_setPaneData(&i_Meter->field_0x1718[1], sMainParts3, 'str2');
    fopMsgM_setPaneData(&i_Meter->field_0x1718[2], sMainParts3, 'str3');
    fopMsgM_setPaneData(&i_Meter->field_0x1718[3], sMainParts3, 'str4');
    fopMsgM_setPaneData(&i_Meter->field_0x17f8, sMainParts3, 'mon1');
    fopMsgM_setPaneData(&i_Meter->field_0x1830, sMainParts3, 'clp');
    fopMsgM_setPaneData(&i_Meter->field_0x1868[0], sMainParts3, 'cld1');
    fopMsgM_setPaneData(&i_Meter->field_0x1868[1], sMainParts3, 'cld2');
    fopMsgM_setPaneData(&i_Meter->field_0x1868[2], sMainParts3, 'cld3');
    fopMsgM_setPaneData(&i_Meter->field_0x1910, sMainParts3, 'sun1');
    fopMsgM_setPaneData(&i_Meter->field_0x1948, sMainParts3, 'cmtm');
    ((J2DPicture*)i_Meter->field_0x1830.pane)->setWhite(0x00000000);
    fopMsgM_setPaneData(&i_Meter->field_0x1980, sMainParts1, 'kyl1');
    fopMsgM_setPaneData(&i_Meter->field_0x19b8, sMainParts1, 'kyl2');
    fopMsgM_setPaneData(&i_Meter->field_0x1ad0[0], sMainParts1, 'nm03');
    fopMsgM_setPaneData(&i_Meter->field_0x1ad0[1], sMainParts1, 'nm04');
    fopMsgM_setPaneData(&i_Meter->field_0x1c20[0], sMainParts1, 'nm08');
    fopMsgM_setPaneData(&i_Meter->field_0x1c20[1], sMainParts1, 'nm09');
    fopMsgM_setPaneData(&i_Meter->field_0x1c90, sMainParts1, 'key0');
    fopMsgM_setPaneData(&i_Meter->field_0x1cc8, sMainParts1, 'basv');
    fopMsgM_setPaneData(&i_Meter->field_0x1d00, sMainParts1, 'bawd');
    fopMsgM_setPaneData(&i_Meter->field_0x1d38, sMainParts1, 'bawp');
    fopMsgM_setPaneData(&i_Meter->field_0x1da8[1], sMainParts1, 'baa2');
    fopMsgM_setPaneData(&i_Meter->field_0x1e18[1], sMainParts1, 'bat2');
    fopMsgM_setPaneData(&i_Meter->field_0x1fd8[1], sMainParts1, 'y01');
    fopMsgM_setPaneData(&i_Meter->field_0x1f30[1], sMainParts1, 'y10');
    fopMsgM_setPaneData(&i_Meter->field_0x2080[1], sMainParts1, 'yitm');
    fopMsgM_setPaneData(&i_Meter->field_0x2128[1], sMainParts1, 'yitk');
    fopMsgM_setPaneData(&i_Meter->field_0x2320[1], sMainParts1, 'bly1');
    fopMsgM_setPaneData(&i_Meter->field_0x23c8[1], sMainParts1, 'bly2');
    fopMsgM_setPaneData(&i_Meter->field_0x2470[1], sMainParts1, 'bly3');
    i_Meter->field_0x2320[1].pane->hide();
    i_Meter->field_0x23c8[1].pane->hide();
    i_Meter->field_0x2470[1].pane->hide();
    fopMsgM_setPaneData(&i_Meter->field_0x1fd8[0], sMainParts1, 'x01');
    fopMsgM_setPaneData(&i_Meter->field_0x1f30[0], sMainParts1, 'x10');
    fopMsgM_setPaneData(&i_Meter->field_0x2080[0], sMainParts1, 'xitm');
    fopMsgM_setPaneData(&i_Meter->field_0x2128[0], sMainParts1, 'xitk');
    fopMsgM_setPaneData(&i_Meter->field_0x2320[0], sMainParts1, 'blx1');
    fopMsgM_setPaneData(&i_Meter->field_0x23c8[0], sMainParts1, 'blx2');
    fopMsgM_setPaneData(&i_Meter->field_0x2470[0], sMainParts1, 'blx3');
    i_Meter->field_0x2320[0].pane->hide();
    i_Meter->field_0x23c8[0].pane->hide();
    i_Meter->field_0x2470[0].pane->hide();
    fopMsgM_setPaneData(&i_Meter->field_0x1fd8[2], sMainParts1, 'z01');
    fopMsgM_setPaneData(&i_Meter->field_0x1f30[2], sMainParts1, 'z10');
    fopMsgM_setPaneData(&i_Meter->field_0x2080[2], sMainParts1, 'zitm');
    fopMsgM_setPaneData(&i_Meter->field_0x2128[2], sMainParts1, 'zitk');
    fopMsgM_setPaneData(&i_Meter->field_0x2320[2], sMainParts1, 'blz1');
    fopMsgM_setPaneData(&i_Meter->field_0x23c8[2], sMainParts1, 'blz2');
    fopMsgM_setPaneData(&i_Meter->field_0x2470[2], sMainParts1, 'blz3');
    i_Meter->field_0x2320[2].pane->hide();
    i_Meter->field_0x23c8[2].pane->hide();
    i_Meter->field_0x2470[2].pane->hide();
    fopMsgM_setPaneData(&i_Meter->field_0x2518, sMainParts1, 'baz');
    fopMsgM_setPaneData(&i_Meter->field_0x2550[1], sMainParts1, 'bay');
    fopMsgM_setPaneData(&i_Meter->field_0x25c0[1], sMainParts1, 'b002');
    fopMsgM_setPaneData(&i_Meter->field_0x2630[1], sMainParts1, 'ba02');
    fopMsgM_setPaneData(&i_Meter->field_0x2550[0], sMainParts1, 'bax1');
    fopMsgM_setPaneData(&i_Meter->field_0x25c0[0], sMainParts1, 'b001');
    fopMsgM_setPaneData(&i_Meter->field_0x2630[0], sMainParts1, 'ba01');
    fopMsgM_setPaneData(&i_Meter->field_0x1da8[0], sMainParts1, 'baa');
    fopMsgM_setPaneData(&i_Meter->field_0x1e18[0], sMainParts1, 'bawe');
    fopMsgM_setPaneData(&i_Meter->field_0x26a0, sMainParts1, 'bar1');
    fopMsgM_setPaneData(&i_Meter->field_0x26d8, sMainParts1, 'ba0r');
    fopMsgM_setPaneData(&i_Meter->field_0x2748, sMainParts1, 'a10');
    fopMsgM_setPaneData(&i_Meter->field_0x2780, sMainParts1, 'a01');
    fopMsgM_setPaneData(&i_Meter->field_0x27b8, sMainParts1, 'yum');
    fopMsgM_setPaneData(&i_Meter->field_0x27f0, sMainParts1, 'yumk');
    fopMsgM_setPaneData(&i_Meter->field_0x2828, sMainParts1, 'weit');
    fopMsgM_setPaneData(&i_Meter->field_0x2860, sMainParts1, 'witk');
    fopMsgM_setPaneData(&i_Meter->field_0x2898, sMainParts1, 'bab');
    fopMsgM_setPaneData(&i_Meter->field_0x28d0, sMainParts1, 'baat');
    fopMsgM_setPaneData(&i_Meter->field_0x2908, sMainParts1, 'cent');
    fopMsgM_setPaneData(&i_Meter->field_0x2940[0], sMainParts1, 'arw1');
    fopMsgM_setPaneData(&i_Meter->field_0x29b0[0], sMainParts1, 'ip00');
    fopMsgM_setPaneData(&i_Meter->field_0x2940[1], sMainParts1, 'arw2');
    fopMsgM_setPaneData(&i_Meter->field_0x29b0[1], sMainParts1, 'ip02');
    fopMsgM_setPaneData(&i_Meter->field_0x2a20, sMainParts2, 'rup1');
    fopMsgM_setPaneData(&i_Meter->field_0x2a58, sMainParts2, 'rup2');
    fopMsgM_setPaneData(&i_Meter->field_0x19f0[0], sMainParts2, 'nm00');
    fopMsgM_setPaneData(&i_Meter->field_0x19f0[1], sMainParts2, 'nm01');
    fopMsgM_setPaneData(&i_Meter->field_0x19f0[2], sMainParts2, 'nm02');
    fopMsgM_setPaneData(&i_Meter->field_0x19f0[3], sMainParts2, 'nm03');
    fopMsgM_setPaneData(&i_Meter->field_0x1b40[0], sMainParts2, 'nm04');
    fopMsgM_setPaneData(&i_Meter->field_0x1b40[1], sMainParts2, 'nm05');
    fopMsgM_setPaneData(&i_Meter->field_0x1b40[2], sMainParts2, 'nm06');
    fopMsgM_setPaneData(&i_Meter->field_0x1b40[3], sMainParts2, 'nm07');
    i_Meter->field_0x19f0[1].mUserArea = dComIfGs_getWalletSize();
    dMeter_walletChange(i_Meter);
}

/* 8020408C-8020438C       .text dMeter_screenDataTimeSet__FP15sub_meter_class */
void dMeter_screenDataTimeSet(sub_meter_class* i_Meter) {
    sScrTimer1 = new J2DScreen();
    JUT_ASSERT(12863, sScrTimer1 != NULL);
    sScrTimer2 = new J2DScreen();
    JUT_ASSERT(12865, sScrTimer2 != NULL);
    sScrTimer1->set("time_swim_1.blo", dComIfGp_getSwimResArchive());
    sScrTimer2->set("time_swim_2.blo", dComIfGp_getSwimResArchive());
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[8], sScrTimer2, 'hk33');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[7], sScrTimer2, 'hk32');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[6], sScrTimer2, 'hk31');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[5], sScrTimer2, 'hk23');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[4], sScrTimer2, 'hk22');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[3], sScrTimer2, 'hk21');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[2], sScrTimer2, 'hk13');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[1], sScrTimer2, 'hk12');
    fopMsgM_setPaneData(&i_Meter->field_0x2a90[0], sScrTimer2, 'hk11');
    fopMsgM_setPaneData(&i_Meter->field_0x2c88, sScrTimer2, 'wk00');
    fopMsgM_setPaneData(&i_Meter->field_0x2cc0, sScrTimer2, 'msk2');
    fopMsgM_setPaneData(&i_Meter->field_0x2d30, sScrTimer1, 'msk1');
    fopMsgM_setPaneData(&i_Meter->field_0x2cf8, sScrTimer1, 'soul');
    fopMsgM_setPaneData(&i_Meter->field_0x2da0, sScrTimer1, 'main');
    fopMsgM_setPaneData(&i_Meter->field_0x2dd8, sScrTimer1, 'kg00');
    sScrTimer2->search('kra')->hide();
}

/* 8020438C-80204404       .text dMeter_screenDataArrowSet__FP15sub_meter_class */
void dMeter_screenDataArrowSet(sub_meter_class* i_Meter) {
    fopMsgM_setPaneData(&i_Meter->field_0x2e10[0], sChoiceRoad, 'yaz4');
    fopMsgM_setPaneData(&i_Meter->field_0x2e10[1], sChoiceRoad, 'yaz3');
    fopMsgM_setPaneData(&i_Meter->field_0x2e10[2], sChoiceRoad, 'yaz2');
    fopMsgM_setPaneData(&i_Meter->field_0x2e10[3], sChoiceRoad, 'yaz1');
}

/* 80204404-80204820       .text dMeter_Draw__FP15sub_meter_class */
static BOOL dMeter_Draw(sub_meter_class* i_Meter) {
    fopMsgM_setAlpha(&i_Meter->field_0x02f8);
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x0100[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x0250);
    fopMsgM_setAlpha(&i_Meter->field_0x0288);
    fopMsgM_setAlpha(&i_Meter->field_0x02c0);
    fopMsgM_setAlpha(&i_Meter->field_0x0368);
    fopMsgM_setAlpha(&i_Meter->field_0x03a0);
    fopMsgM_setAlpha(&i_Meter->field_0x03d8);
    fopMsgM_setAlpha(&i_Meter->field_0x0410);
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x0448[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x0528);
    fopMsgM_setAlpha(&i_Meter->field_0x0560);
    fopMsgM_setAlpha(&i_Meter->field_0x0598);
    fopMsgM_setAlpha(&i_Meter->field_0x0608);
    dMeter_heartDraw(i_Meter);
    for (s32 i = 0; i < 8; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x0f38[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x10f8);
    fopMsgM_setAlpha(&i_Meter->field_0x11a0);
    fopMsgM_setAlpha(&i_Meter->field_0x11d8);
    fopMsgM_setAlpha(&i_Meter->field_0x1210);
    fopMsgM_setAlpha(&i_Meter->field_0x12f0);
    fopMsgM_setAlpha(&i_Meter->field_0x1398);
    fopMsgM_setAlpha(&i_Meter->field_0x13d0);
    fopMsgM_setAlpha(&i_Meter->field_0x1408);
    fopMsgM_setAlpha(&i_Meter->field_0x1440);
    for (s32 i = 0; i < 3; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x1478[i]);
        fopMsgM_setAlpha(i_Meter->field_0x1868);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x1520);
    fopMsgM_setAlpha(&i_Meter->field_0x1558);
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x1590[i]);
        fopMsgM_setAlpha(i_Meter->field_0x1718);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x1670);
    fopMsgM_setAlpha(&i_Meter->field_0x16a8);
    fopMsgM_setAlpha(&i_Meter->field_0x16e0);
    fopMsgM_setAlpha(&i_Meter->field_0x17f8);
    fopMsgM_setAlpha(&i_Meter->field_0x1830);
    fopMsgM_setAlpha(&i_Meter->field_0x1910);
    fopMsgM_setAlpha(&i_Meter->field_0x1948);
    if ((i_Meter->field_0x1830.pane->isVisible()) && (i_Meter->field_0x3020 == 7)) {
        for (s32 i = 0; i < 3; i++) {
            clock[i].mC0.a = i_Meter->field_0x1830.mNowAlpha;
        }
    } else {
        for (s32 i = 0; i < 3; i++) {
            clock[i].mC0.a = 0;
        }
    }
    fopMsgM_setAlpha(&i_Meter->field_0x1980);
    fopMsgM_setAlpha(&i_Meter->field_0x19b8);
    for (s32 i = 0; i < 2; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x1ad0[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x1c20[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x1c90);
    dMeter_weponDraw(i_Meter);
    dMeter_actionDraw(i_Meter);
    dMeter_xyDraw(i_Meter);
    dMeter_rDraw(i_Meter);
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&i_Meter->field_0x19f0[i]);
        fopMsgM_setAlpha(&i_Meter->field_0x1b40[i]);
    }
    fopMsgM_setAlpha(&i_Meter->field_0x2a20);
    fopMsgM_setAlpha(&i_Meter->field_0x2a58);
    dMeter_swimDraw(i_Meter);
    dMeter_arrowDraw(i_Meter);
    if (!fopOvlpM_IsDoingReq()) {
        dComIfGd_set2DOpa(&meter1);
        for (s32 i = 0; i < 3; i++) {
            dComIfGd_set2DOpa(&clock[i]);
        }
        if ((sScrTimer1 != NULL) && (sScrTimer2 != NULL)) {
            dComIfGd_set2DOpa(&tekari);
        }
        dComIfGd_set2DOpaTop(&meter2);
        dMeter_moveItemDraw(i_Meter);
        if ((i_Meter->field_0x3028 == 1) && dComIfGp_getMetronome() && (!(i_Meter->mStatusFlags & dMtrStts_UNK8_e)) &&
            (!(i_Meter->mStatusFlags & dMtrStts_UNK10_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK800000_e)) && (!(i_Meter->mStatusFlags & dMtrStts_UNK20_e)))
        {
            dComIfGd_set2DOpa(dMn_c);
        }
    }
    return TRUE;
}

/* 80204820-80204C20       .text dMeter_Execute__FP15sub_meter_class */
static BOOL dMeter_Execute(sub_meter_class* i_Meter) {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(i_Meter->heap);
    i_Meter->field_0x3024 = 0;
    dMeter_statusCheck(i_Meter);
    dMeter_alphaControl(i_Meter);
    dMeter_heartMove(i_Meter);
    dMeter_actionMove(i_Meter);
    dMeter_weponMove(i_Meter);
    dMeter_xyMove(i_Meter);
    dMeter_rMove(i_Meter);

    f32 f31 = g_meterHIO.field_0x40 / 100.0f;
    f32 f30 = g_meterHIO.field_0x44 / 100.0f;
    f32 f29 = g_meterHIO.field_0x46 / 100.0f;

    dMeter_parentPaneTrans(&i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x2898, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x28d0, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTransOnly(&i_Meter->field_0x1d00, &i_Meter->field_0x2908, f31, f30);
    dMeter_childPaneTransOnly(&i_Meter->field_0x2828, &i_Meter->field_0x2908, f31, f29);
    dMeter_childPaneTransChildTrans(&i_Meter->field_0x2860, &i_Meter->field_0x2908, &i_Meter->field_0x2828, f31, f29);
    dMeter_childPaneTransOnly(&i_Meter->field_0x1d38, &i_Meter->field_0x2908, f31, f30);

    for (int i = 0; i < 2; i++) {
        dMeter_childPaneTrans(&i_Meter->field_0x1e18[i], &i_Meter->field_0x2908, f31);
        dMeter_childPaneTrans(&i_Meter->field_0x1da8[i], &i_Meter->field_0x2908, f31);
    }

    dMeter_childPaneTrans(&i_Meter->field_0x2748, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x2780, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x27b8, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x27f0, &i_Meter->field_0x2908, f31);

    for (int i = 0; i < 3; i++) {
        dMeter_childPaneTransOnly(&i_Meter->field_0x2080[i], &i_Meter->field_0x2908, f31, f29);
        dMeter_childPaneTransChildTransOnly(&i_Meter->field_0x1fd8[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
        dMeter_childPaneTransChildTransOnly(&i_Meter->field_0x1f30[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
        dMeter_childPaneTransChildTrans(&i_Meter->field_0x2128[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
        dMeter_childPaneTransChildTrans(&i_Meter->field_0x2320[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
        dMeter_childPaneTransChildTrans(&i_Meter->field_0x23c8[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
        dMeter_childPaneTransChildTrans(&i_Meter->field_0x2470[i], &i_Meter->field_0x2908, &i_Meter->field_0x2080[i], f31, f29);
    }

    dMeter_childPaneTrans(&i_Meter->field_0x2518, &i_Meter->field_0x2908, f31);

    for (int i = 0; i < 2; i++) {
        dMeter_childPaneTrans(&i_Meter->field_0x2550[i], &i_Meter->field_0x2908, f31);
        dMeter_childPaneTrans(&i_Meter->field_0x25c0[i], &i_Meter->field_0x2908, f31);
        dMeter_childPaneTrans(&i_Meter->field_0x2630[i], &i_Meter->field_0x2908, f31);
    }

    dMeter_childPaneTransOnly(&i_Meter->field_0x1cc8, &i_Meter->field_0x2908, f31, f30);
    dMeter_childPaneTrans(&i_Meter->field_0x26d8, &i_Meter->field_0x2908, f31);
    dMeter_childPaneTrans(&i_Meter->field_0x26a0, &i_Meter->field_0x2908, f31);

    dMeter_enemyMove(i_Meter);
    dMeter_magicMove(i_Meter);
    dMeter_windMove(i_Meter);
    dMeter_metronomeMove(i_Meter);
    dMeter_rupyMove(i_Meter);
    dMeter_keyMove(i_Meter);
    dMeter_compassMove(i_Meter);
    dMeter_mapMove(i_Meter);
    dMeter_swimMove(i_Meter);
    dMeter_arrowMove(i_Meter);

    if (dMeter_itemMoveFlagCheck()) {
        dMeter_moveItemMove(i_Meter);
    }
    dMeter_arwMove(i_Meter);
    dMeter_placeNameMove();
    dMeter_menuMove(i_Meter);
    dMeter_gaugeAlpha(i_Meter);
    dComIfGp_setButtonActionMode(i_Meter->field_0x3024);
    mDoExt_setCurrentHeap(oldHeap);
    return TRUE;
}

/* 80204C20-80204C28       .text dMeter_IsDelete__FP15sub_meter_class */
static BOOL dMeter_IsDelete(sub_meter_class* i_Meter) {
    return TRUE;
}

/* 80204C28-80205034       .text dMeter_Delete__FP15sub_meter_class */
static BOOL dMeter_Delete(sub_meter_class* i_Meter) {
    JKRHeap* pJVar1 = mDoExt_setCurrentHeap(i_Meter->heap);
    if ((s32)dMeter_mMapCtrlDisp.field_0x0 != 0) {
        g_dComIfG_gameInfo.play.field_0x497a = 0;
    } else {
        g_dComIfG_gameInfo.play.field_0x497a = 1;
    }
    if (rupy_soundOnFlag != 0) {
        mDoAud_seStart(JA_SE_LUPY_INC_CNT_2);
        rupy_soundSetFlag = 0;
        rupy_soundOnFlag = 0;
    }
    if (dMeter_windID != fpcM_ERROR_PROCESS_ID_e) {
        if (fopMsgM_SearchByID(dMeter_windID) != NULL) {
            msg_class* pmVar2 = fopMsgM_SearchByID(dMeter_windID);
            fopMsgM_Delete(pmVar2);
            dMeter_windID = fpcM_ERROR_PROCESS_ID_e;
            dMeter_windStatus = 0;
        } else {
            dMeter_windID = fpcM_ERROR_PROCESS_ID_e;
            dMeter_windStatus = 0;
        }
    }
    if (i_Meter->mpRupyParticle != NULL) {
        i_Meter->mpRupyParticle->becomeInvalidEmitter();
        i_Meter->mpRupyParticle->quitImmortalEmitter();
    }
    for (s32 i = 0; i < 2; i++) {
        if (i_Meter->field_0x2f24[i] != NULL) {
            i_Meter->field_0x2f24[i]->becomeInvalidEmitter();
            i_Meter->field_0x2f24[i]->quitImmortalEmitter();
        }
    }
    for (s32 i = 0; i < 2; i++) {
        if (i_Meter->field_0x2f2c[i] != NULL) {
            i_Meter->field_0x2f2c[i]->becomeInvalidEmitter();
            i_Meter->field_0x2f2c[i]->quitImmortalEmitter();
        }
    }
    if (dMn_c != NULL) {
        dMn_c->_delete();
        delete dMn_c;
        dMn_c = NULL;
    }
    for (s32 i = 0; i < 3; i++) {
        i_Meter->heap->free(i_Meter->actionTex[i]);
        i_Meter->heap->free(i_Meter->xyIconTex[i]);
    }
    for (s32 i = 0; i < 2; i++) {
        i_Meter->heap->free(i_Meter->arrowTex[i]);
        if (i == 0) {
            i_Meter->heap->free(i_Meter->moveIconTex[i]);
        }
    }
    delete sMainParts1;
    delete sMainParts2;
    delete sMainParts3;
    if ((sScrTimer1 != NULL) && (sScrTimer2 != NULL)) {
        dComIfGp_getSwimResArchive()->removeResourceAll();
        delete sScrTimer1;
        delete sScrTimer2;
        sScrTimer1 = NULL;
        sScrTimer2 = NULL;
    }
    delete sChoiceRoad;
    sChoiceRoad = NULL;
    delete moveItemPane;
    moveItemPane = NULL;
    mDoExt_setCurrentHeap(pJVar1);
    fopMsgM_destroyExpHeap(i_Meter->heap);
    mDoHIO_deleteChild(g_meterHIO.mNo);
    mDoHIO_deleteChild(g_menuHIO.mNo);
    mDoHIO_deleteChild(g_msgHIO.mNo);
    mDoHIO_deleteChild(g_messageHIO.mNo);
    mDoHIO_deleteChild(g_meter_mapHIO.mNo);
    return TRUE;
}

/* 80205034-802057B8       .text dMeter_Create__FP9msg_class */
static cPhs_State dMeter_Create(msg_class* i_this) {
    sub_meter_class* i_Meter = (sub_meter_class*)i_this;

    mapAlpha = 0;
    menu_status = 0;
    menu_status_old = 0;
    dMenu_pause = 0;
    dMenu_frame_timer = 0;
    dMenu_menuButton = 0;
    subWinFlag = 0;
    dMeter_auctionFlag = 0;
    dMeter_itemMoveFlag = 0;
    dMeter_btn_chk = 0;
    dMeter_itemNum = 0;
    dMeter_itemTimer = 0;
    texRateX = 0.0f;
    texRateY = 0.0f;
    texScaleX = 0.0f;
    texScaleY = 0.0f;
    dMenu_menuFlag = 0;
    dMeter_place_name = 0;
    dMeter_itemMode = 0;
    dMeter_collectMode = 0;
    rupy_soundSetFlag = 0;
    rupy_soundOnFlag = 0;

    i_Meter->heap = fopMsgM_createExpHeap(0x2a819);
    JUT_ASSERT(13475, i_Meter->heap != NULL);

    JKRHeap* oldHeap = mDoExt_setCurrentHeap(i_Meter->heap);
    sMainParts1 = new MyScreen();
    JUT_ASSERT(13480, sMainParts1 != NULL);
    sMainParts1->set("main_parts1.blo", dComIfGp_getMenuArchive());

    sMainParts2 = new J2DScreen();
    JUT_ASSERT(13484, sMainParts2 != NULL);
    sMainParts2->set("main_parts2.blo", dComIfGp_getMenuArchive());

    sMainParts3 = new J2DScreen();
    JUT_ASSERT(13488, sMainParts3 != NULL);
    sMainParts3->set("main_parts3.blo", dComIfGp_getMenuArchive());

    sChoiceRoad = new J2DScreen();
    JUT_ASSERT(13492, sChoiceRoad != NULL);
    sChoiceRoad->set("choice_road.blo", dComIfGp_getMenuArchive());

    for (s32 i = 0; i < 3; i++) {
        i_Meter->actionTex[i] = (ResTIMG*)i_Meter->heap->alloc(0xc00, 0x20);
        JUT_ASSERT(13497, i_Meter->actionTex[i] != NULL);

        i_Meter->xyIconTex[i] = (ResTIMG*)i_Meter->heap->alloc(0xc00, 0x20);
        JUT_ASSERT(13499, i_Meter->xyIconTex[i] != NULL);
    }

    for (s32 i = 0; i < 2; i++) {
        if (i == 0) {
            i_Meter->moveIconTex[i] = (ResTIMG*)i_Meter->heap->alloc(0xc00, 0x20);
            JUT_ASSERT(13506, i_Meter->moveIconTex[i] != NULL);
        }

        i_Meter->arrowTex[i] = (ResTIMG*)i_Meter->heap->alloc(0xc00, 0x20);
        JUT_ASSERT(13509, i_Meter->arrowTex[i] != NULL);
    }

    if (strcmp(dComIfGp_getStartStageName(), "sea_T") != 0) {
        fopMsgM_Create(PROC_MENUWINDOW, NULL, NULL);
    }

    fopMsgM_Create(PROC_MESG, NULL, NULL);

    dComIfGp_setDoStatusForce(dActStts_BLANK_e);
    dComIfGp_setRStatusForce(dActStts_BLANK_e);
    dComIfGp_setAStatusForce(dActStts_BLANK_e);

    g_meterHIO.mNo = mDoHIO_createChild("通常画面表示", &g_meterHIO);        // "Normal Screen Display"
    g_menuHIO.mNo = mDoHIO_createChild("メニュー画面", &g_menuHIO);          // "Menu Screen"
    g_msgHIO.mNo = mDoHIO_createChild("Message（会話）", &g_msgHIO);         // "Message (Talk)"
    g_messageHIO.mNo = mDoHIO_createChild("Message（看板）", &g_messageHIO); // "Message (Sign)"
    g_meter_mapHIO.mNo = mDoHIO_createChild("マップ２", &g_meter_mapHIO);    // "Map 2"

    dMeter_screenDataSet(i_Meter);
    dMeter_screenDataArrowSet(i_Meter);
    dComIfGp_2dShowOn();
    i_Meter->field_0x2f6c = 1.0f;
    i_Meter->field_0x2fd8 = g_meterHIO.field_0x6;
    dMeter_mapInit(i_Meter);
    dMeter_compassInit(i_Meter);
    dMeter_arrowInit(i_Meter);
    mDoExt_setCurrentHeap(i_Meter->heap);
    dMeter_heartInit(i_Meter);
    dMeter_weponInit(i_Meter);
    dMeter_actionInit(i_Meter);
    dMeter_xyInit(i_Meter);
    dMeter_rInit(i_Meter);
    dMeter_enemyInit(i_Meter);
    dMeter_magicInit(i_Meter);
    dMeter_menuInit(i_Meter);
    dMeter_windInit(i_Meter);
    dMeter_metronomeInit(i_Meter);
    dMeter_rupyInit(i_Meter);
    dMeter_keyInit(i_Meter);
    dMeter_moveItemInit(i_Meter);
    dMeter_arwInit(i_Meter);
    dTimer_createStockTimer();
    mDoExt_setCurrentHeap(oldHeap);
    fopMsgM_setStageLayer(i_Meter);
    return cPhs_COMPLEATE_e;
}

/* 802057B8-80205814       .text __dt__16dDlst_2DMETER2_cFv */
dDlst_2DMETER2_c::~dDlst_2DMETER2_c() {
}

/* 80205814-80205870       .text __dt__16dDlst_2DMETER1_cFv */
dDlst_2DMETER1_c::~dDlst_2DMETER1_c() {
}

/* 80205870-802058B8       .text __dt__20dMeter_message_HIO_cFv */
dMeter_message_HIO_c::~dMeter_message_HIO_c() {
}

/* 802058B8-80205900       .text __dt__16dMeter_msg_HIO_cFv */
dMeter_msg_HIO_c::~dMeter_msg_HIO_c() {
}

/* 80205900-80205948       .text __dt__16dMeter_menuHIO_cFv */
dMeter_menuHIO_c::~dMeter_menuHIO_c() {
}

/* 80205948-80205990       .text __dt__12dMeter_HIO_cFv */
dMeter_HIO_c::~dMeter_HIO_c() {
}

/* 80205990-802059E0       .text __ct__16dMeter_map_HIO_cFv */
dMeter_map_HIO_c::dMeter_map_HIO_c() {
    field_0x8 = 0x23;
    field_0xa = 0x152;
    field_0xc = -0xb4;
    field_0x14 = 0x24e;
    field_0x16 = 0x96;
    field_0x6 = 200;
    field_0x7 = 1;
    field_0x10 = 0.8f;
}

/* 802059E0-80205A44       .text initMapCtrlDisp__13mapCtrlDisp_cFv */
void mapCtrlDisp_c::initMapCtrlDisp() {
    dMap_setMapAlpha(0);
    dMap_setIconFreeAlpha(0);
    dMap_setMapDispMode(1);
    dMap_setMapDispPosLeftUpX(g_meter_mapHIO.field_0x8);
    dMap_setMapDispPosLeftUpY(g_meter_mapHIO.field_0xa);
    dMap_setIconFreePosX(g_meter_mapHIO.field_0x14);
    dMap_setIconFreePosY(g_meter_mapHIO.field_0x16);
    dMap_setIconFreeScale(0.0f);
    dMap_setIconSelfAlpha(0);
    dMap_setIconSelfScale(0.0f);
    dMap_setIconDispMode(0);
    field_0x0 = 0;
    field_0x1 = 0;
    field_0x2 = 0;
    field_0x4 = 0;
}

/* 80205A44-80205D24       .text moveMapCtrlDisp__13mapCtrlDisp_cFv */
void mapCtrlDisp_c::moveMapCtrlDisp() {
    f32 fVar1;
    s8 uVar6;
    f32 dVar7;

    if (dCam_isManual(dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0))) != 0) {
        if (field_0x2 < 9) {
            field_0x2++;
            if (field_0x2 < 6) {
                dVar7 = fopMsgM_valueIncrease(6, field_0x2, 0);
                fVar1 = dVar7 * 1.2f;
            } else {
                dVar7 = fopMsgM_valueIncrease(3, field_0x2 - 6, 2);
                fVar1 = 1.2f - (dVar7 * 0.1f);
                dVar7 = 1.0f;
            }
        } else {
            dVar7 = 1.0f;
            fVar1 = 1.1f;
        }
    } else {
        if (field_0x2 > 5) {
            field_0x2 = 5;
        }
        if (field_0x2 != 0) {
            field_0x2--;
        }
        dVar7 = fopMsgM_valueIncrease(5, field_0x2, 2);
        fVar1 = 1.1f;
    }
    dMap_c::mIconDispMode = 0;
    uVar6 = (u8)((dVar7 * 255.0f) * (g_meter_mapHIO.field_0x6 / 255.0f));
    dMap_c::mIconFreeAlpha = (u8)uVar6;
    dMap_c::mIconFreeScale = fVar1 * g_meter_mapHIO.field_0x10;
    if ((u8)uVar6 != 0) {
        dMap_c::mIconDispMode = 1;
    }
    if (dComIfGp_checkCameraAttentionStatus(0, 0x400)) {
        daPy_py_c* player = daPy_getPlayerActorClass();
        BOOL temp = player->checkSubjectAccept() && !dComIfGp_event_runCheck();
        if (temp) {
            dMap_c::mIconSelfAlpha = 0xcc;
            dMap_c::mIconDispMode = 2;
        }
    }
    if (dCam_getBody()->mCurMode == 4) {
        dMap_c::mIconDispMode = 0;
    }
    if (field_0x0 != 0) {
        if (((field_0x4 != 0) && (cLib_addCalcAngleS(&field_0x4, 0, 2, 0x3c, 10) == 0)) && ((field_0x1 & 4) == 0)) {
            mDoAud_seStart(JA_SE_MAP_SHOW_END);
        }
    } else {
        cLib_addCalcAngleS(&field_0x4, g_meter_mapHIO.field_0xc - g_meter_mapHIO.field_0x8, 2, 0x3c, 10);
    }
    int uVar6_2 = ((dComIfGp_getWindow(0)->getScissor()->mYOrig + dComIfGp_getWindow(0)->getScissor()->mHeight) - 452.0f);
    dMap_c::mDispPosLeftUpX = g_meter_mapHIO.field_0x8 + field_0x4;
    dMap_c::mDispPosLeftUpY = g_meter_mapHIO.field_0xa;
    if ((f32)(uVar6_2) < 0.0f) {
        dMap_c::mDispPosLeftUpY = uVar6_2 + g_meter_mapHIO.field_0xa;
    }
}

/* 80205D24-80205D6C       .text __dt__16dMeter_map_HIO_cFv */
dMeter_map_HIO_c::~dMeter_map_HIO_c() {
}

msg_method_class l_dMeter_Method = {
    (process_method_func)dMeter_Create,
    (process_method_func)dMeter_Delete,
    (process_method_func)dMeter_Execute,
    (process_method_func)dMeter_IsDelete,
    (process_method_func)dMeter_Draw,
};

msg_process_profile_definition g_profile_METER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 12,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_METER,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sub_meter_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Priority     */ PRIO_METER,
    /* Msg SubMtd   */ &l_dMeter_Method,
};
