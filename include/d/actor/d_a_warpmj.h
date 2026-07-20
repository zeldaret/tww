#ifndef D_A_WARPMJ_H
#define D_A_WARPMJ_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class mDoExt_btkAnm;
class mDoExt_brkAnm;
class mDoExt_bckAnm;
class JPABaseEmitter;

class daWarpmj_c : public fopAc_ac_c {
public:
    inline void set_mtx();

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _execute();
    void normal_execute();
    void demo_execute();
    void demo_proc();
    void initWait(int);
    int actWait(int);
    void initWarp(int);
    int actWarp(int);
    void initWarpArrive(int);
    int actWarpArrive(int);
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
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A4 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2A8 */ JPABaseEmitter* mpEmitterMajyuWarpA;
    /* 0x2AC */ JPABaseEmitter* mpEmitterMajyuWarpB;
    /* 0x2B0 */ JPABaseEmitter* mpEmitterMajyuWarpC;
    /* 0x2B4 */ u32 mSceneNo;
    /* 0x2B8 */ BOOL m2B8;
    /* 0x2BC */ s16 mEvtToGanonWarpIdx;
    /* 0x2BE */ u8 m2BE[0x2C0 - 0x2BE];
    /* 0x2C0 */ u32 mDemoShapeId;
    /* 0x2C4 */ int mStaffIdx;
    /* 0x2C8 */ dKy_tevstr_c mTevStr;

}; // Size: 0x378

namespace daWarpmj_prm {
inline u32 getSceneNo(daWarpmj_c* i_this) {
    return fopAcM_GetParam(i_this) & 0xFF;
}
} // namespace daWarpmj_prm

#endif /* D_A_WARPMJ_H */
