#ifndef D_POINT_WIND_H
#define D_POINT_WIND_H

#include "SSystem/SComponent/c_m3d_g_cps.h"
#include "d/d_kankyo.h"

class dPointWind_c {
public:
    cM3dGCpsS * mpCps;
    WIND_INFLUENCE mWind;

    void set_pwind_init(cM3dGCpsS * pCps);
    void set_pwind_power(float windStrength){ mWind.mStrength = windStrength; }
    float get_pwind_power_p(){ return mWind.mStrength; }
    void set_pwind_move();
    void set_pwind_delete();
};

#endif /* D_POINT_WIND_H */
