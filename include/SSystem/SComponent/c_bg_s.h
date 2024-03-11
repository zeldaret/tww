#ifndef C_BG_S_H
#define C_BG_S_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "dolphin/types.h"

class fopAc_ac_c;
class cBgS_ShdwDraw;
class cBgS_LinChk;
class cBgS_GndChk;
class cM3dGPla;
class cXyz;

class cBgS_ChkElm {
public:
    /* 0x00 */ cBgW* m_bgw_base_ptr;
    /* 0x04 */ u32 m_flags;
    /* 0x08 */ u32 m_actor_id;
    /* 0x0C */ fopAc_ac_c* m_actor_ptr;
    /* 0x10 vtable */

public:
    cBgS_ChkElm() { Init(); }
    void Init();
    void Release();

    virtual ~cBgS_ChkElm() {}
    virtual void Regist2(cBgW*, uint, void*);

    bool ChkUsed() const { return (m_flags & 1); }
};  // Size: 0x14

STATIC_ASSERT(sizeof(cBgS_ChkElm) == 0x14);

class cBgW;
class cBgS {
public:
    /* 0x0000 */ cBgS_ChkElm m_chk_element[256];
    /* 0x1400 vtable */

public:
    cBgS() {}

    cM3dGPla* GetTriPla(cBgS_PolyInfo& polyInfo) const {
        return GetTriPla(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex());
    }
    bool Regist(cBgW*, uint, void*);
    bool Release(cBgW*);
    bool LineCross(cBgS_LinChk*);
    f32 GroundCross(cBgS_GndChk*);
    static void* ConvDzb(void*);
    fopAc_ac_c* GetActorPointer(int) const;
    cBgW* GetBgWPointer(cBgS_PolyInfo&) const;
    bool ChkPolySafe(cBgS_PolyInfo&);
    s32 GetTriGrp(int, int) const;
    s32 GetGrpToRoomId(int, int) const;
    cM3dGPla* GetTriPla(int, int) const;
    void GetTriPnt(cBgS_PolyInfo&, cXyz*, cXyz*, cXyz*) const;
    void ShdwDraw(cBgS_ShdwDraw*);
    s32 GetGrpInf(cBgS_PolyInfo&, int) const;

    virtual ~cBgS() {}
    virtual void Ct();
    virtual void Dt();
    virtual void Move();
};  // Size: 0x1404

#endif /* C_BG_S_H */
