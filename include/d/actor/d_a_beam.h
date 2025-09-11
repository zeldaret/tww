#ifndef D_A_BEAM_H
#define D_A_BEAM_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_com_inf_game.h"

class JPABaseEmitter;
class daHot_Floor_c;

class daBeam_c : public fopAc_ac_c {
    typedef void (daBeam_c::*Func)();

public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    bool beamCheck() { return m690 != NULL; }
    void beamOff() {
        m690->becomeInvalidEmitter();
        m690 = NULL;
    }
    void beamOn() {
        m690 = dComIfGp_particle_set(dPa_name::ID_SCENE_8121, &current.pos);
    }
    bool checkHFloorParticle() { return !(s32)m5F8; }
    bool checkSmokeParticle() { return !(s32)m5F9; }
    void offHFloorParticle() { m5F8 = false; }
    void offSmokeParticle() { m5F9 = false; }
    void onHFloorParticle() { m5F8 = true; }
    void onSmokeParticle() { m5F9 = true; }
    void setDefaultProc(Func func) { m55C = func; }
    void setEmitterOffset(float) {}
    void setPosAngle(cXyz&, csXyz&) {}
    void setSearchProc(Func func) { m550 = func; }

    void set_mtx();
    BOOL CreateHeap();
    cPhs_State CreateInit();
    bool _execute();
    BOOL checkRange(csXyz*);
    void move_search();
    void fix_search();
    void timer_change();
    void wait_proc();

    static const char M_arcname[];

public:
    /* 0x290 */ dCcD_Stts mStts;
    /* 0x2CC */ dCcD_Cps mCps1;
    /* 0x404 */ dCcD_Cps mCps2;
    /* 0x53C */ u8 m53C;
    /* 0x540 */ cXyz m540;
    /* 0x54C */ u8 m54C;
    /* 0x550 */ Func m550;
    /* 0x55C */ Func m55C;
    /* 0x568 */ request_of_phase_process_class mPhase;
    /* 0x570 */ J3DModel* M_mdl;
    /* 0x574 */ J3DAnmTransform* M_bck;
    /* 0x578 */ mDoExt_bckAnm mBckAnm;
    /* 0x5A8 */ f32 m588;
    /* 0x58C */ J3DAnmTevRegKey* M_brk;
    /* 0x590 */ mDoExt_brkAnm mBrkAnm;
    /* 0x5A8 */ f32 m5A8;
    /* 0x5AC */ J3DAnmTextureSRTKey* M_btk;
    /* 0x5B0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x5C4 */ Mtx m5C4;
    /* 0x5F4 */ s16 m5F4;
    /* 0x5F6 */ s16 m5F6;
    /* 0x5F8 */ bool m5F8;
    /* 0x5F9 */ bool m5F9;
    /* 0x5FC */ dBgS_ObjLinChk mLinChk;
    /* 0x668 */ cXyz m668;
    /* 0x674 */ Quaternion m674;
    /* 0x684 */ fpc_ProcID m684;
    /* 0x688 */ f32 m688;
    /* 0x68C */ daHot_Floor_c* m68C;
    /* 0x690 */ JPABaseEmitter* m690;
    /* 0x694 */ f32 m694;
    /* 0x698 */ s32 m698;
}; // size = 0x69C

class daBeam_HIO_c : public JORReflexible {
public:
    daBeam_HIO_c();
    virtual ~daBeam_HIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
}; // size = 0x10

#endif /* D_A_BEAM_H */
