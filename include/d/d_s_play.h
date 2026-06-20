#ifndef D_S_PLAY
#define D_S_PLAY

#include "d/d_stage.h"
#include "f_op/f_op_scene.h"
#include "m_Do/m_Do_hostIO.h"

class mDoDvdThd_toMainRam_c;

class dScnPly_ply_c : public scene_class {
public:
    s8 calcPauseTimer();
    bool resetGame();
    void offReset();

    static bool isPause() { return pauseTimer != 0; }
    static void setPauseTimer(s8 time) { nextPauseTimer = time; }

    static void onDebugPause() {}
    static void offDebugPause() {}

    static s8 pauseTimer;
    static s8 nextPauseTimer;

    /* 0x1C4 */ request_of_phase_process_class mLoadPhs;
    /* 0x1CC */ mDoDvdThd_toMainRam_c* sceneCommand;
};

class dScnPly_dark_HIO_c : public JORReflexible {
public:
    dScnPly_dark_HIO_c();
    virtual ~dScnPly_dark_HIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07[0x08 - 0x07];
    /* 0x08 */ dStage_darkStatus_c mDarkStatus;
};

class dScnPly_reg_childHIO_c : public JORReflexible {
public:
    dScnPly_reg_childHIO_c();
    virtual ~dScnPly_reg_childHIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ f32 mFloatRegs[30];
    /* 0x7C */ s16 mShortRegs[10];
};

class dScnPly_env_otherHIO_c : public JORReflexible {
public:
    dScnPly_env_otherHIO_c();
    virtual ~dScnPly_env_otherHIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ u8 field_0x0a;
    /* 0x0B */ u8 field_0x0b;
    /* 0x0C */ u8 field_0x0c;
    /* 0x0D */ u8 field_0x0d;
    /* 0x0E */ u8 field_0x0e;
    /* 0x0F */ u8 field_0x0f;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u16 field_0x18[20];
    /* 0x40 */ s16 field_0x40;
    /* 0x44 */ f32 field_0x44;
};

class dScnPly_env_debugHIO_c : public JORReflexible {
public:
    dScnPly_env_debugHIO_c();
    virtual ~dScnPly_env_debugHIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
};

class dScnPly_msg_HIO_c : public JORReflexible {
public:
    dScnPly_msg_HIO_c();
    void dScnPly_msg_HIO_checkUpdate(u8);
    void dScnPly_msg_HIO_setUpdate(u8);
    void dScnPly_msg_HIO_numUpdate(s16, s16);
    void dScnPly_msg_HIO_padCheck();
    void dScnPly_msg_HIO_messageProc();

    virtual ~dScnPly_msg_HIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 mIsUpdate;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ s16 mGroup;
    /* 0x0C */ s16 mID;
    /* 0x10 */ u32 field_0x10;
};

class dScnPly_preLoad_HIO_c : public mDoHIO_entry_c {
public:
    virtual ~dScnPly_preLoad_HIO_c() {}

    void genMessage(JORMContext* ctx);
};

class dScnPly_env_HIO_c : public JORReflexible {
public:
    virtual ~dScnPly_env_HIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ dScnPly_env_otherHIO_c mOther;
    /* 0x50 */ dScnPly_env_debugHIO_c mEnvDebug;
};

class dScnPly_reg_HIO_c {
public:
    virtual ~dScnPly_reg_HIO_c() {}

    /* 0x4 */ s8 mNo;
    /* 0x8 */ dScnPly_reg_childHIO_c mChild[22];
};

extern dScnPly_dark_HIO_c g_darkHIO;
extern dScnPly_reg_HIO_c g_regHIO;
extern dScnPly_env_HIO_c g_envHIO;
extern dScnPly_msg_HIO_c g_msgDHIO;

// Based on Twilight Princess debug, each g_regHIO child here was likely named after a specific developer.
// However, the developer name for each child isn't known here, so the below macro names are all unofficial.

