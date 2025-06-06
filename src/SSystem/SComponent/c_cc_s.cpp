//
// Generated by dtk
// Translation Unit: c_cc_s.cpp
//

#include "SSystem/SComponent/c_cc_s.h"
#include "JSystem/JUtility/JUTAssert.h"

#if VERSION == VERSION_DEMO
#pragma nosyminline on
#endif

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(fpclassify(x) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)
#define CHECK_PVEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v->x && v->x < 1.0e32f && -1.0e32f < v->y && v->y < 1.0e32f && -1.0e32f < v->z && v->z < 1.0e32f)

/* 80242C28-80242C50       .text __ct__4cCcSFv */
cCcS::cCcS() {
}

/* 80242C50-80242CE4       .text Ct__4cCcSFv */
void cCcS::Ct() {
    for (u32 i = 0; i < ARRAY_SIZE(mpObjAt); i++)
        mpObjAt[i] = NULL;
    for (u32 i = 0; i < ARRAY_SIZE(mpObjTg); i++)
        mpObjTg[i] = NULL;
    for (u32 i = 0; i < ARRAY_SIZE(mpObjCo); i++)
        mpObjCo[i] = NULL;
    for (u32 i = 0; i < ARRAY_SIZE(mpObj); i++)
        mpObj[i] = NULL;
    mObjAtCount = 0;
    mObjTgCount = 0;
    mObjCoCount = 0;
    mObjCount = 0;
}

/* 80242CE4-80242D04       .text Dt__4cCcSFv */
void cCcS::Dt() {
    Ct();
}

/* 80242D04-80242DB8       .text Set__4cCcSFP8cCcD_Obj */
void cCcS::Set(cCcD_Obj* obj) {
    if (obj->ChkAtSet() && mObjAtCount < (s32)ARRAY_SIZE(mpObjAt)) {
        mpObjAt[mObjAtCount] = obj;
        mObjAtCount++;
    }
    if (obj->ChkTgSet() && mObjTgCount < (s32)ARRAY_SIZE(mpObjTg)) {
        mpObjTg[mObjTgCount] = obj;
        mObjTgCount++;
    }
    if (obj->ChkCoSet() && mObjCoCount < (s32)ARRAY_SIZE(mpObjCo)) {
        mpObjCo[mObjCoCount] = obj;
        mObjCoCount++;
    }
    if (mObjCount < (s32)ARRAY_SIZE(mpObj)) {
        mpObj[mObjCount] = obj;
        mObjCount++;
    }
}

/* 80242DB8-80242E58       .text ClrCoHitInf__4cCcSFv */
void cCcS::ClrCoHitInf() {
    for (s32 i = 0; i < mObjCoCount; i++) {
        if (mpObjCo[i] != NULL) {
            cCcD_GObjInf * pInf = mpObjCo[i]->GetGObjInf();
            pInf->ClrCoHit();
            cCcD_Stts * pStts = mpObjCo[i]->GetStts();
            if (pStts != NULL)
                pStts->ClrCcMove();
        }
    }
}

/* 80242E58-80242EF8       .text ClrTgHitInf__4cCcSFv */
void cCcS::ClrTgHitInf() {
    for (s32 i = 0; i < mObjTgCount; i++) {
        if (mpObjTg[i] != NULL) {
            cCcD_GObjInf * pInf = mpObjTg[i]->GetGObjInf();
            pInf->ClrTgHit();
            cCcD_Stts * pStts = mpObjTg[i]->GetStts();
            if (pStts != NULL)
                pStts->ClrTg();
        }
    }
}

/* 80242EF8-80242F94       .text ClrAtHitInf__4cCcSFv */
void cCcS::ClrAtHitInf() {
    for (s32 i = 0; i < mObjAtCount; i++) {
        if (mpObjAt[i] != NULL) {
            cCcD_GObjInf * pInf = mpObjAt[i]->GetGObjInf();
            pInf->ClrAtHit();
            cCcD_Stts * pStts = mpObjAt[i]->GetStts();
            if (pStts != NULL)
                pStts->ClrAt();
        }
    }
}

