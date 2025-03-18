#ifndef D_A_OBJ_SWPUSH_H
#define D_A_OBJ_SWPUSH_H

#include "d/d_a_obj.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_w.h"

class J3DNode;

namespace daObjSwpush {
    struct Attr_c {
        u32 m00;
        u32 m04;
        /* 0x08 */ float m08;
        /* 0x0C */ const char* mKbotaResName;
        /* 0x10 */ const char* mHhbotResName;
        /* 0x14 */ const char* m14;
        /* 0x18 */ const char* m18;
        /* 0x1C */ const char* m1C;
        /* 0x20 */ short m20;
        /* 0x22 */ short m22[2];
        /* 0x26 */ short m26;
        u8 m28[0x4c-0x28];
    };

    class Act_c : public fopAc_ac_c {
    public:

        enum Prm_e {
            PRM_SWSAVE2_W = 0x1,
            PRM_SWSAVE2_S = 0x1E,

            PRM_TYPE_W = 0x3,
            PRM_TYPE_S = 0x18,

            PRM_MDL_W = 0x1,
            PRM_MDL_S = 0x10,

            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x8,
        };

        const Attr_c& attr() const { return M_attr[mType]; }
        BOOL is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void off_switch() const {}
        void on_switch() const {}
        s32 prmZ_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
        void prm_get_evId() const {}
        u8 prm_get_mdl() const { return daObj::PrmAbstract(this, PRM_MDL_W, PRM_MDL_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        void prm_get_version() const {}
        void rev_switch() const {}
    
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
        static const Attr_c M_attr[3];
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ u8 m298[0x2A0 - 0x298];
        /* 0x2A0 */ dBgW* mpBgW;
        /* 0x2A4 */ Mtx mMtx;
        /* 0x2D4 */ float m2D4;
        /* 0x2D8 */ J3DModel* mpModel;
        /* 0x2DC */ mDoExt_btpAnm mBtpAnm;
        /* 0x2F0 */ int mType;

        u8 m2F4[0x2FE - 0x2F4];
        short m2FE;
        u16 m300;
        bool m302;
    }; // Size: 0x338

    // STATIC_ASSERT(sizeof(Act_c) == 0x338);
};

#endif /* D_A_OBJ_SWPUSH_H */
