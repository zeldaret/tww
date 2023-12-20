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

        /* 0x00 */ int field_0x0;
        /* 0x04 */ int field_0x4;
        /* 0x08 */ int field_0x8;
        /* 0x0C */ int field_0xc;
        /* 0x10 */ int field_0x10;
        /* 0x14 */ int field_0x14;
        /* 0x18 */ int field_0x18;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ int field_0x20;
        /* 0x24 */ int field_0x24;
        /* 0x28 */ int field_0x28;
        /* 0x2C */ JASystem::Kernel::TPortCmd field_0x2c;
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
        /* 0x0C */ f32 field_0xc;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1c;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32* trackVolume;
        /* 0x28 */ f32* trackPitch;
        /* 0x2C */ f32* trackFxmix;
        /* 0x30 */ f32* trackPan;
        /* 0x34 */ f32* trackDolby;
        /* 0x38 */ int field_0x38;
        /* 0x3C */ int field_0x3c;
        /* 0x40 */ int field_0x40;
        /* 0x44 */ int* trackupdate;
        /* 0x48 */ int field_0x48;
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
        int init();

        /* 0x0000 */ MoveParaSet field_0x0;
        /* 0x0010 */ MoveParaSet field_0x10[16];
        /* 0x0110 */ MoveParaSet field_0x110[20];
        /* 0x0250 */ MoveParaSet* seqPan;
        /* 0x0254 */ MoveParaSet* seqPitch;
        /* 0x0258 */ MoveParaSet* seqFxmix;
        /* 0x025C */ MoveParaSet* seqDolby;
        /* 0x0260 */ MoveParaSet field_0x260[32];
        /* 0x0460 */ MoveParaSet field_0x460[32];
        /* 0x0660 */ MoveParaSet field_0x660[32];
        /* 0x0860 */ MoveParaSet field_0x860[32];
        /* 0x0A60 */ MoveParaSet field_0xa60[32];
        /* 0x0C60 */ MoveParaSet field_0xc60[32];
        /* 0x0E60 */ u8 field_0xe60[0x1261 - 0xe60];
        /* 0x1261 */ u8 field_0x1261;
        /* 0x1262 */ u8 field_0x1262[0x133c - 0x1262];
        /* 0x133C */ MuteBit field_0x133c[32];
        /* 0x135C */ SeqUpdateData* field_0x135c;
        /* 0x1360 */ JASystem::TTrack field_0x1360;
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
        int getPlayTrackInfo(u32);

        extern LinkSound seqControl;
        extern SeqUpdateData* seqTrackInfo;
        extern int* FixSeqBufPointer;
        extern JKRArchive* arcPointer;
    }
}

#endif /* JAISEQUENCEMGR_H */
