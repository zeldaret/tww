#ifndef D_BG_D_BG_S_H
#define D_BG_D_BG_S_H

#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_w.h"
#include "global.h"

class cBgS_LinChk;
class cBgS_GndChk;
class cBgS_PolyInfo;
class cM3dGPla;
class cBgS_ShdwDraw;
class dBgW;
class fopAc_ac_c;
class dBgS_Acch;
class dBgS_RoofChk;
class dBgS_SplGrpChk;
class dBgS_SphChk;

class cBgS_ChkElm {
public:
    /* 0x00 */ cBgW* m_bgw_base_ptr;
    /* 0x04 */ bool m_used;
    /* 0x08 */ u32 m_actor_id;
    /* 0x0C */ fopAc_ac_c* m_actor_ptr;
    /* 0x10 vtable */

public:
    cBgS_ChkElm() { Init(); }
    void Init();
    void Release();

    virtual ~cBgS_ChkElm() {}
    virtual void Regist2(cBgW*, u32, void*);

    bool ChkUsed() const { return m_used; }
};  // Size: 0x14

STATIC_ASSERT(sizeof(cBgS_ChkElm) == 0x14);

class cBgW;
class cBgS {
public:
    /* 0x0000 */ cBgS_ChkElm m_chk_element[256];
    /* 0x1400 vtable */

public:
    cBgS() {}

    bool GetTriPla(cBgS_PolyInfo&) const;
    bool Regist(cBgW*, u32, void*);
    int Release(cBgW*);
    bool LineCross(cBgS_LinChk*);
    f32 GroundCross(cBgS_GndChk*);
    static void* ConvDzb(void*);
    fopAc_ac_c* GetActorPointer(int) const;
    cBgW* GetBgWPointer(cBgS_PolyInfo&) const;
    bool ChkPolySafe(cBgS_PolyInfo&);
    void GetTriGrp(int, int) const;
    void GetGrpToRoomId(int, int) const;
    cM3dGPla* GetTriPla(int, int) const;
    bool GetTriPnt(cBgS_PolyInfo&, cXyz*, cXyz*, cXyz*) const;
    void ShdwDraw(cBgS_ShdwDraw*);
    u32 GetGrpInf(cBgS_PolyInfo&, int) const;

    virtual ~cBgS() {}
    virtual void Ct();
    virtual void Dt();
    virtual void Move();
};  // Size: 0x1404

class dBgS_Acch;

class dBgS : public cBgS {
public:
    dBgS() {}
    virtual ~dBgS() {}

    virtual void Ct();
    virtual void Dt();
    virtual void Move();

    void ClrMoveFlag();
    bool Regist(cBgW*, fopAc_ac_c*);
    bool ChkMoveBG(cBgS_PolyInfo&);
    bool ChkMoveBG_NoDABg(cBgS_PolyInfo&);
    int GetPolyId0(int, int, int, u32, u32);
    int GetPolyCamId(int, int);
    int GetMtrlSndId(cBgS_PolyInfo&);
    int GetExitId(cBgS_PolyInfo&);
    int GetPolyColor(cBgS_PolyInfo&);
    int GetGrpRoomInfId(cBgS_PolyInfo&);
    u8 GetGrpSoundId(cBgS_PolyInfo&);
    u32 ChkGrpInf(cBgS_PolyInfo&, u32);
    int GetPolyId1(int, int, int, u32, u32);
    void GetLinkNo(cBgS_PolyInfo&);
    int GetWallCode(cBgS_PolyInfo&);
    int GetSpecialCode(cBgS_PolyInfo&);
    void GetAttributeCodeDirect(cBgS_PolyInfo&);
    void GetAttributeCode(cBgS_PolyInfo&);
    void GetGroundCode(cBgS_PolyInfo&);
    void GetPolyId2(int, int, int, u32, u32);
    int GetCamMoveBG(cBgS_PolyInfo&);
    int GetRoomCamId(cBgS_PolyInfo&);
    int GetRoomPathId(cBgS_PolyInfo&);
    int GetRoomPathPntNo(cBgS_PolyInfo&);
    int GetRoomId(cBgS_PolyInfo&);
    u32 ChkPolyHSStick(cBgS_PolyInfo&);
    void LineCrossNonMoveBG(cBgS_LinChk*);
    void WallCorrect(dBgS_Acch*);
    f32 RoofChk(dBgS_RoofChk*);
    bool SplGrpChk(dBgS_SplGrpChk*);
    bool SphChk(dBgS_SphChk*, void*);
    void WallCrrPos(dBgS_CrrPos*);
    void MoveBgCrrPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void MoveBgTransPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void MoveBgMatrixCrrPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void RideCallBack(cBgS_PolyInfo&, fopAc_ac_c*);
    void PushPullCallBack(cBgS_PolyInfo&, fopAc_ac_c*, short, dBgW::PushPullLabel);

    bool WaterChk(dBgS_SplGrpChk* chk) { return SplGrpChk(chk); }
};  // Size: 0x1404

#endif /* D_BG_D_BG_S_H */