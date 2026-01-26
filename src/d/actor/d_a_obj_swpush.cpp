/**
 * d_a_obj_swpush.cpp
 * Object - Yellow switch (activated by stepping on it)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_swpush.h"
#include "d/res/res_kbota_00.h"
#include "d/res/res_hhbot.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_w_sv.h"
#include "d/actor/d_a_player.h"

const char daObjSwpush::Act_c::M_arcname_kbota[] = "Kbota_00";
const char daObjSwpush::Act_c::M_arcname_hhbot[] = "Hhbot";

const daObjSwpush::Attr_c daObjSwpush::Act_c::M_attr[] = {
    {
        /* mHeapSize        */ 0xAE0,
        /* mFlags           */ static_cast<AttrFlag_e>(FLAG_STAY_PRESSED | FLAG_OBEY_SAVE),
        /* mScale           */ 1.0f,
        /* mKbotaResName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mHhbotResName    */ NULL,
        /* mBgArcName       */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mModelArcName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mBtpArcName      */ NULL,
        /* mBgResIndex      */ KBOTA_00_DZB_KBOTA_00,
        /* mModelResIndices */ { KBOTA_00_BDL_KBOTA_00, KBOTA_00_BDL_KBOTA_00 },
        /* mBtpResIndex     */ -1,
        /* mSpring          */ 0.9f,
        /* mSpeedDecay      */ 0.6f,
        /* mPushSpeed0      */ 0.0f,
        /* m34              */ -0.3f,
        /* m38              */ 1,
        /* mMiniPushDelay1  */ 6,
        /* mPushDelay       */ 6,
        /* mMiniPushDelay2  */ 13,
        /* m40              */ 1.0f,
        /* m44              */ 2.5f,
        /* mPauseDuration   */ 10
    },
    {
        /* mHeapSize        */ 0xAE0,
        /* mFlags           */ static_cast<AttrFlag_e>(FLAG_UNK20),
        /* mScale           */ 1.0f,
        /* mKbotaResName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mHhbotResName    */ NULL,
        /* mBgArcName       */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mModelArcName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mBtpArcName      */ NULL,
        /* mBgResIndex      */ KBOTA_00_DZB_KBOTA_00,
        /* mModelResIndices */ { KBOTA_00_BDL_KBOTA_00, KBOTA_00_BDL_KBOTA_00 },
        /* mBtpResIndex     */ -1,
        /* mSpring          */ 0.9f,
        /* mSpeedDecay      */ 0.6f,
        /* mPushSpeed0      */ 0.0f,
        /* m34              */ -0.3f,
        /* m38              */ 1,
        /* mMiniPushDelay1  */ 6,
        /* mPushDelay       */ 6,
        /* mMiniPushDelay2  */ 13,
        /* m40              */ 1.0f,
        /* m44              */ 2.5f,
        /* mPauseDuration   */ 10
    },
    {
        /* mHeapSize        */ 0xAE0,
        /* mFlags           */ static_cast<AttrFlag_e>(FLAG_ON_IS_UP | FLAG_STAY_PRESSED | FLAG_OBEY_SAVE),
        /* mScale           */ 1.0f,
        /* mKbotaResName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mHhbotResName    */ NULL,
        /* mBgArcName       */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mModelArcName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mBtpArcName      */ NULL,
        /* mBgResIndex      */ KBOTA_00_DZB_KBOTA_00,
        /* mModelResIndices */ { KBOTA_00_BDL_KBOTA_00, KBOTA_00_BDL_KBOTA_00 },
        /* mBtpResIndex     */ -1,
        /* mSpring          */ 0.9f,
        /* mSpeedDecay      */ 0.6f,
        /* mPushSpeed0      */ 0.0f,
        /* m34              */ -0.3f,
        /* m38              */ 1,
        /* mMiniPushDelay1  */ 6,
        /* mPushDelay       */ 6,
        /* mMiniPushDelay2  */ 13,
        /* m40              */ 1.0f,
        /* m44              */ 2.5f,
        /* mPauseDuration   */ 10
    },
    {
        /* mHeapSize        */ 0x8000,
        /* mFlags           */ static_cast<AttrFlag_e>(FLAG_REQ_HEAVY | FLAG_STAY_PRESSED | FLAG_OBEY_SAVE),
        /* mScale           */ 1.5f,
        /* mKbotaResName    */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mHhbotResName    */ daObjSwpush::Act_c::M_arcname_hhbot,
        /* mBgArcName       */ daObjSwpush::Act_c::M_arcname_kbota,
        /* mModelArcName    */ daObjSwpush::Act_c::M_arcname_hhbot,
        /* mBtpArcName      */ NULL,
        /* mBgResIndex      */ KBOTA_00_DZB_KBOTA_00,
        /* mModelResIndices */ { HHBOT_BDL_HHBOT1, HHBOT_BDL_HHBOT1 },
        /* mBtpResIndex     */ 0xFFFF,
        /* mSpring          */ 0.93f,
        /* mSpeedDecay      */ 0.42f,
        /* mPushSpeed0      */ 0.0f,
        /* m34              */ 0.0f,
        /* m38              */ 4,
        /* mMiniPushDelay1  */ 4,
        /* mPushDelay       */ 15,
        /* mMiniPushDelay2  */ 4,
        /* m40              */ 1.0f,
        /* m44              */ 2.5f,
        /* mPauseDuration   */ 10
    }
};

