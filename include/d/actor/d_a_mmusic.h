#ifndef D_A_MMUSIC_H
#define D_A_MMUSIC_H

#include "f_op/f_op_actor.h"

namespace daMmusic {
    class Act_c : public fopAc_ac_c {
    public:
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void Macore_is_playing();
        void set_mtx();
        s32 _create();
        BOOL _delete();
        void init_se();
        void manage_se(int);
        void delete_se();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_MMUSIC_H */
