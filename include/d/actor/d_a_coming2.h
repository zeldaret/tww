#ifndef D_A_COMING2_H
#define D_A_COMING2_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_obj_barrel2.h"
#include "d/d_com_inf_game.h"

namespace daComing2 {
    static f32 get_speed(fopAc_ac_c*);
    static void* position_is_safety_call_back(void*, void*);
    static BOOL position_is_none_obj(cXyz*);
    static BOOL checkLineCrossXZ(cXyz*, cXyz*, cXyz*, cXyz*);

    extern s32 coming_make_item_no_table[];

    class _barrel_info_ {
    public:
        /* 0x00 */ fpc_ProcID unk_00;
        /* 0x04 */ s16 unk_04;
        /* 0x06 */ u8 unk_06;
        /* 0x08 */ cXyz unk_08;
    }; // size = 0x14

    struct _start_stat_ {
        /* 0x00 */ s16 unk_00;
    }; // size = 0x2?
    
    class Act_c : public fopAc_ac_c {
        class _start_buoy_ {
        public:
            /* 0x00 */ fpc_ProcID unk_00;
            /* 0x04 */ cXyz unk_04;
        }; // size = 0x10

    public:
        virtual ~Act_c() {}

        s32 get_coming_point() {
            return dComIfGs_getEventReg(0x7EFF);
        }
        void init_coming_point() {}
        void minus_coming_point1() {
            s32 evnt = dComIfGs_getEventReg(0x7EFF);
            u8 evnt2 = (evnt - 1 < 0) ? 0 : evnt - 1;
            dComIfGs_setEventReg(0x7EFF, evnt2);
        }
        void minus_coming_point2() {
            minus_coming_point1();
            minus_coming_point1();
        }
        void pluss_coming_point1() {}
    
        void chase_ship();
        void renew_scope_info();
        BOOL no_ship_obstacle(cXyz*);
        BOOL check_in_large_sea(const cXyz*);
        BOOL get_water_height(float*, const cXyz*);
        void init_barrelN_info(int);
        void init_barrel_info();
        void init_flag_info();
        void init_coming_info();
        BOOL make_coming_param(cXyz*, daObjBarrel2::Type_e*, int*, bool*);
        BOOL request_barrel_exitN(int);
        BOOL request_all_barrel_exit();
        BOOL request_all_flag_exit();
        void barrel_execute(int);
        void barrel_main();
        BOOL coming_clear_init();
        void coming_clear_main();
        BOOL coming_wait_init();
        void coming_wait_main();
        BOOL coming_setF_init();
        void coming_setF_main();
        BOOL coming_checkS_init();
        void coming_checkS_main();
        BOOL coming_game_init();
        void coming_game_main();
        bool coming_process_init(short);
        void coming_process_main();
        cPhs_State _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ // vtbl
        /* 0x294 */ s32 unk_294;
        /* 0x298 */ s8 unk_298;
        /* 0x299 */ s8 unk_299;
        /* 0x29A */ s16 unk_29A;
        /* 0x29C */ s16 unk_29C;
        /* 0x29E */ char unk29E[0x2];
        /* 0x2A0 */ f32 unk_2A0;
        /* 0x2A4 */ s16 unk_2A4;
        /* 0x2A6 */ s16 unk_2A6;
        /* 0x2A8 */ s16 unk_2A8;
        /* 0x2AA */ s16 unk_2AA;
        /* 0x2AC */ _barrel_info_ mBarrelInfo[20];
        /* 0x43C */ _start_stat_ mStartStat;
        /* 0x440 */ cXyz unk_440;
        /* 0x44C */ _start_buoy_ mStartBuoy[2];
        /* 0x46C */ s16 unk_46C;
        /* 0x46E */ s16 unk_46E;
        /* 0x470 */ char unk470[0x6];
        /* 0x476 */ u8 unk_476;
        /* 0x477 */ char unk477[0x31];
        /* 0x4A8 */ cXyz unk_4A8;
    }; // size = 0x4B4
};

#endif /* D_A_COMING2_H */