const u8 daObjSwpush::Act_c::M_op_vtx[4] = { 6, 10, 11, 7 };

/* 000000EC-0000011C       .text prmZ_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::prmZ_init() {
    if (mPrmZInit) {
        return;
    }
    mPrmZ = home.angle.z;
    mPrmZInit = true;
    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;
}

/* 0000011C-0000019C       .text is_switch2__Q211daObjSwpush5Act_cCFv */
bool daObjSwpush::Act_c::is_switch2() const {
    s32 swSave2 = prmZ_get_swSave2();

    if (0xFF == swSave2) {
        return false;
    } else {
        return fopAcM_isSwitch(const_cast<Act_c*>(this), swSave2);
    }
}

/* 0000019C-000001C0       .text solidHeapCB__Q211daObjSwpush5Act_cFP10fopAc_ac_c */
BOOL daObjSwpush::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjSwpush::Act_c*>(i_this)->create_heap();
}

/* 000001C0-00000478       .text create_heap__Q211daObjSwpush5Act_cFv */
bool daObjSwpush::Act_c::create_heap() {
    bool rt = false;

    J3DModelData* model_data = (J3DModelData*) dComIfG_getObjectRes(attr().mModelArcName, attr().mModelResIndices[prm_get_mdl()]);
    JUT_ASSERT(0x205, model_data != NULL);

    u32 flag = 0x11000022;
    if (attr().mBtpArcName != NULL) {
        flag |= 0x20000;
    }
    mpModel = mDoExt_J3DModel__create(model_data, 0x80000, flag);
    if (mpModel) {
        model_data->getJointNodePointer(1)->setCallBack(jnodeCB);
        mpModel->setUserArea((u32) this);
    }

    BOOL btp_success = TRUE;
    if (attr().mBtpArcName != NULL) {
        J3DAnmTexPattern* btp_data = (J3DAnmTexPattern*) dComIfG_getObjectRes(attr().mBtpArcName, attr().mBtpResIndex);
        JUT_ASSERT(0x21E, btp_data != NULL);
        btp_success = mBtpAnm.init(model_data, btp_data, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE);
    }

    cBgD_t* bg_data = (cBgD_t*) dComIfG_getObjectRes(attr().mBgArcName, attr().mBgResIndex);
    bool bg_success = false;
    JUT_ASSERT(0x22B, bg_data != NULL);
    mpBgW = new dBgWSv();
    if (mpBgW != NULL && !mpBgW->Set(bg_data, 0)) {
        bg_success = true;
    }

    if (mpModel != NULL && btp_success) {
        if (mpBgW != NULL && bg_success) {
            rt = true;
        }
    }
    if (!rt) {
        mpBgW = NULL;
    }
    return rt;
}

