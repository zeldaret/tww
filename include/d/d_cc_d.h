#ifndef D_CC_D_CC_D_H
#define D_CC_D_CC_D_H

/**
 * d_cc_d.h
 * Actor Collision
 */

#include "SSystem/SComponent/c_cc_d.h"
#include "f_pc/f_pc_manager.h"
#include "d/d_particle_name.h"

enum dCcD_ObjAtType {
    /* 0x00000002 */ AT_TYPE_SWORD          = (1 << 1),
    /* 0x00000008 */ AT_TYPE_UNK8           = (1 << 3),
    /* 0x00000020 */ AT_TYPE_BOMB           = (1 << 5),
    /* 0x00000040 */ AT_TYPE_BOOMERANG      = (1 << 6),
    /* 0x00000080 */ AT_TYPE_BOKO_STICK     = (1 << 7),
    /* 0x00000100 */ AT_TYPE_WATER          = (1 << 8),
    /* 0x00000200 */ AT_TYPE_FIRE           = (1 << 9),
    /* 0x00000400 */ AT_TYPE_MACHETE        = (1 << 10),
    /* 0x00000800 */ AT_TYPE_UNK800         = (1 << 11),
    /* 0x00001000 */ AT_TYPE_SPIKE          = (1 << 12),
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

enum dCcG_AtSPrm_e {
    dCcG_AtSPrm_NoConHit_e         = 1 << 0,
    dCcG_AtSPrm_NoHitMark_e        = 1 << 1,
    dCcG_AtSPrm_StopNoConHit_e     = 1 << 2,
    dCcG_AtSPrm_NoMass_e           = 1 << 3,
};

enum dCcG_AtRPrm_e {
    dCcG_AtRPrm_ShieldHit_e        = 1 << 0,
    dCcG_AtRPrm_HitNoActor_e       = 1 << 1,
};

enum dCcG_TgSPrm_e {
    dCcG_TgSPrm_Shield_e           = 1 << 0,
    dCcG_TgSPrm_NoConHit_e         = 1 << 1,
    dCcG_TgSPrm_NoHitMark_e        = 1 << 2,
    dCcG_TgSPrm_ShieldFrontRange_e = 1 << 3,
};

enum dCcG_TgRPrm_e {
    dCcG_TgRPrm_HitNoActor_e       = 1 << 0,
    dCcG_TgRPrm_ShieldHit_e        = 1 << 1,
};

enum dCcG_CoSPrm_e {
    dCcG_CoSPrm_AtLasso_e          = 1 << 0,
    dCcG_CoSPrm_TgLasso_e          = 1 << 1,
};

enum dCcG_CoRPrm_e {
    dCcG_CoRPrm_HitNoActor_e       = 1 << 0,
};

enum dCcG_hitSe {
    /* 0x01 */ dCcG_SE_UNK1 = 1,
    /* 0x02 */ dCcG_SE_UNK2 = 2,
    /* 0x04 */ dCcG_SE_UNK4 = 4,
    /* 0x05 */ dCcG_SE_UNK5 = 5,
    /* 0x06 */ dCcG_SE_UNK6 = 6,
    /* 0x07 */ dCcG_SE_ARROW = 7,
    /* 0x08 */ dCcG_SE_HOOKSHOT = 8,
    /* 0x23 */ dCcG_SE_UNK23 = 0x23,
    /* 0x25 */ dCcG_SE_UNK25 = 0x25,
};

enum CcG_At_HitMark {
    /* 0x0 */ dCcG_AtHitMark_None_e = dPa_name::ID_NONE,
    /* 0x1 */ dCcG_AtHitMark_Unk1_e = dPa_name::ID_COMMON_0001,
    /* 0xD */ dCcG_AtHitMark_Nrm_e = dPa_name::ID_COMMON_NORMAL_HIT,
    /* 0xF */ dCcG_AtHitMark_Big_e = dPa_name::ID_COMMON_BIG_HIT,
};

enum CcG_Tg_HitMark {
    /* 0x1 */ dCcG_TgHitMark_Unk1_e = dPa_name::ID_COMMON_0001,
    /* 0xC */ dCcg_TgHitMark_Purple_e = dPa_name::ID_COMMON_PURPLE_HIT,
    /* 0xD */ dCcG_TgHitMark_Nrm_e = dPa_name::ID_COMMON_NORMAL_HIT,
};

enum dCcG_At_Spl {
    /* 0x0 */ dCcG_At_Spl_UNK0 = 0,
    /* 0x1 */ dCcG_At_Spl_UNK1 = 1,
    /* 0x3 */ dCcG_At_Spl_UNK3 = 3,
    /* 0x5 */ dCcG_At_Spl_UNK5 = 5,
    /* 0x6 */ dCcG_At_Spl_UNK6 = 6,
    /* 0x7 */ dCcG_At_Spl_UNK7 = 7,
    /* 0x8 */ dCcG_At_Spl_UNK8 = 8,
    /* 0x9 */ dCcG_At_Spl_UNK9 = 9,
    /* 0xA */ dCcG_At_Spl_UNKA = 0xA,
    /* 0xB */ dCcG_At_Spl_UNKB = 0xB,
};

enum dCcG_Tg_Spl {
    /* 0x0 */ dCcG_Tg_Spl_UNK0 = 0,
    /* 0x1 */ dCcG_Tg_Spl_UNK1 = 1,
};

struct dCcD_SrcGAtTgCoCommonBase {
    /* 0x0 */ u32 mSPrm;
};  // Size: 0x4

struct dCcD_SrcGObjAt {
    /* 0x0 */ u8 mSe;       // Sound Effect ID
    /* 0x1 */ u8 mHitMark;  // Hit Mark particle ID
    /* 0x2 */ u8 mSpl;
    /* 0x3 */ u8 mMtrl;     // Seems to be unused and always 0 in TWW
    /* 0x4 */ dCcD_SrcGAtTgCoCommonBase mBase;
};  // Size: 0x8

struct dCcD_SrcGObjTg {
    /* 0x0 */ u8 mSe;       // Sound Effect ID
    /* 0x1 */ u8 mHitMark;  // Hit Mark particle ID
    /* 0x2 */ u8 mSpl;
    /* 0x3 */ u8 mMtrl;     // Seems to be unused and always 0 in TWW
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
    enum {
        Stts_NoActor_e = 1 << 0,
    };

