/**
 * d_a_obj_kanoke.cpp
 * Object - Earth Temple - Coffin
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_kanoke.h"
#include "d/actor/d_a_obj_kanoke.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "res/Object/Mkanoke.h"

static dCcD_SrcCps l_cps_src_body = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 100.0f,
    }},
};


static dCcD_SrcCps l_cps_src_huta = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 25.0f,
    }},
};

static cXyz daObjKanoke_Yoko_pfs[1] = { cXyz(100.0f, 0.0f, 0.0f) };
static cXyz daObjKanoke_Tate_pfs[3][2] = {
    { cXyz(50.0f, 0.0f, -175.0f), cXyz(50.0f, 0.0f, 175.0f) },
    { cXyz(0.0f, 0.0f, -175.0f), cXyz(0.0f, 0.0f, -175.0f) },
    { cXyz(-50.0f, 0.0f, -175.0f), cXyz(-50.0f, 0.0f, -175.0f) },
};

static daObjKanoke_c::ProcFunc_t moveProc[] = {
    &daObjKanoke_c::executeNormal,
    &daObjKanoke_c::executeYureYoko,
    &daObjKanoke_c::executeOpenYoko,
    &daObjKanoke_c::executeEffectYoko,
    &daObjKanoke_c::executeYureTate,
    &daObjKanoke_c::executeOpenTate,
    &daObjKanoke_c::executeEffectTate,
    &daObjKanoke_c::executeWait,
};


/* 000000EC-000002F4       .text __ct__13daObjKanoke_cFv */
daObjKanoke_c::daObjKanoke_c() {
    /* Nonmatching */
    mType = getPrmType();
    mSearch = getPrmSearch();
    mSwNo = getPrmSwNo();
    mSwNo2 = getPrmSwNo2();
    if (mType == 0) {
        field_0x86C.set(0.0f, 0.0f, 0.0f);
    } else {
        current.pos.y = home.pos.y + 200.0f;
        shape_angle.x = 0x4000;
        field_0x86C.set(0.0f, 35.0f, 200.0f);
    }
    field_0x860.set(0.0f, 75.0f, 0.0f);
    field_0x87C = 0;
    field_0x87E = 0;
    field_0x880 = 0;
    field_0x882 = 0;
    for (int i=0; i<2; i++) {
        mpEmitters[i] = NULL;
    }
    mParticleCallBack.setRateOff(0);
    mMode = MODE_NORMAL;
    field_0x88F = 0;
    field_0x888 = 0;
    setMtxHontai();
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
    setMtxHuta(&current.pos);
    MTXCopy(mDoMtx_stack_c::get(), mMtx2);
}

/* 00000644-00000664       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* act) {
    /* Nonmatching */
    return ((daObjKanoke_c*)act)->createHeap();
}

/* 00000664-00000700       .text _create__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::_create() {
    /* Nonmatching */
    fopAcM_ct(this, daObjKanoke_c);
    if (dComIfG_resLoad(&mPhase, "Mkanoke") == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2400) != 0) {
            createInit();
        } else {
#if VERSION > VERSION_DEMO
            mpBgW2 = NULL;
            mpBgW = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
}

/* 00000700-000008BC       .text createHeap__13daObjKanoke_cFv */
BOOL daObjKanoke_c::createHeap() {
    /* Nonmatching */
    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Mkanoke",dRes_INDEX_MKANOKE_BDL_MOKE1_e);
    if (modelData == NULL) {
        return FALSE;
    }
    mpModel = mDoExt_J3DModel__create(modelData, 0,0x11020203);
    if (mpModel == NULL) {
        return FALSE;
    }

    mpBgW = new dBgW();
    if (mpBgW == NULL) {
        return FALSE;
    } else {
        cBgD_t* res = (cBgD_t*) dComIfG_getObjectRes("Mkanoke",dRes_INDEX_MKANOKE_DZB_MOKE1_e);
        if (mpBgW->Set(res, cBgW::MOVE_BG_e, &mMtx) == TRUE) {
            return FALSE;
        }
    }
    modelData = (J3DModelData*) dComIfG_getObjectRes("Mkanoke",dRes_INDEX_MKANOKE_BDL_MOKE2_e);
    if (modelData == NULL) {
        return FALSE;
    }
    mpModel2 = mDoExt_J3DModel__create(modelData, 0,0x11020203);
    if (mpModel2 == NULL) {
        return FALSE;
    }

    mpBgW2 = new dBgW();
    if (mpBgW2 == NULL) {
        return FALSE;
    } else {
        cBgD_t* res = (cBgD_t*) dComIfG_getObjectRes("Mkanoke",dRes_INDEX_MKANOKE_DZB_MOKE2_e);
        if (mpBgW2->Set(res, cBgW::MOVE_BG_e, &mMtx2) == TRUE) {
            return FALSE;
        }
    }

    return TRUE;
}

