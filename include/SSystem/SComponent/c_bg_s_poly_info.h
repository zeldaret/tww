#ifndef C_BG_S_POLY_INFO_H
#define C_BG_S_POLY_INFO_H

#include "dolphin/types.h"
#include "global.h"

class cBgW;
class cBgS_PolyInfo {
private:
    /* 0x00 */ u16 mPolyIndex;
    /* 0x02 */ u16 mBgIndex;
    /* 0x04 */ cBgW* mpBgW;
    /* 0x08 */ unsigned int mActorId;

public:
    cBgS_PolyInfo() {
        ClearPi();
    }
    void ClearPi() {
        mPolyIndex = -1;
        mBgIndex = 0x100;
        mpBgW = NULL;
        mActorId = -1;
    }
    void SetPolyInfo(const cBgS_PolyInfo& other) {
        *this = other;
    }
    bool ChkSafe(const void* bgw, unsigned int pid) {
        if (mpBgW == bgw && mActorId == pid)
            return true;
        return false;
    }

    virtual ~cBgS_PolyInfo() {}

    s32 GetPolyIndex() const { return mPolyIndex; }
    s32 GetBgIndex() const { return mBgIndex; }
    bool ChkSetInfo() const {
        if (mPolyIndex == 0xFFFF || mBgIndex == 0x100) {
            return false;
        }

        return true;
    }
};  // Size: 0x10

STATIC_ASSERT(sizeof(cBgS_PolyInfo) == 0x10);

#endif /* C_BG_S_POLY_INFO_H */
