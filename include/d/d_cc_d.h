#ifndef D_CC_D_CC_D_H
#define D_CC_D_CC_D_H

/**
 * d_cc_d.h
 * Actor Collision
 */

#include "SSystem/SComponent/c_cc_d.h"
#include "f_pc/f_pc_manager.h"

enum dCcD_hitSe {};

enum dCcG_At_Spl {};

enum dCcG_Tg_Spl {};

struct dCcD_SrcGAtTgCoCommonBase {
    /* 0x0 */ u32 mSPrm;
};  // Size: 0x4

struct dCcD_SrcGObjAt {
    /* 0x0 */ u8 mSe;       // Sound Effect ID
    /* 0x1 */ u8 mHitMark;  // Hit Mark particle ID
    /* 0x2 */ u8 mSpl;
    /* 0x3 */ u8 mMtrl;
    /* 0x4 */ dCcD_SrcGAtTgCoCommonBase mBase;
};  // Size: 0x8

struct dCcD_SrcGObjTg {
    /* 0x0 */ u8 mSe;       // Sound Effect ID
    /* 0x1 */ u8 mHitMark;  // Hit Mark particle ID
    /* 0x2 */ u8 mSpl;
    /* 0x3 */ u8 mMtrl;
    /* 0x4 */ dCcD_SrcGAtTgCoCommonBase mBase;
};  // Size: 0x8

struct dCcD_SrcGObjCo {
    /* 0x0 */ dCcD_SrcGAtTgCoCommonBase mBase;
};  // Size: 0x4

struct dCcD_SrcGObjInf {
    /* 0x00 */ cCcD_SrcObj mObj;
    /* 0x1C */ dCcD_SrcGObjAt mGObjAt;
    /* 0x24 */ dCcD_SrcGObjTg mGObjTg;
    /* 0x2C */ dCcD_SrcGObjCo mGObjCo;
};  // Size: 0x30

struct dCcD_SrcSph {
    /* 0x00 */ dCcD_SrcGObjInf mObjInf;
    /* 0x30 */ cCcD_SrcSphAttr mSphAttr;
};  // Size: 0x40

struct dCcD_SrcTri {
    /* 0x00 */ dCcD_SrcGObjInf mObjInf;
    /* 0x30 */ cCcD_SrcTriAttr mTriAttr;
};  // Size: 0x54

struct dCcD_SrcCyl {
    /* 0x00 */ dCcD_SrcGObjInf mObjInf;
    /* 0x30 */ cCcD_SrcCylAttr mCylAttr;
};  // Size: 0x44

struct dCcD_SrcCps {
    /* 0x00 */ dCcD_SrcGObjInf mObjInf;
    /* 0x30 */ cCcD_SrcCpsAttr mCpsAttr;
};  // Size: 0x4C

class dCcD_GStts : public cCcD_GStts {
public:
    dCcD_GStts();
    virtual ~dCcD_GStts() {}

    void Ct();
    void Move();
    void ClrAt() { mAtSpl = 0; }
    void ClrTg() { mTgSpl = 0; }
    void SetAtApid(unsigned int id) { mAtApid = id; }
    void SetTgApid(unsigned int id) { mTgApid = id; }
    u8 GetRoomId() { return mRoomId; }
    void SetRoomId(int id) { mRoomId = id; }
    unsigned int GetAtOldApid() { return mAtOldApid; }
    unsigned int GetTgOldApid() { return mTgOldApid; }
    bool ChkNoActor() { return field_0x1C & 1; }
    bool ChkNoneActorPerfTblId() { return field_0x08 == 0xFFFF; }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mAtSpl; }
    void SetAtSpl(dCcG_At_Spl spl) { mAtSpl = spl; }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mTgSpl; }
    void SetTgSpl(dCcG_Tg_Spl spl) { mTgSpl = spl; }
    void OnNoActor() { field_0x1C |= 1; }

    // private:
    /* 0x04 */ u8 mAtSpl;
    /* 0x05 */ u8 mTgSpl;
    /* 0x06 */ u8 mRoomId;
    /* 0x08 */ u16 field_0x08;
    /* 0x0C */ int mAtApid;
    /* 0x10 */ int mAtOldApid;
    /* 0x14 */ int mTgApid;
    /* 0x18 */ int mTgOldApid;
    /* 0x1C */ int field_0x1C;
};  // Size = 0x20

