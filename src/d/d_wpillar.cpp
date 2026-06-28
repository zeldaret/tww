#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_wpillar.h"
#include "f_op/f_op_kankyo.h"
#include "d/actor/d_a_player_main.h"
#include "cstdint.h"

/* 8023E968-8023E9E4       .text jointCallBack__10dWpillar_cFi */
int dWpillar_c::jointCallBack(int i_jointNo) {
    static const f32 min_y[] = {
        0.1418457f,
        18.307327f,
        16.280472f,
    };

    MtxP m = mpModel->getAnmMtx(i_jointNo);
    f32 var_f2 = mPos.y + mScale.x * min_y[i_jointNo - 1];
    m[1][3] = var_f2 + mHeight * (m[1][3] - var_f2);
    cMtx_copy(m, J3DSys::mCurrentMtx);
    return 1;
}

/* 8023E9E4-8023EA28       .text dWpillar_jointCallBack__FP7J3DNodei */
static BOOL dWpillar_jointCallBack(J3DNode* i_node, int param_1) {
    if (param_1 == 0) {
        J3DJoint* joint = (J3DJoint*)i_node;
        int jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();

        dWpillar_c* i_this = (dWpillar_c*)model->getUserArea();
        i_this->jointCallBack(jntNo);
    }

    return TRUE;
}

/* 8023EA28-8023ECF8       .text draw__10dWpillar_cFv */
BOOL dWpillar_c::draw() {
    int matNo;

    g_env_light.settingTevStruct(TEV_TYPE_BG1, &mPos, &mTevstr);
    g_env_light.setLightTevColorType(mpModel, &mTevstr);

    mBck.entry(mpModel->getModelData());

    if ((int)mParam == 1) {
        matNo = mpModel->getModelData()->getMaterialNum() - 1;
        while (matNo >= 0) {
            J3DMaterial* material = mpModel->getModelData()->getMaterialNodePointer(matNo);

            static const GXColorS10 calc_col = {0x00, 0x00, 0x00, 0x3C};
            material->setTevColor(2, (const J3DGXColorS10*)&calc_col);
            matNo--;
        }

        daPy_getPlayerLinkActorClass()->getBombWaterPillarBrk()->setFrame(mBck.getFrame());
        daPy_getPlayerLinkActorClass()->getBombWaterPillarBtk()->setFrame(mBck.getFrame());
    } else {
        GXColorS10 color;
        color.r = (u8)(mTevstr.mColorC0.r * 0.23529412f + 195.0f);
        color.g = (u8)(mTevstr.mColorC0.g * 0.23529412f + 195.0f);
        color.b = (u8)(mTevstr.mColorC0.b * 0.23529412f + 195.0f);

        GXColor kcolor;
        kcolor.r = mTevstr.mColorK0.r * 0.92156863f + 20.0f;
        kcolor.g = mTevstr.mColorK0.g * 0.92156863f + 20.0f;
        kcolor.b = mTevstr.mColorK0.b * 0.92156863f + 20.0f;

        mBtk.entry(mpModel->getModelData(), mBck.getFrame());

        matNo = mpModel->getModelData()->getMaterialNum() - 1;
        while (matNo >= 0) {
            J3DMaterial* material = mpModel->getModelData()->getMaterialNodePointer(matNo);

            material->setTevColor(0, (const J3DGXColorS10*)&color);
            material->setTevKColor(0, (const J3DGXColor*)&kcolor);
            matNo--;
        }
    }

    mDoExt_modelUpdateDL(mpModel);
    return 1;
}

/* 8023ECF8-8023ED18       .text dWpillar_Draw__FP10dWpillar_c */
static BOOL dWpillar_Draw(dWpillar_c* i_this) {
    return i_this->draw();
}

/* 8023ED18-8023EDB0       .text execute__10dWpillar_cFv */
BOOL dWpillar_c::execute() {
    mBck.play();

    if (mBck.isStop()) {
        fopKyM_Delete(this);
    } else {
        f32 water_y;
        if (fopAcM_getWaterY(&mPos, &water_y)) {
            mpModel->getBaseTRMtx()[1][3] = water_y;
            mPos.y = water_y;
        }
    }

    return 1;
}

/* 8023EDB0-8023EDD0       .text dWpillar_Execute__FP10dWpillar_c */
static BOOL dWpillar_Execute(dWpillar_c* i_this) {
    return i_this->execute();
}

/* 8023EDD0-8023EDD8       .text dWpillar_IsDelete__FP10dWpillar_c */
static BOOL dWpillar_IsDelete(dWpillar_c*) {
    return TRUE;
}

/* 8023EDD8-8023EE08       .text wp_delete__10dWpillar_cFv */
BOOL dWpillar_c::wp_delete() {
    if (mpHeap != NULL) {
        mDoExt_destroySolidHeap(mpHeap);
    }

    return TRUE;
}

