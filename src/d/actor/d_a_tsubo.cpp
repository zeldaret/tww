/**
 * d_a_tsubo.cpp
 * Small, carriable objects (pots, skulls, etc.)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tsubo.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/actor/d_a_obj_eff.h"
#include "d/res/res_always.h"
#include "d/res/res_kmtub_00.h"
#include "d/res/res_ktaru_01.h"
#include "d/res/res_okmono.h"
#include "d/res/res_odokuro.h"
#include "d/res/res_okioke.h"
#include "d/res/res_sitem.h"
#include "d/res/res_kmi00x.h"
#include "d/res/res_hbox2.h"
#include "d/res/res_hseki.h"
#include "d/res/res_ptubo.h"
#include "d/res/res_kkiba_00.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_camera.h"
#include "d/d_lib.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_kankyo_mng.h"

namespace daTsubo {

#if VERSION == VERSION_DEMO
dBgS_ObjGndChk_Yogan Act_c::M_bg_lava;
#define M_GND_CHK M_bg_lava
#else
#define M_GND_CHK mGndChkYogan
#endif

fopAc_ac_c* Act_c::M_spec_act[3];
const char* const Act_c::M_arcname[] = {
    "Always",
    "Always",
    "Kmtub_00",
    "Ktaru_01",
    "Okmono",
    "Odokuro",
    "Okioke",
#if VERSION == VERSION_DEMO
    "Sitem",
#else
    "Kmi00x",
#endif
    "Hbox2",
    "Hseki",
    "Hseki",
    "Hseki",
    "Hseki",
    "Sitem",
    "Ptubo",
    "Kkiba_00",
};
const dCcD_SrcCyl Act_c::M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK8,
        /* SrcObjAt  Atp     */ 2,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoMass_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 60.0f,
    }},
};
const Act_c::Data_c Act_c::M_data[] = {
    {
        -6.0f,
        28.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_1_e | DATA_FLAG_2_e),
        ALWAYS_BDL_OBM_KOTUBO1,
        0x28,
        0x1E,
        0x3C,
        0x3C,
        0x8,
        {1.0f, 1.0f, 1.0f},
        0x0,
        0x6806,
        0x6925,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x1C,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x1C,
        0x0,
        0x30,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.5f,
        0.75f,
        0.34999999f,
        0.6f,
    },
    {
        -6.5f,
        50.0f,
        50.0f,
        1.0f,
        0xC8,
        22.0f,
        43.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        200.0f,
        5.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_1_e | DATA_FLAG_2_e | DATA_FLAG_20_e),
        ALWAYS_BDL_OBM_OOTUBO1,
        0x32,
        0x32,
        0x64,
        0x64,
        0xA,
        2.0f,
        2.0f,
        2.0f,
        0x1,
        0x6807,
        0x6926,
        0x691C,
        0x6919,
        0xD,
        0x0,
        0x30,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x30,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.85f,
        0.75f,
        0.5f,
        1.0f,
    },
    {
        -6.5f,
        50.0f,
        45.0f,
        1.0f,
        0xC8,
        22.0f,
        43.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        200.0f,
        5.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_20_e),
        KMTUB_00_BDL_KMTUB_00,
        0x41,
        0x32,
        0x64,
        0x64,
        0xB,
        2.0f,
        2.0f,
        2.0f,
        0x2,
        0x6921,
        0x6927,
        0x691C,
        0x6919,
        0xD,
        0x0,
        0x24,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x24,
        0x0,
        0x46,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.85f,
        0.75f,
        0.5f,
        1.0f,
    },
    {
        -6.5f,
        50.0f,
        50.0f,
        1.0f,
        0xC8,
        22.0f,
        43.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        200.0f,
        5.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e | DATA_FLAG_10_e | DATA_FLAG_20_e),
        KTARU_01_BDL_KTARU_01,
        0x3C,
        0x32,
        0x64,
        0x64,
        0x9,
        2.0f,
        2.0f,
        2.0f,
        0xFFFFFFFF,
        0x6805,
        0x282A,
        0x691C,
        0x6919,
        0xB,
        0x0,
        0x32,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x32,
        0x0,
        0x4B,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x820,
        1.0f,
        0.75f,
        0.6f,
        1.0f,
    },
    {
        -6.0f,
        40.0f,
        50.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        5.0f,
        0.2f,
        0.02f,
        0.1f,
        0.02f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e | DATA_FLAG_10_e),
        OKMONO_BDL_OSTOOL,
        0x30,
        0x28,
        0x50,
        0x50,
        0xC,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x6936,
        0x6935,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0x26,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x26,
        0x0,
        0x3C,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.85f,
        0.75f,
        0.4f,
        0.8f,
    },
    {
        -6.0f,
        23.0f,
        25.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        DATA_FLAG_2_e,
        ODOKURO_BDL_ODOKURO,
        0x27,
        0x1C,
        0x3C,
        0x32,
        0x8,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x692B,
        0x6929,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x1C,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x1C,
        0x0,
        0x30,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.5f,
        0.75f,
        0.34999999f,
        0.56f,
    },
    {
        -6.0f,
        32.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_10_e),
        OKIOKE_BDL_OKIOKE,
        0x26,
        0x1A,
        0x49,
        0x49,
        0x8,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x6936,
        0x6935,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0x1C,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x1C,
        0x0,
        0x30,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x4C0,
        0.85f,
        0.75f,
        0.4f,
        0.51999998f,
    },
    {
        -5.0f,
        0.0f,
        50.0f,
        1.0f,
        0xC8,
        30.0f,
        50.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        500.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_10_e | DATA_FLAG_20_e),
#if VERSION == VERSION_DEMO
        SITEM_BDL_KMI_00,
#else
        KMI00X_BDL_KMI_00X,
#endif
        0x32,
        0x32,
        0x64,
        0x64,
        0xA,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x69F3,
        0x69F2,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0xFFF6,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0xFFF6,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
#if VERSION == VERSION_DEMO
        0x4000,
#else
        0x860,
#endif
        0.85f,
        0.75f,
        0.5f,
        1.0f,
    },
    {
        -6.0f,
        37.5f,
        37.5f,
        0.5f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        7.5f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_8_e | DATA_FLAG_10_e),
        HBOX2_BDL_HBOX2,
        0x30,
        0x2D,
        0x4B,
        0x4B,
        0xC,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x6804,
        0x6928,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0x1C,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x1C,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
#if VERSION == VERSION_DEMO
        0x4000,
#else
        0x4C0,
#endif
        0.69999999f,
        0.75f,
        0.4f,
        0.8f,
    },
    {
        -6.0f,
        70.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e),
        HSEKI_BDL_HMON1,
        0x48,
        0x38,
        0x96,
        0x96,
        0x9,
        {1.0f, 1.0f, 1.0f},
        0x0,
        0x692B,
        0x6929,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x41,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x41,
        0x0,
        0x64,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x1240,
        1.0f,
        0.75f,
        0.6f,
        1.12f,
    },
    {
        -6.0f,
        70.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e),
        HSEKI_BDL_HMON1,
        0x48,
        0x38,
        0x96,
        0x96,
        0x9,
        {1.0f, 1.0f, 1.0f},
        0x0,
        0x692B,
        0x6929,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x41,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x41,
        0x0,
        0x64,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x1240,
        1.0f,
        0.75f,
        0.6f,
        1.12f,
    },
    {
        -6.0f,
        70.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e),
        HSEKI_BDL_HMON1,
        0x48,
        0x38,
        0x96,
        0x96,
        0x9,
        {1.0f, 1.0f, 1.0f},
        0x0,
        0x692B,
        0x6929,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x41,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x41,
        0x0,
        0x64,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x1240,
        1.0f,
        0.75f,
        0.6f,
        1.12f,
    },
    {
        -6.0f,
        70.0f,
        30.0f,
        1.0f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_4_e),
        HSEKI_BDL_HMON1,
        0x48,
        0x38,
        0x96,
        0x96,
        0x9,
        {1.0f, 1.0f, 1.0f},
        0x0,
        0x692B,
        0x6929,
        0x691B,
        0x6918,
        0xD,
        0x0,
        0x41,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x41,
        0x0,
        0x64,
        {0x00, 0x00, 0x00, 0x00},
        6000.0f,
        {0x00, 0x00, 0x00, 0x00},
        0x1240,
        1.0f,
        0.75f,
        0.6f,
        1.12f,
    },
    {
        -5.0f,
        0.0f,
        50.0f,
        1.0f,
        0xC8,
        25.0f,
        45.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        200.0f,
        4.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_10_e),
        SITEM_BDL_KMI_02,
        0x2D,
        0x32,
        0x64,
        0x64,
        0xA,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x6804,
        0x6928,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0xFFF6,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0xFFF6,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
#if VERSION == VERSION_DEMO
        0x1240,
#else
        0x4C0,
#endif
        0.85f,
        0.75f,
        0.5f,
        1.0f,
    },
    {
        -6.5f,
        50.0f,
        50.0f,
        1.0f,
        0xC8,
        22.0f,
        43.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0x3E8,
        0.006f,
        0.001f,
        200.0f,
        5.0f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_20_e),
        PTUBO_BDL_PTUBO,
        0x2F,
        0x32,
        0x64,
        0x64,
        0xA,
        2.0f,
        2.0f,
        2.0f,
        0x3,
        0x6807,
        0x6926,
        0x691C,
        0x6919,
        0xD,
        0x0,
        0x30,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x30,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
#if VERSION == VERSION_DEMO
        0x1240,
#else
        0x4C0,
#endif
        0.85f,
        0.75f,
        0.5f,
        1.0f,
    },
    {
        -6.0f,
        37.5f,
        37.5f,
        0.5f,
        0xC8,
        27.0f,
        36.0f,
        0.0f,
        0.002f,
        0.00019999999f,
        0x7D0,
        0x7D0,
        0xF63C,
        0.006f,
        0.001f,
        200.0f,
        7.5f,
        0.2f,
        0.02f,
        0.039999999f,
        0.015f,
        30.0f,
        0xF,
        0xF,
        0.1f,
        0.02f,
        0x96,
        0x5,
        0x64,
        0x4,
        0x7D,
        0x5,
        (DataFlag_e)(DATA_FLAG_2_e | DATA_FLAG_8_e | DATA_FLAG_10_e),
        KKIBA_00_BDL_KKIBA_00,
        0x30,
        0x2D,
        0x4B,
        0x4B,
        0xC,
        {1.0f, 1.0f, 1.0f},
        0xFFFFFFFF,
        0x6804,
        0x6928,
        0x691B,
        0x6918,
        0xB,
        0x0,
        0x1C,
        0x0,
        0x12C,
        {0x00, 0x00, 0x00, 0x00},
        0x0,
        0x1C,
        0x0,
        0x44,
        {0x00, 0x00, 0x00, 0x00},
        8000.0f,
        {0x00, 0x00, 0x00, 0x00},
#if VERSION == VERSION_DEMO
        0x1240,
#else
        0x4C0,
#endif
        0.69999999f,
        0.75f,
        0.4f,
        0.8f,
    },
};
const Act_c::SpecBokoData Act_c::M_data_spec_boko[] = {
    {
        0x6D60,
        0xB1E0,
        88.0f,
        -15.0f,
    },
    {
        0x445C,
        0xB1E0,
        88.0f,
        -15.0f,
    },
    {
        0xDAE4,
        0xB9B0,
        88.0f,
        -15.0f,
    },
};
const Act_c::AttrSpine_c Act_c::M_attrSpine = {
    0.55f,
    0.55f,
    0.69999999f,
    0.69999999f,
    0.2f,
    0.2f,
    0x50,
    0xE,
    0x46,
    0xD,
    0.5f,
    0.1f,
    0.02f,
    0.001f,
    0x4B0,
};

