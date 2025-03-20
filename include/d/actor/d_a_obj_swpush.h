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
        FLAG_UNK10 = 0x10,
        FLAG_UNK20 = 0x20,
    };

    struct Attr_c {
        u32 m00;
        u32 mFlags;
        /* 0x08 */ float m08;
        /* 0x0C */ const char* mKbotaResName;
        /* 0x10 */ const char* mHhbotResName;
        /* 0x14 */ const char* m14;
        /* 0x18 */ const char* m18;
        /* 0x1C */ const char* m1C;
        /* 0x20 */ short m20;
        /* 0x22 */ short m22[2];
        /* 0x26 */ short m26;
        float m28;
        float m2C;
        float m30;
        float m34;
        short m38;
        short mMiniPushDelay1;
        short mPushDelay;
        short mMiniPushDelay2;
        float m40;
        float m44;
        short m48;
    };

    class Act_c : public fopAc_ac_c {
    public:

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
        BOOL is_switch2() const;
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
        void top_bg_aim_req(float, short);
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

        static const char M_arcname_kbota[9];
        static const char M_arcname_hhbot[6];
        static const Attr_c M_attr[4];
        static const u8 M_op_vtx[4];
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs1;
        /* 0x298 */ request_of_phase_process_class mPhs2;
        /* 0x2A0 */ dBgWSv* mpBgW;
        /* 0x2A4 */ Mtx mMtx;
        /* 0x2D4 */ float m2D4;
        /* 0x2D8 */ J3DModel* mpModel;
        /* 0x2DC */ mDoExt_btpAnm mBtpAnm;
        /* 0x2F0 */ int mType;
        /* 0x2F4 */ int mMode;
        /* 0x2F8 */ int mDemoMode;
        /* 0x2FC */ short m2FC;
        /* 0x2FE */ short m2FE;
        /* 0x300 */ u16 mPrmZ;
        /* 0x302 */ bool m302;
        /* 0x303 */ u8 m303;
        /* 0x304 */ u8 mRidingMode;
        /* 0x305 */ bool mPrevRiding;
        /* 0x306 */ short mMiniPushTimer;
        /* 0x308 */ bool mMiniPushFlg;
        /* 0x309 */ bool mHeavyRiding;
        /* 0x30A */ bool mPrevHeavyRiding;
        /* 0x30C */ short mPushTimer;
        /* 0x30E */ bool mPushFlg;
        /* 0x30F */ u8 m30F;
        /* 0x310 */ float mTargetHFrac;
        /* 0x314 */ float mCurHFrac;
        /* 0x318 */ float mVSpeed;
        /* 0x31C */ float m31C;
        /* 0x320 */ float m320;
        /* 0x324 */ short m324;
        /* 0x328 */ float m328;
        /* 0x32C */ float m32C;
        /* 0x330 */ float mTopPos;
        /* 0x334 */ short m334;
    }; // Size: 0x338

    STATIC_ASSERT(sizeof(Act_c) == 0x338);
};

#endif /* D_A_OBJ_SWPUSH_H */
