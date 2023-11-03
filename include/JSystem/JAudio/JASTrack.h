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

namespace JASystem {
    class TChannel;

    class TVibrate {
    public:
        TVibrate();
        void init();
        void incCounter();
        f32 getValue() const;

        /* 0x00 */ f32 field_0x0;
        /* 0x04 */ f32 field_0x4;
        /* 0x08 */ f32 field_0x8;
    };

    class TTrack {
    public:
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

            /* 0x00 */ u16 field_0x0;
            /* 0x02 */ u16 field_0x2;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ f32 field_0xc;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
            /* 0x18 */ f32 field_0x18;
            /* 0x1C */ s16 field_0x1c[8];
        };

        class MoveParam_ {
        public:
            MoveParam_();

            /* 0x00 */ f32 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ f32 field_0xc;
        };

        class AInnerParam_ {
        public:
            AInnerParam_();

            /* 0x000 */ f32 field_0x0[48];
            /* 0x0C0 */ MoveParam_ field_0xc0[4];
            /* 0x100 */ f32 field_0x100[8];
        };

        class TimedParam_ {
        public:
            TimedParam_();

            union {
                AInnerParam_ inner;
                MoveParam_ move[18];
            };
        };

        class TNoteMgr {
        public:
            void init();
            void endProcess();
            void setChannel(int, TChannel*);
            void releaseChannel(int);
            TChannel* getChannel(int);

            TChannel* field_0x0[8];
            u16 field_0x20[8];
            int field_0x30;
            u8 field_0x34;
            u8 field_0x35;
            u8 field_0x36;
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
        int checkNoteStop(s32);
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
        void readReg32(u8);
        void readReg16(u8);
        void writeRegDirect(u8, u16);
        void writeRegParam(u8);
        u16 readSelfPort(int);
        void writeSelfPort(int, u16);
        int writePortAppDirect(u32, u16);
        int readPortAppDirect(u32, u16*);
        void routeTrack(u32);
        int writePortApp(u32, u16);
        int readPortApp(u32, u16*);
        void pause(bool, bool);
        int getTranspose() const;
        void setTempo(u16);
        void setTimebase(u16);
        f32 panCalc(f32, f32, f32, u8);
        static int rootCallback(void*);
        static void registerSeqCallback(u16 (*)(TTrack*, u16));
        static void newMemPool(int);

        TTrack* getParent() { return mParent; }
        TTrack* getChild(int index) {
            JUT_ASSERT(242, index >= 0);
            JUT_ASSERT(243, index < MAX_CHILDREN);
            return mChildren[index];
        }

        /* 0x000 */ union {
            TSeqCtrl field_0x0;
            TTrack* next;
        };
        /* 0x048 */ TTrackPort field_0x48;
        /* 0x088 */ TIntrMgr field_0x88;
        /* 0x0B4 */ TNoteMgr field_0xb4;
        /* 0x0EC */ TVibrate field_0xec;
        /* 0x0F8 */ TChannelMgr field_0xf8;
        /* 0x16C */ TimedParam_ field_0x16c;
        /* 0x28C */ TRegisterParam field_0x28c;
        /* 0x2BC */ u8 field_0x2bc[0x2cc - 0x2bc];
        /* 0x2CC */ TOscillator::Osc_ field_0x2cc[2];
        /* 0x2FC */ u32 field_0x2fc[2];
        /* 0x304 */ short field_0x304[12];
        /* 0x31C */ TTrack* mParent;
        /* 0x320 */ TTrack* mChildren[MAX_CHILDREN];
        /* 0x360 */ TOuterParam* field_0x360;
        /* 0x364 */ f32 field_0x364;
        /* 0x368 */ f32 field_0x368;
        /* 0x36C */ int field_0x36c;
        /* 0x370 */ int field_0x370;
        /* 0x374 */ u16 field_0x374;
        /* 0x376 */ u16 field_0x376;
        /* 0x378 */ u16 field_0x378;
        /* 0x37a */ u8 field_0x37a;
        /* 0x37b */ u8 field_0x37b;
        /* 0x37c */ u8 field_0x37c;
        /* 0x37d */ u8 field_0x37d;
        /* 0x37e */ u8 field_0x37e;
        /* 0x37f */ u8 field_0x37f[3];
        /* 0x382 */ u8 field_0x382[3];
        /* 0x385 */ u8 field_0x385;
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