/* 000008BC-00000B28       .text createInit__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::createInit() {
    /* Nonmatching */
    if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
        return cPhs_ERROR_e;
    }
    if (mSwNo != 0xff) {
        if (dComIfGs_isSwitch(mSwNo, fopAcM_GetHomeRoomNo(this))) {
            mMode = MODE_WAIT;
            if (mType == 0) {
                if (dComIfG_Bgsp()->Regist(mpBgW2, this)) {
                    return cPhs_ERROR_e;
                }
                field_0x860.set(148.0f, 75.0f, 0.0f);
                field_0x86C.set(-48.0f, 0.0f, 0.0f);
                field_0x880 = -5600;
            } else {
                field_0x88F |= 2;
            }
        } else {
            if (dComIfG_Bgsp()->Regist(mpBgW2, this)) {
                return cPhs_ERROR_e;
            }
        }
    } else {
        if (dComIfG_Bgsp()->Regist(mpBgW2, this)) {
            return cPhs_ERROR_e;
        }
    }

    mStts.Init(0xff, 0xff, this);
    mCps.Set(l_cps_src_body);
    mCps.SetStts(&mStts);
    mCps.SetStartEnd(current.pos, current.pos);

    for (int i=0; i<3; i++) {
        mCps2[i].Set(l_cps_src_huta);
        mCps2[i].SetStts(&mStts);
        mCps2[i].SetStartEnd(current.pos, current.pos);
    }
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    setMtx();
    if (mType == 0) {
        fopAcM_setCullSizeBox(this, -110.0f, 0.0f, -210.0f, 310.0f, 120.0f, 210.0f);
    } else {
        fopAcM_setCullSizeBox(this, -110.0f, 0.0f, -210.0f, 110.0f, 520.0f, 210.0f);
    }

    return cPhs_COMPLEATE_e;
}

/* 00000B28-00000C0C       .text _delete__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_delete() {
    /* Nonmatching */
#if VERSION > VERSION_DEMO
    if (heap != NULL) {
        if (mpBgW != NULL) {
#endif
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
#if VERSION > VERSION_DEMO
        }
        if (mpBgW2 != NULL) {
#endif
            if (mpBgW2->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW2);
            }
#if VERSION > VERSION_DEMO
        }
    }
#else
    for (int i=0; i<2; i++) {
        // Empty loop
    }
#endif
    mParticleCallBack.end();
#if VERSION > VERSION_DEMO
    dComIfG_resDelete(&mPhase, "Mkanoke");
#else
    dComIfG_deleteObjectRes("Mkanoke");
#endif
    return TRUE;
}

/* 00000C0C-00000CE0       .text _draw__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    g_env_light.setLightTevColorType(mpModel2, &tevStr);
    dComIfGd_setListBG();
    if ((field_0x88F & 1) == 0) {
        mDoExt_modelUpdateDL(mpModel);
    }
    if ((field_0x88F & 2) == 0) {
        mDoExt_modelUpdateDL(mpModel2);
    }
    dComIfGd_setList();
    return TRUE;
}

/* 00000CE0-00000E7C       .text _execute__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_execute() {
    /* Nonmatching */
    cXyz r1(0.0f, 0.0f, -100.0f);
    cXyz r3(0.0f, 0.0f, 100.0f);
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    cMtx_multVec(mDoMtx_stack_c::get(), &r1, &r1);
    cMtx_multVec(mDoMtx_stack_c::get(), &r3, &r3);
    VECAdd(&r1, &current.pos, &r1);
    VECAdd(&r3, &current.pos, &r3);
    mCps.SetStartEnd(r1, r3);
    mCps.SetR(140.0f);
    g_dComIfG_gameInfo.play.mCcS.Set(&mCps);
    (this->*moveProc[mMode])();
    setMtx();
    if (mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    if (mpBgW2->ChkUsed()) {
        mpBgW2->Move();
    }
    return TRUE;
}

