/**
 * d_a_shand.cpp
 * Object - Forbidden Woods - Ceiling tentacle / 汎用触手 (general purpose tentacle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_shand.h"
#include "d/res/res_shand.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"

bool hio_set;
daShand_HIO_c l_HIO;

/* 000000EC-00000114       .text __ct__13daShand_HIO_cFv */
daShand_HIO_c::daShand_HIO_c() {
    this->mNo = -1;
    this->field_6 = -3;
    this->field_8 = 50;
}

/* 00000114-00000194       .text hand_draw__FP11shand_class */
void hand_draw(shand_class* i_this) {
    GXColor color = {0x50, 0x96, 0x96, 0xff};
    i_this->mLineMat.update(0x14, color, &i_this->tevStr);
    dComIfGd_set3DlineMat(&i_this->mLineMat);
}

/* 00000194-000001E0       .text daShand_Draw__FP11shand_class */
static BOOL daShand_Draw(shand_class* i_this) {
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &i_this->eyePos, &i_this->tevStr);
    hand_draw(i_this);
    return TRUE;
}

/* 000001E0-0000052C       .text control1__FP11shand_class */
void control1(shand_class* i_this) {
    float fVar_x, fVar_y, fVar_z;

    i_this->field_31C[0].mPos = i_this->current.pos;
    int i = 1;
    shand_s* shand_i = &i_this->field_31C[i];
    
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);

    cXyz local94, cStack_a0, localac;
    local94.x = 0.0f;
    local94.y = i_this->field_2F8;
    local94.z = i_this->field_2FC;
    MtxPosition(&local94, &localac);
    cLib_addCalc2(&i_this->field_2F8, REG0_F(7), 1.0f, 0.1f);
    cLib_addCalc2(&i_this->field_2FC, REG0_F(8), 1.0f, 1.0f);
    local94.z = i_this->field_2F4;
    float fVar1 = i_this->field_300;
    cXyz idk;
    for(i = 1; i < 19; i++, ++shand_i){
        idk.x = fVar1 * cM_ssin(i_this->mExecuteCount * (REG0_S(5) + 1100) + i * (REG0_S(6) + 4000));
        idk.z =  fVar1 * cM_scos(i_this->mExecuteCount * (REG0_S(7) + 800) + i * (REG0_S(8) + 4000));
        float fVar2 = (i < 15) ? 1.0f : 1.0f - (i - 15) * 0.2f;

        fVar_x = shand_i->mPos.x - shand_i[-1].mPos.x + (localac.x * fVar2) + (idk.x * fVar2);
        fVar_y = shand_i->mPos.y - shand_i[-1].mPos.y + localac.y;
        fVar_z = shand_i->mPos.z - shand_i[-1].mPos.z + (localac.z * fVar2) + (idk.z * fVar2);

        short iVar3;
        int iVar2 = cM_atan2s(fVar_x, fVar_z);
        iVar3 = -cM_atan2s(fVar_y, std::sqrtf(fVar_x * fVar_x + fVar_z * fVar_z));
        mDoMtx_YrotS(*calc_mtx, iVar2);
        mDoMtx_XrotM(*calc_mtx, iVar3);
        MtxPosition(&local94, &cStack_a0);
        shand_i->mPos = shand_i[-1].mPos + cStack_a0;
    }
}

