#ifndef D_A_OBJ_DRIFT_H
#define D_A_OBJ_DRIFT_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjDrift {
    class Act_c : public dBgS_MoveBgActor {
    public:
        inline int prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_W, PRM_S);
        }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        void make_flower();
        void calc_flower_param(cXyz*, csXyz*);
        void set_flower_current();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void mode_wait_init();
        void mode_wait();
        void mode_rot_init();
        void mode_rot();
        void set_mtx();
        void init_mtx();
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void set_current();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
        enum Prm_e {
            PRM_W = 3,
            PRM_S = 0
        };
    
    public:
        /* Place member variables here */
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Cyl mCyl;
        /* 0x440 */ int type;
        /* 0x444 */ Mtx field_0x444;
        /* 0x474 */ fpc_ProcID mProcId;
        /* 0x478 */ s32 field_0x478;
        /* 0x47C */ f32 field_0x47C;
        /* 0x480 */ f32 field_0x480;
        /* 0x484 */ f32 field_0x484;
        /* 0x488 */ f32 field_0x488;
        /* 0x48C */ f32 field_0x48C;
        /* 0x490 */ f32 field_0x490;
        /* 0x494 */ f32 field_0x494;
        /* 0x498 */ s16 field_0x498;
        /* 0x49A */ s16 field_0x49A;
        /* 0x49C */ s16 field_0x49C;
        /* 0x49E */ u8  field_0x49E;
        /* 0x49F */ u8  field_0x49F;
        /* 0x4A0 */ s16 field_0x4A0;
        /* 0x4A2 */ s16 field_0x4A2;
        /* 0x4A4 */ cXyz field_0x4A4;
        /* 0x4B0 */ f32 field_0x4B0;
        /* 0x4B4 */ f32 field_0x4B4;
        /* 0x4B8 */ f32 field_0x4B8;
        /* 0x4BC */ cXyz field_0x4BC;
        /* 0x4C8 */ f32 field_0x4C8;
        /* 0x4CC */ f32 field_0x4CC;
        /* 0x4D0 */ f32 field_0x4D0;
        /* 0x4D4 */ f32 field_0x4D4;
        /* 0x4D8 */ f32 field_0x4D8;
    };  // Size: 0x4DC
};

#endif /* D_A_OBJ_DRIFT_H */
