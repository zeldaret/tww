#ifndef D_D_VIBRATION_H
#define D_D_VIBRATION_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"

class dVibration_c {
public:

    struct vib_pattern {
        u16 rounds;  /* Number of random bits enabled, used by quakes */
        u16 length;  /* length of the pattern */
        u32 pattern; /* pattern bits (interpreted as bitstring) */
    };

    enum { /* mRumbleState values */
        RUMBLE_STATE_PAUSED  = -1,
        RUMBLE_STATE_WAITING =  0,
        RUMBLE_STATE_RUNNING =  1,
    };
    enum { /* Used as flags */
        RUMBLE_SHOCK = 0x1,
        RUMBLE_QUAKE = 0x2,
    };

    static const struct vib_pattern MS_patt[26];
    static const struct vib_pattern CS_patt[26];
    static const struct vib_pattern MQ_patt[12];
    static const struct vib_pattern CQ_patt[12];

    struct {
        struct {
            /* 0x00 */ int  mPatternIdx;
            /* 0x04 */ u32  mPattern;
            /* 0x08 */ s32  mLength;
            /* 0x0C */ s32  mRounds;
            /* 0x10 */ s32  mFlags;
            /* 0x14 */ cXyz mCoord;
            /* 0x20 */ s32  mCurrentFrame;
        } /* 0x00 */ mShock,
          /* 0x24 */ mQuake;
    } /* 0x00 */ mCamera;

    struct {
        struct {
            /* 0x00 */ int mPatternIdx;
            /* 0x04 */ u32 mPattern;
            /* 0x08 */ s32 mLength;
            /* 0x0C */ s32 mRounds;
            /* 0x10 */ s32 mCurrentFrame;
            /* 0x14 */ s32 mStopFrame; /* different from length for looping rumble */
        } /* 0x00 */ mShock,
          /* 0x18 */ mQuake;
    } /* 0x48 */ mMotor;

    /* 0x78 */ s32 mFrameIdx;
    /* 0x7C */ int mRumbleState;
    /* 0x80 */ /* vtable */

public:
#if VERSION == VERSION_DEMO
    dVibration_c() { setDefault(); }
    virtual ~dVibration_c() { Kill(); }
#else
    dVibration_c();
    virtual ~dVibration_c();
#endif

    int Run();
    bool StartShock(int, int, cXyz);
    bool StartQuake(u8 const*, int, int, cXyz);
    bool StartQuake(int, int, cXyz);
    int StopQuake(int);
    void Kill();
    bool CheckQuake();
    void setDefault();
    void Init();
    void Pause();
    void Remove();

    /* Probably debug-only function not present in release build */
    inline void testShake() {}

};  // Size: 0x84

#endif /* D_D_VIBRATION_H */