/* 0000052C-00000740       .text control2__FP11shand_class */
void control2(shand_class* i_this) {
    cXyz rel_offset, abs_offset;
    rel_offset.x = 0;
    rel_offset.y = 0;
    rel_offset.z = i_this->field_2F4;

    cLib_addCalc2(&i_this->field_31C[19].mPos.x, i_this->field_2D4.x, 1.0f, i_this->field_2F0 * 50.0f);
    cLib_addCalc2(&i_this->field_31C[19].mPos.y, i_this->field_2D4.y, 1.0f, i_this->field_2F0 * 50.0f);
    cLib_addCalc2(&i_this->field_31C[19].mPos.z, i_this->field_2D4.z, 1.0f, i_this->field_2F0 * 50.0f);
    cLib_addCalc2(&i_this->field_2F0, 1.0f, 1.0f, 0.01f);

    int i = 18;
    short Yangle;
    int XZangle;
    shand_s* shand_i = &i_this->field_31C[i];
    for(i = 18; i >= 1; i--, shand_i--){
        float delta_pos_x = shand_i->mPos.x - shand_i[1].mPos.x;
        float delta_pos_y = shand_i->mPos.y - shand_i[1].mPos.y;
        float delta_pos_z = shand_i->mPos.z - shand_i[1].mPos.z;
        XZangle = cM_atan2s(delta_pos_x, delta_pos_z);
        Yangle = -cM_atan2s(delta_pos_y, std::sqrtf(delta_pos_x * delta_pos_x + delta_pos_z * delta_pos_z));
        mDoMtx_YrotS(*calc_mtx, XZangle);
        mDoMtx_XrotM(*calc_mtx, Yangle);
        MtxPosition(&rel_offset, &abs_offset);
        shand_i->mPos = shand_i[1].mPos + abs_offset;
    }
}

/* 00000740-000007C4       .text control3__FP11shand_class */
void control3(shand_class* i_this) {
    shand_s* shand_i = i_this->field_31C;
    int counter = 0;
    for(int i = 20; i != 0; i--, counter++, shand_i++){
        if(counter < 12){
            shand_i->field_18 = i_this->field_304;
        }
        else {
            shand_i->field_18 = i_this->field_304 * (1.0f - (counter + -10) * 0.05f);
        }
    }
}

/* 000007C4-00000BAC       .text cut_control__FP11shand_class */
void cut_control(shand_class* i_this) {
    i_this->field_31C[0].mPos = i_this->current.pos;
    int i = 1;
    shand_s *shand_i = &i_this->field_31C[i];

    cXyz local_b8, cStack_c4, local_d0;
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    local_b8.x = 0.0f;
    local_b8.y = i_this->field_2F8;
    local_b8.z = i_this->field_2FC;
    MtxPosition(&local_b8, &local_d0);
    cLib_addCalc2(&i_this->field_2F8, REG14_F(7) + -5.0f, 1.0f, REG12_F(4) + 0.1f);
    cLib_addCalc2(&i_this->field_2FC, REG14_F(8) + 20.0f, 1.0f, REG14_F(5) + 0.2f);
    cLib_addCalc0(&i_this->field_300, 1.0f, REG12_F(6) + 1.0f);
    local_b8.z = i_this->field_2F4;
    cXyz d0_scaled, local_e8;
    float fVar_x, fVar_y, fVar_z, delta_y;
    for(i = 1; i < 20; i++, shand_i++){
        local_e8.x = i_this->field_300 * cM_ssin(i_this->mExecuteCount * (REG0_S(4) + 3500) + i * (REG0_S(5) + 4000));
        local_e8.y = i_this->field_300 * cM_scos(i_this->mExecuteCount * (REG0_S(6) + 4000) + i * (REG0_S(7) + 4000));
        local_e8.z = i_this->field_300 * cM_scos(i_this->mExecuteCount * (REG0_S(8) + 3800) + i * (REG0_S(9) + 4000));
        
        float factor = 1.0f - i * (REG0_F(9) + 0.03763158f);
        d0_scaled.x = local_d0.x * factor;
        d0_scaled.z = local_d0.z * factor;
        
        fVar_x = shand_i->mPos.x - shand_i[-1].mPos.x + d0_scaled.x + local_e8.x;
        fVar_y = shand_i->mPos.y + local_d0.y + local_e8.y;
        if (fVar_y < i_this->ground_y) fVar_y = i_this->ground_y;
        delta_y = fVar_y - shand_i[-1].mPos.y;
        fVar_z = shand_i->mPos.z - shand_i[-1].mPos.z + d0_scaled.z + local_e8.z;
        
        short iVar6;
        int iVar5 = cM_atan2s(fVar_x,fVar_z);
        iVar6 = -cM_atan2s(delta_y, std::sqrtf(fVar_x * fVar_x + fVar_z * fVar_z));
        mDoMtx_YrotS(*calc_mtx, iVar5);
        mDoMtx_XrotM(*calc_mtx, iVar6);
        MtxPosition(&local_b8, &cStack_c4);
        shand_i->mPos = shand_i[-1].mPos + cStack_c4;
    }
}

