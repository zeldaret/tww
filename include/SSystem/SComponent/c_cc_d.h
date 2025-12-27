#ifndef C_CC_D_H
#define C_CC_D_H

#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "SSystem/SComponent/c_m3d_g_cps.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"
#include "f_pc/f_pc_base.h"

class fopAc_ac_c;
class cCcD_PntAttr;
class cCcD_CpsAttr;
class cCcD_TriAttr;
class cCcD_AabAttr;
class cCcD_CylAttr;
class cCcD_SphAttr;

enum cCcD_AtSPrm_e {
    /* 0x01 */ cCcD_AtSPrm_Set_e = 0x01,
    /* 0x02 */ cCcD_AtSPrm_VsEnemy_e = 0x02,
    /* 0x04 */ cCcD_AtSPrm_VsPlayer_e = 0x04,
    /* 0x08 */ cCcD_AtSPrm_VsOther_e = 0x08,
    /* 0x0E */ cCcD_AtSPrm_GrpAll_e = cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
    /* 0x10 */ cCcD_AtSPrm_NoTgHitInfSet_e = 0x10,
};

enum cCcD_AtRPrm_e {
    cCcD_AtRPrm_Hit_e = 1 << 0,
};

enum cCcD_TgSPrm_e {
    /* 0x01 */ cCcD_TgSPrm_Set_e = 0x01,
    /* 0x02 */ cCcD_TgSPrm_IsEnemy_e = 0x02,
    /* 0x04 */ cCcD_TgSPrm_IsPlayer_e = 0x04,
    /* 0x08 */ cCcD_TgSPrm_IsOther_e = 0x08,
    /* 0x0E */ cCcD_TgSPrm_GrpAll_e = cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
    /* 0x10 */ cCcD_TgSPrm_NoAtHitInfSet_e = 0x10,
};

enum cCcD_TgRPrm_e {
    cCcD_TgRPrm_Hit_e = 1 << 0,
};

enum cCcD_CoSPrm_e {
    /* 0x0001 */ cCcD_CoSPrm_Set_e = 0x01,
    /* 0x0002 */ cCcD_CoSPrm_IsEnemy_e = 0x02,
    /* 0x0004 */ cCcD_CoSPrm_IsPlayer_e = 0x04,
    /* 0x0008 */ cCcD_CoSPrm_IsOther_e = 0x08,
    /* 0x0010 */ cCcD_CoSPrm_VsEnemy_e = 0x10,
    /* 0x0020 */ cCcD_CoSPrm_VsPlayer_e = 0x20,
    /* 0x0040 */ cCcD_CoSPrm_VsOther_e = 0x40,
    /* 0x000E */ cCcD_CoSPrm_IGrpAll_e = cCcD_CoSPrm_IsEnemy_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_IsOther_e,
    /* 0x0070 */ cCcD_CoSPrm_VsGrpAll_e = cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
    /* 0x0080 */ cCcD_CoSPrm_Sph3DCrr_e = 0x80,
    /* 0x0100 */ cCcD_CoSPrm_NoCrr_e = 0x100,
    /* 0x0200 */ cCcD_CoSPrm_NoCoHitInfSet_e = 0x200,
};

enum cCcD_CoRPrm_e {
    cCcD_CoRPrm_Hit_e = 1 << 0,
};

class cCcD_ShapeAttr {
public:
    /* 0x00 */ cM3dGAab mAab;
    /* 0x1C vtable */

    cCcD_ShapeAttr() {}
    virtual ~cCcD_ShapeAttr() {}
    virtual bool CrossAtTg(cCcD_ShapeAttr const&, cXyz*) const {
        return false;
    }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const = 0;
    virtual bool CrossCo(cCcD_ShapeAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const = 0;
    virtual const cXyz* GetCoCP() const { return &m_virtual_center; }
    virtual cXyz* GetCoCP() { return &m_virtual_center; }
    virtual void CalcAabBox() = 0;
    virtual bool GetNVec(cXyz const&, cXyz*) const = 0;

    cM3dGAab& GetWorkAab() { return mAab; }
    cM3dGAab const& GetWorkAab() const { return mAab; }

    static cXyz m_virtual_center;
};  // Size: 0x20

STATIC_ASSERT(0x20 == sizeof(cCcD_ShapeAttr));

struct cCcD_SrcCylAttr {
    cM3dGCylS mCyl;
};

struct cCcD_SrcTriAttr {
    cM3dGTriS mTri;
};

class cCcD_TriAttr : public cCcD_ShapeAttr, public cM3dGTri {
public:
    cCcD_TriAttr() {}

    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const {
        return shape.CrossAtTg(*this, xyz);
    }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const {
        return shape.CrossCo(*this, f);
    }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const { return false; }
    virtual ~cCcD_TriAttr() {}
};  // Size: 0x58

struct cCcD_SrcCpsAttr {
    cM3dGCpsS mCps;
};

class cCcD_CpsAttr : public cCcD_ShapeAttr, public cM3dGCps {
public:
    /* 0x00 */ /* cCcD_ShapeAttr */
    /* 0x20 */ /* cM3dGCps */

