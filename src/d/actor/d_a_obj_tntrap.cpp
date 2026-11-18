/**
 * d_a_obj_tntrap.cpp
 * Object - Thunder trap
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_tntrap.h"
#include "d/actor/d_a_ship.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/TnTrap.h"

namespace {
static const char l_arcname[] = "TnTrap";

static const dCcD_SrcTri l_tri_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKB,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGTriS
    {{
        /* a */ {0.0f, 0.0f, 0.0f},
        /* b */ {0.0f, 0.0f, 0.0f},
        /* c */ {0.0f, 0.0f, 0.0f},
    }},
};

static const Vec l_tri_vtx[] = {
    {300.0f, -70.0f, 0.0f},
    {-300.0f, -70.0f, 0.0f},
    {-300.0f, 55.0f, 0.0f},
    {300.0f, 55.0f, 0.0f},
    {300.0f, 180.0f, 0.0f},
    {-300.0f, 180.0f, 0.0f},
};

static const Vec l_offset_ball[] = {
    {-300.0f, 90.0f, 0.0f},
    {300.0f, 90.0f, 0.0f},
};

static const Vec l_offset_thunder[] = {
    {0.0f, 25.0f, 0.0f},
    {0.0f, 85.0f, 0.0f},
    {0.0f, 145.0f, 0.0f},
};
}; // namespace

/* 00000078-000002AC       .text chk_appear__13daObjTnTrap_cFv */
bool daObjTnTrap_c::chk_appear() {
    bool ret = false;
    mSwSave = param_get_swSave();
    mSwSave2 = param_get_swSave2();
    mArg0 = param_get_arg0();
    mMapType = param_get_mapType();
    switch (mMapType) {
    case 0:
        if (dComIfGs_isEventBit(0x3A04) == TRUE) {
            if (mSwSave != 0xFF && fopAcM_isSwitch(this, mSwSave) == TRUE) {
                if (dComIfGs_getTriforceNum() == 8 && mArg0 == 0) {
                    if (dComIfGs_isEventBit(0x2C01) == TRUE) {
                        if (mSwSave2 != 0xFF && fopAcM_isSwitch(this, mSwSave2) == FALSE) {
                            mType = 2;
                            ret = true;
                        }
                    } else {
                        mType = 1;
                        ret = true;
                    }
                }
            } else {
                mType = 0;
                ret = true;
            }
        }
        break;
    case 1:
        if (mSwSave != 0xFF && fopAcM_isSwitch(this, mSwSave) == FALSE) {
            mType = 3;
            ret = true;
        }
        break;
    case 2:
        if (mSwSave != 0xFF) {
            if (fopAcM_isSwitch(this, mSwSave) == FALSE) {
                mType = 5;
                ret = true;
            }
        } else {
            mType = 5;
            ret = true;
        }
        break;
    default:
        JUT_ASSERT(380, 0);
        break;
    }
    return ret;
}

/* 000002AC-00000344       .text set_mtx__13daObjTnTrap_cFv */
void daObjTnTrap_c::set_mtx() {
    mDoMtx_stack_c::transS(home.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mDoMtx_stack_c::transM(0.0f, -9000.0f, -94.0f);
    mDoMtx_stack_c::scaleM(scale.x, 100.0f, scale.z);
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000344-00000364       .text solidHeapCB__13daObjTnTrap_cFP10fopAc_ac_c */
BOOL daObjTnTrap_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->create_heap();
}

/* 00000364-000003D4       .text create_heap__13daObjTnTrap_cFv */
bool daObjTnTrap_c::create_heap() {
    bool ret = true;
    mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_TNTRAP_DZB_TN_WALL01_e), cBgW::MOVE_BG_e, &mMtx);
    if (mpBgW == NULL) {
        ret = false;
    }
    return ret;
}

