#ifndef JAISOUND_H
#define JAISOUND_H

#include "dolphin/types.h"

enum JAISoundType {
    SOUNDPARAM_Unk0     = 0,
    SOUNDPARAM_Dopplar  = 1,
    SOUNDPARAM_Demo     = 2,
    SOUNDPARAM_Unk3     = 3,
    SOUNDPARAM_Distance = 4,
    SOUNDPARAM_Unk5     = 5,
    SOUNDPARAM_Direct   = 6,
    SOUNDPARAM_Fadeout  = 7,
    SOUNDPARAM_Unk8     = 8,
    SOUNDPARAM_Unk9     = 9,
    SOUNDPARAM_Unk10    = 10,
    SOUNDPARAM_Pause    = 11,
};

enum JAISoundState {
    SOUNDSTATE_Inactive = 0,
    SOUNDSTATE_Stored   = 1,
    SOUNDSTATE_Loaded   = 2,
    SOUNDSTATE_Ready    = 3,
    SOUNDSTATE_Playing  = 4,
    SOUNDSTATE_Fadeout  = 5,
};

enum JAISoundTrackActiveFlags {
    SOUNDACTIVE_Unk0                 = 0,
    SOUNDACTIVE_Unk1                 = 1 << 0,  // 0x1
    SOUNDACTIVE_DoFadeout            = 1 << 1,  // 0x2
    SOUNDACTIVE_TempoProportion      = 1 << 2,  // 0x4
    SOUNDACTIVE_Unk4                 = 1 << 3,  // 0x8
    SOUNDACTIVE_Unk5                 = 1 << 4,  // 0x10
    SOUNDACTIVE_Unk6                 = 1 << 5,  // 0x20
    SOUNDACTIVE_TrackVolume          = 1 << 6,  // 0x40
    SOUNDACTIVE_TrackPan             = 1 << 7,  // 0x80
    SOUNDACTIVE_TrackDolby           = 1 << 8,  // 0x100
    SOUNDACTIVE_TrackPitch           = 1 << 9,  // 0x200
    SOUNDACTIVE_Unk11                = 1 << 10, // 0x400
    SOUNDACTIVE_TrackFxmix           = 1 << 11, // 0x800
    SOUNDACTIVE_TrackPortData        = 1 << 12, // 0x1000
    SOUNDACTIVE_Unk14                = 1 << 13, // 0x2000
    SOUNDACTIVE_Unk15                = 1 << 14, // 0x4000
    SOUNDACTIVE_Unk16                = 1 << 15, // 0x8000
    SOUNDACTIVE_Unk17                = 1 << 16, // 0x10000
    SOUNDACTIVE_Unk18                = 1 << 17, // 0x20000
    SOUNDACTIVE_Volume               = 1 << 18, // 0x40000
    SOUNDACTIVE_Pan                  = 1 << 19, // 0x80000
    SOUNDACTIVE_Pitch                = 1 << 20, // 0x100000
    SOUNDACTIVE_Fxmix                = 1 << 21, // 0x200000
    SOUNDACTIVE_Dolby                = 1 << 22, // 0x400000
    SOUNDACTIVE_TrackInterruptSwitch = 1 << 23, // 0x800000
};

namespace JAInter {
    class Actor;
    class SeParameter;
    class SeqParameter;
    class StreamParameter;
}

class JAISound {
public:
    struct PositionInfo_t {
        /* 0x00 */ f32 field_0x0;
        /* 0x04 */ u8 field_0x4[0x8 - 0x4];
        /* 0x08 */ f32 field_0x8;
        /* 0x0C */ u8 field_0xc[0x18 - 0xc];
        /* 0x18 */ f32 field_0x18;
    };

    JAISound();
    virtual f32 setPositionDopplarCommon(u32);
    virtual f32 setDistanceVolumeCommon(f32, u8);
    virtual f32 setDistancePanCommon();
    virtual void setSeDistanceParameters();
    virtual void setSeDistanceVolume(u8);
    virtual void setSeDistancePan(u8);
    virtual void setSeDistancePitch(u8);
    virtual void setSeDistanceFxmix(u8);
    virtual void setSeDistanceFir(u8);
    virtual void setSeDistanceDolby(u8);
    virtual void setSePositionDopplar();

