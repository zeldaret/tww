#ifndef D_A_OBJ_AYGR_H
#define D_A_OBJ_AYGR_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjAygr {
    class Act_c : public dBgS_MoveBgActor {
         enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 24,

            PRM_TYPE_W = 1,
            PRM_TYPE_S = 0,
        };

    public:
        u8 prm_get_mdl() const {
        return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    /*0x290*/ request_of_phase_process_class mPhase;
    /*0x2d0*/ J3DModel* mModel1;
    /*0x2d4*/ J3DModel* mModel2;
    /*0x2d8*/ dBgW* mpBgW;
    /*0x2dc*/ Mtx m2dc;
    /*0x30c*/ u8 m30C;
    static const char M_arcname[];
    static Mtx M_tmp_mtx;
    };
};

#endif /* D_A_OBJ_AYGR_H */
