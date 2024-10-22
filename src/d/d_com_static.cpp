//
// Generated by dtk
// Translation Unit: d_com_static.cpp
//

#include "dolphin/types.h"
#include "d/d_com_inf_game.h"
#include "d/d_salvage.h"
#include "d/d_procname.h"
#include "d/actor/d_a_lod_bg.h"
#include "d/actor/d_a_agb.h"
#include "d/actor/d_a_agbsw0.h"
#include "d/actor/d_a_npc_kamome.h"
#include "d/actor/d_a_npc_os.h"
#include "d/actor/d_a_npc_md.h"
#include "d/actor/d_a_npc_sarace.h"
#include "d/actor/d_a_canon.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_ib.h"
#include "d/actor/d_a_item.h"
#include "d/actor/d_a_tag_light.h"
#include "d/actor/d_a_obj_movebox.h"
#include "d/actor/d_a_windmill.h"
#include "d/actor/d_a_npc_kg1.h"
#include "d/actor/d_a_npc_kg2.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/actor/d_a_steam_tag.h"
#include "d/actor/d_a_ykgr.h"
#include "d/actor/d_a_tag_kb_item.h"
#include "d/actor/d_a_tag_waterlevel.h"
#include "d/actor/d_a_title.h"
#include "d/actor/d_a_wind_tag.h"
#include "d/actor/d_a_salvage.h"
#include "d/actor/d_a_obj_light.h"
#include "d/actor/d_a_dai.h"
#include "d/actor/d_a_obj_roten.h"
#include "d/actor/d_a_dai_item.h"
#include "d/actor/d_a_npc_ji1.h"
#include "d/actor/d_a_npc_bs1.h"
#include "SSystem/SComponent/c_counter.h"

#include "weak_bss_3569.h" // IWYU pragma: keep

s32 daLodbg_c::sObjectCount;
JKRExpHeap* daLodbg_c::sLocalHeap;

u8 daSteamTag_c::mEmitterNum;

/* 8005662C-80056638       .text init__12daSteamTag_cFv */
void daSteamTag_c::init() {
    mEmitterNum = 0;
}

u8 daYkgr_c::m_flag;
u8 daYkgr_c::m_alpha_flag;
u8 daYkgr_c::m_alpha;
f32 daYkgr_c::m_aim_rate;
dPath* daYkgr_c::m_path;
JPABaseEmitter* daYkgr_c::m_emitter;

/* 80056638-800566F0       .text getShipOffsetY__15daObjPirateshipFPsPsf */
f32 daObjPirateship::getShipOffsetY(s16* param_1, s16* param_2, f32 param_3) {
    if (*param_1 > 0x4000 || *param_1 < -0x4000) {
        cLib_addCalcAngleS2(param_2, 0x280, 0x10, 0x300);
    } else {
        cLib_addCalcAngleS2(param_2, 0x180, 0x10, 0x300);
    }
    *param_1 += *param_2;
    return param_3 * cM_ssin(*param_1);
}

f32 daTagWaterlevel::Act_c::M_now;
daTagWaterlevel::Act_c::State_e daTagWaterlevel::Act_c::M_state;

daAgb_c::daAgb_Flags daAgb_c::mFlags;
u8 daAgbsw0_c::mFigureDispose;
u8 daAgbsw0_c::mFigureBeat;

/* 800566F0-80056728       .text incTclDispose__10daAgbsw0_cFv */
void daAgbsw0_c::incTclDispose() {
    daAgb_c* agb = dComIfGp_getAgb();
    if (!agb) {
        return;
    }
    if (!agb->isActive()) {
        return;
    }
    if (mFigureDispose >= 2) {
        return;
    }
    mFigureDispose++;
}

/* 80056728-80056760       .text incTclBeat__10daAgbsw0_cFv */
void daAgbsw0_c::incTclBeat() {
    daAgb_c* agb = dComIfGp_getAgb();
    if (!agb) {
        return;
    }
    if (!agb->isActive()) {
        return;
    }
    if (mFigureBeat >= 6) {
        return;
    }
    mFigureBeat++;
}

const f32 daWindTag::daWindTag_c::mData[] = {
    150.0f,
    1000.0f,
    1000.0f,
    7000.0f,
};

