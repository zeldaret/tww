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
#include "f_pc/f_pc_manager.h"

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

enum dBgS_AttributeCode {
    dBgS_Attr_NORMAL_e       = 0x00,
    dBgS_Attr_DIRT_e         = 0x01,
    dBgS_Attr_WOOD_e         = 0x02,
    dBgS_Attr_STONE_e        = 0x03,
    dBgS_Attr_GRASS_e        = 0x04,
    dBgS_Attr_GIANT_FLOWER_e = 0x05,
    dBgS_Attr_LAVA_e         = 0x06,
    // dBgS_Attr_UNK07_e     = 0x07,
    dBgS_Attr_VOID_e         = 0x08,
    dBgS_Attr_DAMAGE_e       = 0x09,
    dBgS_Attr_CARPET_e       = 0x0A,
    dBgS_Attr_SAND_e         = 0x0B,
    // dBgS_Attr_UNK0C_e     = 0x0C,
    // dBgS_Attr_UNK0D_e     = 0x0D,
    // dBgS_Attr_UNK0E_e     = 0x0E,
    dBgS_Attr_ICE_e          = 0x0F,
    // dBgS_Attr_UNK10_e     = 0x10,
    // dBgS_Attr_UNK11_e     = 0x11,
    // dBgS_Attr_UNK12_e     = 0x12,
    dBgS_Attr_WATER_e        = 0x13,
    dBgS_Attr_METAL_e        = 0x14,
    dBgS_Attr_FREEZE_e       = 0x15,
    dBgS_Attr_ELECTRICITY_e  = 0x16,
    dBgS_Attr_WATERFALL_e    = 0x17,
    // dBgS_Attr_UNK18_e     = 0x18,
    // dBgS_Attr_UNK19_e     = 0x19,
    // dBgS_Attr_UNK1A_e     = 0x1A,
    dBgS_Attr_UNK1B_e        = 0x1B,
    // dBgS_Attr_UNK1C_e     = 0x1C,
    // dBgS_Attr_UNK1D_e     = 0x1D,
    // dBgS_Attr_UNK1E_e     = 0x1E,
    // dBgS_Attr_UNK1F_e     = 0x1F,
};

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
    s32 GetGrpSoundId(cBgS_PolyInfo&);
    u32 ChkGrpInf(cBgS_PolyInfo&, u32);
    int GetPolyId1(int, int, int, u32, u32);
    int GetLinkNo(cBgS_PolyInfo&);
    int GetWallCode(cBgS_PolyInfo&);
    int GetSpecialCode(cBgS_PolyInfo&);
    s32 GetAttributeCodeDirect(cBgS_PolyInfo&);
    s32 GetAttributeCode(cBgS_PolyInfo&);
    int GetGroundCode(cBgS_PolyInfo&);
    int GetPolyId2(int, int, int, u32, u32);
    int GetCamMoveBG(cBgS_PolyInfo&);
    int GetRoomCamId(cBgS_PolyInfo&);
    int GetRoomPathId(cBgS_PolyInfo&);
    int GetRoomPathPntNo(cBgS_PolyInfo&);
    s32 GetRoomId(cBgS_PolyInfo&);
    u32 ChkPolyHSStick(cBgS_PolyInfo&);
    bool LineCrossNonMoveBG(cBgS_LinChk*);
    void WallCorrect(dBgS_Acch*);
    f32 RoofChk(dBgS_RoofChk*);
    bool SplGrpChk(dBgS_SplGrpChk*);
    bool SphChk(dBgS_SphChk*, void*);
    bool WallCrrPos(dBgS_CrrPos*);
    void MoveBgCrrPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void MoveBgTransPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void MoveBgMatrixCrrPos(cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    void RideCallBack(cBgS_PolyInfo&, fopAc_ac_c*);
    fopAc_ac_c* PushPullCallBack(cBgS_PolyInfo&, fopAc_ac_c*, short, dBgW::PushPullLabel);

    bool WaterChk(dBgS_SplGrpChk* chk) { return SplGrpChk(chk); }
};  // Size: 0x1404

