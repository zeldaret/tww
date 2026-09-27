#ifndef D_A_KDDOOR_H
#define D_A_KDDOOR_H

#include "d/d_cc_d.h"
#include "d/d_door.h"

class dBgW;

class dDoor_ssk_sub_c {
public:
    void init();
    void end();
    void openInit();
    BOOL openProc(dDoor_info_c*);
    void closeInit();
    BOOL closeProc(dDoor_info_c*);
    dDoor_ssk_sub_c();
    BOOL drawSet();
    void calcMtx(dDoor_info_c*, float, float, unsigned char);

public:
    /* 0x000 */ mDoExt_McaMorf* field_0x000;
    /* 0x004 */ mDoExt_McaMorf* field_0x004;
    /* 0x008 */ dPa_smokeEcallBack field_0x008;
    /* 0x028 */ dCcD_Stts field_0x028;
    /* 0x064 */ dCcD_Cyl field_0x064;
    /* 0x194 */ u8 field_0x194;
    /* 0x195 */ u8 field_0x195[0x196 - 0x195];
    /* 0x196 */ s16 field_0x196;
    /* 0x198 */ s16 field_0x198;
    /* 0x19A */ s16 field_0x19A;
    /* 0x19C */ s16 field_0x19C;
    /* 0x19E */ s16 field_0x19E;
    /* 0x1A0 */ cXyz field_0x1A0;
    /* 0x1AC */ cXyz field_0x1AC;
    /* 0x1B8 */ cXyz field_0x1B8;
    /* 0x1C4 */ u8 field_0x1C4;
    /* 0x1C5 */ u8 field_0x1C5;
    /* 0x1C6 */ u8 field_0x1C6[0x1C8 - 0x1C6];
};  // Size: 0x1C8

class dDoor_ssk_c {
public:
    void init(dDoor_info_c*);
    void end();
    void calcMtx(dDoor_info_c*);
    void execute(dDoor_info_c*);
    void draw(dDoor_info_c*);
    void closeInit();
    BOOL closeProc(dDoor_info_c*);
    void openInit();
    BOOL openProc(dDoor_info_c*);

public:
    /* 0x000 */ dDoor_ssk_sub_c field_0x000[3];
    /* 0x558 */ u8 field_0x558;
    /* 0x559 */ u8 field_0x559;
    /* 0x55A */ u8 field_0x55A;
    /* 0x55B */ u8 field_0x55B;
    /* 0x55C */ dKy_tevstr_c field_0x55C;
};  // Size: 0x60C

class daKddoor_c : public dDoor_info_c {
public:
    void checkFlag(unsigned short) {}
    inline BOOL execute();
    void offFlag(unsigned short) {}
    void onFlag(unsigned short) {}
    void setAction(unsigned char) {}

    BOOL chkMakeKey();
    void setKey();
    BOOL chkMakeStop();
    int chkStopF();
    int chkStopB();
    void setStop();
    BOOL chkGenocideCase();
    BOOL chkFeelerCase();
    BOOL chkStopOpen();
    void setStopDemo();
    BOOL chkStopClose();
    char* getBmdName();
    char* getBmdName2();
    char* getDzbName();
    BOOL CreateHeap();
    void setEventPrm();
    void openInit();
    void openProc();
    void openEnd();
    void closeInit();
    void closeProc();
    void closeEnd();
    void calcMtx();
    void CreateInit();
    cPhs_State create();
    void demoProc();
    BOOL draw();

public:
    /* 0x2D0 */ request_of_phase_process_class field_0x2D0;
    /* 0x2D8 */ dDoor_smoke_c field_0x2D8;
    /* 0x310 */ dDoor_key2_c field_0x310;
    /* 0x334 */ dDoor_ssk_c field_0x334;
    /* 0x940 */ J3DModel* field_0x940;
    /* 0x944 */ dBgW* field_0x944;
    /* 0x948 */ u8 field_0x948[0x94A - 0x948];
    /* 0x94A */ u16 field_0x94A;
    /* 0x94C */ f32 field_0x94C;
};  // Size: 0x950

#endif /* D_A_KDDOOR_H */
