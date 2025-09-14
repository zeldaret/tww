#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kamome2.h"
#include "d/res/res_kamome.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_camera.h"
#include "d/d_priority.h"
#include "d/d_meter.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_controller_pad.h"
#include "f_op/f_op_camera.h"

class kamome2HIO_c : public JORReflexible {
public:
    kamome2HIO_c() {
        m05 = 0;
        m08 = -2500.0f;
        m0C = 60.0f;
    }
    virtual ~kamome2HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
}; // size = 0x10

static bool hio_set;
static kamome2HIO_c l_HIO;

static void anm_init(kamome2_class* i_this, int anmResIdx, f32 morf, u8 loopMode, f32 playSpeed, int soundResIdx) {
    i_this->mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Kamome", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, dComIfG_getObjectRes("Kamome", soundResIdx)
    );
}

static BOOL daKamome2_Draw(kamome2_class* i_this) {
    g_env_light.settingTevStruct(dDlst_alphaModel_c::TYPE_SPHERE, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &i_this->actor.tevStr);
    i_this->mpMorf->entryDL();

    J3DModel* pJVar4 = i_this->mpMorf->getModel();
    J3DModel* pJVar3 = i_this->mpModel;

    for (u16 i = 0; i < pJVar4->getModelData()->getJointNum(); i++) {
        pJVar3->setAnmMtx(i, pJVar4->getAnmMtx(i));
    }

    for (u16 i = 0; i < pJVar4->getModelData()->getWEvlpMtxNum(); i++) {
        pJVar3->setWeightAnmMtx(i, pJVar4->getWeightAnmMtx(i));
    }

    cXyz sp08;
    sp08.set(i_this->actor.current.pos.x, i_this->actor.current.pos.y + REG0_F(1) * 10.0f, i_this->actor.current.pos.z);
    i_this->m2A0 = dComIfGd_setRealShadow(i_this->m2A0, 1, i_this->mpModel, &sp08, REG0_F(2) * 10.0f + 500.0f, 0.0f, &i_this->actor.tevStr);
    dSnap_RegistFig(0x55, &i_this->actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

const f64 unused_4206[] = {0.5, 3.0};
const f32 unused_4207[] = {0.5f, 0.04f};

static void kamome2_bgcheck(kamome2_class* i_this) {
    f32 val = 40.0f;

    i_this->actor.current.pos.y -= val;
    i_this->actor.old.pos.y -= val;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->actor.current.pos.y += val;
    i_this->actor.old.pos.y += val;
}

static void key_move(kamome2_class* i_this) {
    interface_of_controller_pad* pad = &g_mDoCPd_cpadInfo[0];
    f32 fVar3 = pad->mMainStickPosX;
    f32 fVar4 = pad->mMainStickPosY;
    s32 iVar1 = i_this->mpMorf->getFrame();

    switch (i_this->m2AC) {
    case 0:
        i_this->m2BC = 30.0f;
        i_this->m2C0 = unused_4207[0];
        if (!CPad_CHECK_HOLD_A(0) && iVar1 == REG0_S(0) + 9) {
            i_this->m2AC = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, REG0_F(0) + 12.0f, 2, 1.0f, 8);
        }
        break;

    case 1:
        if (CPad_CHECK_HOLD_X(0)) {
            i_this->m2BC = 5.0f;
            i_this->m2C0 = 0.2f;
        } else {
            i_this->m2BC = 20.0f;
            i_this->m2C0 = 0.1f;
        }

        if (CPad_CHECK_HOLD_A(0)) {
            i_this->m2AC = 0;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 5.0f, 2, 1.0f, 9);
            fopAcM_seStart(&i_this->actor, JA_SE_CV_KAMOME, 0);
        }
        break;
    }

    s16 iVar2 = fVar3 * (REG6_F(10) + -5.0f) * 1000.0f;
    s16 iVar10 = fVar4 * (REG6_F(11) + 5.0f) * 1000.0f;
    s16 uVar9;
    s16 uVar8;
    s16 uVar7;
    s16 uVar6;
    if (std::fabsf(fVar3) > 0.2f) {
        uVar6 = 0x100;
        uVar7 = 0x400;
    } else {
        uVar6 = 0x80;
        uVar7 = 0x80;
    }

    if (std::fabsf(fVar4) > 0.2f) {
        uVar8 = 0x200;
    } else {
        uVar8 = 0x80;
    }

    if (iVar10 > 0 && i_this->mAcch.ChkGroundHit()) {
        iVar10 = 0;
        uVar8 = 0x800;
        uVar9 = 10;
    } else {
        uVar9 = 4;
    }

    cLib_addCalcAngleS2(&i_this->m2DC, iVar2, 10, uVar6);
    cLib_addCalcAngleS2(&i_this->m2DA, iVar10, uVar9, uVar8);
    cLib_addCalc2(&i_this->m314, fVar3 * (REG6_F(12) + -0.4f) * 1000.0f, 1.0f, 50.0f);

    i_this->actor.current.angle.y += (s16)i_this->m314;

    cLib_addCalcAngleS2(&i_this->actor.current.angle.x, iVar10, uVar9, uVar8);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.z, -iVar2, 5, uVar7);
    cLib_addCalcAngleS2(&i_this->m308, i_this->m314 * (REG0_F(8) + -5.0f), 10, 100);
    cLib_addCalc2(&i_this->actor.speedF, i_this->m2BC, 1.0f, i_this->m2C0);

    cXyz sp08;
    sp08.x = 0.0f;
    sp08.y = 0.0f;
    sp08.z = i_this->actor.speedF;
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    MtxPosition(&sp08, &i_this->actor.speed);

    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;

    kamome2_bgcheck(i_this);

    i_this->mSph.SetC(i_this->actor.current.pos);

    dComIfG_Ccsp()->Set(&i_this->mSph);
}