class dBgS_CrrPos : public cBgS_PolyInfo, public dBgS_Chk, public cBgS_Chk {
public:
    dBgS_CrrPos() {
        SetPolyPassChk(GetPolyPassChkInfo());
        SetGrpPassChk(GetGrpPassChkInfo());
        SetActorPid(fpcM_ERROR_PROCESS_ID_e);
        mFlag = 0;
        mWallHeight = 0.0f;
        mWallRadius = 0.0f;
        pm_pos = NULL;
        pm_old_pos = NULL;
        mGroundH = -1e+9f;
        field_0x60 = 0;
        field_0x68 = 20.0f;
        field_0x58 = NULL;
        mGndUpY = 400.0f;
    }
    virtual ~dBgS_CrrPos() {}

    void CrrPos(dBgS&);

    void Set(cXyz* i_pos, cXyz* i_line, void* actor, cXyz* param_3) {
        // not 100% sure if this is right
        Set(i_pos, i_line, fpcM_GetID(actor), param_3);
    }
    void Set(cXyz* i_pos, cXyz* i_line, uint actorPid, cXyz* param_3) {
        // not 100% sure if this is right
        pm_pos = i_pos;
        pm_old_pos = i_line;
        field_0x58 = param_3;
        SetActorPid(actorPid);
    }

    void SetWallHit() { mFlag |= 0x10; }
    void ClrWallHit() { mFlag &= ~0x10; }
    void SetXCrr() { mFlag |= 0x20; }
    void ClrXCrr() { mFlag &= ~0x20; }
    bool ChkXCrr() { return mFlag & 0x20; }
    void SetZCrr() { mFlag |= 0x40; }
    void ClrZCrr() { mFlag &= ~0x40; }
    bool ChkZCrr() { return mFlag & 0x40; }

    void SetGndUpY(f32 y) { mGndUpY = y; }
    void ClrNoRoof() {
        mGndChk.OffWall();
        mFlag &= ~8;
    }
    void ClrPosVec() { field_0x4c.x = field_0x4c.y = field_0x4c.z = 0.0f; }

    f32 GetWallH() const { return mWallHeight; }
    f32 GetWallR() const { return mWallRadius; }
    void SetWall(f32 height, f32 radius) {
        mWallHeight = height;
        mWallRadius = radius;
    }
    f32 GetGroundH() const { return mGroundH; }

    cXyz* GetOldPos() const { return pm_old_pos; }
    cXyz* GetPos() const { return pm_pos; }
    cXyz& GetPosVec() { return field_0x4c; }

    const cM3dGCyl* GetCylP() const { return &mCyl; }
    void SetOldCyl() { mOldCyl.Set(*pm_old_pos, mWallRadius, mWallHeight * 2.0f); }
    void SetCyl() { mCyl.Set(*pm_pos, mWallRadius, mWallHeight * 2.0f); }
    void SetLin() { mLin.SetStartEnd(*pm_old_pos, *pm_pos); }

    void SetWallActorInfo(int bg_index, void* bgw, uint actor_id) {
        SetActorInfo(bg_index, bgw, actor_id);
    }
    void SetWallPolyIndex(int) {} // TODO

    /* 0x038 */ u32 mFlag;
    /* 0x03C */ f32 mWallHeight;
    /* 0x040 */ f32 mWallRadius;
    /* 0x044 */ cXyz* pm_pos;
    /* 0x048 */ cXyz* pm_old_pos;
    /* 0x04C */ cXyz field_0x4c;
    /* 0x058 */ cXyz* field_0x58;
    /* 0x05C */ f32 mGroundH;
    /* 0x060 */ u8 field_0x60;
    /* 0x064 */ f32 mGndUpY;
    /* 0x068 */ f32 field_0x68;
    /* 0x06C */ cM3dGCyl mOldCyl;
    /* 0x084 */ cM3dGCyl mCyl;
    /* 0x09C */ cM3dGLin mLin;
    /* 0x0B8 */ cBgS_GndChk mGndChk;
    /* 0x0F8 */ cBgS_LinChk mLinChk;
};  // Size: 0x150

class dBgS_LinkCrrPos : public dBgS_CrrPos {
public:
    dBgS_LinkCrrPos() { SetLink(); }

    virtual ~dBgS_LinkCrrPos() {}
};

u32 dBgS_GetRoomPathPntNo(u32 polyinfo2);
void dBgS_ChangeAttributeCode(u32 code, u32* dst);

#endif /* D_BG_D_BG_S_H */