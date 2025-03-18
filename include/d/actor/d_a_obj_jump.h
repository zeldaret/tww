#ifndef D_A_OBJ_JUMP_H
#define D_A_OBJ_JUMP_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

class J3DNode;

namespace daObjJump {
    class Act_c : public dBgS_MoveBgActor {
    public:
        static u32 prm_make_b() {
            return 1;
        }
    
        void setup(const cXyz* pos) {
            current.pos = *pos;
            m336 = 1;
        }
        void attr() const {}
        void prm_get_type() const {}
    
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
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
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
    
    public:
        /* 0x2C8 */ u8 m2C8[0x336 - 0x2C8];
        /* 0x336 */ u8 m336;
        /* 0x337 */ u8 m337[0x358 - 0x337];
    };
};

#endif /* D_A_OBJ_JUMP_H */
