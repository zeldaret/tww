#ifndef D_A_OBJ_MMRR_H
#define D_A_OBJ_MMRR_H

#include "f_op/f_op_actor.h"

namespace daObjMmrr {
    class Act_c : public fopAc_ac_c {
    public:
        void setup(const cXyz* pos) {
            current.pos = *pos;
            mBF8 = 1;
        }
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void init_cc();
        void set_cc_rec_pos();
        void set_cc_trans_pos();
        void set_cull();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void init_mtx();
        void chk_light();
        void eff_start();
        void eff_stop();
        void eff_remove();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* 0x290 */ u8 m290[0xBF8 - 0x290];
        /* 0xBF8 */ u8 mBF8;
        /* 0xBF9 */ u8 mBF9[0xC18 - 0xBF9];
    };

    class Eff_c {
    public:
        void end();
        void remove();
    };
};

#endif /* D_A_OBJ_MMRR_H */
