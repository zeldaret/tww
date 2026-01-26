#ifndef D_A_OBJ_TENMADO_H
#define D_A_OBJ_TENMADO_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"

namespace daObjTenmado {
    class Act_c : public dBgS_MoveBgActor {
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 0,

            PRM_SWSAVE2_W = 8,
            PRM_SWSAVE2_S = 8,
        };

    public:
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];
    
    public:
        /* 0x2C8 */ f32 m2C8;
        /* 0x2CC */ s32 m2CC;
        /* 0x2D0 */ request_of_phase_process_class mPhase;
        /* 0x2D8 */ J3DModel* mModel1;
        /* 0x2DC */ J3DModel* mModel2;
    }; // size = 0x2E0
};

#endif /* D_A_OBJ_TENMADO_H */
