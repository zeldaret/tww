#ifndef C_BG_S_POLY_INFO_H
#define C_BG_S_POLY_INFO_H

#include "dolphin/types.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_pc/f_pc_manager.h"
#include "global.h"

class cBgW;
class cBgS_PolyInfo {
private:
    /* 0x00 */ u16 mPolyIndex;
    /* 0x02 */ u16 mBgIndex;
    /* 0x04 */ cBgW* mpBgW;
    /* 0x08 */ uint mActorId;

public:
    cBgS_PolyInfo() {
        ClearPi();
    }
    void ClearPi() {
        mPolyIndex = -1;
        mBgIndex = 0x100;
        mpBgW = NULL;
        mActorId = fpcM_ERROR_PROCESS_ID_e;
    }
    void SetPolyInfo(const cBgS_PolyInfo& other) {
        *this = other;
    }
    void SetActorInfo(int bg_index, void* bgw, uint actor_id) {
        JUT_ASSERT(0x59, 0 <= bg_index);
        mBgIndex = bg_index;
        mpBgW = (cBgW*)bgw;
        mActorId = actor_id;
    }
    bool ChkSafe(const void* bgw, uint pid) {
        if (mpBgW == bgw && mActorId == pid)
            return true;
        return false;
    }

    virtual ~cBgS_PolyInfo() {}

    int GetPolyIndex() const { return mPolyIndex; }
    int GetBgIndex() const { return mBgIndex; }
    bool ChkSetInfo() const {
        if (mPolyIndex == 0xFFFF || mBgIndex == 0x100) {
            return false;
        }

        return true;
    }
    bool ChkBgIndex() const {
        if (mBgIndex == 0x100) {
            return false;
        }
        return true;
    }

    // TODO
    void ChkSafe(const void*, uint) const {}
    void ChkSetInf() const {}
    void SetPolyIndex(int poly_index) {
        JUT_ASSERT(0x7b, 0 <= poly_index);
        mPolyIndex = poly_index;
    }
};  // Size: 0x10

STATIC_ASSERT(sizeof(cBgS_PolyInfo) == 0x10);

#endif /* C_BG_S_POLY_INFO_H */