/* 00000E7C-0000122C       .text executeNormal__13daObjKanoke_cFv */
void daObjKanoke_c::executeNormal() {
    /* Nonmatching */
    bool b1 = false;
    if (mSwNo != 0xff && dComIfGs_isSwitch(mSwNo, fopAcM_GetHomeRoomNo(this))) {
        b1 = true;
    } else {
        if (dComIfGp_getDetect().chk_light(&current.pos) || mCps.ChkTgHit()) {
            field_0x888++;
            if (field_0x888 > 20) {
                mCps.SetTgType(0);
                b1 = true;
            }
        } else {
            field_0x888 = 0;
            if (mSearch != 0) {
                fopAc_ac_c* player = dComIfGp_getPlayer(0);
                cXyz diff = home.pos - player->current.pos;
                if (diff.abs() < mSearch * 100.0f) {
                    b1 = true;
                }
            }
        }
    }

    if (b1) {
        mCps.ClrTgHit();
        if (mSwNo != 0xff) {
            fopAcM_onSwitch(this, mSwNo);
        }
        field_0x882 = 0;
        if (getPrmYure() != 0) {
            field_0x884 = 0;
            if (mType == 0) {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_Y_GATA, 0);
                mMode = MODE_YURE_YOKO;
                field_0x880 = 0;
                field_0x886 = 0x100;
            } else {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_T_GATA, 0);
                mMode = MODE_YURE_TATE;
                field_0x87E = 0;
                field_0x886 = 0x400;
            }
        } else {
            if (mType == 0) {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_Y_OPEN, 0);
                mMode = MODE_OPEN_YOKO;
                field_0x880 = 0;
            } else {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_T_OPEN, 0);
                mMode = MODE_OPEN_TATE;
                if (mpBgW2->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW2);
                }
                field_0x87C = 0;
            }
        }
    }
}

/* 0000122C-00001358       .text executeYureYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureYoko() {
    /* Nonmatching */
    field_0x884 += 0x2000;
    field_0x886 -= 8;
    field_0x880 = field_0x886 * cM_ssin(field_0x884);
    if (field_0x880 < 0) {
        field_0x86C.x = 100.0f;
    } else {
        field_0x86C.x = -100.0f;
    }
    if (field_0x886 <= 0) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_Y_OPEN, 0);
        mMode = MODE_OPEN_YOKO;
        field_0x880 = 0;
        field_0x86C.x = 0.0f;
    }
}

/* 00001358-00001544       .text executeOpenYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenYoko() {
    /* Nonmatching */
    f32 f1 = 100.0f;
    s16 s1 = -5600;
    field_0x860.x += 4.0f;
    field_0x86C.x = f1 - field_0x860.x;
    if (field_0x860.x > f1) {
        field_0x880 += field_0x882;
        field_0x882 -= 100;
        if (field_0x880 <= s1) {
            field_0x880 = s1;
            mMode = MODE_EFFECT_YOKO;
            mDoMtx_stack_c::YrotS(shape_angle.y);
            mDoMtx_stack_c::transM(100.0f, 75.0f, 0.0f);
            mDoMtx_stack_c::ZrotM(field_0x880);
            mDoMtx_stack_c::transM(-100.0f, -75.0f, 0.0f);
            Mtx m;
            MTXCopy(mDoMtx_stack_c::get(), m);
            field_0x858.set(0, shape_angle.y, 0);
            mPartAlpha = 180.0f;
            cXyz r2 = field_0x860 + daObjKanoke_Yoko_pfs[0];
            cMtx_multVec(m, &r2, &r2);
            mPartPos = r2 + current.pos;
#if VERSION > VERSION_DEMO
            if (mParticleCallBack.getEmitter() == NULL) {
#endif
                dComIfGp_particle_setToon(dPa_name::ID_IT_ST_KANOKE_SMOKE01, &mPartPos, &field_0x858, NULL, mPartAlpha, &mParticleCallBack, -1, NULL, NULL, NULL);

#if VERSION > VERSION_DEMO
            }
#endif
            JPABaseEmitter* e = mParticleCallBack.getEmitter();
            if (e != NULL) {
                e->becomeImmortalEmitter();
            }
            field_0x884 = 60;
        }
    }
}