/* 00000BAC-00000C30       .text cut_control3__FP11shand_class */
void cut_control3(shand_class* i_this) {
    shand_s* shand_i = i_this->field_31C;
    int counter = 0;
    for(int i = 20; i != 0; i--, counter++, shand_i++){
        if(counter < 12){
            shand_i->field_18 = i_this->field_304;
        }
        else {
            shand_i->field_18 = i_this->field_304 * (1.0f - (counter - 10) * 0.08f);
        }
    }
}

/* 00000C30-00000FF0       .text normal__FP11shand_class */
void normal(shand_class* i_this) {
    fopAc_ac_c* actor = i_this;

    cXyz unused;
    unused.x = unused.y = 0;

    if(i_this->field_318 != 0){
        dBgS_LinChk local94;
        cXyz chk_start = actor->current.pos, chk_end = actor->current.pos;
        chk_start.y += 50.0f;
        chk_end.y += 4000.0f;
        local94.Set(&chk_start, &chk_end, actor);
        if(dComIfG_Bgsp()->LineCross(&local94) != false)
            i_this->field_31C[19].mPos = i_this->field_2D4 = i_this->field_2C8 = local94.GetCross();
        i_this->field_318--;
    }

    switch(i_this->field_2BA){
        case 0:
            if(std::abs(i_this->field_31C[19].mPos.y - i_this->field_2D4.y) < 10.0f){
                i_this->field_2BA = 1;
                *i_this->field_314 = 2;
            }
            // Fall-through
        case 1:
            i_this->field_2D4 = i_this->field_2C8;
            break;
    }

    float y_diff = std::abs(actor->home.pos.y - i_this->field_2C8.y);
    cLib_addCalc2(&i_this->field_2F4,   y_diff * (REG14_F(11) + 0.05f), 0.1f, 1.0f);
    cLib_addCalc2(&i_this->field_300, REG14_F(12) + 10.0f, 0.1f, 0.5f);
    control1(i_this);
    control2(i_this);
    control3(i_this);
}

/* 00001428-00001508       .text cut__FP11shand_class */
void cut(shand_class* i_this) {
    cLib_addCalc2(&i_this->field_2F4, REG8_F(12) + 20.0f, 0.1f, 0.5f);
    cut_control(i_this);
    cut_control3(i_this);
    if(i_this->field_2BC[0] == 0 && i_this->field_30C->health != 0){
        i_this->mState = 0;
        i_this->field_2BA = 0;
        i_this->field_2F0 = 0.0f;
        i_this->field_300 = 0.0f;
        fopAcM_seStart(i_this, JA_SE_OBJ_VINE_S_RECOVER, 0);
    }
}

