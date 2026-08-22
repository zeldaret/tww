#ifndef D_A_OBJ_SWHAMMER_H
#define D_A_OBJ_SWHAMMER_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"

class J3DNode;

namespace daObjSwhammer {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,

            PRM_SWSAVE2_W = 0x08,
            PRM_SWSAVE2_S = 0,
        };

        BOOL is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void off_switch2() const { fopAcM_offSwitch(const_cast<Act_c*>(this), prm_get_swSave2()); }
        void on_switch() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
    
        Act_c();
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State _create();
        virtual BOOL Delete();
        bool _delete();
        void set_mtx();
        void init_mtx();
        void set_damage();
        void vib_start(s16, f32);
        void vib_proc();
        void crush_start();
        void crush_proc();
        void eff_crush();
        void calc_top_pos();
        static BOOL jnodeCB(J3DNode*, int);
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        virtual ~Act_c() {}

        static int M_damage;
        static s16 M_damage_dir;
        static Mtx M_tmp_mtx;
    
        static const char M_arcname[7];
        static const dCcD_SrcCyl M_cyl_src_co;
        static const dCcD_SrcCyl M_cyl_src_tg;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Cyl mCylCo;
        /* 0x404 */ dCcD_Stts mSttsCo;
        /* 0x440 */ dCcD_Cyl mCylTg;
        /* 0x570 */ dCcD_Stts mSttsTg;
        /* 0x5AC */ int mMode;
        /* 0x5B0 */ s16 mCrushTimer;
        /* 0x5B2 */ u8 mCrushState;
        /* 0x5B4 */ f32 mScaleYSpeed;
        /* 0x5B8 */ f32 mScaleY;
        /* 0x5BC */ f32 mAngleZ;
        /* 0x5C0 */ f32 mAngleX;
        /* 0x5C4 */ f32 mAngleSpeedZ;
        /* 0x5C8 */ f32 mAngleSpeedX;
        /* 0x5CC */ f32 mTargetHFrac;
        /* 0x5D0 */ f32 mCurHFrac;
        /* 0x5D4 */ f32 mVSpeed;
        /* 0x5D8 */ f32 mTopPos;
        /* 0x5DC */ dPa_smokeEcallBack mSmokeCb;
        /* 0x5FC */ bool m5FC;
    }; /* Size: 0x600 */

    STATIC_ASSERT(sizeof(Act_c) == 0x600);
};

#endif /* D_A_OBJ_SWHAMMER_H */