    cCcD_CpsAttr() {}
    void Set(const cCcD_SrcCpsAttr& pSrc) {
        cM3dGCps::Set(pSrc.mCps);
    }
    void Set(const cXyz& pStart, const cXyz& pEnd, f32 radius) {
        cM3dGCps::Set(pStart, pEnd, radius);
    }

    virtual ~cCcD_CpsAttr() {}
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const {
        return shape.CrossAtTg(*this, xyz);
    }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const {
        return shape.CrossCo(*this, f);
    }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
};  // Size: 0x40

STATIC_ASSERT(0x40 == sizeof(cCcD_CpsAttr));

struct cCcD_SrcSphAttr {
    cM3dGSphS mSph;
};

class cCcD_SphAttr : public cCcD_ShapeAttr, public cM3dGSph {
public:
    cCcD_SphAttr() {}

    inline void Set(const cCcD_SrcSphAttr& src) {
        cM3dGSph::Set(src.mSph);
    }

    virtual ~cCcD_SphAttr() {}
    virtual const cXyz* GetCoCP() const { return &mCenter; }
    virtual cXyz* GetCoCP() { return &mCenter; }
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const {
        return shape.CrossAtTg(*this, xyz);
    }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const {
        return shape.CrossCo(*this, f);
    }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
};  // Size = 0x34

STATIC_ASSERT(0x34 == sizeof(cCcD_SphAttr));

class cCcD_CylAttr : public cCcD_ShapeAttr, public cM3dGCyl {
public:
    cCcD_CylAttr() {}
    inline void Set(const cCcD_SrcCylAttr& src) {
        cM3dGCyl::Set(src.mCyl);
    }

