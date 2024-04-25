#ifndef D_A_WIND_TAG_H
#define D_A_WIND_TAG_H

#include "f_op/f_op_actor.h"

namespace daWindTag {
    static BOOL CheckCreateHeap(fopAc_ac_c*);

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
        
        static const f32 mData[];
    
    public:
        /* Place member variables here */
    /* 0x290 */ char pad290[0x208]; /* Placeholder padding */
    /* 0x498 */ f32 unk498;
};
};  // namespace daWindTag

#endif /* D_A_WIND_TAG_H */
