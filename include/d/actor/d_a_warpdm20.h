#ifndef D_A_WARPDM20_H
#define D_A_WARPDM20_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class mDoExt_btkAnm;
class mDoExt_brkAnm;
class mDoExt_bckAnm;

class daWarpdm20_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    inline void set_mtx();
    bool _execute();
    void normal_execute();
    void demo_execute();
    void demo_proc();
    void initWait(int);
    BOOL actWait(int);
    void initWait2(int);
    BOOL actWait2(int);
    void initWarp(int);
    BOOL actWarp(int);
    void initWaitDead(int);
    BOOL actWaitDead(int);
    void initDead(int);
    BOOL actDead(int);
    void initReturnWait(int);
    BOOL actReturnWait(int);
    void eventOrder();
    void checkOrder();
    void animPlay();
    void setEndAnm();
    f32 getSeaY(cXyz);
    BOOL set_effect(unsigned short);
    void set_wpsenko();
    void init_bck_anm(int);
    BOOL check_warp();
    bool _draw();

    static const char m_arcname[];
    static const s16 m_residxA[];
    static const s16 m_residxB[];
    static const u32 m_heapsize;
    static const f32 m_warp_distance;
    static const f32 m_eff_distance;

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A4 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2A8 */ u8 m2A8[0x2AC - 0x2A8];
    /* 0x2AC */ dPa_rippleEcallBack mRippleCallback;
    /* 0x2C0 */ u8 m2C0[0x2C8 - 0x2C0];
    /* 0x2C8 */ s32 m2C8;
    /* 0x2CC */ u8 m2CC;
    /* 0x2CD */ u8 m2CD[0x2D2 - 0x2CD];
    /* 0x2D2 */ s16 mEventIdx;
    /* 0x2D4 */ u8 m2D4[0x2D6 - 0x2D4];
    /* 0x2D6 */ u8 m2D6;
    /* 0x2D8 */ u32 m2D8;
    /* 0x2DC */ s32 mStaffIdx;
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ bool m2F8;
}; // size = 0x2FC

#endif /* D_A_WARPDM20_H */
