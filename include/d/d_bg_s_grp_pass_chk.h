#ifndef D_BG_D_BG_S_GRP_PASS_CHK_H
#define D_BG_D_BG_S_GRP_PASS_CHK_H

#include "SSystem/SComponent/c_bg_s_chk.h"

class dBgS_GrpPassChk : public cBgS_GrpPassChk {
public:
    enum {
        NORMAL_GRP = 0x01,
        WATER_GRP  = 0x02,
        YOGAN_GRP  = 0x04, // Lava
        DOKU_GRP   = 0x08, // Unused, for poison?
        SPL_GRP    = WATER_GRP | YOGAN_GRP | DOKU_GRP,
        FULL_GRP   = NORMAL_GRP | SPL_GRP,
        LIGHT_GRP  = 0x10,
    };

    dBgS_GrpPassChk() { mGrp = NORMAL_GRP; }

    virtual ~dBgS_GrpPassChk() {}

    void OnNormalGrp() { mGrp |= NORMAL_GRP; }
    void OnWaterGrp() { mGrp |= WATER_GRP; }
    void OnYoganGrp() { mGrp |= YOGAN_GRP; }
    void OnSpl() { mGrp |= SPL_GRP; }
    void OnAll() { mGrp |= FULL_GRP; }
    void OnLightGrp() { mGrp |= LIGHT_GRP; }
    void OffNormalGrp() { mGrp &= ~NORMAL_GRP; }
    void OffWaterGrp() { mGrp &= ~WATER_GRP; }
    void OffFullGrp() { mGrp &= ~FULL_GRP; }
    u32 MaskNormalGrp() const { return mGrp & NORMAL_GRP; }
    u32 MaskWaterGrp() const { return mGrp & WATER_GRP; }
    u32 MaskYoganGrp() const { return mGrp & YOGAN_GRP; }
    u32 MaskDokuGrp() const { return mGrp & DOKU_GRP; }
    u32 MaskLightGrp() const { return mGrp & LIGHT_GRP; }
private:
    /* 0x4 */ u32 mGrp;
};

STATIC_ASSERT(sizeof(dBgS_GrpPassChk) == 0x8);

#endif /* D_BG_D_BG_S_GRP_PASS_CHK_H */