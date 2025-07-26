#ifndef D_A_COMING3_H
#define D_A_COMING3_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"

namespace daComing3 {
    static void* position_is_safety_call_back(void*, void*);
    static BOOL position_is_none_obj(cXyz*);
    
    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}

        BOOL get_water_height(float*, int*, const cXyz*);
        s32 get_challenge_id();
        f32 get_limit_dist();
        BOOL coming_start_init();
        void coming_start_main();
        BOOL coming_game_init();
        void coming_game_main();
        BOOL coming_wait_init();
        void coming_wait_main();
        bool coming_process_init(short);
        void eff_break_tsubo();
        void coming_process_main();
        void set_mtx();
        void collision_init();
        bool collision_main();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
        static char M_arcname[];

    public:
        /* 0x290 */ // vtbl
        /* 0x294 */ dCcD_Stts mStts;
        /* 0x2D0 */ dCcD_Cyl mCyl;
        /* 0x400 */ fpc_ProcID unk_400;
        /* 0x404 */ s32 unk_404;
        /* 0x408 */ request_of_phase_process_class mPhase;
        /* 0x410 */ Mtx unk_410;
        /* 0x440 */ J3DModel* unk_440;
        /* 0x444 */ s16 unk_444;
        /* 0x446 */ char unk446[0x32];
        /* 0x478 */ f32 unk_478;
        /* 0x47C */ s16 unk_47C;
        /* 0x47E */ s16 unk_47E;
    }; // size = 0x480
};

#endif /* D_A_COMING3_H */