/* 00000478-0000051C       .text create_res_load__Q211daObjSwpush5Act_cFv */
cPhs_State daObjSwpush::Act_c::create_res_load() {
    cPhs_State rt = attr().mKbotaResName != NULL ? dComIfG_resLoad(&mKbotaPhs, attr().mKbotaResName) : cPhs_COMPLEATE_e;
    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }
    rt = attr().mHhbotResName != NULL ? dComIfG_resLoad(&mHhbotPhs, attr().mHhbotResName) : cPhs_COMPLEATE_e;
    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }
    return cPhs_COMPLEATE_e;
}

/* 0000051C-000008C4       .text Mthd_Create__Q211daObjSwpush5Act_cFv */
cPhs_State daObjSwpush::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, daObjSwpush::Act_c);

    prmZ_init();
    mType = prm_get_type();

    cPhs_State phase_state = create_res_load();
    if (phase_state == cPhs_COMPLEATE_e) {
        scale.x *= attr().mScale;
        scale.z *= attr().mScale;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, attr().mHeapSize)) {
            if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                phase_state = cPhs_ERROR_e;
            } else {
                mDoMtx_stack_c::transS(current.pos);
                mDoMtx_stack_c::ZXYrotM(shape_angle);
                mDoMtx_stack_c::scaleM(scale);
                mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
                mpBgW->ClrNoCalcVtx();
                mpBgW->SetBaseMtxP(&mMtx);
                mpBgW->GlobalVtx();
                mpBgW->SetBaseMtxP(NULL);
                mpBgW->SetNoCalcVtx();

                m2D4 = mpBgW->GetVtxTbl()[M_op_vtx[0]].y;
                mpBgW->SetRideCallback(rideCB);
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                init_mtx();
                fopAcM_setCullSizeBox(this, attr().mScale * -60.0f, -2.0f, attr().mScale * -60.0f, attr().mScale * 60.0f, 39.0f, attr().mScale * 60.0f);

                mVibTimer = 0;
                mRidingMode = 0;
                mPrevRiding = false;
                mMiniPushTimer = 0;
                mMiniPushFlg = false;
                mHeavyRiding = false;
                mPrevHeavyRiding = 0;
                mPushTimer = 0;
                mPushFlg = false;
                mSpeed = 0.0f;
                m324 = 0;
                m328 = 0.0f;

                set_btp_frame();

                bool is_toggle = cLib_checkBit(attr().mFlags, FLAG_IS_TOGGLE);
                bool on_is_up = cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP);
                bool flg20 = cLib_checkBit(attr().mFlags, FLAG_UNK20);
                bool is_sw = is_switch();
                bool is_sw2 = is_switch2();

                if (
                    (
                        is_toggle ||
                        (!is_sw && !on_is_up) ||
                        (is_sw && on_is_up)
                    ) && 
                    (!flg20 || !is_sw2)
                ) {
                    mTargetHFrac = 1.0f;
                    mCurHFrac = 1.0f;
                    m31C = 0.0f;
                    m320 = 1.0f;
                    m32C = 1.0f;
                    mTopPos = 0.0f;
                    mode_upper_init();
                } else {
                    mTargetHFrac = 0.0f;
                    mCurHFrac = 0.0f;
                    m31C = -35.5f;
                    m320 = 0.0f;
                    m32C = 0.0f;
                    mTopPos = -35.5f;
                    mode_lower_init();
                }

                mEventID = dComIfGp_evmng_getEventIdx(NULL, prm_get_evId());
                demo_non_init();
            }
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00000968-000009F8       .text Mthd_Delete__Q211daObjSwpush5Act_cFv */
BOOL daObjSwpush::Act_c::Mthd_Delete() {
    dComIfG_Bgsp()->Release(mpBgW);
    if (attr().mKbotaResName != NULL) {
        dComIfG_resDelete(&mKbotaPhs, attr().mKbotaResName);
    }
    if (attr().mHhbotResName != NULL) {
        dComIfG_resDelete(&mHhbotPhs, attr().mHhbotResName);
    }
    return TRUE;
}

