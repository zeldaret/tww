#ifndef D_A_MBDOOR_H
#define D_A_MBDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class daMbdoor_c : public fopAc_ac_c {
public:
    void draw() {}
    void execute() {}
    void setAction(unsigned char) {}

    void calcMtx();
    void demoProc();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpFuModel;
    /* 0x29C */ J3DModel* mpLModel;
    /* 0x2A0 */ J3DModel* mpRModel;
    /* 0x2A4 */ J3DModel* mpToModel;
    /* 0x2A8 */ dBgW* mpBgW;
    /* 0x2AC */ bool m2AC;
    /* 0x2AD */ u8 m2AD;
    /* 0x2AE */ u8 mCurActionIdx;
    /* 0x2AF */ u8 m2AF[0x2B0 - 0x2AF];
    /* 0x2B0 */ s16 m2B0;
    /* 0x2B2 */ s16 m2B2;
    /* 0x2B4 */ s16 m2B4;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ u8 m2B7[0x2B8 - 0x2B7];
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ u8 m2BA[0x2BC - 0x2BA];
    /* 0x2BC */ int m2BC;
    /* 0x2C0 */ int mEvtStaffId;
    /* 0x2C4 */ cXyz m2C4;
    /* 0x2D0 */ cXyz m2D0;
    /* 0x2DC */ cXyz m2DC;
};

#endif /* D_A_MBDOOR_H */
