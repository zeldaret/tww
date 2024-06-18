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

    struct camera_rumble{
        int  mPatternIdx;
        u32  mPattern;
        s32  mLength;
        s32  mRounds;
        s32  mFlags;
        cXyz mCoord;
        s32  mCurrentFrame;
    }; // Size: 0x24

    struct motor_rumble{
        int mPatternIdx;
        u32 mPattern;
        s32 mLength;
        s32 mRounds;
        s32 mCurrentFrame;
        s32 mStopFrame; /* different from length for looping rumble */
    }; // Size: 0x12

    /* 0x0  */ struct camera_rumble mCameraShock;
    /* 0x24 */ struct camera_rumble mCameraQuake;
    /* 0x48 */ struct motor_rumble  mMotorShock;
    /* 0x60 */ struct motor_rumble  mMotorQuake;
    /* 0x78 */ s32 mFrameIdx;
    /* 0x7C */ int mRumbleState;
    /* 0x80 */ /* vtable */

public:
    dVibration_c();
    virtual ~dVibration_c();

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