    dCcD_GStts();
    virtual ~dCcD_GStts() {}

    void Ct();
    void Move();
    void ClrAt() { mAtSpl = dCcG_At_Spl_UNK0; }
    void ClrTg() { mTgSpl = dCcG_Tg_Spl_UNK0; }
    void SetAtApid(fpc_ProcID id) { mAtApid = id; }
    void SetTgApid(fpc_ProcID id) { mTgApid = id; }
    u8 GetRoomId() { return mRoomId; }
    void SetRoomId(int id) { mRoomId = id; }
    fpc_ProcID GetAtOldApid() { return mAtOldApid; }
    fpc_ProcID GetTgOldApid() { return mTgOldApid; }
    bool ChkNoActor() { return mFlag & 1; }
    bool ChkNoneActorPerfTblId() { return mActorPerfTblId == 0xFFFF; }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mAtSpl; }
    void SetAtSpl(dCcG_At_Spl spl) { mAtSpl = spl; }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mTgSpl; }
    void SetTgSpl(dCcG_Tg_Spl spl) { mTgSpl = spl; }
    void OnNoActor() { mFlag |= Stts_NoActor_e; }

    // private:
    /* 0x04 */ u8 mAtSpl;
    /* 0x05 */ u8 mTgSpl;
    /* 0x06 */ u8 mRoomId;
    /* 0x08 */ u16 mActorPerfTblId;
    /* 0x0C */ fpc_ProcID mAtApid;
    /* 0x10 */ fpc_ProcID mAtOldApid;
    /* 0x14 */ fpc_ProcID mTgApid;
    /* 0x18 */ fpc_ProcID mTgOldApid;
    /* 0x1C */ u32 mFlag;
};  // Size = 0x20

