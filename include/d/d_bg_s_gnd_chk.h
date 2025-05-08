#ifndef D_BG_D_BG_S_GND_CHK_H
#define D_BG_D_BG_S_GND_CHK_H

#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "d/d_bg_s_chk.h"

class dBgS_GndChk : public cBgS_GndChk, public dBgS_Chk {
public:
    dBgS_GndChk() {
        SetPolyPassChk(GetPolyPassChkInfo());
        SetGrpPassChk(GetGrpPassChkInfo());
    }
    virtual ~dBgS_GndChk() {}
};  // Size: 0x54

STATIC_ASSERT(sizeof(dBgS_GndChk) == 0x54);

class dBgS_LinkGndChk : public dBgS_GndChk {
public:
    dBgS_LinkGndChk() { SetLink(); }
    virtual ~dBgS_LinkGndChk() {}
};  // Size: 0x54

class dBgS_ObjGndChk : public dBgS_GndChk {
public:
    dBgS_ObjGndChk() { SetObj(); }

    virtual ~dBgS_ObjGndChk() {}
}; // Size: 0x54

class dBgS_ObjGndChk_Yogan : public dBgS_ObjGndChk {
public:
    dBgS_ObjGndChk_Yogan() {
        OffNormalGrp();
        OnYoganGrp();
    }

    virtual ~dBgS_ObjGndChk_Yogan() {}
}; // Size: 0x54

class dBgS_ObjGndChk_Wtr : public dBgS_ObjGndChk {
public:
    dBgS_ObjGndChk_Wtr() {
        OffNormalGrp();
        OnWaterGrp();
    }

    virtual ~dBgS_ObjGndChk_Wtr() {}
};

class dBgS_ObjGndChk_Spl : public dBgS_ObjGndChk {
public:
    dBgS_ObjGndChk_Spl() {
        OffNormalGrp();
        OnSpl();
    }

    virtual ~dBgS_ObjGndChk_Spl() {}
};

class dBgS_ObjGndChk_All : public dBgS_ObjGndChk {
public:
    virtual ~dBgS_ObjGndChk_All() {}

    dBgS_ObjGndChk_All() { OnAll(); }
};

class dBgS_CamGndChk : public dBgS_GndChk {
public:
    dBgS_CamGndChk() { SetCam(); }

    virtual ~dBgS_CamGndChk() {}
};

class dBgS_CamGndChk_Wtr : public dBgS_CamGndChk {
public:
    dBgS_CamGndChk_Wtr() {
        OffNormalGrp();
        OnWaterGrp();
    };

    virtual ~dBgS_CamGndChk_Wtr() {}
};

#endif /* D_BG_D_BG_S_GND_CHK_H */
