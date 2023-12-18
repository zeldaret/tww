#ifndef D_BG_D_BG_S_LIN_CHK_H
#define D_BG_D_BG_S_LIN_CHK_H

#include "SSystem/SComponent/c_bg_s_lin_chk.h"
#include "d/d_bg_s_chk.h"

class fopAc_ac_c;

class dBgS_LinChk : public cBgS_LinChk, public dBgS_Chk {
public:
    dBgS_LinChk() {
        SetPolyPassChk(GetPolyPassChkInfo());
        SetGrpPassChk(GetGrpPassChkInfo());
    }
    void Set(cXyz* pi_start, cXyz* pi_end, fopAc_ac_c* pi_actor);

    virtual ~dBgS_LinChk() {}

    /* 0x00 cBgS_LinChk */
    /* 0x58 dBgS_Chk */
};  // Size: 0x6C

class dBgS_LinkLinChk : public dBgS_LinChk {
public:
    dBgS_LinkLinChk() { SetLink(); }

    virtual ~dBgS_LinkLinChk() {}
};  // Size: 0x6C

class dBgS_RopeLinChk : public dBgS_LinChk {
public:
    dBgS_RopeLinChk() { SetRope(); }

    virtual ~dBgS_RopeLinChk() {}
};

class dBgS_BoomerangLinChk : public dBgS_LinChk {
public:
    dBgS_BoomerangLinChk() { SetBoomerang(); }

    virtual ~dBgS_BoomerangLinChk() {}
};

class dBgS_ArrowLinChk : public dBgS_LinChk {
public:
    dBgS_ArrowLinChk() {
        SetArrow(); // Don't check arrows
        OnYoganGrp(); // Check lava
        OnNormalGrp();
    }

    virtual ~dBgS_ArrowLinChk() {}
};

class dBgS_ObjLinChk : public dBgS_LinChk {
public:
    dBgS_ObjLinChk() { SetObj(); }

    virtual ~dBgS_ObjLinChk() {}
};

class dBgS_BombLinChk : public dBgS_LinChk {
public:
    dBgS_BombLinChk();

    virtual ~dBgS_BombLinChk();
};

class dBgS_CamLinChk : public dBgS_LinChk {
public:
    dBgS_CamLinChk() {
        mbCamThrough = true;
    }

    virtual ~dBgS_CamLinChk() {}
};

class dBgS_CamLinChk_NorWtr : public dBgS_CamLinChk {
public:
    dBgS_CamLinChk_NorWtr();

    virtual ~dBgS_CamLinChk_NorWtr();
};

class dBgS_MirLightLinChk : public dBgS_LinChk {
public:
    dBgS_MirLightLinChk() {
        SetArrow(); // "Arrow" also covers light
        OnAll();
        OnLightGrp();
    }

    virtual ~dBgS_MirLightLinChk() {}
};

#endif /* D_BG_D_BG_S_LIN_CHK_H */
