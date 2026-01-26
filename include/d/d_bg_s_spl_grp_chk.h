#ifndef D_BG_D_BG_S_SPL_GRP_CHK_H
#define D_BG_D_BG_S_SPL_GRP_CHK_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_s_chk.h"

class dBgS_SplGrpChk : public cBgS_PolyInfo, public cBgS_Chk, public dBgS_Chk {
public:
    enum {
        /* 0x1 */ FIND = 1,
        /* 0x2 */ IN = 2,
    };

    dBgS_SplGrpChk();
    void Init();

    virtual ~dBgS_SplGrpChk() {}

    void OffFind() { m_flags &= ~FIND; }
    void OnFind() { m_flags |= FIND; }
    void OffIn() { m_flags &= ~IN; }
    void OnIn() { m_flags |= IN; }
    void SetHeight(f32 height) { m_height = height; }
    f32 GetHeight() { return m_height; }
    cXyz* GetPosP() { return &m_ground; }
    f32 GetRoof() { return m_roof; }
    void Set(cXyz& ground, f32 roof) {
        m_ground = ground;
        m_roof = roof;
    }

private:
    /* 0x38 */ cXyz m_ground;
    /* 0x44 */ f32 m_roof;
    /* 0x48 */ f32 m_height;
    /* 0x4C */ u32 m_flags;
};  // Size: 0x50

#endif /* D_BG_D_BG_S_SPL_GRP_CHK_H */
