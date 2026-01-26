#ifndef JASTRACK_H
#define JASTRACK_H

#include "JSystem/JAudio/JASChannelMgr.h"
#include "JSystem/JAudio/JASOscillator.h"
#include "JSystem/JAudio/JASRegisterParam.h"
#include "JSystem/JAudio/JASSeqCtrl.h"
#include "JSystem/JAudio/JASSeqParser.h"
#include "JSystem/JAudio/JASTrackInterrupt.h"
#include "JSystem/JAudio/JASTrackPort.h"
#include "JSystem/JUtility/JUTAssert.h"

enum JASOuterParamFlag {
    OUTERPARAM_Volume     = 0x01,
    OUTERPARAM_Pitch      = 0x02,
    OUTERPARAM_Fxmix      = 0x04,
    OUTERPARAM_Pan        = 0x08,
    OUTERPARAM_Dolby      = 0x10,
    OUTERPARAM_Unk6       = 0x20,
    OUTERPARAM_Tempo      = 0x40,
    OUTERPARAM_FIR8Filter = 0x80,
    OUTERPARAM_IIR0       = 0x1000,
    OUTERPARAM_IIR1       = 0x2000,
    OUTERPARAM_IIR2       = 0x4000,
    OUTERPARAM_IIR3       = 0x8000,
    OUTERPARAM_Unk18      = 0x20000,

    OUTERPARAM_IIRFilter = OUTERPARAM_IIR0 | OUTERPARAM_IIR1 | OUTERPARAM_IIR2 | OUTERPARAM_IIR3,
};

namespace JASystem {
    class TChannel;

    class TVibrate {
    public:
        TVibrate();
        void init();
        void incCounter();
        f32 getValue() const;

        void setDepth(f32 depth) { mDepth = depth; }
        void setPitch(f32 pitch) { mPitch = pitch; }

        /* 0x00 */ f32 field_0x0;
        /* 0x04 */ f32 mDepth;
        /* 0x08 */ f32 mPitch;
    };

    class TTrack {
    public:
        enum TimedParamType {
            TIMED_Volume      = 0,
            TIMED_Pitch       = 1,
            TIMED_Fxmix       = 2,
            TIMED_Pan         = 3,
            TIMED_Dolby       = 4,
            TIMED_Unk5        = 5,
            TIMED_Osc0_Width  = 6,
            TIMED_Osc0_Rate   = 7,
            TIMED_Osc0_Vertex = 8,
            TIMED_Osc1_Width  = 9,
            TIMED_Osc1_Rate   = 10,
            TIMED_Osc1_Vertex = 11,
            TIMED_IIR_Unk0    = 12,
            TIMED_IIR_Unk1    = 13,
            TIMED_IIR_Unk2    = 14,
            TIMED_IIR_Unk3    = 15,
            TIMED_Unk16       = 16,
            TIMED_Unk17       = 17,
            TIMED_PARAMS, // 18
        };

        class TOuterParam {
        public:
            TOuterParam();
            void initExtBuffer();
            void setOuterSwitch(u16);
            bool checkOuterSwitch(u16);
            void setOuterUpdate(u16);
            u16 getOuterUpdate();
            s16 getIntFirFilter(u8);
            void setParam(u8, f32);
            void onSwitch(u16);
            void setFirFilter(s16*);

            f32 getVolume() const { return mVolume; }
            f32 getPitch() const { return mPitch; }
            f32 getFxVol() const { return mFxmix; }
            f32 getDolby() const { return mDolby; }
            f32 getPan() const { return mPan; }
            f32 getTempo() const { return mTempo; }

            /* 0x00 */ u16 field_0x0;
            /* 0x02 */ u16 field_0x2;
            /* 0x04 */ f32 mVolume;
            /* 0x08 */ f32 mPitch;
            /* 0x0C */ f32 mFxmix;
            /* 0x10 */ f32 mDolby;
            /* 0x14 */ f32 mPan;
            /* 0x18 */ f32 mTempo;
            /* 0x1C */ s16 field_0x1c[8];
        };

        class MoveParam_ {
        public:
            MoveParam_()
                : mCurrentValue(0.0f)
                , mTargetValue(0.0f)
                , mMoveTime(0.0f)
                , mMoveAmount(0.0f)
            {
            }

