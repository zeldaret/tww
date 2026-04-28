/**
 * d_a_bgn.cpp
 * Boss - Puppet Ganon (Phase 1) / Ｇ（クグツ）(G (Puppet))
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bgn.h"
#include "d/actor/d_a_bgn2.h"
#include "d/actor/d_a_bgn3.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_ki.h"
#if VERSION > VERSION_DEMO
#include "d/actor/d_a_ks.h"
#endif
#include "d/actor/d_a_player.h"
#include "d/d_meter.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_bgn.h"
#include "dolphin/gf/GFGeometry.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/JUtility/JUTReport.h"

class daBgn_HIO_c : public JORReflexible {
public:
    daBgn_HIO_c();
    virtual ~daBgn_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x004 */ s16 m004;
    /* 0x006 */ s8 mNo;
    /* 0x007 */ u8 m007[0x008 - 0x007];
    /* 0x008 */ f32 m008;
    /* 0x00C */ u8 m00C;
    /* 0x00D */ u8 m00D;
    /* 0x00E */ u8 m00E[0x010 - 0x00E];
    /* 0x010 */ f32 m010;
    /* 0x014 */ s16 m014;
    /* 0x016 */ s16 m016;
    /* 0x018 */ s16 m018;
    /* 0x01A */ u8 m01A[0x01C - 0x01A];
    /* 0x01C */ f32 m01C;
    /* 0x020 */ f32 m020;
    /* 0x024 */ u8 m024;
    /* 0x025 */ u8 m025;
    /* 0x026 */ u8 m026;
    /* 0x027 */ u8 m027;
    /* 0x028 */ u8 m028;
    /* 0x029 */ u8 m029;
    /* 0x02A */ u8 m02A;
    /* 0x02B */ u8 m02B;
    /* 0x02C */ u8 m02C;
    /* 0x02D */ u8 m02D;
    /* 0x02E */ u8 m02E;
    /* 0x02F */ u8 m02F;
    /* 0x030 */ u8 m030;
    /* 0x031 */ u8 m031[0x034 - 0x031];
    /* 0x034 */ f32 m034;
    /* 0x038 */ f32 m038;
    /* 0x03C */ s16 m03C;
    /* 0x03E */ s16 m03E;
    /* 0x040 */ s16 m040;
    /* 0x042 */ s16 m042;
    /* 0x044 */ s16 m044;
    /* 0x046 */ u8 m046[0x048 - 0x046];
    /* 0x048 */ f32 m048;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ cXyz m054;
    /* 0x060 */ cXyz m060;
    /* 0x06C */ cXyz m06C;
    /* 0x078 */ cXyz m078;
    /* 0x084 */ cXyz m084;
    /* 0x090 */ cXyz m090;
    /* 0x09C */ cXyz m09C;
    /* 0x0A8 */ s16 m0A8;
    /* 0x0AA */ csXyz m0AA;
    /* 0x0B0 */ csXyz m0B0;
    /* 0x0B6 */ csXyz m0B6;
    /* 0x0BC */ csXyz m0BC;
    /* 0x0C2 */ csXyz m0C2;
    /* 0x0C8 */ csXyz m0C8;
    /* 0x0CE */ csXyz m0CE;
    /* 0x0D4 */ f32 m0D4;
    /* 0x0D8 */ s16 m0D8;
    /* 0x0DA */ s16 m0DA;
    /* 0x0DC */ s16 m0DC;
    /* 0x0DE */ s16 m0DE;
    /* 0x0E0 */ s16 m0E0;
    /* 0x0E2 */ s16 m0E2;
    /* 0x0E4 */ s16 m0E4;
    /* 0x0E6 */ s16 m0E6;
    /* 0x0E8 */ s16 m0E8;
    /* 0x0EA */ s16 m0EA;
    /* 0x0EC */ s16 m0EC;
    /* 0x0EE */ s16 m0EE;
    /* 0x0F0 */ s16 m0F0;
    /* 0x0F2 */ s16 m0F2;
    /* 0x0F4 */ f32 m0F4;
    /* 0x0F8 */ f32 m0F8;
    /* 0x0FC */ f32 m0FC;
    /* 0x100 */ f32 m100;
    /* 0x104 */ f32 m104;
    /* 0x108 */ f32 m108;
    /* 0x10C */ f32 m10C;
    /* 0x110 */ f32 m110;
    /* 0x114 */ f32 m114;
    /* 0x118 */ f32 m118;
    /* 0x11C */ f32 m11C;
    /* 0x120 */ f32 m120;
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ cXyz m12C;
    /* 0x138 */ cXyz m138;
    /* 0x144 */ cXyz m144;
    /* 0x150 */ cXyz m150;
    /* 0x15C */ cXyz m15C;
    /* 0x168 */ f32 m168;
    /* 0x16C */ f32 m16C;
    /* 0x170 */ f32 m170;
    /* 0x174 */ s16 mKeeseNum3HP;
    /* 0x176 */ s16 mKeeseNum2HP;
    /* 0x178 */ s16 mKeeseNum1HP;
    /* 0x17A */ s16 mKeeseNumMax;
}; // Size: 0x17C

/* 000000EC-000003F0       .text __ct__11daBgn_HIO_cFv */
daBgn_HIO_c::daBgn_HIO_c() {
    mNo = 0xFF;
    m00C = 1;
    m00D = 1;
    m010 = 50.0f;
    m014 = 10;
    m016 = 10;
    m018 = 80;
    m01C = 1000.0f;
    m020 = 10000.0f;
    m025 = 0;
    m026 = 0;
    m027 = 0;
    m024 = 0;
    m028 = 1;
    m008 = 200.0f;
    m004 = 0;
    m029 = 0;
    m02A = 0;
    m02B = 0;
    m02C = 0;
    m02D = 0;
    m02E = 0;
    m02F = 0;
    m030 = 0;
    m034 = -20.0f;
    m038 = -30.0f;
    m03C = 0;
    m03E = 22000;
    m040 = 0;
    m042 = 0;
    m044 = 0;
    m048 = 0.0f;
    m04C = 950.0f;
    m050 = 0.0f;
    m054.set(0.0f, 2000.0f, 800.0f);
    m060.set(0.0f, -800.0f, -800.0f);
    m06C.set(700.0f, -900.0f, 300.0f);
    m078.set(-700.0f, -900.0f, 300.0f);
    m084.set(500.0f, -1300.0f, -100.0f);
    m090.set(-500.0f, -1300.0f, -100.0f);
    m09C.set(0.0f, -700.0f, -1200.0f);
    m0A8 = 0;
    m0AA.set(0, 0, 0);
    m0B0.set(0, 0, 0);
    m0B6.set(0, 0, 0);
    m0BC.set(0, 0, 0);
    m0C2.set(0, 0, 0);
    m0C8.set(0, 0, 0);
    m0CE.set(0, 0, 0);
    m0D8 = 120;
    m0DA = 20;
    m0DC = 1200;
    m0DE = 1500;
    m0E0 = 2000;
    m0E2 = DEMO_SELECT(150, 300);
    m0E4 = DEMO_SELECT(100, 200);
    m0E6 = DEMO_SELECT(80, 150);
    m0E8 = DEMO_SELECT(20, 15);
    m0EA = 15;
    m0EC = DEMO_SELECT(10, 15);
    m0EE = 500;
    m0D4 = 40.0f;
    m0F0 = 5;
    m0F2 = 10;
    m0F4 = 1.3f;
    m0FC = 3.25f;
    m0F8 = 1.6f;
    m100 = 1.8f;
    m104 = 1.2f;
    m108 = 0.3f;
    m10C = 1.2f;
    m110 = 0.4f;
    m114 = 1.2f;
    m118 = 0.1f;
    m11C = 185.0f;
    m124 = 185.0f;
    m120 = 185.0f;
    m128 = 185.0f;
    m168 = 100.0f;
    m12C.set(0.0f, -10.0f, 120.0f);
    m138.set(100.0f, 25.0f, 20.0f);
    m144.set(0.0f, -115.0f, 0.0f);
    m150.set(80.0f, -20.0f, 100.0f);
    m15C.set(0.0f, -60.0f, 150.0f);
    m16C = -50.0f;
    m170 = -100.0f;
    mKeeseNum3HP = 3;
    mKeeseNum2HP = DEMO_SELECT(5, 4);
    mKeeseNum1HP = DEMO_SELECT(8, 5);
    mKeeseNumMax = DEMO_SELECT(8, 5);
}

static bgn_class* bgn;
static bgn2_class* bgn2;
static bgn3_class* bgn3;
static cXyz zero(0.0f, 0.0f, 0.0f);
static s32 BGN_HAND_MAX;
static s32 BGN_TAIL_MAX;
static bool hio_set;
static daBgn_HIO_c l_HIO;
static GXColor ke_color; // Unused
static dKy_tevstr_c bg_tevstr;
static cXyz w_pos(0.0f, 0.0f, 0.0f);
static s32 ki_all_count;
static csXyz dance_pause_1[] = {
    csXyz(0, 0, -0x4b0),
    csXyz(0, 0, 0),
    csXyz(0, 0, 0),
    csXyz(0x1f4, 0x3e8, 0x5dc),
    csXyz(-0x1f4, 0x3e8, 0x5dc),
    csXyz(0x4b, 0x384, -0x2bc),
    csXyz(0x1f4, -0x514, -0x64),
    csXyz(-0xc8, 0x258, -0x190),
};

static csXyz dance_pause_2[] = {
    csXyz(0, 0, -0x4b0),
    csXyz(0, 0, 0),
    csXyz(0, 0x12c, 0),
    csXyz(0x1f4, -0x1f4, 0x5dc),
    csXyz(-0x1f4, -0x1f4, 0x5dc),
    csXyz(0x4b, 0x190, -0x2bc),
    csXyz(0x1f4, -0x44c, -0x320),
    csXyz(-0xc8, 0xc8, -0x1f4),
};

static csXyz dance_pause_3[] = {
    csXyz(0, 0, -0x3e8),
    csXyz(0, 0, 0),
    csXyz(0x1f4, 0, -0xc8),
    csXyz(-0xc8, 0x3e8, 0x15e),
    csXyz(0xc8, 0x578, 0x15e),
    csXyz(-0x190, 0x1f4, 0x1f4),
    csXyz(0x190, -0xc8, -0x12c),
    csXyz(0x320, 0x190, -0xc8),
};

static csXyz dance_pause_4[] = {
    csXyz(0, 0, -0x3e8),
    csXyz(0, 0, 0),
    csXyz(-0x1f4, 0, -0xc8),
    csXyz(-0xc8, 0x578, 0x15e),
    csXyz(0xc8, 0x3e8, 0x15e),
    csXyz(-0x190, -0xc8, -0x12c),
    csXyz(0x190, 0x1f4, 0x1f4),
    csXyz(-0x320, 0x190, -0xc8),
};

static csXyz punch_lr1_d[] = {
    csXyz(0, 0, -0x6a4),
    csXyz(0, 0, 0),
    csXyz(-0x96, 0, 0x28a),
    csXyz(0x64, 0x578, -0x1f4),
    csXyz(-0x64, 0x4b0, 0x1f4),
    csXyz(0xc8, 0x12c, 0x384),
    csXyz(-0x64, 0x1f4, 0x384),
    csXyz(-0x258, 0x1f4, 0x12c),
};

static csXyz punch_lr12_d[] = {
    csXyz(0, 0, -0x6a4),
    csXyz(0, 0, 0),
    csXyz(0x96, 0, 0x28a),
    csXyz(0x64, 0x4b0, -0x1f4),
    csXyz(-0x64, 0x578, 0x1f4),
    csXyz(0xc8, 0x1f4, 0x384),
    csXyz(-0x64, 0x12c, 0x384),
    csXyz(0x258, 0x1f4, 0x12c),
};

static csXyz punch_lr2_d[] = {
    csXyz(0, 0, 0),
    csXyz(0, 0, 0),
    csXyz(0, 0, 0x1f4),
    csXyz(-0x1f4, 0x96, 0x3e8),
    csXyz(0x1f4, 0x96, 0x3e8),
    csXyz(0x96, 0x258, 0x3e8),
    csXyz(-0x96, 0x258, 0x384),
    csXyz(0, 0x3b6, 0x64),
};

static csXyz punch_r1_d[] = {
    csXyz(-0x96, 0, 0),
    csXyz(0, 0, 0),
    csXyz(-0xc8, 0, 0x190),
    csXyz(0, 0x190, 0x258),
    csXyz(-0x96, 0x640, -0x190),
    csXyz(-0x258, 0x12c, 0x28a),
    csXyz(-0x4b0, 0, 0xc8),
    csXyz(0x2bc, 0x2bc, 0xc8),
};

static csXyz punch_r2_d[] = {
    csXyz(0x96, 0, -0x1f4),
    csXyz(0, 0, 0),
    csXyz(0x258, 0, 0),
    csXyz(0x28a, 0x3e8, -0x1f4),
    csXyz(-0x258, 0, 0x4b0),
    csXyz(0x3e8, 0xfa, 0x7d0),
    csXyz(0x384, 0xc8, -0x12c),
    csXyz(0, 0x320, -0x15e),
};

static csXyz punch_l1_d[] = {
    csXyz(0x96, 0, 0),
    csXyz(0, 0, 0),
    csXyz(0xc8, 0, 0x190),
    csXyz(0x96, 0x640, -0x190),
    csXyz(0, 0x190, 0x258),
    csXyz(0x4b0, 0, 0x7d0),
    csXyz(0x258, 0x12c, 0x28a),
    csXyz(-0x2bc, 0x2bc, 0xc8),
};

static csXyz punch_l2_d[] = {
    csXyz(-0x96, 0, -0x1f4),
    csXyz(0, 0, 0),
    csXyz(-0x258, 0, 0),
    csXyz(0x258, 0, 0x4b0),
    csXyz(-0x28a, 0x3e8, -0x1f4),
    csXyz(-0x384, 0xc8, -0x12c),
    csXyz(-0x3e8, 0xfa, 0x7d0),
    csXyz(0, 0x320, -0x15e),
};

static csXyz start_pause[] = {
    csXyz(0, 0, 0),
    csXyz(0, 0, 0),
    csXyz(0, 0, 0),
    csXyz(-0x64, 0xfa, 0),
    csXyz(0x190, 0xfa, 0),
    csXyz(-0xc8, 0, 0),
    csXyz(0xc8, 0, 0),
    csXyz(0, 0, 0),
};

static cXyz center_pos(0.0f, 0.0f, 0.0f);

void mDoExt_J3DModelPacketS::draw() {
    J3DShapePacket* shapePacket;
    J3DMatPacket* matPacket;
    J3DModelData* modelData;
    u16 i;
    Mtx m;
    J3DMaterial* mesh;

    cMtx_copy(j3dSys.getViewMtx(), m);
    mDoMtx_stack_c::transS(REG0_F(14), REG0_F(15) + -30.0f, REG0_F(16));
    mDoMtx_stack_c::scaleM(1.0f, -1.0f, 1.0f);
    mDoMtx_stack_c::revConcat(j3dSys.mViewMtx);
    j3dSys.setViewMtx(mDoMtx_stack_c::get());
    modelData = mpModel->getModelData();
    for (i = 0; i < modelData->getJointNum(); i++) {
        mesh = modelData->getJointNodePointer(i)->getMesh();
        while (mesh != NULL) {
            if (!mesh->getShape()->checkFlag(J3DShpFlag_Hide)) {
                matPacket = mpModel->getMatPacket(mesh->getIndex());
                j3dSys.setTexture(matPacket->mpTexture);
                j3dSys.setMatPacket(matPacket);
                mesh->load();
                setMaterial();
                shapePacket = matPacket->getShapePacket();
                shapePacket->getShape()->loadPreDrawSetting();
                for (; shapePacket != NULL; shapePacket = (J3DShapePacket*)shapePacket->getNextPacket()) {
                    if (shapePacket->getDisplayListObj() != NULL) {
                        shapePacket->getDisplayListObj()->callDL();
                    }
                    shapePacket->drawFast();
                }
                J3DShape::resetVcdVatCache();
            }
            mesh = mesh->getNext();
        }
    }
    j3dSys.setViewMtx(m);
};

void mDoExt_J3DModelPacketS::setMaterial() {
    static unsigned char l_DL[] = {0x61, 0x41, 0x00, 0x04, 0xAD, 0x61, 0xF3, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    GFSetCullMode(GX_CULL_FRONT);
    GXCallDisplayList(l_DL, 0x20);
};

/* 000005BC-000008BC       .text part_draw__FP9bgn_classP6part_s */
static void part_draw(bgn_class* i_this, part_s* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* pJVar7;
    cXyz local_38;

    pJVar7 = param_2->mpPartModel;
    if (pJVar7 != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &param_2->m0D4, &param_2->mPartTevStr);
        if (i_this->mCC88 > 0.0f) {
            param_2->mPartTevStr.mFogColor.b = 0;
            param_2->mPartTevStr.mFogColor.g = 0;
            param_2->mPartTevStr.mFogColor.r = 0;
            param_2->mPartTevStr.mFogStartZ = param_2->mPartTevStr.mFogStartZ + i_this->mCC88 * -50000.0f;
        }
        if (param_2->mPartArrowHitFlashTimer != 0) {
            s16 uVar4 = param_2->mPartTevStr.mFogColor.r + param_2->m0C8;
            if (uVar4 > 0xFF) {
                uVar4 = 0xFF;
            }
            s16 uVar5 = param_2->mPartTevStr.mFogColor.g + param_2->m0C8;
            if (uVar5 > 0xFF) {
                uVar5 = 0xFF;
            }
            s16 uVar6 = param_2->mPartTevStr.mFogColor.g + (param_2->m0C8 / 2);
            if (uVar6 > 0xFF) {
                uVar6 = 0xFF;
            }
            if (param_2->mPartArrowHitFlashTimer > 40) {
                cLib_addCalcAngleS2(&param_2->m0C8, 0x118, 1, 30);
                cLib_addCalc2(&param_2->m0CC, -50000.0f, 1.0f, 5000.0f);
            } else {
                cLib_addCalcAngleS2(&param_2->m0C8, 0, 1, 7);
                cLib_addCalc0(&param_2->m0CC, 1.0f, 1250.0f);
            }
            param_2->mPartTevStr.mFogColor.r = uVar4 & 0xFF;
            param_2->mPartTevStr.mFogColor.g = uVar5 & 0xFF;
            param_2->mPartTevStr.mFogColor.b = uVar6 & 0xFF;
            param_2->mPartTevStr.mFogStartZ = param_2->mPartTevStr.mFogStartZ + param_2->m0CC;
        }
        camera_class* camera = (camera_class*)dComIfGp_getCamera(0);
        local_38 = param_2->m224 - camera->mLookat.mEye;
        if (local_38.abs() > l_HIO.m008 * param_2->m0F4) {
            g_env_light.setLightTevColorType(pJVar7, &param_2->mPartTevStr);
            if ((actor->health <= 2) && (param_2 == &i_this->mTailParts[BGN_TAIL_MAX - 1])) {
                if (actor->health == 1) {
                    i_this->mJyakutenCBrkAnm->entry(pJVar7->getModelData());
                } else {
                    i_this->mJyakutenBBrkAnm->entry(pJVar7->getModelData());
                }
            }
            if (param_2 == &i_this->mHeadParts[0]) {
                i_this->mpMorf->entryDL();
            } else {
                mDoExt_modelUpdateDL(pJVar7);
            }
        }
        if (l_HIO.m00C != 0) {
            param_2->m004.setModel(pJVar7);
            dComIfGd_getOpaListSky()->entryImm(&param_2->m004, 0);
        }
    }
}