static BOOL daKamome2_Execute(kamome2_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    i_this->m2A8++;
    if (l_HIO.m05 == 0) {
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2D0); i++) {
            if (i_this->m2D0[i] != 0) {
                i_this->m2D0[i]--;
            }
        }

        if (i_this->m2A4 == 0) {
            key_move(i_this);
        }
        i_this->mpMorf->play(&i_this->actor.eyePos, 0, 0);
    }

    MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, 0);
    cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y + i_this->m2DC);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x + i_this->m2DA);
    cMtx_ZrotM(*calc_mtx, i_this->actor.current.angle.z);

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    model = i_this->mpModel;
    model->setBaseTRMtx(*calc_mtx);

    switch (i_this->m2EC) {
    case 0:
        if (i_this->m2D0[0] == 1) {
            i_this->m2EC = 1;
        }
        break;

    case 1:
        if (!i_this->actor.eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(&i_this->actor, 2, 0xffff, 0);
            i_this->actor.eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        }

        camera->mCamera.Stop();
        dMeter_mtrHide();
        camera->mCamera.SetTrimSize(2);
        i_this->m2EC = 1;
        i_this->m2F0 = i_this->actor.current.pos;
        i_this->m2FC = i_this->actor.current.pos;

    case 2:
        cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
        cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

        cXyz sp2C;
        sp2C.x = 0.0f;
        sp2C.y = 0.0f;
        sp2C.z = l_HIO.m08;
        cXyz sp20;
        MtxPosition(&sp2C, &sp20);
        cLib_addCalc2(&i_this->m2F0.x, i_this->actor.current.pos.x + sp20.x, 0.1f, 1000.0f);
        cLib_addCalc2(&i_this->m2F0.y, i_this->actor.current.pos.y + sp20.y, 0.1f, 1000.0f);
        cLib_addCalc2(&i_this->m2F0.z, i_this->actor.current.pos.z + sp20.z, 0.1f, 1000.0f);

        sp2C.x = i_this->m2DC * 0.015f;
        sp2C.y = i_this->m2DA * -0.01f;
        sp2C.z = 0;
        MtxPosition(&sp2C, &sp20);
        cLib_addCalc2(&i_this->m2FC.x, i_this->actor.current.pos.x + sp20.x, 0.1f, 1000.0f);
        cLib_addCalc2(&i_this->m2FC.y, i_this->actor.current.pos.y + sp20.y, 0.1f, 1000.0f);
        cLib_addCalc2(&i_this->m2FC.z, i_this->actor.current.pos.z + sp20.z, 0.1f, 1000.0f);
        break;
    }

    if (i_this->m2EC != 0) {
        camera->mCamera.Set(i_this->m2FC, i_this->m2F0, i_this->m308, l_HIO.m0C);
    }

    i_this->actor.eyePos = i_this->actor.current.pos;
    return TRUE;
}

static BOOL daKamome2_IsDelete(kamome2_class*) {
    return TRUE;
}

static BOOL daKamome2_Delete(kamome2_class* i_this) {
    dComIfG_deleteObjectRes("Kamome");
    if (i_this->m68C) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

static BOOL useHeapInit(fopAc_ac_c* a_this) {
    kamome2_class* i_this = (kamome2_class*)a_this;
    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Kamome", KAMOME_BDL_KA),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Kamome", KAMOME_BCK_KA_WAIT1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0x1,
        (void*)dComIfG_getObjectRes("Kamome", KAMOME_BAS_KA_WAIT1),
        0x80000,
        0x11000002
    );

    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }

    i_this->mpModel = mDoExt_J3DModel__create(i_this->mpMorf->getModel()->getModelData(), 0x20000, 0x11020203);
    if (i_this->mpModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

static cPhs_State daKamome2_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SWORD,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };

    kamome2_class* i_this = (kamome2_class*)a_this;

    cPhs_State iVar1 = dComIfG_resLoad(&i_this->mPhase, "Kamome");
    if (iVar1 == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(a_this, kamome2_class);

        i_this->m2A4 = fopAcM_GetParam(a_this);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x59A0)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));

        if (i_this->m2A4 == 3) {
            i_this->mAcchCir.SetWall(50.0f, 80.0f);
            i_this->mAcch.SetGroundUpY(40.0f);
        } else {
            i_this->mAcchCir.SetWall(30.0f, 20.0f);
        }
        i_this->mStts.Init(0, 0xff, a_this);
        i_this->mSph.Set(at_sph_src);
        i_this->mSph.SetStts(&i_this->mStts);
        i_this->m2A8 = (s16)cM_rndF(10000.0f);
        if (!hio_set) {
            l_HIO.mNo = mDoHIO_createChild("操作カモメ", &l_HIO);
            i_this->m68C = true;
            hio_set = true;
        }
        i_this->m2D0[0] = 0x1e;
    }

    return iVar1;
}

static actor_method_class l_daKamome2_Method = {
    (process_method_func)daKamome2_Create,
    (process_method_func)daKamome2_Delete,
    (process_method_func)daKamome2_Execute,
    (process_method_func)daKamome2_IsDelete,
    (process_method_func)daKamome2_Draw,
};

actor_process_profile_definition g_profile_KAMOME2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KAMOME2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kamome2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KAMOME2,
    /* Actor SubMtd */ &l_daKamome2_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