            /* 0x00 */ f32 mCurrentValue;
            /* 0x04 */ f32 mTargetValue;
            /* 0x08 */ f32 mMoveTime;
            /* 0x0C */ f32 mMoveAmount;
        };

        class AInnerParam_ {
        public:
                AInnerParam_()
                : mVolume()
                , mPitch()
                , mFxmix()
                , mPan()
                , mDolby()
                , _50()
                , mOsc0Width()
                , mOsc0Rate()
                , mOsc0Vertex()
                , mOsc1Width()
                , mOsc1Rate()
                , mOsc1Vertex()
                , mIIRs()
                , _100()
                , _110()
            {
            }

            /* 0x000 */ MoveParam_ mVolume;
            /* 0x010 */ MoveParam_ mPitch;
            /* 0x020 */ MoveParam_ mFxmix;
            /* 0x030 */ MoveParam_ mPan;
            /* 0x040 */ MoveParam_ mDolby;
            /* 0x050 */ MoveParam_ _50;
            /* 0x060 */ MoveParam_ mOsc0Width;
            /* 0x070 */ MoveParam_ mOsc0Rate;
            /* 0x080 */ MoveParam_ mOsc0Vertex;
            /* 0x090 */ MoveParam_ mOsc1Width;
            /* 0x0A0 */ MoveParam_ mOsc1Rate;
            /* 0x0B0 */ MoveParam_ mOsc1Vertex;
            /* 0x0C0 */ MoveParam_ mIIRs[4];
            /* 0x100 */ MoveParam_ _100;
            /* 0x110 */ MoveParam_ _110;
        };  // Size: 0x120

        class TimedParam_ {
        public:
            TimedParam_();

#ifdef __MWERKS__
            union {
                AInnerParam_ mInnerParam;
                MoveParam_ mMoveParams[TIMED_PARAMS];
            };
#else
            MoveParam_ mMoveParams[TIMED_PARAMS];
#endif
        };

        class TNoteMgr {
        public:
            void setBaseTime(u32 time) { mBaseTime = time; }
            u8 getConnectCase() const { return mConnectCase; }
            void setConnectCase(u8 val) { mConnectCase = val; }
            u8 getLastNote() const { return mLastNote; }
            void setLastNote(u8 note) { mLastNote = note; }
            bool checkBeforeTieMode() const { return mBeforeTieMode; }
            void setBeforeTieMode(bool mode) { mBeforeTieMode = mode; }

            void init();
            void endProcess();
            void setChannel(int, TChannel*);
            void releaseChannel(int);
            TChannel* getChannel(int);

            /* 0x00 */ TChannel* field_0x0[8];
            /* 0x20 */ u16 field_0x20[8];
            /* 0x30 */ int mBaseTime;
            /* 0x34 */ u8 mConnectCase;
            /* 0x35 */ u8 mLastNote;
            /* 0x36 */ u8 mBeforeTieMode;
        };

        static const int MAX_CHILDREN = 16;

        TTrack();
        void init();
        void inherit();
        s8 mainProc();
        void setInterrupt(u16);
        bool tryInterrupt();
        void assignExtBuffer(TOuterParam*);
        void releaseChannelAll();
        void flushAll();
        static int moveFreeChannel(TChannelMgr*, TChannelMgr*, int);
        void initTimed();
        void connectBus(int, int);
        int noteOn(u8, s32, s32, s32, u32);
        void overwriteOsc(TChannel*);
        bool noteOff(u8, u16);
        int gateOn(u8, s32, s32, s32);
        bool checkNoteStop(s32);
        void oscSetupFull(u8, u32, u32);
        void oscSetupSimpleEnv(u8, u32);
        void updateOscParam(int, f32);
        void oscSetupSimple(u8);
        void updateTimedParam();
        void updateTrackAll();
        void updateTrack(u32);
        void updateTempo();
        void updateSeq(u32, bool);
        int seqTimeToDspTime(s32, u8);
        void setParam(int, f32, int);
        bool setSeqData(u8*, s32, int);
        bool startSeq();
        bool stopSeq();
        void stopSeqMain();
        void noteOffAll();
        int close();
        void muteTrack(bool);
        bool start(void*, u32);
        TTrack* openChild(u8, u8);
        int loadTbl(u32, u32, u32);
        int exchangeRegisterValue(u8);
        u32 readReg32(u8);
        u16 readReg16(u8);
        void writeRegDirect(u8, u16);
        void writeRegParam(u8);
        u16 readSelfPort(int);
        void writeSelfPort(int, u16);
        int writePortAppDirect(u32, u16);
        int readPortAppDirect(u32, u16*);
        JASystem::TTrack* routeTrack(u32);
        int writePortApp(u32, u16);
        int readPortApp(u32, u16*);
        void pause(bool, bool);
        int getTranspose() const;
        void setTempo(u16);
        void setTimebase(u16);
        f32 panCalc(f32, f32, f32, u8);
        static s32 rootCallback(void*);
        static void registerSeqCallback(u16 (*)(TTrack*, u16));
        static void newMemPool(int);

