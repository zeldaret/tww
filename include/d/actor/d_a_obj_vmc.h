#ifndef D_A_OBJ_VMC_H
#define D_A_OBJ_VMC_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"

class dBgW;

namespace daObjVmc {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,
        };

        void daObjVmc_ChangeGrow() { mHasTree = true; }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void CreateInit();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        void daObjVmc_base_main();
        void daObjVmc_tree_demo_wait();
        void daObjVmc_tree_demo_main();
        void daObjVmc_tree_main();
        bool _execute();
        bool _draw();

    public:
        static const char M_arcname[];

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ dBgW* mpBgBase;
        /* 0x29A */ dBgW* mpBgTree;
        /* 0x2A0 */ J3DModel* mModelBase;
        /* 0x2A4 */ J3DModel* mModelTree;
        /* 0x2A8 */ mDoExt_bckAnm mBckAnmGrow;
        /* 0x2B8 */ mDoExt_bckAnm mBckAnmHookshot;
        /* 0x2C8 */ dCcD_Stts mStts;
        /* 0x304 */ dCcD_Cyl mCyl;
        /* 0x434 */ Mtx mMtxBase;
        /* 0x434 */ Mtx mMtxTree;
        /* 0x494 */ dPa_smokeEcallBack mSmoke;
#if VERSION == VERSION_DEMO
        /* 0x4B4 */ JPABaseEmitter* m4B4_demo;
#endif
        /* 0x4B4 */ u8 mLinkRangeCheck;
        /* 0x4B8 */ s32 mState;
        /* 0x4BC */ s32 mTimer;
        /* 0x4C0 */ u8 mHookshotAnim;
        /* 0x4C1 */ u8 mHasTreeBg;
        /* 0x4C2 */ u8 mHasTree;
    };
};

#endif /* D_A_OBJ_VMC_H */
