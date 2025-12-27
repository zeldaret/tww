#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include "JSystem/JKernel/JKRDisposer.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/pad/Pad.h"
#include "dolphin/types.h"

typedef void (*callbackFn)(int, void*);

extern u32 channel_mask[4];

namespace CButton {
enum {
    /* 0x0001 */ DPAD_LEFT = 0x0001,
    /* 0x0002 */ DPAD_RIGHT = 0x0002,
    /* 0x0004 */ DPAD_DOWN = 0x0004,
    /* 0x0008 */ DPAD_UP = 0x0008,
    /* 0x0010 */ Z = 0x0010,
    /* 0x0020 */ R = 0x0020,
    /* 0x0040 */ L = 0x0040,
    /* 0x0100 */ A = 0x0100,
    /* 0x0200 */ B = 0x0200,
    /* 0x0400 */ X = 0x0400,
    /* 0x0800 */ Y = 0x0800,
    /* 0x1000 */ START = 0x1000,
};
}

struct JUTGamePadRecordBase {
    virtual void unk0() {}
    virtual void unk1(PADStatus* pad) {}
    virtual void write(PADStatus* pad) {}

    /* 0x4 */ bool mActive;
};

struct JUTGamePad : public JKRDisposer {
public:
    enum EStickMode {
        STICK_MODE_1 = 1,
    };
    enum EWhichStick {
        WS_MAIN_STICK,
        WS_SUB_STICK,
    };
    enum EPadPort {
        Port_Unknown = -1,
        Port_1,
        Port_2,
        Port_3,
        Port_4,
    };

    JUTGamePad(JUTGamePad::EPadPort port);
    virtual ~JUTGamePad();

    void initList();
    static s32 init();
    void clear();
    static u32 read();
    void assign();
    void checkResetCallback(OSTime unk);
    void update();
    void stopPatternedRumble() { mRumble.stopPatternedRumble(mPortNum); }
    static void checkResetSwitch();
    static void clearForReset();
    static JUTGamePad* getGamePad(int pad_index);
    static bool recalibrate(u32 pad_mask);

    static void setAnalogMode(u32 mode) {
        sAnalogMode = mode;
        PADSetAnalogMode(mode);
    }

    static void clearResetOccurred() { C3ButtonReset::sResetOccurred = false; }

    static void setResetCallback(callbackFn callback, void* param_0) {
        C3ButtonReset::sCallback = callback;
        C3ButtonReset::sCallbackArg = param_0;
    }

    u32 getButton() const { return mButton.mButton; }
    u32 getTrigger() const { return mButton.mTrigger; }
    u32 getRelease() const { return mButton.mRelease; }
    u32 getRepeat() const { return mButton.mRepeat; }

    f32 getMainStickX() const { return mMainStick.mPosX; }
    f32 getMainStickY() const { return mMainStick.mPosY; }
    f32 getMainStickValue() const { return mMainStick.mValue; }
    s16 getMainStickAngle() const { return mMainStick.mAngle; }

    f32 getSubStickX() const { return mSubStick.mPosX; }
    f32 getSubStickY() const { return mSubStick.mPosY; }
    f32 getSubStickValue() const { return mSubStick.mValue; }
    s16 getSubStickAngle() const { return mSubStick.mAngle; }

    u8 getAnalogA() const { return mButton.mAnalogA; }
    u8 getAnalogB() const { return mButton.mAnalogB; }

    u8 getAnalogL() const { return mButton.mAnalogL; }
    f32 getAnalogLf() const { return mButton.mAnalogLf; }

    u8 getAnalogR() const { return mButton.mAnalogR; }
    f32 getAnalogRf() const { return mButton.mAnalogRf; }

    s8 getErrorStatus() const { return mErrorStatus; }
    s16 getPortNum() const { return mPortNum; }

    JUTGamePadRecordBase* getPadReplay() const { return mPadReplay; }
    JUTGamePadRecordBase* getPadRecord() const { return mPadRecord; }

    bool testButton(u32 button) const { return mButton.mButton & button; }
    bool testTrigger(u32 button) const { return mButton.mTrigger & button; }

    bool isPushing3ButtonReset() const {
        bool isPushingReset = false;

        if (mPortNum != -1 && mButtonReset.mReset != false) {
            isPushingReset = true;
        }
        return isPushingReset;
    }

    void stopMotorWave() { mRumble.stopPatternedRumbleAtThePeriod(); }
    void stopMotor() { mRumble.stopMotor(mPortNum); }
    void stopMotorHard() { mRumble.stopMotorHard(mPortNum); }

    static PADStatus & getPortStatus(EPadPort port) { return mPadStatus[port]; }

    struct CButton {
        CButton() { clear(); }
        void clear();
        void update(PADStatus const*, u32 unk);
        void setRepeat(u32 unk0, u32 unk1, u32 unk2);

