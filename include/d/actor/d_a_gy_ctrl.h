#ifndef D_A_GY_CTRL_H
#define D_A_GY_CTRL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_lin_chk.h"

class daGy_Ctrl_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_0_e,
        PROC_1_e,
    };

    void getMode() {}
    void isTargetPlayer() {}
    void isTargetPlayerShip() {}

    void* searchNearActor(fopAc_ac_c*);
    void setTarget();
    bool setPathTargetPos();
    f32 getWaterY(cXyz&);
    bool lineCheck(cXyz*, cXyz*);
    bool checkPath();
    void setPathPos();
    void modeProc(Proc_e, int);
    void modeSwWaitInit();
    void modeSwWait();
    void modeCreateInit();
    void modeCreate();
    void modeWaitInit();
    void modeWait();
    void modeHideInit();
    void modeHide();
    void deadCheckGy();
    bool _execute();
    bool _draw();
    void createInitNoArer();
    void createInit();
    u8 getParam(unsigned long, unsigned char, unsigned char);
    void getArg();
    bool checkGyCtrlExist();
    cPhs_State _create();
    bool _delete();

public:
    /* 0x290 */ cXyz m290[5];
    /* 0x2CC */ cXyz m2CC[5];
    /* 0x308 */ s16 m308[5];
    /* 0x312 */ u8 m312[5];
    /* 0x318 */ f32 m318;
    /* 0x31C */ s32 m31C;
    /* 0x320 */ s32 m320;
    /* 0x324 */ int m324;
    /* 0x328 */ u8 m328;
    /* 0x329 */ u8 m329;
    /* 0x32C */ f32 m32C;
    /* 0x330 */ u8 m330;
    /* 0x331 */ u8 m331;
    /* 0x334 */ s32 m334;
    /* 0x338 */ cXyz m338;
    /* 0x344 */ u8 m344;
    /* 0x348 */ f32 m348;
    /* 0x34C */ s16 m34C;
    /* 0x350 */ int m350;
    /* 0x354 */ u8 m354[0x358 - 0x354];
    /* 0x358 */ int m358;
    /* 0x35C */ s32 m35C;
    /* 0x360 */ fpc_ProcID m360[5];
    /* 0x374 */ bool m374[5];
    /* 0x37C */ dBgS_ObjLinChk mLinChk;
    /* 0x3E8 */ u8 m3E8;
    /* 0x3EC */ cXyz m3EC[16];
#if VERSION > VERSION_DEMO
    /* 0x4AC */ bool m4AC;
    /* 0x4B0 */ int m4B0;
#endif
}; // size = 0x4B4

#endif /* D_A_GY_CTRL_H */