/* 000008F8-00000B70       .text water0_disp__FP9bgn_class */
static void water0_disp(bgn_class* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &w_pos, &i_this->mWaterTevStr);
    MtxTrans(0.0f, REG0_F(11), 0.0f, false);
    i_this->mpWater0Model->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mpWater0Model, &i_this->mWaterTevStr);
    dComIfGd_setListSky();
    J3DMaterial* pJVar8 = i_this->mpWater0Model->getModelData()->getMaterialNodePointer(0);
    J3DBlend* blend = pJVar8->getBlend();
    blend->getType();
    J3DZMode* zMode = pJVar8->getZMode();
    zMode->getFunc();
    J3DGXColorS10* tev_col = (J3DGXColorS10*)&pJVar8->getTevColor(0)->mColor;
    J3DGXColor* tev_kcol = (J3DGXColor*)&pJVar8->getTevKColor(0)->mColor;
    J3DGXColor* tev_kcol2 = (J3DGXColor*)&pJVar8->getTevKColor(3)->mColor;
    blend->setType(GX_BM_BLEND);
    blend->setSrcFactor(GX_BL_SRC_ALPHA);
    blend->setDstFactor(GX_BL_INV_SRC_ALPHA);
    zMode->setUpdateEnable(1);
    tev_col->mColor.b = 0;
    tev_col->mColor.g = 0;
    tev_col->mColor.r = 0;
    tev_kcol->mColor.b = 0xFF;
    tev_kcol->mColor.g = 0xFF;
    tev_kcol->mColor.r = 0xFF;
    f32 fVar1 = l_HIO.m010;
    if ((i_this->m02B5 == 1) && (l_HIO.m00D == 0)) {
        fVar1 = (REG0_F(5) + 0.01f) * (REG0_F(4) + 4000.0f + bgn2->actor.current.pos.y);
        if (fVar1 > 90.0f) {
            fVar1 = 90.0f;
        } else if (fVar1 < 50.0f) {
            fVar1 = 50.0f;
        }
    }
    tev_kcol2->mColor.a = (s8)(fVar1 * 2.559f);
    mDoExt_modelUpdateDL(i_this->mpWater0Model);
    dComIfGd_setList();
}

/* 00000B70-00000CAC       .text water1_disp__FP9bgn_class */
static void water1_disp(bgn_class* i_this) {
    MtxTrans(0.0f, REG0_F(11), 0.0f, false);
    i_this->mpWater1Model->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mpWater1Model, &i_this->mWaterTevStr);
    dComIfGd_setListSky();
    J3DMaterial* pJVar8 = i_this->mpWater1Model->getModelData()->getMaterialNodePointer(0);
    J3DBlend* blend = pJVar8->getBlend();
    blend->getType();
    J3DZMode* zMode = pJVar8->getZMode();
    blend->setType(GX_BM_NONE);
    zMode->setUpdateEnable(0);
    mDoExt_modelUpdateDL(i_this->mpWater1Model);
    dComIfGd_setList();
}

/* 00000CAC-00000FCC       .text daBgn_DrawS__FP9bgn_class */
static void daBgn_DrawS(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

#if VERSION == VERSION_DEMO
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
#endif
    if (i_this->mCC88 > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ += i_this->mCC88 * -50000.0f;
    }
    if (i_this->mArrowHitFlashTimer != 0) {
        s16 uVar2 = actor->tevStr.mFogColor.r + i_this->m02F8;
        if (uVar2 > 0xFF) {
            uVar2 = 0xFF;
        }
        s16 uVar3 = actor->tevStr.mFogColor.g + i_this->m02F8;
        if (uVar3 > 0xFF) {
            uVar3 = 0xFF;
        }
        s16 uVar4 = actor->tevStr.mFogColor.g + (i_this->m02F8 / 2);
        if (uVar4 > 0xFF) {
            uVar4 = 0xFF;
        }
        if (i_this->mArrowHitFlashTimer > 40) {
            cLib_addCalcAngleS2(&i_this->m02F8, 0x118, 1, 30);
            cLib_addCalc2(&i_this->m02FC, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m02F8, 0, 1, 7);
            cLib_addCalc0(&i_this->m02FC, 1.0f, 1250.0f);
        }
        actor->tevStr.mFogColor.r = uVar2 & 0xFF;
        actor->tevStr.mFogColor.g = uVar3 & 0xFF;
        actor->tevStr.mFogColor.b = uVar4 & 0xFF;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m02FC;
    }
    g_env_light.setLightTevColorType(i_this->mpChestModel, &actor->tevStr);
    mDoExt_modelUpdateDL(i_this->mpChestModel);
    dSnap_RegistFig(DSNAP_TYPE_BGN, actor, 1.0f, 1.0f, 1.0f);
    if (l_HIO.m00C != 0) {
        i_this->m02C0.setModel(i_this->mpChestModel);
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02C0, 0);
    }
    part_draw(i_this, &i_this->mHeadParts[0]);
    part_draw(i_this, &i_this->mPelvisParts[0]);
    for (s32 i = 0; i < BGN_HAND_MAX; i++) {
        part_draw(i_this, &i_this->mLeftArmParts[i]);
        part_draw(i_this, &i_this->mRightArmParts[i]);
    }
    for (s32 i = 0; i < 3; i++) {
        part_draw(i_this, &i_this->mLeftLegParts[i]);
        part_draw(i_this, &i_this->mRightLegParts[i]);
    }
    for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
        part_draw(i_this, &i_this->mTailParts[i]);
    }
#ifdef __MWERKS__
    i_this->mBlueRopeMat.update(60, (GXColor){DEMO_SELECT(0, 0xFF), 0xFF, 0xFF, 0}, &actor->tevStr);
#else
    GXColor local_24 = (GXColor){DEMO_SELECT(0, 0xFF), 0xFF, 0xFF, 0};
    i_this->mBlueRopeMat.update(60, local_24, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->mBlueRopeMat);
#ifdef __MWERKS__
    i_this->mRedRopeMat.update(60, (GXColor){DEMO_SELECT(0xD2, 0xFF), DEMO_SELECT(0x32, 0xFF), DEMO_SELECT(0x5A, 0xFF), 0}, &actor->tevStr);
#else
    GXColor local_28 = (GXColor){DEMO_SELECT(0xD2, 0xFF), DEMO_SELECT(0x32, 0xFF), DEMO_SELECT(0x5A, 0xFF), 0};
    i_this->mRedRopeMat.update(60, local_28, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->mRedRopeMat);
}

/* 00000FCC-000012D0       .text daBgn2_Draw__FP10bgn2_class */
static BOOL daBgn2_Draw(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    if (i_this->m2E7C > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ += i_this->m2E7C * -50000.0f;
    }
#if VERSION > VERSION_DEMO
    if (i_this->mArrowHitFlashTimer != 0) {
        s16 uVar3 = actor->tevStr.mFogColor.r + i_this->m2D60;
        if (uVar3 > 0xFF) {
            uVar3 = 0xFF;
        }
        s16 uVar4 = actor->tevStr.mFogColor.g + i_this->m2D60;
        if (uVar4 > 0xFF) {
            uVar4 = 0xFF;
        }
        s16 uVar5 = actor->tevStr.mFogColor.g + (i_this->m2D60 / 2);
        if (uVar5 > 0xFF) {
            uVar5 = 0xFF;
        }
        if (i_this->mArrowHitFlashTimer > 20) {
            cLib_addCalcAngleS2(&i_this->m2D60, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m2D64, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m2D60, 0, 1, 0xe);
            cLib_addCalc0(&i_this->m2D64, 1.0f, 2500.0f);
        }
        actor->tevStr.mFogColor.r = uVar3 & 0xFF;
        actor->tevStr.mFogColor.g = uVar4 & 0xFF;
        actor->tevStr.mFogColor.b = uVar5 & 0xFF;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m2D64;
    }
#endif
    g_env_light.setLightTevColorType(i_this->mpHeadMorf->getModel(), &actor->tevStr);
    g_env_light.setLightTevColorType(i_this->mpBodyMorf->getModel(), &actor->tevStr);
    i_this->mpHeadMorf->entryDL();
    if (l_HIO.m00C != 0) {
        i_this->m02B8.setModel(i_this->mpHeadMorf->getModel());
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02B8, 0);
    }
    i_this->mpBodyMorf->entryDL();
    if (l_HIO.m00C != 0) {
        i_this->m02D0.setModel(i_this->mpBodyMorf->getModel());
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02D0, 0);
    }
    J3DModel* pJVar7;
    if (actor->health != 0) {
        if (actor->health == 3) {
            pJVar7 = i_this->mpJyakutenModel[2];
        } else if (actor->health == 1) {
            pJVar7 = i_this->mpJyakutenModel[0];
            i_this->mJyakutenCBrkAnm->entry(pJVar7->getModelData());
        } else {
            pJVar7 = i_this->mpJyakutenModel[1];
            i_this->mJyakutenBBrkAnm->entry(pJVar7->getModelData());
        }
        g_env_light.setLightTevColorType(pJVar7, &actor->tevStr);
        mDoExt_modelUpdateDL(pJVar7);
        if (l_HIO.m00C != 0) {
            i_this->m02E4.setModel(pJVar7);
            dComIfGd_getOpaListSky()->entryImm(&i_this->m02E4, 0);
        }
    }
#ifdef __MWERKS__
    i_this->mRedRopeMat.update(60, (GXColor){0xD2, 0x32, 0x5A, 0}, &actor->tevStr);
#else
    GXColor local_28 = (GXColor){0xD2, 0x32, 0x5A, 0};
    i_this->mRedRopeMat.update(60, local_28, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->mRedRopeMat);
    return TRUE;
}

/* 000012D0-00001754       .text daBgn3_Draw__FP10bgn3_class */
static BOOL daBgn3_Draw(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    if (i_this->m10060 > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m10060 * -50000.0f;
    }
#if VERSION > VERSION_DEMO
    if (i_this->mArrowHitFlashTimer != 0) {
        s16 uVar3 = actor->tevStr.mFogColor.r + i_this->m0FD96;
        if (uVar3 > 0xFF) {
            uVar3 = 0xFF;
        }
        s16 uVar4 = actor->tevStr.mFogColor.g + i_this->m0FD96;
        if (uVar4 > 0xFF) {
            uVar4 = 0xFF;
        }
        s16 uVar5 = actor->tevStr.mFogColor.g + (i_this->m0FD96 / 2);
        if (uVar5 > 0xFF) {
            uVar5 = 0xFF;
        }
        if (i_this->mArrowHitFlashTimer > 40) {
            cLib_addCalcAngleS2(&i_this->m0FD96, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m0FD98, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m0FD96, 0, 1, 7);
            cLib_addCalc0(&i_this->m0FD98, 1.0f, 1250.0f);
        }
        actor->tevStr.mFogColor.r = uVar3 & 0xFF;
        actor->tevStr.mFogColor.g = uVar4 & 0xFF;
        actor->tevStr.mFogColor.b = uVar5 & 0xFF;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m0FD98;
    }
#endif
    J3DModel* pJVar6 = i_this->m002CC;
    g_env_light.setLightTevColorType(pJVar6, &actor->tevStr);
    mDoExt_modelUpdateDL(pJVar6);
#if VERSION == VERSION_DEMO
    i_this->m002D0.setModel(pJVar6);
    dComIfGd_getOpaListSky()->entryImm(&i_this->m002D0, 0);
#else
    if (l_HIO.m00C != 0) {
        i_this->m002D0.setModel(pJVar6);
        dComIfGd_getOpaListSky()->entryImm(&i_this->m002D0, 0);
    }
#endif
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &actor->tevStr);
    i_this->mpMorf->entryDL();
#if VERSION == VERSION_DEMO
    i_this->m002B8.setModel(i_this->mpMorf->getModel());
    dComIfGd_getOpaListSky()->entryImm(&i_this->m002B8, 0);
#else
    if (l_HIO.m00C != 0) {
        i_this->m002B8.setModel(i_this->mpMorf->getModel());
        dComIfGd_getOpaListSky()->entryImm(&i_this->m002B8, 0);
    }
#endif
    part_s3* ppVar8 = i_this->mParts;
    for (s32 i = 0; i < 9; i++, ppVar8++) {
#if VERSION > VERSION_DEMO
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &ppVar8->m00D4, &ppVar8->mPart3TevStr);
        if (i_this->m10060 > 0.0f) {
            ppVar8->mPart3TevStr.mFogColor.b = 0;
            ppVar8->mPart3TevStr.mFogColor.g = 0;
            ppVar8->mPart3TevStr.mFogColor.r = 0;
            ppVar8->mPart3TevStr.mFogStartZ = ppVar8->mPart3TevStr.mFogStartZ + i_this->m10060 * -50000.0f;
        }
        if (ppVar8->mPart3ArrowHitFlashTimer != 0) {
            s16 var_r25 = ppVar8->mPart3TevStr.mFogColor.r + ppVar8->m00C8;
            if (var_r25 > 0xFF) {
                var_r25 = 0xFF;
            }
            s16 var_r21_2 = ppVar8->mPart3TevStr.mFogColor.g + ppVar8->m00C8;
            if (var_r21_2 > 0xFF) {
                var_r21_2 = 0xFF;
            }
            s16 var_r20 = ppVar8->mPart3TevStr.mFogColor.g + (ppVar8->m00C8 / 2);
            if (var_r20 > 0xFF) {
                var_r20 = 0xFF;
            }
            if (ppVar8->mPart3ArrowHitFlashTimer > 40) {
                cLib_addCalcAngleS2(&ppVar8->m00C8, 0x118, 1, 0x1e);
                cLib_addCalc2(&ppVar8->m00CC, -50000.0f, 1.0f, 5000.0f);
            } else {
                cLib_addCalcAngleS2(&ppVar8->m00C8, 0, 1, 7);
                cLib_addCalc0(&ppVar8->m00CC, 1.0f, 1250.0f);
            }
            ppVar8->mPart3TevStr.mFogColor.r = var_r25 & 0xFF;
            ppVar8->mPart3TevStr.mFogColor.g = var_r21_2 & 0xFF;
            ppVar8->mPart3TevStr.mFogColor.b = var_r20 & 0xFF;
            ppVar8->mPart3TevStr.mFogStartZ = ppVar8->mPart3TevStr.mFogStartZ + ppVar8->m00CC;
        }
#endif
        if (i_this->mParts[i].mpPart3Model != NULL) {
            g_env_light.setLightTevColorType(i_this->mParts[i].mpPart3Model, DEMO_SELECT(&actor->tevStr, &ppVar8->mPart3TevStr));
            if (i == 8) {
                if (actor->health == 1) {
                    i_this->mJyakutenCBrkAnm->entry(i_this->mParts[i].mpPart3Model->getModelData());
                } else if (actor->health == 2) {
                    i_this->mJyakutenBBrkAnm->entry(i_this->mParts[i].mpPart3Model->getModelData());
                }
            }
            mDoExt_modelUpdateDL(i_this->mParts[i].mpPart3Model);
#if VERSION == VERSION_DEMO
            i_this->mParts[i].m0004.setModel(i_this->mParts[i].mpPart3Model);
            dComIfGd_getOpaListSky()->entryImm(&i_this->mParts[i].m0004, 0);
#else
            if (l_HIO.m00C != 0) {
                i_this->mParts[i].m0004.setModel(i_this->mParts[i].mpPart3Model);
                dComIfGd_getOpaListSky()->entryImm(&i_this->mParts[i].m0004, 0);
            }
#endif
        }
    }
#ifdef __MWERKS__
    i_this->mRedRopeMat.update(60, (GXColor){0xD2, 0x32, 0x5A, 0}, &actor->tevStr);
#else
    GXColor local_48 = (GXColor){0xD2, 0x32, 0x5A, 0};
    i_this->mRedRopeMat.update(60, local_48, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->mRedRopeMat);
    return TRUE;
}

/* 00001754-00001898       .text room_disp__FP9bgn_class */
static void room_disp(bgn_class* i_this) {
    f32 x;

    g_env_light.settingTevStruct(TEV_TYPE_BG1, &w_pos, &i_this->mRoomTevStr);
    MtxTrans(0.0f, REG0_F(12), 0.0f, false);
    x = REG0_F(13) * 0.01f + 1.0f;
    MtxScale(x, x, x, true);
    i_this->mpRoomReflectionModel->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mpRoomReflectionModel, &i_this->mRoomTevStr);
    if (i_this->mCC38 == 0) {
        mDoExt_modelUpdateDL(i_this->mpRoomReflectionModel);
        i_this->mCC38++;
    } else {
        i_this->mpRoomReflectionModel->calcMaterial();
        i_this->mpRoomReflectionModel->diff();
    }
    i_this->mCB60.setModel(i_this->mpRoomReflectionModel);
    dComIfGd_getOpaListSky()->entryImm(&i_this->mCB60, 0);
}

/* 00001898-0000192C       .text ten_a_d_sub__FPvPv */
static void* ten_a_d_sub(void* param_1, void*) {
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_Obj_Vteng)) {
        if ((actor->model != NULL) && (bgn != NULL)) {
            bgn->mCC24.setModel(actor->model);
            dComIfGd_getOpaListSky()->entryImm(&bgn->mCC24, 0);
        }
        return param_1;
    } else {
        return NULL;
    }
}

/* 0000192C-00001998       .text ki_a_d_sub__FPvPv */
static void* ki_a_d_sub(void* param_1, void*) {
    ki_class* keese = (ki_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        if (keese->actor.model != NULL) {
            keese->m2B8.setModel(keese->actor.model);
            dComIfGd_getOpaListSky()->entryImm(&keese->m2B8, 0);
        }
    }
    return NULL;
}

/* 00001998-000019F4       .text obj_disp__FP9bgn_class */
static void obj_disp(bgn_class* i_this) {
    if (REG0_S(8) == 0) {
        fpcM_Search(ten_a_d_sub, i_this);
    }
    fpcM_Search(ki_a_d_sub, i_this);
}

