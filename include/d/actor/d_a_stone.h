#ifndef D_A_STONE_H
#define D_A_STONE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "SSystem/SComponent/c_angle.h"

namespace daStone {
    static BOOL CreateHeapCB(fopAc_ac_c*);

    enum DataFlag_e {
        DATAFLG_0_e  = 0,
        DATAFLG_1_e  = 1 << 0,
        DATAFLG_2_e  = 1 << 1,
        DATAFLG_4_e  = 1 << 2,
        DATAFLG_8_e  = 1 << 3,
        DATAFLG_10_e = 1 << 4,
    };
    
    struct Data_c {
        /* 0x00 */ f32 m00;
        /* 0x04 */ f32 m04;
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ u8 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 m24;
        /* 0x28 */ s16 m28;
        /* 0x2A */ s16 m2A;
        /* 0x2C */ s16 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ f32 m3C;
        /* 0x40 */ s16 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ f32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ f32 m50;
        /* 0x54 */ f32 m54;
        /* 0x58 */ f32 m58;
        /* 0x5C */ f32 m5C;
        /* 0x60 */ f32 m60;
        /* 0x64 */ f32 m64;
        /* 0x68 */ u8 m68;
        /* 0x69 */ u8 m69;
        /* 0x6A */ u8 m6A;
        /* 0x6B */ u8 m6B;
        /* 0x6C */ u8 m6C;
        /* 0x6D */ u8 m6D;
        /* 0x70 */ u32 m70;
        /* 0x74 */ const char* m74;
        /* 0x78 */ u32 m78;
        /* 0x7C */ u16 m7C;
        /* 0x7E */ u8 m7E;
        /* 0x80 */ s16 shadowScaleXZ;
        /* 0x82 */ s16 m82;
        /* 0x84 */ s16 m84;
        /* 0x86 */ s16 m86;
        /* 0x88 */ u16 m88;
        /* 0x8C */ u32 m8C;
        /* 0x90 */ u32 m90;
        /* 0x94 */ u32 m94;
        /* 0x98 */ u32 m98;
        /* 0x9C */ u32 m9C;
        /* 0xA0 */ s16 mA0;
        /* 0xA0 */ s16 mA2;
        /* 0xA0 */ s16 mA4;
        /* 0xA0 */ s16 mA6;
        /* 0xA8 */ s16 mA8;
        /* 0xAA */ s16 mAA;
        /* 0xAC */ s16 mAC;
        /* 0xAE */ s16 mAE;
        /* 0xB0 */ f32 mB0;
    }; // size = 0xB4
    
    class Act_c : public fopAc_ac_c {
        enum Prm_e {
            PRM_TYPE_W = 3,
            PRM_TYPE_S = 24,

            PRM_MOVEBG_W = 2,
            PRM_MOVEBG_S = 6,

            PRM_CULL_W = 3,
            PRM_CULL_S = 28,

            PRM_ITEMNO_W = 6,
            PRM_ITEMNO_S = 0,

            PRM_ITEMSAVE_W = 7,
            PRM_ITEMSAVE_S = 16,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,
        };
        
    public:
        const Data_c& data() { return M_data[m670]; }
        s32 prm_get_cull() const { return daObj::PrmAbstract(this,PRM_CULL_W, PRM_CULL_S); }
        s32 prm_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
        s32 prm_get_itemSave() const { return daObj::PrmAbstract(this, PRM_ITEMSAVE_W, PRM_ITEMSAVE_S); }
        bool prm_get_moveBg() const { return daObj::PrmAbstract(this, PRM_MOVEBG_W, PRM_MOVEBG_S) == 1UL; }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        void prm_off_moveBg() { fopAcM_SetParam(this, fopAcM_GetParam(this) | 0xC0); }
        
        bool create_heap();
        bool chk_appear();
        cPhs_State _create();
        bool _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_sink_init();
        void mode_sink();
        bool mode_proc_call();
        void cull_set_draw();
        void cull_set_move();
        void damaged(int);
        bool damage_cc_proc();
        bool damage_bg_proc();
        bool damage_bg_proc_directly();
        void set_mtx();
        void init_mtx();
        void init_rot_throw();
        void init_rot_clean();
        void set_drop_rot();
        void set_sink_rot();
        void eff_break();
        void eff_hit_water_splash();
        void eff_hit_lava_splash();
        void eff_land_smoke();
        void bg_crr_water();
        void bg_crr_lava();
        bool chk_sink_lava();
        bool chk_sink_water();
        void water_tention();
        void se_fall_water();
        void se_fall_lava();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        bool _execute();
        bool _draw();

        static cXyz M_axis;
        static const Data_c M_data[5];
        static const char M_arcname_Always[];
        static const char M_arcname_Ebrock[];
        static const char M_arcname_Ekao[];
        static const dCcD_SrcCyl M_cyl_src;

#if VERSION == VERSION_DEMO
        static dBgS_ObjGndChk_Yogan M_bg_lava;
#endif
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ dBgS_ObjAcch mAcch;
        /* 0x460 */ dBgS_AcchCir mAcchCir;
#if VERSION == VERSION_DEMO
        /* 0x4F4 */ f32 m4F4;
#else
        /* 0x4A0 */ dBgS_ObjGndChk_Yogan mGndChkYogan;
        /* 0x4F4 */ cXyz m4F4;
        /* 0x500 */ bool m500;
        /* 0x501 */ bool m501;
#endif
        /* 0x504 */ dCcD_Stts mStts;
        /* 0x540 */ dCcD_Cyl mCyl;
        /* 0x670 */ s32 m670;
        /* 0x674 */ s32 m674;
        /* 0x678 */ u8 m678;
        /* 0x679 */ s8 m679;
        /* 0x67A */ u8 m67A;
        /* 0x67B */ u8 m67B;
        /* 0x67C */ cSAngle m67C;
        /* 0x67E */ cSAngle m67E;
        /* 0x680 */ cSAngle m680;
        /* 0x682 */ cSAngle m682;
        /* 0x684 */ cSAngle m684;
        /* 0x686 */ cSAngle m686;
        /* 0x688 */ f32 m688;
        /* 0x68C */ bool m68C;
        /* 0x68D */ u8 m68D;
    }; // size = 0x690
    
    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_STONE_H */
