#ifndef C_BG_S_GND_CHK_H
#define C_BG_S_GND_CHK_H

#include "SSystem/SComponent/c_bg_s_chk.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_xyz.h"

class cBgS_GndChk : public cBgS_Chk, public cBgS_PolyInfo {
public:
    cBgS_GndChk();
    void SetPos(cXyz* pos) {
        m_pos = *pos;
    }
    void SetPos(Vec*);
    void PreCheck();

    virtual ~cBgS_GndChk() {}

    f32 GetNowY() const { return mNowY; }
    void SetNowY(f32 y) { mNowY = y; }
    cXyz* GetPointP() { return &m_pos; }
    u32 GetWallPrecheck() const { return mWallPrecheck; }
    void OffWall() { mFlag &= ~2; }

public:
    /* 0x24 */ cXyz m_pos;
    /* 0x30 */ u32 mFlag;
    /* 0x34 */ f32 mNowY;
    /* 0x38 */ u32 mWallPrecheck;
    /* 0x3C */ u32 mGndPrecheck;
};

STATIC_ASSERT(sizeof(cBgS_GndChk) == 0x40);

#endif /* C_BG_S_GND_CHK_H */