/* 000019F4-00001A40       .text bgn2_s_sub__FPvPv */
static void* bgn2_s_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN2)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00001A40-00001A8C       .text bgn3_s_sub__FPvPv */
static void* bgn3_s_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN3)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00001A8C-00001C40       .text daBgn_Draw__FP9bgn_class */
static BOOL daBgn_Draw(bgn_class* i_this) {
#if VERSION > VERSION_DEMO
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->mCA60 > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->mCA60);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->mCA60 == 1) {
        i_this->mCA60 = 0;
        mDoGph_gInf_c::offBlure();
    }
#endif
    water0_disp(i_this);
    if (l_HIO.m00D != 0) {
        room_disp(i_this);
    }
    if (l_HIO.m00C != 0) {
        obj_disp(i_this);
    }
    if (i_this->m02B4 != 0xFF) {
#if VERSION > VERSION_DEMO
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
        bgn2 = (bgn2_class*)fpcM_Search(bgn2_s_sub, i_this);
        bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
#endif
        if (i_this->m02B5 == 0) {
            daBgn_DrawS(i_this);
        } else if (i_this->m02B5 == 1) {
#if VERSION == VERSION_DEMO
            daBgn2_Draw(bgn2);
#else
            if (bgn2 != NULL) {
                daBgn2_Draw(bgn2);
            }
#endif
        } else if (i_this->m02B5 == 2) {
#if VERSION == VERSION_DEMO
            daBgn3_Draw(bgn3);
#else
            if (bgn3 != NULL) {
                daBgn3_Draw(bgn3);
            }
#endif
        }
#if VERSION > VERSION_DEMO
        if (i_this->mC720 != 0) {
#ifdef __MWERKS__
            i_this->mDefeatCSRopeMat.update(60, (GXColor){0xFF, 0xFF, 0xFF, 0}, &actor->tevStr);
#else
            GXColor local_18 = (GXColor){0xFF, 0xFF, 0xFF, 0};
            i_this->mDefeatCSRopeMat.update(60, local_18, &actor->tevStr);
#endif
            dComIfGd_set3DlineMat(&i_this->mDefeatCSRopeMat);
        }
#endif
    }
    water1_disp(i_this);
    return TRUE;
}

/* 00001C40-00001C8C       .text ki_del_sub__FPvPv */
static void* ki_del_sub(void* param_1, void*) {
    ki_class* keese = (ki_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        fopAcM_delete(&keese->actor);
    }
    return NULL;
}

#if VERSION > VERSION_DEMO
/* 00001C8C-00001CD8       .text ks_del_sub__FPvPv */
static void* ks_del_sub(void* param_1, void*) {
    ks_class* morth = (ks_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KS)) {
        fopAcM_delete(&morth->actor);
    }
    return NULL;
}
#endif

/* 00001CD8-00001D30       .text ki_c_sub__FPvPv */
static void* ki_c_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        ki_all_count++;
    }
    return NULL;
}

/* 00001D30-00001D74       .text ki_check__FP9bgn_class */
static s32 ki_check(bgn_class* i_this) {
    ki_all_count = 0;
    fpcM_Search(ki_c_sub, i_this);
    return ki_all_count;
}

/* 00001D74-00001FA0       .text move_se_set__FP9bgn_class */
static void move_se_set(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u32 uVar2;
    cXyz local_28;

    local_28 = actor->current.pos - actor->old.pos;
    local_28.y = 0.0f;
    uVar2 = local_28.abs() * 3.5f;
    if (uVar2 > 100) {
        uVar2 = 100;
    }
    fopAcM_seStart(actor, JA_SE_CM_BGN_MECHA_ROTATE, uVar2);
    local_28 = i_this->mC728 - i_this->mC734;
    local_28.z = 0.0f;
    local_28.x = 0.0f;
    uVar2 = local_28.abs();
    if (uVar2 > 100) {
        uVar2 = 100;
    }
    fopAcM_seStart(actor, JA_SE_CM_BGN_MECHA_ROPE, uVar2);
}

/* 00001FA0-00002330       .text gr_check__FP9bgn_classP4cXyz */
static s32 gr_check(bgn_class* i_this, cXyz* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk local_a0;

    cXyz local_ac = *param_2;
    local_ac.y += 200.0f;
    cXyz local_b8 = *param_2;
    local_b8.y -= 1000.0f;
    local_a0.Set(&local_ac, &local_b8, actor);
    if (dComIfG_Bgsp()->LineCross(&local_a0)) {
        *param_2 = local_a0.mLin.GetEnd();
        param_2->y = REG0_F(8) + -2.0f;
        if (dComIfG_Bgsp()->GetAttributeCode(local_a0) == dBgS_Attr_WATER_e) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00002768-0000290C       .text s_b_sub__FPvPv */
static void* s_b_sub(void* param_1, void* param_2) {
    bgn_class* bgn = (bgn_class*)param_2;
    daBomb_c* bomb = (daBomb_c*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BOMB) && bomb->get_explode_instant()) {
        cXyz local_18 = bomb->current.pos;
        if (!gr_check(bgn, &local_18)) {
            dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHSPLASH00, &local_18);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHSPLASH01, &local_18);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHHAMON00, &local_18);
            dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONSPLASH01, &local_18, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON01, &local_18, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
    }
    return NULL;
}

/* 0000290C-00002938       .text bomb_splash_check__FP9bgn_class */
static void bomb_splash_check(bgn_class* i_this) {
    fpcM_Search(s_b_sub, i_this);
}

/* 00002938-00002CD4       .text attack_eff_set__FP9bgn_class4cXyzi */
static void attack_eff_set(bgn_class* i_this, cXyz param_2, int param_3) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (!gr_check(i_this, &param_2)) {
        dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHSPLASH00, &param_2);
        dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHSPLASH01, &param_2);
        dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHHAMON00, &param_2);
        dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONSPLASH01, &param_2, 0xFF, g_whiteColor, g_whiteColor, 0);
        dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON01, &param_2, 0xFF, g_whiteColor, g_whiteColor, 0);
        if (param_3 <= 1) {
            fopAcM_seStart(player, JA_SE_CM_BGN_D_HIT_PUNCH_W, 0);
        } else {
            fopAcM_seStart(player, JA_SE_CM_BGN_D_FALL_WATER, 0);
        }
    } else {
        if (param_3 <= 1) {
            fopAcM_seStart(player, JA_SE_CM_BGN_D_HIT_PUNCH, 0);
        } else {
            fopAcM_seStart(player, JA_SE_CM_BGN_D_FALL, 0);
        }
        if (param_3 > 1) {
            param_3 = 1;
        }
        i_this->mPunchSmokeCb[param_3].remove();
        emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_ST_KGTT1PUNCHSMOKE00, &param_2, NULL, NULL, 0xa0, &i_this->mPunchSmokeCb[param_3], fopAcM_GetRoomNo(actor)
        );
        if (emitter != NULL) {
            emitter->setGlobalPrmColor(bg_tevstr.mColorC0.r, bg_tevstr.mColorC0.g, bg_tevstr.mColorC0.b);
            emitter->setGlobalEnvColor(bg_tevstr.mColorK0.r, bg_tevstr.mColorK0.g, bg_tevstr.mColorK0.b);
        }
        dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT1PUNCHHAHEN00, &param_2);
    }
}

/* 00002CD4-00003144       .text part_control_0__FP9bgn_classiP6part_sP6move_sf */
static void part_control_0(bgn_class* i_this, int param_2, part_s* param_3, move_s* param_4, f32 param_5) {
    cXyz local_d0;
    cXyz cStack_dc;
    cXyz local_e8;

    local_e8.setall(0.0f);
    if ((param_3 == &i_this->mHeadParts[0]) && (i_this->mAAA8[0].m2D0 != 0 || (i_this->mAAA8[1].m2D0 != 0))) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_d0.x = 0.0f;
        local_d0.y = 0.0f;
        local_d0.z = REG0_F(6) + 200.0f;
        MtxPosition(&local_d0, &local_e8);
    } else if ((param_3 == &i_this->mLeftArmParts[0]) && (i_this->mAAA8[3].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_d0.x = REG0_F(8) + 20.0f;
        local_d0.y = 0.0f;
        local_d0.z = 0.0f;
        MtxPosition(&local_d0, &local_e8);
    } else if ((param_3 == &i_this->mRightArmParts[0]) && (i_this->mAAA8[4].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_d0.x = -(REG0_F(8) + 20.0f);
        local_d0.y = 0.0f;
        local_d0.z = 0.0f;
        MtxPosition(&local_d0, &local_e8);
    }
    f32 temp_f26;
    f32 temp_f30;
    f32 temp_f25;
    f32 dVar11 = ((i_this->mC7BC - 50.0f) + REG0_F(6));
    f32 dVar10;
    param_3++;
    if (param_4->m2D0 == 0) {
        dVar10 = l_HIO.m16C;
    } else if (i_this->mCSMode != 0) {
        dVar10 = -40.0f;
    } else {
        dVar10 = l_HIO.m170;
    }
    for (s32 i = 1; i < param_2 + 1; i++, param_3++) {
        f32 y2 = param_3->m0D4.y + dVar10;
        f32 fVar3 = dVar11 * param_3[-1].m0F4;
        if (y2 <= fVar3) {
            y2 = fVar3;
        }
        temp_f30 = local_e8.x + (param_3->m0D4.x - param_3[-1].m0D4.x);
        temp_f26 = y2 - param_3[-1].m0D4.y;
        temp_f25 = local_e8.z + (param_3->m0D4.z - param_3[-1].m0D4.z);
        int iVar5 = param_4->m2F4 * cM_ssin(param_4->m2FA + i * (REG0_S(3) + 8000));
        int iVar2 = param_4->m2F4 * cM_scos(param_4->m2FC + i * (REG0_S(4) + 9000));
        param_3[-1].m0E0.x = (s16)(iVar5 - cM_atan2s(temp_f26, temp_f25));
        param_3[-1].m0E0.y = (s16)(iVar2 + cM_atan2s(temp_f30, std::sqrtf(SQUARE(temp_f26) + SQUARE(temp_f25))));
        cMtx_XrotS(*calc_mtx, param_3[-1].m0E0.x);
        cMtx_YrotM(*calc_mtx, param_3[-1].m0E0.y);
        local_d0.set(0.0f, 0.0f, i_this->mCC80 * (param_5 * param_3[-1].m0F4));
        MtxPosition(&local_d0, &cStack_dc);
        param_3->m0D4 = param_3[-1].m0D4 + cStack_dc;
    }
}

/* 00003144-00003624       .text part_control_0Z__FP9bgn_classiP6part_sP6move_sf */
static void part_control_0Z(bgn_class* i_this, int param_2, part_s* param_3, move_s* param_4, f32 param_5) {
    /* Nonmatching - retail-only regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    f32 x;
    f32 y;
    f32 z;
    f32 dVar10;
    f32 dVar9;
    cXyz local_f8;
    cXyz cStack_104;
    cXyz local_11c;
    cXyz local_128;
    cXyz local_134;

    cMtx_YrotS(*calc_mtx, i_this->mC314.y);
    if (param_3 == &i_this->mLeftArmParts[0]) {
        local_f8.x = REG0_F(8) + 20.0f;
        local_f8.y = 0.0f;
        local_f8.z = 0.0f;
        MtxPosition(&local_f8, &local_128);
    } else if (param_3 == &i_this->mRightArmParts[0]) {
        local_f8.x = -(REG0_F(8) + 20.0f);
        local_f8.y = 0.0f;
        local_f8.z = 0.0f;
        MtxPosition(&local_f8, &local_128);
    } else if (param_3 == &i_this->mTailParts[0]) {
        local_f8.x = 0.0f;
        local_f8.y = 0.0f;
        local_f8.z = REG0_F(6) + -5.0f;
        MtxPosition(&local_f8, &local_128);
    }
    dVar10 = i_this->mC7BC;
    dVar9 = l_HIO.m170;
    param_3++;
    for (s32 i = 1; i < param_2 + 1; i++, param_3++) {
        f32 dVar11 = param_3->m0D4.y + dVar9;
        if (dVar11 <= dVar10) {
            dVar11 = dVar10;
            if ((i == param_2) && ((i_this->mC746 & 7) == 0)) {
                local_134 = param_3->m0D4;
                if (!(gr_check(i_this, &local_134))) {
                    dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON03, &local_134, 0xff, g_whiteColor, g_whiteColor, 0);
                    if (i_this->m0304 == 0) {
                        i_this->m0304 = cM_rndF(20.0f) + 20.0f;
                        i_this->m0308 = local_134;
                        mDoAud_seStart(JA_SE_CM_BGN_BODY_RIPPLE, &i_this->m0308, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    }
                }
            }
        }
        f32 f1 = (param_2 - i);
        local_11c.x = local_128.x * f1;
        local_11c.z = local_128.z * f1;
        x = local_11c.x + (param_3->m0D4.x - param_3[-1].m0D4.x);
        y = (dVar11 - param_3[-1].m0D4.y);
        z = local_11c.z + (param_3->m0D4.z - param_3[-1].m0D4.z);
        int iVar2 = param_4->m2F4 * cM_ssin(param_4->m2FA + i * (REG0_S(3) + 8000));
        int iVar4 = param_4->m2F4 * cM_scos(param_4->m2FC + i * (REG0_S(4) + 9000));
        param_3[-1].m0E0.y = (s16)(iVar4 + cM_atan2s(x, z));
        param_3[-1].m0E0.x = (s16)(iVar2 - cM_atan2s(y, std::sqrtf(SQUARE(x) + SQUARE(z))));
        cMtx_YrotS(*calc_mtx, param_3[-1].m0E0.y);
        cMtx_XrotM(*calc_mtx, param_3[-1].m0E0.x);
        local_f8.set(0.0f, 0.0f, i_this->mCC80 * (param_5 * param_3[-1].m0F4));
        MtxPosition(&local_f8, &cStack_104);
        param_3->m0D4 = param_3[-1].m0D4 + cStack_104;
    }
}

/* 00003624-0000385C       .text part_control_2__FP9bgn_classiP6part_sf */
static void part_control_2(bgn_class*, int param_2, part_s* param_3, f32 param_4) {
    /* Nonmatching */
    s32 i;
    cXyz local_84;
    cXyz cStack_90;
    cXyz local_9c;

    local_9c = param_3->m0D4;
    part_s* ppVar6 = &param_3[param_2 - 1];
    for (s32 i = param_2 - 1; i >= 0; i--, ppVar6--) {
        f32 x = ppVar6[0].m0D4.x - ppVar6[1].m0D4.x;
        f32 y = ppVar6[0].m0D4.y - ppVar6[1].m0D4.y;
        f32 z = ppVar6[0].m0D4.z - ppVar6[1].m0D4.z;
        int iVar5;
        s16 iVar4;
        iVar4 = -cM_atan2s(y, z);
        iVar5 = cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z)));
        cMtx_XrotS(*calc_mtx, iVar4);
        cMtx_YrotM(*calc_mtx, iVar5);
        local_84.set(0.0f, 0.0f, param_4 * ppVar6[0].m0F4);
        MtxPosition(&local_84, &cStack_90);
        ppVar6[0].m0D4 = ppVar6[1].m0D4 + cStack_90;
    }
    ppVar6++;
    local_84 = ppVar6[0].m0D4 - local_9c;
    for (i = 0; i < param_2; i++, ppVar6++) {
        ppVar6[0].m0D4 -= local_84;
    }
}

/* 0000385C-00003FD0       .text part_mtx_set__FP9bgn_classiP6part_sii */
static void part_mtx_set(bgn_class* i_this, int param_2, part_s* param_3, int param_4, int param_5) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar1;
    f32 fVar4;
    f32 fVar5;
    s32 uVar7;
    s16 sVar8;
    f32 dVar10;
    cXyz local_8c;
    cXyz local_98;

    local_8c.z = 0.0f;
    local_8c.y = 0.0f;
    local_8c.x = 0.0f;
    for (s32 i = 0; i < param_2; i++, param_3++) {
        if (i_this->m0302 == param_3->m0D2) {
            param_3->mPartArrowHitFlashTimer = 50;
#if VERSION > VERSION_DEMO
            param_3->mPartArrowHitEffectTimer = 100;
#endif
        }
        if (param_3->mPartArrowHitFlashTimer != 0) {
            param_3->mPartArrowHitFlashTimer--;
        }
        cLib_addCalcAngleS2(&param_3->m0E0.z, i_this->mC314.y, 4, 0x2000);
        if (param_3->m0D4.y <= i_this->mC7BC) {
            param_3->m0D4.y = i_this->mC7BC;
        }
        MtxTrans(param_3->m0D4.x, param_3->m0D4.y, param_3->m0D4.z, false);
        if ((param_4 == 7) && (i_this->mAAA8[7].m2D0 != 0)) {
            cMtx_YrotM(*calc_mtx, param_3->m0E0.y);
            cMtx_XrotM(*calc_mtx, param_3->m0E0.x);
            cMtx_ZrotM(*calc_mtx, -param_3->m0E0.z);
        } else {
            cMtx_XrotM(*calc_mtx, param_3->m0E0.x);
            cMtx_YrotM(*calc_mtx, param_3->m0E0.y);
            if (param_3->m0E0.x < 0) {
                cMtx_ZrotM(*calc_mtx, param_3->m0E0.z);
            } else {
                cMtx_ZrotM(*calc_mtx, -param_3->m0E0.z);
            }
        }
        fVar4 = param_3->m0F4 * l_HIO.m0F4;
        dVar10 = fVar4;
        if ((i != param_2 + -1) && (param_4 == 3 || (param_4 == 4))) {
            fVar5 = (REG0_F(0) + 0.005f) * (i_this->mC324[param_4 + -3] - l_HIO.m124) + 1.0f;
        } else {
            fVar5 = 1.0f;
        }
        MtxScale(fVar4, fVar4, (dVar10 * fVar5), true);
        if (param_4 == 0) {
            uVar7 = (s16)(i_this->mAAA8[0].m300 + i_this->mAAA8[1].m300);
            fVar4 = (s32)(uVar7) * (REG0_F(14) + 170.0f);
            sVar8 = fVar4 * cM_ssin(uVar7 * 0x2100);
            iVar1 = (int)(fVar4 * cM_ssin(sVar8 * 0x2300));
            cMtx_YrotM(*calc_mtx, i_this->mC744 + l_HIO.m03C + iVar1);
            cMtx_ZrotM(*calc_mtx, l_HIO.m040 + sVar8);
        }
        MtxTrans(0.0f, 0.0f, l_HIO.m168, true);
        if (param_4 == 0) {
            MtxTrans(0.0f, l_HIO.m034, l_HIO.m038, true);
            cMtx_XrotM(*calc_mtx, l_HIO.m03E);
        }
        if ((param_4 == 7) && (i == param_2 + -1)) {
            if (actor->health == 3) {
                param_3->mpPartModel = i_this->mpJyakutenAModel;
            } else if (actor->health == 2) {
                param_3->mpPartModel = i_this->mpJyakutenBModel;
            } else if (actor->health == 1) {
                param_3->mpPartModel = i_this->mpJyakutenCModel;
            } else {
                param_3->mpPartModel = NULL;
            }
        }
        if (param_3->mpPartModel != NULL) {
            param_3->mpPartModel->setBaseTRMtx(*calc_mtx);
        }
        if (param_4 == 0) {
            if (((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) || ((int)i_this->mpMorf->getFrame() != 0x18)) {
                i_this->mpMorf->play(NULL, 0, 0);
            }
            i_this->mpMorf->calc();
        }
        MtxPosition(&zero, &local_98);
        param_3->m224 = local_98;
        if ((param_4 == 7) && (i == param_2 + -1)) {
            i_this->mCoreSph.SetR(REG0_F(4) + 150.0f);
            i_this->mCoreSph.SetC(local_98);
            i_this->mCA54 = local_98;
            dComIfG_Ccsp()->Set(&i_this->mCoreSph);
        }
        param_3->mPartSph.SetR(dVar10 * (120.0f + REG0_F(0)));
        param_3->mPartSph.SetC(local_98);
        dComIfG_Ccsp()->Set(&param_3->mPartSph);
        if (i == param_5) {
            if (param_4 == 0) {
                local_8c.set(90.0f, 180.0f, -40.0f);
                MtxPosition(&local_8c, &i_this->mC33C[0]);
                local_8c.x *= -1.0f;
                MtxPosition(&local_8c, &i_this->mC33C[1]);
            } else {
                local_8c.y = 0.0f;
                local_8c.x = 0.0f;
                local_8c.z = l_HIO.m168;
                MtxPosition(&local_8c, &i_this->mC33C[param_4]);
            }
            local_8c.z = 0.0f;
            local_8c.x = 0.0f;
        }
#if VERSION > VERSION_DEMO
        if (param_3->mPartArrowHitEffectTimer != 0) {
            param_3->mPartArrowHitEffectTimer--;
            fVar4 = (REG8_F(0) + 0.04f) * (param_3->m0F4 * param_3->mPartArrowHitEffectTimer);
            if (param_3->mpPartArrowHitEmitter1 == NULL) {
                param_3->mpPartArrowHitEmitter1 = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER00, &param_3->m0D4);
            } else {
                param_3->mpPartArrowHitEmitter1->setGlobalTranslation(param_3->m0D4.x, param_3->m0D4.y, param_3->m0D4.z);
                JGeometry::TVec3<f32> scale(fVar4, fVar4, fVar4);
                param_3->mpPartArrowHitEmitter1->setGlobalScale(scale);
            }
            if (param_3->mpPartArrowHitEmitter2 == NULL) {
                local_8c.setall(fVar4);
                param_3->mpPartArrowHitEmitter2 = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER01, &param_3->m0D4);
            } else {
                param_3->mpPartArrowHitEmitter2->setGlobalTranslation(param_3->m0D4.x, param_3->m0D4.y, param_3->m0D4.z);
                JGeometry::TVec3<f32> scale(fVar4, fVar4, fVar4);
                param_3->mpPartArrowHitEmitter2->setGlobalScale(scale);
            }
        } else {
            if (param_3->mpPartArrowHitEmitter1 != NULL) {
                param_3->mpPartArrowHitEmitter1->becomeInvalidEmitter();
                param_3->mpPartArrowHitEmitter1 = NULL;
            }
            if (param_3->mpPartArrowHitEmitter2 != NULL) {
                param_3->mpPartArrowHitEmitter2->becomeInvalidEmitter();
                param_3->mpPartArrowHitEmitter2 = NULL;
            }
        }
