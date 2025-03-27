#ifndef D_CC_D_CC_S_H
#define D_CC_D_CC_S_H

#include "SSystem/SComponent/c_cc_s.h"
#include "d/d_cc_mass_s.h"
#include "global.h"

class dCcD_GObjInf;
class dCcD_GStts;

class dCcS : public cCcS {
public:
    dCcS() {}
    void Ct();
    void Dt();
    bool ChkShieldFrontRange(cCcD_Obj*, cCcD_Obj*);
    bool ChkShield(cCcD_Obj*, cCcD_Obj*, dCcD_GObjInf*, dCcD_GObjInf*);
    void CalcTgPlusDmg(cCcD_Obj*, cCcD_Obj*, cCcD_Stts*, cCcD_Stts*);
    int GetRank(u8);
    void ProcAtTgHitmark(bool, bool, cCcD_Obj*, cCcD_Obj*, dCcD_GObjInf*,
                                        dCcD_GObjInf*, cCcD_Stts*, cCcD_Stts*, dCcD_GStts*,
                                        dCcD_GStts*, cXyz*);
    bool ChkCamera(cXyz&, cXyz&, f32, fopAc_ac_c*, fopAc_ac_c*);
    void DrawAfter();
    void Move();
    void Draw();
    void MassClear();

    virtual void SetPosCorrect(cCcD_Obj*, cXyz*, cCcD_Obj*, cXyz*, f32);
    virtual void SetCoGObjInf(bool, bool, cCcD_GObjInf*, cCcD_GObjInf*, cCcD_Stts*,
                                             cCcD_Stts*, cCcD_GStts*, cCcD_GStts*);
    virtual void SetAtTgGObjInf(bool, bool, cCcD_Obj*, cCcD_Obj*, cCcD_GObjInf*,
                                               cCcD_GObjInf*, cCcD_Stts*, cCcD_Stts*, cCcD_GStts*,
                                               cCcD_GStts*, cXyz*);
    virtual bool ChkAtTgHitAfterCross(bool, bool, cCcD_GObjInf const*,
                                                     cCcD_GObjInf const*, cCcD_Stts*, cCcD_Stts*,
                                                     cCcD_GStts*, cCcD_GStts*);
    virtual bool ChkNoHitGCo(cCcD_Obj*, cCcD_Obj*);
    virtual ~dCcS() {}
    virtual void MoveAfterCheck();
    virtual void CalcParticleAngle(dCcD_GObjInf*, cCcD_Stts*, cCcD_Stts*, csXyz*);

    u32 ChkMass(cXyz* p_xyz, fopAc_ac_c** p_actor, dCcMassS_HitInf* p_hitInf) {
        return mMass_Mng.Chk(p_xyz, p_actor, p_hitInf);
    }
    void SetMass(cCcD_Obj* i_obj, u8 i_priority) { mMass_Mng.Set(i_obj, i_priority); }
    void PrepareMass() { mMass_Mng.Prepare(); }
    void SetMassAttr(f32 radius, f32 height, u8 param_2, u8 param_3) {
        mMass_Mng.SetAttr(radius, height, param_2, param_3);
    }

    void ChkActor(fopAc_ac_c*) {}
    void GetMassCamTopPos(Vec*) {}
    void GetMassResultCam() {}
    void OffMassAllTimer() {}
    void OnMassAllTimer() {}
    void SetMassAreaChk(cCcD_Obj*, u8, void (*)(fopAc_ac_c*, cXyz*, u32)) {}
    void SetMassCam(cM3dGCps&) {}

    // /* 0x0000 */ cCcS mCCcS;
    /* 0x2854 */ dCcMassS_Mng mMass_Mng;
};  // Size = 0x29F4

STATIC_ASSERT(sizeof(dCcS) == 0x29F4);

#endif /* D_CC_D_CC_S_H */