        void* operator new(size_t n) {
            TTrack* track;
            if (sFreeList == NULL) {
                track = NULL;
            } else {
                track = sFreeList;
                sFreeList = sFreeList->next;
            }
            return track;
        }
        void operator delete(void* ptr, size_t n) {
            TTrack* track = (TTrack*)ptr;
            track->next = sFreeList;
            sFreeList = track;
        }

        TTrack* getParent() { return mParent; }
        TTrack* getChild(int index) {
            JUT_ASSERT(242, index >= 0);
            JUT_ASSERT(243, index < MAX_CHILDREN);
            return mChildren[index];
        }

        TOuterParam* getOuterParam() { return mOuterParam; }

        u8 checkImport(int i) const { return mTrackPort.checkImport(i); }
        u8 checkExport(int i) const { return mTrackPort.checkExport(i); }
        void getActivity() const {}
        void getRoute() const {}
        TSeqCtrl* getSeq() { return &mSeqCtrl; }
        void pauseTrackAll() { pause(true, true); }
        void unPauseTrackAll() { pause(false, true); }
        void setPanPower(int i, u16 power) { mRegisterParam.setPanPower(i, power); }
        void setPauseStatus(u8 status) { mPauseStatus = status; }
        void setTranspose(s32 transpose) { mTranspose = transpose; }
        void setVolumeMode(u8 mode) { mVolumeMode = mode; }

        /* 0x000 */ union {
            TSeqCtrl mSeqCtrl;
            TTrack* next;
        };
        /* 0x048 */ TTrackPort mTrackPort;
        /* 0x088 */ TIntrMgr mIntrMgr;
        /* 0x0B4 */ TNoteMgr mNoteMgr;
        /* 0x0EC */ TVibrate mVibrate;
        /* 0x0F8 */ TChannelMgr mChannelUpdater;
        /* 0x16C */ TimedParam_ mTimedParam;
        /* 0x28C */ TRegisterParam mRegisterParam;
        /* 0x2BC */ u8 field_0x2bc[0x2cc - 0x2bc];
        /* 0x2CC */ TOscillator::Osc_ field_0x2cc[2];
        /* 0x2FC */ u32 mOscRoute[2];
        /* 0x304 */ s16 field_0x304[12];
        /* 0x31C */ TTrack* mParent;
        /* 0x320 */ TTrack* mChildren[MAX_CHILDREN];
        /* 0x360 */ TOuterParam* mOuterParam;
        /* 0x364 */ f32 field_0x364;
        /* 0x368 */ f32 field_0x368;
        /* 0x36C */ int field_0x36c;
        /* 0x370 */ u32 mUpdateFlags;
        /* 0x374 */ u16 field_0x374;
        /* 0x376 */ u16 field_0x376;
        /* 0x378 */ u16 field_0x378;
        /* 0x37A */ s8 mTranspose;
        /* 0x37B */ u8 field_0x37b;
        /* 0x37C */ u8 mPauseStatus;
        /* 0x37D */ u8 mVolumeMode;
        /* 0x37E */ u8 field_0x37e;
        /* 0x37F */ u8 mCalcTypes[3];
        /* 0x382 */ u8 mParentCalcTypes[3];
        /* 0x385 */ bool mIsPaused;
        /* 0x386 */ u8 field_0x386;
        /* 0x387 */ bool field_0x387;
        /* 0x388 */ u8 field_0x388;
        /* 0x389 */ u8 field_0x389;

        static u16 (*sCallBackFunc)(TTrack*, u16);
        static TSeqParser sParser;
        static TTrack* sFreeList;
    };
}

#endif /* JASTRACK_H */
