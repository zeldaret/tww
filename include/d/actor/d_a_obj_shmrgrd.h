#ifndef D_A_OBJ_SHMRGRD_H
#define D_A_OBJ_SHMRGRD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"

class dBgW;
class J3DNode;

class daObjShmrgrd_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_SWSAVE_W = 0x8,
        PRM_SWSAVE_S = 0x0,
    };

    void get_mode() {}
    BOOL is_switch() const {
        s32 swSave = prm_get_swSave();
        if (0xFF == swSave) {
            return false;
        } else {
            return fopAcM_isSwitch(const_cast<daObjShmrgrd_c*>(this), swSave);
        } 
    }
    void on_switch() const {
        s32 swSave = prm_get_swSave();
        if (0xFF != swSave) {
            fopAcM_onSwitch(const_cast<daObjShmrgrd_c*>(this), swSave);
        }
    }
    s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    daObjShmrgrd_c();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    cPhs_State _create();
    bool _delete();
    void search_target_next(daObjShmrgrd_c*);
    void register_list();
    void leave_list();
    void search_gap();
    void set_gap_co();
    void init_mtx();
    void set_mtx();
    void check_player_angle(fopAc_ac_c*);
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

    static const dCcD_SrcCyl M_cyl_src_co;
    static const dCcD_SrcCyl M_cyl_src_at;
    static const dCcD_SrcCyl M_cyl_src_tg;
    static const dCcD_SrcCyl M_cyl_src_gap_co;
    static const char M_arcname[];

public:
    u8 m290[0x298 - 0x290];
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ request_of_phase_process_class mPhs;
    /* 0x2A4 */ dCcD_Cyl mCylCo;
    /* 0x3D4 */ dCcD_Stts mSttsCo;
    /* 0x410 */ dCcD_Cyl mCylAt;
    /* 0x540 */ dCcD_Stts mSttsAt;
    /* 0x57C */ dCcD_Cyl mCylTg;
    /* 0x6AC */ dCcD_Stts mSttsTg;
    /* 0x6E8 */ dCcD_Cyl mCylGapCo;
    /* 0x818 */ dCcD_Stts mSttsGapCo;
    u8 m854[0x858 - 0x854];
    /* 0x858 */ s16 m858;
    u8 m85A[0x860 - 0x85A];
    /* 0x860 */ f32 m860;
    u8 m864[0x8A4 - 0x864];
    /* 0x8A4 */ Mtx mMtx;
    /* 0x2D4 */ dBgW* mpBgW;
}; // Size: 0x8D8

STATIC_ASSERT(sizeof(daObjShmrgrd_c) == 0x8D8);

#endif /* D_A_OBJ_SHMRGRD_H */
