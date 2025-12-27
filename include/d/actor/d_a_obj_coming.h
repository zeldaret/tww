#ifndef D_A_OBJ_COMING_H
#define D_A_OBJ_COMING_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"

namespace daObjComing {
    struct PrmBarrel2_c {
        /* 0x00 */ Vec mPos;
        /* 0x0C */ s32 mType;
        /* 0x10 */ s32 mItem;
        /* 0x14 */ bool m14;
        /* 0x16 */ s16 mAngleY;
    }; // size >= 0x18
    
    class Act_c;
    
    struct Ctrl_c {
        void init(const daObjComing::Act_c*);
        void init_timer(const daObjComing::Act_c*);
        void set_wait_timer(const daObjComing::Act_c*);
        void set_retry_timer(const daObjComing::Act_c*);
        void set_appear_timer(const daObjComing::Act_c*);

        /* 0x00 */ s32 m00;
        /* 0x04 */ s32 m04;
        /* 0x08 */ fpc_ProcID m08;
    }; // size = 0xC
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Ptn_e {
            PTN_00_e = 0,
            PTN_01_e = 1,
            PTN_02_e = 2,
            PTN_03_e = 3,
            PTN_04_e = 4,
            PTN_05_e = 5,
            PTN_06_e = 6,
            PTN_07_e = 7,
            PTN_08_e = 8,
            PTN_09_e = 9,
            PTN_0A_e = 0x0A,
            PTN_0B_e = 0x0B,
            PTN_0C_e = 0x0C,
            PTN_0D_e = 0x0D,
            PTN_0E_e = 0x0E,
            PTN_0F_e = 0x0F,
            PTN_10_e = 0x10,
            PTN_11_e = 0x11,
            PTN_12_e = 0x12,
            PTN_13_e = 0x13,
            PTN_14_e = 0x14,
            PTN_15_e = 0x15,
        };

        enum Prm_e {
            PRM_WAIT_TIME_W = 2,
            PRM_WAIT_TIME_S = 0x18,

            PRM_RANGE_W = 1,
            PRM_RANGE_S = 6,

            PRM_TBL_NUM_W = 3,
            PRM_TBL_NUM_S = 8,

            PRM_SAVE_W = 8,
            PRM_SAVE_S = 0x10,

            PRM_ALWAYS_W = 1,
            PRM_ALWAYS_S = 6,

            PRM_MAKENUM_W = 2,
            PRM_MAKENUM_S = 0x1C,

            PRM_TYPE_W = 4,
            PRM_TYPE_S = 0,
        };
        
        struct MakeTmp_c {
            /* 0x00 */ Vec m00;
            /* 0x0C */ Vec m0C;
            /* 0x18 */ f32 m18;
            /* 0x1C */ f32 m1C;
        }; // size >= 0x20
    
        bool prm_get_always() const { return daObj::PrmAbstract(this, PRM_ALWAYS_W, PRM_ALWAYS_S); }
        s32 prm_get_makeNum() const { return daObj::PrmAbstract(this, PRM_MAKENUM_W, PRM_MAKENUM_S); }
        bool prm_get_range() const { return daObj::PrmAbstract(this, PRM_RANGE_W, PRM_RANGE_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SAVE_W, PRM_SAVE_S); }
        s32 prm_get_tblNum() const { return daObj::PrmAbstract(this, PRM_TBL_NUM_W, PRM_TBL_NUM_S); }
        u32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        s32 prm_get_waitTime() const; // weak but not inlined?
    
        bool chk_switch();
        cPhs_State _create();
        bool _delete();
        static f32 get_aqua_y(const cXyz*);
        bool chk_ship_range(const fopAc_ac_c*) const;
        bool chk_ship_spd(const fopAc_ac_c*) const;
        void get_make_pos(const fopAc_ac_c*, cXyz*) const;
        bool chk_make_pos_gnd(const MakeTmp_c*) const;
        bool chk_make_pos_wall(const MakeTmp_c*) const;
        static void* chk_make_pos_act(void*, void*);
        bool chk_make_pos(const MakeTmp_c*) const;
        Ptn_e barrel2_get_ptn() const;
        static s32 barrel2_get_type(Ptn_e);
        static s32 barrel2_get_item(Ptn_e);
        static bool barrel2_get_buoy(Ptn_e);
        bool barrel2_get_param(PrmBarrel2_c*);
        void mode_barrel2_wait(Ctrl_c*);
        void mode_barrel2_appear(Ctrl_c*);
        void mode_barrel2_leave(Ctrl_c*);
        bool _execute();
        bool _draw();

        static dBgS_ObjGndChk M_gnd_work;
        static dBgS_ObjLinChk M_wall_work;
        static const u8 M_item_tbl[7][16];
    
    public:
        /* 0x290 */ u32 m290;
        /* 0x294 */ Ctrl_c m294[5];
        /* 0x2D0 */ s8 mRoomId;
    }; // size = 0x2D4
};

#endif /* D_A_OBJ_COMING_H */
