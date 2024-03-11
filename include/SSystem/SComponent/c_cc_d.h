#ifndef C_CC_D_H
#define C_CC_D_H

#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "SSystem/SComponent/c_m3d_g_cps.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"

class fopAc_ac_c;
class cCcD_PntAttr;
class cCcD_CpsAttr;
class cCcD_TriAttr;
class cCcD_AabAttr;
class cCcD_CylAttr;
class cCcD_SphAttr;

enum cCcD_ObjAtType {
    /* 0x00000002 */ AT_TYPE_SWORD          = (1 << 1),
    /* 0x00000020 */ AT_TYPE_BOMB           = (1 << 5),
    /* 0x00000040 */ AT_TYPE_BOOMERANG      = (1 << 6),
    /* 0x00000080 */ AT_TYPE_BOKO_STICK     = (1 << 7),
    /* 0x00000100 */ AT_TYPE_WATER          = (1 << 8),
    /* 0x00000200 */ AT_TYPE_FIRE           = (1 << 9),
    /* 0x00000400 */ AT_TYPE_MACHETE        = (1 << 10),
    /* 0x00000800 */ AT_TYPE_UNK800         = (1 << 11),
    /* 0x00001000 */ AT_TYPE_UNK1000        = (1 << 12),
    /* 0x00002000 */ AT_TYPE_UNK2000        = (1 << 13),
    /* 0x00004000 */ AT_TYPE_NORMAL_ARROW   = (1 << 14),
    /* 0x00008000 */ AT_TYPE_HOOKSHOT       = (1 << 15),
    /* 0x00010000 */ AT_TYPE_SKULL_HAMMER   = (1 << 16),
    /* 0x00020000 */ AT_TYPE_UNK20000       = (1 << 17),
    /* 0x00040000 */ AT_TYPE_FIRE_ARROW     = (1 << 18),
    /* 0x00080000 */ AT_TYPE_ICE_ARROW      = (1 << 19),
    /* 0x00100000 */ AT_TYPE_LIGHT_ARROW    = (1 << 20),
    /* 0x00200000 */ AT_TYPE_WIND           = (1 << 21),
    /* 0x00400000 */ AT_TYPE_UNK400000      = (1 << 22),
    /* 0x00800000 */ AT_TYPE_LIGHT          = (1 << 23),
    /* 0x01000000 */ AT_TYPE_STALFOS_MACE   = (1 << 24),
    /* 0x02000000 */ AT_TYPE_UNK2000000     = (1 << 25),
    /* 0x04000000 */ AT_TYPE_DARKNUT_SWORD  = (1 << 26),
    /* 0x08000000 */ AT_TYPE_GRAPPLING_HOOK = (1 << 27),
    /* 0x10000000 */ AT_TYPE_MOBLIN_SPEAR   = (1 << 28),
    /* 0x20000000 */ AT_TYPE_PGANON_SWORD   = (1 << 29),
    /* 0xFFFFFFFF */ AT_TYPE_ALL            = ~0,
};

enum cCcD_AtSPrm_e {
    /* 0x01 */ AT_SPRM_SET = 0x01,
    /* 0x02 */ AT_SPRM_VS_ENEMY = 0x02,
    /* 0x04 */ AT_SPRM_VS_PLAYER = 0x04,
    /* 0x08 */ AT_SPRM_VS_OTHER = 0x08,
    /* 0x0E */ AT_SPRM_GRP = AT_SPRM_VS_ENEMY | AT_SPRM_VS_PLAYER | AT_SPRM_VS_OTHER,
    /* 0x10 */ AT_SPRM_NO_TG_HIT_INF_SET = 0x10,
};

enum cCcD_TgSPrm_e {
    /* 0x01 */ TG_SPRM_SET = 0x01,
    /* 0x02 */ TG_SPRM_IS_ENEMY = 0x02,
    /* 0x04 */ TG_SPRM_IS_PLAYER = 0x04,
    /* 0x08 */ TG_SPRM_IS_OTHER = 0x08,
    /* 0x0E */ TG_SPRM_GRP = TG_SPRM_IS_ENEMY | TG_SPRM_IS_PLAYER | TG_SPRM_IS_OTHER,
    /* 0x10 */ TG_SPRM_NO_AT_HIT_INF_SET = 0x10,
};

