#ifndef D_A_OBJ_HOMEN_H
#define D_A_OBJ_HOMEN_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_cc_d.h"

class dBgW;

namespace daObjHomen {
    class Act_c
#if VERSION == VERSION_DEMO
    : public fopAc_ac_c
#else
    // Note: The fopEn_enemy_c base class isn't used in this actor and doesn't appear in this actor's debug map.
    // However, it seems necessary for the destructor to match.
    : public fopEn_enemy_c
#endif
    {
    public:
        typedef BOOL (Act_c::*ProcInitFunc)();
        typedef void (Act_c::*ProcMainFunc)();
        
        enum Param_e {
            PRM_ARG0_W = 0x04,
            PRM_ARG0_S = 0x08,
            
            PRM_ITEM_W = 0x06,
            PRM_ITEM_S = 0x0C,
            
            PRM_ITEMBIT_W = 0x07,
            PRM_ITEMBIT_S = 0x00,
            
            PRM_ENEMY_W = 0x04,
            PRM_ENEMY_S = 0x12,
            
            PRM_SWITCH_W = 0x08,
            PRM_SWITCH_S = 0x18,
        };

        virtual ~Act_c() {}

        int param_get_arg0() const { return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S); }
        int param_get_item() const { return daObj::PrmAbstract(this, PRM_ITEM_W, PRM_ITEM_S); }
        int param_get_itembit() const { return daObj::PrmAbstract(this, PRM_ITEMBIT_W, PRM_ITEMBIT_S); }
        int param_get_enemy() const { return daObj::PrmAbstract(this, PRM_ENEMY_W, PRM_ENEMY_S); }
        int param_get_sw() const { return daObj::PrmAbstract(this, PRM_SWITCH_W, PRM_SWITCH_S); }
        
        bool is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), param_get_sw()); }
        void on_switch() const { fopAcM_onSwitch(const_cast<Act_c*>(this), param_get_sw()); }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        void exe_event();
        void make_enemy();
        void make_item();
        void manage_item_timer();
        void manage_enemy_timer();
        void get_norse_offset(cXyz*, int);
        void get_norse_point(cXyz*, int);
        BOOL process_free_init();
        void process_free_main();
        BOOL process_wait_falldown_init();
        void process_wait_falldown_main();
        BOOL process_falldown_init();
        void process_falldown_main();
        BOOL process_wait_init();
        void process_wait_main();
        BOOL process_none_init();
        void process_none_main();
        BOOL process_init(s16);
        void process_main();
        void set_co_collision();
        void set_at_collision();
        void adjust_hookshot();
        bool _execute();
        bool _draw();
        
        static const char M_arcname[];
        static const dCcD_SrcSph M_sph_srcL;
        static const dCcD_SrcSph M_sph_srcS;
        static const dCcD_SrcCps M_cps_srcL;
        static const dCcD_SrcCps M_cps_srcS;

    public:
        /* 0x2B0 */ dCcD_Stts mSphStts;
        /* 0x2EC */ dCcD_Sph mSph;
        /* 0x418 */ dCcD_Stts mCpsStts[2];
        /* 0x490 */ dCcD_Cps mCps[2];
        /* 0x700 */ cM3dGCpsS mCpsS[2];
        /* 0x738 */ request_of_phase_process_class mPhase;
        /* 0x740 */ J3DModel* mpModel;
        /* 0x744 */ Mtx mMtx;
        /* 0x774 */ dBgW* mpBgW;
        /* 0x778 */ dBgS_ObjGndChk mGndChk;
        /* 0x7CC */ f32 mGroundY;
        /* 0x7D0 */ int mType;
        /* 0x7D4 */ s16 field_0x7D4;
        /* 0x7D6 */ s16 field_0x7D6;
        /* 0x7D8 */ s16 field_0x7D8;
        /* 0x7DA */ s16 field_0x7DA;
        /* 0x7DC */ s16 field_0x7DC;
        /* 0x7DE */ s16 field_0x7DE;
        /* 0x7E0 */ fpc_ProcID mHookshotID;
        /* 0x7E4 */ fpc_ProcID mEnemyID;
        /* 0x7E8 */ fpc_ProcID mSmokeID;
        /* 0x7EC */ s16 field_0x7EC;
        /* 0x7EE */ s16 mItemTimer;
        /* 0x7F0 */ s16 mEnemyTimer;
        /* 0x7F2 */ s16 mEventIdx;
        /* 0x7F4 */ s16 field_0x7F4;
        /* 0x7F6 */ s16 field_0x7F6;
        /* 0x7F8 */ s16 mState;
        /* 0x7FC */ cXyz field_0x7FC;
    };  // Size: 0x808
};

#endif /* D_A_OBJ_HOMEN_H */
