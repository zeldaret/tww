#ifndef D_BG_D_BG_S_POLY_PASS_CHK_H
#define D_BG_D_BG_S_POLY_PASS_CHK_H

#include "dolphin/types.h"

class cBgS_PolyPassChk {
public:
    virtual ~cBgS_PolyPassChk();

    /* 0x4 */ u8 mbObjThrough;
    /* 0x5 */ u8 mbCamThrough;
    /* 0x6 */ u8 mbLinkThrough;
    /* 0x7 */ u8 mbArrowsAndLightThrough;
    /* 0x8 */ u8 mbBombThrough;
    /* 0x9 */ u8 mbBoomerangThrough;
    /* 0xA */ u8 mbHookshotThrough;
};

class dBgS_PolyPassChk : public cBgS_PolyPassChk {
public:
    dBgS_PolyPassChk();
    virtual ~dBgS_PolyPassChk();

    void SetObj() { mbObjThrough = 1; }
};

STATIC_ASSERT(sizeof(dBgS_PolyPassChk) == 0xC);

#endif /* D_BG_D_BG_S_POLY_PASS_CHK_H */