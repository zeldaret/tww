#ifndef D_S_PLAY
#define D_S_PLAY

#include "d/d_stage.h"
#include "f_op/f_op_scene_mng.h"
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

    /* 0x04 */ s8 mChildID;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07[0x08 - 0x07];
    /* 0x08 */ dStage_darkStatus_c mDarkStatus;
};

class dScnPly_reg_childHIO_c : public JORReflexible {
public:
    dScnPly_reg_childHIO_c();
    virtual ~dScnPly_reg_childHIO_c() {}

    /* 0x04 */ f32 mFloatRegs[30];
    /* 0x7C */ s16 mShortRegs[10];
};

class dScnPly_env_otherHIO_c : public JORReflexible {
public:
    dScnPly_env_otherHIO_c();
    virtual ~dScnPly_env_otherHIO_c() {}

    /* 0x04 */ s8 mChildID;
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

    /* 0x04 */ s8 mChildID;
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

    /* 0x04 */ s8 mChildID;
    /* 0x05 */ u8 mIsUpdate;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ s16 mGroup;
    /* 0x0C */ s16 mID;
    /* 0x10 */ u32 field_0x10;
};

extern dScnPly_msg_HIO_c g_msgDHIO;

class dScnPly_preLoad_HIO_c : public mDoHIO_entry_c {
public:
    virtual ~dScnPly_preLoad_HIO_c() {}
};

class dScnPly_env_HIO_c : public JORReflexible {
public:
    virtual ~dScnPly_env_HIO_c() {}

    /* 0x04 */ s8 mChildID;
    /* 0x08 */ dScnPly_env_otherHIO_c mOther;
    /* 0x50 */ dScnPly_env_debugHIO_c mEnvDebug;
};

class dScnPly_reg_HIO_c {
public:
    virtual ~dScnPly_reg_HIO_c() {}

    /* 0x4 */ s8 mChildID;
    /* 0x8 */ dScnPly_reg_childHIO_c mChild[22];
};

extern dScnPly_reg_HIO_c g_regHIO;
extern dScnPly_env_HIO_c g_envHIO;

#endif /* D_S_PLAY */
