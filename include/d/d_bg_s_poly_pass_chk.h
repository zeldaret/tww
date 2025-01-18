#ifndef D_BG_D_BG_S_POLY_PASS_CHK_H
#define D_BG_D_BG_S_POLY_PASS_CHK_H

#include "global.h"

class cBgS_PolyPassChk {
public:
    virtual ~cBgS_PolyPassChk() {}

    /* 0x4 */ u8 mbObjThrough;
    /* 0x5 */ u8 mbCamThrough;
    /* 0x6 */ u8 mbLinkThrough;
    /* 0x7 */ u8 mbArrowThrough; // Also light
    /* 0x8 */ u8 mbBombThrough;
    /* 0x9 */ u8 mbBoomerangThrough;
    /* 0xA */ u8 mbRopeThrough; // Actually Hookshot?
};

class dBgS_PolyPassChk : public cBgS_PolyPassChk {
public:
    dBgS_PolyPassChk() {
        mbObjThrough = 0;
        mbCamThrough = 0;
        mbLinkThrough = 0;
        mbArrowThrough = 0;
        mbBombThrough = 0;
        mbBoomerangThrough = 0;
        mbRopeThrough = 0;
    }
    virtual ~dBgS_PolyPassChk() {}

    void SetObj() { mbObjThrough = true; }
    void SetCam() { mbCamThrough = true; }
    void SetLink() { mbLinkThrough = true; }
    void SetArrow() { mbArrowThrough = true; }
    void SetBomb() { mbBombThrough = true; }
    void SetBoomerang() { mbBoomerangThrough = true; }
    void SetRope() { mbRopeThrough = true; }
    
    void SetPassChkInfo(dBgS_PolyPassChk& other) {
        *this = other;
    }
};

STATIC_ASSERT(sizeof(dBgS_PolyPassChk) == 0xC);

#endif /* D_BG_D_BG_S_POLY_PASS_CHK_H */
