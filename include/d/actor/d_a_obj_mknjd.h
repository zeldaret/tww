#ifndef D_A_OBJ_MKNJD_H
#define D_A_OBJ_MKNJD_H

#include "f_op/f_op_actor.h"

namespace daObjMknjD {
    class Act_c : public fopAc_ac_c {
    public:
        void anmAtr(unsigned short) {}
        void getMsg() {}
    
        void set_mtx();
        void init_mtx();
        void setGoal(int i_staffIdx);
        void setPlayerAngle(int i_staffIdx);
        void privateCut();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_MKNJD_H */