class dCcD_Stts : public cCcD_Stts, public dCcD_GStts {
public:
    dCcD_Stts() {}
    virtual cCcD_GStts* GetGStts() {
        return (cCcD_GStts*)this;
    }
    void Init(int, int, fopAc_ac_c*);
    virtual void Ct();
    virtual void ClrAt() {
        cCcD_Stts::ClrAt();
        dCcD_GStts::ClrAt();
    }
    virtual void ClrTg() {
        cCcD_Stts::ClrTg();
        dCcD_GStts::ClrTg();
    }
    virtual ~dCcD_Stts() {}

};  // Size = 0x3C

class dCcD_GObjInf;
typedef void (*dCcD_HitCallback)(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);

// Attack/Defense/Correction Collider Common Base
class dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ dCcD_HitCallback mHitCallback;
    /* 0x0C */ u32 mApid;
    /* 0x10 */ fopAc_ac_c* mAc;
    /* 0x14 */ s8 mEffCounter;
    /* 0x15 */ u8 field_0x15[3];
    /* 0x18 vtable */

public:
    dCcD_GAtTgCoCommonBase() { ct(); }
    void ClrActorInfo() {
        mApid = fpcM_ERROR_PROCESS_ID_e;
        mAc = NULL;
    }
    void ct() {
        mSPrm = 0;
        mRPrm = 0;
        mHitCallback = NULL;
        mEffCounter = 0;
    }
    void SetHitApid(unsigned int);
    fopAc_ac_c* GetAc();
    void Set(dCcD_SrcGAtTgCoCommonBase const& base) {
        mSPrm = base.mSPrm;
        ClrEffCounter();
    }
    void SetEffCounterTimer();
    void SubtractEffCounter() {
        mEffCounter -= 1;
        if (mEffCounter < 0)
            mEffCounter = 0;
    }
    bool ChkEffCounter() { return mEffCounter >= 0; }
    virtual ~dCcD_GAtTgCoCommonBase() {}

    void ClrEffCounter() { mEffCounter = 0; }
    u32 GetSPrm() const { return mSPrm; }
    u32 GetRPrm() const { return mRPrm; }
    u32 MskSPrm(u32 mask) const { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) const { return mRPrm & mask; }
    bool ChkSPrm(u32 mask) const { return MskSPrm(mask); }
    void OnSPrm(u32 flag) { mSPrm |= flag; }
    void OnRPrm(u32 flag) { mRPrm |= flag; }
    void OffSPrm(u32 flag) { mSPrm &= ~flag; }
    void OffRPrm(u32 flag) { mRPrm &= ~flag; }
    bool ChkRPrm(u32 flag) const { return MskRPrm(flag); }
    void SetHitCallback(dCcD_HitCallback callback) { mHitCallback = callback; }
    dCcD_HitCallback GetHitCallback() { return mHitCallback; }
};  // Size = 0x1C

