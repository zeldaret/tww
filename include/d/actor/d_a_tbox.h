#ifndef D_A_TBOX_H
#define D_A_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daTbox_c : public fopAc_ac_c {
public:
    void action() {}
    void deleteProc() {}
    inline BOOL draw();
    void flagCheck(unsigned short) {}
    void flagClr() {}
    void flagOff(unsigned short) {}
    void flagOn(unsigned short) {}
    void getItemNo() {}
    void getPhase() {}
    void getSwNo() {}
    void getTboxNo() {}
    void setAction(int (daTbox_c::*)()) {}

    void searchRoomNo();
    void lightReady();
    void clrDzb();
    void setDzb();
    void surfaceProc();
    void CreateInit();
    void lightUpProc();
    void lightDownProc();
    void darkProc();
    void volmProc();
    void demoProcOpen();
    void demoInitAppear_Tact();
    void demoInitAppear();
    void demoProcAppear_Tact();
    void demoProcAppear();
    void OpenInit_com();
    void OpenInit();
    void setCollision();

public:
    /* 0x290 */ int mRoomNo;
    /* 0x294 */ request_of_phase_process_class mResLoadDalways;
    /* 0x29C */ J3DModel* mpModel1;
    /* 0x2A0 */ mDoExt_bckAnm mBckAnkm;
    /* 0x2B0 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2B4 */ mDoExt_brkAnm* m2B4;
    /* 0x2B8 */ cBgW* m2B8;
    /* 0x2BC */ void* m2BC;
    /* 0x2C0 */ void* m2C0;
    /* 0x2C4 */ void* m2C4;
    /* 0x2C8 */ void* m2C8;
    /* 0x2CC */ void* m2CC;
    /* 0x2D0 */ void* m2D0;
    /* 0x2D4 */ void* m2D4;
    /* 0x2D8 */ void* m2D8;
    /* 0x2DC */ void* m2DC;
    /* 0x2E0 */ void* m2E0;
    /* 0x2E4 */ void* m2E4;
    /* 0x2E8 */ void* m2E8;
    /* 0x2EC */ void* m2EC;
    /* 0x2F0 */ void* m2F0;
    /* 0x2F4 */ void* m2F4;
    /* 0x2F8 */ void* m2F8;
    /* 0x2FC */ void* m2FC;
    /* 0x300 */ void* m300;
    /* 0x304 */ void* m304;
    /* 0x308 */ void* m308;
    /* 0x30C */ u8 m30C[0x324 - 0x30C];
    /* 0x324 */ J3DModel* mpModel;
    /* 0x328 */ mDoExt_brkAnm m328;
    /* 0x340 */ u8 m340[0x350 - 0x340];
    /* 0x350 */ int mStaffId;
    /* 0x354 */ Mtx m354;
    /* 0x384 */ LIGHT_INFLUENCE mPLight;
    /* 0x3A4 */ LIGHT_INFLUENCE mEfLight;
    /* 0x3C4 */ u8 m3C4[0x3E4 - 0x3C4];
    /* 0x3E4 */ JPABaseEmitter* m3E4;
    /* 0x3E8 */ f32 mAllColRatio;
    /* 0x3EC */ u8 m3EC[0x3F0 - 0x3EC];
    /* 0x3F0 */ u16 m3F0;
    /* 0x3F2 */ s16 m3F2;
    /* 0x3F4 */ u8 m3F4[0x600 - 0x3F4];
    /* 0x600 */ dCcD_Stts mStts;
    /* 0x63C */ dCcD_Cyl mCyl;
    /* 0x76C */ u8 mChestOpenFlagIndex;
    /* 0x76D */ u8 m76D[0x770 - 0x76D];
};

#endif /* D_A_TBOX_H */
