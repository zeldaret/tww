#ifndef D_BG_D_BG_S_SPH_CHK_H
#define D_BG_D_BG_S_SPH_CHK_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "d/d_bg_s_chk.h"
#include "SSystem/SComponent/c_bg_w.h"

class dBgS_SphChk : public cM3dGSph, public cBgS_PolyInfo, public cBgS_Chk, public dBgS_Chk {
public:
    dBgS_SphChk();
    void Init() {
        ClearPi();
    }

    virtual ~dBgS_SphChk() {}

    typedef void(*SphChk_Callback)(dBgS_SphChk*, cBgD_Vtx_t*, int, int, int, cM3dGPla*, void*);
    void SetCallback(SphChk_Callback cb) { mpCallback = cb; }

public:
    /* 0x4c */ SphChk_Callback mpCallback;
};  // Size: 0x50

#endif /* D_BG_D_BG_S_SPH_CHK_H */