/* 80242F94-802430BC       .text ChkNoHitAtTg__4cCcSFP8cCcD_ObjP8cCcD_Obj */
bool cCcS::ChkNoHitAtTg(cCcD_Obj* at, cCcD_Obj* tg) {
    fopAc_ac_c * ac_at = at->GetAc();
    fopAc_ac_c * ac_tg = tg->GetAc();
    if ((ac_at != NULL && ac_tg != NULL && ac_at == ac_tg) ||
        (at->GetAtGrp() & tg->GetTgGrp()) == 0 ||
        (at->GetAtType() & tg->GetTgType()) == 0)
    {
        return true;
    }

    return ChkNoHitGAtTg(at->GetGObjInf(), tg->GetGObjInf(), at->GetStts()->GetGStts(), tg->GetStts()->GetGStts());
}

/* 802430BC-802432F8       .text ChkAtTg__4cCcSFv */
void cCcS::ChkAtTg() {
    cCcD_Obj** objTgEnd = mpObjTg + mObjTgCount;
    ClrAtHitInf();
    ClrTgHitInf();
    for (cCcD_Obj** pObjAt = mpObjAt; pObjAt < mpObjAt + mObjAtCount; ++pObjAt) {
        if (*pObjAt == NULL || !(*pObjAt)->ChkAtSet())
            continue;
        cCcD_ShapeAttr* atShapeAttr = (*pObjAt)->GetShapeAttr();
        if (atShapeAttr == NULL)
            continue;
        for (cCcD_Obj** pObjTg = mpObjTg; pObjTg < objTgEnd; ++pObjTg) {
            if (*pObjTg == NULL || !(*pObjTg)->ChkTgSet())
                continue;
            if (!(*pObjAt)->GetDivideInfo().Chk((*pObjTg)->GetDivideInfo()))
                continue;
            if (ChkNoHitAtTg(*pObjAt, *pObjTg))
                continue;
            cCcD_ShapeAttr* tgShapeAttr = (*pObjTg)->GetShapeAttr();
            if (tgShapeAttr == NULL)
                continue;
            static cXyz cross;
            bool didCross = atShapeAttr->CrossAtTg(*tgShapeAttr, &cross);
            bool anyBsRevHit = (*pObjAt)->ChkBsRevHit() || (*pObjTg)->ChkBsRevHit();
            if (!anyBsRevHit && didCross) {
                SetAtTgCommonHitInf(*pObjAt, *pObjTg, &cross);
            } else if (anyBsRevHit && !didCross) {
                cCcD_ShapeAttr* atShape2 = (*pObjAt)->GetShapeAttr();
                if (atShape2 == NULL) {
                    cross.set(0.0f, 0.0f, 0.0f);
                } else {
                    atShape2->GetWorkAab().CalcCenter(&cross);
                }
                SetAtTgCommonHitInf(*pObjAt, *pObjTg, &cross);
            }
        }
    }
}

/* 802432F8-802433A8       .text ChkNoHitCo__4cCcSFP8cCcD_ObjP8cCcD_Obj */
bool cCcS::ChkNoHitCo(cCcD_Obj* obj1, cCcD_Obj* obj2) {
    fopAc_ac_c* ac1 = obj1->GetAc();
    fopAc_ac_c* ac2 = obj2->GetAc();
    if (!(
        ((ac1 == NULL || ac2 == NULL) || ac1 != ac2) &&
        (obj1->GetCoIGrp() & (obj2->GetCoVsGrp() >> 3)) &&
        ((obj1->GetCoVsGrp() >> 3) & obj2->GetCoIGrp() && !ChkNoHitGCo(obj1, obj2))
    )) {
        return true;
    } else {
        return false;
    }
}

/* 802433A8-8024352C       .text ChkCo__4cCcSFv */
void cCcS::ChkCo() {
    ClrCoHitInf();
    if (mObjCoCount <= 1)
        return;
    cCcD_Obj** objCoEnd = mpObjCo + mObjCoCount;
    for (cCcD_Obj** objCo1 = mpObjCo; objCo1 < objCoEnd - 1; ++objCo1) {
        if (*objCo1 == NULL || !(*objCo1)->ChkCoSet())
            continue;
        cCcD_ShapeAttr* co1ShapeAttr = (*objCo1)->GetShapeAttr();
        if (co1ShapeAttr == NULL)
            continue;
        for (cCcD_Obj** objCo2 = objCo1 + 1; objCo2 < objCoEnd; ++objCo2) {
            if (*objCo2 == NULL || !(*objCo2)->ChkCoSet())
                continue;
            if (!(*objCo1)->GetDivideInfo().Chk((*objCo2)->GetDivideInfo()))
                continue;
            if (ChkNoHitCo(*objCo1, *objCo2))
                continue;
            cCcD_ShapeAttr* co2ShapeAttr = (*objCo2)->GetShapeAttr();
            if (objCo2 == NULL)
                continue;
            f32 cross_len;
#if VERSION > VERSION_DEMO
            cross_len = 0.0f;
#endif
            if (co1ShapeAttr->CrossCo(*co2ShapeAttr, &cross_len)) {
                SetCoCommonHitInf(*objCo1, co1ShapeAttr->GetCoCP(), *objCo2, co2ShapeAttr->GetCoCP(), cross_len);
            }
        }
    }
}