/* 00001544-000015F8       .text executeEffectYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectYoko() {
    /* Nonmatching */
    field_0x884--;
    if (field_0x884 != 0) {
        if (field_0x884 <= 50) {
            mPartAlpha -= 3.6f;
            if (mPartAlpha < 0.0f) {
                mPartAlpha = 0.0f;
            }
            if (mParticleCallBack.getEmitter() != NULL) {
                mParticleCallBack.getEmitter()->setGlobalAlpha(mPartAlpha);
            }
        }
    } else {
        mParticleCallBack.end();
        mMode = MODE_WAIT;
    }
}

/* 000015F8-00001764       .text executeYureTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureTate() {
    /* Nonmatching */
    field_0x884 += 0x2000;
    field_0x886 -= 0x20;
    field_0x87E = field_0x886 * cM_ssin(field_0x884);
    if (field_0x87E < 0) {
        field_0x86C.x = 100.0f;
    } else {
        field_0x86C.x = -100.0f;
    }
    if (field_0x886 <= 0) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_KANOKE_T_OPEN, 0);
        mMode = MODE_OPEN_TATE;
        if (mpBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW2);
        }
        field_0x87C = 0;
        field_0x87E = 0;
        field_0x86C.x = 0.0f;
    }
}

/* 00001764-00001A6C       .text executeOpenTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenTate() {
    /* Nonmatching */
    field_0x87C += field_0x882;
    field_0x882 += 100;
    if (field_0x87C >= 0x4000) {
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        field_0x87C = 0x4000;
        mMode = MODE_EFFECT_TATE;
        field_0x88F |= 2;
        mDoMtx_multVecZero(mMtx2, &mPartPos);
        field_0x858.set(0, shape_angle.y, 0);
        mpEmitters[0] = dComIfGp_particle_set(dPa_name::ID_IT_SN_KANOKE_ROCK00, &mPartPos, &field_0x858, NULL, 0xff, NULL, -1, &tevStr.mColorK0);
        mPartAlpha = 180.0f;
#if VERSION > VERSION_DEMO
        if (mParticleCallBack.getEmitter() == NULL) {
#endif
            dComIfGp_particle_setToon(dPa_name::ID_IT_ST_KANOKE_SMOKE00, &mPartPos, &field_0x858, NULL, mPartAlpha, &mParticleCallBack, -1, NULL, NULL, NULL);
#if VERSION > VERSION_DEMO
        }
#endif
        if (mParticleCallBack.getEmitter() != NULL) {
            mParticleCallBack.getEmitter()->becomeImmortalEmitter();
        }
        field_0x884 = 60;
    } else {
        mDoMtx_stack_c::YrotS(shape_angle.y);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::transM(0.0f, 110.0f, 200.0f);
        mDoMtx_stack_c::XrotM(field_0x87C);
        mDoMtx_stack_c::transM(0.0f, -110.0f, -200.0f);
        for (int i=0; i<3; i++) {
            cXyz start = daObjKanoke_Tate_pfs[i][0] + field_0x860;
            cXyz end = daObjKanoke_Tate_pfs[i][1] + field_0x860;
            cMtx_multVec(mDoMtx_stack_c::get(), &start, &start);
            cMtx_multVec(mDoMtx_stack_c::get(), &end, &end);
            VECAdd(&start, &current.pos, &start);
            VECAdd(&end, &current.pos, &end);
            mCps2[i].SetStartEnd(start, end);
            dComIfG_Ccsp()->Set(&mCps2[i]);
        }
    }
}