/* 000000EC-0000011C       .text prmZ_init__Q27daTsubo5Act_cFv */
void Act_c::prmZ_init() {
    if (m67E != 0) {
        return;
    }
    mSwitchNo = home.angle.z;
    m67E = 1;
    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;
}

/* 0000011C-00000140       .text solidHeapCB__Q27daTsubo5Act_cFP10fopAc_ac_c */
BOOL Act_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((Act_c*)a_this)->create_heap();
}

/* 00000140-00000330       .text create_heap__Q27daTsubo5Act_cFv */
bool Act_c::create_heap() {
    s32 type = mType;
    u32 modelFlag = type == 7 ? 0x11000022 : 0x11000022;

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname[mType], data().m6C));
    JUT_ASSERT(DEMO_SELECT(1874, 1876), modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, modelFlag);
    bool ret = false;
    if (mType == 7) {
#if VERSION == VERSION_DEMO
        J3DAnmTevRegKey* brk_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname[mType], SITEM_BRK_KMI_00));
#else
        J3DAnmTevRegKey* brk_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname[mType], KMI00X_BRK_KMI_00X));
#endif
        JUT_ASSERT(DEMO_SELECT(1885, 1887), brk_data != NULL);

        mpBrk = new mDoExt_brkAnm();
        if (mpBrk != NULL) {
            if (mpBrk->init(modelData, brk_data, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
                ret = true;
            }
        }
    } else {
        ret = true;
        mpBrk = NULL;
    }

    return mpModel != NULL && ret;
}

/* 00000378-00000444       .text create_init_cull__Q27daTsubo5Act_cFv */
void Act_c::create_init_cull() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    cull_set_draw();
    if (strcmp(dComIfGp_getStartStageName(), "sea") == 0) {
        f32 fVar1 = dStage_stagInfo_GetCullPoint(dComIfGp_getStageStagInfo());
        if (fVar1 > 1.0f) {
            fopAcM_setCullSizeFar(this, data().mB0 / fVar1);
        }
    }
}

/* 00000444-00000594       .text create_init_cc__Q27daTsubo5Act_cFv */
void Act_c::create_init_cc() {
    mStts.Init(data().m10, 0xff, this);
    mCyl.Set(M_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetR(data().mAcchCirRad);
    mCyl.SetH(data().m70);
    mCyl.SetAtVec(*(cXyz*)&cXyz::Zero);
    mCyl.SetTgVec(*(cXyz*)&cXyz::Zero);
    if (cLib_checkBit(data().mFlag, DATA_FLAG_4_e)) {
        mCyl.OnTgShield();
    } else {
        mCyl.OnTgNoHitMark();
    }
}

/* 00000594-00000694       .text create_init_bgc__Q27daTsubo5Act_cFv */
void Act_c::create_init_bgc() {
    mAcchCir.SetWall(30.0f, data().mAcchCirRad);
    mAcch.Set(
        fopAcM_GetPosition_p(this),
        fopAcM_GetOldPosition_p(this),
        this,
        1,
        &mAcchCir,
        fopAcM_GetSpeed_p(this),
        fopAcM_GetAngle_p(this),
        fopAcM_GetShapeAngle_p(this)
    );
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(data().mAcchRoofHeight);
#if VERSION > VERSION_DEMO
    m4F8 = -G_CM3D_F_INF;
    m4FC = -G_CM3D_F_INF;
    m500 = -G_CM3D_F_INF;
    m504 = false;
    m505 = false;
#endif
}

/* 00000694-00000B10       .text _create__Q27daTsubo5Act_cFv */
cPhs_State Act_c::_create() {
    prmZ_init();
    mType = prm_get_type();

    fopAcM_SetupActor(this, Act_c);

    cPhs_State PVar2;
    if (cLib_checkBit(data().mFlag, DATA_FLAG_1_e)) {
        PVar2 = cPhs_COMPLEATE_e;
    } else {
        PVar2 = dComIfG_resLoad(&mPhase, M_arcname[mType]);
    }

    if (PVar2 == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, data().mHeapSize)) {
            create_init_cull();
            create_init_cc();
            create_init_bgc();
            fopAcM_SetGravity(this, data().mGravity);

            if (cLib_checkBit(data().mFlag, DATA_FLAG_10_e)) {
                fopAcM_OnStatus(this, fopAcStts_UNK80000_e);
            }

            if (cLib_checkBit(data().mFlag, DATA_FLAG_20_e)) {
                fopAcM_OnStatus(this, fopAcStts_UNK8000000_e);
            }

            fopAcM_posMoveF(this, NULL);
            mAcch.CrrPos(*dComIfG_Bgsp());
            mAcch.ClrGroundLanding();

            bool iVar1 = prm_get_stick();
            bool iVar3 = prm_get_moveBg();
            if (iVar1 || iVar3) {
                current.pos = home.pos;
                if (iVar3 && dComIfG_Bgsp()->ChkMoveBG_NoDABg(mAcch.m_gnd)) {
                    fopAcM_SetParam(this, fopAcM_GetParam(this) | 0xC000);
                    current.pos.y = mAcch.GetGroundH();
                }
            }

            m680 = 1;
            if (prm_get_spec() == 5 && !is_switch()) {
                m681 = 1;
                fopAcM_SetParam(this, fopAcM_GetParam(this) | 0xC000);
            } else {
                m681 = 0x14;
            }

            m6FC = current.pos.y;
            m6EC = 0.0f;
            m6F0 = cXyz::Zero;
            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = data().mAttnDist;
            attention_info.position.x = current.pos.x;
            attention_info.position.y = current.pos.y + data().mAttnY;
            attention_info.position.z = current.pos.z;
            m802 = 0;
            m800 = 0;
            if (mType == 7) {
                if (!prm_get_stick()) {
                    m800 = attrSpine().m30;
                }
            }

            init_rot_clean();
            s32 iVar4 = prm_get_spec();
            if (iVar4 == 0 && !is_switch()) {
                mode_hide_init();
            } else if (iVar4 == 4) {
                mode_appear_init();
            } else {
                mode_wait_init();
            }

            m4F8 = -G_CM3D_F_INF;
            iVar1 = 0;
            m67F = 0;
            m682 = 1;
            m683 = 0;
            m684 = 0;
            m685 = 0;
            m686 = 0;
            m811 = 0;

            if (mType == 2) {
                for (s32 i = 0; i < ARRAY_SSIZE(m70C); i++) {
                    m70C[i].onEnd();
                    m748[i].onEnd();
                }
            }

            if (mType == 14) {
                eff_kutani_init();
            }
            spec_init();

            m7F4 = cXyz::Zero;
            m814 = cXyz::Zero;
            init_mtx();
            m810 = 0;
        } else {
            PVar2 = cPhs_ERROR_e;
        }
    }
    return PVar2;
}

/* 00001778-000017B8       .text _is_delete__Q27daTsubo5Act_cFv */
bool Act_c::_is_delete() {
    spec_set_actor();
    spec_remove();
    spec_clr_actor();
    return true;
}

/* 000017B8-0000187C       .text _delete__Q27daTsubo5Act_cFv */
bool Act_c::_delete() {
#if VERSION == VERSION_DEMO
    if (mType == 2)
#endif
    {
        for (s32 i = 0; i < ARRAY_SSIZE(m70C); i++) {
            m70C[i].remove();
            m748[i].remove();
        }
    }
#if VERSION == VERSION_DEMO
    if (mType == 14)
#endif
    {
        m784.remove();
    }

    if (!cLib_checkBit(data().mFlag, DATA_FLAG_1_e)) {
        dComIfG_resDeleteDemo(&mPhase, M_arcname[mType]);
    }
    return true;
}

/* 0000187C-00001924       .text spec_make_boko__Q27daTsubo5Act_cFi */
void Act_c::spec_make_boko(int arg1) {
    M7A0* ptr = &m7A0[0];
    for (s32 i = 0; i < arg1; i++, ptr++) {
        ptr->m00 = fopAcM_create(PROC_BOKO, daBoko_c::Type_BOKO_STICK_e, &current.pos, fopAcM_GetHomeRoomNo(this));
        ptr->m06 = data_spec_boko(i).m00;
        ptr->m08 = ptr->m06;
        ptr->m10 = data_spec_boko(i).m04;
    }
}

/* 00001924-00001A94       .text spec_init__Q27daTsubo5Act_cFv */
void Act_c::spec_init() {
    M7A0* ptr = &m7A0[0];
    for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
        ptr->m00 = fpcM_ERROR_PROCESS_ID_e;
        ptr->m04 = 0;
        ptr->m06 = 0;
        ptr->m08 = 0;
        ptr->m0C = 0.0f;
        ptr->m10 = 0.0f;
        ptr->m14 = 0.0f;
        ptr->m18 = 0;
        M_spec_act[i] = NULL;
    }

    s32 iVar2 = prm_get_spec();
    bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;

    if (bVar1) {
        s32 iVar3 = prm_get_spec();
        if (iVar3 == 1) {
            spec_make_boko(1);
        } else if (iVar3 == 2) {
            spec_make_boko(2);
        } else if (iVar3 == 3) {
            spec_make_boko(3);
        }

        if (ptr->m00 != fpcM_ERROR_PROCESS_ID_e) {
            prm_set_cull_non();
        }
    }
    spec_set_actor();
    spec_carry_spec();
    spec_clr_actor();
}

/* 00001A94-00001B84       .text spec_set_actor__Q27daTsubo5Act_cFv */
void Act_c::spec_set_actor() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m00 == fpcM_ERROR_PROCESS_ID_e) {
                    M_spec_act[i] = NULL;
                } else if (!fopAcM_SearchByID(ptr->m00, &M_spec_act[i])) {
                    ptr->m00 = fpcM_ERROR_PROCESS_ID_e;
                }
            }
        }
    }
}

/* 00001B84-00001C34       .text spec_clr_actor__Q27daTsubo5Act_cFv */
void Act_c::spec_clr_actor() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                M_spec_act[i] = NULL;
            }
        }
    }
}

/* 00001C34-00001D18       .text spec_carry_spec__Q27daTsubo5Act_cFv */
void Act_c::spec_carry_spec() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 == 0 && M_spec_act[i] != NULL) {
                    fopAcM_setCarryNow(M_spec_act[i], 0);
                    ptr->m04 = 1;
                }
            }
        }
    }
}

/* 00001D18-00001DF0       .text spec_mode_carry_init__Q27daTsubo5Act_cFv */
void Act_c::spec_mode_carry_init() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0 && M_spec_act[i] != NULL) {
                    fopAcM_setStageLayer(M_spec_act[i]);
                }
            }
        }
    }
}

/* 00001DF0-00001F88       .text spec_mode_carry__Q27daTsubo5Act_cFb */
void Act_c::spec_mode_carry(bool arg1) {
    if (spec_chk_prm_boko()) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0 && M_spec_act[i] != NULL) {
                    f32 fVar1 = data_spec_boko(i).m04;
                    if (arg1) {
                        ptr->m14 = cM_rndF(3.0f);
                        ptr->m18 = 2;
                    } else {
                        ptr->m14 -= 0.8f;
                    }

                    ptr->m10 += ptr->m14;

                    if (ptr->m10 < fVar1) {
                        if (--ptr->m18 <= 0) {
                            ptr->m10 = fVar1;
                            ptr->m14 = 0.0f;
                        } else {
                            ptr->m10 = fVar1 + (ptr->m10 - fVar1) * -0.5f;
                            ptr->m14 *= -0.5f;
                        }
                    }
                }
            }
        }
    }
}

