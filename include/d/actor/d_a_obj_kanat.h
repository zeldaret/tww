#ifndef D_A_OBJ_KANAT_H
#define D_A_OBJ_KANAT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"

namespace daObjKanat {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };

        static Mtx M_tmp_mtx;
        static const char M_arcname[];
    
        int prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        virtual BOOL Delete();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        
        cPhs_State Mthd_Create();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dPa_smokeEcallBack mSmokeCb;
        /* 0x2F4 */ bool mIsBroken;
        /* 0x2F5 */ bool mIsVisible;
    };
};

#endif /* D_A_OBJ_KANAT_H */
