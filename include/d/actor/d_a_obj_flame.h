#ifndef D_A_OBJ_FLAME_H
#define D_A_OBJ_FLAME_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

namespace daObjFlame {
    class Act_c : public fopAc_ac_c {
    public:
        inline s32 _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void _is_delete() {}
        void attr_base() const {}
        void attr_scl() const {}
        void prm_get_haze() const {}
        void prm_get_kiCycle() const {}
        void prm_get_kiNum() const {}
        void prm_get_sch() const {}
        void prm_get_scl() const {}
        void prm_get_swSave() const {}
    
        void set_switch();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void create_mode_init();
        void set_mtx();
        void init_mtx();
        void em_position();
        void em_simple_set();
        void em_simple_inv();
        void em_manual_set();
        void em_manual_inv();
        void ki_init();
        void ki_make();
        void eff_hase();
        void se_fireblast_omen();
        void liftup_magmarock(void*, void*);
        void liftup_mflft(void*, void*);
        void mode_wait();
        void mode_wait2();
        void mode_l_before();
        void mode_l_u();
        void mode_u();
        void mode_u_l();
        void mode_l_after();
        void mode_proc_call();
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
        /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
        /* 0x2A4 */ dCcD_Stts mStts;
        /* 0x2E0 */ dCcD_Cps mCps;
        /* 0x418 */ cXyz mCpsP0;
        /* 0x424 */ cXyz mCpsP1;
        /* 0x430 */ f32 mCpsRad;
        /* 0x434 */ bool m434;
        /* 0x435 */ u8 m435[0x438 - 0x435];
        /* 0x438 */ int mType;
        /* 0x43C */ int mModeProc;
        /* 0x440 */ f32 mTimer;
        /* 0x444 */ f32 mHeight;
        /* 0x448 */ JPABaseEmitter* mpEmitter0;
        /* 0x44C */ JPABaseEmitter* mpEmitter1;
        /* 0x450 */ JPABaseEmitter* mpEmitter2;
        /* 0x454 */ u8 mEm0State;
        /* 0x455 */ u8 mEm1State;
        /* 0x456 */ u8 mEm2State;
        /* 0x457 */ u8 m457;
        /* 0x458 */ u8 m458;
        /* 0x459 */ u8 m459;
        /* 0x45A */ u8 m45A;
        /* 0x45B */ u8 m45B[0x45C - 0x45B];
        /* 0x45C */ int m45C;
        /* 0x460 */ int m460;
        /* 0x464 */ int m464;
        /* 0x468 */ s16 mRotY;
        /* 0x46A */ u8 m46A[0x46C - 0x46A];
        /* 0x46C */ f32 m46C;
        /* 0x470 */ f32 mExtraScaleY;
        /* 0x474 */ cXyz mOrigScale;
        /* 0x480 */ u8 m480[0x500 - 0x480];
    };
    
    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_FLAME_H */