/* 00001A6C-00001B24       .text executeEffectTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectTate() {
    /* Nonmatching */
    field_0x884--;
    if (field_0x884 != 0) {
        if (mParticleCallBack.getEmitter() != NULL && field_0x884 <= 50) {
            mPartAlpha -= 3.6f;
            if (mPartAlpha < 0.0f) {
                mPartAlpha = 0.0f;
            }
            mParticleCallBack.getEmitter()->setGlobalAlpha(mPartAlpha);
        }
    } else {
        mParticleCallBack.end();
        mMode = MODE_WAIT;
    }
}

/* 00001B24-00001B28       .text executeWait__13daObjKanoke_cFv */
void daObjKanoke_c::executeWait() {
    /* Nonmatching */
}

/* 00001B28-00001B54       .text getPrmType__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmType() {
    /* Nonmatching */
    return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S);
}

/* 00001B54-00001B80       .text getPrmSearch__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSearch() {
    /* Nonmatching */
    return daObj::PrmAbstract<Prm_e>(this, PRM_SEARCH_W, PRM_SEARCH_S);
}

/* 00001B80-00001BAC       .text getPrmYure__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmYure() {
    /* Nonmatching */
    return daObj::PrmAbstract<Prm_e>(this, PRM_YURE_W, PRM_YURE_S);
}

/* 00001BAC-00001BD8       .text getPrmSwNo__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo() {
    /* Nonmatching */
    return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO_W, PRM_SWNO_S);
}

/* 00001BD8-00001C04       .text getPrmSwNo2__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo2() {
    /* Nonmatching */
    return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO2_W, PRM_SWNO2_S);
}

/* 00001C04-00001C9C       .text setMtx__13daObjKanoke_cFv */
void daObjKanoke_c::setMtx() {
    /* Nonmatching */
    if ((field_0x88F & 0x1) == 0) {
        setMtxHontai();
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
    }
    if ((field_0x88F & 0x2) == 0) {
        setMtxHuta(&current.pos);
        mpModel2->setBaseTRMtx(mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), mMtx2);
    }
}

/* 00001C9C-00001D38       .text setMtxHontai__13daObjKanoke_cFv */
void daObjKanoke_c::setMtxHontai() {
    /* Nonmatching */
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(field_0x86C);
    mDoMtx_stack_c::YrotM(field_0x87E);
    mDoMtx_stack_c::transM(-field_0x86C.x, -field_0x86C.y, -field_0x86C.z);
}

/* 00001D38-00001E4C       .text setMtxHuta__13daObjKanoke_cFP4cXyz */
void daObjKanoke_c::setMtxHuta(cXyz* param1) {
    /* Nonmatching */
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    cXyz r1;
    cMtx_multVec(mDoMtx_stack_c::get(), &field_0x860, &r1);
    MTXTrans(mDoMtx_stack_c::get(), param1->x + r1.x, param1->y + r1.y, param1->z + r1.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(field_0x86C);
    mDoMtx_stack_c::XrotM(field_0x87C);
    mDoMtx_stack_c::YrotM(field_0x87E);
    mDoMtx_stack_c::ZrotM(field_0x880);
    mDoMtx_stack_c::transM(-field_0x86C.x, -field_0x86C.y, -field_0x86C.z);
}

/* 00001E4C-00001E6C       .text daObjKanokeCreate__FPv */
static cPhs_State daObjKanokeCreate(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_create();
}

/* 00001E6C-00001E8C       .text daObjKanokeDelete__FPv */
static BOOL daObjKanokeDelete(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_delete();
}

/* 00001E8C-00001EAC       .text daObjKanokeExecute__FPv */
static BOOL daObjKanokeExecute(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_execute();
}

/* 00001EAC-00001ECC       .text daObjKanokeDraw__FPv */
static BOOL daObjKanokeDraw(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_draw();
}

/* 00001ECC-00001ED4       .text daObjKanokeIsDelete__FPv */
static BOOL daObjKanokeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObjKanokeMethodTable = {
    (process_method_func)daObjKanokeCreate,
    (process_method_func)daObjKanokeDelete,
    (process_method_func)daObjKanokeExecute,
    (process_method_func)daObjKanokeIsDelete,
    (process_method_func)daObjKanokeDraw,
};

actor_process_profile_definition g_profile_Obj_Kanoke = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Kanoke_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjKanoke_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Kanoke_e,
    /* Actor SubMtd */ &daObjKanokeMethodTable,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
