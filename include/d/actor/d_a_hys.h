#ifndef D_A_HYS_H
#define D_A_HYS_H

#include "d/d_bg_s_movebg_actor.h"
#include "m_Do/m_Do_ext.h"

class daHys_c : public dBgS_MoveBgActor {
public:
    inline cPhs_State _create();
    void set_mtx();

    virtual BOOL Delete();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    virtual BOOL Execute(Mtx**);
    void mode_proc_call();
    void mode_wait();
    void mode_sw_on_init();
    void mode_sw_on();
    void mode_wait_init();
    virtual BOOL Draw();

    static const char* m_arcname[];
    static const s16 m_dzbidx[];
    static const u32 m_heapsize[];

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2E8 */ u8 field_0x2E8[0x450 - 0x2E8];
    /* 0x450 */ u32 field_0x450;
    /* 0x454 */ u32 field_0x454;
    /* 0x458 */ u8 field_0x458;
    /* 0x459 */ u8 mType;
    /* 0x45A */ u8 field_0x45A[0x45C - 0x45A];
};

#endif /* D_A_HYS_H */