    u8 getSeCategoryNumber();
    int getSwBit();
    int checkSwBit(u32);
    u8 getInfoPriority();
    void clearMainSoundPPointer();
    void start(u32);
    void stop(u32);
    void setVolume(f32, u32, u8);
    void setPan(f32, u32, u8);
    void setPitch(f32, u32, u8);
    void setFxmix(f32, u32, u8);
    void setDolby(f32, u32, u8);
    void setTempoProportion(f32, u32);
    void setPortData(u8, u16);
    void setPrepareFlag(u8);
    void setSeqInterVolume(u8, f32, u32);
    void setSeqInterPan(u8, f32, u32);
    void setSeqInterPitch(u8, f32, u32);
    void setSeqInterFxmix(u8, f32, u32);
    void setSeqInterDolby(u8, f32, u32);
    void setSeqTempoProportion(f32, u32);
    void setSeqPortData(u8, u16, u32);
    void setTrackVolume(u8, f32, u32);
    void setTrackInterruptSwitch(u8, u8);
    void setTrackPortData(u8, u8, u16);
    void setSeInterRandomPara(f32*, u32, f32, f32);
    void setSeInterVolume(u8, f32, u32, u8);
    void setSeInterPan(u8, f32, u32, u8);
    void setSeInterPitch(u8, f32, u32, f32);
    void setSeInterFxmix(u8, f32, u32, u8);
    void setSeInterDolby(u8, f32, u32, u8);
    void setSePortData(u8, u16);
    void setStreamInterVolume(u8, f32, u32);
    void setStreamInterPitch(u8, f32, u32);
    void setStreamInterPan(u8, f32, u32);
    void setStreamPrepareFlag(u8);
    void setPauseMode(u8, u8);
    void setSeqPrepareFlag(u8);
    f32 getSeqInterVolume(u8);
    f32 getStreamInterVolume(u8);
    JAInter::SeqParameter* getSeqParameter();
    JAInter::SeParameter* getSeParameter();
    JAInter::StreamParameter* getStreamParameter();
    int getTrackPortRoute(u8, u8);
    u32 checkSoundHandle(u32, void*);
    void initParameter(JAISound**, JAInter::Actor*, u32, u32, u8, void*);

    // TODO
    void decWait() {}
    void getAct() {}
    void getAdjustPriority() {}
    void getFadetime() {}
    u32 getID() { return mSoundID; }
    void getInfoPointer() {}
    void getMapInfo() {}
    void getNextSound() {}
    void getPlayGameFrameCounter() {}
    void getPlayer() {}
    PositionInfo_t* getPositionInfo() { return mPositionInfo; }
    void getPrevSound() {}
    void getPriority() {}
    void getStatus() {}
    void getTrack() {}
    void getTrans() {}
    void getWait() {}
    void incPlayGameFrameCounter() {}
    void setCustomParameterPointer(void*) {}
    void setDemoFxmix(f32 f1, u32 r4) { setFxmix(f1, r4, 3); }
    void setDemoPan(f32 f1, u32 r4) { setPan(f1, r4, 3); }
    void setDemoPitch(f32 f1, u32 r4) { setPitch(f1, r4, 3); }
    void setDemoVolume(f32 f1, u32 r4) { setVolume(f1, r4, SOUNDPARAM_Unk3); }
    void setFadetime(u32) {}
    void setID(u32) {}
    void setMainSoundPPointer(JAISound**) {}
    void setNextSound(JAISound*) {}
    void setPrevSound(JAISound*) {}
    void setPriority(u32) {}
    void setRandom(u8) {}
    void setSeInterDolbyU7(u8, u8, u32, u8) {}
    void setSeInterFxmixU7(u8, u8, u32, u8) {}
    void setSeqInterVolumeU7(u8, u8, u32) {}
    void setStatus(u8) {}
    void setTrack(u8) {}
    void setTrackVolumeU7(u8, u8, u32) {}
    void setVolumeU7(u8, u32, u8) {}
    void setWait(u8) {}

    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 mState;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0a */ s16 field_0xa;
    /* 0x0c */ u32 mSoundID;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ u32 mFadeCounter;
    /* 0x18 */ u32 field_0x18;
    /* 0x1c */ int field_0x1c;
    /* 0x20 */ PositionInfo_t* mPositionInfo;
    /* 0x24 */ void* field_0x24;
    /* 0x28 */ u32 field_0x28;
    /* 0x2C */ int field_0x2c;
    /* 0x30 */ JAISound* field_0x30;
    /* 0x34 */ JAISound* field_0x34;
    /* 0x38 */ JAISound** field_0x38;
    /* 0x3C */ void* field_0x3c;
    /* 0x40 */ void* field_0x40;
};

namespace JAInter {
    class MoveParaSet {
    public:
        MoveParaSet(f32 param_1=1.0f) { init(param_1); }
        int set(f32 param_1, u32 param_2);
        BOOL move();

        void init(f32 value) {
            mCurrentValue = value;
            mTargetValue = value;
            mMoveCounter = 0;
        }

        /* 0x00 */ f32 mTargetValue;
        /* 0x04 */ f32 mCurrentValue;
        /* 0x08 */ f32 mMoveAmount;
        /* 0x0C */ int mMoveCounter;
    };

    class MoveParaSetInitHalf : public MoveParaSet {
    public:
        MoveParaSetInitHalf() : MoveParaSet(0.5f) {}
    };

    class MoveParaSetInitZero : public MoveParaSet {
    public:
        MoveParaSetInitZero() : MoveParaSet(0.0f) {}
    };

    class LinkSound {
    public:
        void init(JAISound* param_1, u32 param_2);
        JAISound* getSound();
        void releaseSound(JAISound* param_1);

        /* 0x00 */ JAISound* field_0x0;
        /* 0x04 */ JAISound* field_0x4;
        /* 0x08 */ JAISound* Buffer;
    };
}

#define IsJAISoundIDInUse(id)    (((id)&0x800) == 0)
#define IsJAISoundIDFree(id)     (((id)&0x800) == 1)
#define JAISoundID_TypeMask      0xC0000000
#define JAISoundID_Type_Se       0x00000000
#define JAISoundID_Type_Sequence 0x80000000
#define JAISoundID_Type_Stream   0xC0000000

#endif /* JAISOUND_H */
