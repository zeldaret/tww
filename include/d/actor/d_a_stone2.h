#ifndef D_A_STONE2_H
#define D_A_STONE2_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_a_obj.h"
#include "d/d_particle.h"

namespace daStone2 {
    struct Attr_c {
        /* 0x00 */ const char* resName;
        /* 0x04 */ s16 m04;
        /* 0x06 */ s16 resIndex;
        /* 0x08 */ u32 heapSize;
        /* 0x0C */ u8 m0C;
        /* 0x0E */ s16 m0E;
        /* 0x10 */ s16 m10;
        /* 0x12 */ s16 m12;
        /* 0x14 */ s16 m14;
        /* 0x18 */ u32 m18;
        /* 0x1C */ u32 m1C;
        /* 0x20 */ s16 m20;
        /* 0x22 */ s16 m22;
        /* 0x24 */ s16 m24;
        /* 0x26 */ s16 m26;
        /* 0x28 */ s16 m28;
        /* 0x2A */ s16 m2A;
        /* 0x2C */ s16 m2C;
        /* 0x2E */ s16 m2E;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ f32 m3C;
        /* 0x40 */ f32 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ f32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ s16 m50;
        /* 0x54 */ f32 m54;
        /* 0x58 */ f32 m58;
        /* 0x5C */ f32 m5C;
    }; // size = 0x60

    class Act_c : public dBgS_MoveBgActor {
        enum Prm_e {
            PRM_ITEMNO_W = 6,
            PRM_ITEMNO_S = 0,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,

            PRM_ITEMSAVE_W = 7,
            PRM_ITEMSAVE_S = 16,

            PRM_TYPE_W = 3,
            PRM_TYPE_S = 24,
            
            PRM_CULL_W = 3,
            PRM_CULL_S = 28,

            PRM_SHADOW_W = 1,
            PRM_SHADOW_S = 31,
        };

    public:
        Act_c();
        virtual ~Act_c() {}
        
        const Attr_c& attr() { return M_attr[m644]; }
        s32 prmZ_get_evId() const { return m64C; }
        s32 prm_get_cull() const { return daObj::PrmAbstract(this, PRM_CULL_W, PRM_CULL_S); }
        s32 prm_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
        s32 prm_get_itemSave() const { return daObj::PrmAbstract(this, PRM_ITEMSAVE_W, PRM_ITEMSAVE_S); }
        bool prm_get_shadow() const { return daObj::PrmAbstract(this, PRM_SHADOW_W, PRM_SHADOW_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        void prmZ_init();
        bool is_switch() const;
        void on_switch() const;
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        bool chk_appear();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void cull_set_draw();
        void cull_set_move();
        void damaged(int);
        bool damage_cc_proc();
        bool damage_bg_proc();
        bool damage_bg_proc_directly();
        void eff_m_break(unsigned short, unsigned short);
        void eff_b_break(unsigned short);
        void eff_break_ebrock();
        void eff_break_ekao();
        void eff_break_ebrock2();
        void eff_lift_smoke_start();
        void eff_lift_smoke_end();
        void eff_lift_smoke_remove();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_fine_init();
        void mode_fine();
        bool mode_proc_call();
        void demo_non_init();
        void demo_non();
        void demo_req_init();
        void demo_req();
        void demo_run_init();
        void demo_run();
        void demo_proc_call();
        virtual BOOL Execute(Mtx**);
        void draw_shadow();
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const dCcD_SrcCyl M_cyl_src;
        static const Attr_c M_attr[5];
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dBgS_ObjAcch mAcch;
        /* 0x498 */ dBgS_AcchCir mAcchCir;
        /* 0x4D8 */ dCcD_Stts mStts;
        /* 0x514 */ dCcD_Cyl mCyl;
        /* 0x644 */ s32 m644;
        /* 0x648 */ s32 m648;
        /* 0x64C */ s32 m64C;
        /* 0x650 */ s16 m650;
        /* 0x652 */ u16 m652;
        /* 0x654 */ s16 m654;
        /* 0x656 */ bool m656;
        /* 0x657 */ u8 m657;
        /* 0x658 */ u8 m658;
        /* 0x659 */ bool m659;
        /* 0x65A */ u8 m65A;
        /* 0x65C */ dPa_smokeEcallBack m65C;
        /* 0x67C */ cXyz m67C;
        /* 0x688 */ dPa_smokeEcallBack m688;
        /* 0x6A8 */ u8 m6A8;
        /* 0x6A9 */ u8 m6A9;
    }; // size = 0x6AC
};

#endif /* D_A_STONE2_H */
