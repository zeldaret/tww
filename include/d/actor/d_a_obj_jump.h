#ifndef D_A_OBJ_JUMP_H
#define D_A_OBJ_JUMP_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_bg_s_gnd_chk.h"

class J3DNode;

namespace daObjJump {
    struct Attr_c {
        /* 0x00 */ u32 resSize;
        /* 0x04 */ s16 resIndex;
        /* 0x06 */ s16 field_0x006;
        /* 0x08 */ SVec cullSizeBoxMin;
        /* 0x0e */ SVec cullSizeBoxMax;
        /* 0x14 */ u8 field_0x014;
        /* 0x15 */ u8 field_0x015;
        /* 0x16 */ u16 field_0x016;
        /* 0x18 */ float field_0x018;
        /* 0x1C */ float field_0x01C;
        /* 0x20 */ float field_0x020;
        /* 0x24 */ float field_0x024;
        /* 0x28 */ float field_0x028;
        /* 0x2C */ float field_0x02C;
        /* 0x30 */ float field_0x030;
        /* 0x34 */ float field_0x034;
        /* 0x38 */ float field_0x038;
        /* 0x3c */ float field_0x03C;
        /* 0x40 */ u8 field_0x040;
        /* 0x41 */ u8 field_0x041;
        /* 0x42 */ u8 field_0x042;
        /* 0x43 */ u8 field_0x043;
        /* 0x44 */ u8 field_0x044;
        /* 0x45 */ u8 field_0x045;
        /* 0x46 */ u8 field_0x046;
        /* 0x47 */ u8 field_0x047;
        /* 0x48 */ u8 field_0x048;
        /* 0x49 */ u8 field_0x049[0x4c - 0x49];
        /* 0x4c */ float field_0x04C;
    };  // Size: 0x50

    class Act_c : public dBgS_MoveBgActor {
    public:
        static u32 prm_make_b() {
            return 1;
        }
    
        void setup(const cXyz* pos) {
            current.pos = *pos;
            m336 = 1;
        }
        const Attr_c& attr() const { return M_attr[field_0x2D4]; }
        int prm_get_type() const { return daObj::PrmAbstract(this, 1, 0); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void set_push_flag();
        void clear_push_flag();
        void calc_vib_pos();
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        static BOOL jnodeCB_lower(J3DNode*, int);
        void mode_wait_init();
        void mode_wait();
        void mode_w_l_init();
        void mode_w_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_upper_init();
        void mode_upper();
        void mode_u_w_init();
        void mode_u_w();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
        static Mtx M_tmp_mtx;
        static const char M_arcname[];
        static const Attr_c M_attr[2];
    public:    
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mModel;
        /* 0x2D4 */ int field_0x2D4;
        /* 0x2D8 */ dBgS_ObjGndChk field_0x2D8;
        /* 0x32C */ f32 field_0x32C;
        /* 0x330 */ int field_0x330;
        /* 0x334 */ s16 field_0x334;
        /* 0x336 */ u8 m336;
        /* 0x337 */ u8 m337;
        /* 0x338 */ f32 field_0x338;
        /* 0x33C */ f32 field_0x33C;
        /* 0x340 */ f32 field_0x340;
        /* 0x344 */ u8 field_0x344;
        /* 0x345 */ u8 field_0x345;
        /* 0x346 */ u8 field_0x346;
        /* 0x347 */ u8 field_0x347;
        /* 0x348 */ u8 field_0x348;
        /* 0x349 */ u8 field_0x349;
        /* 0x34A */ u8 field_0x34a;
        /* 0x34B */ u8 field_0x34b;
        /* 0x34C */ u8 field_0x34c;
        /* 0x34D */ u8 field_0x34d;
        /* 0x34E */ u8 field_0x34e;
        /* 0x34F */ u8 field_0x34f;
        /* 0x350 */ u8 field_0x350;
        /* 0x351 */ u8 field_0x351;
        /* 0x352 */ s16 field_0x352;
        /* 0x354 */ u8 field_0x354;
        /* 0x355 */ u8 field_0x355[0x358 - 0x355];
    };  // Size: 0x358
};

#endif /* D_A_OBJ_JUMP_H */
