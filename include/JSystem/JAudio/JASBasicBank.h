#ifndef JASBASICBANK_H
#define JASBASICBANK_H

#include "JSystem/JAudio/JASBank.h"

namespace JASystem {
    class TBasicBank : public TBank {
    public:
        TBasicBank();
        ~TBasicBank();
        void setInstCount(u32);
        void setInst(int, JASystem::TInst*);
        TInst* getInst(int) const;
        u32 getType() const { return 'BSIC'; }

        /* 0x08 */ TInst** mInstTable;
        /* 0x0C */ u32 mInstCount;
    };
}

#endif /* JASBASICBANK_H */