    virtual ~cCcD_CylAttr() {}
    virtual const cXyz* GetCoCP() const { return &mCenter; }
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const {
        return shape.CrossAtTg(*this, xyz);
    }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const {
        return shape.CrossCo(*this, f);
    }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual cXyz* GetCoCP() { return &mCenter; }
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;

};  // Size = 0x38

STATIC_ASSERT(0x38 == sizeof(cCcD_CylAttr));

class cCcD_DivideInfo {
public:
    /* 0x00 */ u32 mRangeBits;
    /* 0x04 vtable */
public:
    cCcD_DivideInfo() {}
    virtual ~cCcD_DivideInfo() {}
    void Set(u32 param_1) { mRangeBits = param_1; }
    bool Chk(cCcD_DivideInfo const&) const;
};  // Size = 0x8

STATIC_ASSERT(0x8 == sizeof(cCcD_DivideInfo));

class cCcD_DivideArea : public cM3dGAab {
private:
    /* 0x1C */ bool mXDiffIsZero;
    /* 0x20 */ f32 mScaledXDiff;
    /* 0x24 */ f32 mInvScaledXDiff;
    /* 0x28 */ bool mYDiffIsZero;
    /* 0x2C */ f32 mScaledYDiff;
    /* 0x30 */ f32 mInvScaledYDiff;
    /* 0x34 */ bool mZDiffIsZero;
    /* 0x38 */ f32 mScaledZDiff;
    /* 0x3C */ f32 mInvScaledZDiff;

public:
    cCcD_DivideArea() {}
    virtual ~cCcD_DivideArea() {}
    void SetArea(cM3dGAab const&);
    void CalcDivideInfo(cCcD_DivideInfo*, cM3dGAab const&, u32);
    void CalcDivideInfoOverArea(cCcD_DivideInfo*, cM3dGAab const&);
};  // Size = 0x40

STATIC_ASSERT(0x40 == sizeof(cCcD_DivideArea));

struct cCcD_SrcObjCommonBase {
    /* 0x0 */ u32 mSPrm;
};

struct cCcD_SrcObjTg {
    /* 0x0 */ u32 mType;
    /* 0x4 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0x8

struct cCcD_SrcObjAt {
    /* 0x0 */ u32 mType;
    /* 0x4 */ u8 mAtp;
    /* 0x8 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0xC

struct cCcD_SrcObjCo {
    /* 0x0 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0x4

struct cCcD_SrcObjHitInf {
    /* 0x00 */ cCcD_SrcObjAt mObjAt;
    /* 0x0C */ cCcD_SrcObjTg mObjTg;
    /* 0x14 */ cCcD_SrcObjCo mObjCo;
};  // Size: 0x18

struct cCcD_SrcObj {
    /* 0x0 */ u32 mFlags;
    /* 0x4 */ cCcD_SrcObjHitInf mSrcObjHitInf;
};  // Size: 0x1C

class cCcD_GStts {
public:
    virtual ~cCcD_GStts() {}

private:
    /* 0x00 vtable */
};  // Size = 0x4

STATIC_ASSERT(sizeof(cCcD_GStts) == 0x4);

class cCcD_Stts {
private:
    /* 0x00 */ cXyz m_cc_move;
    /* 0x0C */ fopAc_ac_c* mp_actor;
    /* 0x10 */ fpc_ProcID m_apid;
    /* 0x14 */ u8 m_weight;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 m_dmg;
    /* 0x18 */ /* vtable */

public:
    cCcD_Stts() {}
    virtual ~cCcD_Stts() {}
    virtual const cCcD_GStts* GetGStts() const;
    virtual cCcD_GStts* GetGStts();
    void Init(int, int, void*, fpc_ProcID);
    virtual void Ct();
#if VERSION == VERSION_DEMO
    void PlusCcMove(f32 x, f32 y, f32 z) {
        m_cc_move.x += x;
        m_cc_move.y += y;
        m_cc_move.z += z;
    }
#else
    void PlusCcMove(f32, f32, f32);
#endif
    void ClrCcMove() {
        m_cc_move.x = m_cc_move.y = m_cc_move.z = 0.0f;
    }
    void PlusDmg(int dmg) { m_dmg = dmg; }
    u8 GetDmg() { return m_dmg; }
    f32 GetWeightF() const { return (s32)m_weight; }
    u8 GetWeightUc() const { return m_weight; }
    void SetWeight(u8 weight) { m_weight = weight; }
    virtual void ClrAt() {}
    virtual void ClrTg() { m_dmg = 0; }
    
    fopAc_ac_c* GetActor() const { return mp_actor; }
    void SetActor(void* ac) { mp_actor = (fopAc_ac_c*)ac; }
    cXyz* GetCCMoveP() { return &m_cc_move; }
    fpc_ProcID GetApid() const { return m_apid; }
};  // Size = 0x1C

STATIC_ASSERT(0x1C == sizeof(cCcD_Stts));

class cCcD_Obj;  // placeholder

class cCcD_ObjCommonBase {
protected:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ cCcD_Obj* mHitObj;
    /* 0x0C vtable */
public:
    cCcD_ObjCommonBase() { ct(); }
    virtual ~cCcD_ObjCommonBase() {}
    void ct() {
        SetSPrm(0);
        SetRPrm(0);
        ClrObj();
    }
    void SetSPrm(u32 sprm) { mSPrm = sprm; }
    void SetRPrm(u32 rprm) { mRPrm = rprm; }
    cCcD_Obj* GetHitObj() const { return mHitObj; }
    void ClrObj() { mHitObj = NULL; }
    u32 MskSPrm(u32 mask) const { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) const { return mRPrm & mask; }
    void OnSPrmBit(u32 flag) { mSPrm |= flag; }
    void OffSPrmBit(u32 flag) { mSPrm &= ~flag; }
    void ClrRPrm(u32 flag) { mRPrm &= ~flag; }
    void SetHitObj(cCcD_Obj* obj) { mHitObj = obj; }

