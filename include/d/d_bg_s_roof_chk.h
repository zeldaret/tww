#ifndef D_BG_D_BG_S_ROOF_CHK_H
#define D_BG_D_BG_S_ROOF_CHK_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_s_chk.h"

class dBgS_RoofChk : public cBgS_PolyInfo, public cBgS_Chk, public dBgS_Chk {
public:
    /* 80078FF4 */ dBgS_RoofChk();
    /* 80079124 */ void Init();
    /* 800B146C */ void SetPos(cXyz const&);

    /* 80079090 */ virtual ~dBgS_RoofChk();

    void i_SetPos(cXyz const& pos) { m_pos = pos; }
    cXyz* GetPosP() { return &m_pos; }

private:
    /* 0x38 */ cXyz m_pos;
};  // Size: 0x44

STATIC_ASSERT(sizeof(dBgS_RoofChk) == 0x44);

class dBgS_LinkRoofChk : public dBgS_RoofChk {
public:
    dBgS_LinkRoofChk() { /* SetLink(); */ }
    /* 80140E40 */ virtual ~dBgS_LinkRoofChk();
};

#endif /* D_BG_D_BG_S_ROOF_CHK_H */