/* 00001F88-00002094       .text spec_mode_put_init__Q27daTsubo5Act_cFv */
void Act_c::spec_mode_put_init() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0 && M_spec_act[i] != NULL) {
                    fopAcM_setRoomLayer(M_spec_act[i], fopAcM_GetRoomNo(this));
                    ptr->m0C = 0.0f;
                    ptr->m10 = data_spec_boko(i).m04;
                    ptr->m14 = 0.0f;
                }
            }
        }
    }
}

/* 00002094-00002170       .text spec_set_room__Q27daTsubo5Act_cFv */
void Act_c::spec_set_room() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0) {
                    fopAc_ac_c* boko = M_spec_act[i];
                    if (boko != NULL) {
                        s8 room = fopAcM_GetRoomNo(this);
                        boko->tevStr.mRoomNo = room;
                        boko->tevStr.mEnvrIdxOverride = tevStr.mEnvrIdxOverride;
                        fopAcM_SetRoomNo(boko, room);
                    }
                }
            }
        }
    }
}

/* 00002170-0000229C       .text spec_remove__Q27daTsubo5Act_cFv */
void Act_c::spec_remove() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0) {
                    fopAc_ac_c* boko = M_spec_act[i];
                    if (boko != NULL) {
                        fopAcM_SetRoomNo(boko, fopAcM_GetRoomNo(this));
                        fopAcM_cancelCarryNow(boko);
                        boko->current.angle.y = shape_angle.y - ptr->m06;
                        boko->current.angle.y -= -0x8000;
                        fopAcM_SetSpeedF(boko, cM_rndF(9.0f));
                        fopAcM_GetSpeed(boko).y = cM_rndF(13.0f);
                        ptr->m00 = fpcM_ERROR_PROCESS_ID_e;
                    }
                }
            }
        }
    }
}

/* 0000229C-00002390       .text spec_kill__Q27daTsubo5Act_cFv */
void Act_c::spec_kill() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                if (ptr->m04 != 0) {
                    fopAc_ac_c* boko = M_spec_act[i];
                    if (boko != NULL) {
                        s8 room = fopAcM_GetRoomNo(this);
                        ptr->m00 = fpcM_ERROR_PROCESS_ID_e;
                        fopAcM_SetRoomNo(boko, room);
                        fopAcM_cancelCarryNow(boko);
                        fopAcM_delete(boko);
                    }
                }
            }
        }
    }
}

/* 00002390-000024EC       .text spec_mtx__Q27daTsubo5Act_cFv */
void Act_c::spec_mtx() {
    if (prm_get_spec() != 0x3f) {
        s32 iVar2 = prm_get_spec();
        bool bVar1 = iVar2 == 1 || iVar2 == 2 || iVar2 == 3;
        if (bVar1) {
            M7A0* ptr = &m7A0[0];
            for (s32 i = 0; i < ARRAY_SSIZE(m7A0); i++, ptr++) {
                daBoko_c* boko = (daBoko_c*)M_spec_act[i];
                if (boko != NULL) {
                    Mtx sp38;
                    cMtx_copy(mDoMtx_stack_c::get(), sp38);
                    mDoMtx_stack_c::push();
                    mDoMtx_stack_c::YrotS(-ptr->m06);
                    mDoMtx_stack_c::transM(0.0f, ptr->m10, data_spec_boko(i).m08);
                    mDoMtx_stack_c::XrotM(data_spec_boko(i).m02);
                    Mtx sp08;
                    mDoMtx_concat(sp38, mDoMtx_stack_c::get(), sp08);
                    boko->setMatrix(sp08);
                    mDoMtx_stack_c::pop();
                }
            }
        }
    }
}

/* 000024EC-00002578       .text mode_hide_init__Q27daTsubo5Act_cFv */
void Act_c::mode_hide_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OffCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.SetRoofNone();
    mAcch.SetWallNone();
    mAcch.SetGrndNone();
    mAcch.SetWaterNone();
    mAcch.OffLineCheck();

    m67F = 1;
    fopAcM_SetSpeedF(this, 0.0f);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    m678 = 0;
}

/* 00002578-000025CC       .text mode_hide__Q27daTsubo5Act_cFv */
void Act_c::mode_hide() {
    if (is_switch()) {
        mode_appear_init();
    }
}

/* 000025CC-000026FC       .text mode_appear_init__Q27daTsubo5Act_cFv */
void Act_c::mode_appear_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.SetRoofNone();
    mAcch.SetWallNone();
    mAcch.ClrGrndNone();
    mAcch.SetWaterNone();
    mAcch.OffLineCheck();

    m67F = 1;
    fopAcM_SetSpeedF(this, 0.0f);
    scale.setall(0.01f);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

    if (prm_get_spec() == 4) {
        m808 = M_attrSpine.m10;
        m80C = M_attrSpine.m14;
        m802 = M_attrSpine.m18;
    } else {
        speed.y = cM_rndF(5.0f) + 29.0f;
        gravity = data().mGravity;
        m802 = 0xb;
    }
    m678 = 1;
}

/* 000026FC-0000293C       .text mode_appear__Q27daTsubo5Act_cFv */
void Act_c::mode_appear() {
    if (prm_get_spec() == 4) {
        m802--;
        if (m802 == M_attrSpine.m1C) {
            fopAcM_seStart(this, JA_SE_OBJ_BOKKURI_RECOVER, 0);
        }

        if (m802 == M_attrSpine.m1E) {
            fopAcM_seStart(this, JA_SE_OBJ_BOKKURI_SWELL, 0);
        }

        if (m802 >= M_attrSpine.m1A) {
            cLib_addCalc(&scale.x, M_attrSpine.m20, M_attrSpine.m24, M_attrSpine.m28, M_attrSpine.m2C);
            scale.y = scale.x;
            scale.z = scale.x;
        } else {
            f32 tmp = (scale.x - 1.0f);
            m808 -= tmp * M_attrSpine.m08;
            m808 -= m808 * M_attrSpine.m00;
            scale.x += m808;
            scale.z = scale.x;
            f32 tmp2 = (scale.y - 1.0f);
            m80C -= tmp2 * M_attrSpine.m0C;
            m80C -= m80C * M_attrSpine.m04;
            scale.y += m80C;
        }

        if (m802 <= 0) {
            scale.setall(1.0f);
            mode_wait_init();
        }
    } else {
        if (--m802 <= 0) {
            mode_wait_init();
        } else {
            cLib_chaseF(&scale.x, 1.0f, 0.1f);
            scale.y = scale.x;
            scale.z = scale.x;
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
}

/* 0000293C-00002A10       .text mode_wait_init__Q27daTsubo5Act_cFv */
void Act_c::mode_wait_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();

    m67F = 0;
    fopAcM_SetSpeedF(this, 0.0f);
    mStts.Init(data().m10, 0xff, this);
    m802 = 0;
    m678 = 2;
}

/* 00002A10-00002B1C       .text mode_wait__Q27daTsubo5Act_cFv */
void Act_c::mode_wait() {
    if (prm_get_stick() != false) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    } else if (mAcch.ChkGroundHit()) {
        if (speedF > 0.1f) {
            speedF *= 0.5f;
        } else {
            fopAcM_SetSpeedF(this, 0.0f);
        }
        fopAcM_SetGravity(this, data().mGravity);
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    } else {
        f32 sp10;
        f32 sp0C;
        f32 sp08;
        calc_drop_param(&sp10, &sp0C, &sp08);
        fopAcM_SetGravity(this, sp10);
        daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, sp0C, sp08);
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }
}

/* 00002B1C-00002BB8       .text mode_walk_init__Q27daTsubo5Act_cFv */
void Act_c::mode_walk_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();

    m67F = 0;
    init_rot_clean();
    m678 = 3;
}

/* 00002BB8-00002D74       .text mode_walk__Q27daTsubo5Act_cFv */
void Act_c::mode_walk() {
    f32 sp10;
    f32 sp0C;
    f32 sp08;
    calc_drop_param(&sp10, &sp0C, &sp08);
    fopAcM_SetGravity(this, sp10);
    cXyz sp20(mStts.GetCCMoveP()->x, 0.0f, mStts.GetCCMoveP()->z);
    if (sp20.getSquareMag() > 0.010000001f) {
        speedF *= 0.9f;
    }

    cM3dGPla* pNorm = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
    m6F0 += m814;
    f32 fVar2;
    f32 noGradeCos;
    cM3dGPla* pNorm2;
    if (pNorm != NULL) {
        pNorm2 = pNorm;
        fVar2 = data().m5C;
        noGradeCos = cM_scos(cM_deg2s(data().m56 - 0.5f));
    } else {
        pNorm2 = NULL;
        fVar2 = 0.0f;
        noGradeCos = fVar2;
    }

    daObj::posMoveF_grade(this, mStts.GetCCMoveP(), &m7F4, sp0C, sp08, pNorm2->GetNP(), fVar2, noGradeCos, &m6F0);

    if (mAcch.ChkGroundHit()) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        if (speed.abs2XZ() < 0.1f) {
            mode_wait_init();
        }
    } else {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }
}

/* 00002D74-00002EF8       .text mode_carry_init__Q27daTsubo5Act_cFv */
void Act_c::mode_carry_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OffCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();

    m67F = 0;
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    fopAcM_SetSpeedF(this, 0.0f);
    spec_mode_carry_init();
    if (mType == 2) {
        fopAcM_seStart(this, JA_SE_OBJ_WPOT_LIFTUP, 0);
    }

    m802 = 6;
    if (fopAcM_checkHookCarryNow(this)) {
        m684 = 1;
    } else {
        m684 = 0;
    }

    if (mType == 7 && prm_get_stick()) {
        m800 = M_attrSpine.m30;
        se_pickup_carry_init();
    }

    cLib_offBit<u32>(base.mParameters, 0x80000000);
    m685 = 0;
    m686 = 0;
    m678 = 4;
}

/* 00002EF8-0000310C       .text mode_carry__Q27daTsubo5Act_cFv */
void Act_c::mode_carry() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    u8 tmp = m685;

    if (tmp == 0) {
        if (prm_get_spec() == 6) {
            m685 = 1;
            m686 = 1;
        } else if (player->getGrabActorID() == fopAcM_GetID(this)) {
            if (player->getGrabUpStart()) {
                m685 = 1;
                m686 = 1;
            }
        } else {
            m685 = 1;
            m686 = 0;
        }
    }

    if (m685 && !tmp) {
        init_rot_clean();
        shape_angle.x = 0;
        shape_angle.z = 0;
    }

    bool bVar2 = player->getGrabUpEnd() || player->getRightFootOnGround();
    if (bVar2 && mType == 2) {
        eff_drop_water();
        fopAcM_seStart(this, JA_SE_LK_CONVEY_WPOT, 0);
    }

    se_pickup_carry();

    if (m810 == 0) {
        fopAcM_GetSpeed(this).y = 0.0f;
    }

    if (fopAcM_checkCarryNow(this) || fopAcM_checkHookCarryNow(this)) {
        spec_mode_carry(bVar2);
    } else {
        m6FC = current.pos.y;
        if (fopAcM_GetSpeedF(this) > 0.0f && m684 == 0) {
            init_rot_throw();
            mode_drop_init();
            mode_drop();
        } else {
            daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
            spec_mode_put_init();
            m683 = 2;
            mode_wait_init();
        }
    }
}

/* 0000310C-00003260       .text mode_drop_init__Q27daTsubo5Act_cFv */
void Act_c::mode_drop_init() {
    daPy_py_c* player = (daPy_py_c*)daPy_getPlayerActorClass();
    f32 fVar1 = data().m18 + player->getSpeedF() * data().m1C;

    mCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);

    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OnLineCheck();

    m67F = 0;
    mStts.Init(data().m10, 0xff, this);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    if (m810 == 0) {
        speed.y = data().m14;
    }
    m810 = 0;
    fopAcM_SetSpeedF(this, fVar1);
    gravity = data().mGravity;
    m678 = 5;
}

