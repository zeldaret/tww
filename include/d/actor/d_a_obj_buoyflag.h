#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor.h"

namespace daObjBuoyflag {
    class Act_c : public fopAc_ac_c {
    public:
        void _create() {}
        void _delete() {}
        void _draw() {}
        void _execute() {}
        void jump_to_sea(float, float, short) {}
        void make_barrel2_mine(unsigned int, cXyz*, int, csXyz*, daObjBuoyflag::Texture_e, bool) {}
        void make_barrel2_norm(unsigned int, cXyz*, int, csXyz*, daObjBuoyflag::Texture_e) {}
        void make_norm(unsigned int, cXyz*, int, csXyz*) {}
        void prm_make(daObjBuoyflag::Type_e, daObjBuoyflag::Texture_e, bool) {}
        void setup(float(*)[4]) {}
    
        void prm_get_texture() const;
        void attr_type() const;
        void mtx_init();
        void mode_afl();
        void mode_jumpToSea();
    
    public:
        /* 0x0290 */ u8 m0290[0x1090 - 0x0290];
        /* 0x1090 */ Mtx m1090;
        /* 0x10C0 */ u8 m10C0[0x113C - 0x10C0];
    };
};

#endif /* D_A_OBJ_BUOYFLAG_H */
