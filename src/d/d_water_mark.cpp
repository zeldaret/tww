#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_water_mark.h"
#include "m_Do/m_Do_lib.h"

s16 dWaterMark_c::m_circle_cnt;

s16 dWaterMark_c::m_player_foot_now_id;

dBgS_ObjGndChk dWaterMark_c::m_ground_check;

BOOL dWaterMark_c::draw() {
    if (mDoLib_clipper::clip(j3dSys.getViewMtx(), mPos, mScale.x * 50.0f)) {
        return TRUE;
    }

    J3DModelData* modelData = mpModel->getModelData();
    mBrk.entry(modelData, mBrk.getFrame());
    mBtp.entry(mpModel->getModelData(), mParam);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

/* 8023DB48-8023DBF8       .text dWaterMark_Draw__FP12dWaterMark_c */
static BOOL dWaterMark_Draw(dWaterMark_c* i_this) {
    return i_this->draw();
}

/* 8023DBF8-8023DE2C       .text setMatrix__12dWaterMark_cFv */
BOOL dWaterMark_c::setMatrix() {    
    cXyz chk_pos(mPos.x, mPos.y + 10.0f, mPos.z);
    m_ground_check.SetPos(&chk_pos);

    mPos.y = dComIfG_Bgsp()->GroundCross(&m_ground_check);
    if (mPos.y != -G_CM3D_F_INF) {
        cM3dGPla* tri = dComIfG_Bgsp()->GetTriPla(m_ground_check.GetBgIndex(), m_ground_check.GetPolyIndex());
        s16 tri_angle = cM_atan2s(tri->mNormal.x, tri->mNormal.z) - field_0x12e;
        f32 norm_xz_mag = tri->mNormal.absXZ();

        mDoMtx_stack_c::transS(mPos.x, mPos.y + 0.1f, mPos.z);
        mDoMtx_stack_c::ZXYrotM(
            cM_atan2s(norm_xz_mag * cM_scos(tri_angle), tri->mNormal.y),
            field_0x12e,
            cM_atan2s(norm_xz_mag * -cM_ssin(tri_angle), tri->mNormal.y)
        );
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

        bool is_move_bg = dComIfG_Bgsp()->ChkMoveBG(m_ground_check);
        if (is_move_bg) {
            field_0x12c = 1;
        } else {
            field_0x12c = 0;
        }
    } else {
        return FALSE;
    }

    return TRUE;
}

BOOL dWaterMark_c::execute() {
    if (field_0x134 != -1) {
        if (field_0x130 < field_0x132) {
            if (field_0x130 <= dWaterMark_c::m_player_foot_now_id && field_0x132 > dWaterMark_c::m_player_foot_now_id) {
                field_0x134 = -1;
            }
        } else {
            if (field_0x130 <= dWaterMark_c::m_player_foot_now_id || field_0x132 > dWaterMark_c::m_player_foot_now_id) {
                field_0x134 = -1;
            }
        }
    }

    if (field_0x134 == -1) {
        mBrk.play();
    }
    
    if (mBrk.isStop()) {
        fopKyM_Delete(this);
    } else if (field_0x12c == 1 && !setMatrix()) {
        fopKyM_Delete(this);
    }

    return TRUE;
}

/* 8023DE2C-8023DF24       .text dWaterMark_Execute__FP12dWaterMark_c */
static BOOL dWaterMark_Execute(dWaterMark_c* i_this) {   
    return i_this->execute();
}

/* 8023DF24-8023DF2C       .text dWaterMark_IsDelete__FP12dWaterMark_c */
static BOOL dWaterMark_IsDelete(dWaterMark_c* i_this) {
    return TRUE;
}

BOOL dWaterMark_c::wm_delete() {
    if (mpHeap != NULL) {
        mDoExt_destroySolidHeap(mpHeap);
    }

    if ((int)mParam == 1) {
        dWaterMark_c::m_circle_cnt--;
    }

    return TRUE;
}

/* 8023DF2C-8023DF80       .text dWaterMark_Delete__FP12dWaterMark_c */
static BOOL dWaterMark_Delete(dWaterMark_c* i_this) {
    return i_this->wm_delete();
}

/* 8023DF80-8023DFA0       .text dWaterMark_Create__FP12kankyo_class */
static cPhs_State dWaterMark_Create(kankyo_class* kankyo) {
    dWaterMark_c* i_this = (dWaterMark_c*)kankyo;
    return i_this->create();
}

/* 8023DFA0-8023E29C       .text create__12dWaterMark_cFv */
cPhs_State dWaterMark_c::create() {
    new (this) dWaterMark_c();
    
    field_0x12e = mParam >> 0x10;
    mParam &= 0xFFFF;

    if ((int)mParam != 0 && (int)mParam != 1 && (int)mParam != 2) {
        return cPhs_ERROR_e;
    }

    if ((int)mParam == 1 && ++m_circle_cnt > 10) {
        return cPhs_ERROR_e;
    }

    JKRSolidHeap* heap = mDoExt_createSolidHeapFromGameToCurrent(0x12A0, 0x20);
    mpHeap = heap;

    BOOL is_anm_init;
    if (mpHeap != NULL) {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BDL_MPA_SIMI_e));
        JUT_ASSERT(304, modelData != NULL);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020022);

        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BRK_MPA_SIMI_e);
        int brk_rt = mBrk.init(modelData, brk, TRUE, J3DFrameCtrl::EMode_NONE);

        J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Always", dRes_INDEX_ALWAYS_BTP_MPA_SIMI_e);
        int btp_rt = mBtp.init(modelData, btp, FALSE, J3DFrameCtrl::EMode_NONE);
        
        is_anm_init = (brk_rt & btp_rt);

        mDoExt_restoreCurrentHeap();
        mDoExt_adjustSolidHeap(mpHeap);
    } else {
        return cPhs_ERROR_e;
    }

    if (mpModel == NULL || !is_anm_init) {
        return cPhs_ERROR_e;
    }

    mpModel->setBaseScale(mScale);

    if (!setMatrix()) {
        return cPhs_ERROR_e;
    }

    if ((int)mParam == 2) {
        field_0x134 = m_player_foot_now_id;
        m_player_foot_now_id++;
        if (m_player_foot_now_id == 40) {
            m_player_foot_now_id = 0;
        }
    
        field_0x130 = field_0x134 + 20;
        if (field_0x130 >= 40) {
            field_0x130 -= 40;
        }
    
        field_0x132 = field_0x130 + 20;
        if (field_0x132 >= 40) {
            field_0x132 -= 40;
        }
    
        mParam = 0;
    } else {
        field_0x134 = -1;
    }

    return cPhs_COMPLEATE_e;
}

static kankyo_method_class l_dWaterMark_Method = {
    (process_method_func)dWaterMark_Create,
    (process_method_func)dWaterMark_Delete,
    (process_method_func)dWaterMark_Execute,
    (process_method_func)dWaterMark_IsDelete,
    (process_method_func)dWaterMark_Draw,
};

kankyo_process_profile_definition g_profile_WATER_MARK = {
    /* Layer ID      */ fpcLy_CURRENT_e,
    /* List ID       */ 9,
    /* List Prio     */ fpcPi_CURRENT_e,
    /* Proc Name     */ fpcNm_WATER_MARK_e,
    /* Proc SubMtd   */ &g_fpcLf_Method.base,
    /* Size          */ sizeof(dWaterMark_c),
    /* Size Other    */ 0,
    /* Parameters    */ 0,
    /* Leaf SubMtd   */ &g_fopKy_Method,
    /* Draw Prio     */ fpcDwPi_WATER_MARK_e,
    /* Kankyo SubMtd */ &l_dWaterMark_Method,
};
