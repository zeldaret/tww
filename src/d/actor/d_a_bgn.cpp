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
#include "d/actor/d_a_ks.h"
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
    /* 0x174 */ s16 m174;
    /* 0x176 */ s16 m176;
    /* 0x178 */ s16 m178;
    /* 0x17A */ s16 m17A;
}; // Size: 0x17C

/* 000000EC-000003F0       .text __ct__11daBgn_HIO_cFv */
daBgn_HIO_c::daBgn_HIO_c() {
    mNo = 0xff;
    m00C = 1;
    m00D = 1;
    m010 = 50.0f;
    m014 = 10;
    m016 = 10;
    m018 = 0x50;
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
    m0D8 = 0x78;
    m0DA = 0x14;
    m0DC = 0x4b0;
    m0DE = 0x5dc;
    m0E0 = 2000;
    m0E2 = 300;
    m0E4 = 200;
    m0E6 = 0x96;
    m0E8 = 0xf;
    m0EA = 0xf;
    m0EC = 0xf;
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
    m174 = 3;
    m176 = 4;
    m178 = 5;
    m17A = 5;
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
    mDoMtx_stack_c::transS(REG0_F(0xe), REG0_F(0xf) + -30.0f, REG0_F(0x10));
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
void part_draw(bgn_class* i_this, part_s* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar1;
    s16 uVar4;
    s16 uVar5;
    s16 uVar6;
    J3DModel* pJVar7;
    f32 fVar8;
    cXyz local_38;

    pJVar7 = param_2->m000;
    if (pJVar7 != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &param_2->m0D4, &param_2->m018);
        if (i_this->mCC88 > 0.0f) {
            param_2->m018.mFogColor.b = 0;
            param_2->m018.mFogColor.g = 0;
            param_2->m018.mFogColor.r = 0;
            param_2->m018.mFogStartZ = param_2->m018.mFogStartZ + i_this->mCC88 * -50000.0f;
        }
        if (param_2->m0D0 != 0) {
            uVar4 = param_2->m018.mFogColor.r + param_2->m0C8;
            if (0xff < uVar4) {
                uVar4 = 0xff;
            }
            uVar5 = param_2->m018.mFogColor.g + param_2->m0C8;
            if (0xff < uVar5) {
                uVar5 = 0xff;
            }
            uVar6 = param_2->m018.mFogColor.g + (param_2->m0C8 / 2);
            if (0xff < uVar6) {
                uVar6 = 0xff;
            }
            if (param_2->m0D0 > 0x28) {
                cLib_addCalcAngleS2(&param_2->m0C8, 0x118, 1, 0x1e);
                cLib_addCalc2(&param_2->m0CC, -50000.0f, 1.0f, 5000.0f);
            } else {
                cLib_addCalcAngleS2(&param_2->m0C8, 0, 1, 7);
                cLib_addCalc0(&param_2->m0CC, 1.0f, 1250.0f);
            }
            param_2->m018.mFogColor.r = uVar4 & 0xff;
            param_2->m018.mFogColor.g = uVar5 & 0xff;
            param_2->m018.mFogColor.b = uVar6 & 0xff;
            param_2->m018.mFogStartZ = param_2->m018.mFogStartZ + param_2->m0CC;
        }
        camera_class* camera = (camera_class*)dComIfGp_getCamera(0);
        local_38 = param_2->m224 - camera->mLookat.mEye;
        fVar8 = local_38.abs();
        if (fVar8 > l_HIO.m008 * param_2->m0F4) {
            g_env_light.setLightTevColorType(pJVar7, &param_2->m018);
            sVar1 = actor->health;
            if ((sVar1 <= 2) && (param_2 == &i_this->m7BBC[BGN_TAIL_MAX - 1])) {
                if (sVar1 == 1) {
                    i_this->m02EC->entry(pJVar7->getModelData());
                } else {
                    i_this->m02F0->entry(pJVar7->getModelData());
                }
            }
            if (param_2 == i_this->m0314) {
                i_this->m02B8->entryDL();
            } else {
                mDoExt_modelUpdateDL(pJVar7);
            }
        }
        if (l_HIO.m00C != 0) {
            param_2->m004.mpModel = pJVar7;
            dComIfGd_getOpaListSky()->entryImm(&param_2->m004, 0);
        }
    }
}

/* 000008F8-00000B70       .text water0_disp__FP9bgn_class */
void water0_disp(bgn_class* i_this) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;
    J3DMaterial* pJVar8;

    g_env_light.settingTevStruct(TEV_TYPE_BG1, &w_pos, &i_this->mCAAC);
    MtxTrans(0.0f, REG0_F(0xb), 0.0f, false);
    i_this->mCAA4->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mCAA4, &i_this->mCAAC);
    dComIfGd_setListSky();
    pJVar8 = i_this->mCAA4->getModelData()->getMaterialNodePointer(0);
    J3DBlend* blend = pJVar8->getBlend();
    blend->getType();
    J3DZMode* zMode = pJVar8->getZMode();
    zMode->getFunc();
    J3DGXColorS10* tev_col = (J3DGXColorS10*)&pJVar8->getTevColor(0)->mColor;
    J3DGXColor* tev_kcol = (J3DGXColor*)&pJVar8->getTevKColor(0)->mColor;
    J3DGXColor* tev_kcol2 = (J3DGXColor*)&pJVar8->getTevKColor(3)->mColor;
    blend->setType(1);
    blend->setSrcFactor(4);
    blend->setDstFactor(5);
    zMode->setUpdateEnable(1);
    tev_col->mColor.b = 0;
    tev_col->mColor.g = 0;
    tev_col->mColor.r = 0;
    tev_kcol->mColor.b = 0xFF;
    tev_kcol->mColor.g = 0xFF;
    tev_kcol->mColor.r = 0xFF;
    fVar1 = l_HIO.m010;
    if ((i_this->m02B5 == 1) && (l_HIO.m00D == 0)) {
        fVar2 = (REG0_F(5) + 0.01f) * (REG0_F(4) + 4000.0f + bgn2->actor.current.pos.y);
        fVar1 = 90.0f;
        if (fVar2 > 90.0f) {
            fVar1 = fVar2;
        } else if (fVar2 < 50.0f) {
            fVar1 = 50.0f;
        }
    }
    tev_kcol2->mColor.a = (char)(int)(fVar1 * 2.559f);
    mDoExt_modelUpdateDL(i_this->mCAA4);
    dComIfGd_setList();
}

/* 00000B70-00000CAC       .text water1_disp__FP9bgn_class */
void water1_disp(bgn_class* i_this) {
    J3DMaterial* pJVar8;

    MtxTrans(0.0f, REG0_F(0xb), 0.0f, false);
    i_this->mCAA8->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mCAA8, &i_this->mCAAC);
    dComIfGd_setListSky();
    pJVar8 = i_this->mCAA8->getModelData()->getMaterialNodePointer(0);
    J3DBlend* blend = pJVar8->getBlend();
    blend->getType();
    J3DZMode* zMode = pJVar8->getZMode();
    blend->setType(0);
    zMode->setUpdateEnable(0);
    mDoExt_modelUpdateDL(i_this->mCAA8);
    dComIfGd_setList();
}

/* 00000CAC-00000FCC       .text daBgn_DrawS__FP9bgn_class */
void daBgn_DrawS(bgn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar1;
    s16 uVar2;
    s16 uVar3;
    s16 uVar4;

    if (i_this->mCC88 > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ += i_this->mCC88 * -50000.0f;
    }
    if (i_this->m0300 != 0) {
        uVar2 = actor->tevStr.mFogColor.r + i_this->m02F8;
        if (0xff < uVar2) {
            uVar2 = 0xff;
        }
        sVar1 = actor->tevStr.mFogColor.g;
        uVar3 = sVar1 + i_this->m02F8;
        if (0xff < uVar3) {
            uVar3 = 0xff;
        }
        uVar4 = sVar1 + (i_this->m02F8 / 2);
        if (0xff < uVar4) {
            uVar4 = 0xff;
        }
        if (i_this->m0300 > 0x28) {
            cLib_addCalcAngleS2(&i_this->m02F8, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m02FC, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m02F8, 0, 1, 7);
            cLib_addCalc0(&i_this->m02FC, 1.0f, 1250.0f);
        }
        actor->tevStr.mFogColor.r = uVar2 & 0xff;
        actor->tevStr.mFogColor.g = uVar3 & 0xff;
        actor->tevStr.mFogColor.b = uVar4 & 0xff;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m02FC;
    }
    g_env_light.setLightTevColorType(i_this->m02BC, &actor->tevStr);
    mDoExt_modelUpdateDL(i_this->m02BC);
    dSnap_RegistFig(DSNAP_TYPE_BGN, actor, 1.0f, 1.0f, 1.0f);
    if (l_HIO.m00C != 0) {
        i_this->m02C0.mpModel = i_this->m02BC;
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02C0, 0);
    }
    part_draw(i_this, i_this->m0314);
    part_draw(i_this, i_this->m078C);
    for (s32 i = 0; i < BGN_HAND_MAX; i++) {
        part_draw(i_this, &i_this->m0C04[i]);
        part_draw(i_this, &i_this->m3AF0[i]);
    }
    for (s32 i = 0; i < 3; i++) {
        part_draw(i_this, &i_this->m69DC[i]);
        part_draw(i_this, &i_this->m72CC[i]);
    }
    for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
        part_draw(i_this, &i_this->m7BBC[i]);
    }
    GXColor local_24 = {0xFF, 0xFF, 0xFF, 0};
    i_this->mC39C.update(0x3c, local_24, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->mC39C);
    GXColor local_28 = {0xFF, 0xFF, 0xFF, 0};
    i_this->mC3D8.update(0x3c, local_28, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->mC3D8);
}

/* 00000FCC-000012D0       .text daBgn2_Draw__FP10bgn2_class */
static BOOL daBgn2_Draw(bgn2_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar1;
    short sVar2;
    s16 uVar3;
    s16 uVar4;
    s16 uVar5;
    J3DModel* pJVar7;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    if (i_this->m2E7C > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ += i_this->m2E7C * -50000.0f;
    }
    if (i_this->m2D68 != 0) {
        uVar3 = actor->tevStr.mFogColor.r + i_this->m2D60;
        if (0xff < uVar3) {
            uVar3 = 0xff;
        }
        sVar2 = actor->tevStr.mFogColor.g;
        uVar4 = sVar2 + i_this->m2D60;
        if (0xff < uVar4) {
            uVar4 = 0xff;
        }
        uVar5 = sVar2 + (i_this->m2D60 / 2);
        if (0xff < uVar5) {
            uVar5 = 0xff;
        }
        if (i_this->m2D68 > 0x14) {
            cLib_addCalcAngleS2(&i_this->m2D60, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m2D64, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m2D60, 0, 1, 0xe);
            cLib_addCalc0(&i_this->m2D64, 1.0f, 2500.0f);
        }
        actor->tevStr.mFogColor.r = uVar3 & 0xff;
        actor->tevStr.mFogColor.g = uVar4 & 0xff;
        actor->tevStr.mFogColor.b = uVar5 & 0xff;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m2D64;
    }
    g_env_light.setLightTevColorType(i_this->m02B4->getModel(), &actor->tevStr);
    g_env_light.setLightTevColorType(i_this->m02CC->getModel(), &actor->tevStr);
    i_this->m02B4->entryDL();
    if (l_HIO.m00C != 0) {
        i_this->m02B8.mpModel = i_this->m02B4->getModel();
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02B8, 0);
    }
    i_this->m02CC->entryDL();
    if (l_HIO.m00C != 0) {
        i_this->m02D0.mpModel = i_this->m02CC->getModel();
        dComIfGd_getOpaListSky()->entryImm(&i_this->m02D0, 0);
    }
    sVar1 = actor->health;
    if (sVar1 != 0) {
        if (sVar1 == 3) {
            pJVar7 = i_this->m02F8[2];
        } else if (sVar1 == 1) {
            pJVar7 = i_this->m02F8[0];
            i_this->m0304->entry(pJVar7->getModelData());
        } else {
            pJVar7 = i_this->m02F8[1];
            i_this->m0308->entry(pJVar7->getModelData());
        }
        g_env_light.setLightTevColorType(pJVar7, &actor->tevStr);
        mDoExt_modelUpdateDL(pJVar7);
        if (l_HIO.m00C != 0) {
            i_this->m02E4.mpModel = pJVar7;
            dComIfGd_getOpaListSky()->entryImm(&i_this->m02E4, 0);
        }
    }
    GXColor local_28 = {0xd2, 0x32, 0x5a, 0};
    i_this->m2E88.update(0x3c, local_28, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->m2E88);
    return TRUE;
}

