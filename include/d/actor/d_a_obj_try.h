#ifndef D_A_OBJ_TRY_H
#define D_A_OBJ_TRY_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"

namespace daObjTry {
    enum Type_e {
        UNK_2 = 2,
        UNK_3 = 3,
        UNK_4 = 4,
        UNK_5 = 5,
        UNK_6 = 6,
        UNK_7 = 7,
        UNK_8 = 8,
        UNK_9 = 9,
        UNK_10 = 10,
        UNK_11 = 11,
        UNK_12 = 12,
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_S = 8,
            PRM_SWSAVE_W = 8,

            PRM_TYPE_S = 0,
            PRM_TYPE_W = 4,
        };

        void attr() const {}
        void prm_chk_type_tryStatue() const {}
        void prm_get_dummy() const {}
        int prm_get_swSave() const {
            return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }
        int prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
        void to_correct_pos(const cXyz* param_1, short param_2, bool param_3, bool param_4) {
            field_0x63C.set(*param_1);
            field_0x648 = param_2;
            field_0x64C = param_3;
            field_0x64D = param_4;
        }
    
        void prm_set_swSave(int);
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void init_cc();
        void search_sameType(void*, void*);
        void chk_appear() const;
        cPhs_State _create();
        bool _delete();
        void mode_restart_init();
        void mode_restart();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_sink_init();
        void mode_sink();
        void mode_proc_call();
        void cull_set_draw();
        void cull_set_move();
        void damaged();
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        void chk_sink_water();
        void chk_sinkdown_water();
        void calc_drop_param(float*, float*, float*) const;
        void bound();
        void se_fall_water();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        void set_mtx();
        void init_mtx();
        void eff_set_bingo(bool, bool);
        void eff_clr_bingo();
        void eff_land_smoke();
        void eff_hit_water_splash();
        void make_vib();
        void check_circle();
        void get_water_h();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ u8 field_0x290[0x63C - 0x290];
        /* 0x63C */ cXyz field_0x63C;
        /* 0x648 */ s16 field_0x648;
        /* 0x64A */ u8 field_0x64A[0x64C - 0x64A];
        /* 0x64C */ s8 field_0x64C;
        /* 0x64D */ s8 field_0x64D;
        /* 0x64E */ u8 field_0x64E[0x66C - 0x64E];
    };  // Size: 0x66C
};

#endif /* D_A_OBJ_TRY_H */