/* 000009F8-00000A64       .text set_mtx__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000A64-00000AA0       .text init_mtx__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000AA0-00000B34       .text set_btp_frame__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::set_btp_frame() {
    if (attr().mBtpArcName != NULL) {
        mBtpAnm.setFrame(is_switch() ? 1.0f : 0.0f);
    }
}

/* 00000B34-00000EDC       .text rideCB__Q211daObjSwpush5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjSwpush::Act_c::rideCB(dBgW* bgw, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    if (fopAcM_CheckStatus(i_pt, fopAcStts_FREEZE_e)) {
        static cXyz no_push_vec[4] = {
            cXyz(-1.0f, 0.0f, -1.0f),
            cXyz(-1.0f, 0.0f, 1.0f),
            cXyz(1.0f, 0.0f,  1.0f),
            cXyz(1.0f, 0.0f, -1.0f)
        };
        
        static const s8 tri_id[2][3] = {
            {0, 1, 2},
            {3, 0, 2}
        };

        daObjSwpush::Act_c *i_this = (daObjSwpush::Act_c*)i_ac;
        cBgD_Vtx_t* vtx_tbl = i_this->mpBgW->GetVtxTbl();
    
        cM3dGTri tri;
        cXyz vecs[4];

        f32 fscale = i_this->mPrevRiding ? i_this->attr().m44 : i_this->attr().m40;
        mDoMtx_stack_c::push();
        mDoMtx_stack_c::YrotS(i_this->shape_angle.y);
        mDoMtx_stack_c::scaleM(fscale, fscale, fscale);

        for (s32 i = 0; i < 4; i++) {
            vecs[i].set(vtx_tbl[M_op_vtx[i]]);
            cXyz out;
            mDoMtx_stack_c::multVec(&no_push_vec[i], &out);
            vecs[i] += out;
        }

        mDoMtx_stack_c::pop();
        for (s32 i = 0; i < 2; i++) {
            tri.setPos(&vecs[tri_id[i][0]], &vecs[tri_id[i][1]], &vecs[tri_id[i][2]]);
            if (tri.crossY(&i_pt->current.pos)) {
                if (fopAcM_CheckStatus(i_pt, fopAcStts_UNK8000000_e)) {
                    i_this->mRidingMode = 2;
                } else {
                    i_this->mRidingMode = 1;
                }

                bool is_player = fopAcM_GetProfName(i_pt) == PROC_PLAYER;
                if (is_player) {
                    i_this->mVibTimer = 4;
                }
                if (is_player) {
                    if (((daPy_py_c*)i_pt)->checkEquipHeavyBoots()) {
                        i_this->mHeavyRiding = true;
                    }
                }
                break;
            }
        }
    }
}

/* 00000FBC-0000105C       .text jnodeCB__Q211daObjSwpush5Act_cFP7J3DNodei */
BOOL daObjSwpush::Act_c::jnodeCB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = (J3DModel*) j3dSys.getModel();
        daObjSwpush::Act_c *i_this = (daObjSwpush::Act_c*) model->getUserArea();
        J3DJoint* joint = (J3DJoint*) node;
        u16 jntNo = joint->getJntNo();

        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::transM(i_this->m31C, 0.0f, 0.0f);
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 0000105C-00001170       .text calc_top_pos__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::calc_top_pos() {
    f32 decay = attr().mSpeedDecay;
    mSpeed -= (mCurHFrac - mTargetHFrac) * attr().mSpring;
    mSpeed -= mSpeed * decay;
    mCurHFrac += mSpeed;
    m31C = (1.0f - mCurHFrac) * -35.5f;
    m31C = cLib_minMaxLimit(m31C, -36.5f, 1.0f);

    if (m324 > 0) {
        if (--m324 == 0) {
            m320 = m328;
        }
    }
    if (mMode == MODE_UPPER) {
        m32C = mCurHFrac;
    } else {
        m32C = m320;
    }
    mTopPos = (1.0f - m32C) * -35.5f;
    if (mTopPos < m31C) {
        mTopPos = m31C;
    }
}