/* 000012D0-00001754       .text daBgn3_Draw__FP10bgn3_class */
static BOOL daBgn3_Draw(bgn3_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar1;
    short sVar2;
    s16 uVar3;
    s16 uVar4;
    s16 uVar5;
    J3DModel* pJVar6;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    if (i_this->m10060 > 0.0f) {
        actor->tevStr.mFogColor.b = 0;
        actor->tevStr.mFogColor.g = 0;
        actor->tevStr.mFogColor.r = 0;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m10060 * -50000.0f;
    }
    if (i_this->m0FD9C != 0) {
        uVar3 = actor->tevStr.mFogColor.r + i_this->m0FD96;
        if (0xff < uVar3) {
            uVar3 = 0xff;
        }
        sVar2 = actor->tevStr.mFogColor.g;
        uVar4 = sVar2 + i_this->m0FD96;
        if (0xff < uVar4) {
            uVar4 = 0xff;
        }
        uVar5 = sVar2 + (i_this->m0FD96 / 2);
        if (0xff < uVar5) {
            uVar5 = 0xff;
        }
        if (i_this->m0FD9C > 0x28) {
            cLib_addCalcAngleS2(&i_this->m0FD96, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m0FD98, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m0FD96, 0, 1, 7);
            cLib_addCalc0(&i_this->m0FD98, 1.0f, 1250.0f);
        }
        actor->tevStr.mFogColor.r = uVar3 & 0xff;
        actor->tevStr.mFogColor.g = uVar4 & 0xff;
        actor->tevStr.mFogColor.b = uVar5 & 0xff;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m0FD98;
    }
    pJVar6 = i_this->m002CC;
    g_env_light.setLightTevColorType(pJVar6, &actor->tevStr);
    mDoExt_modelUpdateDL(pJVar6);
    if (l_HIO.m00C != 0) {
        i_this->m002D0.mpModel = pJVar6;
        dComIfGd_getOpaListSky()->entryImm(&i_this->m002D0, 0);
    }
    g_env_light.setLightTevColorType(i_this->m002B4->getModel(), &actor->tevStr);
    i_this->m002B4->entryDL();
    if (l_HIO.m00C != 0) {
        i_this->m002B8.mpModel = i_this->m002B4->getModel();
        dComIfGd_getOpaListSky()->entryImm(&i_this->m002B8, 0);
    }
    s32 i = 0;
    part_s3* ppVar8 = &i_this->mParts[i];
    for (i = 0; i < 9; i++, ppVar8++) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &ppVar8->m00D4, &ppVar8->m0018);
        if (i_this->m10060 > 0.0f) {
            ppVar8->m0018.mFogColor.b = 0;
            ppVar8->m0018.mFogColor.g = 0;
            ppVar8->m0018.mFogColor.r = 0;
            ppVar8->m0018.mFogStartZ = ppVar8->m0018.mFogStartZ + i_this->m10060 * -50000.0f;
        }
        if (ppVar8->m00D0 != 0) {
            uVar3 = ppVar8->m0018.mFogColor.r + ppVar8->m00C8;
            if (0xff < uVar3) {
                uVar3 = 0xff;
            }
            sVar2 = ppVar8->m0018.mFogColor.g;
            uVar4 = sVar2 + ppVar8->m00C8;
            if (0xff < uVar4) {
                uVar4 = 0xff;
            }
            uVar5 = sVar2 + (ppVar8->m00C8 / 2);
            if (0xff < uVar5) {
                uVar5 = 0xff;
            }
            if (ppVar8->m00D0 > 0x28) {
                cLib_addCalcAngleS2(&ppVar8->m00C8, 0x118, 1, 0x1e);
                cLib_addCalc2(&ppVar8->m00CC, -50000.0f, 1.0f, 5000.0f);
            } else {
                cLib_addCalcAngleS2(&ppVar8->m00C8, 0, 1, 7);
                cLib_addCalc0(&ppVar8->m00CC, 1.0f, 1250.0f);
            }
            ppVar8->m0018.mFogColor.r = uVar3 & 0xff;
            ppVar8->m0018.mFogColor.g = uVar4 & 0xff;
            ppVar8->m0018.mFogColor.b = uVar5 & 0xff;
            ppVar8->m0018.mFogStartZ = ppVar8->m0018.mFogStartZ + ppVar8->m00CC;
        }
        pJVar6 = i_this->mParts[i].m0000;
        if (pJVar6 != NULL) {
            g_env_light.setLightTevColorType(pJVar6, &ppVar8->m0018);
            if (i == 8) {
                sVar1 = actor->health;
                if (sVar1 == 1) {
                    i_this->m017C0->entry(i_this->mParts[i].m0000->getModelData());
                } else if (sVar1 == 2) {
                    i_this->m017C4->entry(i_this->mParts[i].m0000->getModelData());
                }
            }
            mDoExt_modelUpdateDL(i_this->mParts[i].m0000);
            if (l_HIO.m00C != 0) {
                i_this->mParts[i].m0004.mpModel = i_this->mParts[i].m0000;
                dComIfGd_getOpaListSky()->entryImm(&i_this->mParts[i].m0004, 0);
            }
        }
    }
    GXColor local_48 = {0xd2, 0x32, 0x5a, 0};
    i_this->m10064.update(0x3c, local_48, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->m10064);
    return TRUE;
}

/* 00001754-00001898       .text room_disp__FP9bgn_class */
void room_disp(bgn_class* i_this) {
    f32 x;

    g_env_light.settingTevStruct(TEV_TYPE_BG1, &w_pos, &i_this->mCB74);
    MtxTrans(0.0f, REG0_F(0xc), 0.0f, false);
    x = REG0_F(0xd) * 0.01f + 1.0f;
    MtxScale(x, x, x, true);
    i_this->mCB5C->setBaseTRMtx(*calc_mtx);
    g_env_light.setLightTevColorType(i_this->mCB5C, &i_this->mCB74);
    if (i_this->mCC38 == 0) {
        mDoExt_modelUpdateDL(i_this->mCB5C);
        i_this->mCC38++;
    } else {
        i_this->mCB5C->calcMaterial();
        i_this->mCB5C->diff();
    }
    i_this->mCB60.mpModel = i_this->mCB5C;
    dComIfGd_getOpaListSky()->entryImm(&i_this->mCB60, 0);
}

/* 00001898-0000192C       .text ten_a_d_sub__FPvPv */
void* ten_a_d_sub(void* param_1, void* param_2) {
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_Obj_Vteng)) {
        if ((actor->model != NULL) && (bgn != NULL)) {
            bgn->mCC24.mpModel = actor->model;
            dComIfGd_getOpaListSky()->entryImm(&bgn->mCC24, 0);
        }
        return param_1;
    } else {
        return NULL;
    }
}

/* 0000192C-00001998       .text ki_a_d_sub__FPvPv */
void* ki_a_d_sub(void* param_1, void* param_2) {
    ki_class* keese = (ki_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        if (keese->actor.model != NULL) {
            keese->m2B8.mpModel = keese->actor.model;
            dComIfGd_getOpaListSky()->entryImm(&keese->m2B8, 0);
        }
    }
    return NULL;
}

/* 00001998-000019F4       .text obj_disp__FP9bgn_class */
void obj_disp(bgn_class* i_this) {
    if (REG0_S(8) == 0) {
        fpcM_Search(ten_a_d_sub, i_this);
    }
    fpcM_Search(ki_a_d_sub, i_this);
}

/* 000019F4-00001A40       .text bgn2_s_sub__FPvPv */
void* bgn2_s_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN2)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00001A40-00001A8C       .text bgn3_s_sub__FPvPv */
void* bgn3_s_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN3)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00001A8C-00001C40       .text daBgn_Draw__FP9bgn_class */
static BOOL daBgn_Draw(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->mCA60 > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->mCA60);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->mCA60 == 1) {
        i_this->mCA60 = 0;
        mDoGph_gInf_c::offBlure();
    }
    water0_disp(i_this);
    if (l_HIO.m00D != 0) {
        room_disp(i_this);
    }
    if (l_HIO.m00C != 0) {
        obj_disp(i_this);
    }
    if (i_this->m02B4 != 0xff) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
        bgn2 = (bgn2_class*)fpcM_Search(bgn2_s_sub, i_this);
        bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
        if (i_this->m02B5 == 0) {
            daBgn_DrawS(i_this);
        } else if (i_this->m02B5 == 1) {
            if (bgn2 != NULL) {
                daBgn2_Draw(bgn2);
            }
        } else if ((i_this->m02B5 == 2) && (bgn3 != NULL)) {
            daBgn3_Draw(bgn3);
        }
        if (i_this->mC720 != 0) {
            GXColor local_18 = {0xFF, 0xFF, 0xFF, 0};
            i_this->mC414.update(0x3c, local_18, &actor->tevStr);
            dComIfGd_set3DlineMat(&i_this->mC414);
        }
    }
    water1_disp(i_this);
    return TRUE;
}

/* 00001C40-00001C8C       .text ki_del_sub__FPvPv */
void* ki_del_sub(void* param_1, void* param_2) {
    ki_class* keese = (ki_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        fopAcM_delete(&keese->actor);
    }
    return NULL;
}

/* 00001C8C-00001CD8       .text ks_del_sub__FPvPv */
void* ks_del_sub(void* param_1, void* param_2) {
    ks_class* morth = (ks_class*)param_1;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KS)) {
        fopAcM_delete(morth);
    }
    return NULL;
}

/* 00001CD8-00001D30       .text ki_c_sub__FPvPv */
void* ki_c_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        ki_all_count++;
    }
    return NULL;
}

/* 00001D30-00001D74       .text ki_check__FP9bgn_class */
s32 ki_check(bgn_class* i_this) {
    ki_all_count = 0;
    fpcM_Search(ki_c_sub, i_this);
    return ki_all_count;
}

/* 00001D74-00001FA0       .text move_se_set__FP9bgn_class */
void move_se_set(bgn_class* i_this) {
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
s32 gr_check(bgn_class* i_this, cXyz* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_ac;
    cXyz local_b8;
    dBgS_LinChk local_a0;

    local_ac = *param_2;
    local_ac.y += 200.0f;
    local_b8 = *param_2;
    local_b8.y -= 1000.0f;
    local_a0.Set(&local_ac, &local_b8, actor);
    if (dComIfG_Bgsp()->LineCross(&local_a0)) {
        *param_2 = local_a0.mLin.GetEnd();
        param_2->y = REG0_F(8) + -2.0f;
        if (dComIfG_Bgsp()->GetAttributeCode(local_a0) == 0x13) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00002768-0000290C       .text s_b_sub__FPvPv */
void* s_b_sub(void* param_1, void* param_2) {
    /* Nonmatching */
    bgn_class* bgn = (bgn_class*)param_1;
    daBomb_c* bomb = (daBomb_c*)param_2;
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BOMB) && bomb->get_explode_instant()) {
        cXyz local_18 = bomb->current.pos;
        if (!gr_check(bgn, &local_18)) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8414, &local_18);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8415, &local_18);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8416, &local_18);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_840E, &local_18, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8408, &local_18, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
    }
    return NULL;
}

/* 0000290C-00002938       .text bomb_splash_check__FP9bgn_class */
void bomb_splash_check(bgn_class* i_this) {
    fpcM_Search(ki_a_d_sub, i_this);
}

/* 00002938-00002CD4       .text attack_eff_set__FP9bgn_class4cXyzi */
void attack_eff_set(bgn_class* i_this, cXyz param_2, int param_3) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar7;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (!gr_check(i_this, &param_2)) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_8414, &param_2);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8415, &param_2);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8416, &param_2);
        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_840E, &param_2, 0xFF, g_whiteColor, g_whiteColor, 0);
        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8408, &param_2, 0xFF, g_whiteColor, g_whiteColor, 0);
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
        i_this->mCC3C[param_3].end();
        pJVar7 = dComIfGp_particle_setToon(dPa_name::ID_SCENE_A418, &param_2, NULL, NULL, 0xa0, &i_this->mCC3C[param_3], fopAcM_GetRoomNo(actor));
        if (pJVar7 != NULL) {
            pJVar7->setGlobalPrmColor(bg_tevstr.mColorC0.r, bg_tevstr.mColorC0.g, bg_tevstr.mColorC0.b);
            pJVar7->setGlobalEnvColor(bg_tevstr.mColorK0.r, bg_tevstr.mColorK0.g, bg_tevstr.mColorK0.b);
        }
        dComIfGp_particle_set(dPa_name::ID_SCENE_8417, &param_2);
    }
}