/* 00001508-00001DAC       .text hand_move__FP11shand_class */
void hand_move(shand_class* i_this) {
    fopAc_ac_c* actor = i_this;

    shand_s* shand_i = i_this->field_31C;
    i_this->field_30C = static_cast<shand_class*>(fopAcM_SearchByID(i_this->field_308));
    if(i_this->field_30C != NULL){
        actor->current.pos = *i_this->field_310;
        actor->current.angle.y = actor->home.angle.y + i_this->field_30C->shape_angle.y + REG14_S(3);
        switch(i_this->mState){
            case 0:
                normal(i_this);
                actor->attention_info.flags = fopAc_Attn_LOCKON_MISC_e;
                if(i_this->field_30C->health == 0){
                    i_this->mState = 1;
                    i_this->field_2BA = 0;
                }
                break;

            case 1: 
                if((fopAcM_GetParam(actor) & 0xFF) != 1){
                    dBgS_GndChk local_ac;
                    Vec chk_pos;
                    chk_pos = actor->current.pos;
                    chk_pos.y -= 100.0f;
                    local_ac.SetPos(&chk_pos);
                    i_this->ground_y = dComIfG_Bgsp()->GroundCross(&local_ac);
                    
                    dBgS_ObjGndChk_Spl local_100;
                    chk_pos = actor->current.pos;
                    chk_pos.y += 200.0f;
                    local_100.SetPos(&chk_pos);
                    f32 spl_ground_y = dComIfG_Bgsp()->GroundCross(&local_100) + 10.0f;
                    if(spl_ground_y != -G_CM3D_F_INF){
                        i_this->ground_y = spl_ground_y;
                    }
                }
                else {
                    i_this->ground_y = -G_CM3D_F_INF;
                }
                i_this->mState = 2;

                // Fall-through
            case 2:
                cut(i_this);
                fopAcM_OffStatus(actor, 0);
                actor->attention_info.flags = 0;
                break;
        }
    }

    cXyz* line_data = i_this->mLineMat.getPos(0);
    u8* line_size = i_this->mLineMat.getSize(0);
    for(int i = 20; i != 0; i--){
        *line_data = shand_i->mPos;
        *line_size = shand_i->field_18;

        shand_i++; line_data++; line_size++;
    }

    cXyz* line_segments = i_this->mLineMat.getPos(0);
    actor->eyePos = (line_segments + l_HIO.field_6)[10]; // Have not found any "clean" way to write that
    actor->attention_info.position = actor->eyePos;
    
    bool is_hit = false;
    CcAtInfo hit_atInfo;
    hit_atInfo.pParticlePos = NULL;
    cXyz center;
    int seg_idx;
    if(i_this->field_2BC[1] == 0 && i_this->mState == 0){
        i_this->mSph.SetC(actor->eyePos);
        i_this->mCylArr[0].SetC(actor->current.pos);
        for(int i = 0; i < 5; i++){
            if(i_this->field_2C4 == 0 && i_this->mCylArr[i].ChkTgHit() != 0){
                hit_atInfo.mpObj = i_this->mCylArr[i].GetTgHitObj();
                hit_atInfo.pParticlePos = i_this->mCylArr[i].GetTgHitPosP();
                is_hit = true;
                break;
            }

            if(i > 0){
                seg_idx = ((i_this->mExecuteCount & 0b11) + (i * 4));
                seg_idx %= 20;
                center = line_segments[seg_idx];
                center.y -= 200.0f;
                i_this->mCylArr[i].SetC(center);   
            }
        }
    }
    else {
        center.set(0.0f, -20000.0f, 0.0f);
        i_this->mSph.SetC(center);
        for(int i = 0; i < 5; i++){
            i_this->mCylArr[i].SetC(center);
        }
    }

    dComIfG_Ccsp()->Set(&i_this->mSph);
    for(int i = 0; i < 5; i++){
        dComIfG_Ccsp()->Set(&i_this->mCylArr[i]);
    }
    
    if(is_hit || (i_this->field_2C4 == 0 && i_this->mSph.ChkTgHit() != 0)){
        if(!is_hit){
            hit_atInfo.mpObj = i_this->mSph.GetTgHitObj();
            hit_atInfo.pParticlePos = i_this->mSph.GetTgHitPosP();
        }
        hit_atInfo.mpActor = at_power_check(&hit_atInfo);
        i_this->field_2C4 = 10;
        if(hit_atInfo.mpActor != NULL){
            def_se_set(actor, hit_atInfo.mpObj, 33);
            if(i_this->field_30C != NULL){
                i_this->mState = 1;
                i_this->field_2BA = 0;
                i_this->field_2BC[0] = l_HIO.field_8;
                i_this->field_2BC[1] = l_HIO.field_8 + 90 + REG0_S(2);
                i_this->field_2F8 = 3.0f;
                i_this->field_2FC = 40.0f;
                i_this->field_300 = cM_rndF(20.0f) + 30.0f;
                *i_this->field_314 = 1;
                cXyz particle_scale(0.5f, 0.5f, 0.5f);
                dComIfGp_particle_set(19, &hit_atInfo.mpActor->eyePos, NULL, &particle_scale);
                dComIfGp_particle_set(22, &hit_atInfo.mpActor->eyePos, NULL, &particle_scale);
            }
        }
    }
}