    void Set(cCcD_SrcObjCommonBase const& src) {
        mSPrm = src.mSPrm;
    }
};

STATIC_ASSERT(0x10 == sizeof(cCcD_ObjCommonBase));

class cCcD_ObjAt : public cCcD_ObjCommonBase {
public:
    cCcD_ObjAt() { mType = 0; }
    virtual ~cCcD_ObjAt() {}
    void SetHit(cCcD_Obj* obj) {
        SetRPrm(cCcD_AtRPrm_Hit_e);
        SetHitObj(obj);
    }
    void Set(cCcD_SrcObjAt const& src) {
        cCcD_ObjCommonBase::Set(src.mBase);
        mType = src.mType;
        mAtp = src.mAtp;
    }
    void ClrHit() { ClrRPrm(cCcD_AtRPrm_Hit_e); ClrObj(); }
    u32 GetType() const { return mType; }
    u32 GetGrp() const { return MskSPrm(cCcD_AtSPrm_GrpAll_e); }
    bool ChkSet() const { return MskSPrm(cCcD_AtSPrm_Set_e); }
    u8 GetAtp() const { return mAtp; }
    u32 MskType(u32 msk) const { return mType & msk; }
    void SetType(u32 type) { mType = type; }
    void SetAtp(int atp) { mAtp = atp; }
    void ClrSet() { OffSPrmBit(cCcD_AtSPrm_Set_e); }
    void OnHitBit() { SetRPrm(cCcD_AtRPrm_Hit_e); }
    void OffHitBit() { ClrRPrm(cCcD_AtRPrm_Hit_e); }
    u32 ChkHit() const { return MskRPrm(cCcD_AtRPrm_Hit_e); }

protected:
    /* 0x10 */ u32 mType;
    /* 0x14 */ u8 mAtp; // AtPoint, amount of damage done when attacking
}; // size = 0x18

STATIC_ASSERT(0x18 == sizeof(cCcD_ObjAt));

class cCcD_ObjTg : public cCcD_ObjCommonBase {
public:
    cCcD_ObjTg() { ct(); }
    virtual ~cCcD_ObjTg() {}
    void Set(cCcD_SrcObjTg const& src) {
        cCcD_ObjCommonBase::Set(src.mBase);
        mType = src.mType;
    }
    void SetGrp(u32 grp) {
        OffSPrmBit(cCcD_TgSPrm_GrpAll_e);
        OnSPrmBit(grp);
    }
    void ClrHit() { ClrRPrm(cCcD_TgRPrm_Hit_e); ClrObj(); }
    void SetHit(cCcD_Obj* obj) {
        SetRPrm(cCcD_TgRPrm_Hit_e);
        SetHitObj(obj);
    }
    u32 GetType() const { return mType; }
    void SetType(u32 type) { mType = type; }
    u32 GetGrp() const { return MskSPrm(cCcD_TgSPrm_GrpAll_e); }
    bool ChkSet() const { return MskSPrm(cCcD_TgSPrm_Set_e); }
    void ClrSet() { OffSPrmBit(cCcD_TgSPrm_Set_e); }
    u32 ChkHit() const { return MskRPrm(cCcD_TgRPrm_Hit_e); }

private:
    /* 0x10 */ u32 mType;
};

STATIC_ASSERT(0x14 == sizeof(cCcD_ObjTg));

class cCcD_ObjCo : public cCcD_ObjCommonBase {
public:
    virtual ~cCcD_ObjCo() {}
    void SetHit(cCcD_Obj* obj) {
        SetRPrm(cCcD_CoRPrm_Hit_e);
        SetHitObj(obj);
    }
    void ClrHit() { ClrRPrm(cCcD_CoRPrm_Hit_e); ClrObj(); }
    void SetIGrp(u32 grp) { // Fake inline, but exists in TP
        OffSPrmBit(cCcD_CoSPrm_IGrpAll_e);
        OnSPrmBit(grp);
    }
    void SetVsGrp(u32 grp) {
        OffSPrmBit(cCcD_CoSPrm_VsGrpAll_e);
        OnSPrmBit(grp);
    }
    bool ChkSet() const { return MskSPrm(cCcD_CoSPrm_Set_e); }
    u32 GetVsGrp() const { return MskSPrm(cCcD_CoSPrm_VsGrpAll_e); }
    u32 GetIGrp() const { return MskSPrm(cCcD_CoSPrm_IGrpAll_e); }
    u32 ChkNoCrr() const { return MskSPrm(cCcD_CoSPrm_NoCrr_e); }
    u32 ChkSph3DCrr() const { return MskSPrm(cCcD_CoSPrm_Sph3DCrr_e); }
    void ClrSet() { OffSPrmBit(cCcD_CoSPrm_Set_e); }
    u32 ChkHit() const { return MskRPrm(cCcD_CoRPrm_Hit_e); }

    void Set(cCcD_SrcObjCo const& src) {
        cCcD_ObjCommonBase::Set(src.mBase);
    }
};

STATIC_ASSERT(0x10 == sizeof(cCcD_ObjCo));

class cCcD_ObjHitInf {
protected:
    /* 0x000 */ cCcD_ObjAt mObjAt;
    /* 0x018 */ cCcD_ObjTg mObjTg;
    /* 0x02C */ cCcD_ObjCo mObjCo;
    /* 0x03C vtable */
public:
    virtual ~cCcD_ObjHitInf() {}