#endif
    }
}

/* 00003FD0-000044DC       .text damage_check__FP9bgn_class */
static void damage_check(bgn_class* i_this) {
    /* Nonmatching - retail-only regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    char cVar5;
    f32 dVar8;
    CcAtInfo local_48;

    if (i_this->mC7B6 == 0) {
        local_48.pParticlePos = NULL;
        if (i_this->mCoreSph.ChkTgHit()) {
            local_48.mpObj = i_this->mCoreSph.GetTgHitObj();
            i_this->m0302 = 1;
            i_this->mC7B6 = 100;
            i_this->mC748 = 5;
            i_this->mC74A = 0;
            i_this->mC779 = 0;
            i_this->mC778 = 0;
            if (actor->health != 0) {
                actor->health--;
#if VERSION == VERSION_DEMO
                fopAcM_seStart(actor, JA_SE_LK_ARROW_HIT, 0x35);
#else
                mDoAud_seStart(JA_SE_LK_ARROW_HIT, NULL, 0x35, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                dVar8 = (REG0_F(5) + 2.0f);
                if (actor->health == 0) {
                    mDoAud_bgmStop(30);
                    i_this->mC748 = 6;
                    i_this->mC74A = 0;
                    emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTBREAKWEAKPOINT00, &i_this->mCA54);
                    if (emitter != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        emitter->setGlobalScale(scale);
                    }
                    emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTBREAKWEAKPOINT01, &i_this->mCA54);
                    if (emitter != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        emitter->setGlobalScale(scale);
                    }
#if VERSION == VERSION_DEMO
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_2, 0);
                    fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);
                    fopAcM_seStart(actor, JA_SE_CM_BGN_M_BRK_ORB, 0);
#else
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_2, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_LK_LAST_HIT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_CM_BGN_M_BRK_ORB, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                } else {
                    emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTHITWEAKPOINT00, &i_this->mCA54);
                    if (emitter != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        emitter->setGlobalScale(scale);
                    }
#if VERSION == VERSION_DEMO
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_1, 0);
#else
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                }
            }
        }
        cVar5 = 0;
        if (i_this->mC7FC.ChkTgHit()) {
            local_48.mpObj = i_this->mC7FC.GetTgHitObj();
            cVar5 = 1;
        }
        if (i_this->mHeadParts[0].mPartSph.ChkTgHit()) {
            local_48.mpObj = i_this->mHeadParts[0].mPartSph.GetTgHitObj();
            cVar5 = 2;
        }
        if (i_this->mPelvisParts[0].mPartSph.ChkTgHit()) {
            local_48.mpObj = i_this->mPelvisParts[0].mPartSph.GetTgHitObj();
            cVar5 = 3;
        }
        for (s32 i = 0; i < 20; i++) {
            if (i_this->mLeftArmParts[i].mPartSph.ChkTgHit()) {
                local_48.mpObj = i_this->mLeftArmParts[i].mPartSph.GetTgHitObj();
                cVar5 = 4;
            }
            if (i_this->mRightArmParts[i].mPartSph.ChkTgHit()) {
                local_48.mpObj = i_this->mRightArmParts[i].mPartSph.GetTgHitObj();
                cVar5 = 5;
            }
        }
        for (s32 i = 0; i < 3; i++) {
            if (i_this->mLeftLegParts[i].mPartSph.ChkTgHit()) {
                local_48.mpObj = i_this->mLeftLegParts[i].mPartSph.GetTgHitObj();
                cVar5 = 6;
            }
            if (i_this->mRightLegParts[i].mPartSph.ChkTgHit()) {
                local_48.mpObj = i_this->mRightLegParts[i].mPartSph.GetTgHitObj();
                cVar5 = 7;
            }
        }
        for (s32 i = 0; i < 20; i++) {
            if (i_this->mTailParts[i].mPartSph.ChkTgHit()) {
                local_48.mpObj = i_this->mTailParts[i].mPartSph.GetTgHitObj();
                cVar5 = 8;
            }
        }
        if ((cVar5 != 0) && (i_this->mC7B8 == 0)) {
            i_this->mC7B8 = 10;
            def_se_set(actor, local_48.mpObj, 0x44);
        }
    }
}

/* 00004518-000047D0       .text size_set__FP9bgn_class */
static void size_set(bgn_class* i_this) {
    i_this->mHeadParts[0].m0F4 = l_HIO.m0F8;
    i_this->mPelvisParts[0].m0F4 = l_HIO.m100;
    i_this->mPelvisParts[1].m0F4 = l_HIO.m100;
    f32 fVar2 = (1.0f / (BGN_HAND_MAX - 2)) * (l_HIO.m104 - l_HIO.m108);
    i_this->mLeftArmParts[0].m0F4 = l_HIO.m104 - fVar2;
    i_this->mRightArmParts[0].m0F4 = l_HIO.m104 - fVar2;
    for (s32 i = 1; i < BGN_HAND_MAX; i++) {
        i_this->mLeftArmParts[i].m0F4 = l_HIO.m104 - fVar2 * (i - 1);
        i_this->mRightArmParts[i].m0F4 = l_HIO.m104 - fVar2 * (i - 1);
    }
    i_this->mLeftArmParts[BGN_HAND_MAX].m0F4 = l_HIO.m108;
    i_this->mRightArmParts[BGN_HAND_MAX].m0F4 = l_HIO.m108;
    fVar2 = 0.5f * (l_HIO.m104 - l_HIO.m108);
    fVar2 += l_HIO.m108;
    for (s32 i = 0; i < BGN_HAND_MAX; i++) {
        i_this->mLeftArmParts[i].m0F4 += 2.0f * (i_this->mC32C[0] * (fVar2 - i_this->mLeftArmParts[i].m0F4));
        i_this->mRightArmParts[i].m0F4 += 2.0f * (i_this->mC32C[1] * (fVar2 - i_this->mRightArmParts[i].m0F4));
    }
    fVar2 = 0.5f * (l_HIO.m10C - l_HIO.m110);
    for (s32 i = 0; i < 3; i++) {
        i_this->mLeftLegParts[i].m0F4 = l_HIO.m10C - fVar2 * i;
        i_this->mRightLegParts[i].m0F4 = l_HIO.m10C - fVar2 * i;
    }
    i_this->mLeftLegParts[3].m0F4 = l_HIO.m110;
    i_this->mRightLegParts[3].m0F4 = l_HIO.m110;
    fVar2 = (1.0f / (BGN_TAIL_MAX - 1)) * (l_HIO.m114 - l_HIO.m118);
    for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
        i_this->mTailParts[i].m0F4 = l_HIO.m114 - (fVar2 * i);
    }
    i_this->mRightLegParts[BGN_TAIL_MAX + 3].m0F4 = l_HIO.m114 * 0.7f;
    i_this->mTailParts[BGN_TAIL_MAX].m0F4 = l_HIO.m114 * 0.7f;
}

/* 000047D0-000056DC       .text shape_calc__FP9bgn_class */
static void shape_calc(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar3;
    s16 sVar8;
    s16 sVar5;
    f32 dVar11;
    f32 dVar10;
    f32 dVar9;
    f32 dVar13;
    f32 dVar12;
    cXyz local_8c;
    cXyz cStack_98;
    cXyz local_b0;

    local_b0 = i_this->mC308;
    local_b0.y = i_this->mC308.y + (l_HIO.m0A8);
    fVar3 = i_this->mC7BC + 100.0f + REG0_F(0);
    if (local_b0.y <= fVar3) {
        local_b0.y = fVar3;
    }
    if (i_this->m0302 == 0xd) {
        i_this->mArrowHitFlashTimer = 50;
#if VERSION > VERSION_DEMO
        i_this->mArrowHitEffectTimer = 100;
#endif
    }
    MtxTrans(local_b0.x, local_b0.y, local_b0.z, false);
    sVar8 = 0;
    sVar5 = 0;
    if (i_this->mC770 != 0) {
        i_this->mC770--;
        fVar3 = (i_this->mC770) * (REG0_F(14) + 300.0f);
        sVar8 = (fVar3 * cM_ssin(i_this->mC746 * 0x1c00));
        sVar5 = (fVar3 * cM_scos(i_this->mC746 * 0x1900));
    }
    cMtx_YrotM(*calc_mtx, i_this->mC314.y);
    cMtx_XrotM(*calc_mtx, i_this->mC314.x + sVar8);
    cMtx_ZrotM(*calc_mtx, i_this->mC314.z + sVar5);
    fVar3 = l_HIO.m0FC * l_HIO.m0F4;
    dVar12 = fVar3;
    MtxScale(fVar3, fVar3, fVar3, true);
    MtxPush();
    cMtx_XrotM(*calc_mtx, l_HIO.m004);
    if (i_this->mCC84 > 0.0f) {
        sVar5 = i_this->mC746 * (REG0_S(4) + 0x900);
        cMtx_ZrotM(*calc_mtx, sVar5);
        MtxScale(i_this->mCC84 + 1.0f, 1.0f - i_this->mCC84, i_this->mCC84 + 1.0f, true);
        cMtx_ZrotM(*calc_mtx, -sVar5);
    }
    i_this->mpChestModel->setBaseTRMtx(*calc_mtx);
    i_this->mC7FC.SetR(dVar12 * (REG0_F(1) + 120.0f));
    i_this->mC7FC.SetC(i_this->mC308);
    dComIfG_Ccsp()->Set(&i_this->mC7FC);
#if VERSION > VERSION_DEMO
    if (i_this->mArrowHitEffectTimer != 0) {
        i_this->mArrowHitEffectTimer--;
        fVar3 = (REG8_F(1) + 0.03f) * (dVar12 * (i_this->mArrowHitEffectTimer));
        if (i_this->mpArrowHitEmitter1 == NULL) {
            i_this->mpArrowHitEmitter1 = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER00, &i_this->mC308);
        } else {
            i_this->mpArrowHitEmitter1->setGlobalTranslation(i_this->mC308.x, i_this->mC308.y, i_this->mC308.z);
            JGeometry::TVec3<f32> scale(fVar3, fVar3, fVar3);
            i_this->mpArrowHitEmitter1->setGlobalScale(scale);
        }
        if (i_this->mpArrowHitEmitter2 == NULL) {
            local_8c.setall(dVar12);
            i_this->mpArrowHitEmitter2 = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER01, &i_this->mC308);
        } else {
            i_this->mpArrowHitEmitter2->setGlobalTranslation(i_this->mC308.x, i_this->mC308.y, i_this->mC308.z);
            JGeometry::TVec3<f32> scale(fVar3, fVar3, fVar3);
            i_this->mpArrowHitEmitter2->setGlobalScale(scale);
        }
    } else {
        if (i_this->mpArrowHitEmitter1 != NULL) {
            i_this->mpArrowHitEmitter1->becomeInvalidEmitter();
            i_this->mpArrowHitEmitter1 = NULL;
        }
        if (i_this->mpArrowHitEmitter2 != NULL) {
            i_this->mpArrowHitEmitter2->becomeInvalidEmitter();
            i_this->mpArrowHitEmitter2 = NULL;
        }
    }
#endif
    MtxPull();
    dVar12 = (l_HIO.m11C * l_HIO.m0F4);
    dVar11 = (l_HIO.m120 * l_HIO.m0F4);
    dVar10 = (i_this->mC324[0] * l_HIO.m0F4);
    dVar9 = (i_this->mC324[1] * l_HIO.m0F4);
    dVar13 = (l_HIO.m128 * l_HIO.m0F4);
    MtxPush();
    local_8c = l_HIO.m12C;
    MtxPosition(&local_8c, &i_this->mHeadParts[0].m0D4);
    part_control_0(i_this, 1, &i_this->mHeadParts[0], &i_this->mAAA8[0], dVar12);
    if ((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_8c = l_HIO.m054;
        local_8c += i_this->mAAA8[0].m2D4;
        MtxPosition(&local_8c, &i_this->mHeadParts[1].m0D4);
        i_this->mHeadParts[1].m0D4 += i_this->mC308;
        part_control_2(i_this, 1, &i_this->mHeadParts[0], dVar12);
    }
    part_mtx_set(i_this, 1, &i_this->mHeadParts[0], 0, 0);
    actor->eyePos = i_this->mHeadParts[0].m0D4;
    actor->attention_info.position = actor->eyePos;
    actor->attention_info.position.y += 50.0f;
    MtxPull();
    MtxPush();
    local_8c.x = l_HIO.m144.x;
    local_8c.y = l_HIO.m144.y + 20.0f;
    local_8c.z = l_HIO.m144.z;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->mPelvisParts[0].m0D4);
    part_control_0(i_this, 1, &i_this->mPelvisParts[0], &i_this->mAAA8[2], dVar12);
    if (i_this->mAAA8[2].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_8c = l_HIO.m060;
        local_8c += i_this->mAAA8[2].m2D4;
        MtxPosition(&local_8c, &i_this->mPelvisParts[1].m0D4);
        i_this->mPelvisParts[1].m0D4 += i_this->mC308;
        part_control_2(i_this, 1, &i_this->mPelvisParts[0], dVar12);
    }
    part_mtx_set(i_this, 1, &i_this->mPelvisParts[0], 2, 0);
    MtxPull();
    MtxPush();
    local_8c = l_HIO.m138;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->mLeftArmParts[0].m0D4);
    if (i_this->mAAA8[3].m2D0 == 0) {
        part_control_0(i_this, BGN_HAND_MAX, &i_this->mLeftArmParts[0], &i_this->mAAA8[3], dVar10);
        if (i_this->mC778 != 0) {
            i_this->mLeftArmParts[BGN_HAND_MAX].m0D4 = i_this->mC77C;
        } else {
            cMtx_YrotS(*calc_mtx, i_this->mC314.y);
            local_8c = l_HIO.m06C;
            local_8c += i_this->mAAA8[3].m2D4;
            MtxPosition(&local_8c, &i_this->mLeftArmParts[BGN_HAND_MAX].m0D4);
            i_this->mLeftArmParts[BGN_HAND_MAX].m0D4 += i_this->mC308;
        }
        part_control_2(i_this, BGN_HAND_MAX, &i_this->mLeftArmParts[0], dVar10);
    } else {
        part_control_0(i_this, BGN_HAND_MAX, &i_this->mLeftArmParts[0], &i_this->mAAA8[3], dVar10);
    }
    part_mtx_set(i_this, BGN_HAND_MAX, &i_this->mLeftArmParts[0], 3, BGN_HAND_MAX + -1);
    MtxPull();
    local_8c.x = -l_HIO.m138.x;
    local_8c.y = l_HIO.m138.y;
    local_8c.z = l_HIO.m138.z;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->mRightArmParts[0].m0D4);
    if (i_this->mAAA8[4].m2D0 == 0) {
        part_control_0(i_this, BGN_HAND_MAX, &i_this->mRightArmParts[0], &i_this->mAAA8[4], dVar9);
        if (i_this->mC779 != 0) {
            i_this->mRightArmParts[BGN_HAND_MAX].m0D4 = i_this->mC788;
        } else {
            cMtx_YrotS(*calc_mtx, i_this->mC314.y);
            local_8c = l_HIO.m078;
            local_8c += i_this->mAAA8[4].m2D4;
            MtxPosition(&local_8c, &i_this->mRightArmParts[BGN_HAND_MAX].m0D4);
            i_this->mRightArmParts[BGN_HAND_MAX].m0D4 += i_this->mC308;
        }
        part_control_2(i_this, BGN_HAND_MAX, &i_this->mRightArmParts[0], dVar9);
    } else {
        part_control_0(i_this, BGN_HAND_MAX, &i_this->mRightArmParts[0], &i_this->mAAA8[4], dVar9);
    }
    part_mtx_set(i_this, BGN_HAND_MAX, &i_this->mRightArmParts[0], 4, BGN_HAND_MAX + -1);
    cMtx_XrotS(*calc_mtx, i_this->mPelvisParts[0].m0E0.x);
    cMtx_YrotM(*calc_mtx, i_this->mPelvisParts[0].m0E0.y);
    cMtx_ZrotM(*calc_mtx, -i_this->mPelvisParts[0].m0E0.z);
    fVar3 = l_HIO.m100 * l_HIO.m0F4;
    MtxScale(fVar3, fVar3, fVar3, true);
    MtxPush();
    local_8c = l_HIO.m150;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->mLeftLegParts[0].m0D4 = i_this->mPelvisParts[0].m0D4 + cStack_98;
    part_control_0(i_this, 3, &i_this->mLeftLegParts[0], &i_this->mAAA8[5], dVar11);
    if (i_this->mAAA8[5].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_8c = l_HIO.m084;
        local_8c += i_this->mAAA8[5].m2D4;
        MtxPosition(&local_8c, &i_this->mLeftLegParts[3].m0D4);
        i_this->mLeftLegParts[3].m0D4 += i_this->mC308;
        part_control_2(i_this, 3, &i_this->mLeftLegParts[0], dVar11);
    }
    part_mtx_set(i_this, 3, &i_this->mLeftLegParts[0], 5, 2);
    MtxPull();
    MtxPush();
    local_8c.x = -l_HIO.m150.x;
    local_8c.y = l_HIO.m150.y;
    local_8c.z = l_HIO.m150.z;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->mRightLegParts[0].m0D4 = i_this->mPelvisParts[0].m0D4 + cStack_98;
    part_control_0(i_this, 3, &i_this->mRightLegParts[0], &i_this->mAAA8[6], dVar11);
    if (i_this->mAAA8[6].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_8c = l_HIO.m090;
        local_8c += i_this->mAAA8[6].m2D4;
        MtxPosition(&local_8c, &i_this->mRightLegParts[3].m0D4);
        i_this->mRightLegParts[3].m0D4 += i_this->mC308;
        part_control_2(i_this, 3, &i_this->mRightLegParts[0], dVar11);
    }
    part_mtx_set(i_this, 3, &i_this->mRightLegParts[0], 6, 2);
    MtxPull();
    local_8c = l_HIO.m15C;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->mTailParts[0].m0D4 = i_this->mPelvisParts[0].m0D4 + cStack_98;
    if (i_this->mAAA8[7].m2D0 == 0) {
        part_control_0(i_this, BGN_TAIL_MAX, &i_this->mTailParts[0], &i_this->mAAA8[7], dVar13);
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_8c = l_HIO.m09C;
        local_8c += i_this->mAAA8[7].m2D4;
        MtxPosition(&local_8c, &i_this->mTailParts[BGN_TAIL_MAX].m0D4);
        i_this->mTailParts[BGN_TAIL_MAX].m0D4 += i_this->mC308;
        if (i_this->mTailParts[BGN_TAIL_MAX].m0D4.y <= i_this->mC7BC) {
            i_this->mTailParts[BGN_TAIL_MAX].m0D4.y = i_this->mC7BC;
        }
        part_control_2(i_this, BGN_TAIL_MAX, &i_this->mTailParts[0], dVar13);
    } else {
        part_control_0Z(i_this, BGN_TAIL_MAX, &i_this->mTailParts[0], &i_this->mAAA8[7], dVar13);
    }
    part_mtx_set(i_this, BGN_TAIL_MAX, &i_this->mTailParts[0], 7, BGN_TAIL_MAX + -1);
}