/* 00003260-00003314       .text mode_drop__Q27daTsubo5Act_cFv */
void Act_c::mode_drop() {
    daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
    cXyz* movePos = &m7F4;
    cXyz sp14(mStts.GetCCMoveP()->x, 0.0f, mStts.GetCCMoveP()->z);
    if (sp14.getSquareMag() > 0.010000001f) {
        speedF *= 0.9f;
    }
    f32 sp10;
    f32 sp08;
    f32 sp0C;
    calc_drop_param(&sp10, &sp08, &sp0C);
    fopAcM_SetGravity(this, sp10);
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), movePos, sp08, sp0C);
}

/* 00003314-000034C0       .text mode_sink_init__Q27daTsubo5Act_cFv */
void Act_c::mode_sink_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);

    mStts.Init(0xff, 0xff, this);

    mAcch.SetRoofNone();
    mAcch.SetWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();
    m67F = 0;
    fopAcM_SetGravity(this, data().mGravity + data().m3C);

    f32 sqrt = std::sqrtf(SQUARE(speed.y) + SQUARE(speedF));
    if (sqrt > data().m50) {
        f32 fVar4 = data().m50 / sqrt;
        speed *= fVar4;
        speedF *= fVar4;
    }

    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    m678 = 6;
}

/* 000034C0-00003528       .text mode_sink__Q27daTsubo5Act_cFv */
void Act_c::mode_sink() {
    daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
#if VERSION > VERSION_DEMO
    water_tention();
#endif
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, data().m40, data().m44);
}

/* 00003528-000036D0       .text mode_afl_init__Q27daTsubo5Act_cFv */
void Act_c::mode_afl_init() {
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();
    m67F = 0;

    f32 sqrt = std::sqrtf(SQUARE(speed.y) + SQUARE(speedF));
    if (sqrt > data().m50) {
        f32 fVar4 = data().m50 / sqrt;
        speed *= fVar4;
        speedF *= fVar4;
    }

    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

    m804 = cM_rndFX(32768.0f);
    m806 = cM_rndFX(32768.0f);
    m678 = 7;
}

/* 000036D0-00003824       .text mode_afl__Q27daTsubo5Act_cFv */
void Act_c::mode_afl() {
    daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
    cXyz* pStreamSpd = &daObj::get_path_spd(mAcch.m_gnd, 30.0f);
    cXyz sp14 = m7F4 * data().m20;
    f32 sp10;
    f32 sp0C;
    f32 sp08;
    calc_afl_param(&sp10, &sp0C, &sp08);
    s16 tmp = (s16)cM_rndF(400.0f) + 0x514;
    m804 += tmp;
    fopAcM_SetGravity(this, sp10 + cM_ssin(m804) * 0.3f);
#if VERSION > VERSION_DEMO
    water_tention();
#endif
    daObj::posMoveF_grade(this, mStts.GetCCMoveP(), pStreamSpd, sp0C, sp08, NULL, 0.0f, 0.0f, &sp14);
    s16 tmp2 = (s16)cM_rndF(400.0f) + 0x514;
    m806 += tmp2;
}

/* 00003824-00003BBC       .text mode_proc_call__Q27daTsubo5Act_cFv */
bool Act_c::mode_proc_call() {
    typedef void (Act_c::*ModeProcFunc)();
    static ModeProcFunc mode_proc[] = {
        &Act_c::mode_hide,
        &Act_c::mode_appear,
        &Act_c::mode_wait,
        &Act_c::mode_walk,
        &Act_c::mode_carry,
        &Act_c::mode_drop,
        &Act_c::mode_sink,
        &Act_c::mode_afl,
    };

    if ((fopAcM_checkCarryNow(this) || fopAcM_checkHookCarryNow(this)) && m678 != 4) {
        mode_carry_init();
    }

#if VERSION == VERSION_DEMO
    bool iVar2 = prm_get_moveBg();
    cXyz sp08 = current.pos;
    (this->*mode_proc[m678])();
    f32 fVar7 = fopAcM_GetSpeed(this).y;
    if (m678 == 0 || m678 == 4 || m678 == 6 || prm_get_stick()) {
        sp08 = current.pos;
        iVar2 = true;
    }

    mAcch.CrrPos(*dComIfG_Bgsp());

    bg_crr_lava();

    if (dComIfG_Bgsp()->ChkMoveBG_NoDABg(mAcch.m_gnd)) {
        if (dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)) {
            m682 = 1;
        }

        if (prm_get_moveBg()) {
            prm_off_moveBg();
            sp08.y = mAcch.GetGroundH();
            m6FC = mAcch.GetGroundH();
        }
    }

    if (iVar2) {
        current.pos = sp08;
    }
#else
    cXyz sp08 = current.pos;
    (this->*mode_proc[m678])();
    bool iVar2 = prm_get_moveBg();
    f32 fVar7 = fopAcM_GetSpeed(this).y;
    crr_pos(sp08);
#endif

    if (!damage_bg_proc_directly()) {
        if (!iVar2) {
            bound(fVar7);
        }
        moment_proc_call();

        typedef void (Act_c::*SetTensorFunc)();
        static SetTensorFunc set_tensor_proc[] = {
            &Act_c::set_tensor_hide,
            &Act_c::set_tensor_appear,
            &Act_c::set_tensor_wait,
            &Act_c::set_tensor_walk,
            &Act_c::set_tensor_carry,
            &Act_c::set_tensor_drop,
            &Act_c::set_tensor_sink,
            &Act_c::set_tensor_afl,
        };

        (this->*set_tensor_proc[m678])();

        if (m678 != 4) {
            tevStr.mRoomNo = fopAcM_GetRoomNo(this);
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
        }

        m7F4 *= 0.95f;
        if (m7F4.getSquareMag() < 0.1f) {
            m7F4.setall(0.0f);
        }

        m814 *= 0.6f;
        if (m814.getSquareMag() < 0.1f) {
            m814.setall(0.0f);
        }

        spec_set_room();

        if (mType == 14) {
            eff_kutani_set();
        }
        return true;
    }
    return false;
}

/* 00003BBC-00003C5C       .text cull_set_draw__Q27daTsubo5Act_cFv */
void Act_c::cull_set_draw() {
    fopAcM_setCullSizeSphere(this, data().mCullSphX_Draw, data().mCullSphY_Draw, data().mCullSphZ_Draw, data().mCullSphR_Draw);
}

/* 00003C5C-00003CFC       .text cull_set_move__Q27daTsubo5Act_cFv */
void Act_c::cull_set_move() {
    fopAcM_setCullSizeSphere(this, data().mCullSphX_Move, data().mCullSphY_Move, data().mCullSphZ_Move, data().mCullSphR_Move);
}

/* 00003CFC-00003FC4       .text damaged__Q27daTsubo5Act_cFiP13cBgS_PolyInfobPC4cXyz */
void Act_c::damaged(int arg1, cBgS_PolyInfo* arg2, bool arg3, const cXyz* arg4) {
    s32 itemNo = prm_get_itemNo();
    s32 itemBitNo = prm_get_itemSave();
    csXyz sp08(0, home.angle.y, 0);
    fopAcM_createItemFromTable(&current.pos, itemNo, itemBitNo, fopAcM_GetHomeRoomNo(this), 0, &sp08, arg1, NULL);
    fopAcM_cancelCarryNow(this);
    fopAcM_cancelHookCarryNow(this);

    if (arg3) {
        if (mType == 2 && arg4 != NULL) {
            fopKyM_create(0x19, tevStr.mRoomNo, (cXyz*)arg4, 0, 0);
        }

        typedef void (Act_c::*EffBreakProcFunc)();
        static EffBreakProcFunc eff_break_proc[] = {
            &Act_c::eff_break_tsubo,
            &Act_c::eff_break_tsubo,
            &Act_c::eff_break_tsubo,
            &Act_c::eff_break_barrel,
            &Act_c::eff_break_stool,
            &Act_c::eff_break_skull,
            &Act_c::eff_break_pail,
            &Act_c::eff_break_spine,
            &Act_c::eff_break_hbox2S,
            &Act_c::eff_break_try,
            &Act_c::eff_break_try,
            &Act_c::eff_break_try,
            &Act_c::eff_break_try,
            &Act_c::eff_break_pinecone,
            &Act_c::eff_break_tsubo,
            &Act_c::eff_break_woodS,
        };

        (this->*eff_break_proc[mType])();
        se_break(arg2);
    } else {
        spec_kill();
    }
}

/* 00003FC4-00003FEC       .text damaged__Q27daTsubo5Act_cFiP13cBgS_PolyInfo */
void Act_c::damaged(int arg1, cBgS_PolyInfo* arg2) {
    damaged(arg1, arg2, true, &current.pos);
}

/* 00003FEC-00004054       .text damaged_lava__Q27daTsubo5Act_cFv */
void Act_c::damaged_lava() {
    cXyz sp08;
    cXyz* pcVar2;

    if (current.pos.y < m4F8 - 80.0f) {
        sp08.set(current.pos.x, m4F8 - 80.0f, current.pos.z);
        pcVar2 = &sp08;
    } else {
        pcVar2 = &current.pos;
    }

    damaged(2, &M_GND_CHK, true, pcVar2);
}

/* 00004054-00004384       .text damage_tg_acc__Q27daTsubo5Act_cFv */
bool Act_c::damage_tg_acc() {
    cCcD_Obj* pcVar4 = mCyl.GetTgHitObj();
    bool iVar9 = false;
    if (pcVar4 != NULL) {
        f32 fVar1 = 1.5f;
        f32 fVar2 = 0.0f;
        s32 type = pcVar4->GetAtType();
        if ((type & AT_TYPE_SWORD) || (type & AT_TYPE_BOKO_STICK) || (type & AT_TYPE_MACHETE) || (type & AT_TYPE_UNK800) || (type & AT_TYPE_SPIKE) ||
            (type & AT_TYPE_UNK2000) || (type & AT_TYPE_DARKNUT_SWORD) || (type & AT_TYPE_MOBLIN_SPEAR))
        {
            fVar1 = 2.0f;
            fVar2 = 9.0f;
        }

        if (fVar1 > 0.0f) {
            f32 abs = m814.abs();
            cXyz sp34 = *mCyl.GetTgRVecP();
            f32 abs2 = sp34.abs();

            if (fVar1 > abs && abs2 > abs) {
                if (abs2 < fVar1) {
                    m814 = sp34;
                } else {
                    m814 = sp34 * (fVar1 / abs2);
                }
                m814.y += fVar2;
                iVar9 = true;
            }
        }

        if (!iVar9 && pcVar4->ChkAtType(AT_TYPE_WIND)) {
            cCcD_ShapeAttr* shapeAttr = pcVar4->GetShapeAttr();
            cXyz sp28 = cXyz::Zero;
            if (shapeAttr->GetNVec(current.pos, &sp28)) {
                fopAc_ac_c* pfVar7 = mCyl.GetTgHitAc();
                if (pfVar7 != NULL && fopAcM_GetProfName(pfVar7) == PROC_PLAYER) {
                    s16 atan = cM_atan2s(sp28.x, sp28.z);
                    if (cM_scos(pfVar7->shape_angle.y - atan) > 0.866f) {
                        m814 = sp28 * 1.5f;
                        iVar9 = true;
                    }
                }
            }
        }
    }
    return iVar9;
}