    void Set(const cCcD_SrcObjHitInf& src) {
        mObjAt.Set(src.mObjAt);
        mObjTg.Set(src.mObjTg);
        mObjCo.Set(src.mObjCo);
    }
    cCcD_ObjAt& GetObjAt() { return mObjAt; } // Fake inline
    cCcD_ObjTg& GetObjTg() { return mObjTg; } // Fake inline
    cCcD_ObjCo& GetObjCo() { return mObjCo; } // Fake inline
    u32 GetTgGrp() const { return mObjTg.GetGrp(); }
    u32 GetAtGrp() const { return mObjAt.GetGrp(); }
    u32 GetTgType() const { return mObjTg.GetType(); }
    u32 GetAtType() const { return mObjAt.GetType(); }
    bool ChkTgSet() const { return mObjTg.ChkSet(); }
    bool ChkAtSet() const { return mObjAt.ChkSet(); }
    bool ChkCoSet() const { return mObjCo.ChkSet(); }
    u32 GetCoVsGrp() const { return mObjCo.GetVsGrp(); }
    u32 GetCoIGrp() const { return mObjCo.GetIGrp(); }
    u8 GetAtAtp() const { return mObjAt.GetAtp(); }
    u32 ChkAtNoTgHitInfSet() const { return mObjAt.MskSPrm(cCcD_AtSPrm_NoTgHitInfSet_e); }
    u32 ChkTgNoAtHitInfSet() const { return mObjTg.MskSPrm(cCcD_TgSPrm_NoAtHitInfSet_e); }
    u32 ChkCoNoCoHitInfSet() { return mObjCo.MskSPrm(cCcD_CoSPrm_NoCoHitInfSet_e); }
    void SetAtHit(cCcD_Obj* obj) { mObjAt.SetHit(obj); }
    void SetTgHit(cCcD_Obj* obj) { mObjTg.SetHit(obj); }
    void SetCoHit(cCcD_Obj* obj) { mObjCo.SetHit(obj); }
    bool ChkAtType(u32 type) const { return mObjAt.MskType(type); }
    u32 ChkCoNoCrr() const { return mObjCo.ChkNoCrr(); }
    u32 ChkCoSph3DCrr() const { return mObjCo.ChkSph3DCrr(); }
    void OnAtSPrmBit(u32 flag) { mObjAt.OnSPrmBit(flag); }
    void OffAtSPrmBit(u32 flag) { mObjAt.OffSPrmBit(flag); }
    void OnTgSPrmBit(u32 flag) { mObjTg.OnSPrmBit(flag); }
    void OffTgSPrmBit(u32 flag) { mObjTg.OffSPrmBit(flag); }
    void OnCoSPrmBit(u32 flag) { mObjCo.OnSPrmBit(flag); }
    void OffCoSPrmBit(u32 flag) { mObjCo.OffSPrmBit(flag); }
    void SetAtType(u32 type) { mObjAt.SetType(type); }
    void OnAtSetBit() { mObjAt.OnSPrmBit(cCcD_AtSPrm_Set_e); }
    void SetAtAtp(int atp) { mObjAt.SetAtp(atp); }
    void OffCoSetBit() { mObjCo.ClrSet(); }
    void SetTgType(u32 type) { mObjTg.SetType(type); }
    void OffAtSetBit() { mObjAt.ClrSet(); }
    void OnAtHitBit() { mObjAt.OnHitBit(); }
    void OffAtHitBit() { mObjAt.OffHitBit(); }
    void OnTgSetBit() { mObjTg.OnSPrmBit(cCcD_TgSPrm_Set_e); }
    void OffTgSetBit() { mObjTg.ClrSet(); }
    void OnCoSetBit() { mObjCo.OnSPrmBit(cCcD_CoSPrm_Set_e); }
    void OnAtVsBitSet(u32 prm) { mObjAt.OnSPrmBit(prm); }
    void OffAtVsBitSet(u32 prm) { mObjAt.OffSPrmBit(prm); }
    void OnAtVsEnemyBit() { mObjAt.OnSPrmBit(cCcD_AtSPrm_VsEnemy_e); }
    void OffAtVsEnemyBit() { mObjAt.OffSPrmBit(cCcD_AtSPrm_VsEnemy_e); }
    void OnAtVsPlayerBit() { mObjAt.OnSPrmBit(cCcD_AtSPrm_VsPlayer_e); }
    void OffAtVsPlayerBit() { mObjAt.OffSPrmBit(cCcD_AtSPrm_VsPlayer_e); }
    void SetTgSPrm(u32 prm) { mObjTg.SetSPrm(prm); } // Fake inline, but exists in TP
    void SetCoSPrm(u32 prm) { mObjCo.SetSPrm(prm); }
    void ClrAtHit() { mObjAt.ClrHit(); }
    void ClrTgHit() { mObjTg.ClrHit(); }
    void ClrCoHit() { mObjCo.ClrHit(); }
    u32 ChkAtHit() const { return mObjAt.ChkHit(); }
    u32 ChkTgHit() const { return mObjTg.ChkHit(); }
    u32 ChkCoHit() const { return mObjCo.ChkHit(); }
    cCcD_Obj* GetAtHitObj() const { return mObjAt.GetHitObj(); }
    cCcD_Obj* GetTgHitObj() const { return mObjTg.GetHitObj(); }
    cCcD_Obj* GetCoHitObj() const { return mObjCo.GetHitObj(); }
    void ClrAtSet() { OffAtSetBit(); }
    void ClrTgSet() { OffTgSetBit(); }
    void ClrCoSet() { OffCoSetBit(); }
    u32 MskAtSPrm(u32 prm) const { return mObjAt.MskSPrm(prm); }
    void OnAtNoTgHitInfSet() { mObjAt.OnSPrmBit(cCcD_AtSPrm_NoTgHitInfSet_e); }
    void OffAtNoTgHitInfSet() { mObjAt.OffSPrmBit(cCcD_AtSPrm_NoTgHitInfSet_e); }
    void OnTgNoAtHitInfSet() { mObjTg.OnSPrmBit(cCcD_TgSPrm_NoAtHitInfSet_e); }
    void SetTgGrp(u32 grp) { mObjTg.SetGrp(grp); }
    void SetCoIGrp(u32 grp) { mObjCo.SetIGrp(grp); } // Fake inline, but exists in TP
    void SetCoVsGrp(u32 grp) { mObjCo.SetVsGrp(grp); }
};  // Size = 0x40

STATIC_ASSERT(0x40 == sizeof(cCcD_ObjHitInf));

class cCcD_GObjInf;

class cCcD_Obj : public cCcD_ObjHitInf {
public:
    cCcD_Obj() { ct(); }
    virtual ~cCcD_Obj() {}
    virtual cCcD_GObjInf const* GetGObjInf() const { return NULL; }
    virtual cCcD_GObjInf* GetGObjInf() { return NULL; }
    virtual cCcD_ShapeAttr const* GetShapeAttr() const { return NULL; }
    virtual cCcD_ShapeAttr* GetShapeAttr() { return NULL; }
    void ct() {
        mFlags = 0;
    }
    void Set(cCcD_SrcObj const&);