/* 8024352C-80243544       .text CalcTgPlusDmg__4cCcSFP8cCcD_ObjP8cCcD_ObjP9cCcD_SttsP9cCcD_Stts */
void cCcS::CalcTgPlusDmg(cCcD_Obj* at, cCcD_Obj* tg, cCcD_Stts* at_stts, cCcD_Stts* tg_stts) {
    s32 atp = at->GetAtAtp();
    if (tg_stts->GetDmg() >= atp)
        return;
    tg_stts->PlusDmg(atp);
}

/* 80243544-80243740       .text SetAtTgCommonHitInf__4cCcSFP8cCcD_ObjP8cCcD_ObjP4cXyz */
void cCcS::SetAtTgCommonHitInf(cCcD_Obj* obj1, cCcD_Obj* obj2, cXyz* pXyz) {
    cCcD_Stts* obj1Stts = obj1->GetStts();
    cCcD_Stts* obj2Stts = obj2->GetStts();
    bool hit = ChkAtTgHitAfterCross(
        !obj2->ChkTgNoAtHitInfSet(), !obj1->ChkAtNoTgHitInfSet(),
        obj1->GetGObjInf(), obj2->GetGObjInf(), obj1Stts, obj2Stts,
        obj1Stts->GetGStts(), obj2Stts->GetGStts()
    );
    if (!hit) {
        if (!obj2->ChkTgNoAtHitInfSet()) {
            obj1->SetAtHit(obj2);
        }
        if (!obj1->ChkAtNoTgHitInfSet()) {
            obj2->SetTgHit(obj1);
            CalcTgPlusDmg(obj1, obj2, obj1Stts, obj2Stts);
        }
        SetAtTgGObjInf(
            !obj2->ChkTgNoAtHitInfSet(), !obj1->ChkAtNoTgHitInfSet(),
            obj1, obj2, obj1->GetGObjInf(), obj2->GetGObjInf(),
            obj1Stts, obj2Stts, obj1Stts->GetGStts(), obj2Stts->GetGStts(),
            pXyz
        );
    }
}

/* 80243740-8024388C       .text SetCoCommonHitInf__4cCcSFP8cCcD_ObjP4cXyzP8cCcD_ObjP4cXyzf */
void cCcS::SetCoCommonHitInf(cCcD_Obj* obj1, cXyz* ppos1, cCcD_Obj* obj2, cXyz* ppos2, f32 cross_len) {
    bool obj2CoHitInfSet = !obj2->ChkCoNoCoHitInfSet();
    bool obj1CoHitInfSet = !obj1->ChkCoNoCoHitInfSet();
    if (obj2CoHitInfSet) {
        obj1->SetCoHit(obj2);
    }
    if (obj1CoHitInfSet) {
        obj2->SetCoHit(obj1);
    }
    if (obj2CoHitInfSet && obj1CoHitInfSet) {
        SetPosCorrect(obj1, ppos1, obj2, ppos2, cross_len);
    }
    cCcD_Stts* obj1Stts = obj1->GetStts();
    cCcD_Stts* obj2Stts = obj2->GetStts();
    SetCoGObjInf(obj2CoHitInfSet, obj1CoHitInfSet, obj1->GetGObjInf(), obj2->GetGObjInf(),
                       obj1Stts, obj2Stts, obj1Stts->GetGStts(), obj2Stts->GetGStts());
}

