//
// Generated by dtk
// Translation Unit: d_a_shand.cpp
//

#include "d/actor/d_a_shand.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_s_play.h"

bool hio_set;
daShand_HIO_c l_HIO;

/* 000000EC-00000114       .text __ct__13daShand_HIO_cFv */
daShand_HIO_c::daShand_HIO_c() {
    this->mId = -1;
    this->u6 = -3;
    this->u8 = 50;
}

/* 00000114-00000194       .text hand_draw__FP11shand_class */
void hand_draw(shand_class* actor) {
    GXColor color = {0x50, 0x96, 0x96, 0xff};
    actor->mLineMat.update(0x14, color, &actor->tevStr);
    dComIfGd_set3DlineMat(&actor->mLineMat);
}

/* 00000194-000001E0       .text daShand_Draw__FP11shand_class */
static BOOL daShand_Draw(shand_class* actor) {
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &actor->eyePos, &actor->tevStr);
    hand_draw(actor);
    return TRUE;
}

/* 000001E0-0000052C       .text control1__FP11shand_class */
void control1(shand_class* actor) {
    float fVar_x, fVar_y, fVar_z;

    actor->u31C[0].mPos = actor->current.pos;
    int i = 1;
    shand_s* shand_i = &actor->u31C[i];
    
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);

    cXyz local94, cStack_a0, localac;
    local94.x = 0.0f;
    local94.y = actor->u2F8;
    local94.z = actor->u2FC;
    MtxPosition(&local94, &localac);
    cLib_addCalc2(&actor->u2F8, REG0_F(7), 1.0f, 0.1f);
    cLib_addCalc2(&actor->u2FC, REG0_F(8), 1.0f, 1.0f);
    local94.z = actor->u2F4;
    float fVar1 = actor->u300;
    cXyz idk;
    for(i = 1; i < 19; i++, ++shand_i){
        idk.x = fVar1 * cM_ssin(actor->mExecuteCount * (REG0_S(5) + 1100) + i * (REG0_S(6) + 4000));
        idk.z =  fVar1 * cM_scos(actor->mExecuteCount * (REG0_S(7) + 800) + i * (REG0_S(8) + 4000));
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
void control2(shand_class* actor) {
    cXyz rel_offset, abs_offset;
    rel_offset.x = 0;
    rel_offset.y = 0;
    rel_offset.z = actor->u2F4;

    cLib_addCalc2(&actor->u31C[19].mPos.x, actor->u2D4.x, 1.0, actor->u2F0 * 50.0f);
    cLib_addCalc2(&actor->u31C[19].mPos.y, actor->u2D4.y, 1.0, actor->u2F0 * 50.0f);
    cLib_addCalc2(&actor->u31C[19].mPos.z, actor->u2D4.z, 1.0, actor->u2F0 * 50.0f);
    cLib_addCalc2(&actor->u2F0, 1.0, 1.0, 0.01);

    int i = 18;
    short Yangle;
    int XZangle;
    shand_s* shand_i = &actor->u31C[i];
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
void control3(shand_class* actor) {
    shand_s* shand_i = actor->u31C;
    int counter = 0;
    for(int i = 20; i != 0; i--, counter++, shand_i++){
        if(counter < 12){
            shand_i->u18 = actor->u304;
        }
        else {
            shand_i->u18 = actor->u304 * (1.0f - (counter + -10) * 0.05f);
        }
    }
}

/* 000007C4-00000BAC       .text cut_control__FP11shand_class */
void cut_control(shand_class* actor) {
    actor->u31C[0].mPos = actor->current.pos;
    int i = 1;
    shand_s *shand_i = &actor->u31C[i];

    cXyz local_b8, cStack_c4, local_d0;
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_b8.x = 0.0f;
    local_b8.y = actor->u2F8;
    local_b8.z = actor->u2FC;
    MtxPosition(&local_b8, &local_d0);
    cLib_addCalc2(&actor->u2F8, REG14_F(7) + -5.0f, 1.0f, REG12_F(4) + 0.1f);
    cLib_addCalc2(&actor->u2FC, REG14_F(8) + 20.0f, 1.0f, REG14_F(5) + 0.2f);
    cLib_addCalc0(&actor->u300, 1.0f, REG12_F(6) + 1.0f);
    local_b8.z = actor->u2F4;
    cXyz d0_scaled, local_e8;
    float fVar_x, fVar_y, fVar_z, delta_y;
    for(i = 1; i < 20; i++, shand_i++){
        local_e8.x = actor->u300 * cM_ssin(actor->mExecuteCount * (REG0_S(4) + 3500) + i * (REG0_S(5) + 4000));
        local_e8.y = actor->u300 * cM_scos(actor->mExecuteCount * (REG0_S(6) + 4000) + i * (REG0_S(7) + 4000));
        local_e8.z = actor->u300 * cM_scos(actor->mExecuteCount * (REG0_S(8) + 3800) + i * (REG0_S(9) + 4000));
        
        float factor = 1.0f - i * (REG0_F(9) + 0.03763158f);
        d0_scaled.x = local_d0.x * factor;
        d0_scaled.z = local_d0.z * factor;
        
        fVar_x = shand_i->mPos.x - shand_i[-1].mPos.x + d0_scaled.x + local_e8.x;
        fVar_y = shand_i->mPos.y + local_d0.y + local_e8.y;
        if (fVar_y < actor->uCE0) fVar_y = actor->uCE0;
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
void cut_control3(shand_class* actor) {
    shand_s* shand_i = actor->u31C;
    int counter = 0;
    for(int i = 20; i != 0; i--, counter++, shand_i++){
        if(counter < 12){
            shand_i->u18 = actor->u304;
        }
        else {
            shand_i->u18 = actor->u304 * (1.0f - (counter - 10) * 0.08f);
        }
    }
}

/* 00000C30-00000FF0       .text normal__FP11shand_class */
void normal(shand_class* actor) {
    cXyz unused, chk_start, chk_end;

    unused.x = unused.y = 0;
    if(actor->u318 != 0){
        dBgS_LinChk local94;
        chk_end = chk_start = actor->current.pos;
        chk_start.y = chk_end.y + 50.0f;
        chk_end.y += 4000.0f;
        local94.Set(&chk_start, &chk_end, actor);
        if(dComIfG_Bgsp()->LineCross(&local94) != false){
            actor->u2C8 = local94.GetLinP()->GetStart();
            actor->u2D4 = local94.GetCross();
            actor->u31C[19].mPos = actor->u2D4;
        };
        actor->u318--;
    }

    switch(actor->u2BA){
        case 0:
            if(std::abs(actor->u31C[19].mPos.y - actor->u2D4.y) < 10.0f){
                actor->u2BA = 1;
                *actor->u314 = 2;
            }
        case 1:
            actor->u2D4.set(actor->u2C8);
    }

    cLib_addCalc2(&actor->u2F4, std::abs(actor->home.pos.y - actor->u2C8.y) * (REG14_F(11) + 0.05f), 0.1f, 1.0f);
    cLib_addCalc2(&actor->u300, REG14_F(12) + 10.0f, 0.1f, 0.5f);
    control1(actor);
    control2(actor);
    control3(actor);
}

/* 00001428-00001508       .text cut__FP11shand_class */
void cut(shand_class* actor) {
    cLib_addCalc2(&actor->u2F4, REG8_F(12) + 20.0f, 0.1f, 0.5f);
    cut_control(actor);
    cut_control3(actor);
    if(actor->u2BC[0] == 0 && actor->u30C->health != 0){
        actor->mState = 0;
        actor->u2BA = 0;
        actor->u2F0 = 0.0f;
        actor->u300 = 0.0f;
        fopAcM_seStart(actor, JA_SE_OBJ_VINE_S_RECOVER, 0);
    }
}

/* 00001508-00001DAC       .text hand_move__FP11shand_class */
void hand_move(shand_class* actor) {
    shand_s* shand_i = actor->u31C;
    
    actor->u30C = static_cast<shand_class*>(fopAcM_SearchByID(actor->u308));
    if(actor->u30C != NULL){
        actor->current.pos = *actor->u310;
        actor->current.angle.y = actor->home.angle.y + actor->u30C->shape_angle.y + REG14_S(3);
        switch(actor->mState){
            case 0:
                normal(actor);
                actor->attention_info.flags = fopAc_Attn_LOCKON_MISC_e;
                if(actor->u30C->health == 0){
                    actor->mState = 1;
                    actor->u2BA = 0;
                }
                break;

            case 1: 
                if((fopAcM_GetParam(actor) & 0xFF) != 1){
                    dBgS_GndChk local_ac;
                    float chk_pos_x = actor->current.pos.x, chk_pos_y = actor->current.pos.y, chk_pos_z = actor->current.pos.z;
                    chk_pos_y -= 100.0f;
                    local_ac.m_pos.set(chk_pos_x, chk_pos_y, chk_pos_z);
                    actor->uCE0 = dComIfG_Bgsp()->GroundCross(&local_ac);
                    
                    dBgS_ObjGndChk_Spl local_100;
                    chk_pos_x = actor->current.pos.x; chk_pos_y = actor->current.pos.y; chk_pos_z = actor->current.pos.z;
                    chk_pos_y += 200.0f;
                    local_100.m_pos.set(chk_pos_x, chk_pos_y, chk_pos_z);
                    float gnd_cross = dComIfG_Bgsp()->GroundCross(&local_100) + 10.0f;
                    if(gnd_cross != -1e09f){
                        actor->uCE0 = gnd_cross;
                    }
                }
                else {
                    actor->uCE0 = -1e9f;
                }
                actor->mState = 2;

            case 2:
                cut(actor);
                fopAcM_OffStatus(actor, 0);
                actor->attention_info.flags = 0;
                break;
        }
    }

    mDoExt_3Dline_c* lines = actor->mLineMat.mpLines;
    cXyz* line_data = lines->mpSegments;
    u8* line_size = lines->mpSize;
    for(int i = 20; i != 0; i--){
        *line_data = shand_i->mPos;
        *line_size = shand_i->u18;

        shand_i++; line_data++; line_size++;
    }

    cXyz* line_segments = actor->mLineMat.mpLines->mpSegments;
    actor->eyePos = (line_segments + l_HIO.u6)[10]; // Have not found any "clean" way to write that
    actor->attention_info.position = actor->eyePos;
    
    CcAtInfo hit_atInfo;
    hit_atInfo.pParticlePos = NULL;
    bool is_hit = false;
    if(actor->u2BC[1] == 0 && actor->mState == 0){
        actor->mSph.SetC(actor->eyePos);
        actor->mCylArr[0].SetC(actor->current.pos);
        for(int i = 0; i < 5; i++){
            if(actor->u2C4 == 0 && actor->mCylArr[i].ChkTgHit() != 0){
                hit_atInfo.mpObj = actor->mCylArr[i].GetTgHitObj();
                hit_atInfo.pParticlePos = actor->mCylArr[i].GetTgHitPosP();
                is_hit = true;
                break;
            }

            if(i > 0){
                cXyz center = line_segments[((actor->mExecuteCount & 0b11) + (i * 4)) % 20];
                center.y -= 200.0f;
                actor->mCylArr[i].SetC(center);   
            }
        }
    }
    else {
        cXyz local_128(0.0f, -20000.0f, 0.0f);
        actor->mSph.SetC(local_128);
        for(int i = 0; i < 5; i++){
            actor->mCylArr[i].SetC(local_128);
        }
    }

    dComIfG_Ccsp()->Set(&actor->mSph);
    for(int i = 0; i < 5; i++){
        dComIfG_Ccsp()->Set(&actor->mCylArr[i]);
    }
    
    if(is_hit || (actor->u2C4 == 0 && actor->mSph.ChkTgHit() != 0)){
        if(!is_hit){
            hit_atInfo.mpObj = actor->mSph.GetTgHitObj();
            hit_atInfo.pParticlePos = actor->mSph.GetTgHitPosP();
        }
        hit_atInfo.mpActor = at_power_check(&hit_atInfo);
        actor->u2C4 = 10;
        if(hit_atInfo.mpActor != NULL){
            def_se_set(actor, hit_atInfo.mpObj, 33);
            if(actor->u30C != NULL){
                actor->mState = 1;
                actor->u2BA = 0;
                actor->u2BC[0] = l_HIO.u8;
                actor->u2BC[1] = l_HIO.u8 + 90 + REG0_S(2);
                actor->u2F8 = 3.0f;
                actor->u2FC = 40.0f;
                actor->u300 = cM_rndF(20.0f) + 30.0f;
                *actor->u314 = 1;
                cXyz particle_scale(0.5f, 0.5f, 0.5f);
                dComIfGp_particle_set(19, &hit_atInfo.mpActor->eyePos, NULL, &particle_scale);
                dComIfGp_particle_set(22, &hit_atInfo.mpActor->eyePos, NULL, &particle_scale);
            }
        }
    }
}

/* 000021EC-0000225C       .text daShand_Execute__FP11shand_class */
static BOOL daShand_Execute(shand_class* actor) {
    actor->mExecuteCount++;
    
    
    for(int i = 4, j = 0; i != 0; i--, j++){
        if(actor->u2BC[j] != 0)
            actor->u2BC[j]--;    
    }

    if(actor->u2C4 != 0)
        actor->u2C4--;

    hand_move(actor);

    return TRUE;
}

/* 0000225C-00002264       .text daShand_IsDelete__FP11shand_class */
static BOOL daShand_IsDelete(shand_class*) {
    return TRUE;
}

/* 00002264-000022D4       .text daShand_Delete__FP11shand_class */
static BOOL daShand_Delete(shand_class* actor) {
    dComIfG_resDelete(&actor->mPhs, "Shand");
    if(actor->mHasHIO){
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mId);
    }

    return TRUE;
}

/* 000022D4-00002360       .text useHeapInit__FP11shand_class */
static BOOL useHeapInit(shand_class* actor) {
    const int res_index = ((fopAcM_GetParam(actor) & 0xff) == 53) + 3;
    ResTIMG* res = static_cast<ResTIMG*>(dComIfG_getObjectRes("Shand", res_index));
    int ret;
    if(actor->mLineMat.init(1, 20, res, 1) != 0){
        ret = TRUE;
    }
    else {
        ret = FALSE;
    }

    return ret;
}

/* 00002360-00002380       .text daShand_solidHeapCB__FP10fopAc_ac_c */
static BOOL daShand_solidHeapCB(fopAc_ac_c* actor) {
    return useHeapInit(static_cast<shand_class*>(actor));
}

/* 00002380-00002630       .text daShand_Create__FP10fopAc_ac_c */
static s32 daShand_Create(fopAc_ac_c* f_this) {
    static dCcD_SrcCyl tg_src_cyl = {
        0,
        0, 
        0,
        0,
        AT_TYPE_ALL - (AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT), // 0xff1dfeff 
        cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e, 
        0, 
        0, 
        0,
        0,
        0,
        0,
        0,
        0,
        0, 
        0,
        0,
        0,
        0,
        0,
        15.0f, 
        200.0f
    };

    static dCcD_SrcSph bm_sph_src = {
        0,
        0,
        0,
        0,
        AT_TYPE_ALL - (AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT), 
        cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e, 
        0, 
        0, 
        0,
        0,
        0,
        0,
        0,
        0,
        0, 
        0,
        0,
        0,
        0,
        0,
        80.0f
    };

    fopAcM_SetupActor(f_this, shand_class);
    shand_class* s_this = static_cast<shand_class*>(f_this);
    int ret = dComIfG_resLoad(&s_this->mPhs, "Shand");
    if(ret == cPhs_COMPLEATE_e){
        if(fopAcM_entrySolidHeap(s_this, daShand_solidHeapCB, 0x1040) != false){
            s_this->health = 2;
            s_this->mExecuteCount = cM_rndF(10000.0f);
            s_this->u318 = 10;
            s_this->u2BA = 1;
            s_this->u2F0 = 1.0f;
            if((fopAcM_GetParam(s_this) & 0xff) == true)
                s_this->u304 = 15.75f;
            else
                s_this->u304 = 10.5f;
            s_this->mStts.Init(0xff, 0xff, s_this);
            for(int i = 0; i < 5; i++){
                s_this->mCylArr[i].Set(tg_src_cyl);
                s_this->mCylArr[i].SetStts(&s_this->mStts);
            }
            s_this->mSph.Set(bm_sph_src);
            s_this->mSph.SetStts(&s_this->mStts);
            s_this->u2C4 = 30;
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
            l_HIO.mId = mDoHIO_createChild("\x94\xc4\x97\x70\x90\x47\x8e\xe8", &l_HIO);
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
    /* Priority     */ 0x0095,
    /* Actor SubMtd */ &l_daShand_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