const u16 daSalvage_c::m_savelabel[] = {
    0x2080, 0x2004,
    0x2002, 0x2804,
    0x2802, 0x2801,
    0x2980, 0x2940,
    0x3B01, 0x3C80,
    0x3C40, 0x3C20,
    0x3C10, 0x3C08,
    0x3C04, 0x3C02,
};
dSalvage_control_c* daSalvage_c::mTagData_p;
s8 daSalvage_c::mNowRoomNo;
s32 daSalvage_c::mSalvageId;

/* 80056760-80056790       .text init_room__11daSalvage_cFSc */
void daSalvage_c::init_room(s8 roomNo) {
    if (mTagData_p) {
        mTagData_p->init_room(roomNo);
    }
}

s16 daObjLight::Act_c::M_S_light_angle;
u32 daObjLight::Act_c::M_S_pre_set_frame_LOD;
u32 daObjLight::Act_c::M_S_pre_set_frame_FRRS;
u8 daObjLight::Act_c::M_S_lod_access;

/* 80056790-800567F8       .text renew_light_angle__Q210daObjLight5Act_cFv */
bool daObjLight::Act_c::renew_light_angle() {
    M_S_lod_access = 1;
    if (dKy_daynight_check() == 1) {
        if (dComIfGs_isEventBit(0x1C02) == 1) {
            set_light_dif_angle_LOD(get_light_dif_angle() + 0x80);
            return true;
        }
    }
    return false;
}

/* 800567F8-80056824       .text get_light_angle__Q210daObjLight5Act_cFv */
s16 daObjLight::Act_c::get_light_angle() {
    return get_light_dif_angle() + 0xF6C2;
}

/* 80056824-8005682C       .text get_light_dif_angle__Q210daObjLight5Act_cFv */
s16 daObjLight::Act_c::get_light_dif_angle() {
    return M_S_light_angle;
}

/* 8005682C-80056860       .text set_light_dif_angle_LOD__Q210daObjLight5Act_cFs */
BOOL daObjLight::Act_c::set_light_dif_angle_LOD(s16 r3) {
    if (g_Counter.mCounter0 != M_S_pre_set_frame_FRRS) {
        M_S_light_angle = r3;
        M_S_pre_set_frame_LOD = g_Counter.mCounter0;
        return TRUE;
    } else {
        M_S_pre_set_frame_LOD = g_Counter.mCounter0;
        return FALSE;
    }
}

/* 80056860-800568A8       .text set_light_dif_angle_FRRS__Q210daObjLight5Act_cFs */
BOOL daObjLight::Act_c::set_light_dif_angle_FRRS(s16 r3) {
    if (g_Counter.mCounter0 != M_S_pre_set_frame_LOD && g_Counter.mCounter0-1 == M_S_pre_set_frame_FRRS) {
        M_S_light_angle = r3;
        M_S_pre_set_frame_FRRS = g_Counter.mCounter0;
        return TRUE;
    } else {
        M_S_pre_set_frame_FRRS = *(s32*)&g_Counter.mCounter0; // fakematch
        return FALSE;
    }
}

s8 daDai_c::mNowDaizaNum;
s8 daDai_c::mNowItemNum;
const u16 daDai_c::m_savelabel[] = {
    0xF8FF, 0xF7FF,
    0xF6FF, 0xF5FF,
    0xF4FF, 0xF3FF,
    0xF2FF, 0xF1FF,
    0xF0FF, 0xEFFF,
    0xEEFF, 0xEDFF,
    0xECFF, 0xEBFF,
    0xEAFF, 0xE9FF,
    0xE8FF, 0xE7FF,
    0xE6FF, 0xE5FF,
    0xE4FF, 0xE3FF,
    0xE2FF, 0xE1FF,
    0xE0FF, 0xDFFF,
    0xDEFF, 0xDDFF,
    0xDCFF, 0xDBFF,
    0xDAFF, 0xD9FF,
    0xD8FF, 0xD7FF,
    0xD6FF, 0xD5FF,
    0xD4FF, 0xD3FF,
    0xD2FF, 0xD1FF,
};

/* 800568A8-800568B0       .text getMaxDaiza__7daDai_cFv */
int daDai_c::getMaxDaiza() {
    return (u8)mNowDaizaNum; // cast is weird, but it's the only way I've found to match its uses in d_a_npc_people
}

/* 800568B0-800568B8       .text getDaizaSetItemNum__7daDai_cFv */
int daDai_c::getDaizaSetItemNum() {
    return (u8)mNowItemNum; // cast is weird, but it's the only way I've found to match its uses in d_a_npc_people
}

