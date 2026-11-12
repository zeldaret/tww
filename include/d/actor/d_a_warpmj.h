#ifndef D_A_WARPMJ_H
#define D_A_WARPMJ_H

#include "f_op/f_op_actor.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_ext.h"

class JPABaseEmitter;

class daWarpmj_c : public fopAc_ac_c {
public:
    inline void set_mtx(); // weak but not inlined?

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _execute();
    void normal_execute();
    void demo_execute();
    void demo_proc();
    void initWait(int);
    BOOL actWait(int);
    void initWarp(int);
    BOOL actWarp(int);
    void initWarpArrive(int);
    BOOL actWarpArrive(int);
    void eventOrder();
    void checkOrder();
    void animPlay();
    void setEndAnm();
    f32 getSeaY(cXyz);
    BOOL check_warp();
    bool _draw();

    static const char m_arcname[];
    static const u32 m_heapsize;
    static const f32 m_warp_distance;

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A4 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2A8 */ JPABaseEmitter* mpEmitter1;
    /* 0x2AC */ JPABaseEmitter* mpEmitter2;
    /* 0x2B0 */ JPABaseEmitter* mpEmitter3;
    /* 0x2B4 */ u32 mSceneNo;
    /* 0x2B8 */ s32 mOrder;
    /* 0x2BC */ s16 mEventIdx;
    /* 0x2C0 */ u32 mDemoShape;
    /* 0x2C4 */ s32 mStaffId;
    /* 0x2C8 */ dKy_tevstr_c mTevStr;
};  // Size: 0x378

#endif /* D_A_WARPMJ_H */
