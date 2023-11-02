#ifndef JASBANKMGR_H
#define JASBANKMGR_H

#include "JSystem/JAudio/JASOscillator.h"

namespace JASystem {
    class TBank;
    class TChannel;
    class TChannelMgr;

    namespace BankMgr {
        void init(int);
        bool registBank(int, TBank*);
        bool registBankBNK(int, void*);
        TBank* getBank(int);
        u16 getPhysicalNumber(u16);
        void setVir2PhyTable(u32, int);
        bool assignWaveBank(int, int);
        float clamp01(float);
        TChannel* noteOn(TChannelMgr*, int, int, u8, u8, u32);
        TChannel* noteOnOsc(TChannelMgr*, int, u8, u8, u32);
        void gateOn(TChannel*, u8, u8, u32);

        extern s32 sTableSize;
        extern TBank** sBankArray;
        extern u16* sVir2PhyTable;

        extern TOscillator::Osc_ OSC_ENV;
    }
}

#endif /* JASBANKMGR_H */