/* 00002CD4-00003144       .text part_control_0__FP9bgn_classiP6part_sP6move_sf */
void part_control_0(bgn_class* i_this, int param_2, part_s* param_3, move_s* param_4, f32 param_5) {
    /* Nonmatching */
    f32 fVar1;
    int iVar2;
    f32 fVar3;
    int iVar5;
    int iVar7;
    f32 dVar8;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    cXyz local_d0;
    cXyz cStack_dc;
    cXyz local_e8;

    local_e8.setall(0.0f);
    if ((param_3 == i_this->m0314) && (i_this->mAAA8[0].m2D0 != 0 || (i_this->mAAA8[1].m2D0 != 0))) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_d0.x = 0.0f;
        local_d0.y = 0.0f;
        local_d0.z = REG0_F(6) + 200.0f;
        MtxPosition(&local_d0, &local_e8);
    } else if ((param_3 == i_this->m0C04) && (i_this->mAAA8[3].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_d0.x = REG0_F(8) + 20.0f;
        local_d0.y = 0.0f;
        local_d0.z = 0.0f;
        MtxPosition(&local_d0, &local_e8);
    } else if ((param_3 == i_this->m3AF0) && (i_this->mAAA8[4].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_d0.x = -(REG0_F(8) + 20.0f);
        local_d0.y = 0.0f;
        local_d0.z = 0.0f;
        MtxPosition(&local_d0, &local_e8);
    }
    dVar11 = ((i_this->mC7BC - 50.0f) + REG0_F(6));
    part_s* ppVar6 = &param_3[1];
    if (param_4->m2D0 == 0) {
        dVar10 = l_HIO.m16C;
    } else if (i_this->mCA62 != 0) {
        dVar10 = -40.0f;
    } else {
        dVar10 = l_HIO.m170;
    }
    for (iVar7 = 1; iVar7 < param_2 + 1; iVar7++, ppVar6++) {
        fVar1 = (ppVar6->m0D4.y + dVar10);
        fVar3 = (dVar11 * ppVar6[-1].m0F4);
        if (fVar1 <= fVar3) {
            fVar1 = fVar3;
        }
        dVar12 = (local_e8.x + (ppVar6->m0D4.x - ppVar6[-1].m0D4.x));
        fVar1 = fVar1 - ppVar6[-1].m0D4.y;
        dVar9 = fVar1;
        fVar3 = local_e8.z + (ppVar6->m0D4.z - ppVar6[-1].m0D4.z);
        dVar8 = fVar3;
        iVar5 = (int)(param_4->m2F4 * cM_ssin(param_4->m2FA + iVar7 * (REG0_S(3) + 8000)));
        iVar2 = (int)(param_4->m2F4 * cM_scos(param_4->m2FC + iVar7 * (REG0_S(4) + 9000)));
        ppVar6[-1].m0E0.x = iVar5 - cM_atan2s(fVar1, fVar3);
        dVar8 = std::sqrtf((dVar9 * dVar9) + (dVar8 * dVar8));
        ppVar6[-1].m0E0.y = iVar2 + cM_atan2s(dVar12, dVar8);
        cMtx_XrotS(*calc_mtx, (int)ppVar6[-1].m0E0.x);
        cMtx_YrotM(*calc_mtx, ppVar6[-1].m0E0.y);
        local_d0.x = i_this->mCC80 * (param_5 * ppVar6[-1].m0F4);
        local_d0.y = 0.0f;
        local_d0.z = 0.0f;
        MtxPosition(&local_d0, &cStack_dc);
        ppVar6->m0D4 = ppVar6[-1].m0D4 + cStack_dc;
    }
}

/* 00003144-00003624       .text part_control_0Z__FP9bgn_classiP6part_sP6move_sf */
void part_control_0Z(bgn_class* i_this, int param_2, part_s* param_3, move_s* param_4, f32 param_5) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    int iVar2;
    int iVar4;
    int iVar7;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    f32 fVar16;
    cXyz local_f8;
    cXyz cStack_104;
    cXyz local_11c;
    cXyz local_128;
    cXyz local_134;

    cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
    if (param_3 == i_this->m0C04) {
        local_f8.x = REG0_F(8) + 20.0f;
        local_f8.y = 0.0f;
        local_f8.z = 0.0f;
        MtxPosition(&local_f8, &local_128);
    } else if (param_3 == i_this->m3AF0) {
        local_f8.x = -(REG0_F(8) + 20.0f);
        local_f8.y = 0.0f;
        local_f8.z = 0.0f;
        MtxPosition(&local_f8, &local_128);
    } else if (param_3 == i_this->m7BBC) {
        local_f8.x = 0.0f;
        local_f8.y = 0.0f;
        local_f8.z = REG0_F(6) + -5.0f;
        MtxPosition(&local_f8, &local_128);
    }
    dVar10 = i_this->mC7BC;
    dVar9 = l_HIO.m170;
    iVar7 = 1;
    part_s* ppVar6 = &param_3[iVar7];
    for (; iVar7 < param_2 + 1; iVar7++, ppVar6++) {
        dVar11 = (ppVar6->m0D4.y + dVar9);
        if (dVar11 <= dVar10) {
            dVar11 = dVar10;
            if ((iVar7 == param_2) && ((i_this->mC746 & 7U) == 0)) {
                local_134 = ppVar6->m0D4;
                if (!(gr_check(i_this, &local_134))) {
                    dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8443, &local_134, 0xff, g_whiteColor, g_whiteColor, 0);
                    if (i_this->m0304 == 0) {
                        fVar16 = cM_rndF(20.0f);
                        i_this->m0304 = (s16)(int)(fVar16 + 20.0f);
                        i_this->m0308 = local_134;
                        mDoAud_seStart(JA_SE_CM_BGN_BODY_RIPPLE, &i_this->m0308, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    }
                }
            }
        }
        f32 temp = (param_2 - iVar7);
        local_11c.x = local_128.x * temp;
        local_11c.z = local_128.z * temp;
        fVar16 = local_11c.x + (ppVar6->m0D4.x - ppVar6[-1].m0D4.x);
        dVar13 = fVar16;
        dVar12 = (dVar11 - ppVar6[-1].m0D4.y);
        fVar1 = local_11c.z + (ppVar6->m0D4.z - ppVar6[-1].m0D4.z);
        dVar11 = fVar1;
        iVar2 = (int)(param_4->m2F4 * cM_ssin(param_4->m2FA + iVar7 * (REG0_S(3) + 8000)));
        iVar4 = (int)(param_4->m2F4 * cM_scos(param_4->m2FC + iVar7 * (REG0_S(4) + 9000)));
        ppVar6[-1].m0E0.y = iVar4 + cM_atan2s(fVar16, fVar1);
        dVar11 = std::sqrtf((dVar13 * dVar13) + (dVar11 * dVar11));
        ppVar6[-1].m0E0.x = iVar2 - cM_atan2s(dVar12, dVar11);
        cMtx_YrotS(*calc_mtx, (int)ppVar6[-1].m0E0.y);
        cMtx_XrotM(*calc_mtx, ppVar6[-1].m0E0.x);
        f32 temp2 = i_this->mCC80 * (param_5 * ppVar6[-1].m0F4);
        local_f8.x = 0.0f;
        local_f8.y = 0.0f;
        local_f8.z = temp2;
        MtxPosition(&local_f8, &cStack_104);
        ppVar6->m0D4 = ppVar6[-1].m0D4 + cStack_104;
    }
}

/* 00003624-0000385C       .text part_control_2__FP9bgn_classiP6part_sf */
void part_control_2(bgn_class* i_this, int param_2, part_s* param_3, f32 param_4) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;
    int iVar3;
    s16 iVar4;
    int iVar5;
    part_s* ppVar6;
    f32 dVar7;
    f32 dVar8;
    f32 dVar9;
    cXyz local_84;
    cXyz cStack_90;
    cXyz local_9c;

    local_9c = param_3->m0D4;
    iVar3 = param_2 + -1;
    ppVar6 = &param_3[iVar3];
    s32 var_r29 = iVar3;
    for (; var_r29 >= 0; var_r29 = var_r29 + -1, ppVar6--) {
        dVar9 = (ppVar6->m0D4.x - ppVar6[1].m0D4.x);
        fVar1 = ppVar6->m0D4.y - ppVar6[1].m0D4.y;
        dVar8 = fVar1;
        fVar2 = ppVar6->m0D4.z - ppVar6[1].m0D4.z;
        dVar7 = fVar2;
        iVar4 = -cM_atan2s(dVar8, fVar2);
        dVar7 = std::sqrtf((dVar8 * dVar8) + (dVar7 * dVar7));
        iVar5 = cM_atan2s(dVar9, dVar7);
        cMtx_XrotS(*calc_mtx, iVar4);
        cMtx_YrotM(*calc_mtx, iVar5);
        f32 temp = (param_4 * ppVar6->m0F4);
        local_84.x = 0.0f;
        local_84.y = 0.0f;
        local_84.z = temp;
        MtxPosition(&local_84, &cStack_90);
        ppVar6->m0D4 = ppVar6[1].m0D4 + cStack_90;
    }
    part_s* ppVar6_2 = &ppVar6[1];
    local_84 = ppVar6_2[1].m0D4 - local_9c;
    for (iVar3 = 0; iVar3 < param_2; iVar3++, ppVar6_2++) {
        ppVar6_2->m0D4 -= local_84;
    }
}

/* 0000385C-00003FD0       .text part_mtx_set__FP9bgn_classiP6part_sii */
void part_mtx_set(bgn_class* i_this, int param_2, part_s* param_3, int param_4, int param_5) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar1;
    f32 fVar4;
    f32 fVar5;
    s32 uVar7;
    short sVar8;
    int iVar9;
    f32 dVar10;
    f32 dVar11;
    cXyz local_8c;
    cXyz local_98;

    local_8c.z = 0.0f;
    local_8c.y = 0.0f;
    local_8c.x = 0.0f;
    dVar11 = 120.0f;
    for (iVar9 = 0; iVar9 < param_2; iVar9++, param_3++) {
        if ((int)i_this->m0302 == (int)(char)param_3->m0D2) {
            param_3->m0D0 = 0x32;
            param_3->m238 = 100;
        }
        if (param_3->m0D0 != 0) {
            param_3->m0D0--;
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
        if ((iVar9 != param_2 + -1) && (param_4 == 3 || (param_4 == 4))) {
            fVar5 = (REG0_F(0) + 0.005f) * (i_this->mC324[param_4 + -3] - l_HIO.m124) + 1.0f;
        } else {
            fVar5 = 1.0f;
        }
        MtxScale(fVar4, fVar4, (dVar10 * fVar5), true);
        if (param_4 == 0) {
            uVar7 = (s16)(i_this->mAAA8[0].m300 + i_this->mAAA8[1].m300);
            fVar4 = (s32)(uVar7) * (REG0_F(0xe) + 170.0f);
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
        if ((param_4 == 7) && (iVar9 == param_2 + -1)) {
            if (actor->health == 3) {
                param_3->m000 = i_this->m02E8;
            } else if (actor->health == 2) {
                param_3->m000 = i_this->m02E4;
            } else if (actor->health == 1) {
                param_3->m000 = i_this->m02E0;
            } else {
                param_3->m000 = NULL;
            }
        }
        if (param_3->m000 != NULL) {
            param_3->m000->setBaseTRMtx(*calc_mtx);
        }
        if (param_4 == 0) {
            if (((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) || ((int)i_this->m02B8->getFrame() != 0x18)) {
                i_this->m02B8->play(NULL, 0, 0);
            }
            i_this->m02B8->calc();
        }
        MtxPosition(&zero, &local_98);
        param_3->m224 = local_98;
        if ((param_4 == 7) && (iVar9 == param_2 + -1)) {
            i_this->mC928.SetR(REG0_F(4) + 150.0f);
            i_this->mC928.SetC(local_98);
            i_this->mCA54 = local_98;
            dComIfG_Ccsp()->Set(&i_this->mC928);
        }
        param_3->m0F8.SetR(dVar10 * (dVar11 + REG0_F(0)));
        param_3->m0F8.SetC(local_98);
        dComIfG_Ccsp()->Set(&param_3->m0F8);
        if (iVar9 == param_5) {
            if (param_4 == 0) {
                local_8c.set(90.0f, 180.0f, -40.0f);
                MtxPosition(&local_8c, i_this->mC33C);
                local_8c.x *= -1.0f;
                MtxPosition(&local_8c, i_this->mC33C + 1);
            } else {
                local_8c.y = 0.0f;
                local_8c.x = 0.0f;
                local_8c.z = l_HIO.m168;
                MtxPosition(&local_8c, i_this->mC33C + param_4);
            }
            local_8c.z = 0.0f;
            local_8c.x = 0.0f;
        }
        if (param_3->m238 != 0) {
            param_3->m238--;
            fVar4 = (REG8_F(0) + 0.04f) * (param_3->m0F4 * param_3->m238);
            dVar10 = fVar4;
            if (param_3->m230 == NULL) {
                param_3->m230 = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &param_3->m0D4);
            } else {
                param_3->m230->setGlobalTranslation(param_3->m0D4.x, param_3->m0D4.y, param_3->m0D4.z);
                JGeometry::TVec3<f32> scale(fVar4, fVar4, fVar4);
                param_3->m230->setGlobalScale(scale);
            }
            if (param_3->m234 == NULL) {
                local_8c.setall(dVar10);
                param_3->m234 = dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &param_3->m0D4);
            } else {
                param_3->m234->setGlobalTranslation(param_3->m0D4.x, param_3->m0D4.y, param_3->m0D4.z);
                JGeometry::TVec3<f32> scale(dVar10, dVar10, dVar10);
                param_3->m234->setGlobalScale(scale);
            }
        } else {
            if (param_3->m230 != NULL) {
                param_3->m230->becomeInvalidEmitter();
                param_3->m230 = NULL;
            }
            if (param_3->m234 != NULL) {
                param_3->m234->becomeInvalidEmitter();
                param_3->m234 = NULL;
            }
        }
    }
}