        /* 0x00 */ u32 mButton;
        /* 0x04 */ u32 mTrigger;  // Pressed Buttons
        /* 0x08 */ u32 mRelease;  // Released Buttons
        /* 0x0C */ u8 mAnalogA;
        /* 0x0D */ u8 mAnalogB;
        /* 0x0E */ u8 mAnalogL;
        /* 0x0F */ u8 mAnalogR;
        /* 0x10 */ f32 mAnalogLf;
        /* 0x14 */ f32 mAnalogRf;
        /* 0x18 */ u32 mRepeat;
        /* 0x1C */ u32 field_0x1c;
        /* 0x20 */ u32 field_0x20;
        /* 0x24 */ u32 field_0x24;
        /* 0x28 */ u32 field_0x28;
        /* 0x2C */ u32 field_0x2c;
    };  // Size: 0x30

    struct C3ButtonReset {
        C3ButtonReset() { mReset = false; }

        static u32 sResetPattern;
        static u32 sResetMaskPattern;
        static callbackFn sCallback;
        static void* sCallbackArg;
        static OSTime sThreshold;
        static s32 sResetOccurredPort;
        static bool sResetOccurred;
        static bool sResetSwitchPushing;

        /* 0x0 */ bool mReset;
    };  // Size: 0x4

    struct CStick {
        static f32 sPressPoint;
        static f32 sReleasePoint;

        CStick() { clear(); }
        void clear();
        void clear(JUTGamePad* pad);
        u32 update(s8 unk0, s8 unk1, JUTGamePad::EStickMode mode, JUTGamePad::EWhichStick stick);
        u32 getButton();

        /* 0x0 */ f32 mPosX;
        /* 0x4 */ f32 mPosY;
        /* 0x8 */ f32 mValue;
        /* 0xC */ s16 mAngle;
        /* 0xE */ s8 field_0xe;
        /* 0xF */ s8 field_0xf;
    };  // Size: 0x10

    void stopMotorWaveHard() { mRumble.stopPatternedRumble(mPortNum); }

    struct CRumble {
        CRumble(JUTGamePad* pad) { clear(pad); }

        static u8 mStatus[4];
        static PADMask mEnabled;

        enum ERumble {
            LOOP_ONCE    = 0,
            LOOP_FOREVER = 1,
            SET_DURATION = 2,
        };

        void clear();
        void clear(JUTGamePad* pad);
        static void startMotor(int channel);
        static void stopMotor(int channel);
        static void stopMotorHard(int channel);
        void update(s16 unk0);
        void triggerPatternedRumble(u32 unk0);
        void startPatternedRumble(u8* unk0, ERumble rumble, u32 unk1);
        void stopPatternedRumble(s16 pad_port);
        void stopPatternedRumbleAtThePeriod();
        static void setEnabled(u32 pad_mask);

        static bool isEnabled(u32 mask) { return mEnabled & mask; }
        static bool isEnabledPort(int port) { return isEnabled(channel_mask[port]); }

        /* 0x00 */ u32 mFrame;
        /* 0x04 */ u32 mLength;
        /* 0x08 */ u8* mData;
        /* 0x0C */ u32 mFrameCount;
    };  // Size: 0x10

    void startMotorWave(u8* param_2, CRumble::ERumble rumble, u32 param_4) {
        mRumble.startPatternedRumble(param_2, rumble, param_4);
    }

    // TODO:
    void isResetOccurred(int*) {}
    void suppressPadReset(u32) {}

    /* 0x18 */ CButton mButton;
    /* 0x48 */ CStick mMainStick;
    /* 0x58 */ CStick mSubStick;
    /* 0x68 */ CRumble mRumble;
    /* 0x78 */ s16 mPortNum;
    /* 0x7A */ s8 mErrorStatus;
    /* 0x7C */ JSULink<JUTGamePad> mLink;
    /* 0x8C */ JUTGamePadRecordBase* mPadRecord;
    /* 0x90 */ JUTGamePadRecordBase* mPadReplay;
    /* 0x94 */ u8 field_0x94[4];
    /* 0x98 */ C3ButtonReset mButtonReset;
    /* 0x9C */ OSTime mResetTime;

    static JSUList<JUTGamePad> mPadList;
    static bool mListInitialized;
    static PADStatus mPadStatus[4];
    static CButton mPadButton[4];
    static CStick mPadMStick[4];
    static CStick mPadSStick[4];
    static EStickMode sStickMode;
    static u32 sClampMode;
    static u8 mPadAssign[4];
    static u32 mSuppressPadReset;
    static s32 sAnalogMode;
    static u32 sRumbleSupported;
};

struct JUTGamePadLongPress {
    static JSUList<JUTGamePadLongPress> sPatternList;
    void checkCallback(int port, u32 timer);

    u32 getMaskPattern() const { return mMaskPattern; }
    u32 getPattern() const { return mPattern; }

    /* 0x00 */ u8 field_0x0[0x10];
    /* 0x10 */ bool mValid;
    /* 0x11 */ bool field_0x11;
    /* 0x14 */ u32 mPattern;
    /* 0x18 */ u32 mMaskPattern;
    /* 0x1C */ u32 field_0x1c;
    /* 0x20 */ bool field_0x20[4];
    /* 0x28 */ OSTime mTimer[4];
    /* 0x48 */ bool field_0x48[4];
    /* 0x4C */ void (*mCallback)(s32, JUTGamePadLongPress*, s32);
    /* 0x50 */ s32 field_0x50;
};

#endif /* JUTGAMEPAD_H */