/* 00004384-00004768       .text damage_cc_proc__Q27daTsubo5Act_cFv */
bool Act_c::damage_cc_proc() {
    bool bVar1 = false;
    if (mCyl.ChkAtHit()) {
        if (mType != 7) {
            damaged(3, NULL);
            bVar1 = true;
        }
        mCyl.ClrAtHit();
    } else if (mCyl.ChkTgHit()) {
        cCcD_Obj* pcVar4 = mCyl.GetTgHitObj();
        if (pcVar4 != NULL && (!cLib_checkBit(data().mFlag, DATA_FLAG_10_e) || !pcVar4->ChkAtType(AT_TYPE_HOOKSHOT))) {
            if (pcVar4->ChkAtType(AT_TYPE_WIND) && !prm_get_stick()) {
                set_wind_vec();
                if (m678 == 2) {
                    mode_walk_init();
                }
            } else {
                if (damage_tg_acc() && m678 == 2 && mType == 7) {
                    if (mType == 7 && prm_get_stick()) {
                        m800 = M_attrSpine.m30;
                    }

                    if (prm_get_stick()) {
                        se_pickup();
                    }

                    prm_off_stick();
                    mode_walk_init();
                }

                if ((mType == 3) || (mType == 4)) {
                    if (pcVar4->ChkAtType(AT_TYPE_BOMB)) {
                        damaged(7, NULL);
                        bVar1 = true;
                    } else if (pcVar4->ChkAtType(AT_TYPE_UNK8)) {
                        damaged(3, NULL);
                        bVar1 = true;
                    } else if (pcVar4->ChkAtType(AT_TYPE_SKULL_HAMMER)) {
                        damaged(1, NULL);
                        bVar1 = true;
                    }
                } else if ((mType == 0) || (mType == 1) || (mType == 2) || (mType == 5 || (mType == 6)) || (mType == 8 || (mType == 13 || (mType == 14))) ||
                           (mType == 15))
                {
                    if (pcVar4->ChkAtType(AT_TYPE_BOMB)) {
                        damaged(7, NULL);
                        bVar1 = true;
                    } else if (pcVar4->ChkAtType(AT_TYPE_SWORD)) {
                        damaged(1, NULL);
                        bVar1 = true;
                    } else {
                        damaged(9, NULL);
                        bVar1 = true;
                    }
                } else if (mType == 7) {
                    if (pcVar4->ChkAtType(AT_TYPE_BOMB)) {
                        damaged(7, NULL);
                        bVar1 = true;
                    } else if (pcVar4->ChkAtType(AT_TYPE_SKULL_HAMMER)) {
                        damaged(1, NULL);
                        bVar1 = true;
                    }
                } else if (pcVar4->ChkAtType(AT_TYPE_BOMB)) {
                    damaged(7, NULL);
                    bVar1 = true;
                }
            }
        }

        if (!bVar1) {
            daObj::HitSeStart(&eyePos, current.roomNo, &mCyl, data().mSoundID_Hit);
            set_senv(data().m62, data().m63);
            if ((mType == 3) || (mType == 4) || (mType == 7)) {
                daObj::HitEff_kikuzu(this, &mCyl);
            } else if ((mType == 9) || (mType == 10) || (mType == 0xb || (mType == 0xc))) {
                daObj::HitEff_hibana(this, &mCyl);
            }
        }

        mCyl.ClrTgHit();
    }
    return bVar1;
}

/* 00004768-00004990       .text damage_bg_proc__Q27daTsubo5Act_cFv */
bool Act_c::damage_bg_proc() {
    bool uVar6 = mAcch.ChkGroundHit();
    bool cVar2 = chk_sink_water();
    bool cVar3 = chk_sink_lava();
    bool bVar7 = false;

    if (m678 == 2 || m678 == 3) {
        if (cVar2 || cVar3) {
            if (cVar2) {
                se_fall_water();
                eff_hit_water_splash();
                init_rot_clean();
                if (data().mGravity + data().m3C >= 0.0f) {
                    mode_afl_init();
                } else {
                    mode_sink_init();
                }
            } else {
                se_fall_lava();
                eff_hit_lava_splash();
                damaged_lava();
                bVar7 = true;
            }
        }
    } else if (m678 == 5) {
        if (cVar2) {
            se_fall_water();
            eff_hit_water_splash();
            if (data().mGravity + data().m3C >= 0.0f) {
                mode_afl_init();
            } else {
                mode_sink_init();
            }
        } else if (cVar3) {
            se_fall_lava();
            eff_hit_lava_splash();
            damaged_lava();
            bVar7 = true;
        } else if (mType == 7 && uVar6) {
            mode_walk_init();
        }
    } else if (m678 == 6) {
        if (chk_sinkdown_water()) {
#if VERSION == VERSION_DEMO
            damaged(2, &mAcch.m_wtr, false, &current.pos);
#else
            damaged(2, m505 ? NULL : &mAcch.m_wtr, false, &current.pos);
#endif
            bVar7 = true;
        }
    } else if (m678 == 7 && uVar6 && !chk_sink_water()) {
        mode_wait_init();
    }
    return bVar7;
}

/* 00004990-00004D04       .text damage_bg_proc_directly__Q27daTsubo5Act_cFv */
bool Act_c::damage_bg_proc_directly() {
    bool uVar11 = mAcch.ChkGroundHit();
    bool uVar8 = mAcch.ChkGroundLanding();
    bool iVar10 = false;

    if (m678 == 2 || m678 == 3) {
        bool uVar7 = mAcch.ChkRoofHit();
        if (uVar8 && m6FC - current.pos.y > data().m38) {
            damaged(2, NULL);
            iVar10 = true;
        } else if (uVar11 && uVar7) {
            f32 roofHeight = mAcch.GetRoofHeight();
            if (roofHeight < current.pos.y + data().mAcchRoofHeight - 10.0f && mAcch.GetRoofHeight() > mAcch.GetGroundH()) {
                damaged(3, NULL);
                iVar10 = true;
            }
        }

        if (uVar11) {
            m6FC = current.pos.y;
        }
    } else if (m678 == 5) {
        bool uVar7 = mAcch.ChkRoofHit();
        bool uVar9 = mAcch.ChkWallHit();
        bool cVar5 = chk_sink_water();
        bool cVar3 = chk_sink_lava();

        s32 type = mType;
        if (type == 7) {
            if (uVar8 && m6FC - current.pos.y > data().m38) {
                damaged(2, NULL);
                iVar10 = true;
            }

            if (uVar11) {
                m6FC = current.pos.y;
            }
        } else if (uVar11) {
            damaged(2, NULL);
            iVar10 = true;
        } else if (uVar9) {
            damaged(3, &mAcchCir);
            iVar10 = true;
        } else if (uVar7) {
            damaged(3, &mAcch.m_roof);
            iVar10 = true;
        }

        if (uVar11 || uVar9 || uVar7 || cVar5 || cVar3) {
            cam_lockoff();
        }
    } else if (m678 == 7) {
        m6FC = current.pos.y;
    }

    if (m681 > 0) {
        m681--;
    } else if (uVar11) {
        if (m680 == 0) {
            if (m678 == 2 || m678 == 3 || m678 == 1 || m678 == 5) {
                if (!iVar10) {
                    if (mType == 2) {
                        eff_drop_water();
                    }

                    s32 uVar12;
                    if (mType == 7) {
                        uVar12 = 0x2d;
                    } else {
                        uVar12 = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
                    }

                    fopAcM_seStart(this, data().m88, uVar12);
#if VERSION > VERSION_DEMO
                    if (!chk_sink_water())
#endif
                    {
                        eff_land_smoke();
                    }
                }
                m680 = 1;
            }
        }
    } else {
        m680 = 0;
    }
    return iVar10;
}

/* 00004D04-00004D58       .text damage_kill_proc__Q27daTsubo5Act_cFv */
bool Act_c::damage_kill_proc() {
    bool bVar1 = false;
    if (m800 > 0) {
        m800--;
        if (m800 == 0) {
            damaged(1, NULL);
            bVar1 = true;
        }
    }
    return bVar1;
}

#if VERSION > VERSION_DEMO
/* 00004D58-00004EB4       .text crr_pos__Q27daTsubo5Act_cFRC4cXyz */
void Act_c::crr_pos(const cXyz& arg1) {
    cXyz sp08 = arg1;
    bool bVar1 = prm_get_moveBg();
    if (m678 == 0 || m678 == 4 || m678 == 6 || prm_get_stick()) {
        sp08 = current.pos;
        bVar1 = true;
    }

    mAcch.CrrPos(*dComIfG_Bgsp());
    crr_pos_water();
    crr_pos_lava();

    if (dComIfG_Bgsp()->ChkMoveBG_NoDABg(mAcch.m_gnd)) {
        if (dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)) {
            m682 = 1;
        }

        if (prm_get_moveBg()) {
            fopAcM_SetParam(this, fopAcM_GetParam(this) | 0xC000);
            m6FC = sp08.y = mAcch.GetGroundH();
        }
    }

    if (bVar1) {
        current.pos = sp08;
    }
}
#endif

#if VERSION > VERSION_DEMO
/* 00004EB4-00004FE8       .text crr_pos_water__Q27daTsubo5Act_cFv */
void Act_c::crr_pos_water() {
    f32 fVar1 = mAcch.m_wtr.GetHeight();
    bool bVar5 = daSea_ChkArea(current.pos.x, current.pos.z);
    f32 fVar7 = daSea_calcWave(current.pos.x, current.pos.z);
    f32 fVar2 = current.pos.y + data().m04;

    bool bVar3 = mAcch.ChkWaterIn() && fVar2 < fVar1;
    bool bVar4 = bVar5 && fVar2 < fVar7;
    bool uVar6 = false;

    m500 = m4FC;

    if (bVar3 && bVar4) {
        if (fVar1 > fVar7) {
            bVar4 = false;
        } else {
            bVar3 = false;
        }
    }

    if (bVar3) {
        m4FC = fVar1;
        uVar6 = true;
        m505 = 0;
    } else if (bVar4) {
        m4FC = fVar7;
        uVar6 = true;
        m505 = 1;
    } else {
        m4FC = -G_CM3D_F_INF;
        m505 = 0;
    }
    m504 = uVar6;
}
#endif

#if VERSION > VERSION_DEMO
/* 00004FE8-0000508C       .text crr_pos_lava__Q27daTsubo5Act_cFv */
void Act_c::crr_pos_lava() {
    if (m67F != 0) {
        m4F8 = -G_CM3D_F_INF;
    } else {
        f32 fVar3 = current.pos.z;
        f32 fVar1 = old.pos.y;
        cXyz sp08(current.pos.x, fVar1 + data().m04 + 1.0f, fVar3);
        M_GND_CHK.SetPos(&sp08);
        m4F8 = dComIfG_Bgsp()->GroundCross(&M_GND_CHK);
    }
}
#endif

#if VERSION > VERSION_DEMO
/* 0000508C-0000511C       .text water_tention__Q27daTsubo5Act_cFv */
void Act_c::water_tention() {
    if (chk_sink_water()) {
        if (m4FC != -G_CM3D_F_INF && m500 != -G_CM3D_F_INF) {
            f32 fVar2 = m4FC - m500;
            f32 fVar1;
            if (fVar2 < 0.0f) {
                fVar1 = fVar2 * 0.8f;
            } else {
                fVar1 = fVar2 * 0.2f;
            }
            current.pos.y += fVar1;
        }
    }
}
#endif

/* 0000511C-00005258       .text reflect__Q27daTsubo5Act_cFP4cXyzRC13cBgS_PolyInfof */
f32 Act_c::reflect(cXyz* pos, const cBgS_PolyInfo& pTri, float rebound) {
    cM3dGPla* pcVar1 = dComIfG_Bgsp()->GetTriPla(pTri.GetBgIndex(), pTri.GetPolyIndex());
    f32 ret;
    if (pcVar1 != NULL) {
        cXyz sp18;
        C_VECReflect(pos, &pcVar1->mNormal, &sp18);
        f32 fVar5 = sp18.inprod(pcVar1->mNormal);
        f32 dVar4 = 1.0f - (1.0f - rebound) * fVar5;
        f32 tmp = dVar4 * pos->abs();
        *pos = sp18 * tmp;
        ret = dVar4;
    } else {
        ret = 0.0f;
    }
    return ret;
}