/* 000056DC-000058F4       .text dance_A__FP9bgn_class */
static void dance_A(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 uVar2;
    s16 target;

    for (s32 i = 0; i < 8; i++) {
        move_s* tmp = &i_this->mAAA8[i];
        switch (i_this->mC74E) {
        case 0:
            i_this->mC74E++;
            i_this->mC752 = 0;
            // fallthrough
        case 1:
            tmp->m2E0 = dance_pause_1[i];
            if (i_this->mC7AC[3] == 0) {
                i_this->mC74E++;
                i_this->mC7AC[3] = l_HIO.m0DA;
            }
            break;
        case 2:
            tmp->m2E0 = dance_pause_2[i];
            if (i_this->mC7AC[3] == 0) {
                i_this->mC74E = 1;
                i_this->mC7AC[3] = l_HIO.m0DA;
            }
            break;
        }
    }
    uVar2 = i_this->mC750;
    i_this->mC750 = uVar2 + i_this->mC752;
    if (((0 < uVar2) && (i_this->mC750 <= i_this->mC752)) || (0x8000 < (u16)uVar2 && ((u16)i_this->mC750 <= (u16)(i_this->mC752 + 0x8000)))) {
        mDoAud_seStart(JA_SE_CM_BGN_D_KAZEKIRI, &i_this->mCA54, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
    if (actor->health == 3) {
        target = l_HIO.m0DC;
    } else if (actor->health == 2) {
        target = l_HIO.m0DE;
    } else {
        target = l_HIO.m0E0;
    }
    cLib_addCalcAngleS2(&i_this->mC752, target, 1, 0x10);
}

/* 000058F4-00005ACC       .text dance_B__FP9bgn_class */
static void dance_B(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar4;

    fopAcM_seStart(actor, JA_SE_CM_BGN_D_DANCE, 0);
    for (s32 i = 0; i < 8; i++) {
        move_s* tmp = &i_this->mAAA8[i];
        switch (i_this->mC74E) {
        case 0:
            tmp->m2E0 = dance_pause_3[i];
            if (i_this->mC7AC[3] == 0) {
                i_this->mC74E++;
                if (actor->health == 3) {
                    i_this->mC7AC[3] = l_HIO.m0E8;
                } else if (actor->health == 2) {
                    i_this->mC7AC[3] = l_HIO.m0EA;
                } else {
                    i_this->mC7AC[3] = l_HIO.m0EC;
                }
            }
            break;
        case 1:
            tmp->m2E0 = dance_pause_4[i];
            if (i_this->mC7AC[3] == 0) {
                i_this->mC74E = 0;
                if (actor->health == 3) {
                    i_this->mC7AC[3] = l_HIO.m0E8;
                } else if (actor->health == 2) {
                    i_this->mC7AC[3] = l_HIO.m0EA;
                } else {
                    i_this->mC7AC[3] = l_HIO.m0EC;
                }
            }
            break;
        }
    }
    if (i_this->mC74E == 1) {
        sVar4 = 0x1555;
    } else {
        sVar4 = -0x1555;
    }
    cLib_addCalcAngleS2(&i_this->mC750, sVar4, 8, l_HIO.m0EE);
}

/* 00005ACC-00005B2C       .text ki_set__FP9bgn_class */
static void ki_set(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (actor->health == 3) {
        i_this->mKeeseSpawnNum = l_HIO.mKeeseNum3HP;
    } else if (actor->health == 2) {
        i_this->mKeeseSpawnNum = l_HIO.mKeeseNum2HP;
    } else {
        i_this->mKeeseSpawnNum = l_HIO.mKeeseNum1HP;
    }
}

/* 00005B2C-0000616C       .text dance_0__FP9bgn_class */
static void dance_0(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 uVar2;

    if (i_this->mC7AC[1] == 0) {
        i_this->mC7AC[1] = cM_rndF(150.0f) + 50.0f;
        i_this->mC758.x = cM_rndFX(1500.0f);
        i_this->mC758.z = cM_rndFX(1500.0f);
        i_this->mC76C = 0.0f;
    }
    cLib_addCalc2(&actor->current.pos.x, i_this->mC758.x, 0.05f, i_this->mC76C);
    cLib_addCalc2(&actor->current.pos.z, i_this->mC758.z, 0.05f, i_this->mC76C);
    cLib_addCalc2(&i_this->mC76C, REG0_F(19) + 20.0f, 1.0f, 0.5f);
    cLib_addCalc2(&i_this->mC728.y, (REG0_F(9) + 50.0f) * cM_ssin(i_this->mC746 * (REG0_S(9) + 500)), 0.5f, REG0_F(8) + 20.0f);
    if ((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 10, 0x400);
    }
    switch (i_this->mC74A) {
    case 0:
        if (i_this->mC754 == 0) {
            i_this->mC74C = 0;
            i_this->mC7AC[0] = l_HIO.m0D8;
            ki_set(i_this);
        } else {
            i_this->mC74C = 1;
            if (actor->health == 3) {
                i_this->mC7AC[0] = l_HIO.m0E2;
            } else if (actor->health == 2) {
                i_this->mC7AC[0] = l_HIO.m0E4;
            } else {
                i_this->mC7AC[0] = l_HIO.m0E6;
            }
        }
        i_this->mC74E = 0;
        i_this->mC74A++;
        goto block_51;
    case 1:
        if (((i_this->mC7AC[0] == 0) && (!ki_check(i_this))) && (l_HIO.m028 != 0)) {
            if (((i_this->mC754 == 1) || (i_this->mC754 == 2)) || (i_this->mC754 == 3)) {
                if (((i_this->mAAA8[0].m2D0 != 0) && (i_this->mAAA8[1].m2D0 != 0)) && (i_this->mC7AC[2] == 0)) {
                    i_this->mC748 = 4;
                    i_this->mC74A = 0;
                    i_this->mCA98 = 0.0f;
                    return;
                }
                i_this->mC748 = 1;
                i_this->mC7AC[0] = REG0_S(0) + 0x32;
                uVar2 = i_this->mAAA8[3].m2D0;
                if ((uVar2 == 0) && (i_this->mAAA8[4].m2D0 == 0)) {
                    i_this->mC74A = 5;
                    i_this->mC7AC[0] = REG0_S(6) + 0x40;
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_D_ATTACK, 0);
                } else if (uVar2 == 0) {
                    i_this->mC74A = 3;
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_D_ATTACK, 0);
                } else if (i_this->mAAA8[4].m2D0 == 0) {
                    i_this->mC74A = 1;
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_D_ATTACK, 0);
                } else if (i_this->mAAA8[7].m2D0 == 0) {
                    i_this->mC748 = 3;
                    i_this->mC74A = 0;
                } else {
                    i_this->mC748 = 2;
                    i_this->mC74A = 0;
                }
            } else if ((i_this->mC754 == 0) || (i_this->mC754 == 5)) {
                i_this->mC74A = 0;
            }
            i_this->mC754++;
            if (i_this->mC754 > 5) {
                i_this->mC754 = 0;
            }
            // fallthrough
        }
    default:
    block_51:
        switch (i_this->mC74C) {
        case 0:
            dance_A(i_this);
            break;
        case 1:
            dance_B(i_this);
            break;
        }
    }
    move_s* pmVar8 = i_this->mAAA8;
    for (s32 i = 0; i < 8; i++, pmVar8++) {
        if (pmVar8->m2D0 == 0) {
            cXyz local_34;
            local_34.x = pmVar8->m2E0.x - pmVar8->m2D4.x;
            local_34.y = pmVar8->m2E0.y - pmVar8->m2D4.y;
            local_34.z = pmVar8->m2E0.z - pmVar8->m2D4.z;
            f32 fVar9 = local_34.abs();
            f32 temp_f0_4 = REG0_F(0) + 100.0f;
            if (fVar9 > temp_f0_4) {
                f32 f4 = (fVar9 - temp_f0_4);
                if ((s16)(int)(REG0_F(2) + (50.0f + (f4 * (REG0_F(1) + 0.06f)))) > pmVar8->m2F8) {
                    pmVar8->m2F8 = (s16)(int)(REG0_F(2) + (50.0f + (f4 * (REG0_F(1) + 0.06f))));
                }
            }
        }
    }
}

/* 0000616C-00007108       .text punch_LR__FP9bgn_class */
static void punch_LR(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    s8 bVar3;
    s16 sVar7;
    s32 uVar11;
    cXyz local_6c;
    cXyz local_84;
    cXyz local_90;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bVar2 = false;
    cLib_addCalc0(&i_this->mC728.y, 0.5f, 20.0f);
    bVar3 = false;
    uVar11 = 0;
    local_90 = player->current.pos;
    if ((i_this->mAAA8[0].m2D0 != 0) && (i_this->mAAA8[1].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        local_6c.x = cM_rndFX(1000.0f);
        local_6c.y = 0.0f;
        local_6c.z = cM_rndF(1000.0f) + 1000.0f;
        MtxPosition(&local_6c, &local_90);
        local_90 += actor->current.pos;
        local_90.y = 0.0f;
    }
    switch (i_this->mC74A) {
    case 1:
        bVar3 = true;
        uVar11 = 2;
        i_this->mC338 = 130.0f;
        if (i_this->mC7AC[0] == 0x14) {
            i_this->mC788 = i_this->mRightArmParts[BGN_HAND_MAX].m0D4;
            local_84 = local_90 - i_this->mC788;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, std::sqrtf(SQUARE(local_84.x) + SQUARE(local_84.z))));
            local_6c.x = 0.0f;
            local_6c.y = 0.0f;
            local_6c.z = REG0_F(7) + 200.0f;
            MtxPosition(&local_6c, &i_this->mC7A0);
        }
        if (i_this->mC7AC[0] != 0) {
            break;
        }
        i_this->mC779 = 1;
        i_this->mC74A++;
        i_this->mC7AC[0] = REG0_S(1) + 0x32;
        fopAcM_seStart(actor, JA_SE_CM_BGN_D_PUNCH_FIRE, 0);
        // fallthrough
    case 2:
        uVar11 = 2;
        i_this->mC338 = 200.0f;
        i_this->mC334 = 200.0f;
        i_this->mRightArmParts[BGN_HAND_MAX - 1].mPartSph.OnAtSetBit();
        i_this->mC788 += i_this->mC7A0;
        i_this->mAAA8[4].m2E8 = 100.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mC779 = 0;
            i_this->mAAA8[4].m2F4 = REG0_F(15) + 5000.0f;
            bVar2 = true;
            i_this->mAAA8[4].m2E0.x = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.x;
            i_this->mAAA8[4].m2E0.y = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.y;
            i_this->mAAA8[4].m2E0.z = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.z;
            attack_eff_set(i_this, i_this->mRightArmParts[BGN_HAND_MAX - 1].m0D4, 1);
        }
        break;
    case 3:
        bVar3 = true;
        uVar11 = 1;
        i_this->mC338 = 200.0f;
        i_this->mC334 = 200.0f;
        if (i_this->mC7AC[0] == 0x14) {
            i_this->mC77C = i_this->mLeftArmParts[BGN_HAND_MAX - 1].m0D4;
            local_84 = local_90 - i_this->mC77C;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, std::sqrtf(SQUARE(local_84.x) + SQUARE(local_84.z))));
            local_6c.x = 0.0f;
            local_6c.y = 0.0f;
            local_6c.z = REG0_F(7) + 200.0f;
            MtxPosition(&local_6c, &i_this->mC794);
        }
        if (i_this->mC7AC[0] != 0) {
            break;
        }
        i_this->mC74A++;
        i_this->mC7AC[0] = REG0_S(1) + 0x32;
        i_this->mC778 = 1;
        fopAcM_seStart(actor, JA_SE_CM_BGN_D_PUNCH_FIRE, 0);
        // fallthrough
    case 4:
        uVar11 = 1;
        i_this->mLeftArmParts[BGN_HAND_MAX - 1].mPartSph.OnAtSetBit();
        i_this->mC77C += i_this->mC794;
        i_this->mC338 = 200.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mAAA8[3].m2F4 = REG0_F(15) + 5000.0f;
            i_this->mC778 = 0;
            bVar2 = true;
            i_this->mAAA8[3].m2E0.x = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.x;
            i_this->mAAA8[3].m2E0.y = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.y;
            i_this->mAAA8[3].m2E0.z = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.z;
            attack_eff_set(i_this, i_this->mLeftArmParts[BGN_HAND_MAX - 1].m0D4, 0);
        }
        break;
    case 5:
        bVar3 = true;
        uVar11 = 3;
        i_this->mC338 = 50.0f;
        if (i_this->mC7AC[0] == 0x14) {
            i_this->mC77C = i_this->mLeftArmParts[BGN_HAND_MAX - 1].m0D4;
            i_this->mC788 = i_this->mRightArmParts[BGN_HAND_MAX - 1].m0D4;
            local_84 = local_90 - i_this->mC77C;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, std::sqrtf(SQUARE(local_84.x) + SQUARE(local_84.z))));
            local_6c.x = 0.0f;
            local_6c.y = 0.0f;
            local_6c.z = REG0_F(7) + 200.0f;
            MtxPosition(&local_6c, &i_this->mC794);
            local_84 = local_90 - i_this->mC788;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, std::sqrtf(SQUARE(local_84.x) + SQUARE(local_84.z))));
            local_6c.x = 0.0f;
            local_6c.y = 0.0f;
            local_6c.z = REG0_F(7) + 200.0f;
            MtxPosition(&local_6c, &i_this->mC7A0);
        }
        if (i_this->mC7AC[0] != 0) {
            break;
        }
        i_this->mC778 = 1;
        i_this->mC779 = 1;
        i_this->mC74A++;
        i_this->mC7AC[0] = REG0_S(1) + 0x32;
        fopAcM_seStart(actor, JA_SE_CM_BGN_D_PUNCH_FIRE, 0);
        // fallthrough
    case 6:
        uVar11 = 3;
        i_this->mRightArmParts[BGN_HAND_MAX - 1].mPartSph.OnAtSetBit();
        i_this->mLeftArmParts[BGN_HAND_MAX - 1].mPartSph.OnAtSetBit();
        i_this->mC77C += i_this->mC794;
        i_this->mC788 += i_this->mC7A0;
        i_this->mC338 = 200.0f;
        i_this->mC334 = 200.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mAAA8[3].m2F4 = REG0_F(15) + 5000.0f;
            i_this->mAAA8[4].m2F4 = REG0_F(15) + 5000.0f;
            i_this->mC778 = 0;
            i_this->mC779 = 0;
            i_this->mAAA8[3].m2E0.x = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.x;
            i_this->mAAA8[3].m2E0.y = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.y;
            i_this->mAAA8[3].m2E0.z = i_this->mPelvisParts[BGN_HAND_MAX + 1].m0D4.z;
            i_this->mAAA8[4].m2E0.x = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.x;
            i_this->mAAA8[4].m2E0.y = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.y;
            i_this->mAAA8[4].m2E0.z = i_this->mLeftArmParts[BGN_HAND_MAX + 0x14].m0D4.z;
            attack_eff_set(i_this, i_this->mRightArmParts[BGN_HAND_MAX - 1].m0D4, 1);
            attack_eff_set(i_this, i_this->mLeftArmParts[BGN_HAND_MAX - 1].m0D4, 0);
            bVar2 = true;
        }
        break;
    }
    if (bVar2) {
        i_this->mC748 = 0;
        i_this->mC74A = 0;
    }
    if (uVar11 != 0) {
        if (uVar11 <= 2) {
            cLib_addCalc2(&i_this->mC32C[uVar11 - 1], REG0_F(14) + 1.0f, 0.2f, 0.05f);
        } else {
            for (s32 i = 0; i < 2; i++) {
                cLib_addCalc2(&i_this->mC32C[i], (1.0f + REG0_F(14)), 0.2f, 0.05f);
            }
        }
    }
    if ((bVar3) && (i_this->mAAA8[0].m2D0 == 0 || (i_this->mAAA8[1].m2D0 == 0))) {
        sVar7 = fopAcM_searchPlayerAngleY(actor);
        cLib_addCalcAngleS2(&actor->shape_angle.y, sVar7, 10, 0x400);
    }
    for (s32 i = 0; i < 8; i++) {
        move_s* tmp = &i_this->mAAA8[i];
        switch (i_this->mC74A) {
        case 1:
            tmp->m2E0 = punch_r1_d[i];
            break;
        case 2:
            tmp->m2E0 = punch_r2_d[i];
            break;
        case 3:
            tmp->m2E0 = punch_l1_d[i];
            break;
        case 4:
            tmp->m2E0 = punch_l2_d[i];
            break;
        case 5:
            if ((i_this->mC7AC[0] & 0x10) != 0) {
                tmp->m2E0 = punch_lr1_d[i];
            } else {
                tmp->m2E0 = punch_lr12_d[i];
            }
            break;
        case 6:
            tmp->m2E0 = punch_lr2_d[i];
            break;
        }
    }
}

