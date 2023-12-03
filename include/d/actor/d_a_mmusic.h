#ifndef D_A_MMUSIC_H
#define D_A_MMUSIC_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;

namespace daMmusic {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        BOOL Macore_is_playing();
        void set_mtx();
        s32 _create();
        bool _delete();
        void init_se();
        void manage_se(int);
        void delete_se();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ s32 field_0x298;
        /* 0x29C */ s32 field_0x29c;
        /* 0x2A0 */ JPABaseEmitter* mpEmitter;
        /* 0x2A4 */ Mtx mMtx;
        /* 0x2D4 */ s16 mTimer;
    };
};

#endif /* D_A_MMUSIC_H */
