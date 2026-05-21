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
    static const Attr_c L_attr = { 30.0f, 50.0f, 10.0f, 2.0f, 0.3f, 1.2f, 250.0f, 10, 16384, 2.5f, 0x00, 0x02, 0x0a, 0x08, 0x07, 0x00, 0x00, 0x00 };
    
    class Act_c : public dBgS_MoveBgActor {
    public:
        struct size_data {
            /* 0x00 */ s16 field_0x00;
            /* 0x01 */ s16 field_0x01;
            /* 0x02 */ int field_0x02;
        };

        enum Mode_e {
            // FIXME names
            Mode_L_U = 0x01,
            Mode_U_L = 0x03,
            Mode_UNK = 0x05,
        };
    
        enum Prm_e {
            // FIXME names
            PRM_HLIFT_0 = 0x00,
            PRM_HLIFT_1 = 0x01,
            PRM_HLIFT_3 = 0x03,
            PRM_HLIFT_4 = 0x04,
            PRM_HLIFT_8 = 0x08,
            PRM_HLIFT_16 = 0x10,
        };
        int prm_get_dist() const { return daObj::PrmAbstract<Prm_e>(this, PRM_HLIFT_3, PRM_HLIFT_0); }
        u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_HLIFT_8, PRM_HLIFT_16); }
        int prm_get_size() const { return daObj::PrmAbstract<Prm_e>(this, PRM_HLIFT_1, PRM_HLIFT_4); }
        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_HLIFT_8, PRM_HLIFT_8); }
    
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
        BOOL chk_demo_end();
        void se_whole();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
        static Mtx M_tmp_mtx;
        static u8 M_lift_move_flag;
        static int M_control_id;
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