/* 00007108-000071C0       .text start__FP9bgn_class */
static void start(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 target;

    target = fopAcM_searchPlayerAngleY(actor);
    cLib_addCalcAngleS2(&actor->shape_angle.y, target, 10, 0x400);
    for (s32 i = 0; i < 8; i++) {
        i_this->mAAA8[i].m2E0 = start_pause[i];
    }
    if (i_this->mC7AC[0] == 0) {
        i_this->mC74C = 0;
        i_this->mC754 = 1;
        i_this->mC748 = 0;
    }
}

/* 000071C0-000076F4       .text body_attack__FP9bgn_class */
static void body_attack(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    s16 sVar6;
    f32 fVar10;
    cXyz local_50;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bVar2 = false;
    local_50 = i_this->mC758 - actor->current.pos;
    local_50.y = 0.0f;
    fVar10 = local_50.abs();
    switch (i_this->mC74A) {
    case 0:
        i_this->mC76C = 0.0f;
        i_this->mC758 = player->current.pos;
        i_this->mC758.y = 0.0f;
        if ((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) {
            sVar6 = fopAcM_searchPlayerAngleY(actor);
            i_this->mC764 = sVar6;
        }
        i_this->mC74A = 1;
        break;
    case 1:
        bVar2 = true;
        if (fVar10 < 200.0f) {
            i_this->mC74A = 2;
            i_this->mC7AC[0] = 0x1e;
        }
        break;
    case 2:
        bVar2 = true;
        i_this->mC758.y = 500.0f;
        if (i_this->mC7AC[0] == 0) {
            i_this->mC74A = 3;
            actor->speed.y = 0.0f;
            i_this->mC770 = REG0_S(0) + 0x14;
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x1e;
                i_this->mAAA8[i].m2F4 = REG0_F(15) + 5000.0f;
            }
        }
        break;
    case 3:
        i_this->mC728.y += actor->speed.y;
        actor->speed.y -= (REG0_F(4) + 10.0f);
        i_this->mC7FC.OnAtSetBit();
        i_this->mPelvisParts[0].mPartSph.OnAtSetBit();
        if (i_this->mC728.y <= -1000.0f) {
            i_this->mC728.y = -1000.0f;
            actor->speed.y *= -(REG0_F(19) + 0.4f);
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x28;
                i_this->mAAA8[i].m2F4 = REG0_F(15) + 5000.0f;
            }
            i_this->mC770 = REG0_S(0) + 0x14;
            i_this->mC7AC[0] = 0x46;
            i_this->mC74A = 4;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 9, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            attack_eff_set(i_this, i_this->mC308, 2);
        }
        break;
    case 4:
        i_this->mC728.y += actor->speed.y;
        actor->speed.y -= (REG0_F(4) + 10.0f);
        if (i_this->mC728.y <= -1000.0f) {
            i_this->mC728.y = -1000.0f;
            actor->speed.y = 0.0f;
        }
        if (i_this->mC7AC[0] > 10) {
            cLib_addCalc2(&i_this->mC774, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
            for (s32 i = 0; i < 8; i++) {
                cLib_addCalc2(&i_this->mAAA8[i].m2EC, (250.0f + REG0_F(9)), 1.0f, (50.0f + REG0_F(10)));
            }
        }
        if (i_this->mC7AC[0] == 0) {
            i_this->mC748 = 0;
            i_this->mC74A = 0;
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x32;
                i_this->mAAA8[i].m2F4 = REG0_F(15) + 5000.0f;
            }
        }
        break;
    }
    if (bVar2) {
        cLib_addCalc2(&actor->current.pos.x, i_this->mC758.x, 0.1f, i_this->mC76C);
        cLib_addCalc2(&actor->current.pos.z, i_this->mC758.z, 0.1f, i_this->mC76C);
        cLib_addCalc2(&i_this->mC76C, REG0_F(19) + 30.0f, 1.0f, 0.5f);
        cLib_addCalc2(&i_this->mC728.y, i_this->mC758.y, 0.1f, 50.0f);
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->mC764, 10, 0x400);
    }
}

/* 000076F4-000078D0       .text tail_attack__FP9bgn_class */
static void tail_attack(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mC74A) {
    case 0:
        i_this->mC7AC[0] = 100;
        i_this->mC74A = 1;
        i_this->mC764 = 0;
        i_this->mC76C = 0.0f;
        break;
    case 1:
        actor->shape_angle.y += i_this->mC764;
        if (i_this->mC7AC[0] > 0x28) {
            cLib_addCalcAngleS2(&i_this->mC764, 0x800, 1, 0x80);
            cLib_addCalc2(&actor->current.pos.x, player->current.pos.x, 0.1f, i_this->mC76C);
            cLib_addCalc2(&actor->current.pos.z, player->current.pos.z, 0.1f, i_this->mC76C);
            cLib_addCalc2(&i_this->mC76C, REG0_F(19) + 15.0f, 1.0f, 0.2f);
            for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
                i_this->mTailParts[i].mPartSph.OnAtSetBit();
            }
            i_this->mAAA8[7].m2E0.z = (int)(REG0_F(3) + -600.0f);
            cLib_addCalc2(&i_this->mC728.y, -550.0f, 0.1f, 20.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->mC764, 0, 1, 0x20);
            cLib_addCalc2(&i_this->mC728.y, 0.0f, 0.1f, 5.0f);
            i_this->mAAA8[7].m2E0.z = 0;
        }
        if (i_this->mC7AC[0] == 0) {
            i_this->mC748 = 0;
            i_this->mC74A = 0;
        }
        break;
    }
}

/* 000078D0-00007B38       .text damage__FP9bgn_class */
static void damage(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mpMorf->play(NULL, 0, 0);
    i_this->mpMorf->play(NULL, 0, 0);
    switch (i_this->mC74A) {
    case 0:
        i_this->mC7AC[0] = 0;
        i_this->mC74A = 1;
        actor->speed.y = REG0_F(8) + 100.0f;
        i_this->mC770 = REG0_S(0) + 0x32;
        for (s32 i = 0; i < 8; i++) {
            i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x46;
            i_this->mAAA8[i].m2F4 = REG0_F(15) + 8000.0f;
        }
        break;
    case 1:
        if (i_this->mC728.y <= 0.0f) {
            actor->speed.y = REG0_F(9) + 30.0f;
            i_this->mC7AC[0] = REG0_S(5) + 0x28;
            i_this->mC74A = 2;
        }
        break;
    case 2:
        if (i_this->mC7AC[0] == 0) {
            if (i_this->mAAA8[7].m2D0 != 0) {
                i_this->mC748 = 4;
            } else {
                i_this->mC748 = 0;
            }
            i_this->mC74A = 0;
        }
        break;
    }
    i_this->mC728.y += actor->speed.y;
    actor->speed.y -= (REG0_F(4) + 10.0f);
    if (i_this->mC728.y <= 0.0f) {
        i_this->mC728.y = 0.0f;
        actor->speed.y = 0.0f;
    }
    if (i_this->mC728.y > 100.0f) {
        cLib_addCalc2(&i_this->mC774, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
        for (s32 i = 0; i < 8; i++) {
            cLib_addCalc2(&i_this->mAAA8[i].m2EC, (250.0f + REG0_F(9)), 1.0f, (50.0f + REG0_F(10)));
        }
    }
}

/* 00007B38-00007CF0       .text head_recover__FP9bgn_class */
static void head_recover(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mC74A) {
    case 0:
        cLib_addCalc2(&i_this->mC728.y, 4000.0f, 0.2f, (REG0_F(10) + 100.0f) * i_this->mCA98);
        cLib_addCalc2(&i_this->mCA98, 1.0f, 1.0f, 0.02f);
        actor->shape_angle.y = actor->shape_angle.y + 0x200;
        if (i_this->mC728.y >= 3990.0f) {
            i_this->mC74A = 1;
            i_this->mC7AC[0] = REG0_S(5) + 0x28;
            i_this->mAAA8[1].m2D0 = 0;
            i_this->mAAA8[0].m2D0 = 0;
            i_this->mAAA8[1].m308 = 2;
            i_this->mAAA8[0].m308 = 2;
            i_this->mAAA8[4].m2D0 = 0;
            i_this->mAAA8[3].m2D0 = 0;
            i_this->mAAA8[4].m308 = 2;
            i_this->mAAA8[3].m308 = 2;
            i_this->mAAA8[7].m2D0 = 0;
            i_this->mAAA8[7].m308 = DEMO_SELECT(1, 2);
            fopAcM_seStart(player, JA_SE_CM_BGN_D_ROPE_RESET, 0);
        }
        break;
    case 1:
        if (i_this->mC7AC[0] == 0) {
            actor->shape_angle.y = actor->shape_angle.y + -0x400;
            cLib_addCalc2(&i_this->mC728.y, 0.0f, 0.05f, REG0_F(10) + 200.0f);
            if (i_this->mC728.y < 5.0f) {
                i_this->mC748 = 0;
                i_this->mC74A = 0;
            }
        }
        break;
    }
}

/* 00007CF0-000084B4       .text hensin__FP9bgn_class */
static void hensin(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;

    cLib_addCalc2(&actor->current.pos.x, 0.0f, 0.05f, 50.0f);
    cLib_addCalc2(&actor->current.pos.z, 0.0f, 0.05f, 50.0f);
    switch (i_this->mC74A) {
    case 0:
        i_this->mC74A = 1;
        for (s32 i = 0; i < 8; i++) {
            i_this->mAAA8[i].m2D0 = 1;
        }
        i_this->mCSMode = 1;
        // fallthrough
    case 1:
    case 2:
    case 3:
    case 4:
        i_this->mC728.y = i_this->mC728.y + actor->speed.y;
        actor->speed.y = actor->speed.y - (REG0_F(4) + 10.0f);
        if (i_this->mC728.y <= REG0_F(2) + -1000.0f) {
            i_this->mC728.y = REG0_F(2) + -1000.0f;
            i_this->mC770 = REG0_S(0) + 0x14;
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x3c;
                i_this->mAAA8[i].m2F4 = REG0_F(15) + 6000.0f;
            }
            if (i_this->mC74A == 1) {
                actor->speed.y = REG0_F(3) + 220.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(18) + 20.0f;
                attack_eff_set(i_this, i_this->mHeadParts[0].m0D4, 0);
            } else if (i_this->mC74A == 2) {
                actor->speed.y = REG0_F(3) + 190.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(18) + 15.0f;
                attack_eff_set(i_this, i_this->mHeadParts[0].m0D4, 1);
            } else if (i_this->mC74A == 3) {
                actor->speed.y = REG0_F(3) + 130.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(18) + 10.0f;
            } else {
                actor->speed.y = 0.0f;
                mDoAud_bgmStart(JA_BGM_BGN_TARABA_IN);
            }
            i_this->mC74A++;
        }
        break;
    case 5:
        if (i_this->mKSubCount >= (s16)(REG0_S(3) + 150)) {
            cLib_addCalc2(&i_this->mCC88, 1.0f, 1.0f, REG0_F(15) + 0.005f);
        }
        cLib_addCalc2(&i_this->mC774, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
        if (i_this->mKSubCount == 280) {
            i_this->mC74A = 10;
            i_this->mC7AC[0] = REG0_S(6) + 300;
            i_this->mC7AC[1] = REG0_S(7) + 0x96;
            i_this->mCC8C = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT2CHESTPOTA00, &actor->current.pos);
        }
        break;
    case 10:
        cLib_addCalc2(&i_this->mCC88, 1.0f, 1.0f, REG0_F(15) + 0.005f);
        if (i_this->mCC8C != NULL) {
            if (i_this->mC7AC[1] != 0) {
                i_this->mCC8C->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
            } else {
                i_this->mCC8C->becomeInvalidEmitter();
                i_this->mCC8C = NULL;
            }
        }
        cLib_addCalc2(&i_this->mC728.y, REG0_F(9) + 1000.0f, 0.05f, actor->speed.y);
        cLib_addCalc2(&actor->speed.y, 50.0f, 1.0f, 0.2f);
        if (i_this->mC7AC[0] <= 0x64) {
            cLib_addCalc0(&i_this->mCC80, 1.0f, 0.02f);
            if (i_this->mC7AC[0] == 100) {
                mDoAud_seStart(JA_SE_CM_BGN_D_TO_T_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
#if VERSION == VERSION_DEMO
            if (i_this->mC7AC[0] == 1) {
                mDoGph_gInf_c::setBlureRate(REG0_S(4) + 0xB4);
                // Required to match.
                mDoGph_gInf_c::mBlureFlag = true;
                mDoMtx_copy(cMtx_getIdentity(), mDoGph_gInf_c::mBlureMtx);
            }
#endif
            if (i_this->mC7AC[0] <= 1) {
                cLib_addCalc2(&i_this->mCC84, 0.22f, 0.1f, 0.0055f);
                if (i_this->mC7AC[0] == 1) {
                    mDoAud_seStart(JA_SE_CM_BGN_D_TO_T_2, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
                if (i_this->mCC84 > 0.21f) {
#if VERSION == VERSION_DEMO
                    mDoGph_gInf_c::offBlure();
#endif
                    l_HIO.m024++;
                    bgn2->actor.current.angle = i_this->mC314;
                    bgn2->actor.shape_angle = i_this->mC314;
                    bgn2->actor.current.pos = i_this->mC308;
                    bgn2->m2E7C = 1.0f;
                    i_this->mCSMode++;
                    i_this->mKSubCount = 0;
                    local_20.setall(REG0_F(4) + 10.0f);
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUBAKUEN, &bgn2->actor.current.pos, NULL, &local_20);
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &bgn2->actor.current.pos, NULL, &local_20);
                    mDoAud_seStart(JA_SE_CM_BGN_METAM_EXPLODE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                }
#if VERSION > VERSION_DEMO
                else
                {
                    cLib_addCalcAngleS2(&i_this->mCA60, 0xb4, 1, 4);
                }
#endif
            }
        }
        break;
    }
}

/* 000084B4-00008888       .text himo_control__FP9bgn_classP6move_sP4cXyz */
static void himo_control(bgn_class* i_this, move_s* param_2, cXyz* param_3) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar9;
    f32 dVar10;
    cXyz local_ac;
    cXyz local_b8;
    cXyz local_c4;

    cXyz* pcVar5 = &param_2->m000[1];
    local_ac.x = 0.0f;
    local_ac.y = 0.0f;
    local_ac.z = (REG0_F(12) + 15.0f) * i_this->mCC80;
    s32 j, k, i;
    j = 0;
    k = 0;
    i = 1;
    param_3++;
    for (; i < 60; i++, pcVar5++, param_3++) {
        f32 x = (pcVar5[0].x - pcVar5[-1].x);
        f32 z = pcVar5[0].z - pcVar5[-1].z;
        f32 y2 = ((pcVar5[0].y - 40.0f) + REG0_F(13));
        if (y2 < 0.0f) {
            y2 = 0.0f;
            bVar9 = true;
        } else {
            bVar9 = false;
        }
        f32 y = (y2 - pcVar5[-1].y);
        dVar10 = param_2->m304;
        if (dVar10 > 0.01f) {
            j = (int)(dVar10 * cM_ssin(param_2->m2FA + i * (REG0_S(3) + 2000)));
            k = (int)(dVar10 * cM_scos(param_2->m2FC + i * (REG0_S(4) + 0x9c4)));
        }
        cMtx_XrotS(*calc_mtx, (int)j - cM_atan2s(y, z));
        cMtx_YrotM(*calc_mtx, (int)k + cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z))));
        MtxPosition(&local_ac, &local_b8);
        pcVar5[0].x = pcVar5[-1].x + local_b8.x;
        pcVar5[0].y = pcVar5[-1].y + local_b8.y;
        pcVar5[0].z = pcVar5[-1].z + local_b8.z;
        *param_3 = pcVar5[0];
        if (((bVar9) && (((int)i_this->mC746 & 7) == 0)) && (((int)i_this->mC746 >> 3 & 0xf) == (i & 0xf))) {
            local_c4 = pcVar5[0];
            if (!gr_check(i_this, &local_c4)) {
                dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON00, &local_c4, 0xff, g_whiteColor, g_whiteColor, 0);
                if (i_this->m0304 == 0) {
                    i_this->m0304 = cM_rndF(20.0f) + 20.0f;
                    i_this->m0308 = local_c4;
                    mDoAud_seStart(JA_SE_CM_BGN_STRING_RIPPLE, &i_this->m0308, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
    }
}

#if VERSION > VERSION_DEMO
/* 00008888-00008C20       .text last_himo_control__FP9bgn_class */
static void last_himo_control(bgn_class* i_this) {
    /* Nonmatching */
    cXyz* pcVar5;
    cXyz local_a8;
    cXyz local_b4;

    i_this->mC450[0].set(-15.0f, REG8_F(4) + 4441.46f, REG8_F(3) + 375.17f);
    cXyz* pcVar8 = i_this->mDefeatCSRopeMat.getPos(0);
    u8* puVar8 = i_this->mDefeatCSRopeMat.getSize(0);
    *puVar8 = 10;
    *pcVar8 = i_this->mC450[0];
    if (i_this->mC720 == 1) {
        i_this->mC720++;
        pcVar5 = &i_this->mC450[1];
        for (s32 i = 0; i < 59; i++, pcVar5++) {
            *pcVar5 = i_this->mC450[0];
        }
        i_this->mC724 = REG0_F(19) + 5000.0f;
    } else {
        cLib_addCalc0(&i_this->mC724, 1.0f, (REG0_F(18) + 50.0f));
    }
    pcVar5 = &i_this->mC450[1];
    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
    local_a8.z = REG0_F(12) + 45.0f;
    s32 i, j, k;
    k = 0;
    j = 0;
    i = 1;
    cXyz* var_r25 = &pcVar8[1];
    u8* var_r28 = &puVar8[1];
    for (; i < 60; i++, pcVar5++, var_r25++, var_r28++) {
        f32 x = (pcVar5->x - pcVar5[-1].x);
        f32 y = REG0_F(13) + ((pcVar5->y - pcVar5[-1].y) - 35.0f);
        f32 z = pcVar5->z - pcVar5[-1].z;
        if (i_this->mC724 > 0.01f) {
            k = i_this->mC724 * cM_ssin(i_this->mC746 * 2000 + i * (REG0_S(3) + 2000));
            j = i_this->mC724 * cM_scos(i_this->mC746 * 0x8fc + i * (REG0_S(4) + 0x9c4));
        }
        cMtx_XrotS(*calc_mtx, (int)k - cM_atan2s(y, z));
        cMtx_YrotM(*calc_mtx, (int)j + cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z))));
        MtxPosition(&local_a8, &local_b4);
        pcVar5->x = pcVar5[-1].x + local_b4.x;
        pcVar5->y = pcVar5[-1].y + local_b4.y;
        pcVar5->z = pcVar5[-1].z + local_b4.z;
        *var_r25 = *pcVar5;
        *var_r28 = 10;
    }
}
#endif