/* 8024388C-80244750       .text SetPosCorrect__4cCcSFP8cCcD_ObjP4cXyzP8cCcD_ObjP4cXyzf */
void cCcS::SetPosCorrect(cCcD_Obj* obj1, cXyz* ppos1, cCcD_Obj* obj2, cXyz* ppos2, f32 cross_len) {
    CHECK_FLOAT_CLASS(604, cross_len);
#if VERSION > VERSION_DEMO
    CHECK_FLOAT_RANGE(605, cross_len);
#endif
    
    if (obj1->ChkCoNoCrr() || obj2->ChkCoNoCrr()) {
        return;
    }
    if (obj1->GetStts() == NULL || obj2->GetStts() == NULL) {
        return;
    }
    if (obj1->GetStts()->GetActor() != NULL && obj1->GetStts()->GetActor() == obj2->GetStts()->GetActor()) {
        return;
    }
#if VERSION == VERSION_DEMO
    if (std::fabsf(cross_len) < G_CM3D_F_ABS_MIN) {
        return;
    }
#else
    if (std::fabsf(cross_len) < (1.0f / 125.0f)) {
        return;
    }
#endif
    
    SetCoGCorrectProc(obj1, obj2);
    
    bool correctY = false;
    if (obj1->ChkCoSph3DCrr() && obj2->ChkCoSph3DCrr()) {
        correctY = true;
    }
    WeightType obj1WeightType = GetWt(obj1->GetStts()->GetWeightUc());
    WeightType obj2WeightType = GetWt(obj2->GetStts()->GetWeightUc());
    f32 obj1SrcWeight = obj1->GetStts()->GetWeightF();
    f32 obj2SrcWeight = obj2->GetStts()->GetWeightF();
    f32 combinedWeight = obj1SrcWeight + obj2SrcWeight;

    f32 obj2Weight, obj1Weight;
    if (cM3d_IsZero(combinedWeight)) {
        obj1SrcWeight = 1;
        obj2SrcWeight = 1;
        combinedWeight = 2;
    }
    f32 invCombinedWeight = 1 / combinedWeight;
    if (obj1WeightType == WeightType_0) {
        if (obj2WeightType == WeightType_0) {
            return;
        } else {
            obj2Weight = 0;
            obj1Weight = 1;
        }
    } else if (obj1WeightType == WeightType_1) {
        if (obj2WeightType == WeightType_0) {
            obj2Weight = 1;
            obj1Weight = 0;
        } else if (obj2WeightType == WeightType_1) {
            obj2Weight = 0.5;
            obj1Weight = 0.5;
        } else {
            obj2Weight = 0;
            obj1Weight = 1;
        }
    } else {
        if (obj2WeightType == WeightType_2) {
            obj2Weight = obj2SrcWeight * invCombinedWeight;
            obj1Weight = obj1SrcWeight * invCombinedWeight;
        } else {
            obj2Weight = 1;
            obj1Weight = 0;
        }
    }
    f32 objDistLen;
    Vec vec1;
    Vec vec2;
    Vec objsDist;
    if (correctY) {
        objsDist.x = ppos2->x - ppos1->x;
        objsDist.y = ppos2->y - ppos1->y;
        objsDist.z = ppos2->z - ppos1->z;
        objDistLen = std::sqrtf(objsDist.x*objsDist.x + objsDist.y*objsDist.y + objsDist.z*objsDist.z);
    } else {
        objsDist.x = ppos2->x - ppos1->x;
        objsDist.y = 0.0f;
        objsDist.z = ppos2->z - ppos1->z;
        objDistLen = std::sqrtf(objsDist.x*objsDist.x + objsDist.z*objsDist.z);
    }
    if (!cM3d_IsZero(objDistLen)) {
        if (correctY) {
            f32 pushFactor = cross_len / objDistLen;
            objsDist.x *= pushFactor;
            objsDist.y *= pushFactor;
            objsDist.z *= pushFactor;
            vec1.x = -objsDist.x * obj2Weight;
            vec1.y = -objsDist.y * obj2Weight;
            vec1.z = -objsDist.z * obj2Weight;
            vec2.x = objsDist.x * obj1Weight;
            vec2.y = objsDist.y * obj1Weight;
            vec2.z = objsDist.z * obj1Weight;
        } else {
            f32 pushFactor = cross_len / objDistLen;
            objsDist.x *= pushFactor;
            objsDist.z *= pushFactor;
            vec1.x = -objsDist.x * obj2Weight;
            vec1.y = 0;
            vec1.z = -objsDist.z * obj2Weight;
            vec2.x = objsDist.x * obj1Weight;
            vec2.y = 0;
            vec2.z = objsDist.z * obj1Weight;
        }
    } else {
        vec1.y = 0;
        vec1.z = 0;
        vec2.y = 0;
        vec2.z = 0;
        if (!cM3d_IsZero(cross_len)) {
            vec1.x = -cross_len * obj2Weight;
            vec2.x = cross_len * obj1Weight;
        } else {
            vec1.x = -obj2Weight;
            vec2.x = obj1Weight;
        }
    }
    
#if VERSION > VERSION_DEMO
    CHECK_FLOAT_CLASS(794, vec1.x);
    CHECK_FLOAT_CLASS(795, vec1.y);
    CHECK_FLOAT_CLASS(796, vec1.z);
    CHECK_FLOAT_CLASS(798, vec2.x);
    CHECK_FLOAT_CLASS(799, vec2.y);
    CHECK_FLOAT_CLASS(800, vec2.z);
    CHECK_VEC3_RANGE(804, vec1);
    CHECK_VEC3_RANGE(808, vec2);
#endif
    
    obj1->GetStts()->PlusCcMove(vec1.x, vec1.y, vec1.z);
    obj2->GetStts()->PlusCcMove(vec2.x, vec2.y, vec2.z);
    (*ppos1) += vec1;
    (*ppos2) += vec2;
    
#if VERSION > VERSION_DEMO
    CHECK_FLOAT_CLASS(817, ppos1->x);
    CHECK_FLOAT_CLASS(818, ppos1->y);
    CHECK_FLOAT_CLASS(819, ppos1->z);
    CHECK_FLOAT_CLASS(821, ppos2->x);
    CHECK_FLOAT_CLASS(822, ppos2->y);
    CHECK_FLOAT_CLASS(823, ppos2->z);
    CHECK_PVEC3_RANGE(827, ppos1);
    CHECK_PVEC3_RANGE(831, ppos2);
#endif
}

