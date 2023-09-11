#ifndef D_BG_D_BG_S_POLY_PASS_CHK_H
#define D_BG_D_BG_S_POLY_PASS_CHK_H

#include "dolphin/types.h"

class cBgS_PolyPassChk {
public:
    virtual ~cBgS_PolyPassChk();
};

class dBgS_PolyPassChk : public cBgS_PolyPassChk {
public:
    dBgS_PolyPassChk();
    virtual ~dBgS_PolyPassChk();
};

#endif /* D_BG_D_BG_S_POLY_PASS_CHK_H */