/* 00008C20-000092B8       .text action_s__FP9bgn_classP6move_si */
static void action_s(bgn_class* i_this, move_s* param_2, int param_3) {
    /* Nonmatching */
    f32 target;
    f32 fVar3;
    cXyz* pcVar4;
    u8* pcVar7;
    cXyz local_64;
    cXyz local_70;
    cXyz cStack_7c;

    if (param_2->m2F8 != 0) {
        param_2->m2F8--;
    }
    target = 0.0f;
    if ((l_HIO.m025 == 0) && (i_this->mC728.y > REG0_F(12) + -900.0f)) {
        target = (REG0_F(13) + ((param_2->m2F8) * (REG0_F(2) + 20.0f) + 300.0f));
    }
    cLib_addCalc2(&param_2->m2F4, target, 0.5f, REG0_F(8) + 200.0f);
    param_2->m2FA += (s16)((param_3 * 3) + (REG0_S(5) + 0xa28));
    param_2->m2FC += (s16)((param_3 * 3) + (REG0_S(6) + 0x8fc));
    if (param_2->m2FE != 0) {
        param_2->m2FE--;
    }
    if (l_HIO.m025 != 0) {
        param_2->m2D0 = 0;
        switch (param_3) {
        case 0:
            param_2->m2E0 = l_HIO.m0AA;
            break;
        case 2:
            param_2->m2E0 = l_HIO.m0B0;
            break;
        case 3:
            param_2->m2E0 = l_HIO.m0B6;
            break;
        case 4:
            param_2->m2E0 = l_HIO.m0BC;
            break;
        case 5:
            param_2->m2E0 = l_HIO.m0C2;
            break;
        case 6:
            param_2->m2E0 = l_HIO.m0C8;
            break;
        case 7:
            param_2->m2E0 = l_HIO.m0CE;
        }
    }
    if (param_2->m2D0 == 0) {
        cLib_addCalc2(&param_2->m2D4.x, param_2->m2E0.x, 0.5f, i_this->mC334);
        cLib_addCalc2(&param_2->m2D4.y, param_2->m2E0.y, 0.5f, i_this->mC334);
        cLib_addCalc2(&param_2->m2D4.z, param_2->m2E0.z, 0.5f, i_this->mC334);
    }
    pcVar4 = i_this->mBlueRopeMat.getPos(param_3);
    pcVar7 = i_this->mBlueRopeMat.getSize(param_3);
    local_64 = i_this->mC33C[param_3];
    if (param_2->m2D0 != 0) {
        param_2->m000[0] = local_64;
        *pcVar4 = local_64;
        himo_control(i_this, param_2, pcVar4);
        cLib_addCalc0(&param_2->m304, 1.0f, (REG0_F(5) + 100.0f));
    } else {
        local_70.y = 0.0f;
        cLib_addCalc0(&param_2->m2EC, 1.0f, 25.0f);
        if (param_2->m300 != 0) {
            param_2->m300--;
        }
        cMtx_YrotS(*calc_mtx, (int)(param_3 * (REG0_S(2) + 13000)));
        for (s32 i = 0; i < 60; i++, pcVar4++, pcVar7++) {
            if (param_2->m300 != 0) {
                fVar3 = (REG0_F(12) + 10.0f) * (param_2->m300 * cM_ssin(cM_rad2s((s32)(i) * 0.053247336f)));
                local_70.x = fVar3 * cM_scos(i_this->mC746 * (REG0_S(3) + 0x5800));
                local_70.z = fVar3 * cM_scos(i_this->mC746 * (REG0_S(5) + 0x5200));
            } else {
                fVar3 = param_2->m2EC * cM_ssin(cM_rad2s(0.053247336f * (f32)(i)));
                fVar3 *= (0.01666667f * (f32)(0x3B - i));
                local_70.x = fVar3 * cM_scos(i_this->mC746 * (REG0_S(3) + 200) + i * (REG0_S(4) + 2000));
                local_70.z = fVar3 * cM_scos(i_this->mC746 * (REG0_S(5) + 0xfa) + i * (REG0_S(6) + 2000));
            }
            MtxPosition(&local_70, &cStack_7c);
            param_2->m000[i] = local_64;
            *pcVar4 = local_64 + cStack_7c;
            *pcVar7 = REG0_S(2) + 6;
            local_64.y += 50.0f;
        }
    }
}

/* 000092B8-0000960C       .text action_main__FP9bgn_class */
static void action_main(bgn_class* i_this) {
    cXyz* pcVar7;
    u8* pcVar5;
    f32 dVar9;
    cXyz local_90;
    cXyz local_9c;

    local_9c = i_this->mC308;
    cLib_addCalc0(&i_this->mC774, 1.0f, 25.0f);
    pcVar7 = i_this->mRedRopeMat.getPos(0);
    pcVar5 = i_this->mRedRopeMat.getSize(0);
    for (s32 i = 0; i < 60; i++, pcVar7++, pcVar5++) {
        dVar9 = i_this->mC774 * cM_ssin(cM_rad2s(0.053247336f * (f32)(i)));
        dVar9 *= (0.01666667f * (f32)(0x3B - i));
        local_90.x = dVar9 * cM_ssin(i_this->mC746 * (REG0_S(3) + 300) + i * (REG0_S(4) + 2000));
        local_90.z = dVar9 * cM_ssin(i_this->mC746 * (REG0_S(5) + 0xfa) + i * (REG0_S(6) + 2000));
        *pcVar7 = local_9c + local_90;
        *pcVar5 = REG0_S(3) + 10;
        local_9c.y += 50.0f;
    }
    if (l_HIO.m025 == 0) {
        switch (i_this->mC748) {
        case 0:
            dance_0(i_this);
            move_se_set(i_this);
            break;
        case 1:
            punch_LR(i_this);
            move_se_set(i_this);
            break;
        case 2:
            body_attack(i_this);
            move_se_set(i_this);
            break;
        case 3:
            tail_attack(i_this);
            move_se_set(i_this);
            break;
        case 4:
            head_recover(i_this);
            move_se_set(i_this);
            break;
        case 5:
            damage(i_this);
            break;
        case 6:
            hensin(i_this);
            break;
        case 7:
            start(i_this);
            break;
        case 10:
            i_this->mC754 = 1;
            i_this->mCC80 = 1.0f;
        }
        if (i_this->mC748 > 0) {
            cLib_addCalcAngleS2(&i_this->mC750, 0, 10, 0x200);
        }
    }
    for (s32 i = 0; i < 8; i++) {
        action_s(i_this, &i_this->mAAA8[i], i);
    }
    cLib_addCalc2(&i_this->mC334, i_this->mC338, 1.0f, 10.0f);
    i_this->mC338 = l_HIO.m0D4;
}

/* 0000960C-00009F6C       .text move__FP9bgn_class */
static void move(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar1;
    int iVar3;
    f32 fVar9;
    csXyz local_110;
    cXyz local_e4;

    i_this->mC734 = i_this->mC728;
    i_this->mJyakutenCBrkAnm->play();
    i_this->mJyakutenBBrkAnm->play();
    if (i_this->m02B5 != 0) {
        i_this->mC748 = 10;
        actor->current.pos.set(0.0f, 30000.0f, 0.0f);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        i_this->mCC80 = REG0_F(25) + 1.0f;
        i_this->mCC84 = REG0_F(20);
        i_this->mCC88 = REG0_F(21);
    } else {
        if (i_this->mC748 == 10) {
            actor->current.pos = actor->home.pos;
            i_this->mC748 = 0;
            i_this->mC74A = 0;
            actor->health = 3;
        }
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x22;
        i_this->mC308 = actor->current.pos + i_this->mC728;
        i_this->mC308.y += l_HIO.m04C;
        if (i_this->mC308.y <= (i_this->mC7BC + 100.0f + REG0_F(0))) {
            i_this->mC308.y = (i_this->mC7BC + 100.0f + REG0_F(0));
        }
        local_110 = actor->shape_angle;
        if (l_HIO.m025 != 0) {
            local_110.y = l_HIO.m042;
        }
        BGN_HAND_MAX = l_HIO.m0F0;
        BGN_TAIL_MAX = l_HIO.m0F2;
        dBgS_GndChk local_d8;
        Vec pos;
        pos = actor->current.pos;
        pos.y += 500.0f;
        local_d8.SetPos(&pos);
        i_this->mC7BC = (((REG0_F(16) + -40.0f) + 30.0f) + 100.0f);
        sVar1 = 0;
        if (i_this->mAAA8[0].m2D0 != 0) {
            sVar1 = 8000;
        }
        if (i_this->mAAA8[1].m2D0 != 0) {
            sVar1 -= 8000;
        }
        cLib_addCalcAngleS2(&i_this->mC744, sVar1, 8, 0x400);
        if (i_this->mAAA8[2].m2D0 == 0) {
            local_110.x += (int)(i_this->mAAA8[2].m2D4.y * (REG0_F(11) + 8.0f));
        }
        if (i_this->mAAA8[3].m2D0 != 0) {
            local_110.z -= (s16)(REG0_S(0) + 3000);
        } else {
            local_110.z += (int)(i_this->mAAA8[3].m2D4.y * (REG0_F(12) + 5.0f));
            local_110.y += (int)(i_this->mAAA8[3].m2D4.z * -(REG0_F(13) + 5.0f));
        }
        if (i_this->mAAA8[4].m2D0 != 0) {
            local_110.z += (s16)(REG0_S(0) + 3000);
        } else {
            local_110.z += (int)(i_this->mAAA8[4].m2D4.y * -(REG0_F(12) + 5.0f));
            local_110.y += (int)(i_this->mAAA8[4].m2D4.z * (REG0_F(13) + 5.0f));
        }
        cLib_addCalcAngleS2(&i_this->mC314.x, local_110.x, 4, 0x200);
        cLib_addCalcAngleS2(&i_this->mC31A, local_110.y, 4, 0x1000);
        cLib_addCalcAngleS2(&i_this->mC314.z, local_110.z, 4, 0x200);
        i_this->mC314.y = i_this->mC31A + i_this->mC750;
        if (l_HIO.m029 != 0) {
            i_this->mAAA8[0].m2D0 = 1;
        }
        if (l_HIO.m02A != 0) {
            i_this->mAAA8[1].m2D0 = 1;
        }
        if (l_HIO.m02B != 0) {
            i_this->mAAA8[2].m2D0 = 1;
        }
        if (l_HIO.m02C != 0) {
            i_this->mAAA8[3].m2D0 = 1;
        }
        if (l_HIO.m02D != 0) {
            i_this->mAAA8[4].m2D0 = 1;
        }
        if (l_HIO.m02E != 0) {
            i_this->mAAA8[5].m2D0 = 1;
        }
        if (l_HIO.m02F != 0) {
            i_this->mAAA8[6].m2D0 = 1;
        }
        if (l_HIO.m030 != 0) {
            i_this->mAAA8[7].m2D0 = 1;
        }
        fVar9 = 0.0f;
        for (s32 i = 0; i < 2; i++) {
            if ((i == 0) && (i_this->mC778 != 0)) {
                local_e4 = i_this->mLeftArmParts[BGN_HAND_MAX].m0D4 - i_this->mLeftArmParts[BGN_HAND_MAX - 1].m0D4;
                fVar9 = local_e4.abs();
            } else if ((i == 1) && (i_this->mC779 != 0)) {
                local_e4 = i_this->mRightArmParts[BGN_HAND_MAX].m0D4 - i_this->mRightArmParts[BGN_HAND_MAX - 1].m0D4;
                fVar9 = local_e4.abs();
            }
            f32 temp_f0_8 = (200.0f + REG0_F(5));
            if (fVar9 > temp_f0_8) {
                fVar9 -= temp_f0_8;
                fVar9 *= (REG0_F(6) + 0.2f);
            } else {
                fVar9 = 0.0f;
            }
            cLib_addCalc2(&i_this->mC324[i], (l_HIO.m124 + fVar9), 1.0f, (20.0f + REG0_F(4)));
            cLib_addCalc0(&i_this->mC32C[i], 0.05f, 0.02f);
        }
        size_set(i_this);
        i_this->mC7FC.OffAtSetBit();
        i_this->mPelvisParts[0].mPartSph.OffAtSetBit();
        i_this->mLeftArmParts[BGN_HAND_MAX - 1].mPartSph.OffAtSetBit();
        i_this->mRightArmParts[BGN_HAND_MAX - 1].mPartSph.OffAtSetBit();
        for (iVar3 = 0; iVar3 < BGN_TAIL_MAX; iVar3++) {
            i_this->mTailParts[iVar3].mPartSph.OffAtSetBit();
        }
        action_main(i_this);
        damage_check(i_this);
        shape_calc(i_this);
    }
}

