//
// Generated by dtk
// Translation Unit: d_a_obj_paper.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "d/d_procname.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_a_obj.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "dolphin/types.h"

namespace daObjPaper {
    namespace {
        struct L_attr_entry {
            char* ResName;
            int mHeapSize;
            short mModelId;
            short mEyeOffset;
            short mAttentionOffset;
            short mCullSphereRadius;
            short mCullSphereYOffset;

            s8 mAttentionDist1;
            s8 mAttentionDist2;

            bool TevType;
            short mHasCc;

            short mColCylinderRadius;
            short mColCylinderHeight;

            const char* getResName() const { return ResName; }
            int getHeapSize() const { return mHeapSize; }
            int getModelId() const { return mModelId; }
            int getTevType() const { return TevType == 0 ? TEV_TYPE_BG0 : TEV_TYPE_ACTOR; }
        };

        static const L_attr_entry L_attr[3] = {
            { "Opaper", 0x04C0, 3, 0x00, 0x28, 0x28, 0x00, 0x1D, 0x1E, 0x100, 0x00, 0x00 },
            { "Ppos",   0x04C0, 3, 0x00, 0x32, 0x3C, 0x00, 0x1F, 0x20, 0x100, 0x00, 0x00 },
            { "Piwa",   0x04C0, 3, 0x3C, 0x82, 0x50, 0x3C, 0x1D, 0x1E, 0x000, 0x37, 0x73 }
        };

        inline static const char* getEntryResName(int idx) { return L_attr[idx].getResName(); }
        inline static int getEntryModelId(int idx) { return L_attr[idx].getModelId(); }
    }

    static const dCcD_SrcCyl M_cyl_src = {
        0,
        0,
        0,
        0,
        0xFF1DFEFF,
        0xF,
        0x79,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        3,
        0,
        
        // Cylinder
        0.0f, // X
        0.0f, // Y
        0.0f, // Z
        0.0f, // Radius
        0.0f, // Height
    };

    enum Act_Mode_e {
        ActMode_WAIT_e,
        ActMode_TALKBEGIN_e,
        ActMode_GETMSG_e,
        ActMode_TALKWAIT_e,
    };

    class Act_c : public fopAc_ac_c {
    public:
        static int solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        s32 _create();
        bool _delete();

        void mode_wait_init();
        void mode_wait();

        void mode_talk0_init();
        void mode_talk0();
        
        void mode_talk1_init();
        void mode_talk1();

        void mode_talk2_init();
        void mode_talk2();

        void set_mtx();
        void init_mtx();

        void damage_cc_proc();
        bool _execute();
        bool _draw();

    public:
        /* 0x0290 */ request_of_phase_process_class mPhs;
        /* 0x0298 */ J3DModel* mpModel;

        /* 0x029C */ dCcD_Cyl mCylinderCol;
        /* 0x03CC */ dCcD_Stts mColStatus;
        /* 0x0408 */ bool mbHasCc;

        /* 0x040C */ int mMode;
        /* 0x0410 */ int mMsgId;
        /* 0x0414 */ msg_class* mpMsg;
        /* 0x0418 */ int mType;

        int getMsgId() const { return mMsgId; }

        enum Prm_e {
            PRM_MSG_ID_W = 0x10,
            PRM_MSG_ID_S = 0x00,

            PRM_TYPE_W = 0x04,
            PRM_TYPE_S = 0x10,
        };
    };

    /* 00000078-0000009C       .text solidHeapCB__Q210daObjPaper5Act_cFP10fopAc_ac_c */
    int Act_c::solidHeapCB(fopAc_ac_c* i_this) {
        return static_cast<Act_c*>(i_this)->create_heap();
    }

    /* 0000009C-00000170       .text create_heap__Q210daObjPaper5Act_cFv */
    bool Act_c::create_heap() {
        /* Nonmatching */
        bool val = false;

        const L_attr_entry* f = &L_attr[mType];
        J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(L_attr[mType].getResName(), L_attr[mType].getModelId());

        JUT_ASSERT(0x13E, mdl_data != 0);

        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000022);
        val = mpModel != 0;

