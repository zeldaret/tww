#ifndef D_A_OBJ_MTEST_H
#define D_A_OBJ_MTEST_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"

namespace daObjMtest {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Type {
            Type_0 = 0,
            Type_1 = 1,
            Type_2 = 2,
            Type_3 = 3,
            Type_4 = 4,
            Type_5 = 5,
            Type_6 = 6,
            Type_7 = 7,
            Type_Max,
        };
        
        enum Prm_e {
            PRM_ARG0_W = 0x04,
            PRM_ARG0_S = 0x10,
            
            PRM_ARG1_W = 0x04,
            PRM_ARG1_S = 0x18,
            
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,
            
            PRM_TYPE_W = 0x03,
            PRM_TYPE_S = 0x00,
        };
        
        s32 prm_get_arg0() const { return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S); }
        s32 prm_get_arg1() const { return daObj::PrmAbstract(this, PRM_ARG1_W, PRM_ARG1_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        
        static char* M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
        static cXyz M_scl_mult[];
        
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        virtual BOOL Delete();
        virtual BOOL Execute(Mtx** pMtx);
        virtual BOOL Draw();
        
        bool chk_appear();
        s32 Mthd_Create();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
    
    public:
        /* 0x2C8 */ Mtx mMtx;
        /* 0x2F8 */ request_of_phase_process_class mPhs;
        /* 0x300 */ J3DModel* mpModel;
        /* 0x304 */ dCcD_Stts mStts;
        /* 0x340 */ dCcD_Cyl mCyl;
        /* 0x470 */ int M_type;
        /* 0x474 */ bool mbAppear;
    };
};

#endif /* D_A_OBJ_MTEST_H */