/* 0000A104-0000AE8C       .text demo_camera__FP9bgn_class */
static void demo_camera(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    f32 dVar11;
    cXyz local_44;
    cXyz local_50;
    cXyz local_5c;
    cXyz camera_eye;
    cXyz camera_center;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    switch (i_this->mCSMode) {
    case 0:
        break;
    case 1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCSMode++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mKSubCount = 0;
        i_this->mCSFovY = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCSCamCenter = i_this->mC308;
        player->changeOriginalDemo();
        fpcM_Search(ki_del_sub, i_this);
        i_this->mKeeseSpawnNum = 0;
        // fallthrough
    case 2:
        cMtx_YrotS(*calc_mtx, i_this->mC314.y);
        local_44.x = REG0_F(0) + 200.0f;
        local_44.y = REG0_F(1) + 100.0f;
        local_44.z = REG0_F(2) + 2000.0f;
        MtxPosition(&local_44, &local_50);
        i_this->mCSCamEye = local_50;
        if (i_this->mKSubCount > 300) {
            fVar2 = 0.1f;
        } else {
            fVar2 = 0.5f;
        }
        dVar11 = fVar2;
        cLib_addCalc2(&i_this->mCSCamCenter.x, i_this->mC308.x, 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.y, i_this->mC308.y + 100.0f + REG0_F(3), dVar11, 400.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.z, i_this->mC308.z, 0.1f, 300.0f);
        local_44.x = REG0_F(4);
        local_44.y = player->current.pos.y;
        local_44.z = REG0_F(5) + 1500.0f;
        MtxPosition(&local_44, &local_50);
        player->setPlayerPosAndAngle(&local_50, (int)(s16)(i_this->mC314.y + 0x8000));
        if (i_this->mKSubCount == (s16)(REG0_S(5) + 220)) {
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        if (i_this->mKSubCount == (s16)(REG0_S(6) + 320)) {
            player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        }
        break;
    case 3:
        cLib_addCalc2(&i_this->mCSCamCenter.x, bgn2->actor.current.pos.x, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.y, bgn2->actor.current.pos.y + REG0_F(13), 0.1f, 200.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.z, bgn2->actor.current.pos.z, 0.1f, 100.0f);
        if (i_this->mKSubCount == (s16)(REG0_S(7) + 90)) {
            i_this->mCA9C = REG0_F(18) + 30.0f;
        }
        if (i_this->mKSubCount == (s16)(REG0_S(7) + 100)) {
            player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
            player->voiceStart(29);
        }
        if (i_this->mKSubCount > (s16)(REG0_S(8) + 110)) {
            cLib_addCalc2(&i_this->mCSFovY, REG0_F(11) + 35.0f, 0.1f, REG0_F(12) + 0.5f);
            if ((i_this->mKSubCount == 130) || (i_this->mKSubCount == 180)) {
                mDoAud_seStart(JA_SE_CM_BGN_T_MOUSE_OPEN, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
            if (i_this->mKSubCount == 152) {
                mDoAud_seStart(JA_SE_CM_BGN_T_MOUSE_CLOSE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
#if VERSION > VERSION_DEMO
        cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 1);
#endif
        if (i_this->mKSubCount <= (s16)(REG0_S(8) + 200)) {
            break;
        }
        mDoAud_bgmStart(JA_BGM_BGN_TARABA);
        goto block_57;
    case 10:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCSMode++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mKSubCount = 0;
        i_this->mCSFovY = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCSCamCenter = bgn2->actor.current.pos;
        player->changeOriginalDemo();
#if VERSION > VERSION_DEMO
        fpcM_Search(ki_del_sub, i_this);
#endif
        bgn2->m2ED0 = 0;
        i_this->mCA74.set(200.0f, 2100.0f, 2500.0f);
    case 11:
    case 12:
        cLib_addCalc2(&i_this->mCA74.x, -1800.0f, 0.05f, i_this->mCA98 * 2000.0f);
        cLib_addCalc2(&i_this->mCA74.y, 1100.0f, 0.05f, i_this->mCA98 * 1000.0f);
        cLib_addCalc2(&i_this->mCA74.z, 1000.0f, 0.05f, i_this->mCA98 * 1500.0f);
        cLib_addCalc2(&i_this->mCA98, 0.01f, 1.0f, 0.0001f);
        cMtx_YrotS(*calc_mtx, bgn2->actor.shape_angle.y);
        MtxPosition(&i_this->mCA74, &local_50);
        i_this->mCSCamEye = local_50;
        if (i_this->mCSMode == 11) {
            cLib_addCalc2(&i_this->mCSCamCenter.x, bgn2->actor.current.pos.x, 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCSCamCenter.y, bgn2->actor.current.pos.y + REG0_F(13), 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCSCamCenter.z, bgn2->actor.current.pos.z, 0.1f, 300.0f);
            local_44.x = REG0_F(4);
            local_44.y = player->current.pos.y;
            local_44.z = REG0_F(5) + -2000.0f;
            MtxPosition(&local_44, &local_50);
            player->setPlayerPosAndAngle(&local_50, bgn2->actor.shape_angle.y);
        } else {
            cLib_addCalc2(&i_this->mCSCamCenter.x, bgn3->actor.current.pos.x, 0.1f, 300.0f);
            cLib_addCalc2(
                &i_this->mCSCamCenter.y,
                DEMO_SELECT(bgn3->actor.current.pos.y + 200.0f + REG0_F(16), bgn3->actor.current.pos.y + 50.0f + REG8_F(16)),
                0.1f,
                300.0f
            );
            cLib_addCalc2(&i_this->mCSCamCenter.z, bgn3->actor.current.pos.z, 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCSFovY, REG0_F(17) + 30.0f, REG0_F(18) + 0.05f, REG0_F(19) + 0.2f);
#if VERSION > VERSION_DEMO
            cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 2);
#endif
        }
        if (i_this->mKSubCount > (s16)(REG0_S(9) + DEMO_SELECT(310, 370))) {
            goto block_57;
        }
        break;
    case 20:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCSMode++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mKSubCount = 0;
        i_this->mCSFovY = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCSCamCenter = bgn3->actor.current.pos;
        player->changeOriginalDemo();
#if VERSION > VERSION_DEMO
        i_this->mCA60 = 0xb4;
        fpcM_Search(ki_del_sub, i_this);
        fpcM_Search(ks_del_sub, i_this);
#endif
    case 21:
#if VERSION > VERSION_DEMO
        cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 1);
#endif
        i_this->mCSCamEye.set(500.0f, REG0_F(3) + 500.0f, REG0_F(4) + 2000.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.x, bgn3->actor.current.pos.x, 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.y, bgn3->actor.current.pos.y + REG0_F(13), 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCSCamCenter.z, bgn3->actor.current.pos.z, 0.1f, 300.0f);
        local_44.x = REG0_F(4);
        local_44.y = player->current.pos.y;
        local_44.z = REG0_F(5) + -1000.0f;
        player->setPlayerPosAndAngle(&local_44, bgn2->actor.shape_angle.y);
        if (i_this->mKSubCount == 260) {
            mDoAud_monsSeStart(JA_SE_CV_BGN_DIE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mKSubCount >= 370) {
            local_5c.setall(REG0_F(4) + 10.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUBAKUEN, &bgn3->actor.current.pos, NULL, &local_5c);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &bgn3->actor.current.pos, NULL, &local_5c);
            mDoAud_seStart(JA_SE_CM_BGN_LAST_EXPLODE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->m02B5 = 3;
            l_HIO.m024 = 3;
            i_this->mCSMode++;
#if VERSION > VERSION_DEMO
            i_this->mC720 = 1;
            i_this->mCA60 = 0xb4;
#endif
        }
        break;
    case 22:
#if VERSION > VERSION_DEMO
        if (i_this->mKSubCount >= 390) {
            last_himo_control(i_this);
        }
#endif
        if (i_this->mKSubCount >= DEMO_SELECT(430, (s16)(REG8_S(7) + 500))) {
            i_this->mCC90 = 2;
        }
        break;
    case 150:
    block_57:
        camera->mCamera.SetTrimSize(0);
        camera->mCamera.Start();
        dMeter_mtrShow();
        dComIfGp_event_reset();
        i_this->mCSMode = 0;
#if VERSION > VERSION_DEMO
        i_this->mCA60 = 1;
#endif
        break;
    default:
        break;
    }
    if (i_this->mCSMode != 0) {
        f32 fx = i_this->mCA9C * cM_ssin(i_this->mKSubCount * 0x3300);
        f32 fy = i_this->mCA9C * cM_scos(i_this->mKSubCount * 0x3000);
        camera_eye.x = i_this->mCSCamEye.x + fx;
        camera_eye.y = i_this->mCSCamEye.y + fy;
        camera_eye.z = i_this->mCSCamEye.z;
        camera_center.x = i_this->mCSCamCenter.x + fx;
        camera_center.y = i_this->mCSCamCenter.y + fy;
        camera_center.z = i_this->mCSCamCenter.z;
        s16 bank = (i_this->mCA9C * cM_scos(i_this->mC746 * 0x1c00) * 7.5f);
        camera->mCamera.Set(camera_center, camera_eye, bank, i_this->mCSFovY);
        cLib_addCalc0(&i_this->mCA9C, 1.0f, (REG0_F(16) + 1.0f));
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->mKSubCount);
        i_this->mKSubCount++;
    }
}

/* 0000AE8C-0000B134       .text daBgn_Execute__FP9bgn_class */
static BOOL daBgn_Execute(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

    if (i_this->m02B4 == 0xFF) {
        return TRUE;
    }
    local_1c.setall(0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &center_pos, &bg_tevstr);
    bomb_splash_check(i_this);
#if VERSION == VERSION_DEMO
    bgn = i_this;
    if (bgn2 == NULL) {
        bgn2 = (bgn2_class*)fpcM_Search(bgn2_s_sub, i_this);
    }
    if (bgn3 == NULL) {
        bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
    }
#else
    bgn2 = (bgn2_class*)fpcM_Search(bgn2_s_sub, i_this);
    bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
#endif
    if (l_HIO.m027 != 0) {
        actor->health = l_HIO.m027;
    }
    if (i_this->mCC90 == 1) {
        i_this->mCC90 = 0;
        i_this->m02B5 = 2;
        l_HIO.m024 = 2;
    }
    i_this->mC746++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->mC7AC[i] != 0) {
            i_this->mC7AC[i]--;
        }
    }
    if (i_this->mC7B6 != 0) {
        i_this->mC7B6--;
    }
    if (i_this->mC7B8 != 0) {
        i_this->mC7B8--;
    }
    if (i_this->mArrowHitFlashTimer != 0) {
        i_this->mArrowHitFlashTimer--;
    }
    if (i_this->m0304 != 0) {
        i_this->m0304--;
    }
    if (i_this->m0302 != 0) {
        i_this->m0302++;
        if (i_this->m0302 > 100) {
            i_this->m0302 = 0;
        }
    }
    move(i_this);
    demo_camera(i_this);
    if (i_this->mKeeseSpawnNum != 0) {
        i_this->mKeeseSpawnNum--;
        if (ki_check(i_this) < l_HIO.mKeeseNumMax) {
            local_28.x = cM_rndFX(2500.0f);
            local_28.y = cM_rndF(500.0f) + 3500.0f;
            local_28.x = cM_rndFX(2500.0f);
            fopAcM_create(PROC_KI, 0xFFFF0003, &local_28, fopAcM_GetRoomNo(actor));
        }
    }
    i_this->m02B5 = l_HIO.m024;
    if (i_this->mCC90 == 2) {
        i_this->mCC90 = 0;
        dComIfGp_setNextStage("GanonK", 4, 0, 9);
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F10);
    }
    return TRUE;
}

/* 0000B134-0000B13C       .text daBgn_IsDelete__FP9bgn_class */
static BOOL daBgn_IsDelete(bgn_class*) {
    return TRUE;
}

/* 0000B13C-0000B238       .text daBgn_Delete__FP9bgn_class */
static BOOL daBgn_Delete(bgn_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Bgn");
#if VERSION > VERSION_DEMO
    i_this->mPunchSmokeCb[0].remove();
    i_this->mPunchSmokeCb[1].remove();
#endif
    if (i_this->mCC91 != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    mDoAud_seDeleteObject(&i_this->mC77C);
    mDoAud_seDeleteObject(&i_this->mC788);
    mDoAud_seDeleteObject(&i_this->mCA54);
    mDoAud_seDeleteObject(&i_this->m0308);
    return TRUE;
}

/* 0000B238-0000B284       .text part_init__FP6part_sP12J3DModelData */
static s32 part_init(part_s* param_1, J3DModelData* param_2) {
    param_1->mpPartModel = mDoExt_J3DModel__create(param_2, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (!param_1->mpPartModel) {
        return FALSE;
    }
    return TRUE;
}

/* 0000B284-0000B994       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    J3DModelData* modelData;
    J3DModelData* bodyModelData;
    J3DAnmTevRegKey* pBrk;
    ResTIMG* pBti;
    bgn_class* i_this = (bgn_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_HEAD1),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bgn", BGN_BCK_BGN_HEAD1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mHeadParts[0].mpPartModel = i_this->mpMorf->getModel();
    i_this->mHeadParts[0].m0D2 = 16;
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_MAIN1);
    i_this->mpChestModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->mpChestModel == NULL) {
        return FALSE;
    }
    bodyModelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_BODY1);
    if (!part_init(&i_this->mPelvisParts[0], bodyModelData)) {
        return FALSE;
    }
    i_this->mPelvisParts[0].m0D2 = 10;
    for (s32 i = 0; i < 20; i++) {
        if (!part_init(&i_this->mLeftArmParts[i], bodyModelData)) {
            return FALSE;
        }
        if (!part_init(&i_this->mRightArmParts[i], bodyModelData)) {
            return FALSE;
        }
        i_this->mRightArmParts[i].m0D2 = i * 3 + 13;
        i_this->mLeftArmParts[i].m0D2 = i * 3 + 13;
    }
    for (s32 i = 0; i < 3; i++) {
        if (!part_init(&i_this->mLeftLegParts[i], bodyModelData)) {
            return FALSE;
        }
        if (!part_init(&i_this->mRightLegParts[i], bodyModelData)) {
            return FALSE;
        }
        i_this->mRightLegParts[i].m0D2 = i * 3 + 10;
        i_this->mLeftLegParts[i].m0D2 = i * 3 + 10;
    }
    for (s32 i = 0; i < 20; i++) {
        if (!part_init(&i_this->mTailParts[i], bodyModelData)) {
            return FALSE;
        }
        i_this->mTailParts[i].m0D2 = 11 - i;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENA);
    i_this->mpJyakutenAModel = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenAModel == NULL) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENB);
    i_this->mpJyakutenBModel = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenBModel == NULL) {
        return FALSE;
    }
    i_this->mJyakutenBBrkAnm = new mDoExt_brkAnm();
#if VERSION > VERSION_DEMO
    if (i_this->mJyakutenBBrkAnm == NULL) {
        return FALSE;
    }
#endif
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENB));
    if (!i_this->mJyakutenBBrkAnm->init(modelData, pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENC);
    i_this->mpJyakutenCModel = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenCModel == NULL) {
        return FALSE;
    }
    i_this->mJyakutenCBrkAnm = new mDoExt_brkAnm();
#if VERSION > VERSION_DEMO
    if (i_this->mJyakutenCBrkAnm == NULL) {
        return FALSE;
    }
#endif
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENC));
    if (!i_this->mJyakutenCBrkAnm->init(modelData, pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    pBti = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    if (!i_this->mRedRopeMat.init(1, 0x3C, pBti, 1)) {
        return FALSE;
    }
    pBti = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_HIMO);
    if (!i_this->mBlueRopeMat.init(8, 0x3C, pBti, 1)) {
        return FALSE;
    }
#if VERSION > VERSION_DEMO
    pBti = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    if (!i_this->mDefeatCSRopeMat.init(1, 0x3C, pBti, 1)) {
        return FALSE;
    }
#endif
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_R0E_A);
    JUT_ASSERT(DEMO_SELECT(6628, 7026), modelData != NULL);
    i_this->mpWater0Model = mDoExt_J3DModel__create(modelData, 0x80000, 0x31000000);
    if (i_this->mpWater0Model == NULL) {
        return FALSE;
    }
    i_this->mpWater1Model = mDoExt_J3DModel__create(modelData, 0x80000, 0x30000000);
    if (i_this->mpWater1Model == NULL) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_R00);
    i_this->mpRoomReflectionModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    JUT_ASSERT(DEMO_SELECT(6654, 7052), modelData != NULL);
    if (i_this->mpRoomReflectionModel == NULL) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/* 0000B9DC-0000CA80       .text daBgn_Create__FP10fopAc_ac_c */
static cPhs_State daBgn_Create(fopAc_ac_c* a_this) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
    };
    static dCcD_SrcSph core_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_LIGHT_ARROW,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 70.0f,
        }},
    };
    cXyz local_50;

    bgn_class* i_this = (bgn_class*)a_this;
    cPhs_State res;
    fopAcM_SetupActor(a_this, bgn_class);
    res = dComIfG_resLoad(&i_this->mPhase, "Bgn");
    if (res == cPhs_COMPLEATE_e) {
        i_this->mPunchSmokeCb[0].setFollowOff();
        i_this->mPunchSmokeCb[1].setFollowOff();
#if VERSION > VERSION_DEMO
        bgn = i_this;
#endif
        bgn2 = NULL;
        bgn3 = NULL;
        i_this->m02B4 = (u8)fopAcM_GetParam(a_this);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        if (i_this->m02B4 != 0xFF) {
            if (hio_set == false) {
                i_this->mCC91 = 1;
                hio_set = true;
                l_HIO.mNo = mDoHIO_createChild("Ｇ（クグツ）", &l_HIO); // G (Puppet)
                BGN_HAND_MAX = l_HIO.m0F0;
                BGN_TAIL_MAX = l_HIO.m0F2;
            }
            i_this->mStts.Init(0xFF, 0xFF, a_this);
            i_this->mC7FC.Set(cc_sph_src);
            i_this->mC7FC.SetStts(&i_this->mStts);
            i_this->mC7FC.OffAtSetBit();
            i_this->mCoreSph.Set(core_sph_src);
            i_this->mCoreSph.SetStts(&i_this->mStts);
            i_this->mHeadParts[0].mPartSph.Set(cc_sph_src);
            dCcD_Stts* temp_r26 = &i_this->mStts;
            i_this->mHeadParts[0].mPartSph.SetStts(temp_r26);
            i_this->mHeadParts[0].mPartSph.OffAtSetBit();
#if VERSION > VERSION_DEMO
            i_this->mHeadParts[0].mPartTevStr = a_this->tevStr;
#endif
            i_this->mPelvisParts[0].mPartSph.Set(cc_sph_src);
            i_this->mPelvisParts[0].mPartSph.SetStts(temp_r26);
            i_this->mPelvisParts[0].mPartSph.OffAtSetBit();
#if VERSION > VERSION_DEMO
            i_this->mPelvisParts[0].mPartTevStr = a_this->tevStr;
#endif
            for (s32 i = 0; i < 20; i++) {
                i_this->mLeftArmParts[i].mPartSph.Set(cc_sph_src);
                i_this->mLeftArmParts[i].mPartSph.SetStts(&i_this->mStts);
                i_this->mLeftArmParts[i].mPartSph.OffAtSetBit();
                i_this->mRightArmParts[i].mPartSph.Set(cc_sph_src);
                i_this->mRightArmParts[i].mPartSph.SetStts(&i_this->mStts);
                i_this->mRightArmParts[i].mPartSph.OffAtSetBit();
#if VERSION > VERSION_DEMO
                i_this->mLeftArmParts[i].mPartTevStr = a_this->tevStr;
                i_this->mRightArmParts[i].mPartTevStr = a_this->tevStr;
#endif
            }
            for (s32 i = 0; i < 3; i++) {
                i_this->mLeftLegParts[i].mPartSph.Set(cc_sph_src);
                i_this->mLeftLegParts[i].mPartSph.SetStts(&i_this->mStts);
                i_this->mLeftLegParts[i].mPartSph.OffAtSetBit();
                i_this->mRightLegParts[i].mPartSph.Set(cc_sph_src);
                i_this->mRightLegParts[i].mPartSph.SetStts(&i_this->mStts);
                i_this->mRightLegParts[i].mPartSph.OffAtSetBit();
#if VERSION > VERSION_DEMO
                i_this->mLeftLegParts[i].mPartTevStr = a_this->tevStr;
                i_this->mRightLegParts[i].mPartTevStr = a_this->tevStr;
#endif
            }
            for (s32 i = 0; i < 20; i++) {
                i_this->mTailParts[i].mPartSph.Set(cc_sph_src);
                i_this->mTailParts[i].mPartSph.SetStts(&i_this->mStts);
                i_this->mTailParts[i].mPartSph.OffAtSetBit();
#if VERSION > VERSION_DEMO
                i_this->mTailParts[i].mPartTevStr = a_this->tevStr;
#endif
            }
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2FA = cM_rndF(32768.0f);
                i_this->mAAA8[i].m2FC = cM_rndF(32768.0f);
            }
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3F10)) {
                i_this->m02B4 = 0xFF;
                local_50.set(375.17f, REG8_F(4) + 4441.46f, REG8_F(3) + -15.0f);
                fopAcM_create(PROC_HIMO3, 0xf, &local_50, fopAcM_GetRoomNo(a_this));
                local_50.set(375.17f, REG8_F(4) + 4453.96f, 0.0f);
                csXyz cStack_58(0, 0x4000, 0);
                fopAcM_create(PROC_KUI, 0xffff0400, &local_50, fopAcM_GetRoomNo(a_this), &cStack_58, NULL, 0xFF, NULL);
            } else {
                for (s32 parameters = 0, i = 0; parameters < 8; i++, parameters++) {
                    fopAcM_create(PROC_ATT, parameters, &a_this->current.pos, fopAcM_GetRoomNo(a_this));
                    i_this->mAAA8[i].m308 = 3;
                }
                fopAcM_create(PROC_BGN2, 0, &a_this->current.pos, fopAcM_GetRoomNo(a_this));
                fopAcM_create(PROC_BGN3, 0, &a_this->current.pos, fopAcM_GetRoomNo(a_this));
                mDoAud_bgmStart(JA_BGM_BGN_KUGUTSU);
                a_this->health = 3;
                a_this->max_health = 3;
            }
            i_this->mCC80 = 1.0f;
            i_this->mC748 = 7;
            i_this->mC7AC[0] = 0x3c;
#if VERSION > VERSION_DEMO
            bg_tevstr = a_this->tevStr;
            i_this->mWaterTevStr = a_this->tevStr;
            i_this->mRoomTevStr = a_this->tevStr;
#endif
            daBgn_Execute(i_this);
        }
    }
    return res;
}

static actor_method_class l_daBgn_Method = {
    (process_method_func)daBgn_Create,
    (process_method_func)daBgn_Delete,
    (process_method_func)daBgn_Execute,
    (process_method_func)daBgn_IsDelete,
    (process_method_func)daBgn_Draw,
};

actor_process_profile_definition g_profile_BGN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN,
    /* Actor SubMtd */ &l_daBgn_Method,
    /* Status       */ DEMO_SELECT(fopAcStts_UNK4000_e | fopAcStts_UNK40000_e, fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e),
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
