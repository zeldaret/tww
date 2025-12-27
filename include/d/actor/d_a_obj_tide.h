#ifndef D_A_OBJ_TIDE_H
#define D_A_OBJ_TIDE_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"

class mDoExt_bckAnm;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

namespace daObjTide {
    namespace {
        enum Type_e {
            TYPE_0_e = 0,
            TYPE_1_e = 1,
            TYPE_2_e = 2,
            TYPE_3_e = 3,
            TYPE_4_e = 4,
            TYPE_5_e = 5,
        };

        struct Attr_c {
            /* 0x00 */ const char* arcName;
            /* 0x04 */ s16 m04;
            /* 0x06 */ s16 m06;
            /* 0x08 */ s16 m08;
            /* 0x0A */ s16 m0A;
            /* 0x0C */ s16 m0C;
            /* 0x10 */ u32 m10;
            /* 0x14 */ s16 m14;
            /* 0x16 */ s16 m16;
            /* 0x18 */ u32 m18;
            /* 0x1C */ u32 resSize;
            /* 0x20 */ s16 m20;
            /* 0x24 */ f32 m24;
            /* 0x28 */ f32 m28;
            /* 0x2C */ f32 m2C;
            /* 0x30 */ f32 m30;
            /* 0x34 */ s16 minX;
            /* 0x36 */ s16 minY;
            /* 0x38 */ s16 minZ;
            /* 0x3A */ s16 maxX;
            /* 0x3C */ s16 maxY;
            /* 0x3E */ s16 maxZ;
            /* 0x40 */ bool sch_flag;
            /* 0x42 */ s16 m42;
            /* 0x44 */ f32 m44;
        }; // size = 0x48
    }

    class Act_c : public dBgS_MoveBgActor {
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 24,

            PRM_TYPE_W = 3,
            PRM_TYPE_S = 16,
        };

    public:
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        Type_e prm_get_type() const { return Type_e(daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S)); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void move_to_aim(float, bool);
        bool chk_demo_rescue() const;
        bool gmtw_demo_up_start() const;
        void mode_norm_init();
        void mode_norm();
        void mode_gmtw_pre_init();
        void mode_gmtw_pre();
        void mode_gmtw_init();
        void mode_gmtw();
        void mode_gmtw_demo_init();
        void mode_gmtw_demo();
        void se_init_gmtw();
        void se_set_gmtw();
        void se_start_gopo();
        void se_start_out();
        void se_start_up();
        void se_stop_gopo();
        void se_stop_out();
        void se_stop_up();
        void se_pos_up();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mModel1;
        /* 0x2D4 */ mDoExt_bckAnm* mBck1;
        /* 0x2D8 */ mDoExt_brkAnm* mBrk1;
        /* 0x2DC */ mDoExt_btkAnm* mBtk;
        /* 0x2E0 */ J3DModel* mModel2;
        /* 0x2E4 */ mDoExt_brkAnm* mBrk2;
        /* 0x2E8 */ Type_e M_type;
        /* 0x2EC */ s32 m2EC;
        /* 0x2F0 */ f32 m2F0;
        /* 0x2F4 */ s16 m2F4;
        /* 0x2F6 */ u8 m2F6;
        /* 0x2F7 */ bool m2F7;
        /* 0x2F8 */ bool m2F8;
        /* 0x2F9 */ bool m2F9;
        /* 0x2FA */ bool m2FA;
        /* 0x2FB */ bool m2FB;
        /* 0x2FC */ fpc_ProcID M_id_gopo;
        /* 0x300 */ fpc_ProcID M_id_out;
        /* 0x304 */ fpc_ProcID M_id_up;
        /* 0x308 */ bool m308;
        /* 0x309 */ bool m309;
        /* 0x30A */ bool m30A;
        /* 0x30B */ bool m30B;
#if VERSION > VERSION_DEMO
        /* 0x30C */ s32 m30C;
#endif
    }; // size = 0x310
};

#endif /* D_A_OBJ_TIDE_H */