        return val;
    }

    /* 00000170-000004E0       .text _create__Q210daObjPaper5Act_cFv */
    s32 Act_c::_create() {
        /* Nonmatching */
        const L_attr_entry* attributes = L_attr;

        fopAcM_SetupActor(this, Act_c);
        
        mType = daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S);

        s32 result = dComIfG_resLoad(&mPhs, attributes[mType].getResName());

        if (result == cPhs_COMPLEATE_e) {
            s32 solidHeapStatus = fopAcM_entrySolidHeap(this, (heapCallbackFunc)solidHeapCB, attributes[mType].getHeapSize());

            if (solidHeapStatus & 0xFF == 0) {
                result = cPhs_ERROR_e;
            }
            else {
                mEyePos.y += attributes[mType].mEyeOffset;

                mAttentionInfo.mPosition.y += attributes[mType].mAttentionOffset;
                mAttentionInfo.mDistances[1] = attributes[mType].mAttentionDist1;
                mAttentionInfo.mDistances[3] = attributes[mType].mAttentionDist2;
                mAttentionInfo.setFlag(0x4000000A);

                mMsgId = -1;

                if (mType == 2) {
                    mStatus &= 0xFFFFFFC0 | 0x38;
                }

                if (attributes[mType].mHasCc == 0) {
                    mbHasCc = false;
                }
                else {
                    mbHasCc = true;

                    mColStatus.Init(0xFF, 0xFF, this);    
                    mCylinderCol.Set(M_cyl_src);

                    mCylinderCol.SetStts(&mColStatus);

                    mCylinderCol.SetR(attributes[mType].mColCylinderRadius);
                    mCylinderCol.SetH(attributes[mType].mColCylinderHeight);
                }

                fopAcM_setCullSizeSphere(this, 0.0f, attributes[mType].mCullSphereYOffset, 0.0f, attributes[mType].mCullSphereRadius);
                mCullMtx = mpModel->mBaseTransformMtx;

                init_mtx();
                mode_wait_init();
            }
        }

        return result;
    }

    /* 000006F4-00000730       .text _delete__Q210daObjPaper5Act_cFv */
    bool daObjPaper::Act_c::_delete() {
        dComIfG_resDelete(&mPhs, L_attr[mType].getResName());
        return TRUE;
    }

    /* 00000730-00000748       .text mode_wait_init__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_wait_init() {
        mStatus |= fopAcStts_NOEXEC_e;
        mMode = ActMode_WAIT_e;
    }

    /* 00000748-00000784       .text mode_wait__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_wait() {
        if (mEvtInfo.mCommand == dEvtCmd_INTALK_e) {
            mode_talk0_init();
        }
        else {
            mEvtInfo.mCondition |= dEvtCnd_CANTALK_e;
        }
    }

    /* 00000784-000007A4       .text mode_talk0_init__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk0_init() {
        mStatus &= ~fopAcStts_NOEXEC_e;
        mMsgId = -1;
        mMode = ActMode_TALKBEGIN_e;
    }

    /* 000007A4-00000820       .text mode_talk0__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk0() {
        if (getMsgId() == 0xFFFFFFFF && dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
            int msgId = daObj::PrmAbstract<Prm_e>(this, PRM_MSG_ID_W, PRM_MSG_ID_S);
            msgId = fopMsgM_messageSet(msgId, &mEyePos);

            mMsgId = msgId;
            mode_talk1_init();
        }
    }

    /* 00000820-0000082C       .text mode_talk1_init__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk1_init() {
        mMode = ActMode_GETMSG_e;
    }

    /* 0000082C-00000874       .text mode_talk1__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk1() {
        mpMsg = fopMsgM_SearchByID(mMsgId);
        if (mpMsg) {
            mode_talk2_init();
        }
    }

    /* 00000874-00000880       .text mode_talk2_init__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk2_init() {
        mMode = ActMode_TALKWAIT_e;
    }

    /* 00000880-000008DC       .text mode_talk2__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::mode_talk2() {
        if (mpMsg->mMode == dNpcMsgStts_BOX_CLOSED_e) {
            mpMsg->mMode = dNpcMsgStts_MSG_DESTROYED_e;
            mpMsg = 0;
            mMsgId = -1;

            g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
            mode_wait_init();
        }
    }

    /* 000008DC-00000948       .text set_mtx__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::set_mtx() {
        mDoMtx_stack_c::transS(getPosition());
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    /* 00000948-00000984       .text init_mtx__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::init_mtx() {
        mpModel->setBaseScale(mScale);
        set_mtx();
    }

    /* 00000984-00000A38       .text damage_cc_proc__Q210daObjPaper5Act_cFv */
    void daObjPaper::Act_c::damage_cc_proc() {
        u32 hitResult = mCylinderCol.ChkTgHit();
        if (hitResult) {
            daObj::HitSeStart(&mEyePos, getRoomNo(), &mCylinderCol, 0x0D);
            dKy_Sound_set(getPosition(), 4, fopAcM_GetID(this), 100);

            daObj::HitEff_hibana(this, &mCylinderCol);

            mCylinderCol.ClrTgHit();
        }

        mColStatus.Move();
    }

    typedef void (Act_c::*daObjPaper_mode_t)(void);

    /* 00000A38-00000B58       .text _execute__Q210daObjPaper5Act_cFv */
    bool daObjPaper::Act_c::_execute() {
        /* Nonmatching */
        static const daObjPaper_mode_t mode_proc[] = {
            &Act_c::mode_wait,
            &Act_c::mode_talk0,
            &Act_c::mode_talk1,
            &Act_c::mode_talk2
        };

        if (mbHasCc) {
            damage_cc_proc();
        }

        (this->*mode_proc[mMode])();

        set_mtx();
        if (mbHasCc) {
            mCylinderCol.SetC(getPosition());
            g_dComIfG_gameInfo.play.mCcS.Set(&mCylinderCol);
        }

        return true;
    }

    /* 00000B58-00000BD4       .text _draw__Q210daObjPaper5Act_cFv */
    bool daObjPaper::Act_c::_draw() {
        /* Nonmatching */
        g_env_light.settingTevStruct(L_attr[mType].getTevType(), getPositionP(), &mTevStr);
        g_env_light.setLightTevColorType(mpModel, &mTevStr);

        mDoExt_modelUpdateDL(mpModel);

        return TRUE;
    }

    namespace {
        /* 00000BD4-00000BF4       .text Mthd_Create__Q210daObjPaper27@unnamed@d_a_obj_paper_cpp@FPv */
        static s32 Mthd_Create(void* i_this) {
            return static_cast<Act_c*>(i_this)->_create();
        }

        /* 00000BF4-00000C18       .text Mthd_Delete__Q210daObjPaper27@unnamed@d_a_obj_paper_cpp@FPv */
        static s32 Mthd_Delete(void* i_this) {
            return static_cast<Act_c*>(i_this)->_delete();
        }

        /* 00000C18-00000C3C       .text Mthd_Execute__Q210daObjPaper27@unnamed@d_a_obj_paper_cpp@FPv */
        static s32 Mthd_Execute(void* i_this) {
            return static_cast<Act_c*>(i_this)->_execute();
        }

        /* 00000C3C-00000C60       .text Mthd_Draw__Q210daObjPaper27@unnamed@d_a_obj_paper_cpp@FPv */
        static s32 Mthd_Draw(void* i_this) {
            return static_cast<Act_c*>(i_this)->_draw();
        }

        /* 00000C60-00000C68       .text Mthd_IsDelete__Q210daObjPaper27@unnamed@d_a_obj_paper_cpp@FPv */
        static s32 Mthd_IsDelete(void* i_this) {
            return TRUE;
        }

        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }

    extern actor_process_profile_definition g_profile_Obj_Paper = {
        fpcLy_CURRENT_e,
        7,
        fpcLy_CURRENT_e,
        PROC_Obj_Paper,
        &g_fpcLf_Method.mBase,
        sizeof(Act_c),
        0,
        0,
        &g_fopAc_Method.base,
        0x0108,
        &Mthd_Table,
        0x00040180,
        fopAc_ACTOR_e,
        fopAc_CULLSPHERE_8_e,
    };
}