/* 8023EE08-8023EE28       .text dWpillar_Delete__FP10dWpillar_c */
static BOOL dWpillar_Delete(dWpillar_c* i_this) {
    return i_this->wp_delete();
}

/* 8023EE28-8023F5B0       .text create__10dWpillar_cFv */
cPhs_State dWpillar_c::create() {
    new (this) dWpillar_c();

    J3DModelData* modelData;
    BOOL is_anm_init;
    mpHeap = mDoExt_createSolidHeapFromGameToCurrent(0x3440, 0x20);
    if (mpHeap != NULL) {
        if ((int)mParam == 0) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BDL_W_PILLAR_A_e);
            JUT_ASSERT(293, modelData != NULL);
            mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000202);

            J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BCK_W_PILLAR_A_e);
            is_anm_init = mBck.init(modelData, bck, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);

            J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BTK_W_PILLAR_A_e);
            is_anm_init &= mBtk.init(modelData, btk, FALSE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1);
        } else {
            modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", 0x42));
            JUT_ASSERT(320, modelData != NULL);
            mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000202);

            J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes("Link", 0xE);
            is_anm_init = mBck.init(modelData, bck, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
        }

        mDoExt_restoreCurrentHeap();
        mDoExt_adjustSolidHeap(mpHeap);
    } else {
        return cPhs_ERROR_e;
    }

    if (mpModel == NULL || !is_anm_init) {
        return cPhs_ERROR_e;
    }

    mHeight = mScale.y;
    mScale.y = mScale.x;
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(mPos.x, mPos.y, mPos.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if ((int)mParam == 0) {
        for (u16 i = 1; i < modelData->getJointNum(); i++) {
            modelData->getJointNodePointer(i)->setCallBack(dWpillar_jointCallBack);
        }

        mpModel->setUserArea((std::uintptr_t)this);
        dComIfGp_particle_setShipTail(0x3D, &mPos, NULL, &mScale, 0xFF, &dPa_control_c::mSingleRippleEcallBack);
        dComIfGp_particle_setShipTail(0x3E, &mPos, NULL, &mScale, 0xFF, &dPa_control_c::mSingleRippleEcallBack);
        dComIfGp_particle_setShipTail(0x3F, &mPos, NULL, &mScale, 0xFF, &dPa_control_c::mSingleRippleEcallBack);
        dComIfGp_particle_set(0x40, &mPos, NULL, &mScale, 0xFF, NULL);
    } else {
        dComIfGp_particle_setBombSmoke(0x200A, &mPos);
        dComIfGp_particle_setToonP1(0x2041, &mPos);
        dComIfGp_particle_setP1(0x3C, &mPos);
    }

    dBgS_ObjGndChk gndchk;
    gndchk.SetPos(&mPos);

    int roomNo;
    u8 polyColor;
    f32 y = dComIfG_Bgsp()->GroundCross(&gndchk);
    if (y != -G_CM3D_F_INF) {
        roomNo = dComIfG_Bgsp()->GetRoomId(gndchk);
        polyColor = dComIfG_Bgsp()->GetPolyColor(gndchk);
    } else {
        roomNo = dComIfGp_roomControl_getStayNo();
        polyColor = 0xFF;
    }

    dKy_tevstr_init(&mTevstr, roomNo, polyColor);
    return cPhs_COMPLEATE_e;
}

/* 8023F5B0-8023F5D0       .text dWpillar_Create__FP12kankyo_class */
static cPhs_State dWpillar_Create(kankyo_class* i_this) {
    dWpillar_c* a_this = (dWpillar_c*)i_this;
    return a_this->create();
}

static kankyo_method_class l_dWpillar_Method = {
    (process_method_func)dWpillar_Create,
    (process_method_func)dWpillar_Delete,
    (process_method_func)dWpillar_Execute,
    (process_method_func)dWpillar_IsDelete,
    (process_method_func)dWpillar_Draw,
};

kankyo_process_profile_definition g_profile_WPILLAR = {
    /* Layer ID      */ fpcLy_CURRENT_e,
    /* List ID       */ 8,
    /* List Prio     */ fpcPi_CURRENT_e,
    /* Proc Name     */ fpcNm_WPILLAR_e,
    /* Proc SubMtd   */ &g_fpcLf_Method.base,
    /* Size          */ sizeof(dWpillar_c),
    /* Size Other    */ 0,
    /* Parameters    */ 0,
    /* Leaf SubMtd   */ &g_fopKy_Method,
    /* Draw Prio     */ fpcDwPi_WPILLAR_e,
    /* Kankyo SubMtd */ &l_dWpillar_Method,
};
