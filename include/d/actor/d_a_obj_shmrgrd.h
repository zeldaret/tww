#ifndef D_A_OBJ_SHMRGRD_H
#define D_A_OBJ_SHMRGRD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/d_particle.h"

class dBgW;
class J3DNode;

class daObjShmrgrd_c : public fopAc_ac_c {
public:
    enum Mode_e {
        MODE_UPPER = 0,
        MODE_U_L = 1,
        MODE_LOWER = 2
    };

    enum Prm_e {
        PRM_SWSAVE_W = 0x8,
        PRM_SWSAVE_S = 0x0,
    };

    Mode_e get_mode() { return mMode; }
    bool is_switch() const {
        if (prm_get_swSave() == 0xFF) {
            return false;
        } else {
            return fopAcM_isSwitch(const_cast<daObjShmrgrd_c*>(this), prm_get_swSave());
        }
    }
    void on_switch() const {
        if (prm_get_swSave() != 0xFF) {
            fopAcM_onSwitch(const_cast<daObjShmrgrd_c*>(this), prm_get_swSave());
        }
    }
    s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    daObjShmrgrd_c();
    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
    bool _delete();
    daObjShmrgrd_c* search_target_next(daObjShmrgrd_c*);
    void register_list();
    void leave_list();
    daObjShmrgrd_c* search_gap();
    void set_gap_co();
    void init_mtx();
    void set_mtx();
    BOOL check_player_angle(fopAc_ac_c*);
    void set_damage();
    void vib_start(short, float);
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
    bool _execute();
    bool _draw();

    virtual ~daObjShmrgrd_c() {}

    static int M_damage;
    static short M_damage_dir;
    static daObjShmrgrd_c* M_list_p;

    static const dCcD_SrcCyl M_cyl_src_co;
    static const dCcD_SrcCyl M_cyl_src_at;
    static const dCcD_SrcCyl M_cyl_src_tg;
    static const dCcD_SrcCyl M_cyl_src_gap_co;
    static const char M_arcname[8];

public:
    /* 0x290 */ // vtable
    /* 0x294 */ daObjShmrgrd_c* mpNext;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ request_of_phase_process_class mPhs;
    /* 0x2A4 */ dCcD_Cyl mCylCo;
    /* 0x3D4 */ dCcD_Stts mSttsCo;
    /* 0x410 */ dCcD_Cyl mCylTg;
    /* 0x540 */ dCcD_Stts mSttsTg;
    /* 0x57C */ dCcD_Cyl mCylAt;
    /* 0x6AC */ dCcD_Stts mSttsAt;
    /* 0x6E8 */ dCcD_Cyl mCylGapCo;
    /* 0x818 */ dCcD_Stts mSttsGapCo;
    /* 0x854 */ Mode_e mMode;
    /* 0x858 */ s16 mCrushTimer;
    /* 0x85A */ u8 mCrushState;
    /* 0x85C */ f32 m85C; // unused
    /* 0x860 */ f32 mScaleY;
    /* 0x864 */ f32 mAngleZ;
    /* 0x868 */ f32 mAngleX;
    /* 0x86C */ f32 mAngleSpeedZ;
    /* 0x870 */ f32 mAngleSpeedX;
    /* 0x874 */ f32 mTargetHFrac;
    /* 0x878 */ f32 mCurHFrac;
    /* 0x87C */ f32 mVSpeed;
    /* 0x880 */ f32 mTopPos;
    /* 0x884 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x8A4 */ Mtx mMtx;
    /* 0x2D4 */ dBgW* mpBgW;
}; // Size: 0x8D8

STATIC_ASSERT(sizeof(daObjShmrgrd_c) == 0x8D8);

#endif /* D_A_OBJ_SHMRGRD_H */