    cCcD_Stts* GetStts() { return mStts; }
    void SetStts(cCcD_Stts* stts) { mStts = stts; }
    fopAc_ac_c* GetAc() { return mStts == NULL ? NULL : mStts->GetActor(); }
    cCcD_DivideInfo& GetDivideInfo() { return mDivideInfo; }
    cCcD_DivideInfo* GetPDivideInfo() { return &mDivideInfo; }
    u32 ChkBsRevHit() const { return mFlags & 2; }
    void OnBsRevHit() { mFlags |= 2; }

private:
    /* 0x040 */ u32 mFlags;
    /* 0x044 */ cCcD_Stts* mStts;
    /* 0x048 */ cCcD_DivideInfo mDivideInfo;
};  // Size = 0x50

STATIC_ASSERT(0x50 == sizeof(cCcD_Obj));

class cCcD_GObjInf : public cCcD_Obj {
public:
    cCcD_GObjInf() {}
    virtual ~cCcD_GObjInf() {}
    virtual void ClrAtHit() { mObjAt.ClrHit(); }
    virtual void ClrTgHit() { mObjTg.ClrHit(); }
    virtual void ClrCoHit() { mObjCo.ClrHit(); }
    virtual cCcD_GObjInf const* GetGObjInf() const { return this; }
    virtual cCcD_GObjInf* GetGObjInf() { return this; }
};

STATIC_ASSERT(0x50 == sizeof(cCcD_GObjInf));

#endif /* C_CC_D_H */