/* 00005258-00005544       .text bound__Q27daTsubo5Act_cFf */
void Act_c::bound(float arg1) {
    if (mType == 7) {
        cXyz sp28(speed.x, arg1, speed.z);
        f32 abs = sp28.abs();

        if (abs > 8.0f) {
            bool uVar8 = mAcch.ChkWallHit();
            bool uVar7 = mAcch.ChkGroundLanding();
            bool uVar5 = mAcch.ChkRoofHit();
            cXyz sp1C = sp28;

            f32 dVar9 = 0.0f;
            if (uVar8) {
                f32 dVar10 = reflect(&sp1C, mAcchCir, 0.5f);
                if (dVar10 > dVar9) {
                    dVar9 = dVar10;
                }
            }

            if (uVar7) {
                f32 dVar10 = reflect(&sp1C, mAcch.m_gnd, 0.6f);
                if (dVar10 > dVar9) {
                    dVar9 = dVar10;
                }
            }

            if (uVar5) {
                f32 dVar10 = reflect(&sp1C, mAcch.m_roof, 0.4f);
                if (dVar10 > dVar9) {
                    dVar9 = dVar10;
                }
            }

            if (uVar8 || uVar7 || uVar5) {
                speed = sp1C;
                fopAcM_SetSpeedF(this, sp1C.absXZ());
                current.angle.y = cM_atan2s(sp1C.x, sp1C.z);

                s32 uVar6;
                if (abs > 45.0f) {
                    uVar6 = 100;
                } else {
                    uVar6 = abs * dVar9 * 2.2222223f;
                }

                if (uVar6 != 0u) {
                    fopAcM_seStart(this, JA_SE_OBJ_BOKKURI_BOUND, uVar6);
                }
            }
        }
    } else if (mAcch.ChkWallHit() != false) {
        speedF *= 0.9f;
    }
}

/* 00005544-00005548       .text moment_small__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_small(const cXyz*) {
}

/* 00005548-0000554C       .text moment_big__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_big(const cXyz*) {
}

/* 0000554C-00005550       .text moment_water__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_water(const cXyz*) {
}

/* 00005550-00005554       .text moment_barrel__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_barrel(const cXyz*) {
}

/* 00005554-00005558       .text moment_stool__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_stool(const cXyz*) {
}

/* 00005558-0000555C       .text moment_skull__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_skull(const cXyz*) {
}

/* 0000555C-00005560       .text moment_pail__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_pail(const cXyz*) {
}

/* 00005560-00005564       .text moment_spine__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_spine(const cXyz*) {
}

/* 00005564-00005568       .text moment_hbox2S__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_hbox2S(const cXyz*) {
}

/* 00005568-0000556C       .text moment_tryColSun__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_tryColSun(const cXyz*) {
}

/* 0000556C-00005570       .text moment_tryColMer__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_tryColMer(const cXyz*) {
}

/* 00005570-00005574       .text moment_tryColJup__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_tryColJup(const cXyz*) {
}

/* 00005574-00005578       .text moment_tryKeyGate__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_tryKeyGate(const cXyz*) {
}

/* 00005578-0000557C       .text moment_pinecone__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_pinecone(const cXyz*) {
}

/* 0000557C-00005580       .text moment_kutani__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_kutani(const cXyz*) {
}

/* 00005580-00005584       .text moment_woodS__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::moment_woodS(const cXyz*) {
}

/* 00005584-00005820       .text moment_proc_call__Q27daTsubo5Act_cFv */
void Act_c::moment_proc_call() {
    m6F0 = cXyz::Zero;

    typedef void (Act_c::*ModeProcFunc)(const cXyz*);
    static ModeProcFunc moment_proc[] = {
        &Act_c::moment_small,
        &Act_c::moment_big,
        &Act_c::moment_water,
        &Act_c::moment_barrel,
        &Act_c::moment_stool,
        &Act_c::moment_skull,
        &Act_c::moment_pail,
        &Act_c::moment_spine,
        &Act_c::moment_hbox2S,
        &Act_c::moment_tryColSun,
        &Act_c::moment_tryColMer,
        &Act_c::moment_tryColJup,
        &Act_c::moment_tryKeyGate,
        &Act_c::moment_pinecone,
        &Act_c::moment_kutani,
        &Act_c::moment_woodS,
    };

    if (m678 == 3) {
        cM3dGPla* pcVar1 = NULL;
        if (mAcch.ChkGroundHit()) {
            pcVar1 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd.GetBgIndex(), mAcch.m_gnd.GetPolyIndex());
        }

        if (pcVar1 != NULL) {
            (this->*moment_proc[mType])(pcVar1->GetNP());
        } else {
            cLib_addCalc0(&m6EC, 0.4f, data().mAcchRoofHeight * 0.125f);
        }
    }
}

/* 00005820-00005A94       .text set_wind_vec__Q27daTsubo5Act_cFv */
void Act_c::set_wind_vec() {
    cCcD_Obj* pcVar3 = mCyl.GetTgHitObj();
    if (pcVar3 != NULL && pcVar3->ChkAtType(AT_TYPE_WIND)) {
        cXyz sp48 = *mCyl.GetTgRVecP();
        f32 fVar7 = sp48.getSquareMag();
        if (fVar7 > 31684.0f) {
            sp48 *= 178.0f / std::sqrtf(fVar7);
        }
        cCcD_ShapeAttr* shapeAttr = pcVar3->GetShapeAttr();
        cXyz sp3C = cXyz::Zero;
        f32 fVar1 = 1.0f;
        if (shapeAttr->GetNVec(current.pos, &sp3C)) {
            sp3C *= 45.0f;
            m7F4.getSquareMag();
            fopAc_ac_c* pfVar4 = mCyl.GetTgHitAc();
            if (pfVar4 != NULL && fopAcM_GetProfName(pfVar4) == PROC_PLAYER) {
                s16 iVar5 = cM_atan2s(sp3C.x, sp3C.z);
                f32 cos = cM_scos(pfVar4->shape_angle.y - iVar5);
                if (cos > 0.866f) {
                    fVar1 = cos * 2.0f + 1.0f;
                } else {
                    fVar1 = 0.0f;
                }
            }
        }

        f32 fVar2;
        if (fVar7 > 0.01f) {
            fVar7 = 1.0f;
            fVar2 = 0.05f;
        } else {
            fVar7 = 0.0f;
            fVar2 = 1.0f;
        }

        m7F4 = (sp48 * fVar7) + (sp3C * fVar2) * fVar1;
    }
}

/* 00005A94-00005B1C       .text init_mtx__Q27daTsubo5Act_cFv */
void Act_c::init_mtx() {
    mDoMtx_identity(mPoseMtx);
    m694 = ZeroQuat;
    m6B0 = cXyz::Zero;
    set_tensor(&cXyz::BaseX);
    set_mtx();
}

/* 00005B1C-00005D28       .text set_mtx__Q27daTsubo5Act_cFv */
void Act_c::set_mtx() {
    mpModel->setBaseScale(scale * data().mModelScale);

    s32 type = mType;
    f32 fVar1;
    if (type == 13 || type == 7) {
        fVar1 = data().mAcchRoofHeight * 0.5f * scale.y;
    } else {
        fVar1 = 0.0f;
    }

    if (m678 == 4 && m685 != 0) {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m6EC + fVar1, current.pos.z);
        mDoMtx_stack_c::concat(mPoseMtx);
    } else {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + data().m04 + m6EC + fVar1, current.pos.z);
        mDoMtx_stack_c::concat(mPoseMtx);
        mDoMtx_stack_c::transM(0.0f, -data().m04, 0.0f);
    }

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if (mType == 2) {
        static cXyz offset_pos(0.0f, 85.0f, 0.0f);
        mDoMtx_stack_c::multVec(&offset_pos, &m700);
    }
    spec_mtx();
}

/* 00005D28-00005DB8       .text set_tensor__Q27daTsubo5Act_cFPC4cXyz */
void Act_c::set_tensor(const cXyz* pos) {
    mDoMtx_quatStack_c::rotAxisRadS(pos, cM_s2rad(m68E));
    MTXQuat(mPoseMtx, mDoMtx_quatStack_c::get());
    mDoMtx_ZXYrotM(mPoseMtx, shape_angle.x, shape_angle.y, shape_angle.z);
}

/* 00005DB8-00005E88       .text init_rot_throw__Q27daTsubo5Act_cFv */
void Act_c::init_rot_throw() {
    m688.Val(data().m28);
    m688 *= cM_rnd();
    m68A.Val((s16)cM_rndFX(32768.0f));
    m68C.Val(data().m2A);
    m68E.Val(cSAngle::_0);
    m690.Val(data().m2C);
    m692.Val(current.angle.y);
}

/* 00005E88-00005F0C       .text init_rot_clean__Q27daTsubo5Act_cFv */
void Act_c::init_rot_clean() {
    m688.Val(cSAngle::_0);
    m68A.Val(cSAngle::_0);
    m68C.Val(cSAngle::_0);
    m68E.Val(cSAngle::_0);
    m690.Val(cSAngle::_0);
    m692.Val(current.angle.y);
}

/* 00005F0C-00005F2C       .text set_tensor_hide__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_hide() {
    set_tensor_wait();
}

/* 00005F2C-00005F4C       .text set_tensor_appear__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_appear() {
    set_tensor_wait();
}

/* 00005F4C-00006034       .text set_tensor_wait__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_wait() {
    if (prm_get_stick()) {
        mDoMtx_stack_c::YrotS(m692);
        mDoMtx_stack_c::XrotM(m68A);
        mDoMtx_stack_c::ZrotM(m688);
        cXyz sp14;
        mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp14);
        set_tensor(&sp14);
    } else {
        mDoMtx_stack_c::YrotS(m692);
        mDoMtx_stack_c::XrotM(m68A);
        mDoMtx_stack_c::ZrotM(m688);
        cXyz sp14;
        mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp14);
        set_tensor(&sp14);
    }
}

/* 00006034-000061E4       .text set_tensor_walk__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_walk() {
    cXyz sp28 = current.pos - old.pos;
    f32 abs = sp28.abs() * 2.0f / data().mAcchRoofHeight;
    f32 dVar3 = m690.Radian();
    m690.Val(cM_rad2s(dVar3 + (abs - dVar3) * 0.7f));
    m68E += m690;
    cSAngle sp08(current.angle.y);
    m692 = sp08;

    mDoMtx_stack_c::YrotS(m692);
    mDoMtx_stack_c::XrotM(m68A);
    mDoMtx_stack_c::ZrotM(m688);
    cXyz sp1C;
    mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp1C);
    set_tensor(&sp1C);
}

/* 000061E4-00006204       .text set_tensor_carry__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_carry() {
    set_tensor_wait();
}

/* 00006204-00006330       .text set_tensor_drop__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_drop() {
    f32 dVar2 = m68C.Radian();
    m68C -= cM_rad2s(dVar2 * data().m30 + dVar2 * std::fabsf(dVar2) * data().m34);
    m68A += m68C;

    dVar2 = m690.Radian();
    m690 -= cM_rad2s(dVar2 * data().m30 + dVar2 * std::fabsf(dVar2) * data().m34);
    m68E += m690;

    mDoMtx_stack_c::YrotS(m692);
    mDoMtx_stack_c::XrotM(m68A);
    mDoMtx_stack_c::ZrotM(m688);
    cXyz sp08;
    mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp08);
    set_tensor(&sp08);
}

/* 00006330-0000645C       .text set_tensor_sink__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_sink() {
    f32 dVar2 = m68C.Radian();
    m68C -= cM_rad2s(dVar2 * data().m48 + dVar2 * std::fabsf(dVar2) * data().m4C);
    m68A += m68C;

    dVar2 = m690.Radian();
    m690 -= cM_rad2s(dVar2 * data().m48 + dVar2 * std::fabsf(dVar2) * data().m4C);
    m68E += m690;

    mDoMtx_stack_c::YrotS(m692);
    mDoMtx_stack_c::XrotM(m68A);
    mDoMtx_stack_c::ZrotM(m688);
    cXyz sp08;
    mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp08);
    set_tensor(&sp08);
}

/* 0000645C-00006600       .text set_tensor_afl__Q27daTsubo5Act_cFv */
void Act_c::set_tensor_afl() {
    f32 dVar2 = m68C.Radian();
    m68C -= cM_rad2s(dVar2 * data().m48 + dVar2 * std::fabsf(dVar2) * data().m4C);
    m68A += m68C;

    dVar2 = m68E.Radian();
    m690 += cM_rad2s(dVar2 * -0.0005f);
    m690 += cM_ssin(m806) * 4.0f;

    dVar2 = m690.Radian();
    m690 -= cM_rad2s(dVar2 * data().m48 + dVar2 * std::fabsf(dVar2) * data().m4C);
    m68E += m690;

    mDoMtx_stack_c::YrotS(m692);
    mDoMtx_stack_c::XrotM(m68A);
    mDoMtx_stack_c::ZrotM(m688);
    cXyz sp08;
    mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &sp08);
    set_tensor(&sp08);
}