bool daNpc_Os_c::m_playerRoom[3] = { false, false, false };
s8 daNpc_Os_c::m_cattleRoomNo = -1;
dPa_smokeEcallBack daNpc_Os_c::m_smoke(0, 1, 1, 1);
dKy_tevstr_c daNpc_Os_c::m_smoke_tevstr;

bool daNpc_Md_c::m_flying;
bool daNpc_Md_c::m_mirror;
bool daNpc_Md_c::m_seaTalk;
s16 daNpc_Md_c::m_flyingTimer;
bool daNpc_Md_c::m_playerRoom;

/* 800568B8-800568C0       .text getMaxFlyingTimer__10daNpc_Md_cFv */
s16 daNpc_Md_c::getMaxFlyingTimer() {
    return 15*30;
}

s32 daNpc_Sarace_c::ship_race_rupee;
s32 daNpc_Sarace_c::ship_race_result;

daCanon_c* daCanon_c::canon_p;

s8 daNpc_Kg2_c::canon_game_result;
daNpc_Kg2_c* daNpc_Kg2_c::l_kg2_pointer;

u8 daArrow_c::m_keep_type;

/* 800568C0-800568C8       .text getKeepType__9daArrow_cFv */
u8 daArrow_c::getKeepType() {
    return m_keep_type;
}

/* 800568C8-800568D0       .text setKeepType__9daArrow_cFUc */
void daArrow_c::setKeepType(u8 type) {
    m_keep_type = type;
}

u32 daIball_c::m_ib_actor[5];

/* 800568D0-800568F8       .text init__9daIball_cFv */
void daIball_c::init() {
    for (int i = 0; i < ARRAY_SIZE(m_ib_actor); i++) {
        m_ib_actor[i] = fpcM_ERROR_PROCESS_ID_e;
    }
}

/* 800568F8-80056944       .text regist__9daIball_cFP10fopAc_ac_c */
void daIball_c::regist(fopAc_ac_c* i_actor) {
    for (int i = 0; i < ARRAY_SIZE(m_ib_actor); i++) {
        if (m_ib_actor[i] == fpcM_ERROR_PROCESS_ID_e) {
            m_ib_actor[i] = fopAcM_GetID(i_actor);
            break;
        }
    }
}

/* 80056944-80056990       .text remove__9daIball_cFP10fopAc_ac_c */
void daIball_c::remove(fopAc_ac_c* i_actor) {
    for (int i = 0; i < ARRAY_SIZE(m_ib_actor); i++) {
        if (m_ib_actor[i] == fopAcM_GetID(i_actor)) {
            m_ib_actor[i] = fpcM_ERROR_PROCESS_ID_e;
            break;
        }
    }
}

/* 80056990-80056A18       .text remove_old__9daIball_cFv */
void daIball_c::remove_old() {
    u32 iball_id = fpcM_ERROR_PROCESS_ID_e;
    for (int i = 0; i < ARRAY_SIZE(m_ib_actor); i++) {
        if (m_ib_actor[i] == fpcM_ERROR_PROCESS_ID_e) {
            return;
        }
        if (m_ib_actor[i] < iball_id) {
            iball_id = m_ib_actor[i];
        }
    }
    fopAc_ac_c* iball = fopAcM_SearchByID(iball_id);
    if (iball) {
        static_cast<daIball_c*>(iball)->dead();
        remove(iball);
    }
}

/* 80056A18-80056AD0       .text getCreateCount__13daObj_Roten_cFv */
int daObj_Roten_c::getCreateCount() {
    u8 r30 = 0;
    int r29 = 0;
    for (; r30 <= 0xB; r30++) {
        if (dComIfGs_isGetItemReserve(r30)) {
            r29++;
        } else if (r30 == 0) {
            r29++;
        }
    }
    
    if (r29 > 9) {
        return 4;
    } else if (r29 > 6) {
        return 3;
    } else if (r29 > 3) {
        return 2;
    } else {
        return 1;
    }
}

const f32 daTagLight::Act_c::M_box_x_min = -50.0f;
const f32 daTagLight::Act_c::M_box_x_max = 50.0f;
const f32 daTagLight::Act_c::M_box_y_min = 0.0f;
const f32 daTagLight::Act_c::M_box_y_max = 100.0f;
const f32 daTagLight::Act_c::M_box_z_min = -50.0f;
const f32 daTagLight::Act_c::M_box_z_max = 50.0f;
const f32 daTagLight::Act_c::M_cone_lower = 0.0f;
const f32 daTagLight::Act_c::M_cone_upper = 100.0f;
const f32 daTagLight::Act_c::M_cone_r = 50.0f;

