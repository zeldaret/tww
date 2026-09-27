#ifndef JAISEMGR_H
#define JAISEMGR_H

#include "JSystem/JAudio/JAISoundParams.h"

namespace JAInter {
    class Actor;
    class SeqUpdateData;

    class SeParameter {
    public:
        SeParameter();

        /* 0x000 */ u16 field_0x0[16];
        /* 0x020 */ u16 field_0x20;
        /* 0x024 */ MoveParaSet field_0x24[16];
        /* 0x124 */ MoveParaSet mVolumes[8];
        /* 0x1A4 */ MoveParaSetInitHalf mPans[8];
        /* 0x224 */ MoveParaSet mPitches[8];
        /* 0x2A4 */ MoveParaSetInitZero mFxmixes[8];
        /* 0x324 */ MoveParaSetInitZero field_0x324[8];
        /* 0x3A4 */ MoveParaSet mDolbys[8];
        /* 0x424 */ f32* field_0x424;
        /* 0x428 */ f32* field_0x428;
        /* 0x42C */ f32* field_0x42c;
        /* 0x430 */ f32* field_0x430;
        /* 0x434 */ u32 field_0x434;
        /* 0x438 */ f32* field_0x438;
        /* 0x43C */ SeParameter* field_0x43c;
        /* 0x440 */ SeParameter* field_0x440;
    };

    namespace SeMgr {
        void init();
        void startSeSequence();
        void processGFrameSe();
        void checkNextFrameSe();
        void checkPlayingSe();
        void setSeqMuteFromSeStart(JAISound* param_1);
        void clearSeqMuteFromSeStop(JAISound* param_1);
        void checkSeMovePara();
        void sendSeAllParameter(JAISound* param_1);
        void checkPlayingSeUpdateMultiplication(JAISound* param_1, SeqUpdateData* param_2, f32* param_3, MoveParaSet* param_4, f32 param_5, u8 param_6, f32* param_7);
        void checkPlayingSeUpdateAddition(JAISound* param_1, SeqUpdateData* param_2, f32* param_3, MoveParaSet* param_4, u8 param_5, f32* param_6, f32 param_7);
        u8 changeIDToCategory(u32 param_1);
        void releaseSeRegist(JAISound* param_1);
        SeParameter* getSeParametermeterPointer();
        void releaseSeParameterPointer(SeParameter* param_1);
        void storeSeBuffer(JAISound** param_1, Actor* param_2, u32 param_3, u32 param_4, u8 param_5, void* param_6);
        void releaseSeBuffer(JAISound* param_1, u32 param_2);

        struct seTrackUpdate_s {
            void init() {
                mPlayingVolume = 1.0f;
                mPlayingPitch = 1.0f;
                mPlayingFxmix = 0.0f;
                mPlayingPan = 0.5f;
                field_0x0 = 0xff;
                mPlayingDolby = 0.0f;
            }

            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 mPlayingVolume;
            /* 0x08 */ f32 mPlayingPitch;
            /* 0x0C */ f32 mPlayingFxmix;
            /* 0x10 */ f32 mPlayingPan;
            /* 0x14 */ f32 mPlayingDolby;
        };

        extern seTrackUpdate_s* seTrackUpdate;
        extern u8** categoryInfoTable;
        extern JAISound*** sePlaySound;
        extern SeParameter* seParameterFreeStartPointer;
        extern SeParameter* seParameterUsedEndPointer;
        extern LinkSound* seRegist;
        extern JAISound** seRegistBuffer;
        extern JAISound* seHandle;
        extern u8 seScene;
        extern u32 seqMuteFlagFromSe;
        extern f32* seCategoryVolume;
        extern u8* seEntryCancel;
    }
}


#endif /* JAISEMGR_H */