enum cCcD_CoSPrm_e {
    /* 0x0001 */ CO_SPRM_SET = 0x01,
    /* 0x0002 */ CO_SPRM_IS_UNK2 = 0x02,
    /* 0x0004 */ CO_SPRM_IS_UNK4 = 0x04,
    /* 0x0008 */ CO_SPRM_IS_UNK8 = 0x08,
    /* 0x0010 */ CO_SPRM_VS_UNK2 = 0x10,
    /* 0x0020 */ CO_SPRM_VS_UNK4 = 0x20,
    /* 0x0040 */ CO_SPRM_VS_UNK8 = 0x40,
    /* 0x000E */ CO_SPRM_IGRP = CO_SPRM_IS_UNK2 | CO_SPRM_IS_UNK4 | CO_SPRM_IS_UNK8,
    /* 0x0070 */ CO_SPRM_VSGRP = CO_SPRM_VS_UNK2 | CO_SPRM_VS_UNK4 | CO_SPRM_VS_UNK8,
    /* 0x0080 */ CO_SPRM_SPH_3D_CRR = 0x80,
    /* 0x0100 */ CO_SPRM_NO_CRR = 0x100,
    /* 0x0200 */ CO_SPRM_NO_CO_HIT_INF_SET = 0x200,
};

class cCcD_ShapeAttr {
public:
    /* 0x00 */ cM3dGAab mAab;
    /* 0x1C vtable */

    struct Shape {
        ~Shape();

        /* 0x00 */ int _0;
        /* 0x04 */ f32 _4;
        /* 0x08 */ f32 _8;
        /* 0x0C */ f32 _C;
        /* 0x10 */ f32 _10;
        /* 0x14 */ f32 _14;
    };
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
};

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
    void Set(const cXyz& pStart, const cXyz& pEnd, float radius) {
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
};

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

class cCcD_Stts {
private:
    /* 0x00 */ cXyz m_cc_move;
    /* 0x0C */ fopAc_ac_c* mActor;
    /* 0x10 */ uint mApid;
    /* 0x14 */ u8 mWeight;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 mDmg;
    /* 0x18 */ /* vtable */

public:
    cCcD_Stts() {}
    virtual ~cCcD_Stts() {}
    virtual const cCcD_GStts* GetGStts() const;
    virtual cCcD_GStts* GetGStts();
    void Init(int, int, void*, uint);
    virtual void Ct();
    void PlusCcMove(f32, f32, f32);
    void ClrCcMove() {
        m_cc_move.x = m_cc_move.y = m_cc_move.z = 0.0f;
    }
    void PlusDmg(int dmg) { mDmg = dmg; }
    u8 GetDmg() { return mDmg; }
    f32 GetWeightF() const { return (s32)mWeight; }
    u8 GetWeightUc() const { return mWeight; }
    void SetWeight(u8 weight) { mWeight = weight; }
    virtual void ClrAt() {}
    virtual void ClrTg() { mDmg = 0; }
    
    fopAc_ac_c* GetActor() const { return mActor; }
    void SetActor(void* ac) { mActor = (fopAc_ac_c*)ac; }
    cXyz* GetCCMoveP() { return &m_cc_move; }
    uint GetApid() const { return mApid; }
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
        SetRPrm(1);
        SetHitObj(obj);
    }
    void Set(cCcD_SrcObjAt const& src) {
        cCcD_ObjCommonBase::Set(src.mBase);
        mType = src.mType;
        mAtp = src.mAtp;
    }
    void ClrHit() { ClrRPrm(1); ClrObj(); }
    u32 GetType() const { return mType; }
    u32 GetGrp() const { return MskSPrm(AT_SPRM_GRP); }
    bool ChkSet() const { return MskSPrm(AT_SPRM_SET); }
    u8 GetAtp() const { return mAtp; }
    u32 MskType(u32 msk) const { return mType & msk; }
    void SetType(u32 type) { mType = type; }
    void SetAtp(int atp) { mAtp = atp; }
    void ClrSet() { OffSPrmBit(AT_SPRM_SET); }
    void OnHitBit() { SetRPrm(1); }
    void OffHitBit() { ClrRPrm(1); }
    u32 ChkHit() const { return MskRPrm(1); }

