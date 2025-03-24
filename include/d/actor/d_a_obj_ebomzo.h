#ifndef D_A_OBJ_EBOMZO_H
#define D_A_OBJ_EBOMZO_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "JSystem/JParticle/JPAEmitter.h"

namespace daObjEbomzo {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 0
        };

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

        void check();
        void demo();
        void fall();

        static Mtx M_tmp_mtx; //.bss 80810060
        static const char M_arcname[];

    public:

        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Sph mCollider;
        /* 0x43C */ s32 mMode;
        /* 0x440 */ s16 mXRotRate;
        /* 0x444 */ JPABaseEmitter* mpParticleEmitter;

    };
};

#endif /* D_A_OBJ_EBOMZO_H */