/* 00003FD0-000044DC       .text damage_check__FP9bgn_class */
void damage_check(bgn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar2;
    char cVar5;
    f32 dVar8;
    CcAtInfo local_48;

    if (i_this->mC7B6 == 0) {
        local_48.pParticlePos = NULL;
        if (i_this->mC928.ChkTgHit()) {
            local_48.mpObj = i_this->mC928.GetTgHitObj();
            i_this->m0302 = 1;
            i_this->mC7B6 = 100;
            i_this->mC748 = 5;
            i_this->mC74A = 0;
            i_this->mC779 = 0;
            i_this->mC778 = 0;
            if (actor->health != 0) {
                actor->health--;
                mDoAud_seStart(JA_SE_LK_ARROW_HIT, NULL, 0x35, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                dVar8 = (REG0_F(5) + 2.0f);
                if (actor->health == 0) {
                    mDoAud_bgmStop(30);
                    i_this->mC748 = 6;
                    i_this->mC74A = 0;
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_SCENE_8457, &i_this->mCA54);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_SCENE_8458, &i_this->mCA54);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_2, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_LK_LAST_HIT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_CM_BGN_M_BRK_ORB, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                } else {
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_SCENE_8459, &i_this->mCA54);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
        cVar5 = 0;
        if (i_this->mC7FC.ChkTgHit()) {
            local_48.mpObj = i_this->mC7FC.GetTgHitObj();
            cVar5 = 1;
        }
        if (i_this->m0314[0].m0F8.ChkTgHit()) {
            local_48.mpObj = i_this->m0314[0].m0F8.GetTgHitObj();
            cVar5 = 2;
        }
        dCcD_Sph* sph = &i_this->m078C[0].m0F8;
        if (sph->ChkTgHit()) {
            local_48.mpObj = sph->GetTgHitObj();
            cVar5 = 3;
        }
        for (s32 i = 0; i < 0x14; i++) {
            if (i_this->m0C04[i].m0F8.ChkTgHit()) {
                local_48.mpObj = i_this->m0C04[i].m0F8.GetTgHitObj();
                cVar5 = 4;
            }
            if (i_this->m3AF0[i].m0F8.ChkTgHit()) {
                local_48.mpObj = i_this->m3AF0[i].m0F8.GetTgHitObj();
                cVar5 = 5;
            }
        }
        for (s32 i = 0; i < 3; i++) {
            if (i_this->m69DC[i].m0F8.ChkTgHit()) {
                local_48.mpObj = i_this->m69DC[i].m0F8.GetTgHitObj();
                cVar5 = 6;
            }
            if (i_this->m72CC[i].m0F8.ChkTgHit()) {
                local_48.mpObj = i_this->m72CC[i].m0F8.GetTgHitObj();
                cVar5 = 7;
            }
        }
        for (s32 i = 0; i < 0x14; i++) {
            if (i_this->m7BBC[i].m0F8.ChkTgHit()) {
                local_48.mpObj = i_this->m7BBC[i].m0F8.GetTgHitObj();
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
void size_set(bgn_class* i_this) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;

    i_this->m0314[0].m0F4 = l_HIO.m0F8;
    i_this->m078C[0].m0F4 = l_HIO.m100;
    i_this->m078C[1].m0F4 = l_HIO.m100;
    fVar2 = (1.0f / (s32)(BGN_HAND_MAX - 2U)) * (l_HIO.m104 - l_HIO.m108);
    i_this->m0C04[0].m0F4 = l_HIO.m104 - fVar2;
    i_this->m3AF0[0].m0F4 = l_HIO.m104 - fVar2;
    for (s32 i = 1; i < BGN_HAND_MAX; i++) {
        i_this->m0C04[i].m0F4 = l_HIO.m104 - fVar2 * (s32)(i - 1U);
        i_this->m3AF0[i].m0F4 = l_HIO.m104 - fVar2 * (s32)(i - 1U);
    }
    i_this->m0C04[BGN_HAND_MAX].m0F4 = l_HIO.m108;
    i_this->m3AF0[BGN_HAND_MAX].m0F4 = l_HIO.m108;
    fVar2 =  (0.5f * (l_HIO.m104 - l_HIO.m108)) + l_HIO.m108;
    for (s32 i = 0; i < BGN_HAND_MAX; i++) {
        fVar1 = i_this->m0C04[i].m0F4;
        i_this->m0C04[i].m0F4 = fVar1 + i_this->mC32C[0] * (fVar2 - fVar1) * 2.0f;
        fVar1 = i_this->m3AF0[i].m0F4;
        i_this->m3AF0[i].m0F4 = fVar1 + i_this->mC32C[1] * (fVar2 - fVar1) * 2.0f;
    }
    fVar2 = 0.5f * (l_HIO.m10C - l_HIO.m110);
    for (s32 i = 0; i < 3; i++) {
        i_this->m69DC[i].m0F4 = l_HIO.m10C - fVar2 * (s32)(i);
        i_this->m72CC[i].m0F4 = l_HIO.m10C - fVar2 * (s32)(i);
    }
    i_this->m69DC[3].m0F4 = l_HIO.m110;
    i_this->m72CC[3].m0F4 = l_HIO.m110;
    f32 temp = (1.0f / (s32)(BGN_TAIL_MAX - 1));
    fVar2 *= l_HIO.m114 - l_HIO.m118;
    for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
        i_this->m7BBC[i].m0F4 = l_HIO.m114 - temp * (fVar2 * (f32)(i));
    }
    i_this->m72CC[BGN_TAIL_MAX + 3].m0F4 = l_HIO.m114 * 0.7f;
    i_this->m7BBC[BGN_TAIL_MAX].m0F4 = l_HIO.m114 * 0.7f;
}

/* 000047D0-000056DC       .text shape_calc__FP9bgn_class */
void shape_calc(bgn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar3;
    short sVar5;
    short sVar8;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
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
        i_this->m0300 = 0x32;
        i_this->m02DC = 100;
    }
    MtxTrans(local_b0.x, local_b0.y, local_b0.z, false);
    sVar8 = 0;
    sVar5 = 0;
    if (i_this->mC770 != 0) {
        i_this->mC770--;
        fVar3 = (i_this->mC770) * (REG0_F(0xe) + 300.0f);
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
    i_this->m02BC->setBaseTRMtx(*calc_mtx);
    i_this->mC7FC.SetR(dVar12 * (REG0_F(1) + 120.0f));
    i_this->mC7FC.SetC(i_this->mC308);
    dComIfG_Ccsp()->Set(&i_this->mC7FC);
    if (i_this->m02DC != 0) {
        i_this->m02DC--;
        fVar3 = (REG8_F(1) + 0.03f) * (dVar12 * (i_this->m02DC));
        dVar9 = fVar3;
        if (i_this->m02D4 == NULL) {
            i_this->m02D4 = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &i_this->mC308);
        } else {
            i_this->m02D4->setGlobalTranslation(i_this->mC308.x, i_this->mC308.y, i_this->mC308.z);
            JGeometry::TVec3<f32> scale(fVar3, fVar3, fVar3);
            i_this->m02D4->setGlobalScale(scale);
        }
        if (i_this->m02D8 == NULL) {
            local_8c.setall(dVar12);
            i_this->m02D8 = dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &i_this->mC308);
            ;
        } else {
            i_this->m02D8->setGlobalTranslation(i_this->mC308.x, i_this->mC308.y, i_this->mC308.z);
            JGeometry::TVec3<f32> scale(dVar9, dVar9, dVar9);
            i_this->m02D8->setGlobalScale(scale);
        }
    } else {
        if (i_this->m02D4 != NULL) {
            i_this->m02D4->becomeInvalidEmitter();
            i_this->m02D4 = NULL;
        }
        if (i_this->m02D8 != NULL) {
            i_this->m02D8->becomeInvalidEmitter();
            i_this->m02D8 = NULL;
        }
    }
    MtxPull();
    dVar13 = (l_HIO.m11C * l_HIO.m0F4);
    dVar11 = (l_HIO.m120 * l_HIO.m0F4);
    dVar10 = (i_this->mC324[0] * l_HIO.m0F4);
    dVar9 = (i_this->mC324[1] * l_HIO.m0F4);
    dVar12 = (l_HIO.m128 * l_HIO.m0F4);
    MtxPush();
    local_8c = l_HIO.m12C;
    MtxPosition(&local_8c, &i_this->m0314[0].m0D4);
    part_control_0(i_this, 1, i_this->m0314, i_this->mAAA8, dVar13);
    if ((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_8c = l_HIO.m054;
        local_8c += i_this->mAAA8[0].m2D4;
        MtxPosition(&local_8c, &i_this->m0314[1].m0D4);
        i_this->m0314[1].m0D4 += i_this->mC308;
        part_control_2(i_this, 1, i_this->m0314, dVar13);
    }
    part_mtx_set(i_this, 1, i_this->m0314, 0, 0);
    actor->eyePos = i_this->m0314[0].m0D4;
    actor->attention_info.position = actor->eyePos;
    actor->attention_info.position.y += 50.0f;
    MtxPull();
    MtxPush();
    local_8c.set(l_HIO.m144.x, l_HIO.m144.y + 20.0f, l_HIO.m144.z);
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->m078C[0].m0D4);
    part_control_0(i_this, 1, i_this->m078C, i_this->mAAA8 + 2, dVar13);
    if (i_this->mAAA8[2].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_8c = l_HIO.m060;
        local_8c += i_this->mAAA8[2].m2D4;
        MtxPosition(&local_8c, &i_this->m078C[1].m0D4);
        i_this->m078C[1].m0D4 += i_this->mC308;
        part_control_2(i_this, 1, i_this->m078C, dVar13);
    }
    part_mtx_set(i_this, 1, i_this->m078C, 2, 0);
    MtxPull();
    MtxPush();
    local_8c = l_HIO.m138;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->m0C04[0].m0D4);
    if (i_this->mAAA8[3].m2D0 == 0) {
        part_control_0(i_this, BGN_HAND_MAX, i_this->m0C04, i_this->mAAA8 + 3, dVar10);
        if (i_this->mC778 != 0) {
            i_this->m0C04[BGN_HAND_MAX].m0D4 = i_this->mC77C;
        } else {
            cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
            local_8c = l_HIO.m06C;
            local_8c += i_this->mAAA8[3].m2D4;
            MtxPosition(&local_8c, &i_this->m0C04[BGN_HAND_MAX].m0D4);
            i_this->m0C04[BGN_HAND_MAX].m0D4 += i_this->mC308;
        }
        part_control_2(i_this, BGN_HAND_MAX, i_this->m0C04, dVar10);
    } else {
        part_control_0(i_this, BGN_HAND_MAX, i_this->m0C04, i_this->mAAA8 + 3, dVar10);
    }
    part_mtx_set(i_this, BGN_HAND_MAX, i_this->m0C04, 3, BGN_HAND_MAX + -1);
    MtxPull();
    local_8c.set(-l_HIO.m138.x, l_HIO.m138.y, l_HIO.m138.z);
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &i_this->m3AF0[0].m0D4);
    if (i_this->mAAA8[4].m2D0 == 0) {
        part_control_0(i_this, BGN_HAND_MAX, i_this->m3AF0, i_this->mAAA8 + 4, dVar9);
        if (i_this->mC779 != 0) {
            i_this->m3AF0[BGN_HAND_MAX].m0D4 = i_this->mC788;
        } else {
            cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
            local_8c = l_HIO.m078;
            local_8c += i_this->mAAA8[4].m2D4;
            MtxPosition(&local_8c, &i_this->m3AF0[BGN_HAND_MAX].m0D4);
            i_this->m3AF0[BGN_HAND_MAX].m0D4 += i_this->mC308;
        }
        part_control_2(i_this, BGN_HAND_MAX, i_this->m3AF0, dVar9);
    } else {
        part_control_0(i_this, BGN_HAND_MAX, i_this->m3AF0, i_this->mAAA8 + 4, dVar9);
    }
    part_mtx_set(i_this, BGN_HAND_MAX, i_this->m3AF0, 4, BGN_HAND_MAX + -1);
    cMtx_XrotS(*calc_mtx, (int)i_this->m078C[0].m0E0.x);
    cMtx_YrotM(*calc_mtx, i_this->m078C[0].m0E0.y);
    cMtx_ZrotM(*calc_mtx, -i_this->m078C[0].m0E0.z);
    fVar3 = l_HIO.m100 * l_HIO.m0F4;
    MtxScale(fVar3, fVar3, fVar3, true);
    MtxPush();
    local_8c = l_HIO.m150;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->m69DC[0].m0D4 = i_this->m078C[0].m0D4 + cStack_98;
    part_control_0(i_this, 3, i_this->m69DC, i_this->mAAA8 + 5, dVar11);
    if (i_this->mAAA8[5].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_8c = l_HIO.m084;
        local_8c += i_this->mAAA8[5].m2D4;
        MtxPosition(&local_8c, &i_this->m69DC[3].m0D4);
        i_this->m69DC[3].m0D4 += i_this->mC308;
        part_control_2(i_this, 3, i_this->m69DC, dVar11);
    }
    part_mtx_set(i_this, 3, i_this->m69DC, 5, 2);
    MtxPull();
    MtxPush();
    local_8c.set(-l_HIO.m150.x, l_HIO.m150.y, l_HIO.m150.z);
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->m72CC[0].m0D4 = i_this->m078C[0].m0D4 + cStack_98;
    part_control_0(i_this, 3, i_this->m72CC, i_this->mAAA8 + 6, dVar11);
    if (i_this->mAAA8[6].m2D0 == 0) {
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_8c = l_HIO.m090;
        local_8c += i_this->mAAA8[6].m2D4;
        MtxPosition(&local_8c, &i_this->m72CC[3].m0D4);
        i_this->m72CC[3].m0D4 += i_this->mC308;
        part_control_2(i_this, 3, i_this->m72CC, dVar11);
    }
    part_mtx_set(i_this, 3, i_this->m72CC, 6, 2);
    MtxPull();
    local_8c = l_HIO.m15C;
    local_8c.x *= i_this->mCC80;
    local_8c.y *= i_this->mCC80;
    local_8c.z *= i_this->mCC80;
    MtxPosition(&local_8c, &cStack_98);
    i_this->m7BBC[0].m0D4 = i_this->m078C[0].m0D4 + cStack_98;
    if (i_this->mAAA8[7].m2D0 == 0) {
        part_control_0(i_this, BGN_TAIL_MAX, i_this->m7BBC, i_this->mAAA8 + 7, dVar12);
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_8c = l_HIO.m09C;
        local_8c += i_this->mAAA8[7].m2D4;
        MtxPosition(&local_8c, &i_this->m7BBC[BGN_TAIL_MAX].m0D4);
        i_this->m7BBC[BGN_TAIL_MAX].m0D4 += i_this->mC308;
        if (i_this->m7BBC[BGN_TAIL_MAX].m0D4.y <= i_this->mC7BC) {
            i_this->m7BBC[BGN_TAIL_MAX].m0D4.y = i_this->mC7BC;
        }
        part_control_2(i_this, BGN_TAIL_MAX, i_this->m7BBC, dVar12);
    } else {
        part_control_0Z(i_this, BGN_TAIL_MAX, i_this->m7BBC, i_this->mAAA8 + 7, (f32)(dVar12));
    }
    part_mtx_set(i_this, BGN_TAIL_MAX, i_this->m7BBC, 7, BGN_TAIL_MAX + -1);
}

