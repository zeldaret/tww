#ifndef C_CC_S_H
#define C_CC_S_H

#include "SSystem/SComponent/c_cc_d.h"
#include "global.h"

enum WeightType {
    WeightType_0 = 0,
    WeightType_1 = 1,
    WeightType_2 = 2,
};

class cCcS {
public:
    /* 0x0000 */ cCcD_Obj* mpObjAt[0x100];
    /* 0x0400 */ cCcD_Obj* mpObjTg[0x300];
    /* 0x1000 */ cCcD_Obj* mpObjCo[0x100];
    /* 0x1400 */ cCcD_Obj* mpObj[0x500];
    /* 0x2800 */ int mObjAtCount;
    /* 0x2804 */ int mObjTgCount;
    /* 0x2808 */ int mObjCoCount;
    /* 0x280C */ int mObjCount;
    /* 0x2810 */ cCcD_DivideArea mDivideArea;
    /* 0x2850 vtable */

    cCcS();
    void Ct();
    void Dt();
    WeightType GetWt(u8 weight) const {
        if (weight == 0xFF) {
            return WeightType_0;
        }
        if (weight == 0xFE) {
            return WeightType_1;
        }
        return WeightType_2;
    }
    void Set(cCcD_Obj*);
    void ClrCoHitInf();
    void ClrTgHitInf();
    void ClrAtHitInf();
    bool ChkNoHitAtTg(cCcD_Obj*, cCcD_Obj*);
    void ChkAtTg();
    bool ChkNoHitCo(cCcD_Obj*, cCcD_Obj*);
    void ChkCo();
    virtual void CalcTgPlusDmg(cCcD_Obj*, cCcD_Obj*, cCcD_Stts*, cCcD_Stts*);
    void SetAtTgCommonHitInf(cCcD_Obj*, cCcD_Obj*, cXyz*);
    void SetCoCommonHitInf(cCcD_Obj*, cXyz*, cCcD_Obj*, cXyz*, f32);
    virtual void SetPosCorrect(cCcD_Obj*, cXyz*, cCcD_Obj*, cXyz*, f32);
    void CalcArea();
    void Move();
    void DrawClear();
    virtual void SetCoGObjInf(bool, bool, cCcD_GObjInf*, cCcD_GObjInf*, cCcD_Stts*, cCcD_Stts*,
                              cCcD_GStts*, cCcD_GStts*) {}
    virtual void SetAtTgGObjInf(bool, bool, cCcD_Obj*, cCcD_Obj*, cCcD_GObjInf*, cCcD_GObjInf*,
                                cCcD_Stts*, cCcD_Stts*, cCcD_GStts*, cCcD_GStts*, cXyz*) {}
    virtual bool ChkNoHitGAtTg(cCcD_GObjInf const*, cCcD_GObjInf const*, cCcD_GStts*, cCcD_GStts*) { return false; }
    virtual bool ChkAtTgHitAfterCross(bool, bool, cCcD_GObjInf const*, cCcD_GObjInf const*,
                                      cCcD_Stts*, cCcD_Stts*, cCcD_GStts*, cCcD_GStts*) { return false; }
    virtual bool ChkNoHitGCo(cCcD_Obj*, cCcD_Obj*) { return false; }
    virtual ~cCcS() {}
    virtual void MoveAfterCheck() {}
    virtual void SetCoGCorrectProc(cCcD_Obj*, cCcD_Obj*);
};  // Size = 0x2850

STATIC_ASSERT(sizeof(cCcS) == 0x2854);

#endif /* C_CC_S_H */
