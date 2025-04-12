#ifndef D_A_LWOOD_H
#define D_A_LWOOD_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class dBgW;

class daLwood_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    f32 getYureScale() const { return mScale; }
    s16 getYureTimer() const { return mTimer; }
    void setMoveBGMtx(); // weak but not inlined?
    void set_mtx(); // weak but not inlined?

    BOOL CreateHeap();
    void CreateInit();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mtx;
    /* 0x2D0 */ s16 mTimer;
    /* 0x2D4 */ f32 mScale;
};

#endif /* D_A_LWOOD_H */
