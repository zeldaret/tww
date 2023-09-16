#ifndef D_BG_D_BG_S_GRP_PASS_CHK_H
#define D_BG_D_BG_S_GRP_PASS_CHK_H

#include "SSystem/SComponent/c_bg_s_chk.h"

class dBgS_GrpPassChk : public cBgS_GrpPassChk {
public:
    enum {
        /* 0x1 */ NORMAL_GRP = 1,
        /* 0x2 */ WATER_GRP = 2,
        /* 0x3 */ FULL_GRP = NORMAL_GRP | WATER_GRP | 4 | 8,
    };

    /* 80077BA0 */ dBgS_GrpPassChk() { mGrp = NORMAL_GRP; }

    /* 80077BC4 */ virtual ~dBgS_GrpPassChk() {}

    void OnWaterGrp() { mGrp |= WATER_GRP; }
    void OnSpl() { mGrp |= WATER_GRP; }
    void OnNormalGrp() { mGrp |= NORMAL_GRP; }
    void OffNormalGrp() { mGrp &= ~NORMAL_GRP; }
    void OffFullGrp() { mGrp &= ~FULL_GRP; }
    void OnAll() { mGrp |= FULL_GRP; }
    u32 MaskNormalGrp() const {return mGrp & 1; }
    u32 MaskWaterGrp() const {return mGrp & 2; }
private:
    /* 0x4 */ u32 mGrp;
};

STATIC_ASSERT(sizeof(dBgS_GrpPassChk) == 0x8);

#endif /* D_BG_D_BG_S_GRP_PASS_CHK_H */