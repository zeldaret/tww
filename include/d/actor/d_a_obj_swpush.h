#ifndef D_A_OBJ_SWPUSH_H
#define D_A_OBJ_SWPUSH_H

#include "d/d_a_obj.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_w.h"

class dBgWSv;
class J3DNode;

namespace daObjSwpush {
    enum AttrFlag_e {
        FLAG_OBEY_SAVE = 0x1,
        FLAG_STAY_PRESSED = 0x2,
        FLAG_IS_TOGGLE = 0x4,
        FLAG_REQ_HEAVY = 0x8,
        FLAG_ON_IS_UP = 0x10,
        FLAG_UNK20 = 0x20,
    };

    struct Attr_c {
        /* 0x00 */ u32 mHeapSize;
        /* 0x04 */ AttrFlag_e mFlags;
        /* 0x08 */ f32 mScale;
        /* 0x0C */ const char* mKbotaResName;
        /* 0x10 */ const char* mHhbotResName;
        /* 0x14 */ const char* mBgArcName;
        /* 0x18 */ const char* mModelArcName;
        /* 0x1C */ const char* mBtpArcName;
        /* 0x20 */ s16 mBgResIndex;
        /* 0x22 */ s16 mModelResIndices[2];
        /* 0x26 */ s16 mBtpResIndex;
        /* 0x28 */ f32 mSpring;
        /* 0x2C */ f32 mSpeedDecay;
        /* 0x30 */ f32 mPushSpeed0;
        /* 0x34 */ f32 m34;
        /* 0x38 */ s16 m38;
        /* 0x3A */ s16 mMiniPushDelay1;
        /* 0x3C */ s16 mPushDelay;
        /* 0x3E */ s16 mMiniPushDelay2;
        /* 0x40 */ f32 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ s16 mPauseDuration;
    };

    class Act_c : public fopAc_ac_c {
    public:
        enum Mode_e {
            MODE_UPPER = 0,
            MODE_U_L = 1,
            MODE_LOWER = 2,
            MODE_L_U = 3
        };

        enum DemoMode_e {
            DEMO_MODE_NON = 0,
            DEMO_MODE_REQ_PAUSE = 1,
            DEMO_MODE_RUN_PAUSE = 2,
            DEMO_MODE_REQ_SW = 3,
            DEMO_MODE_RUN_SW = 4
        };

        enum Prm_e {
            PRM_VERSION_W = 0x1,
            PRM_VERSION_S = 0x1E,

            PRM_TYPE_W = 0x3,
            PRM_TYPE_S = 0x18,

            PRM_MDL_W = 0x1,
            PRM_MDL_S = 0x10,

            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x8,

            PRM_EVID_W = 0x8,
            PRM_EVID_S = 0x0,
        };

        const Attr_c& attr() const { return M_attr[mType]; }
        BOOL is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void off_switch() const { fopAcM_offSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void on_switch() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        u8 prmZ_get_swSave2() const { return prm_get_version() >= 1 ? mPrmZ & 0xff : 0xff; }
        u8 prm_get_evId() const { return daObj::PrmAbstract(this, PRM_EVID_W, PRM_EVID_S); }
        s32 prm_get_mdl() const { return daObj::PrmAbstract(this, PRM_MDL_W, PRM_MDL_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        s32 prm_get_version() const { return daObj::PrmAbstract(this, PRM_VERSION_W, PRM_VERSION_S); }
        void rev_switch() const { fopAcM_revSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
    
        void prmZ_init();
        bool is_switch2() const;
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State create_res_load();
        cPhs_State Mthd_Create();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void set_btp_frame();
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        static BOOL jnodeCB(J3DNode*, int);
        void calc_top_pos();
        void top_bg_aim_req(f32, s16);
        void set_push_flag();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void demo_non_init();
        void demo_non();
        void demo_reqPause_init();
        void demo_reqPause();
        void demo_runPause_init();
        void demo_runPause();
        void demo_stop_puase();
        void demo_reqSw_init();
        void demo_reqSw();
        void demo_runSw_init();
        void demo_runSw();
        BOOL Mthd_Execute();
        BOOL Mthd_Draw();

        static const char M_arcname_kbota[];
        static const char M_arcname_hhbot[];
        static const Attr_c M_attr[];
        static const u8 M_op_vtx[];
    
    public:
        /* 0x290 */ request_of_phase_process_class mKbotaPhs;
        /* 0x298 */ request_of_phase_process_class mHhbotPhs;
        /* 0x2A0 */ dBgWSv* mpBgW;
        /* 0x2A4 */ Mtx mMtx;
        /* 0x2D4 */ f32 m2D4;
        /* 0x2D8 */ J3DModel* mpModel;
        /* 0x2DC */ mDoExt_btpAnm mBtpAnm;
        /* 0x2F0 */ int mType;
        /* 0x2F4 */ int mMode;
        /* 0x2F8 */ int mDemoMode;
        /* 0x2FC */ s16 mPauseTimer;
        /* 0x2FE */ s16 mEventID;
        /* 0x300 */ u16 mPrmZ;
        /* 0x302 */ bool mPrmZInit;
        /* 0x303 */ u8 mVibTimer;
        /* 0x304 */ u8 mRidingMode;
        /* 0x305 */ bool mPrevRiding;
        /* 0x306 */ s16 mMiniPushTimer;
        /* 0x308 */ bool mMiniPushFlg;
        /* 0x309 */ bool mHeavyRiding;
        /* 0x30A */ bool mPrevHeavyRiding;
        /* 0x30C */ s16 mPushTimer;
        /* 0x30E */ bool mPushFlg;
        /* 0x30F */ bool mChangingState;
        /* 0x310 */ f32 mTargetHFrac;
        /* 0x314 */ f32 mCurHFrac;
        /* 0x318 */ f32 mSpeed;
        /* 0x31C */ f32 m31C;
        /* 0x320 */ f32 m320;
        /* 0x324 */ s16 m324;
        /* 0x328 */ f32 m328;
        /* 0x32C */ f32 m32C;
        /* 0x330 */ f32 mTopPos;
        /* 0x334 */ s16 mDebounceTimer;
    }; // Size: 0x338

    STATIC_ASSERT(sizeof(Act_c) == 0x338);
};

#endif /* D_A_OBJ_SWPUSH_H */