/* 000056DC-000058F4       .text dance_A__FP9bgn_class */
void dance_A(bgn_class* i_this) {
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
            if (i_this->mC7B2 == 0) {
                i_this->mC74E++;
                i_this->mC7B2 = l_HIO.m0DA;
            }
            break;
        case 2:
            tmp->m2E0 = dance_pause_2[i];
            if (i_this->mC7B2 == 0) {
                i_this->mC74E = 1;
                i_this->mC7B2 = l_HIO.m0DA;
            }
            break;
        }
    }
    uVar2 = i_this->mC750;
    i_this->mC750 = uVar2 + i_this->mC752;
    if (((0 < uVar2) && (i_this->mC750 <= i_this->mC752)) || (0x8000 < (u16)uVar2 && ((u16)i_this->mC750 <= (u16)(i_this->mC752 + 0x8000U)))) {
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
void dance_B(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar4;

    fopAcM_seStart(actor, JA_SE_CM_BGN_D_DANCE, 0);
    for (s32 i = 0; i < 8; i++) {
        move_s* tmp = &i_this->mAAA8[i];
        switch (i_this->mC74E) {
        case 0:
            tmp->m2E0 = dance_pause_3[i];
            if (i_this->mC7B2 == 0) {
                i_this->mC74E++;
                if (actor->health == 3) {
                    i_this->mC7B2 = l_HIO.m0E8;
                } else if (actor->health == 2) {
                    i_this->mC7B2 = l_HIO.m0EA;
                } else {
                    i_this->mC7B2 = l_HIO.m0EC;
                }
            }
            break;
        case 1:
            tmp->m2E0 = dance_pause_4[i];
            if (i_this->mC7B2 == 0) {
                i_this->mC74E = 0;
                if (actor->health == 3) {
                    i_this->mC7B2 = l_HIO.m0E8;
                } else if (actor->health == 2) {
                    i_this->mC7B2 = l_HIO.m0EA;
                } else {
                    i_this->mC7B2 = l_HIO.m0EC;
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
void ki_set(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (actor->health == 3) {
        i_this->mCC7C = (s8)l_HIO.m174;
        return;
    }
    if (actor->health == 2) {
        i_this->mCC7C = (s8)l_HIO.m176;
        return;
    }
    i_this->mCC7C = (s8)l_HIO.m178;
}

/* 00005B2C-0000616C       .text dance_0__FP9bgn_class */
void dance_0(bgn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    u8 uVar2;
    short sVar4;
    f32 fVar9;
    cXyz local_34;

    if (i_this->mC7AC[1] == 0) {
        i_this->mC7AC[1] = (s16)(int)(cM_rndF(150.0f) + 50.0f);
        i_this->mC758.x = cM_rndFX(1500.0f);
        i_this->mC758.z = cM_rndFX(1500.0f);
        i_this->mC76C = 0.0f;
    }
    cLib_addCalc2(&actor->current.pos.x, i_this->mC758.x, 0.05f, i_this->mC76C);
    cLib_addCalc2(&actor->current.pos.z, i_this->mC758.z, 0.05f, i_this->mC76C);
    cLib_addCalc2(&i_this->mC76C, REG0_F(0x13) + 20.0f, 1.0f, 0.5f);
    cLib_addCalc2(&i_this->mC728.y, (REG0_F(9) + 50.0f) * cM_ssin(i_this->mC746 * (REG0_S(9) + 500)), 0.5f, REG0_F(8) + 20.0f);
    if ((i_this->mAAA8[0].m2D0 == 0) || (i_this->mAAA8[1].m2D0 == 0)) {
        sVar4 = fopAcM_searchPlayerAngleY(actor);
        cLib_addCalcAngleS2(&actor->shape_angle.y, sVar4, 10, 0x400);
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
        break;
    case 1:
        if (((i_this->mC7AC[0] == 0) && (!ki_check(i_this))) && (l_HIO.m028 != 0)) {
            if (((i_this->mC754 == 1) || (i_this->mC754 == 2)) || (i_this->mC754 == 3)) {
                if (((i_this->mAAA8[0].m2D0 != 0) && (i_this->mAAA8[1].m2D0 != 0)) && (i_this->mC7B0 == 0)) {
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
        switch (i_this->mC74C) {
        case 0:
            dance_A(i_this);
            break;
        case 1:
            dance_B(i_this);
            break;
        }
    }
    s32 i = 0;
    move_s* pmVar8 = &i_this->mAAA8[i];
    for (i = 0; i < 8; i++, pmVar8++) {
        if (pmVar8->m2D0 == 0) {
            local_34.x = pmVar8->m2E0.x - pmVar8->m2D4.x;
            local_34.y = pmVar8->m2E0.y - pmVar8->m2D4.y;
            local_34.z = pmVar8->m2E0.z - pmVar8->m2D4.z;
            fVar9 = local_34.abs();
            if (fVar9 > REG0_F(0) + 100.0f) {
                sVar4 = (int)(REG0_F(2) + (fVar9 - ((REG0_F(0) + 100.0f) * (REG0_F(1) + 0.06f) + 50.0f)));
                if (pmVar8->m2F8 > sVar4) {
                    pmVar8->m2F8 = sVar4;
                }
            }
        }
    }
}

/* 0000616C-00007108       .text punch_LR__FP9bgn_class */
void punch_LR(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    s8 bVar2;
    s8 bVar3;
    short sVar7;
    s32 uVar11;
    cXyz local_6c;
    cXyz local_84;
    cXyz local_90;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    bVar2 = false;
    cLib_addCalc0(&i_this->mC728.y, 0.5f, 20.0f);
    bVar3 = false;
    uVar11 = 0;
    local_90 = player->current.pos;
    if ((i_this->mAAA8[0].m2D0 != 0) && (i_this->mAAA8[1].m2D0 != 0)) {
        cMtx_YrotS(*calc_mtx, (int)actor->shape_angle.y);
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
            i_this->mC788 = i_this->m3AF0[BGN_HAND_MAX].m0D4;
            local_84 = local_90 - i_this->mC788;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            fVar1 = std::sqrtf(local_84.x * local_84.x + local_84.z * local_84.z);
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, fVar1));
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
        i_this->m3AF0[BGN_HAND_MAX - 1].m0F8.OnAtSetBit();
        i_this->mC788 += i_this->mC7A0;
        i_this->mAAA8[4].m2E8 = 100.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mC779 = 0;
            i_this->mAAA8[4].m2F4 = REG0_F(0xf) + 5000.0f;
            bVar2 = true;
            i_this->mAAA8[4].m2E0.x = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.x;
            i_this->mAAA8[4].m2E0.y = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.y;
            i_this->mAAA8[4].m2E0.z = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.z;
            attack_eff_set(i_this, i_this->m3AF0[BGN_HAND_MAX - 1].m0D4, 1);
        }
        break;
    case 3:
        bVar3 = true;
        uVar11 = 1;
        i_this->mC338 = 200.0f;
        i_this->mC334 = 200.0f;
        if (i_this->mC7AC[0] == 0x14) {
            i_this->mC77C = i_this->m0C04[BGN_HAND_MAX - 1].m0D4;
            local_84 = local_90 - i_this->mC77C;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            fVar1 = std::sqrtf(local_84.x * local_84.x + local_84.z * local_84.z);
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, fVar1));
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
        i_this->m0C04[BGN_HAND_MAX - 1].m0F8.OnAtSetBit();
        i_this->mC77C += i_this->mC794;
        i_this->mC338 = 200.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->m078C[BGN_HAND_MAX + 1].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mAAA8[3].m2F4 = REG0_F(0xf) + 5000.0f;
            i_this->mC778 = 0;
            bVar2 = true;
            i_this->mAAA8[3].m2E0.x = i_this->m078C[BGN_HAND_MAX + 1].m0D4.x;
            i_this->mAAA8[3].m2E0.y = i_this->m078C[BGN_HAND_MAX + 1].m0D4.y;
            i_this->mAAA8[3].m2E0.z = i_this->m078C[BGN_HAND_MAX + 1].m0D4.z;
            attack_eff_set(i_this, i_this->m0C04[BGN_HAND_MAX - 1].m0D4, 0);
        }
        break;
    case 5:
        bVar3 = true;
        uVar11 = 3;
        i_this->mC338 = 50.0f;
        if (i_this->mC7AC[0] == 0x14) {
            i_this->mC77C = i_this->m0C04[BGN_HAND_MAX - 1].m0D4;
            i_this->mC788 = i_this->m3AF0[BGN_HAND_MAX - 1].m0D4;
            local_84 = local_90 - i_this->mC77C;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            fVar1 = std::sqrtf(local_84.x * local_84.x + local_84.z * local_84.z);
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, fVar1));
            local_6c.x = 0.0f;
            local_6c.y = 0.0f;
            local_6c.z = REG0_F(7) + 200.0f;
            MtxPosition(&local_6c, &i_this->mC794);
            local_84 = local_90 - i_this->mC788;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_84.x, local_84.z));
            fVar1 = std::sqrtf(local_84.x * local_84.x + local_84.z * local_84.z);
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_84.y, fVar1));
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
        i_this->m3AF0[BGN_HAND_MAX - 1].m0F8.OnAtSetBit();
        i_this->m0C04[BGN_HAND_MAX - 1].m0F8.OnAtSetBit();
        i_this->mC77C += i_this->mC794;
        i_this->mC788 += i_this->mC7A0;
        i_this->mC338 = 200.0f;
        i_this->mC334 = 200.0f;
        if ((i_this->mC7AC[0] == 0) || (i_this->m078C[BGN_HAND_MAX + 1].m0D4.y < i_this->mC7BC + 30.0f)) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->mAAA8[3].m2F4 = REG0_F(0xf) + 5000.0f;
            i_this->mAAA8[4].m2F4 = REG0_F(0xf) + 5000.0f;
            i_this->mC778 = 0;
            i_this->mC779 = 0;
            i_this->mAAA8[3].m2E0.x = i_this->m078C[BGN_HAND_MAX + 1].m0D4.x;
            i_this->mAAA8[3].m2E0.y = i_this->m078C[BGN_HAND_MAX + 1].m0D4.y;
            i_this->mAAA8[3].m2E0.z = i_this->m078C[BGN_HAND_MAX + 1].m0D4.z;
            i_this->mAAA8[4].m2E0.x = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.x;
            i_this->mAAA8[4].m2E0.y = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.y;
            i_this->mAAA8[4].m2E0.z = i_this->m0C04[BGN_HAND_MAX + 0x14].m0D4.z;
            attack_eff_set(i_this, i_this->m3AF0[BGN_HAND_MAX - 1].m0D4, 1);
            attack_eff_set(i_this, i_this->m0C04[BGN_HAND_MAX - 1].m0D4, 0);
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
            cLib_addCalc2(&i_this->mC32C[uVar11 - 1], REG0_F(0xe) + 1.0f, 0.2f, 0.05f);
        } else {
            for (s32 i = 0; i < 2; i++) {
                cLib_addCalc2(&i_this->mC32C[i], (1.0f + REG0_F(0xe)), 0.2f, 0.05f);
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
            if ((i_this->mC7AC[0] & 0x10U) != 0) {
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
void start(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short target;

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
void body_attack(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    s16 sVar6;
    f32 fVar10;
    cXyz local_50;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
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
                i_this->mAAA8[i].m2F4 = REG0_F(0xf) + 5000.0f;
            }
        }
        break;
    case 3:
        i_this->mC728.y += actor->speed.y;
        actor->speed.y -= (REG0_F(4) + 10.0f);
        i_this->mC7FC.OnAtSetBit();
        i_this->m078C[0].m0F8.OnAtSetBit();
        if (i_this->mC728.y <= -1000.0f) {
            i_this->mC728.y = -1000.0f;
            actor->speed.y = actor->speed.y * -(REG0_F(0x13) + 0.4f);
            for (s32 i = 0; i < 8; i++) {
                i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x28;
                i_this->mAAA8[i].m2F4 = REG0_F(0xf) + 5000.0f;
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
                i_this->mAAA8[i].m2F4 = REG0_F(0xf) + 5000.0f;
            }
        }
        break;
    }
    if (bVar2) {
        cLib_addCalc2(&actor->current.pos.x, i_this->mC758.x, 0.1f, i_this->mC76C);
        cLib_addCalc2(&actor->current.pos.z, i_this->mC758.z, 0.1f, i_this->mC76C);
        cLib_addCalc2(&i_this->mC76C, REG0_F(0x13) + 30.0f, 1.0f, 0.5f);
        cLib_addCalc2(&i_this->mC728.y, i_this->mC758.y, 0.1f, 50.0f);
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->mC764, 10, 0x400);
    }
}

