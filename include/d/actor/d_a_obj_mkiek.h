#ifndef D_A_OBJ_MKIEK_H
#define D_A_OBJ_MKIEK_H

#include "d/d_bg_s_movebg_actor.h"
#include "m_Do/m_Do_ext.h"

namespace daObjMkiek {

    enum daObjMkiek_State {
        STATE_0 = 0,
        STATE_1 = 1,
        STATE_2 = 2,
    };

    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,

            PRM_SOUND_W = 0x01,
            PRM_SOUND_S = 0x08
        };

        int prm_get_sound() const { return daObj::PrmAbstract(this, PRM_SOUND_W, PRM_SOUND_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void check();
        void demo_wait();
        void demo();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static const char M_arcname[];
        static const char M_envname[];

    private:
        static Mtx M_tmp_mtx;
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ J3DModel* mpModelV;
        /* 0x2D8 */ mDoExt_brkAnm mBrkAnm;
        /* 0x2F0 */ dCcD_Stts mStts;
        /* 0x32C */ dCcD_Sph mSph;
        /* 0x458 */ bool m458;
        /* 0x45A */ s16 mDieEventIdx;
        /* 0x45C */ daObjMkiek_State mState;
        /* 0x460 */ s32 m460;
    };
};

#endif /* D_A_OBJ_MKIEK_H */