/* 00006600-00006708       .text eff_drop_water__Q27daTsubo5Act_cFv */
void Act_c::eff_drop_water() {
    for (s32 i = 0; i < ARRAY_SSIZE(m70C); i++) {
        if (m70C[i].isEnd()) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8085, &m700, &shape_angle, NULL, 0xff, &m70C[i], -1, NULL, NULL, NULL);
            break;
        }
    }

    for (s32 i = 0; i < ARRAY_SSIZE(m748); i++) {
        if (m748[i].isEnd()) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8092, &m700, &shape_angle, NULL, 0xff, &m748[i], -1, NULL, NULL, NULL);
            break;
        }
    }
}

/* 00006708-00006744       .text eff_land_smoke__Q27daTsubo5Act_cFv */
void Act_c::eff_land_smoke() {
    daObj::make_land_effect(this, &mAcch.m_gnd, data().mC8);
}

/* 00006744-00006888       .text eff_break_barrel__Q27daTsubo5Act_cFv */
void Act_c::eff_break_barrel() {
    cXyz sp18(current.pos.x, current.pos.y + data().mAcchRoofHeight * 0.5f, current.pos.z);
    JPABaseEmitter* pJVar1 = dComIfGp_particle_set(dPa_name::ID_COMMON_03E5, &sp18, NULL, NULL, 0xff, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
    if (pJVar1 != NULL) {
        static JGeometry::TVec3<f32> em_scl(1.0f, 0.8f, 1.0f);
        pJVar1->setEmitterScale(em_scl);
    }
    daObjEff::Act_c::make_barrel_smoke(&sp18);
}

/* 00006888-00006A48       .text eff_break_tsubo__Q27daTsubo5Act_cFv */
void Act_c::eff_break_tsubo() {
    u16 uVar1 = data().m80;
    J3DModelData* pJVar2 = (J3DModelData*)(dComIfG_getObjectRes("Always", ALWAYS_BDL_MPM_TUBO));
    J3DAnmTexPattern* pJVar3 = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Always", ALWAYS_BTP_MPM_TUBO));
    JPABaseEmitter* pJVar4 =
        static_cast<JPABaseEmitter*>(dComIfGp_particle_set(dPa_name::ID_COMMON_0017, &current.pos, NULL, (cXyz*)data().get_particle_scale()));
    if (pJVar4 != NULL) {
        dPa_J3DmodelEmitter_c* modelEmitter = new dPa_J3DmodelEmitter_c(pJVar4, pJVar2, tevStr, pJVar3, uVar1, 0);
        if (modelEmitter != NULL) {
            dComIfGp_particle_addModelEmitter(modelEmitter);
        }
    }

    GXColor color;
    color.r = tevStr.mColorC0.r;
    color.g = tevStr.mColorC0.g;
    color.b = tevStr.mColorC0.b;
    color.a = tevStr.mColorC0.a;
    dComIfGp_particle_set(
        dPa_name::ID_COMMON_0018,
        &current.pos,
        NULL,
        (cXyz*)data().get_particle_scale(),
        0xff,
        dPa_control_c::getTsuboSelectTexEcallBack(data().m80),
        -1,
        &color,
        &tevStr.mColorK0,
        NULL
    );
}

/* 00006A48-00006B60       .text eff_break_stool__Q27daTsubo5Act_cFv */
void Act_c::eff_break_stool() {
    cXyz sp18(current.pos.x, current.pos.y + 35.0f, current.pos.z);
    static cXyz particle_scl(1.0f, 0.8f, 1.0f);
    JPABaseEmitter* pJVar1 =
        dComIfGp_particle_set(dPa_name::ID_COMMON_03E7, &sp18, NULL, NULL, 0xff, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0, &particle_scl);
    if (pJVar1 != NULL) {
        pJVar1->setDirectionalSpeed(25.0f);
    }
    daObjEff::Act_c::make_stool_smoke(&sp18);
}

/* 00006B60-00006C10       .text eff_break_skull__Q27daTsubo5Act_cFv */
void Act_c::eff_break_skull() {
    cXyz sp18(current.pos.x, current.pos.y + 20.0f, current.pos.z);

    dComIfGp_particle_set(dPa_name::ID_COMMON_03E8, &sp18, NULL, NULL, 0xff, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
    daObjEff::Act_c::make_skull_smoke(&sp18);
}

/* 00006C10-00006C30       .text eff_break_pail__Q27daTsubo5Act_cFv */
void Act_c::eff_break_pail() {
    eff_break_stool();
}

/* 00006C30-00006C50       .text eff_break_spine__Q27daTsubo5Act_cFv */
void Act_c::eff_break_spine() {
    eff_break_pinecone();
}

/* 00006C50-00006C70       .text eff_break_hbox2S__Q27daTsubo5Act_cFv */
void Act_c::eff_break_hbox2S() {
    eff_break_stool();
}

/* 00006C70-00006C90       .text eff_break_try__Q27daTsubo5Act_cFv */
void Act_c::eff_break_try() {
    eff_break_skull();
}

/* 00006C90-00006D7C       .text eff_break_pinecone__Q27daTsubo5Act_cFv */
void Act_c::eff_break_pinecone() {
    cXyz sp18(current.pos.x, current.pos.y + data().mAcchRoofHeight * 0.5f, current.pos.z);

    dComIfGp_particle_set(dPa_name::ID_SCENE_816A, &sp18, NULL, NULL, 0xff, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
    daObjEff::Act_c::make_pinecone_smoke(&sp18);
}

/* 00006D7C-00006D9C       .text eff_break_woodS__Q27daTsubo5Act_cFv */
void Act_c::eff_break_woodS() {
    eff_break_stool();
}

/* 00006D9C-00006DF8       .text eff_hit_water_splash__Q27daTsubo5Act_cFv */
void Act_c::eff_hit_water_splash() {
#if VERSION == VERSION_DEMO
    cXyz sp08(current.pos.x, mAcch.m_wtr.GetHeight(), current.pos.z);
#else
    cXyz sp08(current.pos.x, m4FC, current.pos.z);
#endif
    fopKyM_createWpillar(&sp08, data().mBC, data().mC0, 0);
}

/* 00006DF8-00006E50       .text eff_hit_lava_splash__Q27daTsubo5Act_cFv */
void Act_c::eff_hit_lava_splash() {
    cXyz sp08(current.pos.x, m4F8, current.pos.z);
    fopKyM_createMpillar(&sp08, data().mC4);
}

/* 00006E50-00006ED4       .text eff_kutani_set__Q27daTsubo5Act_cFv */
void Act_c::eff_kutani_set() {
    if (m798 != 0 && --m798 == 0) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_814B, &current.pos, NULL, NULL, 0xff, &m784);
    }
}

/* 00006ED4-00006F1C       .text eff_kutani_init__Q27daTsubo5Act_cFv */
void Act_c::eff_kutani_init() {
    u8 fVar1 = cM_rndF(30.0f);
    m798 = fVar1 + 1;
}

#if VERSION == VERSION_DEMO
void Act_c::bg_crr_lava() {
    if (m67F) {
        m4F8 = -G_CM3D_F_INF;
    } else {
        cXyz sp08(current.pos.x, old.pos.y + data().m04 + 1.0f, current.pos.z);
        M_GND_CHK.SetPos(&sp08);
        m4F8 = dComIfG_Bgsp()->GroundCross(&M_GND_CHK);
    }
}
#endif

/* 00006F1C-00006F7C       .text chk_sink_lava__Q27daTsubo5Act_cFv */
bool Act_c::chk_sink_lava() {
    if (m67F != 0) {
        return false;
    }

    f32 fVar1 = data().m04 < 20.0f ? data().m04 : 20.0f;
    return m4F8 > current.pos.y + fVar1;
}

/* 00006F7C-00006F84       .text chk_sink_water__Q27daTsubo5Act_cFv */
bool Act_c::chk_sink_water() {
#if VERSION == VERSION_DEMO
    bool bVar2 = mAcch.ChkWaterHit() && mAcch.m_wtr.GetHeight() > current.pos.y + data().m04;
    bool uVar3 = false;

    if (bVar2) {
        uVar3 = true;
    } else if (daSea_ChkArea(current.pos.x, current.pos.z) && current.pos.y < daSea_calcWave(current.pos.x, current.pos.z)) {
        uVar3 = true;
    }
    return uVar3;
#else
    return m504;
#endif
}

/* 00006F84-00006FF8       .text chk_sinkdown_water__Q27daTsubo5Act_cFv */
bool Act_c::chk_sinkdown_water() {
#if VERSION == VERSION_DEMO
    return mAcch.ChkWaterHit() && mAcch.m_wtr.GetHeight() > current.pos.y + data().mAcchRoofHeight + 50.0f;
#else
    return m4FC != -G_CM3D_F_INF && m4FC > current.pos.y + data().mAcchRoofHeight + 50.0f;
#endif
}

/* 00006FF8-000071D4       .text calc_drop_param__Q27daTsubo5Act_cCFPfPfPf */
void Act_c::calc_drop_param(float* outArg1, float* outArg2, float* outArg3) const {
#if VERSION == VERSION_DEMO
    bool bVar5 = const_cast<Act_c*>(this)->mAcch.ChkWaterHit();
    bool fVar5 = m4F8 > current.pos.y;

    if (bVar5 || fVar5) {
        f32 fVar7;
        if (bVar5 && fVar5) {
            fVar7 = const_cast<Act_c*>(this)->mAcch.m_wtr.GetHeight();
            if (m4F8 > fVar7) {
                fVar7 = m4F8;
            }
        } else if (bVar5) {
            fVar7 = const_cast<Act_c*>(this)->mAcch.m_wtr.GetHeight();
        } else {
            fVar7 = m4F8;
        }
#else
    bool bVar5 = m4FC != -G_CM3D_F_INF;
    bool fVar5 = m4F8 > current.pos.y;

    if (bVar5 || fVar5) {
        f32 fVar7;
        if (bVar5 && fVar5) {
            if (m4F8 > m4FC) {
                fVar7 = m4F8;
            } else {
                fVar7 = m4FC;
            }
        } else {
            if (bVar5) {
                fVar7 = m4FC;
            } else {
                fVar7 = m4F8;
            }
        }
#endif

        f32 fVar3 = current.pos.y - fVar7;
        f32 fVar0 = 0.0f;

        if (fVar3 >= 0.0f) {
            fVar0 = 0.0f;
        } else {
            if (fVar3 <= -data().mAcchRoofHeight) {
                fVar0 = 0.5f;
            } else {
                fVar0 = -fVar3 * (0.5f / data().mAcchRoofHeight);
            }
        }

        f32 fVar6 = 1.0f - fVar0;

        *outArg2 = fVar0 * data().m40 + fVar6 * data().m20;
        *outArg3 = fVar0 * data().m44 + fVar6 * data().m24;

        f32 gravity = fVar0 * data().m3C + data().mGravity;
        f32 gravityMax = data().mGravity * 0.1f;
        if (gravity > gravityMax) {
            *outArg1 = gravityMax;
        } else {
            *outArg1 = gravity;
        }
    } else {
        *outArg2 = data().m20;
        *outArg3 = data().m24;
        *outArg1 = data().mGravity;
    }
}

/* 000071D4-00007398       .text calc_afl_param__Q27daTsubo5Act_cCFPfPfPf */
void Act_c::calc_afl_param(float* outArg1, float* outArg2, float* outArg3) const {
#if VERSION == VERSION_DEMO
    bool bVar5 = const_cast<Act_c*>(this)->mAcch.ChkWaterHit();
    bool fVar5 = m4F8 > current.pos.y;

    if (bVar5 || fVar5) {
        f32 fVar7;
        if (bVar5 && fVar5) {
            fVar7 = const_cast<Act_c*>(this)->mAcch.m_wtr.GetHeight();
            if (m4F8 > fVar7) {
                fVar7 = m4F8;
            }
        } else if (bVar5) {
            fVar7 = const_cast<Act_c*>(this)->mAcch.m_wtr.GetHeight();
        } else {
            fVar7 = m4F8;
        }
#else
    bool bVar5 = m4FC != -G_CM3D_F_INF;
    bool fVar5 = m4F8 > current.pos.y;

    if (bVar5 || fVar5) {
        f32 fVar7;
        if (bVar5 && fVar5) {
            if (m4F8 > m4FC) {
                fVar7 = m4F8;
            } else {
                fVar7 = m4FC;
            }
        } else {
            if (bVar5) {
                fVar7 = m4FC;
            } else {
                fVar7 = m4F8;
            }
        }
#endif
        f32 fVar3 = current.pos.y - fVar7;
        f32 fVar0 = 0.0f;

        if (fVar3 >= 0.0f) {
            fVar0 = 0.0f;
        } else {
            if (fVar3 <= -data().mAcchRoofHeight) {
                fVar0 = 1.0f;
            } else {
                fVar0 = -fVar3 * (1.0f / data().mAcchRoofHeight);
            }
        }

        f32 fVar6 = 1.0f - fVar0;

        *outArg2 = fVar0 * data().m40 + fVar6 * data().m20;
        *outArg3 = fVar0 * data().m44 + fVar6 * data().m24;
        *outArg1 = fVar0 * data().m3C + data().mGravity;
    } else {
        *outArg2 = data().m20;
        *outArg3 = data().m24;
        *outArg1 = data().mGravity;
    }
}

/* 00007398-000074CC       .text se_fall_water__Q27daTsubo5Act_cFv */
void Act_c::se_fall_water() {
    cBgS_PolyInfo* polyInfoArr[] = {
#if VERSION == VERSION_DEMO
        &mAcch.m_wtr,
#else
        m505 ? NULL : &mAcch.m_wtr,
#endif
        &mAcch.m_gnd,
    };

    u32 materialSoundId = 0x13;
    for (s32 i = 0; i < ARRAY_SSIZE(polyInfoArr); i++) {
        if (
#if VERSION > VERSION_DEMO
        polyInfoArr[i] != NULL &&
#endif
            polyInfoArr[i]->GetBgIndex() >= 0 && polyInfoArr[i]->GetBgIndex() < 0x100)
        {
            materialSoundId = dComIfG_Bgsp()->GetMtrlSndId(*polyInfoArr[i]);
            break;
        }
    }

    fopAcM_seStart(this, data().mSoundID_FallWater, materialSoundId);
    set_senv(data().m64, data().m65);
}

/* 000074CC-000075E4       .text se_fall_lava__Q27daTsubo5Act_cFv */
void Act_c::se_fall_lava() {
    cBgS_PolyInfo* polyInfoArr[] = {
        &M_GND_CHK,
        &mAcch.m_gnd,
    };

    u32 materialSoundId = 0x17;
    for (s32 i = 0; i < ARRAY_SSIZE(polyInfoArr); i++) {
        if (polyInfoArr[i]->GetBgIndex() >= 0 && polyInfoArr[i]->GetBgIndex() < 0x100) {
            materialSoundId = dComIfG_Bgsp()->GetMtrlSndId(*polyInfoArr[i]);
            break;
        }
    }

    fopAcM_seStart(this, data().mSoundID_FallLava, materialSoundId);
    set_senv(data().m64, data().m65);
}

/* 000075E4-00007700       .text se_break__Q27daTsubo5Act_cFP13cBgS_PolyInfo */
void Act_c::se_break(cBgS_PolyInfo* arg1) {
    cBgS_PolyInfo* polyInfoArr[] = {
        arg1,
        &mAcch.m_gnd,
    };

    u32 materialSoundId = 0;
    for (s32 i = 0; i < ARRAY_SSIZE(polyInfoArr); i++) {
        if (polyInfoArr[i] != NULL && polyInfoArr[i]->GetBgIndex() >= 0 && polyInfoArr[i]->GetBgIndex() < 0x100) {
            materialSoundId = dComIfG_Bgsp()->GetMtrlSndId(*polyInfoArr[i]);
            break;
        }
    }

    fopAcM_seStart(this, data().mSoundID_Break, materialSoundId);
    set_senv(data().m60, data().m61);
}

/* 00007700-00007758       .text se_pickup_carry__Q27daTsubo5Act_cFv */
void Act_c::se_pickup_carry() {
    if (mType == 7) {
        if (m811 != 0 && daPy_getPlayerActorClass()->getGrabUpStart()) {
            m811 = 0;
            se_pickup();
        }
    }
}

/* 00007758-00007770       .text se_pickup_carry_init__Q27daTsubo5Act_cFv */
void Act_c::se_pickup_carry_init() {
    if (mType == 7) {
        m811 = 1;
    }
}

/* 00007770-000077EC       .text se_pickup__Q27daTsubo5Act_cFv */
void Act_c::se_pickup() {
    if (mType == 7) {
        fopAcM_seStart(this, JA_SE_OBJ_BOKKURI_PICK_UP, 0);
    }
}

/* 000077EC-00007840       .text set_senv__Q27daTsubo5Act_cCFii */
void Act_c::set_senv(int arg1, int arg2) const {
    dKy_Sound_set(current.pos, arg1, fopAcM_GetID((Act_c*)this), arg2);
}

/* 00007840-00007878       .text cam_lockoff__Q27daTsubo5Act_cCFv */
void Act_c::cam_lockoff() const {
    dComIfGp_getCamera(0)->mCamera.ForceLockOff(base.mBsPcId);
}

/* 00007878-00007B08       .text _execute__Q27daTsubo5Act_cFv */
bool Act_c::_execute() {
    cull_set_move();

    bool bVar4;
    if (prm_get_spec() == 5) {
        bVar4 = is_switch() == FALSE;
    } else {
        bVar4 = false;
    }

    if (!bVar4) {
        if (m682 != 0 || m678 != 2 || mAcch.ChkGroundHit() == FALSE || mAcch.ChkGroundLanding() || prm_get_cull() == 0 || !fopAcM_cullingCheck(this) ||
            m800 != 0 || prm_get_moveBg())
        {
            m682 = 0;
            BOOL bVar6 = TRUE;

            spec_set_actor();

            if (!damage_cc_proc()) {
                if (!damage_bg_proc() && !damage_kill_proc()) {
                    if (m683 != 0) {
                        m683--;
                    }

                    if (mode_proc_call()) {
                        bVar6 = FALSE;
                        set_mtx();
                        spec_carry_spec();
                        if (m678 != 0) {
                            mStts.SetRoomId(current.roomNo);
                            mCyl.MoveCAtTg(current.pos);
                            dComIfG_Ccsp()->Set(&mCyl);
                        }

                        if (m678 == 5 || m678 == 6 || m678 == 3 || m683 != 0) {
                            dComIfG_Ccsp_SetMass(&mCyl, 3);
                        }

                        attention_info.position.x = current.pos.x;
                        attention_info.position.y = current.pos.y + data().mAttnY;
                        attention_info.position.z = current.pos.z;
                        eyePos = attention_info.position;
                    }
                }
            }

            spec_clr_actor();

            fopAcM_SetModel(this, m678 == 4 && m686 != 0 ? mpModel : NULL);

            if (bVar6) {
                fopAcM_delete(this);
            }
        }
    }

    cull_set_draw();
    return true;
}

/* 00007B08-00007D2C       .text _draw__Q27daTsubo5Act_cFv */
bool Act_c::_draw() {
    bool bVar3 = true;

    switch (m678) {
    default:
        if (!prm_get_moveBg()) {
            break;
        }

    case 0:
        bVar3 = false;
        break;
    }

    if (bVar3) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        if (mpBrk != NULL) {
            s16 maxFrame = mpBrk->getBrkAnm()->getFrameMax();
            f32 fVar1 = (1.0f - (f32)m800 / attrSpine().m30) * maxFrame;
            if (m800 == 0 || fVar1 < 0.0f) {
                fVar1 = 0.0f;
            } else if (fVar1 >= maxFrame) {
                fVar1 = maxFrame - 0.001f;
            }
            mpBrk->entry(mpModel->getModelData(), fVar1);
        }

        mDoExt_modelUpdateDL(mpModel);

        if (mpBrk != NULL) {
            mpBrk->remove(mpModel->getModelData());
        }

        if (fopAcM_GetModel(this) == NULL) {
            f32 fVar1 = scale.x * data().m6E;
            if (cLib_checkBit(data().mFlag, DATA_FLAG_8_e)) {
                dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), fVar1, mAcch.m_gnd, shape_angle.y, 1.0f, NULL);
            } else {
                dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), fVar1, mAcch.m_gnd, 0, 1.0f);
            }
        }
    }
    return true;
}

