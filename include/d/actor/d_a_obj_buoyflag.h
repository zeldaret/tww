#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"

namespace daObjBuoyflag {
    class Act_c;
    
    enum Type_e {
        
    };
    enum Texture_e {
        
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
        static uint make_norm(uint parentPId, cXyz* pos, int roomNo, csXyz* angle) {
            u32 params = prm_make(static_cast<Type_e>(0), static_cast<Texture_e>(0), false); // TODO: placeholder
            return fopAcM_createChild(PROC_Obj_Buoyflag, parentPId, params, pos, roomNo, angle);
        }
        static u32 prm_make(Type_e, Texture_e, bool) {
            // TODO: placeholder function
            return 0;
        }
    
        void setup(MtxP mtx) { cMtx_copy(mtx, m1090); }
        inline s32 _create();
        inline BOOL _delete();
        inline BOOL _draw();
        inline BOOL _execute();
        void jump_to_sea(float, float, short) {}
        void make_barrel2_mine(uint, cXyz*, int, csXyz*, Texture_e, bool) {}
        void make_barrel2_norm(uint, cXyz*, int, csXyz*, Texture_e) {}
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
        /* 0x10C0 */ u8 m10C0[0x113C - 0x10C0];
    };
};

#endif /* D_A_OBJ_BUOYFLAG_H */
