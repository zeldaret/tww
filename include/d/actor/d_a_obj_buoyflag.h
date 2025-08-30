#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"

namespace daObjBuoyflag {
    class Act_c;
    
    enum Type_e {
        Type_UNK0_e = 0,
        Type_UNK1_e = 1,
        Type_UNK2_e = 2,
    };
    enum Texture_e {
        Texture_00_e = 0x0,
        Texture_01_e = 0x1,
    };
    
    class Packet_c {
    public:
        void calc_pos_gravity(int, int) {}
        void calc_pos_spd(int, int) {}
        void calc_pos_spring(int, int) {}
        void calc_pos_wave(int, int) {}
        
        void hasi_nrm_init();
        void draw_hata(daObjBuoyflag::Act_c*);
        void draw_hasi(daObjBuoyflag::Act_c*);
        void draw();
        void init(daObjBuoyflag::Act_c*);
        void calc_wind_base(daObjBuoyflag::Act_c*);
        void calc_pos_spring_near(const cXyz*, const cXyz*, float, float);
        void calc_pos(daObjBuoyflag::Act_c*);
        void calc_nrm();
        void calc(daObjBuoyflag::Act_c*);
        void update(daObjBuoyflag::Act_c*);
    };
    
    class DrawVtx_c {
    public:
        
    };
    
    class MoveVtx_c {
    public:
        
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        static fpc_ProcID make_norm(fpc_ProcID parentPId, cXyz* pos, int roomNo, csXyz* angle) {
            u32 params = prm_make(Type_UNK0_e, Texture_00_e, false);
            return fopAcM_createChild(PROC_Obj_Buoyflag, parentPId, params, pos, roomNo, angle);
        }
        static u32 prm_make(Type_e type, Texture_e texture, bool arg2) {
            s32 b = arg2 ? 1 : 0;
            return (type << 0) | (texture << 8) | (b << 31);
        }
    
        void setup(MtxP mtx) { cMtx_copy(mtx, m1090); }
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void jump_to_sea(float, float, short) {}
        static fpc_ProcID make_barrel2_mine(fpc_ProcID parent, cXyz* pos, int room, csXyz* angle, Texture_e texture, bool arg5) {
            u32 params = prm_make(Type_UNK2_e, texture, arg5);
            return fopAcM_createChild(PROC_Obj_Buoyflag, parent, params, pos, room, angle);
        }
        static fpc_ProcID make_barrel2_norm(fpc_ProcID parent, cXyz* pos, int room, csXyz* angle, Texture_e texture) {
            u32 params = prm_make(Type_UNK1_e, texture, false);
            return fopAcM_createChild(PROC_Obj_Buoyflag, parent, params, pos, room, angle);
        }
        void attr_type() const; // weak but not inlined?
        void prm_get_noCull() const {}
        void prm_get_texture() const; // weak but not inlined?
        void prm_get_type() const {}
    
        void mtx_init();
        void mode_afl();
        void mode_jumpToSea();
    
    public:
        /* 0x0290 */ u8 m0290[0x1090 - 0x0290];
        /* 0x1090 */ Mtx m1090;
        /* 0x10C0 */ u8 m10C0[0x10F0 - 0x10C0];
        /* 0x10F0 */ Mtx m10F0;
        /* 0x1120 */ u8 m1120[0x1124 - 0x1120];
        /* 0x1124 */ s32 m1124;
        /* 0x1128 */ bool m1128;
    };
};

#endif /* D_A_OBJ_BUOYFLAG_H */