// Attack (At) Collider
class dCcD_GObjAt : public dCcD_GAtTgCoCommonBase {
public:
    void Set(dCcD_SrcGObjAt const&);
    dCcD_GObjAt() {}
    virtual ~dCcD_GObjAt() {}
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    cXyz* GetVecP() { return &mVec; }
    void SetHitMark(u8 mark) { mHitMark = mark; }
    void SetSe(u8 se) { mSe = se; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    void SetAtSpl(dCcG_At_Spl spl) { mSpl = spl; }
    u8 GetSe() { return mSe; }
    u8 GetSpl() { return mSpl; }
    u8 GetMtrl() { return mMtrl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }
    void ClrHit() { ClrActorInfo(); }

    // private:
    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mHitPos;
    /* 0x2C */ cXyz mVec;
    /* 0x38 */ cXyz mRVec;
};  // Size = 0x44

// Defense (Tg) Collider
class dCcD_GObjTg : public dCcD_GAtTgCoCommonBase {
public:
    void Set(dCcD_SrcGObjTg const&);
    virtual ~dCcD_GObjTg() {}
    void SetSe(u8 se) { mSe = se; }
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    void SetShieldFrontRangeYAngle(s16* angle) { mShieldFrontRangeYAngle = angle; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    u8 GetMtrl() { return mMtrl; }
    void SetHitMark(CcG_Tg_HitMark mark) { mHitMark = mark; }
    s16* GetShieldFrontRangeYAngle() { return mShieldFrontRangeYAngle; }
    u8 GetSpl() { return mSpl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    cXyz* GetVecP() { return &mVec; }
    cXyz* GetRVecP() { return &mRVec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }
    inline void ClrHit() { ClrActorInfo(); }

private:
    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mVec;
    /* 0x2C */ cXyz mRVec;
    /* 0x38 */ cXyz mHitPos;
    /* 0x44 */ s16* mShieldFrontRangeYAngle;
};  // Size = 0x48

// Correction (Co) Collider
class dCcD_GObjCo : public dCcD_GAtTgCoCommonBase {
public:
    virtual ~dCcD_GObjCo() {}
    void Set(dCcD_SrcGObjCo const& pSrc) { dCcD_GAtTgCoCommonBase::Set(pSrc.mBase); }
    void ClrHit() { ClrActorInfo(); }
};  // Size = 0x1C ?

// Object Info
class dCcD_GObjInf : public cCcD_GObjInf {
public:
    dCcD_GObjInf();
    virtual ~dCcD_GObjInf();
    virtual cCcD_GObjInf* GetGObjInf();
    virtual void ClrAtHit();
#if VERSION != VERSION_JPN
    u32 ChkAtHit();
#endif
    void ResetAtHit();
    cCcD_Obj* GetAtHitObj();
    cCcD_GObjInf* GetAtHitGObj();
    u8 ChkAtNoGuard();
    virtual void ClrTgHit();
#if VERSION != VERSION_JPN
    u32 ChkTgHit();
#endif
    void ResetTgHit();
    cCcD_Obj* GetTgHitObj();
    dCcD_GObjInf* GetTgHitGObj();
    u8 GetTgHitObjSe();
    virtual void ClrCoHit();
#if VERSION != VERSION_JPN
    u32 ChkCoHit();
#endif
    void ResetCoHit();
    cCcD_Obj* GetCoHitObj();
    void Set(dCcD_SrcGObjInf const&);

    fopAc_ac_c* GetCoHitAc() { return mGObjCo.GetAc(); }

    void SetAtVec(cXyz& vec) { mGObjAt.SetVec(vec); }
    void SetTgVec(cXyz& vec) { mGObjTg.SetVec(vec); }
    bool ChkAtNoMass() const { return mGObjAt.ChkSPrm(8); }
    void OnAtNoHitMark() { mGObjAt.OnSPrm(2); }
    void OffAtNoHitMark() { mGObjAt.OffSPrm(2); }
    void OnTgNoHitMark() { mGObjTg.OnSPrm(4); }
    void OffTgNoHitMark() { mGObjTg.OffSPrm(4); }
    void OnAtNoConHit() { mGObjAt.OnSPrm(1); }
    void OffAtNoConHit() { mGObjAt.OffSPrm(1); }
    void OnTgNoConHit() { mGObjTg.OnSPrm(2); }
    void SetAtHitMark(u8 mark) { mGObjAt.SetHitMark(mark); }
    void SetAtSe(u8 se) { mGObjAt.SetSe(se); }
    void SetTgSe(u8 se) { mGObjTg.SetSe(se); }
    void SetAtMtrl(u8 mtrl) { mGObjAt.SetMtrl(mtrl); }
    void SetTgMtrl(u8 mtrl) { mGObjTg.SetMtrl(mtrl); }
    fopAc_ac_c* GetAtHitAc() { return mGObjAt.GetAc(); }
    cXyz* GetAtVecP() { return mGObjAt.GetVecP(); }
    cXyz* GetTgVecP() { return mGObjTg.GetVecP(); }
    cXyz* GetTgRVecP() { return mGObjTg.GetRVecP(); }
    void SetAtSpl(dCcG_At_Spl spl) { mGObjAt.SetAtSpl(spl); }
    void SetAtHitCallback(dCcD_HitCallback callback) { mGObjAt.SetHitCallback(callback); }
    void SetTgHitCallback(dCcD_HitCallback callback) { mGObjTg.SetHitCallback(callback); }
    void SetCoHitCallback(dCcD_HitCallback callback) { mGObjCo.SetHitCallback(callback); }
    u8 GetAtSe() { return mGObjAt.GetSe(); }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mGObjAt.GetSpl(); }
    u8 GetAtMtrl() { return mGObjAt.GetMtrl(); }
    u8 GetTgMtrl() { return mGObjTg.GetMtrl(); }
    fopAc_ac_c* GetTgHitAc() { return mGObjTg.GetAc(); }
    void SetTgShieldFrontRangeYAngle(s16* angle) { mGObjTg.SetShieldFrontRangeYAngle(angle); }
    void SetTgHitMark(CcG_Tg_HitMark mark) { mGObjTg.SetHitMark(mark); }
    void OnTgShield() { mGObjTg.OnSPrm(0x1); }
    void OffTgShield() { mGObjTg.OffSPrm(0x1); }
    void OnTgShieldFrontRange() { mGObjTg.OnSPrm(0x8); }
    void OffTgShieldFrontRange() { mGObjTg.OffSPrm(0x8); }
    bool ChkTgIronBallRebound() { return mGObjTg.ChkSPrm(0x100); }
    s16* GetTgShieldFrontRangeYAngle() { return mGObjTg.GetShieldFrontRangeYAngle(); }
    bool ChkTgShield() { return mGObjTg.ChkSPrm(1); }
    bool ChkTgSpShield() { return mGObjTg.ChkSPrm(0x40); }
    bool ChkTgSmallShield() { return mGObjTg.ChkSPrm(0x10); }
    bool ChkTgShieldFrontRange() { return mGObjTg.ChkSPrm(8); }
    bool ChkAtNoConHit() { return mGObjAt.ChkSPrm(1); }
    bool ChkAtStopNoConHit() { return mGObjAt.ChkSPrm(0x4); }
    bool ChkTgNoConHit() { return mGObjTg.ChkSPrm(2); }
    bool ChkTgStopNoConHit() { return mGObjTg.ChkSPrm(0x2000); }
    bool ChkCoAtLasso() { return mGObjCo.ChkSPrm(1); }
    bool ChkCoTgLasso() { return mGObjCo.ChkSPrm(2); }
    dCcD_HitCallback GetCoHitCallback() { return mGObjCo.GetHitCallback(); }
    dCcD_HitCallback GetAtHitCallback() { return mGObjAt.GetHitCallback(); }
    dCcD_HitCallback GetTgHitCallback() { return mGObjTg.GetHitCallback(); }
    void SetCoHitApid(unsigned int apid) { mGObjCo.SetHitApid(apid); }
    void SetAtHitApid(unsigned int apid) { mGObjAt.SetHitApid(apid); }
    void SetTgHitApid(unsigned int apid) { mGObjTg.SetHitApid(apid); }
    void OnCoHitNoActor() { mGObjCo.OnRPrm(1); }
    void OffCoHitNoActor() { mGObjCo.OffRPrm(1); }
    void OnAtHitNoActor() { mGObjAt.OnRPrm(2); }
    void OffAtHitNoActor() { mGObjAt.OffRPrm(2); }
    void OnTgHitNoActor() { mGObjTg.OnRPrm(1); }
    void OffTgHitNoActor() { mGObjTg.OffRPrm(1); }
    bool ChkCoHitNoActor() const { return mGObjCo.ChkRPrm(1); }
    bool ChkAtHitNoActor() const { return mGObjAt.ChkRPrm(2); }
    bool ChkTgHitNoActor() const { return mGObjTg.ChkRPrm(1); }
    bool ChkAtNoHitMark() { return mGObjAt.ChkSPrm(2); }
    bool ChkTgNoHitMark() { return mGObjTg.ChkSPrm(4); }
    bool ChkTgHookShotNoHitMark() { return mGObjTg.ChkSPrm(0x400); }
    bool ChkTgArrowNoHitMark() { return mGObjTg.ChkSPrm(0x1000); }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mGObjTg.GetSpl(); }
    int GetTgHitMark() { return mGObjTg.GetHitMark(); }
    int GetAtHitMark() { return mGObjAt.GetHitMark(); }
    bool ChkAtEffCounter() { return mGObjAt.ChkEffCounter(); }
    bool ChkTgEffCounter() { return mGObjTg.ChkEffCounter(); }
    void ClrAtEffCounter() { mGObjAt.ClrEffCounter(); }
    void ClrTgEffCounter() { mGObjTg.ClrEffCounter(); }
    void ClrCoEffCounter() { mGObjCo.ClrEffCounter(); }
    void SetAtEffCounterTimer() { mGObjAt.SetEffCounterTimer(); }
    void SetTgEffCounterTimer() { mGObjTg.SetEffCounterTimer(); }
    void SubtractAtEffCounter() { mGObjAt.SubtractEffCounter(); }
    void SubtractTgEffCounter() { mGObjTg.SubtractEffCounter(); }
    void SubtractCoEffCounter() { mGObjCo.SubtractEffCounter(); }
    void OnTgShieldHit() { mGObjTg.OnRPrm(2); }
    void OffTgShieldHit() { mGObjTg.OffRPrm(2); }
    bool ChkTgShieldHit() { return mGObjTg.ChkRPrm(2); }
    void OnAtShieldHit() { mGObjAt.OnRPrm(1); }
    void OffAtShieldHit() { mGObjAt.OffRPrm(1); }
    bool ChkAtShieldHit() { return mGObjAt.ChkRPrm(1); }
    void SetTgRVec(cXyz& vec) { mGObjTg.SetRVec(vec); }
    void SetAtRVec(cXyz& vec) { mGObjAt.SetRVec(vec); }
    void SetTgHitPos(cXyz& pos) { mGObjTg.SetHitPos(pos); }
    void SetAtHitPos(cXyz& pos) { mGObjAt.SetHitPos(pos); }
    cXyz* GetAtHitPosP() { return mGObjAt.GetHitPosP(); }
    cXyz* GetTgHitPosP() { return mGObjTg.GetHitPosP(); }

protected:
    /* 0x050 */ dCcD_GObjAt mGObjAt;
    /* 0x094 */ dCcD_GObjTg mGObjTg;
    /* 0x0DC */ dCcD_GObjCo mGObjCo;
};  // Size = 0xF8

STATIC_ASSERT(sizeof(dCcD_GObjInf) == 0xF8);

// Cylinder
class dCcD_Cyl : public dCcD_GObjInf, public cCcD_CylAttr {
public:
    void Set(dCcD_SrcCyl const&);
    cCcD_ShapeAttr* GetShapeAttr() { return this; }
    void StartCAt(cXyz&);
    void StartCTg(cXyz&);
    void MoveCAtTg(cXyz&);
    void MoveCAt(cXyz&);
    void MoveCTg(cXyz&);
    virtual ~dCcD_Cyl() {}
    dCcD_Cyl() {}
};  // Size = 0x130

// Sphere
class dCcD_Sph : public dCcD_GObjInf, public cCcD_SphAttr {
public:
    dCcD_Sph() {}
    void Set(dCcD_SrcSph const&);
    void StartCAt(cXyz&);
    void MoveCAt(cXyz&);
    virtual cCcD_ShapeAttr* GetShapeAttr() { return (cCcD_ShapeAttr*)this; }
    virtual ~dCcD_Sph() {}
};  // Size = 0x12C

// Capsule
class dCcD_Cps : public dCcD_GObjInf, public cCcD_CpsAttr {
public:
    void Set(dCcD_SrcCps const&);
    cCcD_ShapeAttr* GetShapeAttr() { return (cCcD_ShapeAttr*)this; }
    void CalcAtVec() {
        cXyz* atVecP = GetAtVecP();
        CalcVec(atVecP);
    }
    void CalcTgVec();
    virtual ~dCcD_Cps() {}
    dCcD_Cps() {}
};  // Size = 0x138

// Triangle
class dCcD_Tri : public dCcD_GObjInf, public cCcD_TriAttr {
public:
    void Set(dCcD_SrcTri const&);
    cCcD_ShapeAttr* GetShapeAttr();
    virtual ~dCcD_Tri() {}
    dCcD_Tri() {}
};

dCcD_GObjInf* dCcD_GetGObjInf(cCcD_Obj* param_0);

#endif /* D_CC_D_CC_D_H */