STATIC_ASSERT(sizeof(dCcD_GStts) == 0x20);

class dCcD_Stts : public cCcD_Stts, public dCcD_GStts {
public:
    dCcD_Stts() {}
    virtual cCcD_GStts* GetGStts() {
        return (cCcD_GStts*)this;
    }
    void Init(int weight, int, fopAc_ac_c* pActor);
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

    /* 0x00 */ /* cCcD_Stts */
    /* 0x18 */ /* vtable */
    /* 0x1C */ /* dCcD_GStts */
};  // Size = 0x3C

STATIC_ASSERT(sizeof(dCcD_Stts) == 0x3C);

class dCcD_GObjInf;
typedef void (*dCcD_HitCallback)(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);

// Attack/Defense/Correction Collider Common Base
class dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ dCcD_HitCallback mHitCallback;
    /* 0x0C */ fpc_ProcID mApid;
    /* 0x10 */ fopAc_ac_c* mAc;
    /* 0x14 */ s8 mEffCounter;
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
    void SetHitApid(fpc_ProcID id) {
        mApid = id;
        mAc = NULL;
    }
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
    bool ChkEffCounter() { return mEffCounter > 0; }
    virtual ~dCcD_GAtTgCoCommonBase() {}

    void ClrEffCounter() { mEffCounter = 0; }
    u32 GetSPrm() { return mSPrm; }
    u32 GetRPrm() { return mRPrm; }
    u32 MskSPrm(u32 mask) { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) { return mRPrm & mask; }
    bool ChkSPrm(u32 mask) { return MskSPrm(mask); }
    bool ChkRPrm(u32 flag) { return MskRPrm(flag); }
    void OnSPrm(u32 flag) { mSPrm |= flag; }
    void OnRPrm(u32 flag) { mRPrm |= flag; }
    void OffSPrm(u32 flag) { mSPrm &= ~flag; }
    void OffRPrm(u32 flag) { mRPrm &= ~flag; }
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
    void SetSpl(dCcG_At_Spl spl) { mSpl = spl; }
    u8 GetSe() { return mSe; }
    u8 GetSpl() { return mSpl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }
    void ClrHit() { ClrActorInfo(); }

    // private:
    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl; // Seems to be unused and always 0 in TWW
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
    void SetShieldFrontRangeYAngle(s16* angle) { mpShieldFrontRangeYAngle = angle; }
    void SetHitMark(CcG_Tg_HitMark mark) { mHitMark = mark; }
    s16* GetShieldFrontRangeYAngle() { return mpShieldFrontRangeYAngle; }
    u8 GetSpl() { return mSpl; }
    void SetSpl(dCcG_Tg_Spl spl) { mSpl = spl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    cXyz* GetVecP() { return &mVec; }
    cXyz* GetRVecP() { return &mRVec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }
    inline void ClrHit() { ClrActorInfo(); }

private:
    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl; // Seems to be unused and always 0 in TWW
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mVec;
    /* 0x2C */ cXyz mRVec;
    /* 0x38 */ cXyz mHitPos;
    /* 0x44 */ s16* mpShieldFrontRangeYAngle;
};  // Size = 0x48

// Correction (Co) Collider
class dCcD_GObjCo : public dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ /* dCcD_GAtTgCoCommonBase */
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
#if VERSION > VERSION_JPN
    u32 ChkAtHit();
#endif
    void ResetAtHit();
    cCcD_Obj* GetAtHitObj();
    cCcD_GObjInf* GetAtHitGObj();
    u8 ChkAtNoGuard();
    virtual void ClrTgHit();
