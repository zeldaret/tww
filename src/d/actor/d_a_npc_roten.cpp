/**
 * d_a_npc_roten.cpp
 * NPC - Traveling Merchants
 */

#include "d/actor/d_a_npc_roten.h"
#include "d/res/res_ro.h"
#include "m_Do/m_Do_ext.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_demo_item.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_a_obj.h"
#include "d/d_snap.h"

#include "weak_data_1811.h" // IWYU pragma: keep

extern dCcD_SrcCyl dNpc_cyl_src;

static const char* l_arcname_tbl[] = {
    "Ro",
    "Ro",
    "Ro",
};

static sRotenAnmDat l_npc_anm_wait[] = {
    {
        0x00,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_talk[] = {
    {
        0x01,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_walk[] = {
    {
        0x02,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_talk2[] = {
    {
        0x03,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_talk3[] = {
    {
        0x04,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_talk4[] = {
    {
        0x05,
        0x06,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_talk5[] = {
    {
        0x06,
        0x0A,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_watasu[] = {
    {
        0x07,
        0x0E,
        0x01,
    },
    {
        0x08,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_itemwait[] = {
    {
        0x08,
        0x0E,
        0xFF,
    },
};

static sRotenAnmDat l_npc_anm_wind[] = {
    {
        0x09,
        0x0E,
        0x01,
    },
    {
        0x00,
        0x14,
        0x01,
    },
    {
        0xFF,
        0x08,
        0x00,
    },
};

struct NpcDatStruct {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ s16 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ s16 field_0x4C;
    /* 0x4E */ s16 field_0x4E;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
}; // Size: 0x54

static NpcDatStruct l_npc_dat[] = {
    {
        0.0f,
        0x09C4,
        0x1388,
        0x1388,
        0x1388,
        0xF63C,
        0xEC78,
        0xEC78,
        0xEC78,
        0x03E8,
        0x0352,
        0x0190,
        0x0000,
        190.0f,
        0x7FFF,
        250.0f,
        150.0f,
        120.0f,
        120.0f,
        40.0f,
        60.0f,
        30.0f,
        1.0f,
        1.0f,
        0x0006,
        0x0400,
        0x003C,
        0x005A,
        0x00C8,
        0x012C,
    },
    {
        0.0f,
        0x09C4,
        0x1388,
        0x1388,
        0x1388,
        0xF63C,
        0xEC78,
        0xEC78,
        0xEC78,
        0x03E8,
        0x0352,
        0x0190,
        0x0000,
        190.0f,
        0x7FFF,
        250.0f,
        150.0f,
        120.0f,
        120.0f,
        40.0f,
        50.0f,
        20.0f,
        1.0f,
        1.0f,
        0x0006,
        0x0400,
        0x003C,
        0x005A,
        0x00C8,
        0x012C,
    },
    {
        0.0f,
        0x09C4,
        0x1388,
        0x1388,
        0x1388,
        0xF63C,
        0xEC78,
        0xEC78,
        0xEC78,
        0x03E8,
        0x0352,
        0x0190,
        0x0000,
        190.0f,
        0x7FFF,
        250.0f,
        150.0f,
        120.0f,
        120.0f,
        40.0f,
        60.0f,
        30.0f,
        1.0f,
        1.0f,
        0x0006,
        0x0400,
        0x003C,
        0x005A,
        0x00C8,
        0x012C,
    },
};

static u32 l_msg_1st_talk_A[] = {
    0x2905,
    0x2906,
    0x2907,
    0x2908,
    0x2909,
    0x0000,
};

static u32 l_msg_1st_talk_B[] = {
    0x2969,
    0x296A,
    0x296B,
    0x296C,
    0x296D,
    0x0000,
};

static u32 l_msg_1st_talk_C[] = {
    0x29CD,
    0x29CE,
    0x29CF,
    0x29D0,
    0x29D1,
    0x0000,
};

static u32* l_msg_1st_talk[] = {
    l_msg_1st_talk_A,
    l_msg_1st_talk_B,
    l_msg_1st_talk_C,
};

static u32 l_msg_exchange3_A[] = {
    0x290C,
    0x290D,
    0x290E,
    0x0000,
};

static u32 l_msg_exchange3_B[] = {
    0x2970,
    0x2971,
    0x2972,
    0x0000,
};

static u32 l_msg_exchange3_C[] = {
    0x29D4,
    0x29D5,
    0x29D6,
    0x0000,
};

static u32* l_msg_exchange3[] = {
    l_msg_exchange3_A,
    l_msg_exchange3_B,
    l_msg_exchange3_C,
};

static u32 l_msg_exchange_A[] = {
    0x290F,
    0x2910,
    0x0000,
};

static u32 l_msg_exchange_B[] = {
    0x2973,
    0x2974,
    0x0000,
};

static u32 l_msg_exchange_C[] = {
    0x29D7,
    0x29D8,
    0x0000,
};

static u32* l_msg_exchange[] = {
    l_msg_exchange_A,
    l_msg_exchange_B,
    l_msg_exchange_C,
};

static u32 l_msg_etc_A[] = {
    0x290A,
    0x290B,
    0x0000,
};

static u32 l_msg_etc_B[] = {
    0x296E,
    0x296F,
    0x0000,
};

static u32 l_msg_etc_C[] = {
    0x29D2,
    0x29D3,
    0x0000,
};

static u32* l_msg_etc[] = {
    l_msg_etc_A,
    l_msg_etc_B,
    l_msg_etc_C,
};

static u32 l_msg_xy_exchange3_A[] = {
    0x2911,
    0x2912,
    0x0000,
};

static u32 l_msg_xy_exchange3_B[] = {
    0x2975,
    0x2976,
    0x0000,
};

static u32 l_msg_xy_exchange3_C[] = {
    0x29D9,
    0x29DA,
    0x0000,
};

static u32* l_msg_xy_exchange3[] = {
    l_msg_xy_exchange3_A,
    l_msg_xy_exchange3_B,
    l_msg_xy_exchange3_C,
};

static u32 l_msg_xy_no_roten_item_A[] = {
    0x2914,
    0x0000,
};

static u32 l_msg_xy_no_roten_item_B[] = {
    0x2978,
    0x0000,
};

static u32 l_msg_xy_no_roten_item_C[] = {
    0x29DC,
    0x0000,
};

static u32* l_msg_xy_no_roten_item[] = {
    l_msg_xy_no_roten_item_A,
    l_msg_xy_no_roten_item_B,
    l_msg_xy_no_roten_item_C,
};

static u32 l_msg_xy_invalid_item_A[] = {
    0x2915,
    0x0000,
};

static u32 l_msg_xy_invalid_item_B[] = {
    0x2979,
    0x0000,
};

static u32 l_msg_xy_invalid_item_C[] = {
    0x29DD,
    0x0000,
};

static u32* l_msg_xy_invalid_item[] = {
    l_msg_xy_invalid_item_A,
    l_msg_xy_invalid_item_B,
    l_msg_xy_invalid_item_C,
};

static u32 l_msg_xy_koukan_item_A0[] = {
    0x2913,
    0x2916,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A1[] = {
    0x2913,
    0x2917,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A2[] = {
    0x2913,
    0x2918,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A3[] = {
    0x2913,
    0x2919,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A4[] = {
    0x2913,
    0x291A,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A5[] = {
    0x2913,
    0x291B,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A6[] = {
    0x2913,
    0x291C,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A7[] = {
    0x2913,
    0x291D,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A8[] = {
    0x2913,
    0x291E,
    0x0000,
};

static u32 l_msg_xy_koukan_item_A9[] = {
    0x2913,
    0x291F,
    0x0000,
};

static u32 l_msg_xy_koukan_item_AA[] = {
    0x2913,
    0x2920,
    0x0000,
};

static u32 l_msg_xy_koukan_item_AB[] = {
    0x2913,
    0x2921,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B0[] = {
    0x2977,
    0x297A,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B1[] = {
    0x2977,
    0x297B,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B2[] = {
    0x2977,
    0x297C,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B3[] = {
    0x2977,
    0x297D,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B4[] = {
    0x2977,
    0x297E,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B5[] = {
    0x2977,
    0x297F,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B6[] = {
    0x2977,
    0x2980,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B7[] = {
    0x2977,
    0x2981,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B8[] = {
    0x2977,
    0x2982,
    0x0000,
};

static u32 l_msg_xy_koukan_item_B9[] = {
    0x2977,
    0x2983,
    0x0000,
};

static u32 l_msg_xy_koukan_item_BA[] = {
    0x2977,
    0x2984,
    0x0000,
};

static u32 l_msg_xy_koukan_item_BB[] = {
    0x2977,
    0x2985,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C0[] = {
    0x29DB,
    0x29DE,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C1[] = {
    0x29DB,
    0x29DF,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C2[] = {
    0x29DB,
    0x29E0,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C3[] = {
    0x29DB,
    0x29E1,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C4[] = {
    0x29DB,
    0x29E2,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C5[] = {
    0x29DB,
    0x29E3,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C6[] = {
    0x29DB,
    0x29E4,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C7[] = {
    0x29DB,
    0x29E5,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C8[] = {
    0x29DB,
    0x29E6,
    0x0000,
};

static u32 l_msg_xy_koukan_item_C9[] = {
    0x29DB,
    0x29E7,
    0x0000,
};

static u32 l_msg_xy_koukan_item_CA[] = {
    0x29DB,
    0x29E8,
    0x0000,
};

static u32 l_msg_xy_koukan_item_CB[] = {
    0x29DB,
    0x29E9,
    0x0000,
};

static u32* l_msg_xy_koukan_item[][12] = {
    {
        l_msg_xy_koukan_item_A0,
        l_msg_xy_koukan_item_A1,
        l_msg_xy_koukan_item_A2,
        l_msg_xy_koukan_item_A3,
        l_msg_xy_koukan_item_A4,
        l_msg_xy_koukan_item_A5,
        l_msg_xy_koukan_item_A6,
        l_msg_xy_koukan_item_A7,
        l_msg_xy_koukan_item_A8,
        l_msg_xy_koukan_item_A9,
        l_msg_xy_koukan_item_AA,
        l_msg_xy_koukan_item_AB,
    },
    {
        l_msg_xy_koukan_item_B0,
        l_msg_xy_koukan_item_B1,
        l_msg_xy_koukan_item_B2,
        l_msg_xy_koukan_item_B3,
        l_msg_xy_koukan_item_B4,
        l_msg_xy_koukan_item_B5,
        l_msg_xy_koukan_item_B6,
        l_msg_xy_koukan_item_B7,
        l_msg_xy_koukan_item_B8,
        l_msg_xy_koukan_item_B9,
        l_msg_xy_koukan_item_BA,
        l_msg_xy_koukan_item_BB,
    },
    {
        l_msg_xy_koukan_item_C0,
        l_msg_xy_koukan_item_C1,
        l_msg_xy_koukan_item_C2,
        l_msg_xy_koukan_item_C3,
        l_msg_xy_koukan_item_C4,
        l_msg_xy_koukan_item_C5,
        l_msg_xy_koukan_item_C6,
        l_msg_xy_koukan_item_C7,
        l_msg_xy_koukan_item_C8,
        l_msg_xy_koukan_item_C9,
        l_msg_xy_koukan_item_CA,
        l_msg_xy_koukan_item_CB,
    },
};

static u32 l_msg_xy_koukan_item2_A0[] = {
    0x2922,
    0x0001,
    0x2930,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A1[] = {
    0x2923,
    0x0001,
    0x2931,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A2[] = {
    0x2924,
    0x0001,
    0x2932,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A3[] = {
    0x2925,
    0x0001,
    0x2933,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A4[] = {
    0x2926,
    0x0001,
    0x2934,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A5[] = {
    0x2927,
    0x0001,
    0x2935,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A6[] = {
    0x2928,
    0x0001,
    0x2936,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A7[] = {
    0x2929,
    0x0001,
    0x2937,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A8[] = {
    0x292A,
    0x0001,
    0x2938,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_A9[] = {
    0x292B,
    0x0001,
    0x2939,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_AA[] = {
    0x292C,
    0x0001,
    0x293A,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_AB[] = {
    0x292D,
    0x0001,
    0x293B,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B0[] = {
    0x2986,
    0x0001,
    0x2994,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B1[] = {
    0x2987,
    0x0001,
    0x2995,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B2[] = {
    0x2988,
    0x0001,
    0x2996,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B3[] = {
    0x2989,
    0x0001,
    0x2997,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B4[] = {
    0x298A,
    0x0001,
    0x2998,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B5[] = {
    0x298B,
    0x0001,
    0x2999,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B6[] = {
    0x298C,
    0x0001,
    0x299A,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B7[] = {
    0x298D,
    0x0001,
    0x299B,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B8[] = {
    0x298E,
    0x0001,
    0x299C,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_B9[] = {
    0x298F,
    0x0001,
    0x299D,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_BA[] = {
    0x2990,
    0x0001,
    0x299E,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_BB[] = {
    0x2991,
    0x0001,
    0x299F,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C0[] = {
    0x29EA,
    0x0001,
    0x29F8,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C1[] = {
    0x29EB,
    0x0001,
    0x29F9,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C2[] = {
    0x29EC,
    0x0001,
    0x29FA,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C3[] = {
    0x29ED,
    0x0001,
    0x29FB,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C4[] = {
    0x29EE,
    0x0001,
    0x29FC,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C5[] = {
    0x29EF,
    0x0001,
    0x29FD,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C6[] = {
    0x29F0,
    0x0001,
    0x29FE,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C7[] = {
    0x29F1,
    0x0001,
    0x29FF,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C8[] = {
    0x29F2,
    0x0001,
    0x2A00,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_C9[] = {
    0x29F3,
    0x0001,
    0x2A01,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_CA[] = {
    0x29F4,
    0x0001,
    0x2A02,
    0x0000,
};

static u32 l_msg_xy_koukan_item2_CB[] = {
    0x29F5,
    0x0001,
    0x2A03,
    0x0000,
};

static u32* l_msg_xy_koukan_item2[][12] = {
    {
        l_msg_xy_koukan_item2_A0,
        l_msg_xy_koukan_item2_A1,
        l_msg_xy_koukan_item2_A2,
        l_msg_xy_koukan_item2_A3,
        l_msg_xy_koukan_item2_A4,
        l_msg_xy_koukan_item2_A5,
        l_msg_xy_koukan_item2_A6,
        l_msg_xy_koukan_item2_A7,
        l_msg_xy_koukan_item2_A8,
        l_msg_xy_koukan_item2_A9,
        l_msg_xy_koukan_item2_AA,
        l_msg_xy_koukan_item2_AB,
    },
    {
        l_msg_xy_koukan_item2_B0,
        l_msg_xy_koukan_item2_B1,
        l_msg_xy_koukan_item2_B2,
        l_msg_xy_koukan_item2_B3,
        l_msg_xy_koukan_item2_B4,
        l_msg_xy_koukan_item2_B5,
        l_msg_xy_koukan_item2_B6,
        l_msg_xy_koukan_item2_B7,
        l_msg_xy_koukan_item2_B8,
        l_msg_xy_koukan_item2_B9,
        l_msg_xy_koukan_item2_BA,
        l_msg_xy_koukan_item2_BB,
    },
    {
        l_msg_xy_koukan_item2_C0,
        l_msg_xy_koukan_item2_C1,
        l_msg_xy_koukan_item2_C2,
        l_msg_xy_koukan_item2_C3,
        l_msg_xy_koukan_item2_C4,
        l_msg_xy_koukan_item2_C5,
        l_msg_xy_koukan_item2_C6,
        l_msg_xy_koukan_item2_C7,
        l_msg_xy_koukan_item2_C8,
        l_msg_xy_koukan_item2_C9,
        l_msg_xy_koukan_item2_CA,
        l_msg_xy_koukan_item2_CB,
    },
};

static u32 l_msg_xy_koukan_item3_A0[] = {
    0x292E,
    0x2930,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A1[] = {
    0x292E,
    0x2931,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A2[] = {
    0x292E,
    0x2932,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A3[] = {
    0x292E,
    0x2933,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A4[] = {
    0x292E,
    0x2934,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A5[] = {
    0x292E,
    0x2935,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A6[] = {
    0x292E,
    0x2936,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A7[] = {
    0x292E,
    0x2937,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A8[] = {
    0x292E,
    0x2938,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_A9[] = {
    0x292E,
    0x2939,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_AA[] = {
    0x292E,
    0x293A,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_AB[] = {
    0x292E,
    0x293B,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B0[] = {
    0x2992,
    0x2994,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B1[] = {
    0x2992,
    0x2995,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B2[] = {
    0x2992,
    0x2996,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B3[] = {
    0x2992,
    0x2997,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B4[] = {
    0x2992,
    0x2998,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B5[] = {
    0x2992,
    0x2999,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B6[] = {
    0x2992,
    0x299A,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B7[] = {
    0x2992,
    0x299B,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B8[] = {
    0x2992,
    0x299C,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_B9[] = {
    0x2992,
    0x299D,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_BA[] = {
    0x2992,
    0x299E,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_BB[] = {
    0x2992,
    0x299F,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C0[] = {
    0x29F6,
    0x29F8,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C1[] = {
    0x29F6,
    0x29F9,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C2[] = {
    0x29F6,
    0x29FA,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C3[] = {
    0x29F6,
    0x29FB,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C4[] = {
    0x29F6,
    0x29FC,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C5[] = {
    0x29F6,
    0x29FD,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C6[] = {
    0x29F6,
    0x29FE,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C7[] = {
    0x29F6,
    0x29FF,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C8[] = {
    0x29F6,
    0x2A00,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_C9[] = {
    0x29F6,
    0x2A01,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_CA[] = {
    0x29F6,
    0x2A02,
    0x0002,
    0x0000,
};

static u32 l_msg_xy_koukan_item3_CB[] = {
    0x29F6,
    0x2A03,
    0x0002,
    0x0000,
};

static u32* l_msg_xy_koukan_item3[][12] = {
    {
        l_msg_xy_koukan_item3_A0,
        l_msg_xy_koukan_item3_A1,
        l_msg_xy_koukan_item3_A2,
        l_msg_xy_koukan_item3_A3,
        l_msg_xy_koukan_item3_A4,
        l_msg_xy_koukan_item3_A5,
        l_msg_xy_koukan_item3_A6,
        l_msg_xy_koukan_item3_A7,
        l_msg_xy_koukan_item3_A8,
        l_msg_xy_koukan_item3_A9,
        l_msg_xy_koukan_item3_AA,
        l_msg_xy_koukan_item3_AB,
    },
    {
        l_msg_xy_koukan_item3_B0,
        l_msg_xy_koukan_item3_B1,
        l_msg_xy_koukan_item3_B2,
        l_msg_xy_koukan_item3_B3,
        l_msg_xy_koukan_item3_B4,
        l_msg_xy_koukan_item3_B5,
        l_msg_xy_koukan_item3_B6,
        l_msg_xy_koukan_item3_B7,
        l_msg_xy_koukan_item3_B8,
        l_msg_xy_koukan_item3_B9,
        l_msg_xy_koukan_item3_BA,
        l_msg_xy_koukan_item3_BB,
    },
    {
        l_msg_xy_koukan_item3_C0,
        l_msg_xy_koukan_item3_C1,
        l_msg_xy_koukan_item3_C2,
        l_msg_xy_koukan_item3_C3,
        l_msg_xy_koukan_item3_C4,
        l_msg_xy_koukan_item3_C5,
        l_msg_xy_koukan_item3_C6,
        l_msg_xy_koukan_item3_C7,
        l_msg_xy_koukan_item3_C8,
        l_msg_xy_koukan_item3_C9,
        l_msg_xy_koukan_item3_CA,
        l_msg_xy_koukan_item3_CB,
    },
};

static u32 l_msg_xy_koukan_yes[] = {
    0x292E,
    0x2992,
    0x29F6,
};

static u32 l_msg_xy_koukan_no[] = {
    0x292F,
    0x2993,
    0x29F7,
};

static u32 l_msg_xy_koukan_rupee[] = {
    0x293C,
    0x29A0,
    0x2A04,
};

static u32 l_msg_xy_koukan_end[] = {
    0x293D,
    0x29A1,
    0x2A05,
};

static u32 l_msg_xy_koukan_first[] = {
    0x293E,
    0x29A2,
    0x2A06,
};

static u32 l_msg_xy_after_get_demo_A[] = {
    0x293F,
    0x2940,
    0x0000,
};

static u32 l_msg_xy_after_get_demo_B[] = {
    0x29A3,
    0x29A4,
    0x0000,
};

static u32 l_msg_xy_after_get_demo_C[] = {
    0x2A07,
    0x2A08,
    0x0000,
};

static u32* l_msg_xy_after_get_demo[] = {
    l_msg_xy_after_get_demo_A,
    l_msg_xy_after_get_demo_B,
    l_msg_xy_after_get_demo_C,
};

static u32 l_msg_xy_after_get_demo2_A[] = {
    0x2941,
    0x0000,
};

static u32 l_msg_xy_after_get_demo2_B[] = {
    0x29A5,
    0x0000,
};

static u32 l_msg_xy_after_get_demo2_C[] = {
    0x2A09,
    0x0000,
};

static u32* l_msg_xy_after_get_demo2[] = {
    l_msg_xy_after_get_demo2_A,
    l_msg_xy_after_get_demo2_B,
    l_msg_xy_after_get_demo2_C,
};

static u32 l_msg_collect_map[] = {
    0x29A6,
    0x0000
};

static u32 l_msg_try_force[] = {
    0x29A7,
    0x29A8,
    0x29A9,
    0x29AA,
    0x0003,
    0x29AB,
    0x0000
};

static u32 l_get_item_no[] = {
    dItem_HEART_PIECE_e,
};

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
    },
};

static char* l_npc_staff_id[] = {
    "Roten",
    "Roten",
    "Roten",
};

const char daNpcRoten_c::m_arcname[] = "Ro";

static const int l_bmd_ix_tbl[] = {
    RO_BDL_RO,
    RO_BDL_RO,
    RO_BDL_RO,
};

static const int l_bck_ix_tbl[][10] = {
    {
        RO_BCK_RO_WAIT01,
        RO_BCK_RO_TALK01,
        RO_BCK_RO_WALK,
        RO_BCK_RO_TALK02,
        RO_BCK_RO_TALK03,
        RO_BCK_RO_TALK04,
        RO_BCK_RO_TALK05,
        RO_BCK_RO_WATASU,
        RO_BCK_RO_ITEMWAIT,
        RO_BCK_RO_WIND,
    },
    {
        RO_BCK_RO_WAIT01,
        RO_BCK_RO_TALK01,
        RO_BCK_RO_WALK,
        RO_BCK_RO_TALK02,
        RO_BCK_RO_TALK03,
        RO_BCK_RO_TALK04,
        RO_BCK_RO_TALK05,
        RO_BCK_RO_WATASU,
        RO_BCK_RO_ITEMWAIT,
        RO_BCK_RO_WIND,
    },
    {
        RO_BCK_RO_WAIT01,
        RO_BCK_RO_TALK01,
        RO_BCK_RO_WALK,
        RO_BCK_RO_TALK02,
        RO_BCK_RO_TALK03,
        RO_BCK_RO_TALK04,
        RO_BCK_RO_TALK05,
        RO_BCK_RO_WATASU,
        RO_BCK_RO_ITEMWAIT,
        RO_BCK_RO_WIND,
    },
};

static const int l_head_bmd_ix_tbl[] = {
    RO_BDL_RO_HAT,
    RO_BDL_RO_HAT2,
    RO_BDL_RO_HAT3,
};

static const int l_head_bck_ix_tbl[] = {
    RO_BCK_HAT_WID,
    RO_BCK_HAT2_WIND,
    RO_BCK_HAT3_WID,
};

static const int l_btp_ix_tbl[] = {
    RO_BTP_RO,
    RO_BTP_RO,
    RO_BTP_RO,
};

static const int l_bmt_ix_tbl[] = {
    -1,
    RO_BMT_RO2,
    RO_BMT_RO3,
};

static const int l_diff_flag_tbl[] = {
    0x11020022,
    0x37461622,
    0x37461622,
};

struct SaveDatStruct {
    /* 0x00 */ u16 field_0x00;
    /* 0x02 */ u16 field_0x02;
    /* 0x04 */ u16 field_0x04;
    /* 0x06 */ u16 field_0x06;
}; // Size: 0x08

static const SaveDatStruct l_save_dat[] = {
    {
        0x1320,
        0xCB03,
        0xC803,
        0x1304,
    },
    {
        0x1310,
        0xCA03,
        0xC703,
        0x1302,
    },
    {
        0x1308,
        0xC903,
        0xC603,
        0x1301,
    },
};

static const u8 l_item_dat[][12] = {
    {
        0x01,
        0x00,
        0x07,
        0x04,
        0x09,
        0x03,
        0x07,
        0x09,
        0x09,
        0x07,
        0x09,
        0x0A,
    },
    {
        0x01,
        0x02,
        0x01,
        0x0A,
        0x09,
        0x03,
        0x02,
        0x09,
        0x09,
        0x08,
        0x09,
        0x0A,
    },
    {
        0x01,
        0x00,
        0x06,
        0x05,
        0x07,
        0x04,
        0x02,
        0x04,
        0x05,
        0x05,
        0x0B,
        0x0A,
    },
};

/* 00000078-000002F0       .text __ct__12daNpcRoten_cFv */
daNpcRoten_c::daNpcRoten_c() {
    field_0x9BB = 0;
    field_0x98C = NULL;
    field_0x9B2 = 0;
    field_0x990 = 0.0f;
    field_0x9C0 = 0;
    field_0x9C1 = 0;
    field_0x9C4 = 0;
    field_0x99C = 1;
    mShownItemBtn = dItemBtn_NONE_e;
    field_0x9BC = 0;
    field_0x9C6 = 0;
    field_0x9C7 = 0;
    field_0x9C8 = 1;
    field_0x9C9 = 0;
    field_0x9CA = 0;
    field_0x6FC = fpcM_ERROR_PROCESS_ID_e;
    field_0x994 = -1.0f;
}

/* 000007B4-000008CC       .text daNpc_Roten_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Roten_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpcRoten_c* i_this = (daNpcRoten_c*)model->getUserArea();
        
        s32 jntNo = joint->getJntNo();
        cMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);

        if(jntNo == i_this->m_jnt.getHeadJntNum()) {
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getHead_y());
            mDoMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getHead_x());
        }
        if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getBackbone_y());
            mDoMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
    }

    return true;
}

/* 000008CC-000008EC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcRoten_c*>(i_this)->createHeap();
}

/* 000008EC-00000974       .text phase_1__FP12daNpcRoten_c */
static cPhs_State phase_1(daNpcRoten_c* i_this) {
    fopAcM_SetupActor(i_this, daNpcRoten_c);

    i_this->setNpcNo(i_this->getPrmNpcNo());

    if(!dComIfGs_isEventBit(0x1108)) {
        return cPhs_STOP_e;
    }

    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 00000974-000009F4       .text phase_2__FP12daNpcRoten_c */
static cPhs_State phase_2(daNpcRoten_c* i_this) {
    cPhs_State result = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getPrmNpcNo()]);
    if(result == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x4620)) {
            result = i_this->createInit();
        }
        else {
            i_this->mpMorf = NULL;
            return cPhs_ERROR_e;
        }
    }

    return result;
}

/* 000009F4-00000A24       .text _create__12daNpcRoten_cFv */
cPhs_State daNpcRoten_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL
    };

    return dComLbG_PhaseHandler(&mPhs2, l_method, this);
}

/* 00000A24-00000E88       .text createHeap__12daNpcRoten_cFv */
BOOL daNpcRoten_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bmd_ix_tbl[mNpcNo]));
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mNpcNo][field_0x9C0])),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        l_diff_flag_tbl[mNpcNo]
    );

    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }
    
    J3DModelData* headModelData = (J3DModelData*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_head_bmd_ix_tbl[mNpcNo]));
    field_0x6D8 = new mDoExt_McaMorf(
        headModelData,
        NULL, NULL,
        (J3DAnmTransformKey*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_head_bck_ix_tbl[mNpcNo])),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x37441422
    );

    if(field_0x6D8 == NULL || field_0x6D8->getModel() == NULL) {
        return false;
    }

    field_0x6D4 = field_0x6D8->getModel();

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x632, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone1"));
    JUT_ASSERT(0x637, m_jnt.getBackboneJntNum() >= 0);

    if(!initTexPatternAnm(false)) {
        return false;
    }

    m_hand_L_jnt_num = modelData->getJointName()->getIndex("handL");
    JUT_ASSERT(0x63E, m_hand_L_jnt_num >= 0);
    m_bag_jnt_num = modelData->getJointName()->getIndex("Bag1");
    JUT_ASSERT(0x642, m_bag_jnt_num >= 0);

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Roten_nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));

    return true;
}

/* 00000E88-00000EA8       .text daNpcRoten_XyEventCB__FPvi */
static s16 daNpcRoten_XyEventCB(void* i_this, int param_1) {
    return static_cast<daNpcRoten_c*>(i_this)->XyEventCB(param_1);
}

/* 00000EA8-000011C8       .text createInit__12daNpcRoten_cFv */
cPhs_State daNpcRoten_c::createInit() {
    int weight = 0xFF;
    if(getPrmRailID() != 0xFF) {
        mPathRun.setInf(getPrmRailID(), fopAcM_GetRoomNo(this), true);
        if(mPathRun.mPath == NULL) {
            return cPhs_ERROR_e;
        }

        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
        old.pos = point;
        current.pos = old.pos;
        mPathRun.incIdxLoop();
        point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &current.angle.y);
        field_0x9A6 = 1;
        weight = 0xFE;
    }

    gravity = -9.0f;

    field_0x99E = dComIfGp_evmng_getEventIdx("ROTEN_EXCHANGE_1ST");
    field_0x9A0 = dComIfGp_evmng_getEventIdx("ROTEN_EXCHANGE_2ND");
    field_0x9A2 = dComIfGp_evmng_getEventIdx("ROTEN_CHANGE_ITEM");
    field_0x9A4 = dComIfGp_evmng_getEventIdx("ROTEN_GET_MAP");
    mEventCut.setActorInfo2(l_npc_staff_id[mNpcNo], this);
    field_0x9AC = 0;
    field_0x9AE = 0;
    field_0x9B4 = false;
    field_0x9B5 = 0;
    eventInfo.setXyEventCB(daNpcRoten_XyEventCB);

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAA;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAA;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -200.0f, 0.0f, -200.0f, 200.0f, 300.0f, 200.0f);

    mObjAcch.CrrPos(*dComIfG_Bgsp());
    if(-G_CM3D_F_INF != mObjAcch.GetGroundH()) {
        current.pos.y = home.pos.y = mObjAcch.GetGroundH();
    }

    setMtx();
    mpMorf->getModel()->calc();

    mStts.Init(weight, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl2.Set(dNpc_cyl_src);
    mCyl2.SetStts(&mStts);
    setCollision(l_npc_dat[mNpcNo].field_0x2C, 200.0f);
    setCollisionB();
    mSph.Set(l_sph_src);
    mSph.SetStts(&mStts);

    return cPhs_COMPLEATE_e;
}

/* 000011C8-0000122C       .text _delete__12daNpcRoten_cFv */
bool daNpcRoten_c::_delete() {
    dComIfG_resDelete(getPhaseP(), l_arcname_tbl[mNpcNo]);
    if(heap && mpMorf) {
        mpMorf->stopZelAnime();
    }

    return true;
}

/* 0000122C-000013F8       .text _draw__12daNpcRoten_cFv */
bool daNpcRoten_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    g_env_light.setLightTevColorType(field_0x6D4, &tevStr);
    mBtpAnm.entry(modelData, field_0x9B8);

    if(l_bmt_ix_tbl[mNpcNo] >= 0) {
        mpMorf->updateDL((J3DMaterialTable*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bmt_ix_tbl[mNpcNo]));
    }
    else {
        mpMorf->updateDL();
    }

    if(field_0x9C8 != 0) {
        field_0x6D4->setBaseTRMtx(pModel->getAnmMtx(m_jnt.getHeadJntNum()));
        field_0x6D8->updateDL();
    }

    mBtpAnm.remove(modelData);

    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );
    if(mShadowId != 0) {
        dComIfGd_addRealShadow(mShadowId, field_0x6D4);
    }

    dSnap_RegistFig(DSNAP_TYPE_ROTEN, this, 1.0f, 1.0f, 1.0f);

    return true;
}

static daNpcRoten_c::InitFunc_t l_execute_init[] = {
    &daNpcRoten_c::executeWaitInit,
    &daNpcRoten_c::executeTalkInit,
    &daNpcRoten_c::executeWalkInit,
    &daNpcRoten_c::executeTurnInit,
    &daNpcRoten_c::executeWindInit,
};

static daNpcRoten_c::MoveFunc_t moveProc[] = {
    &daNpcRoten_c::executeWait,
    &daNpcRoten_c::executeTalk,
    &daNpcRoten_c::executeWalk,
    &daNpcRoten_c::executeTurn,
    &daNpcRoten_c::executeWind,
};

/* 000013F8-00001604       .text _execute__12daNpcRoten_cFv */
bool daNpcRoten_c::_execute() {
    chkAttention();
    checkOrder();

    dBgS* bgs = dComIfG_Bgsp(); // fakematch?

    if(dComIfGp_event_getMode() == dEvtMode_NONE_e || (eventInfo.checkCommandTalk() && (field_0x9B2 & 0x8000) == 0)) {
        (this->*moveProc[field_0x9BB])();
    }
    else {
        eventMove();
    }

    eventOrder();
    playTexPatternAnm();
    playAnm();

    speedF = field_0x990;
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*bgs);
    setCollision(l_npc_dat[mNpcNo].field_0x2C, 200.0f);
    setCollisionH();

    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x1C, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x28, current.pos.z);
    if(field_0x9C7) {
        m_jnt.setParam(0, 0, 0, 0, l_npc_dat[mNpcNo].field_0x04, l_npc_dat[mNpcNo].field_0x08, l_npc_dat[mNpcNo].field_0x0C, l_npc_dat[mNpcNo].field_0x10, l_npc_dat[mNpcNo].field_0x14);
    }
    else {
        m_jnt.setParam(l_npc_dat[mNpcNo].field_0x06, l_npc_dat[mNpcNo].field_0x0A, l_npc_dat[mNpcNo].field_0x0E, l_npc_dat[mNpcNo].field_0x12, l_npc_dat[mNpcNo].field_0x04, l_npc_dat[mNpcNo].field_0x08, l_npc_dat[mNpcNo].field_0x0C, l_npc_dat[mNpcNo].field_0x10, l_npc_dat[mNpcNo].field_0x14);
    }

    lookBack();
    setCollisionB();
    setMtx();

    return false;
}

/* 00001604-00001674       .text executeCommon__12daNpcRoten_cFv */
bool daNpcRoten_c::executeCommon() {
    if(field_0x9B6 != 0 && field_0x9BB != 4) {
        field_0x9B7 = 1;
    }
    else {
        field_0x9B7 = 0;
    }

    if(field_0x9B4 == true) {
        executeSetMode(1);
    }

    return field_0x9B4;
}

/* 00001674-000016C8       .text executeSetMode__12daNpcRoten_cFUc */
void daNpcRoten_c::executeSetMode(u8 param_1) {
    field_0x990 = 0.0f;
    field_0x9BB = (this->*l_execute_init[param_1])();
}

/* 000016C8-00001790       .text executeWaitInit__12daNpcRoten_cFv */
s32 daNpcRoten_c::executeWaitInit() {
    setAnmTbl(l_npc_anm_wait);
    field_0x9A6 = l_npc_dat[mNpcNo].field_0x4C + cM_rndF(l_npc_dat[mNpcNo].field_0x4E - l_npc_dat[mNpcNo].field_0x4C);

    return 0;
}

/* 00001790-00001808       .text executeWait__12daNpcRoten_cFv */
void daNpcRoten_c::executeWait() {
    if(!executeCommon() && mPathRun.mPath != NULL && field_0x9A6 && !field_0x9B5) {
        field_0x9A6--;
        if(field_0x9A6 == 0) {
            executeSetMode(3);
        }
    }
}

/* 00001808-00001810       .text executeTalkInit__12daNpcRoten_cFv */
s32 daNpcRoten_c::executeTalkInit() {
    return 1;
}

/* 00001810-000018E0       .text executeTalk__12daNpcRoten_cFv */
void daNpcRoten_c::executeTalk() {
    executeCommon();
    if(!dComIfGp_event_chkTalkXY() || dComIfGp_evmng_ChkPresentEnd()) {
        if(talk(1) == fopMsgStts_BOX_CLOSED_e) {
            field_0x9B4 = 0;
            executeSetMode(0);
            dComIfGp_event_reset();
            field_0x9B2 &= ~0x4000;
            field_0x9C6 = 0;
        }
        else {
            setAnmFromMsgTag();
        }
    }
}

/* 000018E0-000019A8       .text executeWalkInit__12daNpcRoten_cFv */
s32 daNpcRoten_c::executeWalkInit() {
    setAnmTbl(l_npc_anm_walk);
    field_0x9A6 = l_npc_dat[mNpcNo].field_0x50 + cM_rndF(l_npc_dat[mNpcNo].field_0x52 - l_npc_dat[mNpcNo].field_0x50);

    return 2;
}

/* 000019A8-00001B54       .text executeWalk__12daNpcRoten_cFv */
void daNpcRoten_c::executeWalk() {
    if(!executeCommon()) {
        bool temp = false;
        if(mPathRun.chkPointPass(current.pos, mPathRun.mbGoingForwards) && !mPathRun.nextIdxAuto()) {
            temp = true;
        }

        if(field_0x9B5 != 0) {
            executeSetMode(0);
        }
        else if(!temp) {
            cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
            s16 angle;
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
            field_0x9B0 = angle;
            field_0x99C = 0;
            field_0x9AC = l_npc_dat[mNpcNo].field_0x18;
            field_0x9C4 = 2;
            m_jnt.setTrn();
            field_0x990 = l_npc_dat[mNpcNo].field_0x44;
            if(field_0x9A6 != 0) {
                field_0x9A6--;
                if(field_0x9A6 == 0) {
                    executeSetMode(0);
                }
            }
        }
        else {
            mPathRun.mbGoingForwards ^= 1;
            executeSetMode(0);
        }
    }
}

/* 00001B54-00001C98       .text executeTurnInit__12daNpcRoten_cFv */
s32 daNpcRoten_c::executeTurnInit() {
    int ret = 3;

    cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    if(angle == current.angle.y) {
        ret = 2;

        setAnmTbl(l_npc_anm_walk);
        field_0x9A6 = l_npc_dat[mNpcNo].field_0x50 + cM_rndF(l_npc_dat[mNpcNo].field_0x52 - l_npc_dat[mNpcNo].field_0x50);\
    }

    return ret;
}

/* 00001C98-00001D5C       .text executeTurn__12daNpcRoten_cFv */
void daNpcRoten_c::executeTurn() {
    if(!executeCommon()) {
        cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        field_0x9B0 = angle;
        field_0x99C = 0;
        field_0x9C4 = 2;
        if(!m_jnt.trnChk()) {
            executeSetMode(2);
        }
    }
}

/* 00001D5C-00001E00       .text executeWindInit__12daNpcRoten_cFv */
s32 daNpcRoten_c::executeWindInit() {
    setAnmTbl(l_npc_anm_wind);
    J3DAnmTransform* pAnmRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_head_bck_ix_tbl[mNpcNo]));
    field_0x6D8->setAnm(pAnmRes, J3DFrameCtrl::EMode_NONE, 14.0f, 1.0f, 0.0f, 39.0f, NULL);

    return 4;
}

/* 00001E00-00001E68       .text executeWind__12daNpcRoten_cFv */
void daNpcRoten_c::executeWind() {
    if(!executeCommon()) {
        field_0x6D8->play(NULL, 0, 0);

        if(field_0x9C1 & 1) {
            executeSetMode(0);
            field_0x9CA = 0;
        }
    }
}

/* 00001E68-00001FA0       .text checkOrder__12daNpcRoten_cFv */
void daNpcRoten_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(field_0x99E) && field_0x9B7 == 3) {
            field_0x9B7 = 0;
        }
        else if(dComIfGp_evmng_startCheck(field_0x9A0) && field_0x9B7 == 4) {
            field_0x9B7 = 0;
        }
        else if(dComIfGp_evmng_startCheck(field_0x9A2) && field_0x9B7 == 5) {
            field_0x9B7 = 0;
        }
        else if(dComIfGp_evmng_startCheck(field_0x9A4) && field_0x9B7 == 6) {
            field_0x9B7 = 0;
        }
    }
    else if(eventInfo.checkCommandTalk() && (field_0x9B7 == 2 || field_0x9B7 == 1) && field_0x9B4 == false) {
        field_0x9B4 = true;
        field_0x990 = 0.0f;
        field_0x9C6 = 1;
    }
}

/* 00001FA0-0000211C       .text eventOrder__12daNpcRoten_cFv */
void daNpcRoten_c::eventOrder() {
    if(field_0x9B7 == 2 || field_0x9B7 == 1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(dComIfGs_isEventBit(l_save_dat[mNpcNo].field_0x00)) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }

        if(field_0x9B7 == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(field_0x9B7 == 3) {
        fopAcM_orderOtherEventId(this, field_0x99E, 0xFF, 0xFF7F);
        field_0x9B2 |= 0x4000;
    }
    else if(field_0x9B7 == 4) {
        fopAcM_orderOtherEventId(this, field_0x9A0, 0xFF, 0xFF7F);
        field_0x9B2 |= 0x4000;
    }
    else if(field_0x9B7 == 5) {
        fopAcM_orderOtherEventId(this, field_0x9A2, 0xFF, 0xFF7F);
        field_0x9B2 |= 0x4000;
    }
    else if(field_0x9B7 == 6) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, field_0x9A4, 0, 0xFFFF);
        field_0x9B2 |= 0x4000;
        dComIfGs_setReserveItemEmpty();
    }
}

/* 0000211C-00002314       .text eventMove__12daNpcRoten_cFv */
void daNpcRoten_c::eventMove() {
    if(field_0x9B2 & 0x4000) {
        if(dComIfGp_evmng_endCheck(field_0x99E)) {
            dComIfGp_event_reset();
            field_0x9B2 &= ~0xC000;
            executeSetMode(0);
            field_0x9B4 = 0;

            if(field_0x9B2 & 8) {
                field_0x9B7 = 2;
                eventOnPlrInit();
            }
            else {
                field_0x9B7 = 4;
            }
        }
        else if(dComIfGp_evmng_endCheck(field_0x9A0)) {
            dComIfGp_event_reset();
            field_0x9B2 &= ~0x4000;
            executeSetMode(0);
            if(field_0x9B2 & 0x40) {
                field_0x9B2 &= ~0x40;
                eventOnPlrInit();
            }
            else if(field_0x9B2 & 0x30) {
                field_0x9B7 = 2;
                eventOnPlrInit();
            }
            else {
                field_0x9B7 = 5;
            }
        }
        else if(dComIfGp_evmng_endCheck(field_0x9A2)) {
            field_0x9C6 = 0;
            dComIfGp_event_reset();
            field_0x9B2 &= ~0x4000;
            executeSetMode(0);
        }
        else if(dComIfGp_evmng_endCheck(field_0x9A4)) {
            field_0x9B4 = 0;
            field_0x9C6 = 0;
            dComIfGp_event_reset();
            field_0x9B2 &= ~0xC000;
            executeSetMode(0);
        }
        else {
            bool oldFlag = mEventCut.getAttnFlag();
            if(mEventCut.cutProc()) {
                if(!mEventCut.getAttnFlag()) {
                    mEventCut.setAttnFlag(oldFlag);
                }
            }
            else {
                privateCut();
                setAnmFromMsgTag();
            }
        }
    }
    
}

/* 00002314-000025FC       .text privateCut__12daNpcRoten_cFv */
void daNpcRoten_c::privateCut() {
    static char* cut_name_tbl[] = {
        "INIT",
        "MES_SET",
        "SET_ITEM",
        "CLR_ITEM",
        "GET_ITEM",
        "SET_ANGLE",
        "ON_PLR",
        "OFF_PLR",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo]);
    if(staffIdx != -1) {
        field_0x9C3 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0);
        if(field_0x9C3 == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }

        if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch(field_0x9C3) {
                case 0:
                    eventInit();
                    break;
                case 1:
                    eventMesSetInit(staffIdx);
                    break;
                case 2:
                    eventSetItemInit();
                    break;
                case 3:
                    eventClrItemInit();
                    break;
                case 4:
                    eventGetItemInit(staffIdx);
                    break;
                case 5:
                    eventSetAngleInit();
                    break;
                case 6:
                    eventOnPlrInit();
                    break;
                case 7:
                    eventOffPlrInit();
                    break;
            }
        }
        
        bool temp;
        switch(field_0x9C3) {
            case 1:
                temp = eventMesSet();
                break;
            case 2:
                temp = eventSetItem();
                break;
            default:
                temp = true;
        }

        if(temp) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }

        daDitem_c* pItem;
        if (fopAcM_SearchByID(field_0x6F8, (fopAc_ac_c**)&pItem) && pItem) {
            if(field_0x9C0 == 7 && (s16)mpMorf->getFrame() >= 0x3C) {
                cMtx_copy(mpMorf->getModel()->getAnmMtx(m_hand_L_jnt_num), *calc_mtx);
                mDoMtx_stack_c::transS(20.0f, -30.0f, -30.0f);
                cMtx_concat(*calc_mtx, mDoMtx_stack_c::get(), *calc_mtx);

                cXyz offset;
                mDoMtx_multVecZero(*calc_mtx, &offset);
                pItem->setOffsetPos(offset);
                pItem->show();
                field_0x714 = offset;
            }
            else if(field_0x9C0 == 8) {
                field_0x708 = field_0x714;
                field_0x99C = 1;
                field_0x9C4 = 1;
                field_0x9C6 = 0;
                field_0x9C7 = 1;
            }
        }
    }
}

/* 000025FC-00002600       .text eventInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventInit() {
    return;
}

/* 00002600-0000280C       .text eventMesSetInit__12daNpcRoten_cFi */
void daNpcRoten_c::eventMesSetInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(pData) {
        u32 msgNo = *pData;
        switch(msgNo) {
            case 0x0:
                field_0x98C = l_msg_xy_koukan_item[mNpcNo][field_0x9BE];
                setMessage(field_0x98C[0]);
                dComIfGs_onEventBit(l_save_dat[mNpcNo].field_0x06);
                break;
            case 0x1:
                field_0x98C = l_msg_xy_koukan_item2[mNpcNo][field_0x9BE];
                setMessage(field_0x98C[0]);
                break;
            case 0xA:
                field_0x98C = l_msg_xy_koukan_item3[mNpcNo][field_0x9BE];
                setMessage(field_0x98C[0]);
                break;
            case 0x14:
                field_0x98C = l_msg_xy_after_get_demo[mNpcNo];
                setMessage(field_0x98C[0]);
                break;
            case 0x15:
                field_0x98C = l_msg_xy_after_get_demo2[mNpcNo];
                setMessage(field_0x98C[0]);
                break;
            case 0x63:
                setMessage(getMsg());
                break;
            default:
                setMessage(msgNo);
                break;
        }
    }
    else {
        field_0x98C = &field_0x98C[1];
        setMessage(field_0x98C[0]);
    }
}

/* 0000280C-00002840       .text eventMesSet__12daNpcRoten_cFv */
bool daNpcRoten_c::eventMesSet() {
    return talk(0) == fopMsgStts_BOX_CLOSED_e;
}

/* 00002840-000028C4       .text eventSetItemInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventSetItemInit() {
    u8 itemIdx = l_item_dat[mNpcNo][field_0x9BE];
    cXyz pos(0.0f, 0.0f, 0.0f);
    u8 itemNo = itemIdx + FLOWER_1;
    field_0x6F8 = fopAcM_createItemForPresentDemo(&pos, itemNo, daDitem_c::FLAG_UNK01 | daDitem_c::FLAG_UNK08, -1, fopAcM_GetRoomNo(this));
}

/* 000028C4-0000290C       .text eventSetItem__12daNpcRoten_cFv */
bool daNpcRoten_c::eventSetItem() {
    fopAc_ac_c* pActor;
    if(fopAcM_SearchByID(field_0x6F8, &pActor)) {
        if(pActor) {
            return true;
        }

        return false;
    }

    return true;
}

/* 0000290C-00002978       .text eventClrItemInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventClrItemInit() {
    daDitem_c* pItem;
    if(fopAcM_SearchByID(field_0x6F8, (fopAc_ac_c**)&pItem) && pItem != NULL) {
        pItem->dead();
    }

    field_0x9C6 = 1;
    field_0x9C7 = 0;
    setAnmTbl(l_npc_anm_wait);
}

/* 00002978-00002A70       .text eventGetItemInit__12daNpcRoten_cFi */
void daNpcRoten_c::eventGetItemInit(int staffIdx) {
    fpc_ProcID pcId;

    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "ItemNo");
    if(pData != NULL) {
        u32 itemNo = *pData; // fakematch?
        itemNo = l_get_item_no[itemNo];
        pcId = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, fopAcM_GetRoomNo(this));
    }
    else {
        u8 temp = l_item_dat[mNpcNo][field_0x9BE];
        u32 itemIdx = temp; // fakematch?
        dComIfGs_onGetItemReserve(temp);

        u8 itemNo = FLOWER_1;
        itemNo += itemIdx; // fakematch?
        pcId = fopAcM_createItemForPresentDemo(&current.pos, itemNo, daDitem_c::FLAG_UNK01, -1, fopAcM_GetRoomNo(this));
    }

    if(pcId != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(pcId);
    }
}

/* 00002A70-00002AD4       .text eventSetAngleInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventSetAngleInit() {
    daPy_lk_c* player = daPy_getPlayerLinkActorClass();
    cXyz delta = current.pos - player->current.pos;
    player->changeDemoMoveAngle(cM_atan2s(delta.x, delta.z));
}

/* 00002AD4-00002AF0       .text eventOnPlrInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventOnPlrInit() {
    daPy_getPlayerLinkActorClass()->offPlayerNoDraw();
}

/* 00002AF0-00002B0C       .text eventOffPlrInit__12daNpcRoten_cFv */
void daNpcRoten_c::eventOffPlrInit() {
    daPy_getPlayerLinkActorClass()->onPlayerNoDraw();
}

/* 00002B0C-00002D5C       .text next_msgStatus__12daNpcRoten_cFPUl */
u16 daNpcRoten_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;

    switch(*pMsgNo) {
        case 0x293D:
        case 0x29A1:
        case 0x2A05:
            status = fopMsgStts_MSG_ENDS_e;
            break;
        default:
            if(field_0x98C) {
                field_0x98C = &field_0x98C[1];
                switch(field_0x98C[0]) {
                    case 0:
                        field_0x98C = NULL;
                        status = fopMsgStts_MSG_ENDS_e;
                        break;
                    case 1:
                        if(mpCurrMsg->mSelectNum != 0) {
                            field_0x9B2 |= 8;
                        }

                        field_0x98C = NULL;
                        status = fopMsgStts_MSG_ENDS_e;
                        break;
                    case 2:
                        if(mpCurrMsg->mSelectNum == 0) {
                            if(dComIfGs_getRupee() < dComIfGp_getMessageRupee()) {
                                field_0x9B2 |= 0x20;
                                field_0x98C = NULL;
                                status = fopMsgStts_MSG_ENDS_e;
                                break;
                            }

                            dComIfGp_setItemRupeeCount(-dComIfGp_getMessageRupee());
                            u8 temp = l_item_dat[mNpcNo][field_0x9BE];
                            u8 temp2 = dComIfGs_getEventReg(l_save_dat[mNpcNo].field_0x02);
                            dComIfGs_setEventReg(l_save_dat[mNpcNo].field_0x02, temp2 + 1);
                            if(dComIfGs_isGetItemReserve(temp)) {
                                *pMsgNo = l_msg_xy_koukan_end[mNpcNo];
                                field_0x9B2 |= 0x40;
                            }
                            else {
                                *pMsgNo = l_msg_xy_koukan_first[mNpcNo];
                            }

                            dComIfGs_setReserveItemChange(mShownItemBtn, temp + FLOWER_1);
                            field_0x98C = NULL;
                            break;
                        }
                        else {
                            field_0x9B2 |= 0x10;
                            field_0x98C = NULL;
                            status = fopMsgStts_MSG_ENDS_e;
                            break;
                        }

                        field_0x98C = NULL;
                        status = fopMsgStts_MSG_ENDS_e;
                        break;
                    case 3:
                        status = fopMsgStts_MSG_ENDS_e;
                        break;
                    default:
                        *pMsgNo = field_0x98C[0];
                        break;
                }
            }
            else {
                status = fopMsgStts_MSG_ENDS_e;
            }

            break;
    }

    return status;
}

/* 00002D5C-000030C0       .text getMsg__12daNpcRoten_cFv */
u32 daNpcRoten_c::getMsg() {
    u32 msgNo = 0;

    field_0x98C = NULL;
    if(field_0x9B2 & 8) {
        field_0x9B2 &= ~0x0008;
        msgNo = l_msg_xy_koukan_no[mNpcNo];
    }
    else if(field_0x9B2 & 0x10) {
        field_0x9B2 &= ~0x0010;
        msgNo = l_msg_xy_koukan_no[mNpcNo];
    }
    else if(field_0x9B2 & 0x20) {
        field_0x9B2 &= ~0x0020;
        msgNo = l_msg_xy_koukan_rupee[mNpcNo];
    }
    else if(dComIfGp_event_chkTalkXY()) {
        int itemNo = dComIfGp_event_getPreItemNo();
        if(isGetMap(itemNo)) {
            field_0x98C = l_msg_try_force;
            dComIfGs_setReserveItemEmpty();
            dComIfGs_onEventBit(0x3E04);
        }
        else if(dComIfGs_getEventReg(l_save_dat[mNpcNo].field_0x02) >= 3) {
            field_0x98C = l_msg_xy_exchange3[mNpcNo];
        }
        else if(!isHaitatuItem(itemNo)) {
            field_0x98C = l_msg_xy_no_roten_item[mNpcNo];
        }
        else if(!isKoukanItem(itemNo)) {
            field_0x98C = l_msg_xy_invalid_item[mNpcNo];
        }
        else {
            field_0x9BE = itemNo - FLOWER_1;
            field_0x98C = l_msg_xy_koukan_item[mNpcNo][field_0x9BE];
            dComIfGs_onEventBit(l_save_dat[mNpcNo].field_0x06);
        }
    }
    else {
        if(!dComIfGs_isEventBit(l_save_dat[mNpcNo].field_0x00)) {
            field_0x98C = l_msg_1st_talk[mNpcNo];
            dComIfGs_onEventBit(l_save_dat[mNpcNo].field_0x00);
        }
        else if(dComIfGs_getEventReg(l_save_dat[mNpcNo].field_0x02) >= 3) {
            field_0x98C = l_msg_exchange3[mNpcNo];
        }
        else if(mNpcNo == 1 && dComIfGs_isEventBit(0x3E04)) {
            field_0x98C = l_msg_collect_map;
        }
        else if(dComIfGs_isEventBit(l_save_dat[mNpcNo].field_0x06)) {
            field_0x98C = l_msg_exchange[mNpcNo];
        }
        else {
            field_0x98C = l_msg_etc[mNpcNo];
        }
    }

    if(field_0x98C) {
        msgNo = field_0x98C[0];
    }

    return msgNo;
}

/* 000030C0-000030D0       .text setMessage__12daNpcRoten_cFUl */
void daNpcRoten_c::setMessage(u32 msgNo) {
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mCurrMsgNo = msgNo;
}

/* 000030D0-00003198       .text setAnmFromMsgTag__12daNpcRoten_cFv */
void daNpcRoten_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(l_npc_anm_talk);
            break;
        case 2:
            setAnmTbl(l_npc_anm_talk2);
            break;
        case 3:
            setAnmTbl(l_npc_anm_talk3);
            break;
        case 4:
            setAnmTbl(l_npc_anm_walk);
            break;
        case 5:
            setAnmTbl(l_npc_anm_watasu);
            break;
        case 6:
            setAnmTbl(l_npc_anm_itemwait);
            break;
        case 7:
            setAnmTbl(l_npc_anm_talk4);
            break;
        case 8:
            setAnmTbl(l_npc_anm_talk5);
            break;
    }

    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 00003198-000031C4       .text getPrmNpcNo__12daNpcRoten_cFv */
u8 daNpcRoten_c::getPrmNpcNo() {
    return daObj::PrmAbstract(this, PRM_NPC_NO_W, PRM_NPC_NO_S);
}

/* 000031C4-000031F0       .text getPrmRailID__12daNpcRoten_cFv */
u8 daNpcRoten_c::getPrmRailID() {
    return daObj::PrmAbstract(this, PRM_RAIL_ID_W, PRM_RAIL_ID_S);
}

/* 000031F0-00003278       .text setMtx__12daNpcRoten_cFv */
void daNpcRoten_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003278-00003558       .text chkAttention__12daNpcRoten_cFv */
void daNpcRoten_c::chkAttention() {
    if(mEventCut.getAttnFlag()) {
        field_0x708 = mEventCut.getAttnPos();
        field_0x9C4 = 1;
        if(field_0x9C6 != 0) {
            field_0x99C = 0;
            m_jnt.setTrn();
        }
        else {
            field_0x99C = 1;
        }

        if(field_0x9B5 == 0) {
            field_0x9B5 = 1;
            field_0x9B6 = 1;
        }
    }
    else {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);

        f32 temp = l_npc_dat[mNpcNo].field_0x24;
        int temp2 = l_npc_dat[mNpcNo].field_0x20;
        int temp3 = 0x4000;
        if(field_0x9B4 != 0) {
            temp3 = 0x7FFF;
        }
        f32 temp4;
        s16 temp5;

        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &temp4, &temp5);
        if(field_0x9B5 != 0) {
            temp += 40.0f;
            temp2 += 0x071C;
        }

        temp5 -= current.angle.y;
        if(temp > temp4 && field_0x9CA == 0 && temp3 > abs(temp5)) {
            field_0x708 = dNpc_playerEyePos(l_npc_dat[mNpcNo].field_0x00);
            field_0x9C4 = 1;
            if(field_0x9C6 != 0) {
                field_0x99C = 0;
            }
            else {
                field_0x99C = 1;
            }

            if(field_0x9B5 == 0) {
                field_0x9B5 = 1;
            }

            field_0x9B6 = 1;
        }
        else if(temp > temp4 && field_0x9CA == 0 && temp2 > abs(temp5)) {
            if(field_0x9B6 == 0) {
                field_0x9B6 = 1;
            }

            if(field_0x9B5 == 1) {
                field_0x9B5 = 0;
                field_0x9A8 = 0x1E;
            }
        }
        else {
            if(field_0x9B5 == 1) {
                field_0x9B5 = 0;
                field_0x9A8 = 0x1E;
            }

            field_0x9B6 = 0;
            field_0x9C4 = 0;

            if(mPathRun.mPath == NULL) {
                if(field_0x9A8 != 0) {
                    field_0x9A8--;
                }
                else {
                    field_0x9B0 = home.angle.y;
                    field_0x99C = 0;
                    field_0x9C4 = 2;
                    m_jnt.setTrn();
                }
            }
        }
    }

    field_0x9AC = l_npc_dat[mNpcNo].field_0x16;
}

/* 00003558-000036A4       .text lookBack__12daNpcRoten_cFv */
void daNpcRoten_c::lookBack() {
    cXyz temp4;
    s16 temp1 = field_0x9AC;
    s16 targetY = current.angle.y;
    cXyz* dstPos = NULL;
    cXyz temp2 = eyePos;
    bool temp3 = field_0x99C;

    switch(field_0x9C4) {
        case 0:
            break;
        case 1:
            temp4 = field_0x708;
            dstPos = &temp4;
            break;
        case 2:
            targetY = field_0x9B0;
            break;
    }

    if(field_0x9B4 != 0 && field_0x9C6 != 0) {
        temp3 = false;
        m_jnt.setTrn();
    }

    if(m_jnt.trnChk()) {
        s16 speed = mEventCut.getTurnSpeed();
        if(speed != 0) {
            temp1 = speed;
        }

        cLib_addCalcAngleS2(&field_0x9AE, temp1, 4, 0x800);
    }
    else {
        field_0x9AE = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp2, targetY, field_0x9AE, temp3);
    shape_angle = current.angle;
}

/* 000036A4-000037BC       .text initTexPatternAnm__12daNpcRoten_cFb */
BOOL daNpcRoten_c::initTexPatternAnm(bool modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_btp_ix_tbl[mNpcNo]));
    JUT_ASSERT(0xBFF, m_head_tex_pattern != NULL);

    if(!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP,  1.0f, 0, -1, modify, FALSE)) {
        return false;
    }

    field_0x9B8 = 0;
    field_0x9AA = 0;
    return true;
}

/* 000037BC-00003828       .text playTexPatternAnm__12daNpcRoten_cFv */
void daNpcRoten_c::playTexPatternAnm() {
    if(cLib_calcTimer(&field_0x9AA) == 0) {
        if(field_0x9B8 >= m_head_tex_pattern->getFrameMax()) {
            field_0x9B8 -= m_head_tex_pattern->getFrameMax();
            field_0x9AA = 0x78;
        }
        else {
            field_0x9B8++;
        }
    }
}

/* 00003828-000038E4       .text playAnm__12daNpcRoten_cFv */
void daNpcRoten_c::playAnm() {
    if(mpMorf->play(NULL, 0, 0) && field_0x988 && field_0x9C2 > 0) {
        field_0x9C2--;

        if(field_0x9C2 == 0) {
            field_0x988++;
            if(setAnmTbl(field_0x988)) {
                field_0x9C1 |= 1;
            }
        }
        else {
            setAnm(field_0x988->field_0x00, 0, 0.0f);
        }
    }
}

/* 000038E4-000039C8       .text setAnm__12daNpcRoten_cFUcif */
void daNpcRoten_c::setAnm(u8 param_1, int param_2, f32 param_3) {
    if(field_0x994 >= 0.0f) {
        param_3 = field_0x994;
        field_0x994 = -1.0f;
    }

    J3DAnmTransform* pAnmRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mNpcNo][param_1]));
    mpMorf->setAnm(pAnmRes, param_2, param_3, 1.0f, 0.0f, -1.0f, NULL);
    field_0x9C0 = param_1;
    field_0x998 = param_2;
}

/* 000039C8-00003A80       .text setAnmTbl__12daNpcRoten_cFP12sRotenAnmDat */
bool daNpcRoten_c::setAnmTbl(sRotenAnmDat* param_1) {
    field_0x9C1  &= ~0x1;
    if(param_1->field_0x00 == 0xFF) {
        field_0x988 = 0;
        return true;
    }

    field_0x988 = param_1;
    field_0x9C2 = field_0x988->field_0x02;
    int temp = 2;
    if(field_0x9C2 > 0) {
        temp = 0;
    }
    if(field_0x9C0 != field_0x988->field_0x00 || temp == 0 || field_0x998 == 0) {
        setAnm(field_0x988->field_0x00, temp, field_0x988->field_0x01);
    }

    return false;
}

/* 00003A80-00003AA4       .text isHaitatuItem__12daNpcRoten_cFUc */
BOOL daNpcRoten_c::isHaitatuItem(u8 itemNo) {
    return FLOWER_1 <= itemNo && itemNo <= XXX_039;
}

/* 00003AA4-00003AC8       .text isKoukanItem__12daNpcRoten_cFUc */
BOOL daNpcRoten_c::isKoukanItem(u8 itemNo) {
    return FLOWER_1 <= itemNo && itemNo <= PRESIDENT_STATUE;
}

/* 00003AC8-00003B30       .text isGetMap__12daNpcRoten_cFUc */
BOOL daNpcRoten_c::isGetMap(u8 itemNo) {
    if(mNpcNo == 1 && !dComIfGs_isEventBit(0x3E04) && itemNo == PRESIDENT_STATUE) {
        return true;
    }

    return false;
}

/* 00003B30-00003C7C       .text XyEventCB__12daNpcRoten_cFi */
s16 daNpcRoten_c::XyEventCB(int i_itemBtn) {
    s16 eventIdx;

    int itemNo = dComIfGp_getSelectItem(i_itemBtn);
    field_0x9BE = itemNo - FLOWER_1;
    if(isKoukanItem(itemNo) && dComIfGs_getEventReg(l_save_dat[mNpcNo].field_0x02) < 3 && !isGetMap(itemNo)) {
        if(dComIfGp_event_getTalkXYBtn() == dTalkBtn_X_e) {
            mShownItemBtn = dItemBtn_X_e;
        }
        else if(dComIfGp_event_getTalkXYBtn() == dTalkBtn_Y_e) {
            mShownItemBtn = dItemBtn_Y_e;
        }
        else if(dComIfGp_event_getTalkXYBtn() == dTalkBtn_Z_e) {
            mShownItemBtn = dItemBtn_Z_e;
        }
        else {
            mShownItemBtn = dItemBtn_NONE_e;
        }

        eventIdx = field_0x99E;
        field_0x9B2 |= 0xC000;
    }
    else {
        if(isGetMap(itemNo)) {
            eventIdx = field_0x9A4;
            field_0x9B2 |= 0xC000;
        }
        else {
            eventIdx = dComIfGp_evmng_getEventIdx("DEFAULT_TALK_XY");
        }
    }

    return eventIdx;
}

/* 00003C7C-00003DD4       .text setCollisionB__12daNpcRoten_cFv */
void daNpcRoten_c::setCollisionB() {
    MtxP pMtx = mpMorf->getModel()->getAnmMtx(m_bag_jnt_num);

    cXyz temp;
    mDoMtx_multVecZero(pMtx, &temp);
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, temp, NULL, &angle);

    temp.x += l_npc_dat[mNpcNo].field_0x34 * cM_ssin(angle);
    temp.y = current.pos.y;
    temp.z += l_npc_dat[mNpcNo].field_0x34 * cM_scos(angle);

    mCyl2.SetC(temp);
    mCyl2.SetR(l_npc_dat[mNpcNo].field_0x30);
    mCyl2.SetH(200.0f);
    dComIfG_Ccsp()->Set(&mCyl2);
}

/* 00003DD4-00003F08       .text setCollisionH__12daNpcRoten_cFv */
void daNpcRoten_c::setCollisionH() {
    cMtx_copy(mpMorf->getModel()->getAnmMtx(m_jnt.getHeadJntNum()), *calc_mtx);
    mDoMtx_stack_c::transS(l_npc_dat[mNpcNo].field_0x3C, 0.0f, 0.0f);
    cMtx_concat(*calc_mtx, mDoMtx_stack_c::get(), *calc_mtx);

    cXyz temp;
    mDoMtx_multVecZero(*calc_mtx, &temp);

    mSph.SetC(temp);
    mSph.SetR(l_npc_dat[mNpcNo].field_0x38);
    dComIfG_Ccsp()->Set(&mSph);
    if(field_0x9CA == 0 && mSph.ChkTgHit()) {
        executeSetMode(4);
        field_0x9CA = 1;
    }
}

/* 00003F08-00003F28       .text daNpc_RotenCreate__FPv */
static s32 daNpc_RotenCreate(void* i_this) {
    return static_cast<daNpcRoten_c*>(i_this)->_create();
}

/* 00003F28-00003F4C       .text daNpc_RotenDelete__FPv */
static BOOL daNpc_RotenDelete(void* i_this) {
    return static_cast<daNpcRoten_c*>(i_this)->_delete();
}

/* 00003F4C-00003F70       .text daNpc_RotenExecute__FPv */
static BOOL daNpc_RotenExecute(void* i_this) {
    return static_cast<daNpcRoten_c*>(i_this)->_execute();
}

/* 00003F70-00003F94       .text daNpc_RotenDraw__FPv */
static BOOL daNpc_RotenDraw(void* i_this) {
    return static_cast<daNpcRoten_c*>(i_this)->_draw();
}

/* 00003F94-00003F9C       .text daNpc_RotenIsDelete__FPv */
static BOOL daNpc_RotenIsDelete(void*) {
    return true;
}

static actor_method_class daNpc_RotenMethodTable = {
    (process_method_func)daNpc_RotenCreate,
    (process_method_func)daNpc_RotenDelete,
    (process_method_func)daNpc_RotenExecute,
    (process_method_func)daNpc_RotenIsDelete,
    (process_method_func)daNpc_RotenDraw,
};

actor_process_profile_definition g_profile_NPC_ROTEN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_ROTEN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcRoten_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_ROTEN,
    /* Actor SubMtd */ &daNpc_RotenMethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