/* 00007D2C-00007D4C       .text Create__Q27daTsubo6MethodFPv */
cPhs_State Method::Create(void* v_this) {
    return ((Act_c*)v_this)->_create();
}

/* 00007D4C-00007D70       .text Delete__Q27daTsubo6MethodFPv */
BOOL Method::Delete(void* v_this) {
    return ((Act_c*)v_this)->_delete();
}

/* 00007D70-00007D94       .text Execute__Q27daTsubo6MethodFPv */
BOOL Method::Execute(void* v_this) {
    return ((Act_c*)v_this)->_execute();
}

/* 00007D94-00007DB8       .text Draw__Q27daTsubo6MethodFPv */
BOOL Method::Draw(void* v_this) {
    return ((Act_c*)v_this)->_draw();
}

/* 00007DB8-00007DDC       .text IsDelete__Q27daTsubo6MethodFPv */
BOOL Method::IsDelete(void* v_this) {
    return ((Act_c*)v_this)->_is_delete();
}

actor_method_class Method::Table = {
    (process_method_func)Method::Create,
    (process_method_func)Method::Delete,
    (process_method_func)Method::Execute,
    (process_method_func)Method::IsDelete,
    (process_method_func)Method::Draw,
};

} // namespace daTsubo

actor_process_profile_definition g_profile_TSUBO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TSUBO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTsubo::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TSUBO,
    /* Actor SubMtd */ &daTsubo::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