#if VERSION > VERSION_JPN
    u32 ChkTgHit();
#endif
    void ResetTgHit();
    cCcD_Obj* GetTgHitObj();
    dCcD_GObjInf* GetTgHitGObj();
    u8 GetTgHitObjSe();
    virtual void ClrCoHit();
#if VERSION > VERSION_JPN
    u32 ChkCoHit();
#endif
    void ResetCoHit();
    cCcD_Obj* GetCoHitObj();
    void Set(dCcD_SrcGObjInf const&);

    fopAc_ac_c* GetCoHitAc() { return mGObjCo.GetAc(); }

    void SetAtVec(cXyz& vec) { mGObjAt.SetVec(vec); }
    void SetTgVec(cXyz& vec) { mGObjTg.SetVec(vec); }
    bool ChkAtNoMass() { return mGObjAt.ChkSPrm(dCcG_AtSPrm_NoMass_e); }
    bool ChkAtNoHitMark() { return mGObjAt.ChkSPrm(dCcG_AtSPrm_NoHitMark_e); }
    void OnAtNoHitMark() { mGObjAt.OnSPrm(dCcG_AtSPrm_NoHitMark_e); }
    void OffAtNoHitMark() { mGObjAt.OffSPrm(dCcG_AtSPrm_NoHitMark_e); }
    bool ChkTgNoHitMark() { return mGObjTg.ChkSPrm(dCcG_TgSPrm_NoHitMark_e); }
    void OnTgNoHitMark() { mGObjTg.OnSPrm(dCcG_TgSPrm_NoHitMark_e); }
    void OffTgNoHitMark() { mGObjTg.OffSPrm(dCcG_TgSPrm_NoHitMark_e); }
    bool ChkAtNoConHit() { return mGObjAt.ChkSPrm(dCcG_AtSPrm_NoConHit_e); }
    void OnAtNoConHit() { mGObjAt.OnSPrm(dCcG_AtSPrm_NoConHit_e); }
    void OffAtNoConHit() { mGObjAt.OffSPrm(dCcG_AtSPrm_NoConHit_e); }
    bool ChkTgNoConHit() { return mGObjTg.ChkSPrm(dCcG_TgSPrm_NoConHit_e); }
    void OnTgNoConHit() { mGObjTg.OnSPrm(dCcG_TgSPrm_NoConHit_e); }
    int GetAtHitMark() { return mGObjAt.GetHitMark(); }
    int GetTgHitMark() { return mGObjTg.GetHitMark(); }
    void SetAtHitMark(u8 mark) { mGObjAt.SetHitMark(mark); }
    void SetTgHitMark(CcG_Tg_HitMark mark) { mGObjTg.SetHitMark(mark); }
    void SetAtSe(u8 se) { mGObjAt.SetSe(se); }
    void SetTgSe(u8 se) { mGObjTg.SetSe(se); }
    fopAc_ac_c* GetAtHitAc() { return mGObjAt.GetAc(); }
    cXyz* GetAtVecP() { return mGObjAt.GetVecP(); }
    cXyz* GetTgVecP() { return mGObjTg.GetVecP(); }
    cXyz* GetTgRVecP() { return mGObjTg.GetRVecP(); }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mGObjAt.GetSpl(); }
    void SetAtSpl(dCcG_At_Spl spl) { mGObjAt.SetSpl(spl); }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mGObjTg.GetSpl(); }
    void SetTgSpl(dCcG_Tg_Spl spl) { mGObjTg.SetSpl(spl); }
    void SetAtHitCallback(dCcD_HitCallback callback) { mGObjAt.SetHitCallback(callback); }
    void SetTgHitCallback(dCcD_HitCallback callback) { mGObjTg.SetHitCallback(callback); }
    void SetCoHitCallback(dCcD_HitCallback callback) { mGObjCo.SetHitCallback(callback); }
    u8 GetAtSe() { return mGObjAt.GetSe(); }
    bool ChkAtStopNoConHit() { return mGObjAt.ChkSPrm(dCcG_AtSPrm_StopNoConHit_e); }
    fopAc_ac_c* GetTgHitAc() { return mGObjTg.GetAc(); }
    void SetTgShieldFrontRangeYAngle(s16* angle) { mGObjTg.SetShieldFrontRangeYAngle(angle); }
    bool ChkTgShield() { return mGObjTg.ChkSPrm(dCcG_TgSPrm_Shield_e); }
    void OnTgShield() { mGObjTg.OnSPrm(dCcG_TgSPrm_Shield_e); }
    void OffTgShield() { mGObjTg.OffSPrm(dCcG_TgSPrm_Shield_e); }
    bool ChkTgShieldFrontRange() { return mGObjTg.ChkSPrm(dCcG_TgSPrm_ShieldFrontRange_e); }
    void OnTgShieldFrontRange() { mGObjTg.OnSPrm(dCcG_TgSPrm_ShieldFrontRange_e); }
    void OffTgShieldFrontRange() { mGObjTg.OffSPrm(dCcG_TgSPrm_ShieldFrontRange_e); }
    s16* GetTgShieldFrontRangeYAngle() { return mGObjTg.GetShieldFrontRangeYAngle(); }
    bool ChkCoAtLasso() { return mGObjCo.ChkSPrm(dCcG_CoSPrm_AtLasso_e); }
    bool ChkCoTgLasso() { return mGObjCo.ChkSPrm(dCcG_CoSPrm_TgLasso_e); }
    dCcD_HitCallback GetCoHitCallback() { return mGObjCo.GetHitCallback(); }
    dCcD_HitCallback GetAtHitCallback() { return mGObjAt.GetHitCallback(); }
    dCcD_HitCallback GetTgHitCallback() { return mGObjTg.GetHitCallback(); }
    void SetCoHitApid(fpc_ProcID apid) { mGObjCo.SetHitApid(apid); }
    void SetAtHitApid(fpc_ProcID apid) { mGObjAt.SetHitApid(apid); }
    void SetTgHitApid(fpc_ProcID apid) { mGObjTg.SetHitApid(apid); }
    bool ChkAtHitNoActor() { return mGObjAt.ChkRPrm(dCcG_AtRPrm_HitNoActor_e); }
    void OnAtHitNoActor() { mGObjAt.OnRPrm(dCcG_AtRPrm_HitNoActor_e); }
    void OffAtHitNoActor() { mGObjAt.OffRPrm(dCcG_AtRPrm_HitNoActor_e); }
    bool ChkTgHitNoActor() { return mGObjTg.ChkRPrm(dCcG_TgRPrm_HitNoActor_e); }
    void OnTgHitNoActor() { mGObjTg.OnRPrm(dCcG_TgRPrm_HitNoActor_e); }
    void OffTgHitNoActor() { mGObjTg.OffRPrm(dCcG_TgRPrm_HitNoActor_e); }
    bool ChkCoHitNoActor() { return mGObjCo.ChkRPrm(dCcG_CoRPrm_HitNoActor_e); }
    void OnCoHitNoActor() { mGObjCo.OnRPrm(dCcG_CoRPrm_HitNoActor_e); }
    void OffCoHitNoActor() { mGObjCo.OffRPrm(dCcG_CoRPrm_HitNoActor_e); }
    bool ChkTgShieldHit() { return mGObjTg.ChkRPrm(dCcG_TgRPrm_ShieldHit_e); }
    void OnTgShieldHit() { mGObjTg.OnRPrm(dCcG_TgRPrm_ShieldHit_e); }
    void OffTgShieldHit() { mGObjTg.OffRPrm(dCcG_TgRPrm_ShieldHit_e); }
    bool ChkAtShieldHit() { return mGObjAt.ChkRPrm(dCcG_AtRPrm_ShieldHit_e); }
    void OnAtShieldHit() { mGObjAt.OnRPrm(dCcG_AtRPrm_ShieldHit_e); }
    void OffAtShieldHit() { mGObjAt.OffRPrm(dCcG_AtRPrm_ShieldHit_e); }

    bool ChkAtEffCounter() { return mGObjAt.ChkEffCounter(); }
    void ClrAtEffCounter() { mGObjAt.ClrEffCounter(); }
    void SetAtEffCounterTimer() { mGObjAt.SetEffCounterTimer(); }
    void SubtractAtEffCounter() { mGObjAt.SubtractEffCounter(); }
    bool ChkTgEffCounter() { return mGObjTg.ChkEffCounter(); }
    void ClrTgEffCounter() { mGObjTg.ClrEffCounter(); }
    void SetTgEffCounterTimer() { mGObjTg.SetEffCounterTimer(); }
    void SubtractTgEffCounter() { mGObjTg.SubtractEffCounter(); }
    void ClrCoEffCounter() { mGObjCo.ClrEffCounter(); }
    void SubtractCoEffCounter() { mGObjCo.SubtractEffCounter(); }
    void SetTgRVec(cXyz& vec) { mGObjTg.SetRVec(vec); }
    void SetAtRVec(cXyz& vec) { mGObjAt.SetRVec(vec); }
    void SetTgHitPos(cXyz& pos) { mGObjTg.SetHitPos(pos); }
    void SetAtHitPos(cXyz& pos) { mGObjAt.SetHitPos(pos); }
    cXyz* GetAtHitPosP() { return mGObjAt.GetHitPosP(); }
    cXyz* GetTgHitPosP() { return mGObjTg.GetHitPosP(); }

