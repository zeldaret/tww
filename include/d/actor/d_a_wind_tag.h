#ifndef D_A_WIND_TAG_H
#define D_A_WIND_TAG_H

#include "f_op/f_op_actor.h"

namespace daWindTag {
    class daWindTag_c : public fopAc_ac_c {
    public:
        void getCurLength() const {}
        void getMaxLength() const {}
    
        BOOL _delete();
        void CreateHeap();
        void CreateInit();
        void set_wind_angle();
        s32 _create();
        void set_mtx();
        void checkSizeSpecialBig();
        void set_wind_se_sub(unsigned long, cXyz*);
        void set_wind_se();
        BOOL _execute();
        void path_move();
        void set_next_pnt();
        BOOL _draw();
        void MoveEmitter();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_WIND_TAG_H */
