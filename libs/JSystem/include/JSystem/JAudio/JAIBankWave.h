#ifndef JAIBANKWAVE_H
#define JAIBANKWAVE_H

#include "dolphin/types.h"

namespace JAInter {
    namespace BankWave {
        void setWsGroupNumber(s32, s32);
        void setWsLoadStatus(s32, s32);
        void init();
        void setWaveScene();
        void loadSecondStayWave();
        void setSceneSetFinishCallback(s32, s32);
        void finishSceneSet(u32);
        void loadSceneWave(s32, s32);
        void loadGroupWave(s32, s32);
        s32 getWaveLoadStatus(s32);
        bool checkAllWaveLoadStatus();

        struct initOnCode_s {
            u8* field_0x0;
            int field_0x4;
            u32 field_0x8;
        };
        struct flags_t {
            u16 flag1 : 1;
            u16 flag2 : 1;
            u16 flag3 : 1;
            u16 flag4 : 1;
            u16 flag5 : 1;
            u16 flag6 : 1;
            u16 flag7 : 1;
            u16 flag8 : 1;
            u16 flag9 : 1;
        };

        extern initOnCode_s* initOnCodeBnk;
        extern initOnCode_s* initOnCodeWs;
        extern s32* wsGroupNumber;
        extern s32* wsLoadStatus;
        extern s32 wsMax;
        extern flags_t flags;
        extern s32 SceneSetFlag;
    };
}

#endif /* JAIBANKWAVE_H */
