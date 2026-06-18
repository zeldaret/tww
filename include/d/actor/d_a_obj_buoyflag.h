#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_phase.h"

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

    class DrawVtx_c {
    public:
        /* 0x000 */ cXyz m000[35];
        /* 0x1A4 */ cXyz m1A4[35];
        /* 0x348 */ cXyz m348[35];
    };

    class MoveVtx_c {
    public:
        /* 0x000 */ cXyz m000[35];
    };
    
    class Packet_c : public J3DPacket {
    public:
        void calc_pos_gravity(int, int) {}
        void calc_pos_spd(int, int) {}
        void calc_pos_spring(int, int) {}
        void calc_pos_wave(int, int) {}
        
        void hasi_nrm_init();
        void draw_hata(daObjBuoyflag::Act_c*);
        void draw_hasi(daObjBuoyflag::Act_c*);
        virtual void draw();
        void init(daObjBuoyflag::Act_c*);
        void calc_wind_base(daObjBuoyflag::Act_c*);
        void calc_pos_spring_near(const cXyz*, const cXyz*, float, float);
        void calc_pos(daObjBuoyflag::Act_c*);
        void calc_nrm();
        void calc(daObjBuoyflag::Act_c*);
        void update(daObjBuoyflag::Act_c*);

        static cXyz M_hasi_nrm[11];
        static u8 M_hasi_nrm_flag;

    public:
        /* 0x0010 */ DrawVtx_c mDrawVtx[2];
        /* 0x09E8 */ MoveVtx_c m09E8;
        /* 0x0B8C */ s32 m0B8C;
        /* 0x0B90 */ Mtx m0B90;
        /* 0x0BC0 */ Mtx m0BC0;
        /* 0x0BF0 */ Mtx m0BF0;
        /* 0x0C20 */ Mtx m0C20;
        /* 0x0C50 */ cXyz m0C50;
        /* 0x0C5C */ cXyz m0C5C;
        /* 0x0C68 */ s16 m0C68[12];
        /* 0x0C80 */ cXyz m0C80;
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        Act_c() { ((Packet_c*)mPacket.m09E8.m000)->hasi_nrm_init(); }

        enum Prm_e {
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 0,

            PRM_TEXTURE_W = 1,
            PRM_TEXTURE_S = 8,

            PRM_NOCULL_W = 1,
            PRM_NOCULL_S = 0x1F,
        };

        struct AttrType_c {
            /* 0x0 */ f32 mScale;
            /* 0x4 */ u8 m04;
            /* 0x5 */ u8 m05;
            /* 0x6 */ u8 m06;
            /* 0x7 */ u8 m07;
        };

        static fpc_ProcID make_norm(fpc_ProcID parentPId, cXyz* pos, int roomNo, csXyz* angle) {
            u32 params = prm_make(Type_UNK0_e, Texture_00_e, false);
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parentPId, params, pos, roomNo, angle);
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
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parent, params, pos, room, angle);
        }
        static fpc_ProcID make_barrel2_norm(fpc_ProcID parent, cXyz* pos, int room, csXyz* angle, Texture_e texture) {
            u32 params = prm_make(Type_UNK1_e, texture, false);
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parent, params, pos, room, angle);
        }
        const AttrType_c* attr_type() const; // weak but not inlined?
        bool prm_get_noCull() const { return daObj::PrmAbstract<Prm_e>(this, PRM_NOCULL_W, PRM_NOCULL_S); }
        Texture_e prm_get_texture() const; // weak but not inlined?
        s32 prm_get_type() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        void mtx_init();
        bool mode_afl();
        bool mode_jumpToSea();

        static const dCcD_SrcCyl M_cyl_src;
        static const AttrType_c M_attr_type[];
    
    public:
        /* 0x0290 */ request_of_phase_process_class mPhase;
        /* 0x0298 */ dCcD_Stts mStts;
        /* 0x02D4 */ dCcD_Cyl mCyl;
        /* 0x0404 */ Packet_c mPacket;
        /* 0x1090 */ Mtx m1090;
        /* 0x10C0 */ Mtx m10C0;
        /* 0x10F0 */ Mtx m10F0;
        /* 0x1120 */ s32 m1120;
        /* 0x1124 */ s32 m1124;
        /* 0x1128 */ bool m1128;
        /* 0x1129 */ u8 m1129;
        /* 0x112A */ s16 m112A;
        /* 0x112C */ f32 m112C;
        /* 0x1130 */ cXyz m1130;
    };

    STATIC_ASSERT(sizeof(DrawVtx_c) == 0x4EC);
    STATIC_ASSERT(sizeof(MoveVtx_c) == 0x1A4);
    STATIC_ASSERT(sizeof(Packet_c) == 0xC8C);
    STATIC_ASSERT(offsetof(Packet_c, mDrawVtx) == 0x10);
    STATIC_ASSERT(offsetof(Packet_c, m09E8) == 0x9E8);
    STATIC_ASSERT(offsetof(Packet_c, m0B90) == 0xB90);
    STATIC_ASSERT(offsetof(Packet_c, m0C80) == 0xC80);
    STATIC_ASSERT(offsetof(Act_c, mPhase) == 0x290);
    STATIC_ASSERT(offsetof(Act_c, mStts) == 0x298);
    STATIC_ASSERT(offsetof(Act_c, mCyl) == 0x2D4);
    STATIC_ASSERT(offsetof(Act_c, mPacket) == 0x404);
    STATIC_ASSERT(offsetof(Act_c, m1090) == 0x1090);
    STATIC_ASSERT(offsetof(Act_c, m112A) == 0x112A);
    STATIC_ASSERT(offsetof(Act_c, m1130) == 0x1130);
};

#endif /* D_A_OBJ_BUOYFLAG_H */