/**
 * === Register Usage ===
 * Short Reg(00-09) ... -32768 - +32768
 * Float Reg(00-19) ... -100000.0 - +100000.0
 * Float Reg(20-24) ... 0.0 - 1.0
 * Float Reg(25-29) ... -1.0 - +1.0
 */

#define REG0_F(i) g_regHIO.mChild[0].mFloatRegs[i]
#define REG0_S(i) g_regHIO.mChild[0].mShortRegs[i]

#define REG1_F(i) g_regHIO.mChild[1].mFloatRegs[i]
#define REG1_S(i) g_regHIO.mChild[1].mShortRegs[i]

#define REG2_F(i) g_regHIO.mChild[2].mFloatRegs[i]
#define REG2_S(i) g_regHIO.mChild[2].mShortRegs[i]

#define REG3_F(i) g_regHIO.mChild[3].mFloatRegs[i]
#define REG3_S(i) g_regHIO.mChild[3].mShortRegs[i]

#define REG4_F(i) g_regHIO.mChild[4].mFloatRegs[i]
#define REG4_S(i) g_regHIO.mChild[4].mShortRegs[i]

#define REG5_F(i) g_regHIO.mChild[5].mFloatRegs[i]
#define REG5_S(i) g_regHIO.mChild[5].mShortRegs[i]

#define REG6_F(i) g_regHIO.mChild[6].mFloatRegs[i]
#define REG6_S(i) g_regHIO.mChild[6].mShortRegs[i]

#define REG7_F(i) g_regHIO.mChild[7].mFloatRegs[i]
#define REG7_S(i) g_regHIO.mChild[7].mShortRegs[i]

#define REG8_F(i) g_regHIO.mChild[8].mFloatRegs[i]
#define REG8_S(i) g_regHIO.mChild[8].mShortRegs[i]

#define REG9_F(i) g_regHIO.mChild[9].mFloatRegs[i]
#define REG9_S(i) g_regHIO.mChild[9].mShortRegs[i]

#define REG10_F(i) g_regHIO.mChild[10].mFloatRegs[i]
#define REG10_S(i) g_regHIO.mChild[10].mShortRegs[i]

#define REG11_F(i) g_regHIO.mChild[11].mFloatRegs[i]
#define REG11_S(i) g_regHIO.mChild[11].mShortRegs[i]

#define REG12_F(i) g_regHIO.mChild[12].mFloatRegs[i]
#define REG12_S(i) g_regHIO.mChild[12].mShortRegs[i]

#define REG13_F(i) g_regHIO.mChild[13].mFloatRegs[i]
#define REG13_S(i) g_regHIO.mChild[13].mShortRegs[i]

#define REG14_F(i) g_regHIO.mChild[14].mFloatRegs[i]
#define REG14_S(i) g_regHIO.mChild[14].mShortRegs[i]

#define REG15_F(i) g_regHIO.mChild[15].mFloatRegs[i]
#define REG15_S(i) g_regHIO.mChild[15].mShortRegs[i]

#define REG16_F(i) g_regHIO.mChild[16].mFloatRegs[i]
#define REG16_S(i) g_regHIO.mChild[16].mShortRegs[i]

#define REG17_F(i) g_regHIO.mChild[17].mFloatRegs[i]
#define REG17_S(i) g_regHIO.mChild[17].mShortRegs[i]

#define REG18_F(i) g_regHIO.mChild[18].mFloatRegs[i]
#define REG18_S(i) g_regHIO.mChild[18].mShortRegs[i]

#define REG19_F(i) g_regHIO.mChild[19].mFloatRegs[i]
#define REG19_S(i) g_regHIO.mChild[19].mShortRegs[i]

#define REG20_F(i) g_regHIO.mChild[20].mFloatRegs[i]
#define REG20_S(i) g_regHIO.mChild[20].mShortRegs[i]

#define REG21_F(i) g_regHIO.mChild[21].mFloatRegs[i]
#define REG21_S(i) g_regHIO.mChild[21].mShortRegs[i]

#endif /* D_S_PLAY */