protected:
    /* 0x10 */ u32 mType;
    /* 0x14 */ u8 mAtp;
};

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
        OffSPrmBit(TG_SPRM_GRP);
        OnSPrmBit(grp);
    }
    void ClrHit() { ClrRPrm(1); ClrObj(); }
    void SetHit(cCcD_Obj* obj) {
        SetRPrm(1);
        SetHitObj(obj);
    }
    u32 GetType() const { return mType; }
    void SetType(u32 type) { mType = type; }
    u32 GetGrp() const { return MskSPrm(TG_SPRM_GRP); }
    bool ChkSet() const { return MskSPrm(TG_SPRM_SET); }
    void ClrSet() { OffSPrmBit(TG_SPRM_SET); }
    u32 ChkHit() const { return MskRPrm(1); }

private:
    /* 0x10 */ u32 mType;
};

STATIC_ASSERT(0x14 == sizeof(cCcD_ObjTg));

class cCcD_ObjCo : public cCcD_ObjCommonBase {
public:
    virtual ~cCcD_ObjCo() {}
    void SetHit(cCcD_Obj* obj) {
        SetRPrm(1);
        SetHitObj(obj);
    }
    void ClrHit() { ClrRPrm(1); ClrObj(); }
    void SetIGrp(u32 grp) { // Fake inline, but exists in TP
        OffSPrmBit(CO_SPRM_IGRP);
        OnSPrmBit(grp);
    }
    void SetVsGrp(u32 grp) {
        OffSPrmBit(CO_SPRM_VSGRP);
        OnSPrmBit(grp);
    }
    bool ChkSet() const { return MskSPrm(CO_SPRM_SET); }
    u32 GetVsGrp() const { return MskSPrm(CO_SPRM_VSGRP); }
    u32 GetIGrp() const { return MskSPrm(CO_SPRM_IGRP); }
    u32 ChkNoCrr() const { return MskSPrm(CO_SPRM_NO_CRR); }
    u32 ChkSph3DCrr() const { return MskSPrm(CO_SPRM_SPH_3D_CRR); }
    void ClrSet() { OffSPrmBit(CO_SPRM_SET); }
    u32 ChkHit() const { return MskRPrm(1); }

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
    u32 ChkAtNoTgHitInfSet() const { return mObjAt.MskSPrm(AT_SPRM_NO_TG_HIT_INF_SET); }
    u32 ChkTgNoAtHitInfSet() const { return mObjTg.MskSPrm(TG_SPRM_NO_AT_HIT_INF_SET); }
    u32 ChkCoNoCoHitInfSet() { return mObjCo.MskSPrm(CO_SPRM_NO_CO_HIT_INF_SET); }
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
    void OnAtSetBit() { mObjAt.OnSPrmBit(AT_SPRM_SET); }
    void SetAtAtp(int atp) { mObjAt.SetAtp(atp); }
    void OffCoSetBit() { mObjCo.ClrSet(); }
    void SetTgType(u32 type) { mObjTg.SetType(type); }
    void OffAtSetBit() { mObjAt.ClrSet(); }
    void OnAtHitBit() { mObjAt.OnHitBit(); }
    void OffAtHitBit() { mObjAt.OffHitBit(); }
    void OnTgSetBit() { mObjTg.OnSPrmBit(TG_SPRM_SET); }
    void OffTgSetBit() { mObjTg.ClrSet(); }
    void OnCoSetBit() { mObjCo.OnSPrmBit(CO_SPRM_SET); }
    void OnAtVsBitSet(u32 prm) { mObjAt.OnSPrmBit(prm); }
    void OffAtVsBitSet(u32 prm) { mObjAt.OffSPrmBit(prm); }
    void OnAtVsEnemyBit() { mObjAt.OnSPrmBit(AT_SPRM_VS_ENEMY); }
    void OffAtVsEnemyBit() { mObjAt.OffSPrmBit(AT_SPRM_VS_ENEMY); }
    void OnAtVsPlayerBit() { mObjAt.OnSPrmBit(AT_SPRM_VS_PLAYER); }
    void OffAtVsPlayerBit() { mObjAt.OffSPrmBit(AT_SPRM_VS_PLAYER); }
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
    void OnAtNoTgHitInfSet() { mObjAt.OnSPrmBit(AT_SPRM_NO_TG_HIT_INF_SET); }
    void OffAtNoTgHitInfSet() { mObjAt.OffSPrmBit(AT_SPRM_NO_TG_HIT_INF_SET); }
    void OnTgNoAtHitInfSet() { mObjTg.OnSPrmBit(TG_SPRM_NO_AT_HIT_INF_SET); }
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
