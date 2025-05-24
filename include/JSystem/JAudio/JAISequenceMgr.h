#ifndef JAISEQUENCEMGR_H
#define JAISEQUENCEMGR_H

#include "JSystem/JAudio/JAISound.h"
#include "JSystem/JAudio/JASCmdStack.h"
#include "JSystem/JAudio/JASTrack.h"

class JAISound;
class JKRArchive;

namespace JAInter {
    class Actor;
    class MoveParaSet;

    class PlayerParameter {
    public:
        PlayerParameter();
        ~PlayerParameter();

        // fake struct to match JAInter::SystemInterface::setSeqPortargsF32 and JAInter::SystemInterface::setSeqPortargsU32
        union PortArg {
            f32 f32;
            u32 u32;
            s16* ps16;
        };

        /* 0x00 */ JASystem::TTrack* mTrack;
        // /* 0x04 */ JASystem::Kernel::TPortArgs mPortArgs;
        /* 0x04 */ union {
            PortArg asArray[10];
            JASystem::Kernel::TPortArgs asStruct;
        } mPortArgs;
        /* 0x2C */ JASystem::Kernel::TPortCmd mCommand;
    };

    class SeqUpdateData {
    public:
        SeqUpdateData();

        /* 0x00 */ u8 field_0x0;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 field_0x2;
        /* 0x03 */ u8 field_0x3;
        /* 0x04 */ int field_0x4;
        /* 0x08 */ int field_0x8;
        /* 0x0C */ f32 mSeqVolume;
        /* 0x10 */ f32 mSeqPitch;
        /* 0x14 */ f32 mSeqFxmix;
        /* 0x18 */ f32 mSeqPan;
        /* 0x1C */ f32 mSeqDolby;
        /* 0x20 */ f32 mSeqTempo;
        /* 0x24 */ f32* trackVolume;
        /* 0x28 */ f32* trackPitch;
        /* 0x2C */ f32* trackFxmix;
        /* 0x30 */ f32* trackPan;
        /* 0x34 */ f32* trackDolby;
        /* 0x38 */ int field_0x38;
        /* 0x3C */ int field_0x3c;
        /* 0x40 */ int field_0x40;
        /* 0x44 */ int* trackupdate;
        /* 0x48 */ JAISound* field_0x48;
        /* 0x4C */ PlayerParameter* systemTrackParameter;
    };

    class MuteBit {
    public:
        MuteBit();

        u8 flag1 : 1;
        u8 flag2 : 1;
        u8 flag3 : 1;
        u8 flag4 : 1;
        u8 flag5 : 1;
        u8 flag6 : 1;
        u8 flag7 : 1;
        u8 flag8 : 1;
    };

    class SeqParameter {
    public:
        SeqParameter() {}
        void init() {}
        JASystem::TTrack* getRootTrackPointer() { return &mTrack; }

        /* 0x0000 */ MoveParaSet mTempo;
        /* 0x0010 */ MoveParaSet field_0x10[16];
        /* 0x0110 */ MoveParaSet mVolumes[20];
        /* 0x0250 */ MoveParaSet* seqPan;
        /* 0x0254 */ MoveParaSet* seqPitch;
        /* 0x0258 */ MoveParaSet* seqFxmix;
        /* 0x025C */ MoveParaSet* seqDolby;
        /* 0x0260 */ MoveParaSet mTrackVolumes[32];
        /* 0x0460 */ MoveParaSetInitHalf mTrackPans[32];
        /* 0x0660 */ MoveParaSet mTrackPitches[32];
        /* 0x0860 */ MoveParaSetInitZero mTrackFxmixes[32];
        /* 0x0A60 */ MoveParaSetInitZero mTrackDolbys[32];
        /* 0x0C60 */ MoveParaSetInitZero field_0xc60[32];
        /* 0x0E60 */ u8 field_0xe60[0x1261 - 0xe60];
        /* 0x1261 */ u8 field_0x1261;
        /* 0x1262 */ u8 field_0x1262[0x1268 - 0x1262];
        /* 0x1268 */ int field_0x1268;
        /* 0x126C */ int field_0x126c;
        /* 0x1270 */ int field_0x1270;
        /* 0x1274 */ int field_0x1274;
        /* 0x1278 */ int field_0x1278;
        /* 0x127C */ int field_0x127c;
        /* 0x1280 */ int field_0x1280;
        /* 0x1284 */ u8 field_0x1284[0x1298 - 0x1284];
        /* 0x1298 */ int field_0x1298;
        /* 0x129C */ int field_0x129c[32];
        /* 0x131C */ u8 field_0x131c[32];
        /* 0x133C */ MuteBit mMuteBits[32];
        /* 0x135C */ SeqUpdateData* field_0x135c;
        /* 0x1360 */ JASystem::TTrack mTrack;
        /* 0x16EC */ JASystem::TTrack::TOuterParam field_0x16ec;
    };

    namespace SequenceMgr {
        void init();
        void getArchiveName(char*);
        void setArchivePointer(JKRArchive*);
        void processGFrameSequence();
        void checkEntriedSeq();
        void checkFadeoutSeq();
        void checkStoppedSeq();
        void checkPlayingSeq();
        void checkStartedSeq();
        void checkReadSeq();
        void checkSeqWave();
        void checkPlayingSeqUpdateMultiplication(u32, u8, u32, MoveParaSet*, u32*, u8, f32*);
        void checkPlayingSeqUpdateAddition(u32, u8, u32, MoveParaSet*, u32*, u8, f32*, f32);
        void checkPlayingSeqUpdateTrack(u32, u32, MoveParaSet*, u32*, u8, f32*);
        void checkPlayingSeqTrack(u32);
        void stopSeq(JAISound*);
        void checkDvdLoadArc(u32, u32);
        void storeSeqBuffer(JAISound**, Actor*, u32, u32, u8, void*);
        void releaseSeqBuffer(JAISound*, u32);
        SeqUpdateData* getPlayTrackInfo(u32);

        extern LinkSound seqControl;
        extern SeqUpdateData* seqTrackInfo;
        extern int* FixSeqBufPointer;
        extern JKRArchive* arcPointer;
    }
}

#endif /* JAISEQUENCEMGR_H */
