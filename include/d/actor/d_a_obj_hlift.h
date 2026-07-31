#ifndef D_A_OBJ_HLIFT_H
#define D_A_OBJ_HLIFT_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjHlift {
    struct Attr_c {
        /* 0x00 */ f32 field_0x00;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ f32 field_0x0C;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ s16 field_0x1C;
        /* 0x1E */ s16 field_0x1E;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ u8 field_0x24[0x2C - 0x24];
    };
    
    class Act_c : public dBgS_MoveBgActor {
    public:
        struct size_data {
            /* 0x00 */ s16 field_0x00;
            /* 0x01 */ s16 field_0x01;
            /* 0x02 */ int field_0x02;
        };

        enum Mode_e {
            Mode_L_U = 0x01,
            Mode_U_L = 0x03,
            Mode_UNK = 0x05,
        };
    
        enum Prm_e {
            PRM_DIST_W = 3,
            PRM_DIST_S = 0,

            PRM_EVENTID_W = 8,
            PRM_EVENTID_S = 0x10,

            PRM_SIZE_W = 1,
            PRM_SIZE_S = 4,
        
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,
        };
        int prm_get_dist() const { return daObj::PrmAbstract<Prm_e>(this, PRM_DIST_W, PRM_DIST_S); }
        u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EVENTID_W, PRM_EVENTID_S); }
        int prm_get_size() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SIZE_W, PRM_SIZE_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_demoreq_init(Mode_e);
        void mode_demoreq();
        void set_mtx();
        void init_mtx();
        void rot_set();
        void vib_set();
        void vib_proc();
        bool chk_demo_end();
        void se_whole();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
        static Mtx M_tmp_mtx;
        static u8 M_lift_move_flag;
        static fpc_ProcID M_control_id;
        static const char M_arcname[];
        static const char M_evname[];
        static const s16 M_up_dist[8];
        static const size_data M_data_size[2];
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mModel1;
        /* 0x2D4 */ J3DModel* mModel2;
        /* 0x2D8 */ int field_0x2D8;
        /* 0x2DC */ int field_0x2DC;
        /* 0x2E0 */ int field_0x2E0;
        /* 0x2E4 */ Mode_e field_0x2E4;
        /* 0x2E8 */ s16 field_0x2E8;
        /* 0x2EA */ s16 field_0x2EA;
        /* 0x2EC */ f32 field_0x2EC;
        /* 0x2F0 */ f32 field_0x2F0;
        /* 0x2F4 */ s16 field_0x2F4;
        /* 0x2F6 */ u8 field_0x2F6;
        /* 0x2F7 */ u8 field_0x2F7[0x2F8 - 0x2F7];
        /* 0x2F8 */ s16 mEventId;
        /* 0x2FA */ u8 field_0x2FA[0x2FC - 0x2FA];
    };  // Size: 0x2FC
};

#endif /* D_A_OBJ_HLIFT_H */