/* 000021EC-0000225C       .text daShand_Execute__FP11shand_class */
static BOOL daShand_Execute(shand_class* i_this) {
    i_this->mExecuteCount++;
    
    
    for(int i = 4, j = 0; i != 0; i--, j++){
        if(i_this->field_2BC[j] != 0)
            i_this->field_2BC[j]--;    
    }

    if(i_this->field_2C4 != 0)
        i_this->field_2C4--;

    hand_move(i_this);

    return TRUE;
}

/* 0000225C-00002264       .text daShand_IsDelete__FP11shand_class */
static BOOL daShand_IsDelete(shand_class*) {
    return TRUE;
}

/* 00002264-000022D4       .text daShand_Delete__FP11shand_class */
static BOOL daShand_Delete(shand_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Shand");
    if(i_this->mHasHIO){
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }

    return TRUE;
}

/* 000022D4-00002360       .text useHeapInit__FP11shand_class */
static BOOL useHeapInit(shand_class* i_this) {
    int bti_idx;
    if ((fopAcM_GetParam(i_this) & 0xff) == 53) {
        bti_idx = SHAND_BTI_VHLIF_VINE;
    } else {
        bti_idx = SHAND_BTI_SHAND;
    }
    ResTIMG* img = static_cast<ResTIMG*>(dComIfG_getObjectRes("Shand", bti_idx));
    
    if(i_this->mLineMat.init(1, 20, img, TRUE) == FALSE){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

/* 00002360-00002380       .text daShand_solidHeapCB__FP10fopAc_ac_c */
static BOOL daShand_solidHeapCB(fopAc_ac_c* i_this) {
    return useHeapInit(static_cast<shand_class*>(i_this));
}

/* 00002380-00002630       .text daShand_Create__FP10fopAc_ac_c */
static cPhs_State daShand_Create(fopAc_ac_c* i_this) {
    static dCcD_SrcCyl tg_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 200.0f,
        }},
    };

    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    shand_class* s_this = static_cast<shand_class*>(i_this);
    fopAcM_SetupActor(i_this, shand_class);

    cPhs_State ret = dComIfG_resLoad(&s_this->mPhs, "Shand");
    if(ret == cPhs_COMPLEATE_e){
        if(fopAcM_entrySolidHeap(i_this, daShand_solidHeapCB, 0x1040) != false){
            i_this->health = 2;
            s_this->mExecuteCount = cM_rndF(10000.0f);
            s_this->field_318 = 10;
            s_this->field_2BA = 1;
            s_this->field_2F0 = 1.0f;
            if((fopAcM_GetParam(i_this) & 0xff) == 1)
                s_this->field_304 = 15.75f;
            else
                s_this->field_304 = 10.5f;
            s_this->mStts.Init(0xff, 0xff, i_this);
            for(int i = 0; i < 5; i++){
                s_this->mCylArr[i].Set(tg_cyl_src);
                s_this->mCylArr[i].SetStts(&s_this->mStts);
            }
            s_this->mSph.Set(bm_sph_src);
            s_this->mSph.SetStts(&s_this->mStts);
            s_this->field_2C4 = 30;
            for(int i = 0; i < 3; i++){
                daShand_Execute(s_this);
            }
        }
        else {
            ret = cPhs_ERROR_e;
        }

        if(hio_set == false){
            hio_set = true;
            s_this->mHasHIO = true;
            l_HIO.mNo = mDoHIO_createChild("汎用触手", &l_HIO);
        }
    }

    return ret;
}

static actor_method_class l_daShand_Method = {
    (process_method_func)daShand_Create,
    (process_method_func)daShand_Delete,
    (process_method_func)daShand_Execute,
    (process_method_func)daShand_IsDelete,
    (process_method_func)daShand_Draw,
};

actor_process_profile_definition g_profile_SHAND = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SHAND,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(shand_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SHAND,
    /* Actor SubMtd */ &l_daShand_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
