#ifndef D_A_OBJ_ASHUT_H
#define D_A_OBJ_ASHUT_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjAshut {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            Mode_U    = 0x00,     // Bars are up
            Mode_U_L  = 0x01,     // Bars are falling down
            Mode_L    = 0x02,     // Bars are down
            Mode_L_U  = 0x03,     // Bars are rising up
            Mode_DemoReq  = 0x04,
            Mode_UNK5     = 0x05
        };

        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
            PRM_EV_ID_W  = 0x08,
            PRM_EV_ID_S  = 0x08,
        };

        bool is_switch() const {
            s32 event_prm = prm_get_swSave();
            return fopAcM_isSwitch(const_cast<Act_c*>(this), event_prm);
        }

        u8 prm_get_evId() const {
            return daObj::PrmAbstract<Prm_e>(this, PRM_EV_ID_W, PRM_EV_ID_S);
        }

        s32 prm_get_swSave() const {
            return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        virtual BOOL Delete();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        cPhs_State Mthd_Create();
        BOOL Mthd_Delete();

        void set_mtx();
        void init_mtx();
        bool chk_safe_area() const;

        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_demoreq_init(Mode_e);
        void mode_demoreq();

    public:
        static const char M_arcname[];
        static Mtx M_tmp_mtx;

        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ Mode_e mMode;
        /* 0x2D8 */ f32 field_0x2D8;
        /* 0x2DC */ f32 field_0x2DC;
        /* 0x2E0 */ u8  field_0x2E0;
        /* 0x2E2 */ s16 field_0x2E2;
        /* 0x2E4 */ bool field_0x2E4;
        /* 0x2E6 */ s16 mEventId;
        /* 0x2E8 */ s32 mNextMode;
    };
};

#endif /* D_A_OBJ_ASHUT_H */