/* 000003D4-0000058C       .text particle_set__13daObjTnTrap_cFif */
void daObjTnTrap_c::particle_set(int idx, float offsetY) {
    cXyz trans;
    if (mParticleOn[idx] == 1) {
        if (mOffsetY[idx] != offsetY) {
            particle_delete(idx);
        } else {
            return;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (mpBallEmitter[idx][i] == NULL) {
            trans.set(l_offset_ball[i].x, offsetY + l_offset_ball[i].y, l_offset_ball[i].z);
            mpBallEmitter[idx][i] = dComIfGp_particle_set(0x82EA, &home.pos, &shape_angle);
            mpBallEmitter[idx][i]->setEmitterTranslation((const JGeometry::TVec3<f32>&)trans);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (mpThunderEmitter[idx][i] == NULL) {
            trans.set(l_offset_thunder[i].x, offsetY + l_offset_thunder[i].y, l_offset_thunder[i].z);
            mpThunderEmitter[idx][i] = dComIfGp_particle_set(0x82EB, &home.pos, &shape_angle);
            mpThunderEmitter[idx][i]->setEmitterTranslation((const JGeometry::TVec3<f32>&)trans);
        }
    }
    mOffsetY[idx] = offsetY;
    mParticleOn[idx] = 1;
}

/* 0000058C-00000614       .text particle_delete__13daObjTnTrap_cFi */
void daObjTnTrap_c::particle_delete(int idx) {
    int i;
    if (mParticleOn[idx] == 1) {
        for (i = 0; i < 2; i++) {
            if (mpBallEmitter[idx][i] != NULL) {
                mpBallEmitter[idx][i]->becomeInvalidEmitter();
                mpBallEmitter[idx][i] = NULL;
            }
        }
        for (i = 0; i < 3; i++) {
            if (mpThunderEmitter[idx][i] != NULL) {
                mpThunderEmitter[idx][i]->becomeInvalidEmitter();
                mpThunderEmitter[idx][i] = NULL;
            }
        }
    }
    mParticleOn[idx] = 0;
}

/* 00000614-0000069C       .text set_se__13daObjTnTrap_cFv */
void daObjTnTrap_c::set_se() {
    switch (mAction) {
    case 1:
    case 2:
    case 3:
    case 4:
        mDoAud_seStart(0x6239, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        break;
    }
}

/* 0000069C-000007E4       .text set_tri__13daObjTnTrap_cFi */
void daObjTnTrap_c::set_tri(int idx) {
    static int table_idx[4][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {3, 2, 5},
        {3, 5, 4},
    };

    mDoMtx_stack_c::transS(home.pos.x, home.pos.y + mOffsetY[idx], home.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    for (int i = 0; i < 4; i++) {
        Vec vtx[3];
        for (int j = 0; j < 3; j++) {
            vtx[j] = l_tri_vtx[table_idx[i][j]];
            mDoMtx_stack_c::multVec(&vtx[j], &vtx[j]);
        }
        mTri[idx][i].setPos(&vtx[0], &vtx[1], &vtx[2]);
    }
}

/* 000007E4-00000978       .text chk_event_flg__13daObjTnTrap_cFv */
bool daObjTnTrap_c::chk_event_flg() {
    bool ret = true;
    switch (mType) {
    case 1:
        break;
    case 0:
        if (mSwSave != 0xFF && fopAcM_isSwitch(this, mSwSave) == TRUE) {
            int action = 4;
            if (mArg0 == 0) {
                action = 2;
                dComIfGs_onEventBit(0x3B40);
            }
            setup_action(action);
        }
        break;
    case 2:
        if (mAction == 1) {
            setup_action(2);
        }
        break;
    case 3:
        if (mSwSave != 0xFF && fopAcM_isSwitch(this, mSwSave) == TRUE && dComIfGp_getShipActor() != NULL) {
            dComIfGp_getShipActor()->offStateFlg(daShip_c::daSFLG_UNK800000_e);
            fopAcM_delete(this);
            ret = false;
        }
        break;
    case 5:
        if (mSwSave != 0xFF && fopAcM_isSwitch(this, mSwSave) == TRUE) {
            fopAcM_delete(this);
            ret = false;
        }
        break;
    }
    return ret;
}

/* 00000978-00000A10       .text set_em_set_offsetY__13daObjTnTrap_cFv */
void daObjTnTrap_c::set_em_set_offsetY() {
    if (mType == 5) {
        if (dComIfGp_getPlayer(0) != NULL) {
            mOffsetY[0] = 180.0f * (int)((dComIfGp_getPlayer(0)->eyePos.y - home.pos.y) / 180.0f);
        }
    } else {
        mOffsetY[0] = 0.0f;
    }
}

/* 00000A10-00000C70       .text _create__13daObjTnTrap_cFv */
cPhs_State daObjTnTrap_c::_create() {
    cPhs_State ret = cPhs_ERROR_e;
    fopAcM_ct(this, daObjTnTrap_c);
    if (fopAcM_IsFirstCreating(this)) {
        mAppear = chk_appear();
    }
    if (mAppear == 1) {
        ret = dComIfG_resLoad(&mPhase, l_arcname);
    }
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x2E0)) {
            if (mType != 3 && dComIfG_Bgsp()->Regist(mpBgW, this)) {
                ret = cPhs_ERROR_e;
            } else {
                set_em_set_offsetY();
                set_mtx();
                mStts.Init(0xFF, 0xFF, this);
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 4; j++) {
                        mTri[i][j].Set(l_tri_src);
                        mTri[i][j].SetStts(&mStts);
                    }
                    set_tri(i);
                }
                int action = 0;
                if (mType == 3) {
                    action = 6;
                }
                setup_action(action);
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

/* 00000F50-00000FF4       .text _delete__13daObjTnTrap_cFv */
bool daObjTnTrap_c::_delete() {
    if (mAppear == 1) {
        dComIfG_resDelete(&mPhase, l_arcname);
        if (heap != NULL && mpBgW != NULL) {
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
            mpBgW = NULL;
        }
        for (int i = 0; i < 2; i++) {
            particle_delete(i);
        }
    }
    return true;
}

/* 00000FF4-000010E8       .text trap_off_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::trap_off_wait_act_proc() {
    if (dComIfGp_getPlayer(0) != NULL) {
        if ((dComIfGp_getPlayer(0)->current.pos - home.pos).absXZ() < 500.0f) {
            setup_action(1);
        }
    }
    return chk_event_flg();
}

/* 000010E8-0000132C       .text trap_on_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::trap_on_wait_act_proc() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (player != NULL) {
        if ((player->current.pos - home.pos).absXZ() > 500.0f) {
            setup_action(0);
        } else if (mType == 5) {
            f32 dist[2];
            for (int i = 0; i < 2; i++) {
                dist[i] = player->current.pos.y - (90.0f + (home.pos.y + mOffsetY[i]));
                if (std::fabsf(dist[i]) > 150.0f) {
                    particle_delete(i);
                }
            }
            for (int i = 0; i < 2; i++) {
                if (std::fabsf(dist[i]) > 80.0f) {
                    f32 offsetY;
                    if (dist[i] > 0.0f) {
                        offsetY = 180.0f + mOffsetY[i];
                    } else {
                        offsetY = mOffsetY[i] - 180.0f;
                    }
                    if (std::fabsf(player->current.pos.y - (90.0f + (home.pos.y + offsetY))) <= 150.0f) {
                        particle_set(i ^ 1, offsetY);
                    }
                }
            }
        }
    }
    return chk_event_flg();
}

/* 0000132C-000013E4       .text demo_regist_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::demo_regist_wait_act_proc() {
    if (mEventIdx != -1) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            setup_action(3);
        } else {
            fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
        }
    } else if (mType == 2) {
        mEventIdx = dComIfGp_evmng_getEventIdx("break_tntrap2");
    } else {
        mEventIdx = dComIfGp_evmng_getEventIdx("break_tntrap");
    }
    return TRUE;
}

/* 000013E4-00001478       .text demo_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::demo_wait_act_proc() {
    if (dComIfGp_evmng_existence(mEventIdx)) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("TnTrap");
        if (staffIdx != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "Delete") == 0) {
                setup_action(5);
            }
        }
    }
    return TRUE;
}

/* 00001478-00001534       .text demo_wait2_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::demo_wait2_act_proc() {
    bool ret = true;
    if (dComIfGp_evmng_existence("break_tntrap")) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("TnTrap");
        if (staffIdx != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "Delete2") == 0) {
                fopAcM_delete(this);
                ret = false;
            }
        }
    }
    return ret;
}

/* 00001534-00001614       .text demo_end_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::demo_end_wait_act_proc() {
    bool ret = true;
    if (dComIfGp_evmng_endCheck(mEventIdx)) {
        dComIfGp_event_reset();
        switch (mType) {
        case 1:
            break;
        case 0:
            mDoAud_seStart(0x806);
            break;
        case 2:
            if (mSwSave2 != 0xFF) {
                fopAcM_onSwitch(this, mSwSave2);
            }
            break;
        }
        fopAcM_delete(this);
        ret = false;
    }
    return ret;
}

/* 00001614-000016B8       .text hide_wait_act_proc__13daObjTnTrap_cFv */
bool daObjTnTrap_c::hide_wait_act_proc() {
    if (mSwSave2 != 0xFF && fopAcM_isSwitch(this, mSwSave2) == TRUE && dComIfGp_getShipActor() != NULL) {
        dComIfGp_getShipActor()->onStateFlg(daShip_c::daSFLG_UNK800000_e);
        if (!dComIfG_Bgsp()->Regist(mpBgW, this)) {
            setup_action(0);
        }
    }
    return FALSE;
}

/* 000016B8-000016BC       .text dummy_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::dummy_proc() {
}

/* 000016BC-000016FC       .text trap_off_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::trap_off_wait_act_init_proc() {
    for (int i = 0; i < 2; i++) {
        particle_delete(i);
    }
}

/* 000016FC-00001730       .text trap_on_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::trap_on_wait_act_init_proc() {
    set_em_set_offsetY();
    particle_set(0, mOffsetY[0]);
}

/* 00001730-000017B8       .text demo_regist_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::demo_regist_wait_act_init_proc() {
    mOffsetY[0] = 0.0f;
    particle_set(0, 0.0f);
    if (mType == 2) {
        mEventIdx = dComIfGp_evmng_getEventIdx("break_tntrap2");
    } else {
        mEventIdx = dComIfGp_evmng_getEventIdx("break_tntrap");
    }
}

/* 000017B8-000017E8       .text demo_wait2_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::demo_wait2_act_init_proc() {
    mOffsetY[0] = 0.0f;
    particle_set(0, 0.0f);
}

/* 000017E8-00001828       .text demo_end_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::demo_end_wait_act_init_proc() {
    for (int i = 0; i < 2; i++) {
        particle_delete(i);
    }
}

/* 00001828-00001AC4       .text setup_action__13daObjTnTrap_cFi */
void daObjTnTrap_c::setup_action(int action) {
    static ActProc act_proc[] = {
        &daObjTnTrap_c::trap_off_wait_act_proc,
        &daObjTnTrap_c::trap_on_wait_act_proc,
        &daObjTnTrap_c::demo_regist_wait_act_proc,
        &daObjTnTrap_c::demo_wait_act_proc,
        &daObjTnTrap_c::demo_wait2_act_proc,
        &daObjTnTrap_c::demo_end_wait_act_proc,
        &daObjTnTrap_c::hide_wait_act_proc,
    };
    static InitProc act_init_proc[] = {
        &daObjTnTrap_c::trap_off_wait_act_init_proc,
        &daObjTnTrap_c::trap_on_wait_act_init_proc,
        &daObjTnTrap_c::demo_regist_wait_act_init_proc,
        &daObjTnTrap_c::dummy_proc,
        &daObjTnTrap_c::demo_wait2_act_init_proc,
        &daObjTnTrap_c::demo_end_wait_act_init_proc,
        &daObjTnTrap_c::dummy_proc,
    };

    (this->*act_init_proc[action])();
    mActProc = act_proc[action];
    mAction = action;
}

/* 00001AC4-00001BE8       .text _execute__13daObjTnTrap_cFv */
bool daObjTnTrap_c::_execute() {
    int i, j;
    if (mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    for (i = 0; i < 2; i++) {
        set_tri(i);
    }
    mStts.Move();
    if ((this->*mActProc)() == true) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 4; j++) {
                dComIfG_Ccsp()->Set(&mTri[i][j]);
            }
        }
        set_se();
    }
    return true;
}

/* 00001BE8-00001BF0       .text _draw__13daObjTnTrap_cFv */
bool daObjTnTrap_c::_draw() {
    return true;
}

/* 00001BF0-00001C10       .text daObjTnTrap_Create__FP10fopAc_ac_c */
static cPhs_State daObjTnTrap_Create(fopAc_ac_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_create();
}

/* 00001C10-00001C34       .text daObjTnTrap_Delete__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Delete(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_delete();
}

/* 00001C34-00001C58       .text daObjTnTrap_Execute__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Execute(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_execute();
}

/* 00001C58-00001C7C       .text daObjTnTrap_Draw__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Draw(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_draw();
}

/* 00001C7C-00001C84       .text daObjTnTrap_IsDelete__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_IsDelete(daObjTnTrap_c*) {
    return TRUE;
}

static actor_method_class l_daObjTnTrap_Method = {
    (process_method_func)daObjTnTrap_Create,
    (process_method_func)daObjTnTrap_Delete,
    (process_method_func)daObjTnTrap_Execute,
    (process_method_func)daObjTnTrap_IsDelete,
    (process_method_func)daObjTnTrap_Draw,
};

actor_process_profile_definition g_profile_Obj_TnTrap = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_TnTrap_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTnTrap_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_TnTrap_e,
    /* Actor SubMtd */ &l_daObjTnTrap_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
