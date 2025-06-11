#ifndef D_A_OBJ_MTEST_H
#define D_A_OBJ_MTEST_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMtest {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Type {
            Type_Mcube   = 0,
            Type_Mcyln   = 1,
            Type_Mcube10 = 2,
            Type_Mcyln10 = 3,
            Type_MwtrSB  = 4, // Water splashes
            Type_MygnSB  = 5,
            Type_Owater  = 6,
            Type_Astop   = 7,
            Type_Max,
        };
        
        enum Prm_e {
            PRM_TYPE_W = 0x03,
            PRM_TYPE_S = 0x00,
            
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,
            
            PRM_ARG0_W = 0x04,
            PRM_ARG0_S = 0x10,
            
            PRM_ARG1_W = 0x04,
            PRM_ARG1_S = 0x18,
        };
        
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        // arg0 = 0 checks swSave and appears if set. arg0 = 1 checks swSave and appears if not set.
        // Any other value for arg0 will cause it to appear unconditionally.
        s32 prm_get_arg0() const { return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S); }
        // arg1 affects which DZB mesh to use. The meshes seem to be the same shape but have different properties.
        // TODO: Look into these meshes more.
        s32 prm_get_arg1() const { return daObj::PrmAbstract(this, PRM_ARG1_W, PRM_ARG1_S); }
        
        static char* M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
        static cXyz M_scl_mult[];
        
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        virtual BOOL Delete();
        virtual BOOL Execute(Mtx** pMtx);
        virtual BOOL Draw();
        
        bool chk_appear();
        cPhs_State Mthd_Create();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
    
    public:
        /* 0x2C8 */ Mtx mMtx;
        /* 0x2F8 */ request_of_phase_process_class mPhase;
        /* 0x300 */ J3DModel* mpModel;
        /* 0x304 */ dCcD_Stts mStts;
        /* 0x340 */ dCcD_Cyl mCyl;
        /* 0x470 */ int M_type;
        /* 0x474 */ bool mbAppear;
    };
};

#endif /* D_A_OBJ_MTEST_H */
