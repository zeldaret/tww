#ifndef D_OVLP_FADE4_H
#define D_OVLP_FADE4_H

#include "d/d_drawlist.h"
#include "f_op/f_op_overlap_mng.h"

class dDlst_snapShot2_c : public dDlst_base_c {
public:
    ~dDlst_snapShot2_c() {}
    void draw();

    /* 0x04 */ void* field_0x4;
    /* 0x08 */ u16 field_0x8;
    /* 0x0A */ u16 field_0xa;
};

class dDlst_2Dt_Sp_c : public dDlst_base_c {
public:
    ~dDlst_2Dt_Sp_c() {}
    void draw();
    void init(ResTIMG*, f32, f32, f32, f32, GXColor);

    /* 0x04 */ GXTexObj field_0x4;
    /* 0x24 */ ResTIMG* field_0x24;
    /* 0x28 */ void* field_0x28;
    /* 0x2C */ u32 field_0x2c;
    /* 0x30 */ u32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ GXColor field_0x44;
    /* 0x48 */ f32 field_0x48;
};

class dDlst_2DtEff1_c : public dDlst_base_c {
public:
    ~dDlst_2DtEff1_c() {}
    void init(_GXColor);
    void draw();

    /* 0x004 */ f32 field_0x4;
    /* 0x008 */ u8 field_0x8[0xC - 0x8];
    /* 0x00C */ dDlst_snapShot2_c field_0xc;
    /* 0x018 */ dDlst_2Dt_Sp_c field_0x18;
    /* 0x064 */ dDlst_snapShot2_c field_0x64;
    /* 0x070 */ dDlst_2Dt_Sp_c field_0x70;
    /* 0x0BC */ dDlst_snapShot2_c field_0xbc;
    /* 0x0C8 */ dDlst_2Dt_Sp_c field_0xc8;
    /* 0x114 */ short field_0x114;
    /* 0x118 */ short field_0x118;
};

class dOvlpFd4_c : public overlap_task_class {
public:
    dOvlpFd4_c();
    void drawFadeOut();
    void drawFadeIn();
    void execFirstSnap();
    void execFadeOut();
    void execNextSnap();
    void execFadeIn();

    /* 0x0CC */ void (dOvlpFd4_c::*field_0xcc)();
    /* 0x0D8 */ void (dOvlpFd4_c::*field_0xd8)();
    /* 0x0E4 */ dDlst_snapShot2_c field_0xe4;
    /* 0x0F0 */ dDlst_snapShot2_c field_0xf0;
    /* 0x0FC */ dDlst_2Dt_Sp_c field_0xfc;
    /* 0x148 */ dDlst_2Dt_Sp_c field_0x148;
    /* 0x194 */ dDlst_2DtEff1_c field_0x194;
    /* 0x2AC */ u8 field_0x2ac;
    /* 0x2AD */ u8 field_0x2ad;
    /* 0x2AE */ u8 field_0x2ae;
    /* 0x2B0 */ short field_0x2b0;
    /* 0x2B4 */ f32 field_0x2b4;
    /* 0x2B8 */ u8 field_0x2b8[0x2BC - 0x2B8];
    /* 0x2BC */ f32 field_0x2bc;
    /* 0x2C0 */ u8 field_0x2c0;
    /* 0x2C1 */ u8 field_0x2c1;
    /* 0x2C2 */ u8 field_0x2c2[0x2C8 - 0x2C2];
    /* 0x2C8 */ f32 field_0x2c8;
    /* 0x2CC */ u8 field_0x2cc;
};

#endif /* D_OVLP_FADE4_H */
