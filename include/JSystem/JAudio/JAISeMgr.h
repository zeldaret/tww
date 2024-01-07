#ifndef JAISEMGR_H
#define JAISEMGR_H

#include "JSystem/JAudio/JAISound.h"

namespace JAInter {
    class SeqUpdateData;

    class SeParameter {
    public:
        SeParameter();

        u16 field_0x0[18];
        MoveParaSet field_0x24[16];
        MoveParaSet field_0x124[8];
        MoveParaSetInitHalf field_0x1a4[8];
        MoveParaSet field_0x224[8];
        MoveParaSetInitZero field_0x2a4[8];
        MoveParaSetInitZero field_0x324[8];
        MoveParaSet field_0x3a4[8];
        f32* field_0x424;
        f32 field_0x428;
        u8 field_0x42c[0x43c - 0x42c];
        SeParameter* field_0x43c;
        SeParameter* field_0x440;
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
            u8 field_0x0;
            f32 field_0x4;
            f32 field_0x8;
            f32 field_0xc;
            f32 field_0x10;
            f32 field_0x14;
        };

        extern seTrackUpdate_s* seTrackUpdate;
        extern u8** categoryInfoTable;
        extern u32** sePlaySound;
        extern SeParameter* seParameterFreeStartPointer;
        extern SeParameter* seParameterUsedEndPointer;
        extern LinkSound* seRegist;
        extern JAISound** seRegistBuffer;
        extern JAISound* seHandle;
        extern u8 seScene;
        extern int seqMuteFlagFromSe;
        extern f32* seCategoryVolume;
        extern u8* seEntryCancel;
    }
}


#endif /* JAISEMGR_H */