const s16 daObjMovebox::Act_c::M_dir_base[4] = {
    0x0000,
    0x4000,
    0x8000,
    0xC000,
};

const s16 daWindMill_c::m_max_rot_speed[] = {
    0x09C4,
    0x09C4,
};

const u8 daNpc_Kg1_c::m_highscore = 20;

/* 80056AD0-80056AFC       .text kb_dig__13daTagKbItem_cFP10fopAc_ac_c */
void daTagKbItem_c::kb_dig(fopAc_ac_c* i_actor) {
    field_0x299 = 1;
    mpActor = i_actor;
    dig_main();
}

/* 80056AFC-80056CC0       .text dig_main__13daTagKbItem_cFv */
void daTagKbItem_c::dig_main() {
#if VERSION != VERSION_JPN
    if (fopAcM_isSwitch(this, field_0x2a4)) {
        return;
    }
#endif
    if (field_0x299 == 0) {
        return;
    }
    if (field_0x298 != 0) {
        return;
    }
    
    cXyz scale = cXyz::Zero;
    csXyz angle = csXyz::Zero;
    bool r30 = false;
    if (!fopAcM_IsActor(mpActor)) {
        return;
    }
    if (fopAcM_GetName(mpActor) != PROC_KB) {
        // Not a pig.
        return;
    }
#if VERSION == VERSION_JPN
    if (field_0x2a0 != 0xFF && field_0x298 == 0) {
#else
    if (field_0x2a0 != 0xFF) {
#endif
        angle.y = cM_rndF((f32)0x7FFE);
        s8 roomNo = current.roomNo;
        daItem_c* item = (daItem_c*)fopAcM_fastCreateItem(
            &mpActor->current.pos, field_0x2a0, roomNo, &angle,
            &scale, cM_rndF(5.0f), 60.0f + cM_rndFX(5.0f), -6.0f, field_0x29c
        );
        if (item) {
            fopAcM_OnStatus(item, fopAcStts_UNK4000_e);
        }
#if VERSION == VERSION_JPN
        fopAcM_delete(this);
#else
        if (field_0x2a4 != 0xFF) {
            fopAcM_onSwitch(this, field_0x2a4);
        } else {
            fopAcM_delete(this);
        }
#endif
        r30 = true;
    }
    
    if (field_0x2a1 != 0xFF) {
        mpActor->home.angle.z = field_0x2a1;
        fopAcM_onSwitch(this, field_0x2a4);
        fopAcM_delete(this);
        r30 = true;
    }
    
    if (r30) {
        field_0x298 = r30;
    }
    field_0x299 = 0;
}

bool daTitle_proc_c::daTitle_Kirakira_Sound_flag = true;

/* 80056CC0-80056CCC       .text daTitle_Kirakira_Sound_flag_on__14daTitle_proc_cFv */
void daTitle_proc_c::daTitle_Kirakira_Sound_flag_on() {
    daTitle_Kirakira_Sound_flag = true;
}

/* 80056CCC-80056DE0       .text daiItemNodeCallBack__13daStandItem_cFP7J3DNodei */
BOOL daStandItem_c::daiItemNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        void* userArea = (void*)model->getUserArea();
        if (userArea && fopAcM_IsActor(userArea) && fopAcM_GetName(userArea) == PROC_STANDITEM) {
            daStandItem_c* i_this = (daStandItem_c*)userArea;
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            switch (i_this->getItemNo()) {
            case 0x92:
                mDoMtx_stack_c::XrotM(i_this->m6B4);
                break;
            case 0x95:
                if (jntNo == 0) {
                    mDoMtx_copy(mDoMtx_stack_c::get(), i_this->m630);
                } else if (jntNo == 1) {
                    mDoMtx_copy(mDoMtx_stack_c::get(), i_this->m660);
                }
                break;
            }
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

s8 daNpc_Ji1_c::game_life_point;

bool daNpc_kam_c::m_hyoi_kamome;

u8 daNpc_Bs1_c::m_tag_buy_item_max;
u8 daNpc_Bs1_c::m_tag_buy_item;
s16 daNpc_Bs1_c::m_tag_pay_rupee;