/* 000076F4-000078D0       .text tail_attack__FP9bgn_class */
void tail_attack(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
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
            cLib_addCalc2(&i_this->mC76C, REG0_F(0x13) + 15.0f, 1.0f, 0.2f);
            for (s32 i = 0; i < BGN_TAIL_MAX; i++) {
                i_this->m7BBC[i].m0F8.OnAtSetBit();
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
void damage(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m02B8->play(NULL, 0, 0);
    i_this->m02B8->play(NULL, 0, 0);
    switch (i_this->mC74A) {
    case 0:
        i_this->mC7AC[0] = 0;
        i_this->mC74A = 1;
        actor->speed.y = REG0_F(8) + 100.0f;
        i_this->mC770 = REG0_S(0) + 0x32;
        for (s32 i = 0; i < 8; i++) {
            i_this->mAAA8[i].m2F8 = REG0_S(7) + 0x46;
            i_this->mAAA8[i].m2F4 = REG0_F(0xf) + 8000.0f;
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
void head_recover(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
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
            i_this->mAAA8[7].m308 = 2;
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
void hensin(bgn_class* i_this) {
    /* Nonmatching */
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
        i_this->mCA62 = 1;
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
                i_this->mAAA8[i].m2F4 = REG0_F(0xf) + 6000.0f;
            }
            if (i_this->mC74A == 1) {
                actor->speed.y = REG0_F(3) + 220.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(0x12) + 20.0f;
                attack_eff_set(i_this, i_this->m0314[0].m0D4, 0);
            } else if (i_this->mC74A == 2) {
                actor->speed.y = REG0_F(3) + 190.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(0x12) + 15.0f;
                attack_eff_set(i_this, i_this->m0314[0].m0D4, 1);
            } else if (i_this->mC74A == 3) {
                actor->speed.y = REG0_F(3) + 130.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mCA9C = REG0_F(0x12) + 10.0f;
            } else {
                actor->speed.y = 0.0f;
                mDoAud_bgmStart(JA_BGM_BGN_TARABA_IN);
            }
            i_this->mC74A++;
        }
        break;
    case 5:
        if (i_this->mCA64 >= (s16)(REG0_S(3) + 0x96)) {
            cLib_addCalc2(&i_this->mCC88, 1.0f, 1.0f, REG0_F(0xf) + 0.005f);
        }
        cLib_addCalc2(&i_this->mC774, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
        if (i_this->mCA64 == 0x118) {
            i_this->mC74A = 10;
            i_this->mC7AC[0] = REG0_S(6) + 300;
            i_this->mC7AC[1] = REG0_S(7) + 0x96;
            i_this->mCC8C = dComIfGp_particle_set(dPa_name::ID_SCENE_8419, &actor->current.pos);
        }
        break;
    case 10:
        cLib_addCalc2(&i_this->mCC88, 1.0f, 1.0f, REG0_F(0xf) + 0.005f);
        if (i_this->mCC8C != NULL) {
            if (i_this->mC7AC[1] != 0) {
                i_this->mCC8C->setGlobalRTMatrix(i_this->m02B8->getModel()->getAnmMtx(2));
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
            if (i_this->mC7AC[0] <= 1) {
                cLib_addCalc2(&i_this->mCC84, 0.22f, 0.1f, 0.0055f);
                if (i_this->mC7AC[0] == 1) {
                    mDoAud_seStart(JA_SE_CM_BGN_D_TO_T_2, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
                if (i_this->mCC84 > 0.21f) {
                    l_HIO.m024++;
                    bgn2->actor.current.angle = i_this->mC314;
                    bgn2->actor.shape_angle = i_this->mC314;
                    bgn2->actor.current.pos = i_this->mC308;
                    bgn2->m2E7C = 1.0f;
                    i_this->mCA62++;
                    i_this->mCA64 = 0;
                    local_20.setall(REG0_F(4) + 10.0f);
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0013, &bgn2->actor.current.pos, NULL, &local_20);
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0016, &bgn2->actor.current.pos, NULL, &local_20);
                    mDoAud_seStart(JA_SE_CM_BGN_METAM_EXPLODE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                } else {
                    cLib_addCalcAngleS2(&i_this->mCA60, 0xb4, 1, 4);
                }
            }
        }
        break;
    }
}

/* 000084B4-00008888       .text himo_control__FP9bgn_classP6move_sP4cXyz */
void himo_control(bgn_class* i_this, move_s* param_2, cXyz* param_3) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    s8 bVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    f32 fVar17;
    cXyz local_ac;
    cXyz local_b8;
    cXyz local_c4;

    cXyz* pcVar5 = &param_2->m000[1];
    local_ac.x = 0.0f;
    local_ac.y = 0.0f;
    local_ac.z = (REG0_F(0xc) + 15.0f) * i_this->mCC80;
    s32 j, k, i;
    j = 0;
    k = 0;
    i = 1;
    cXyz* temp = &param_3[1];
    for (; i < 60; i++, pcVar5++, temp++) {
        dVar13 = (pcVar5[0].x - pcVar5[-1].x);
        fVar17 = pcVar5[0].z - pcVar5[-1].z;
        dVar12 = fVar17;
        dVar10 = ((pcVar5[0].y - 40.0f) + REG0_F(0xd));
        if (dVar10 < 0.0f) {
            dVar10 = 0.0f;
            bVar9 = true;
        } else {
            bVar9 = false;
        }
        fVar1 = (dVar10 - pcVar5[-1].y);
        dVar11 = fVar1;
        dVar10 = param_2->m304;
        if (dVar10 > 0.01f) {
            j = (int)(dVar10 * cM_ssin(param_2->m2FA + i * (REG0_S(3) + 2000)));
            k = (int)(dVar10 * cM_scos(param_2->m2FC + i * (REG0_S(4) + 0x9c4)));
        }
        cMtx_XrotS(*calc_mtx, (int)j - cM_atan2s(fVar1, fVar17));
        cMtx_YrotM(*calc_mtx, (int)k + cM_atan2s(dVar13, std::sqrtf((dVar11 * dVar11) + (dVar12 * dVar12))));
        MtxPosition(&local_ac, &local_b8);
        pcVar5[0].x = pcVar5[-1].x + local_b8.x;
        pcVar5[0].y = pcVar5[-1].y + local_b8.y;
        pcVar5[0].z = pcVar5[-1].z + local_b8.z;
        *temp = pcVar5[0];
        if (((bVar9) && (((int)i_this->mC746 & 7U) == 0)) && (((int)i_this->mC746 >> 3 & 0xf) == (i & 0xf))) {
            local_c4 = pcVar5[0];
            if (!gr_check(i_this, &local_c4)) {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8407, &local_c4, 0xff, g_whiteColor, g_whiteColor, 0);
                if (i_this->m0304 == 0) {
                    i_this->m0304 = (s16)(int)(cM_rndF(20.0f) + 20.0f);
                    i_this->m0308 = local_c4;
                    mDoAud_seStart(JA_SE_CM_BGN_STRING_RIPPLE, &i_this->m0308, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
    }
}

/* 00008888-00008C20       .text last_himo_control__FP9bgn_class */
void last_himo_control(bgn_class* i_this) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;
    cXyz* pcVar5;
    u8* puVar8;
    cXyz* pcVar8;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    f32 dVar14;
    cXyz local_a8;
    cXyz local_b4;

    i_this->mC450[0].set(-15.0f, REG8_F(4) + 4441.46f, REG8_F(3) + 375.17f);
    pcVar8 = i_this->mC414.getPos(0);
    puVar8 = i_this->mC414.getSize(0);
    *puVar8 = 10;
    *pcVar8 = i_this->mC450[0];
    if (i_this->mC720 == 1) {
        i_this->mC720++;
        pcVar5 = &i_this->mC450[1];
        for (s32 i = 0; i < 59; i++, pcVar5++) {
            *pcVar5 = i_this->mC450[0];
        }
        i_this->mC724 = REG0_F(0x13) + 5000.0f;
    } else {
        cLib_addCalc0(&i_this->mC724, 1.0f, (REG0_F(0x12) + 50.0f));
    }
    pcVar5 = &i_this->mC450[1];
    dVar14 = 0.0f;
    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
    local_a8.z = REG0_F(0xc) + 45.0f;
    s32 i, j, k;
    k = 0;
    cXyz* var_r25;
    j = 0;
    i = 1;
    var_r25 = &pcVar8[1];
    u8* var_r28 = &puVar8[1];
    for (; i < 60; i++, var_r25++, var_r28++) {
        dVar13 = (pcVar5->x - pcVar5[-1].x);
        fVar1 = REG0_F(0xd) + ((pcVar5->y - pcVar5[-1].y) - 35.0f);
        dVar12 = fVar1;
        fVar2 = pcVar5->z - pcVar5[-1].z;
        dVar11 = fVar2;
        dVar10 = i_this->mC724;
        if (dVar10 > 0.01f) {
            k = (int)(dVar10 * cM_ssin(i_this->mC746 * 2000 + i * (REG0_S(3) + 2000)));
            j = (int)(dVar10 * cM_scos(i_this->mC746 * 0x8fc + i * (REG0_S(4) + 0x9c4)));
        }
        cMtx_XrotS(*calc_mtx, (int)k - cM_atan2s(fVar1, fVar2));
        dVar10 = std::sqrtf((dVar12 * dVar12) + (dVar11 * dVar11));
        cMtx_YrotM(*calc_mtx, (int)j + cM_atan2s(dVar13, dVar10));
        MtxPosition(&local_a8, &local_b4);
        pcVar5->x = pcVar5[-1].x + local_b4.x;
        pcVar5->y = pcVar5[-1].y + local_b4.y;
        pcVar5->z = pcVar5[-1].z + local_b4.z;
        *var_r25 = *pcVar5;
        *var_r28 = 10;
        pcVar5++;
    }
}

/* 00008C20-000092B8       .text action_s__FP9bgn_classP6move_si */
void action_s(bgn_class* i_this, move_s* param_2, int param_3) {
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
    if ((l_HIO.m025 == 0) && (i_this->mC728.y > REG0_F(0xc) + -900.0f)) {
        target = (REG0_F(0xd) + ((param_2->m2F8) * (REG0_F(2) + 20.0f) + 300.0f));
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
    pcVar4 = i_this->mC39C.getPos(param_3);
    pcVar7 = i_this->mC39C.getSize(param_3);
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
                fVar3 = (REG0_F(0xc) + 10.0f) * (param_2->m300) * cM_ssin(cM_rad2s((s32)(i) * 0.053247336f));
                local_70.x = fVar3 * cM_scos(i_this->mC746 * (REG0_S(3) + 0x5800));
                local_70.z = fVar3 * cM_scos(i_this->mC746 * (REG0_S(5) + 0x5200));
            } else {
                fVar3 = param_2->m2EC * (cM_ssin(cM_rad2s((s32)(i) * 0.053247336f)) * (s32)(0x3b - i) * 0.01666667f);
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
void action_main(bgn_class* i_this) {
    /* Nonmatching */
    cXyz* pcVar7;
    u8* pcVar5;
    f32 dVar9;
    cXyz local_90;
    cXyz local_9c;

    local_9c.x = i_this->mC308.x;
    local_9c.y = i_this->mC308.y;
    local_9c.z = i_this->mC308.z;
    cLib_addCalc0(&i_this->mC774, 1.0f, 25.0f);
    pcVar7 = i_this->mC3D8.getPos(0);
    pcVar5 = i_this->mC3D8.getSize(0);
    for (s32 i = 0; i < 60; i++, pcVar7++, pcVar5++) {
        dVar9 = i_this->mC774 * (cM_ssin(cM_rad2s((s32)(i) * 0.053247336f)) * ((s32)(0x3b - i) * 0.01666667f));
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
        if (0 < i_this->mC748) {
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
void move(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar1;
    int iVar3;
    f32 fVar9;
    csXyz local_110;
    cXyz local_e4;

    i_this->mC734 = i_this->mC728;
    i_this->m02EC->play();
    i_this->m02F0->play();
    if (i_this->m02B5 != 0) {
        i_this->mC748 = 10;
        actor->current.pos.set(0.0f, 30000.0f, 0.0f);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        i_this->mCC80 = REG0_F(0x19) + 1.0f;
        i_this->mCC84 = REG0_F(0x14);
        i_this->mCC88 = REG0_F(0x15);
    } else {
        if (i_this->mC748 == 10) {
            actor->current.pos = actor->home.pos;
            i_this->mC748 = 0;
            i_this->mC74A = 0;
            actor->health = 3;
        }
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        actor->attention_info.distances[2] = 0x22;
        i_this->mC308 = actor->current.pos + i_this->mC728;
        i_this->mC308.y = i_this->mC308.y + l_HIO.m04C;
        if (i_this->mC308.y <= (i_this->mC7BC + 100.0f + REG0_F(0))) {
            i_this->mC308.y = (i_this->mC7BC + 100.0f + REG0_F(0));
        }
        local_110 = actor->shape_angle;
        if (l_HIO.m025 != 0) {
            local_110.y = l_HIO.m042;
        }
        BGN_HAND_MAX = (int)l_HIO.m0F0;
        BGN_TAIL_MAX = (int)l_HIO.m0F2;
        dBgS_GndChk local_d8;
        Vec pos;
        pos = actor->current.pos;
        pos.y += 500.0f;
        local_d8.SetPos(&pos);
        i_this->mC7BC = REG0_F(0x10) + -40.0f + 30.0f + 100.0f;
        sVar1 = 0;
        if (i_this->mAAA8[0].m2D0 != 0) {
            sVar1 = 8000;
        }
        if (i_this->mAAA8[1].m2D0 != 0) {
            sVar1 -= 8000;
        }
        cLib_addCalcAngleS2(&i_this->mC744, sVar1, 8, 0x400);
        if (i_this->mAAA8[2].m2D0 == 0) {
            local_110.x += (int)(i_this->mAAA8[2].m2D4.y * (REG0_F(0xb) + 8.0f));
        }
        if (i_this->mAAA8[3].m2D0 != 0) {
            local_110.z -= (s16)(REG0_S(0) + 3000);
        } else {
            local_110.z += (int)(i_this->mAAA8[3].m2D4.y * (REG0_F(0xc) + 5.0f));
            local_110.y += (int)(i_this->mAAA8[3].m2D4.z * -(REG0_F(0xd) + 5.0f));
        }
        if (i_this->mAAA8[4].m2D0 != 0) {
            local_110.z += (s16)(REG0_S(0) + 3000);
        } else {
            local_110.z += (int)(i_this->mAAA8[4].m2D4.y * -(REG0_F(0xc) + 5.0f));
            local_110.y += (int)(i_this->mAAA8[4].m2D4.z * (REG0_F(0xd) + 5.0f));
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
                local_e4 = i_this->m0C04[BGN_HAND_MAX].m0D4 - i_this->m0C04[BGN_HAND_MAX - 1].m0D4;
                fVar9 = local_e4.abs();
            } else if ((i == 1) && (i_this->mC779 != 0)) {
                local_e4 = i_this->m3AF0[BGN_HAND_MAX].m0D4 - i_this->m3AF0[BGN_HAND_MAX - 1].m0D4;
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
        i_this->m078C[0].m0F8.OffAtSetBit();
        i_this->m0C04[BGN_HAND_MAX - 1].m0F8.OffAtSetBit();
        i_this->m3AF0[BGN_HAND_MAX - 1].m0F8.OffAtSetBit();
        for (iVar3 = 0; iVar3 < BGN_TAIL_MAX; iVar3++) {
            i_this->m7BBC[iVar3].m0F8.OffAtSetBit();
        }
        action_main(i_this);
        damage_check(i_this);
        shape_calc(i_this);
    }
}

/* 0000A104-0000AE8C       .text demo_camera__FP9bgn_class */
void demo_camera(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    f32 dVar11;
    cXyz local_44;
    cXyz local_50;
    cXyz local_5c;
    cXyz local_8c;
    cXyz local_98;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    switch (i_this->mCA62) {
    case 0:
        break;
    case 1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCA62++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mCA64 = 0;
        i_this->mCAA0 = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCA80 = i_this->mC308;
        player->changeOriginalDemo();
        fpcM_Search(ki_del_sub, i_this);
        i_this->mCC7C = 0;
        // fallthrough
    case 2:
        cMtx_YrotS(*calc_mtx, (int)i_this->mC314.y);
        local_44.set(REG0_F(0) + 200.0f, REG0_F(1) + 100.0f, REG0_F(2) + 2000.0f);
        MtxPosition(&local_44, &local_50);
        i_this->mCA68 = local_50;
        if (i_this->mCA64 > 0x12C) {
            fVar2 = 0.1f;
        } else {
            fVar2 = 0.5f;
        }
        dVar11 = fVar2;
        cLib_addCalc2(&i_this->mCA80.x, i_this->mC308.x, 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCA80.y, i_this->mC308.y + 100.0f + REG0_F(3), (f32)dVar11, 400.0f);
        cLib_addCalc2(&i_this->mCA80.z, i_this->mC308.z, 0.1f, 300.0f);
        local_44.x = REG0_F(4);
        local_44.y = player->current.pos.y;
        local_44.z = REG0_F(5) + 1500.0f;
        MtxPosition(&local_44, &local_50);
        player->setPlayerPosAndAngle(&local_50, (int)(short)(i_this->mC314.y + 0x8000));
        if (i_this->mCA64 == (s16)(REG0_S(5) + 0xdc)) {
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        if (i_this->mCA64 == (s16)(REG0_S(6) + 0x140)) {
            player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        }
        break;
    case 3:
        cLib_addCalc2(&i_this->mCA80.x, bgn2->actor.current.pos.x, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->mCA80.y, bgn2->actor.current.pos.y + REG0_F(0xd), 0.1f, 200.0f);
        cLib_addCalc2(&i_this->mCA80.z, bgn2->actor.current.pos.z, 0.1f, 100.0f);
        if (i_this->mCA64 == (s16)(REG0_S(7) + 0x5a)) {
            i_this->mCA9C = REG0_F(0x12) + 30.0f;
        }
        if (i_this->mCA64 == (s16)(REG0_S(7) + 100)) {
            player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
            player->voiceStart(29);
        }
        if (i_this->mCA64 > (short)(REG0_S(8) + 0x6e)) {
            cLib_addCalc2(&i_this->mCAA0, REG0_F(0xb) + 35.0f, 0.1f, REG0_F(0xc) + 0.5f);
            if ((i_this->mCA64 == 0x82) || (i_this->mCA64 == 0xb4)) {
                mDoAud_seStart(JA_SE_CM_BGN_T_MOUSE_OPEN, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
            if (i_this->mCA64 == 0x98) {
                mDoAud_seStart(JA_SE_CM_BGN_T_MOUSE_CLOSE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
        cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 1);
        if (i_this->mCA64 <= (short)(REG0_S(8) + 200)) {
            break;
        }
        mDoAud_bgmStart(JA_BGM_BGN_TARABA);
        goto block_57;
    case 0xA:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCA62++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mCA64 = 0;
        i_this->mCAA0 = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCA80 = bgn2->actor.current.pos;
        player->changeOriginalDemo();
        fpcM_Search(ki_del_sub, i_this);
        bgn2->m2ED0 = 0;
        i_this->mCA74.set(200.0f, 2100.0f, 2500.0f);
    case 0xB:
    case 0xC:
        cLib_addCalc2(&i_this->mCA74.x, -1800.0f, 0.05f, i_this->mCA98 * 2000.0f);
        cLib_addCalc2(&i_this->mCA74.y, 1100.0f, 0.05f, i_this->mCA98 * 1000.0f);
        cLib_addCalc2(&i_this->mCA74.z, 1000.0f, 0.05f, i_this->mCA98 * 1500.0f);
        cLib_addCalc2(&i_this->mCA98, 0.01f, 1.0f, 0.0001f);
        cMtx_YrotS(*calc_mtx, (int)bgn2->actor.shape_angle.y);
        MtxPosition(&i_this->mCA74, &local_50);
        i_this->mCA68.x = local_50.x;
        i_this->mCA68.y = local_50.y;
        i_this->mCA68.z = local_50.z;
        if (i_this->mCA62 == 0xb) {
            cLib_addCalc2(&i_this->mCA80.x, bgn2->actor.current.pos.x, 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCA80.y, bgn2->actor.current.pos.y + REG0_F(0xd), 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCA80.z, bgn2->actor.current.pos.z, 0.1f, 300.0f);
            local_44.x = REG0_F(4);
            local_44.y = player->current.pos.y;
            local_44.z = REG0_F(5) + -2000.0f;
            MtxPosition(&local_44, &local_50);
            player->setPlayerPosAndAngle(&local_50, (int)bgn2->actor.shape_angle.y);
        } else {
            cLib_addCalc2(&i_this->mCA80.x, bgn3->actor.current.pos.x, 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCA80.y, bgn3->actor.current.pos.y + 50.0f + REG8_F(0x10), 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCA80.z, bgn3->actor.current.pos.z, 0.1f, 300.0f);
            cLib_addCalc2(&i_this->mCAA0, REG0_F(0x11) + 30.0f, REG0_F(0x12) + 0.05f, REG0_F(0x13) + 0.2f);
            cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 2);
        }
        if (i_this->mCA64 > (short)(REG0_S(9) + 0x172)) {
            goto block_57;
        }
        break;
    case 0x14:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->mCA62++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mCA64 = 0;
        i_this->mCAA0 = 55.0f;
        i_this->mCA98 = 0.0f;
        i_this->mCA80 = bgn3->actor.current.pos;
        player->changeOriginalDemo();
        i_this->mCA60 = 0xb4;
        fpcM_Search(ki_del_sub, i_this);
        fpcM_Search(ks_del_sub, i_this);
    case 0x15:
        cLib_addCalcAngleS2(&i_this->mCA60, 1, 1, 1);
        i_this->mCA68.set(500.0f, REG0_F(3) + 500.0f, REG0_F(4) + 2000.0f);
        cLib_addCalc2(&i_this->mCA80.x, bgn3->actor.current.pos.x, 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCA80.y, bgn3->actor.current.pos.y + REG0_F(0xd), 0.1f, 300.0f);
        cLib_addCalc2(&i_this->mCA80.z, bgn3->actor.current.pos.z, 0.1f, 300.0f);
        local_44.x = REG0_F(4);
        local_44.y = player->current.pos.y;
        local_44.z = REG0_F(5) + -1000.0f;
        player->setPlayerPosAndAngle(&local_44, (int)bgn2->actor.shape_angle.y);
        if (i_this->mCA64 == 0x104) {
            mDoAud_monsSeStart(JA_SE_CV_BGN_DIE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mCA64 >= 0x172) {
            local_5c.setall(REG0_F(4) + 10.0f);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0013, &bgn3->actor.current.pos, NULL, &local_5c);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0016, &bgn3->actor.current.pos, NULL, &local_5c);
            mDoAud_seStart(JA_SE_CM_BGN_LAST_EXPLODE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->m02B5 = 3;
            l_HIO.m024 = 3;
            i_this->mCA62++;
            i_this->mC720 = 1;
            i_this->mCA60 = 0xb4;
        }
        break;
    case 0x16:
        if (i_this->mCA64 >= 0x186) {
            last_himo_control(i_this);
        }
        if (i_this->mCA64 >= (short)(REG8_S(7) + 500)) {
            i_this->mCC90 = 2;
        }
        break;
    case 0x96:
    block_57:
        camera->mCamera.SetTrimSize(0);
        camera->mCamera.Start();
        dMeter_mtrShow();
        dComIfGp_event_reset();
        i_this->mCA62 = 0;
        i_this->mCA60 = 1;
        break;
    default:
        break;
    }
    if (i_this->mCA62 != 0) {
        f32 fx = i_this->mCA9C * cM_ssin(i_this->mCA64 * 0x3300);
        f32 fy = i_this->mCA9C * cM_scos(i_this->mCA64 * 0x3000);
        local_8c.x = i_this->mCA68.x + fx;
        local_8c.y = i_this->mCA68.y + fy;
        local_8c.z = i_this->mCA68.z;
        local_98.x = i_this->mCA80.x + fx;
        local_98.y = i_this->mCA80.y + fy;
        local_98.z = i_this->mCA80.z;
        s16 r6 = (i_this->mCA9C * cM_scos(i_this->mC746 * 0x1c00) * 7.5f);
        camera->mCamera.Set(local_98, local_8c, r6, i_this->mCAA0);
        cLib_addCalc0(&i_this->mCA9C, 1.0f, (REG0_F(0x10) + 1.0f));
        JUTReport(410, 430, "K SUB  COUNT  %d", (int)i_this->mCA64);
        i_this->mCA64++;
    }
}

/* 0000AE8C-0000B134       .text daBgn_Execute__FP9bgn_class */
static BOOL daBgn_Execute(bgn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

    if (i_this->m02B4 == 0xff) {
        return TRUE;
    }
    local_1c.setall(0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &center_pos, &bg_tevstr);
    bomb_splash_check(i_this);
    bgn2 = (bgn2_class*)fpcM_Search(bgn2_s_sub, i_this);
    bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
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
    if (i_this->m0300 != 0) {
        i_this->m0300--;
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
    if (i_this->mCC7C != 0) {
        i_this->mCC7C--;
        if (ki_check(i_this) < l_HIO.m17A) {
            local_28.x = cM_rndFX(2500.0f);
            local_28.y = cM_rndF(500.0f) + 3500.0f;
            local_28.x = cM_rndFX(2500.0f);
            fopAcM_create(PROC_KI, 0xffff0003, &local_28, fopAcM_GetRoomNo(actor));
        }
    }
    i_this->m02B5 = l_HIO.m024;
    if (i_this->mCC90 == 2) {
        i_this->mCC90 = 0;
        dComIfGp_setNextStage("GanonK", 4, 0, 9);
        dComIfGs_onEventBit(0x3f10);
    }
    return TRUE;
}

/* 0000B134-0000B13C       .text daBgn_IsDelete__FP9bgn_class */
static BOOL daBgn_IsDelete(bgn_class*) {
    return TRUE;
}

/* 0000B13C-0000B238       .text daBgn_Delete__FP9bgn_class */
static BOOL daBgn_Delete(bgn_class* i_this) {
    /* Nonmatching */
    dComIfG_resDeleteDemo(&i_this->m02AC, "Bgn");
    i_this->mCC3C[0].end();
    i_this->mCC3C[1].end();
    if (i_this->mCC91 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    mDoAud_seDeleteObject(&i_this->mC77C);
    mDoAud_seDeleteObject(&i_this->mC788);
    mDoAud_seDeleteObject(&i_this->mCA54);
    mDoAud_seDeleteObject(&i_this->m0308);
    return TRUE;
}

/* 0000B238-0000B284       .text part_init__FP6part_sP12J3DModelData */
s32 part_init(part_s* param_1, J3DModelData* param_2) {
    param_1->m000 = mDoExt_J3DModel__create(param_2, 0, 0x11020203);
    if (!param_1->m000) {
        return FALSE;
    }
    return TRUE;
}

/* 0000B284-0000B994       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    /* Nonmatching */
    mDoExt_McaMorf* morf;
    J3DModelData* modelData;
    J3DModelData* pvVar4;
    int iVar4;
    J3DAnmTevRegKey* pJVar7;
    ResTIMG* pRVar8;
    bgn_class* i_this = (bgn_class*)a_this;

    morf = new mDoExt_McaMorf(
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
    i_this->m02B8 = morf;
    if ((i_this->m02B8 == NULL) || (i_this->m02B8->getModel() == NULL)) {
        return FALSE;
    }
    i_this->m0314[0].m000 = i_this->m02B8->getModel();
    i_this->m0314[0].m0D2 = 0x10;
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_MAIN1);
    i_this->m02BC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02BC == NULL) {
        return FALSE;
    }
    pvVar4 = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_BODY1);
    if (!part_init(i_this->m078C, pvVar4)) {
        return FALSE;
    }
    i_this->m078C[0].m0D2 = 10;
    for (s32 i = 0, j = 0; i < 0x14; j += 3, i++) {
        if (!part_init(&i_this->m0C04[i], pvVar4)) {
            return FALSE;
        }
        if (!part_init(&i_this->m3AF0[i], pvVar4)) {
            return FALSE;
        }
        i_this->m3AF0[i].m0D2 = j + 0xdU;
        i_this->m0C04[i].m0D2 = j + 0xdU;
    }
    for (s32 i = 0, j = 0; i < 3; j += 3, i++) {
        if (!part_init(&i_this->m69DC[i], pvVar4)) {
            return FALSE;
        }
        if (!part_init(&i_this->m72CC[i], pvVar4)) {
            return FALSE;
        }
        i_this->m72CC[i].m0D2 = j + 10U;
        i_this->m69DC[i].m0D2 = j + 10U;
    }
    for (s32 i = 0; i < 0x14; i++) {
        if (!part_init(&i_this->m7BBC[i], pvVar4)) {
            return FALSE;
        }
        i_this->m7BBC[i].m0D2 = 0xb - i;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENA);
    i_this->m02E8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02E8 == NULL) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENB);
    i_this->m02E4 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02E4 == NULL) {
        return FALSE;
    }
    i_this->m02F0 = new mDoExt_brkAnm();
    if (i_this->m02F0 == NULL) {
        return FALSE;
    }
    pJVar7 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENB));
    iVar4 = i_this->m02F0->init(modelData, pJVar7, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar4 == 0) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_JYAKUTENC);
    i_this->m02E0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02E0 == NULL) {
        return FALSE;
    }
    i_this->m02EC = new mDoExt_brkAnm();
    if (i_this->m02EC == NULL) {
        return FALSE;
    }
    pJVar7 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENC));
    iVar4 = i_this->m02EC->init(modelData, pJVar7, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar4 == 0) {
        return FALSE;
    }
    pRVar8 = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    iVar4 = i_this->mC3D8.init(1, 0x3c, pRVar8, 1);
    if (iVar4 == 0) {
        return FALSE;
    }
    pRVar8 = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_HIMO);
    iVar4 = i_this->mC39C.init(8, 0x3c, pRVar8, 1);
    if (iVar4 == 0) {
        return FALSE;
    }
    pRVar8 = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    iVar4 = i_this->mC414.init(1, 0x3c, pRVar8, 1);
    if (iVar4 == 0) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_R0E_A);
    JUT_ASSERT(7026, modelData != NULL);
    i_this->mCAA4 = mDoExt_J3DModel__create(modelData, 0x80000, 0x31000000);
    if (i_this->mCAA4 == NULL) {
        return FALSE;
    }
    i_this->mCAA8 = mDoExt_J3DModel__create(modelData, 0x80000, 0x30000000);
    if (i_this->mCAA8 == NULL) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_R00);
    i_this->mCB5C = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    JUT_ASSERT(7052, modelData != NULL);
    if (i_this->mCB5C == NULL) {
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
    f32 fVar8;
    cXyz local_50;

    fopAc_ac_c* actor = a_this;
    bgn_class* i_this = (bgn_class*)a_this;
    cPhs_State res;
    fopAcM_SetupActor(actor, bgn_class);
    res = dComIfG_resLoad(&i_this->m02AC, "Bgn");
    if (res == cPhs_COMPLEATE_e) {
        i_this->mCC3C[0].setFollowOff();
        i_this->mCC3C[1].setFollowOff();
        bgn = i_this;
        bgn2 = 0;
        bgn3 = 0;
        i_this->m02B4 = (u8)fopAcM_GetParam(actor);
        if (!fopAcM_entrySolidHeap(actor, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        if (i_this->m02B4 != 0xff) {
            if (hio_set == 0) {
                i_this->mCC91 = 1;
                hio_set = 1;
                l_HIO.mNo = mDoHIO_createChild("Ｇ（クグツ）", &l_HIO); // G (Puppet)
                BGN_HAND_MAX = (int)l_HIO.m0F0;
                BGN_TAIL_MAX = (int)l_HIO.m0F2;
            }
            i_this->mC7C0.Init(0xFF, 0xFF, actor);
            i_this->mC7FC.Set(cc_sph_src);
            i_this->mC7FC.SetStts(&i_this->mC7C0);
            i_this->mC7FC.OffAtSetBit();
            i_this->mC928.Set(core_sph_src);
            i_this->mC928.SetStts(&i_this->mC7C0);
            i_this->m0314[0].m0F8.Set(cc_sph_src);
            i_this->m0314[0].m0F8.SetStts(&i_this->mC7C0);
            i_this->m0314[0].m0F8.OffAtSetBit();
            i_this->m0314[0].m018 = actor->tevStr;
            i_this->m078C[0].m0F8.Set(cc_sph_src);
            i_this->m078C[0].m0F8.SetStts(&i_this->mC7C0);
            i_this->m078C[0].m0F8.OffAtSetBit();
            i_this->m078C[0].m018 = actor->tevStr;
            for (s32 i = 0; i < 0x14; i++) {
                i_this->m0C04[i].m0F8.Set(cc_sph_src);
                i_this->m0C04[i].m0F8.SetStts(&i_this->mC7C0);
                i_this->m0C04[i].m0F8.OffAtSetBit();
                i_this->m3AF0[i].m0F8.Set(cc_sph_src);
                i_this->m3AF0[i].m0F8.SetStts(&i_this->mC7C0);
                i_this->m3AF0[i].m0F8.OffAtSetBit();
                i_this->m0C04[i].m018 = actor->tevStr;
                i_this->m3AF0[i].m018 = actor->tevStr;
            }
            for (s32 i = 0; i < 3; i++) {
                i_this->m69DC[i].m0F8.Set(cc_sph_src);
                i_this->m69DC[i].m0F8.SetStts(&i_this->mC7C0);
                i_this->m69DC[i].m0F8.OffAtSetBit();
                i_this->m72CC[i].m0F8.Set(cc_sph_src);
                i_this->m72CC[i].m0F8.SetStts(&i_this->mC7C0);
                i_this->m72CC[i].m0F8.OffAtSetBit();
                i_this->m69DC[i].m018 = actor->tevStr;
                i_this->m72CC[i].m018 = actor->tevStr;
            }
            for (s32 i = 0; i < 0x14; i++) {
                i_this->m7BBC[i].m0F8.Set(cc_sph_src);
                i_this->m7BBC[i].m0F8.SetStts(&i_this->mC7C0);
                i_this->m7BBC[i].m0F8.OffAtSetBit();
                i_this->m7BBC[i].m018 = actor->tevStr;
            }
            for (s32 i = 0; i < 8; i++) {
                fVar8 = cM_rndF(32768.0f);
                i_this->mAAA8[i].m2FA = (s16)(int)fVar8;
                fVar8 = cM_rndF(32768.0f);
                i_this->mAAA8[i].m2FC = (s16)(int)fVar8;
            }
            if (dComIfGs_isEventBit(0x3f10)) {
                i_this->m02B4 = 0xff;
                local_50.x = 375.17f;
                local_50.y = REG8_F(4) + 4441.46f;
                local_50.z = REG8_F(3) + -15.0f;
                fopAcM_create(PROC_HIMO3, 0xf, &local_50, fopAcM_GetRoomNo(actor));
                local_50.x = 375.17f;
                local_50.y = REG8_F(4) + 4453.96f;
                local_50.z = 0.0f;
                csXyz cStack_58(0, 0x4000, 0);
                fopAcM_create(PROC_KUI, 0xffff0400, &local_50, fopAcM_GetRoomNo(actor), &cStack_58, NULL, 0xFF, NULL);
            } else {
                for (s32 parameters = 0, i = 0; parameters < 8; i++, parameters++) {
                    fopAcM_create(PROC_ATT, parameters, &actor->current.pos, fopAcM_GetRoomNo(actor));
                    i_this->mAAA8[i].m308 = 3;
                }
                fopAcM_create(PROC_BGN2, 0, &actor->current.pos, fopAcM_GetRoomNo(actor));
                fopAcM_create(PROC_BGN3, 0, &actor->current.pos, fopAcM_GetRoomNo(actor));
                mDoAud_bgmStart(JA_BGM_BGN_KUGUTSU);
                actor->health = 3;
                actor->max_health = 3;
            }
            i_this->mCC80 = 1.0f;
            i_this->mC748 = 7;
            i_this->mC7AC[0] = 0x3c;
            bg_tevstr = actor->tevStr;
            i_this->mCAAC = actor->tevStr;
            i_this->mCB74 = actor->tevStr;
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
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