/* 00001170-0000117C       .text top_bg_aim_req__Q211daObjSwpush5Act_cFfs */
void daObjSwpush::Act_c::top_bg_aim_req(f32 param_1, s16 param_2) {
    m328 = param_1;
    m324 = param_2;
}

/* 0000117C-0000130C       .text set_push_flag__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::set_push_flag() {
    if (mVibTimer != 0) {
        mVibTimer--;
    }
    if (mMiniPushFlg) {
        if (mRidingMode != 0) {
            if (mRidingMode == 2) {
                mMiniPushTimer = attr().mMiniPushDelay2;
            } else {
                mMiniPushTimer = attr().mMiniPushDelay1;
            }
        } else {
            if (--mMiniPushTimer <= 0) {
                mMiniPushFlg = false;
            }
        }
    } else {
        if (mRidingMode != 0) {
            if (++mMiniPushTimer >= attr().mMiniPushDelay1) {
                mMiniPushFlg = true;
            }
        } else {
            mMiniPushTimer = 0;
        }
    }

    if (mPushFlg) {
        if (mHeavyRiding) {
            mPushTimer = attr().mPushDelay;
        } else {
            if (--mPushTimer <= 0) {
                mPushFlg = false;
            }
        }
    } else {
        if (mHeavyRiding) {
            if (++mPushTimer >= attr().mPushDelay) {
                mPushFlg = true;
            }
        } else {
            mPushTimer = 0;
        }
    }
}

/* 0000130C-0000132C       .text mode_upper_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_upper_init() {
    mMode = MODE_UPPER;
    mTargetHFrac = 1.0f;
    mChangingState = false;
    mDebounceTimer = 0;
}

/* 0000132C-00001508       .text mode_upper__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_upper() {
    bool bVar4 = false;
    bool bVar3 = false;
    bool pressing = false;
    f32 height = 1.0f;
    if (mMiniPushFlg) {
        if (cLib_checkBit(attr().mFlags, FLAG_REQ_HEAVY)) {
            if (mPushFlg) {
                pressing = true;
            } else {
                height = 0.9f;
            }
        } else {
            pressing = true;
        }
    }

    if (!cLib_checkBit(attr().mFlags, FLAG_REQ_HEAVY) && mDebounceTimer <= 0 && mRidingMode != 0 && !mPrevRiding) {
        mSpeed = attr().m34;
        mDebounceTimer = 30;
        bVar4 = true;
    } else if (mDebounceTimer > 0) {
        mDebounceTimer--;
    }

    bool is_sw = is_switch();
    if (pressing ||
        (cLib_checkBit(attr().mFlags, FLAG_OBEY_SAVE) &&
            (
                (is_sw && !cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP)) ||
                (!is_sw && cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP))
            )
        )
    ) {
        if (pressing) {
            mChangingState = true;
        }
        bVar3 = true;
        mode_u_l_init();
    } else {
        mTargetHFrac = height;
        top_bg_aim_req(height, 1);
    }
    if (bVar3) {
        demo_reqSw_init();
    } else if (bVar4) {
        demo_reqPause_init();
    }
}

/* 00001508-00001568       .text mode_u_l_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_u_l_init() {
    mMode = MODE_U_L;
    mTargetHFrac = 0.0f;
    mSpeed = attr().mPushSpeed0;
    top_bg_aim_req(0.0f, attr().m38);
}

/* 00001568-000016DC       .text mode_u_l__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_u_l() {
    if (mCurHFrac <= 0.0f) {
        if (mChangingState) {
            if (cLib_checkBit(attr().mFlags, FLAG_IS_TOGGLE)) {
                rev_switch();
            } else {
                if (cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP)) {
                    off_switch();
                } else {
                    on_switch();
                }
            } 
            if (mVibTimer != 0) {
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
        fopAcM_seStart(this, JA_SE_OBJ_FOOT_SW_ON, 0);
        mode_lower_init();
    }
}

/* 000016DC-000016FC       .text mode_lower_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_lower_init() {
    mMode = MODE_LOWER;
    mTargetHFrac = 0.0f;
    mChangingState = 0;
}

/* 000016FC-00001898       .text mode_lower__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_lower() {
    bool pressing = false;
    if (mMiniPushFlg) {
        if (cLib_checkBit(attr().mFlags, FLAG_REQ_HEAVY)) {
            if (mPushFlg) {
                pressing = true;
            }
        } else {
            pressing = true;
        }
    }
    bool is_sw = is_switch();
    bool is_sw2 = is_switch2();
    bool obey_save = cLib_checkBit(attr().mFlags, FLAG_OBEY_SAVE);
    bool stay_pressed = cLib_checkBit(attr().mFlags, FLAG_STAY_PRESSED);
    bool is_toggle = cLib_checkBit(attr().mFlags, FLAG_IS_TOGGLE);
    bool on_is_up = cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP);
    bool flg20 = cLib_checkBit(attr().mFlags, FLAG_UNK20);

    bool pop_back_up = !stay_pressed && !pressing;
    bool match_state_up = obey_save &&
        ((!is_sw && !on_is_up) || (is_sw && on_is_up)) &&
        !pressing;

    bool bVar5 = !(flg20 && is_sw2);
    if (pop_back_up || match_state_up) {
        if (bVar5) {
            if (pop_back_up && !is_toggle && !pressing) {
                mChangingState = true;
            }
            demo_reqSw_init();
            mode_l_u_init();
        }
    }
}

/* 00001898-000018D0       .text mode_l_u_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_l_u_init() {
    mMode = MODE_L_U;
    mTargetHFrac = 1.0f;
    top_bg_aim_req(1.0f, 1);
}

/* 000018D0-00001990       .text mode_l_u__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::mode_l_u() {
    if (mCurHFrac >= 1.0f) {
        if (mChangingState) {
            if (cLib_checkBit(attr().mFlags, FLAG_ON_IS_UP)) {
                on_switch();
            } else {
                off_switch();
            }
        }
        mode_upper_init();
    }
}

/* 00001990-0000199C       .text demo_non_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_non_init() {
    mDemoMode = DEMO_MODE_NON;
}

/* 0000199C-000019A0       .text demo_non__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_non() {
}

/* 000019A0-000019F8       .text demo_reqPause_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_reqPause_init() {
    if (mDemoMode == DEMO_MODE_NON) {
        mDemoMode = DEMO_MODE_REQ_PAUSE;
        fopAcM_orderPotentialEvent(this, dEvtFlag_STAFF_ALL_e, 0, 0);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
}

/* 000019F8-00001A2C       .text demo_reqPause__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_reqPause() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        demo_runPause_init();
    } else {
        demo_non_init();
    }
}

/* 00001A2C-00001A54       .text demo_runPause_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_runPause_init() {
    mDemoMode = DEMO_MODE_RUN_PAUSE;
    mPauseTimer = attr().mPauseDuration;
}

/* 00001A54-00001AA0       .text demo_runPause__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_runPause() {
    --mPauseTimer;
    if (mPauseTimer <= 0) {
        dComIfGp_event_reset();
        demo_non_init();
    }
}

/* 00001AA0-00001AF8       .text demo_stop_puase__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_stop_puase() {
    if (mDemoMode == DEMO_MODE_REQ_PAUSE) {
        demo_reqPause();
    }
    if (mDemoMode == DEMO_MODE_RUN_PAUSE) {
        dComIfGp_event_reset();
    }
}

/* 00001AF8-00001BA4       .text demo_reqSw_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_reqSw_init() {
    if (dComIfGp_evmng_existence(mEventID) && 
        (
            mDemoMode == DEMO_MODE_NON ||
            mDemoMode == DEMO_MODE_REQ_PAUSE ||
            mDemoMode == DEMO_MODE_RUN_PAUSE
        )
    ){
        demo_stop_puase();
        mDemoMode = DEMO_MODE_REQ_SW;
        fopAcM_orderOtherEventId(this, mEventID, prm_get_evId());
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
}

/* 00001BA4-00001C18       .text demo_reqSw__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_reqSw() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        demo_runSw_init();
    } else {
        fopAcM_orderOtherEventId(this, mEventID, prm_get_evId());
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
}

/* 00001C18-00001C24       .text demo_runSw_init__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_runSw_init() {
    mDemoMode = DEMO_MODE_RUN_SW;
}

/* 00001C24-00001C84       .text demo_runSw__Q211daObjSwpush5Act_cFv */
void daObjSwpush::Act_c::demo_runSw() {
    if (dComIfGp_evmng_endCheck(mEventID)) {
        dComIfGp_event_reset();
        demo_non_init();
    }
}

