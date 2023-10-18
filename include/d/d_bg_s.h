#ifndef D_BG_D_BG_S_H
#define D_BG_D_BG_S_H

#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_bg_s.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "SSystem/SComponent/c_bg_s_lin_chk.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "d/d_bg_s_chk.h"
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
    u32 GetMtrlSndId(cBgS_PolyInfo&);
    int GetExitId(cBgS_PolyInfo&);
    int GetPolyColor(cBgS_PolyInfo&);
    int GetGrpRoomInfId(cBgS_PolyInfo&);
    u8 GetGrpSoundId(cBgS_PolyInfo&);
    u32 ChkGrpInf(cBgS_PolyInfo&, u32);
    int GetPolyId1(int, int, int, u32, u32);
    void GetLinkNo(cBgS_PolyInfo&);
    int GetWallCode(cBgS_PolyInfo&);
    int GetSpecialCode(cBgS_PolyInfo&);
    s32 GetAttributeCodeDirect(cBgS_PolyInfo&);
    s32 GetAttributeCode(cBgS_PolyInfo&);
    int GetGroundCode(cBgS_PolyInfo&);
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

class dBgS_CrrPos : public cBgS_PolyInfo, public dBgS_Chk, public cBgS_Chk {
public:
    dBgS_CrrPos();
    void CrrPos(dBgS&);

    virtual ~dBgS_CrrPos() {}

    void Set(cXyz* i_pos, cXyz* i_line, void* param_2, cXyz* param_3) {
        mpLine0 = i_line;
        pm_pos = i_pos;
        field_0x058 = param_2;
        SetActorPid(-1);
        field_0x3c = param_3->y;
        field_0x40 = param_3->z;
    }

    void SetGndUpY(f32 param_0) { mOffsY2 = param_0; }

    void ClrNoRoof() {
        mGndChk.OffWall();
        field_0x38 &= ~8;
    }

    /* 0x038 */ u32 field_0x38;
    /* 0x03C */ f32 field_0x3c;
    /* 0x040 */ f32 field_0x40;
    /* 0x044 */ cXyz* pm_pos;
    /* 0x048 */ cXyz* mpLine0;
    /* 0x04C */ u8 field_0x04C[0x058 - 0x04C];
    /* 0x058 */ void* field_0x058;
    /* 0x05C */ f32 field_0x05c;
    /* 0x060 */ u8 field_0x060;
    /* 0x064 */ f32 mOffsY2;
    /* 0x068 */ f32 field_0x068;
    /* 0x06C */ cM3dGCyl mCyl0;
    /* 0x084 */ cM3dGCyl mCyl1;
    /* 0x09C */ cM3dGLin mLin;
    /* 0x0B8 */ cBgS_GndChk mGndChk;
    /* 0x0F8 */ cBgS_LinChk mLinChk;
};  // Size: 0x150

class dBgS_LinkCrrPos : public dBgS_CrrPos {
public:
    dBgS_LinkCrrPos();

    virtual ~dBgS_LinkCrrPos() {}
};

#endif /* D_BG_D_BG_S_H */