/* 80244750-80244894       .text CalcArea__4cCcSFv */
void cCcS::CalcArea() {
    cM3dGAab aab;
    aab.ClearForMinMax();
    for (cCcD_Obj** pObj = mpObj; pObj < mpObj + mObjCount; ++pObj) {
        if (*pObj == NULL)
            continue;
        cCcD_ShapeAttr* objShape = (*pObj)->GetShapeAttr();
        if (objShape == NULL)
            continue;
        objShape->CalcAabBox();
        cM3dGAab& shapeAab = objShape->GetWorkAab();
        aab.SetMinMax(*shapeAab.GetMinP());
        aab.SetMinMax(*shapeAab.GetMaxP());
    }
    mDivideArea.SetArea(aab);
    for (cCcD_Obj** pObj = mpObj; pObj < mpObj + mObjCount; ++pObj) {
        if (*pObj != NULL) {
            const cCcD_ShapeAttr* objShape = (*pObj)->GetShapeAttr();
            if (objShape == NULL)
                continue;
            cCcD_DivideInfo* divideInfo = &(*pObj)->GetDivideInfo();
            mDivideArea.CalcDivideInfo(divideInfo, objShape->GetWorkAab(), (*pObj)->ChkBsRevHit());
        }
    }
}

/* 80244894-802448F8       .text Move__4cCcSFv */
void cCcS::Move() {
    CalcArea();
    ChkAtTg();
    ChkCo();
    MoveAfterCheck();
    mObjAtCount = 0;
    mObjTgCount = 0;
    mObjCoCount = 0;
    mObjCount = 0;
}

/* 802448F8-8024498C       .text DrawClear__4cCcSFv */
void cCcS::DrawClear() {
    for (u32 i = 0; i < ARRAY_SIZE(mpObjAt); i++)
        mpObjAt[i] = NULL;
    mObjAtCount = 0;

    for (u32 i = 0; i < ARRAY_SIZE(mpObjTg); i++)
        mpObjTg[i] = NULL;
    mObjTgCount = 0;

    for (u32 i = 0; i < ARRAY_SIZE(mpObjCo); i++)
        mpObjCo[i] = NULL;
    mObjCoCount = 0;

    for (u32 i = 0; i < ARRAY_SIZE(mpObj); i++)
        mpObj[i] = NULL;
    mObjCount = 0;
}

/* 8024498C-80244990       .text SetCoGCorrectProc__4cCcSFP8cCcD_ObjP8cCcD_Obj */
void cCcS::SetCoGCorrectProc(cCcD_Obj*, cCcD_Obj*) {
}