/* 00001C84-00001F14       .text Mthd_Execute__Q211daObjSwpush5Act_cFv */
BOOL daObjSwpush::Act_c::Mthd_Execute() {
    typedef void (daObjSwpush::Act_c::*procFunc)();

    static procFunc demo_proc[] = {
        &daObjSwpush::Act_c::demo_non,
        &daObjSwpush::Act_c::demo_reqPause,
        &daObjSwpush::Act_c::demo_runPause,
        &daObjSwpush::Act_c::demo_reqSw,
        &daObjSwpush::Act_c::demo_runSw,
    };
    (this->*demo_proc[mDemoMode])();

    set_push_flag();

    static procFunc mode_proc[] = {
        &daObjSwpush::Act_c::mode_upper,
        &daObjSwpush::Act_c::mode_u_l,
        &daObjSwpush::Act_c::mode_lower,
        &daObjSwpush::Act_c::mode_l_u,
    };
    (this->*mode_proc[mMode])();

    calc_top_pos();
    mPrevRiding = mRidingMode != 0;
    mPrevHeavyRiding = mHeavyRiding;
    mRidingMode = 0;
    mHeavyRiding = false;
    set_mtx();
    mpBgW->CopyBackVtx();

    cBgD_Vtx_t* vtx_tbl = mpBgW->GetVtxTbl();
    int i_max = mpBgW->GetVtxNum();

    for (int i = 0; i < 4; i++) {
        JUT_ASSERT(0x578, M_op_vtx[i] < i_max)
        vtx_tbl[M_op_vtx[i]].y = m2D4 + mTopPos;
    }
    mpBgW->Move();
    eyePos.x = current.pos.x;
    eyePos.y = current.pos.y + m31C - -35.5f;
    eyePos.z = current.pos.z;
    set_btp_frame();
    return TRUE;
}

/* 00001F14-00001FF8       .text Mthd_Draw__Q211daObjSwpush5Act_cFv */
BOOL daObjSwpush::Act_c::Mthd_Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    if (attr().mBtpArcName != NULL) {
        mBtpAnm.entry(mpModel->getModelData());
    }
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

namespace daObjSwpush {
namespace {
/* 00001FF8-00002018       .text Mthd_Create__Q211daObjSwpush28@unnamed@d_a_obj_swpush_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Create();
}

/* 00002018-00002038       .text Mthd_Delete__Q211daObjSwpush28@unnamed@d_a_obj_swpush_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Delete();
}

/* 00002038-00002058       .text Mthd_Execute__Q211daObjSwpush28@unnamed@d_a_obj_swpush_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Execute();
}

/* 00002058-00002078       .text Mthd_Draw__Q211daObjSwpush28@unnamed@d_a_obj_swpush_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Draw();
}

/* 00002078-00002080       .text Mthd_IsDelete__Q211daObjSwpush28@unnamed@d_a_obj_swpush_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSwpush

actor_process_profile_definition g_profile_Obj_Swpush = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Swpush,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwpush::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Swpush,
    /* Actor SubMtd */ &daObjSwpush::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
