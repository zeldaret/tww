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
        void getWaveLoadStatus(s32);
        bool checkAllWaveLoadStatus();

        extern s32* wsGroupNumber;
        extern s32* wsLoadStatus;
        extern s32 wsMax;
    };
}

#endif /* JAIBANKWAVE_H */