protected:
    /* 0x000 */ /* cCcD_GObjInf */
    /* 0x050 */ dCcD_GObjAt mGObjAt;
    /* 0x094 */ dCcD_GObjTg mGObjTg;
    /* 0x0DC */ dCcD_GObjCo mGObjCo;
};  // Size = 0xF8

STATIC_ASSERT(sizeof(dCcD_GObjInf) == 0xF8);

// Cylinder
class dCcD_Cyl : public dCcD_GObjInf, public cCcD_CylAttr {
public:
    /* 0x00 */ /* dCcD_GObjInf */
    /* 0xF8 */ /* cCcD_CylAttr */

    void Set(dCcD_SrcCyl const&);
    virtual cCcD_ShapeAttr* GetShapeAttr() { return this; }
    void StartCAt(cXyz&);
    void StartCTg(cXyz&);
    void MoveCAtTg(cXyz&);
    void MoveCAt(cXyz&);
    void MoveCTg(cXyz&);
    virtual ~dCcD_Cyl() {}
    dCcD_Cyl() {}
};  // Size = 0x130

STATIC_ASSERT(sizeof(dCcD_Cyl) == 0x130);

// Sphere
class dCcD_Sph : public dCcD_GObjInf, public cCcD_SphAttr {
public:
    /* 0x000 */ /* dCcD_GObjInf */
    /* 0x0F8 */ /* cCcD_SphAttr */

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
    /* 0x00 */ /* dCcD_GObjInf */
    /* 0xF8 */ /* cCcD_CpsAttr */

    void Set(dCcD_SrcCps const&);
    virtual cCcD_ShapeAttr* GetShapeAttr() { return (cCcD_ShapeAttr*)this; }
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
    /* 0x00 */ /* dCcD_GObjInf */
    /* 0xF8 */ /* cCcD_TriAttr */

    void Set(dCcD_SrcTri const&);
    virtual cCcD_ShapeAttr* GetShapeAttr() { return this; }
    virtual ~dCcD_Tri() {}
    dCcD_Tri() {}
};  // Size: 0x150

dCcD_GObjInf* dCcD_GetGObjInf(cCcD_Obj* param_0);

#endif /* D_CC_D_CC_D_H */
