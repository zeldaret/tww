/**
 * d_a_obj_pirateship.cpp
 * Object - Pirate Ship
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_pirateship.h"
#include "d/actor/d_a_knob00.h"
#include "d/res/res_kaizokusen.h"
#include "d/d_procname.h"
#include "d/d_particle.h"
#include "d/d_priority.h"
#include "d/d_path.h"
#include "d/d_lib.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

class daObjPirateShipHIO_c : public JORReflexible {
public:
    daObjPirateShipHIO_c() {
        mNo = -1;
        m08 = 2.0f;
        m0C = 100.0f;
        m05 = 0;
        m06 = 0;
        m10 = 250;
        m12 = 500;
        m14 = 0;
        m18 = cXyz::Zero;
        m24 = 4.0f;
        m28 = -0.02f;
        m2C = 5.0f;
        m30 = 300.0f;
        m34 = 3.0f;
        m38 = 17.0f;
    }
    virtual ~daObjPirateShipHIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ s16 m06;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ s16 m10;
    /* 0x12 */ s16 m12;
    /* 0x14 */ s8 m14;
    /* 0x18 */ cXyz m18;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
}; // size = 0x3C

static daObjPirateShipHIO_c l_HIO;

namespace daObjPirateship {
daObjPirateship::Act_c::PirateOffset daObjPirateship::Act_c::p_offset[] = {
    {
        "P2a",
        0xFFFFFF00,
        {135.5f, 2200.0f, 198.0f},
        {0, 0x2900, 0},
        0,
    },
    {
        "P2c",
        0xFFFFFF02,
        {275.0f, 400.0f, 216.0f},
        {0, 0x4D00, 0},
        02,
    },
    {
        "P1b",
        0xF0100000,
        {-150.0f, 700.0f, 950.0f},
        {0, 0x4000, 0},
        01,
    },
    {
        "P1a",
        0xF0000000,
        {150.0f, 700.0f, 950.0f},
        {0, 0xC000, 0},
        00,
    },
    {
        "Zl1",
        0xFFFFFF04,
        {-200.0f, 680.0f, -875.0f},
        {0, 0, 0},
        0xFF,
    },
    {
        "P1b",
        0xF0100002,
        {163.0f, 700.0f, 822.0f},
        {0, 0xC000, 0},
        01,
    },
    {
        "P1a",
        0xF0000002,
        {0.0f, 750.0f, -860.0f},
        {0, 0, 0},
        00,
    },
    {
        "Zl1",
        0xFFFFFF03,
        {125.0f, 2200.0f, 100.0f},
        {0, 0, 0},
        0xFF,
    },
    {
        "P2a",
        0xFFFFFF00,
        {-200.0f, 680.0f, -875.0f},
        {0, 0, 0},
        00,
    },
    {
        "P1b",
        0xF0100003,
        {215.0f, 700.0f, 765.0f},
        {0, 0x3C00, 0},
        01,
    },
    {
        "P1a",
        0xF0000003,
        {275.0f, 740.0f, -1145.0f},
        {0, 0x1800, 0},
        00,
    },
};
static int create_idx_tbl_1stIsland[] = {0, 1, 2, 3, -1};
static int create_idx_tbl_1stIsland_demo[] = {2, -1};
static int create_idx_tbl_umikz[] = {0, 1, 4, 5, 6, -1};
static int create_idx_tbl_arriveMj[] = {1, 7, 8, 9, 10, -1};
static int create_idx_tbl_Yuukaigo[] = {0, 1, 5, -1};
} // namespace daObjPirateship

/* 000000EC-000000FC       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c* arg2) {
    fopAcM_OffStatus(arg2, fopAcStts_NOCULLEXEC_e);
}

/* 000000FC-00000220       .text path_move_call_back__FP4cXyzP4cXyzP4cXyzPv */
int path_move_call_back(cXyz* arg0, cXyz* arg1, cXyz* arg2, void* v_this) {
    daObjPirateship::Act_c* i_this = (daObjPirateship::Act_c*)v_this;

    cXyz sp2C(arg1->x, i_this->current.pos.y, arg1->z);
    cXyz sp20(arg2->x, i_this->current.pos.y, arg2->z);
    cXyz sp14 = sp20 - sp2C;
    if (!sp14.normalizeRS()) {
        return TRUE;
    }

    s16 uVar2 = cLib_addCalcAngleS(&i_this->current.angle.y, cM_atan2s(sp14.x, sp14.z), 0x40, 0x40, 8);
    i_this->shape_angle.y = i_this->current.angle.y;

    f32 tmp = std::fabsf(cM_scos(uVar2)) * (l_HIO.m08 + 5.0f);
    if (cLib_chasePos(arg0, sp20, tmp)) {
        return TRUE;
    }
    return FALSE;
}

const char daObjPirateship::Act_c::mArcname[] = "Kaizokusen";

/* 0000025C-000003B0       .text set_mtx__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::set_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    if (m304 != NULL) {
        static cXyz offset(0.0f, 400.0f, 475.0f);

        cXyz sp0C;
        daKnob00_c* knob = m304;
        mDoMtx_stack_c::copy(mModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&offset, &sp0C);
        knob->setPosAndAngle(&sp0C, shape_angle.y - -0x8000);
    } else {
        m304 = (daKnob00_c*)fopAcM_SearchByID(m308);
    }
}

/* 000003B0-00000448       .text pirateCreate__Q215daObjPirateship5Act_cFPi */
void daObjPirateship::Act_c::pirateCreate(int* arg1) {
    m2CD = 1;
    while (*arg1 != -1) {
        fopAcM_createChildFromOffset(
            p_offset[*arg1].name,
            fopAcM_GetID(this),
            p_offset[*arg1].params,
            (cXyz*)&p_offset[*arg1].pos,
            tevStr.mRoomNo,
            (csXyz*)&p_offset[*arg1].angle,
            NULL,
            NULL
        );
        arg1++;
    }
}

/* 00000448-00000814       .text partsCreate__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::partsCreate() {
    static u32 dr_prm[] = {0x101000FF, 0x101004FF};

    u8 uVar2 = fopAcM_GetParam(this) >> 0x18;
    m_sail_id = fopAcM_createChild("Psail", fopAcM_GetID(this), 0, &current.pos, tevStr.mRoomNo, &current.angle);
    JUT_ASSERT(DEMO_SELECT(282, 282), (m_sail_id != fpcM_ERROR_PROCESS_ID_e));

    m2F0 = fopAcM_createChild(PROC_PIRATE_FLAG, fopAcM_GetID(this), 0, &current.pos, tevStr.mRoomNo, &current.angle);

    if (uVar2 != 3) {
        cXyz sp30 = current.pos;
        sp30.y += 700.0f;
        sp30.x += cM_ssin(current.angle.y) * 850.0f;
        sp30.z += cM_scos(current.angle.y) * 850.0f;
        m2F8 = fopAcM_createChild(PROC_Obj_Tousekiki, fopAcM_GetID(this), 0, &sp30, tevStr.mRoomNo, &current.angle);
    }

    if (uVar2 != 3) {
        cXyz sp24 = current.pos;
        sp24.y += 838.0f;
        sp24.x += cM_ssin(current.angle.y) * -788.0f;
        sp24.z += cM_scos(current.angle.y) * -788.0f;

        m300 = fopAcM_createChild(PROC_Kaji, fopAcM_GetID(this), 0, &sp24, tevStr.mRoomNo, &current.angle);
    }

    cXyz sp18 = current.pos;
    csXyz sp10(0xFFF, current.angle.y - -0x8000, 0);
    s32 uVar3 = (fopAcM_GetParam(this) >> 8) & 0xff;

    s16 sVar6 = 0;
    if (dComIfGs_isEventBit(0x520)) {
        sVar6 = 0x1B18;
    }
    sp10.z = sVar6;

    sp18.y += 400.0f;
    sp18.x += cM_ssin(current.angle.y) * 475.0f;
    sp18.z += cM_scos(current.angle.y) * 475.0f;

    m308 = fopAcM_createChild(PROC_KNOB00, fopAcM_GetID(this), dr_prm[uVar3], &sp18, tevStr.mRoomNo, &sp10);
    m304 = NULL;
}

/* 00000814-0000095C       .text sound_proc__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::sound_proc() {
    if (m2CC == 1) {
        mDoMtx_stack_c::copy(mModel->getBaseTRMtx());
        if (strcmp(dComIfGp_getStartStageName(), "A_umikz") == 0) {
            cXyz sp14(0.0f, 800.0f, 2000.0f);
            mDoMtx_stack_c::multVec(&sp14, &m30C);
            mDoAud_seStart(JA_SE_OBJ_PIRATE_CRUISE, &m30C);
        }

        if (m2CE != 0) {
            cXyz sp08(0.0f, 1500.0f, 300.0f);
            mDoMtx_stack_c::multVec(&sp08, &m318);
            mDoAud_seStart(JA_SE_OBJ_PIRATE_SAIL, &m318);
        }
    }
}

/* 0000095C-00000A50       .text CreateHeap__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(mArcname, KAIZOKUSEN_INDEX_BDL_OBA_KAIZOKU_A);
    JUT_ASSERT(DEMO_SELECT(374, 374), modelData != NULL);

    mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("海賊船", &l_HIO);
    }
    return mModel != NULL;
}

/* 00000A50-00000B9C       .text CreateWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::CreateWave() {
    m6C8 = current.pos;
    if (m4AC.getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(0x8315, &m6C8, &current.angle, NULL, 0, &m4AC);
        JPABaseEmitter* emitter = m4AC.getEmitter();
        if (emitter != NULL) {
            const JGeometry::TVec3<f32> scale = (Vec){20.0f, 20.0f, 20.0f};

            emitter->setGlobalDynamicsScale(scale);
            emitter->setGlobalParticleScale(scale);
        }
    }
#if VERSION > VERSION_JPN
    if (m4FC == NULL)
#endif
    {
        GXColor sea_color;
        dKy_get_seacolor(&m500, &sea_color);
        m4FC = dComIfGp_particle_set(0x833d, &current.pos, &current.angle, NULL, 0xff, NULL, -1, &m500);
    }
}

/* 00000B9C-00000CEC       .text SetWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::SetWave() {
    if (m4AC.getEmitter() != NULL) {
        const JGeometry::TVec3<f32> scale(l_HIO.m24, l_HIO.m24, l_HIO.m24);
        m4AC.getEmitter()->setGlobalScale(scale);

        mDoMtx_stack_c::copy(mModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&l_HIO.m18, &m6C8);

        m4AC.setWaterY(m6C8.y);
        m4AC.setIndirectTexData(l_HIO.m28, l_HIO.m2C);
        m4AC.setSpeed(l_HIO.m30);
        f32 water_y;
        if (m504.ChkWaterHit()) {
            water_y = m504.m_wtr.GetHeight();
        } else {
            water_y = m6C8.y;
        }
        m4AC.setWaterFlatY(water_y);
        m4AC.setLimitSpeed(l_HIO.m34);
        m4AC.getEmitter()->setDirectionalSpeed(l_HIO.m38);
    }

    if (m4FC != NULL) {
        GXColor sea_color;
        dKy_get_seacolor(&m500, &sea_color);
        m4FC->setGlobalPrmColor(m500.r, m500.g, m500.b);

#if VERSION > VERSION_JPN
        m4FC->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
        const JGeometry::TVec3<s16> rot(current.angle.x, current.angle.y, current.angle.z);
        m4FC->setGlobalRotation(rot);
#endif
    }
}

/* 00000CEC-00000D38       .text DeleteWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::DeleteWave() {
    if (m4FC != NULL) {
        m4FC->becomeInvalidEmitter();
        m4FC = NULL;
    }
    m4AC.remove();
}

/* 00000D38-00000DA4       .text Create__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Create() {
    fopAcM_SetMtx(this, mModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -1400.0f, -200.0f, -1800.0f, 1400.0f, 3300.0f, 2200.0f);
    fopAcM_setCullSizeFar(this, 10.0f);
    return TRUE;
}

/* 00000DA4-00000DB4       .text Execute__Q215daObjPirateship5Act_cFPPA3_A4_f */
BOOL daObjPirateship::Act_c::Execute(Mtx** mtx) {
    *mtx = NULL;
    return TRUE;
}

/* 00000DB4-00000E68       .text Draw__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Draw() {
    if (!m2CC) {
        return false;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();
    return true;
}

/* 00000E68-00000E70       .text Delete__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Delete() {
    return TRUE;
}

/* 00000E70-00000EF0       .text demo_move__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::demo_move() {
    dDemo_actor_c* pdVar1 = dComIfGp_demo_getActor(demoActorID);
    if (pdVar1 == NULL) {
        return FALSE;
    }
    dDemo_setDemoData(this, 10, NULL, "Pirates");
    return TRUE;
}

/* 00000EF0-00000F10       .text Create__Q215daObjPirateship6MethodFPv */
cPhs_State daObjPirateship::Method::Create(void* v_this) {
    return ((daObjPirateship::Act_c*)v_this)->_create();
}

/* 000012A4-000017E0       .text _execute__Q215daObjPirateship5Act_cFv */
bool daObjPirateship::Act_c::_execute() {
    dBgS_GndChk gndChk;
    cXyz sp14(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    gndChk.SetPos(&sp14);
    gndChk.OffWall();
    if (dComIfG_Bgsp()->GroundCross(&gndChk) > -G_CM3D_F_INF) {
        s32 roomNo = dComIfG_Bgsp()->GetRoomId(gndChk);
        JUT_ASSERT(VERSION_SELECT(717, 720, 739, 739), 0 <= roomNo && roomNo < 64)
        fopAcM_SetRoomNo(this, roomNo);
    }

    if (!demo_move()) {
        if (l_HIO.m05 == 0 && m4A8 != NULL) {
            dLib_pathMove(&current.pos, &m4A4, m4A8, 3.0f, path_move_call_back, (void*)this);
            if (m32E > 0x4000 || m32E < -0x4000) {
                cLib_addCalcAngleS2(&m330, l_HIO.m12, 0x10, 0x300);
            } else {
                cLib_addCalcAngleS2(&m330, l_HIO.m10, 0x10, 0x300);
            }
            m32E += m330;
            current.pos.y = home.pos.y + (l_HIO.m0C + 10.0f) * cM_ssin(m32E);
        }
        m2CA = l_HIO.m06;
    }

    if (m2CC == 0) {
        if (dComIfGs_isEventBit(0x310)) {
#if VERSION > VERSION_JPN
            if (!dComIfGs_isEventBit(1)) {
                CreateWave();
            }
#endif
            m2CC = 1;
        } else {
            return false;
        }
    } else if (m2CD == 0 && dComIfGs_isEventBit(1)) {
        m2CD = 1;
        pirateCreate(create_idx_tbl_1stIsland_demo);
#if VERSION > VERSION_JPN
        DeleteWave();
#endif
    }

    m2E4 = NULL;
    m2E4 = fopAcM_SearchByID(m_sail_id);
    m2EC = NULL;
    m2EC = fopAcM_SearchByID(m2F0);
    m2FC = NULL;
    m2FC = fopAcM_SearchByID(m300);
    set_mtx();
    sound_proc();
    SetWave();
    return MoveBGExecute() != FALSE;
}

/* 00000F10-000012A4       .text _create__Q215daObjPirateship5Act_cFv */
cPhs_State daObjPirateship::Act_c::_create() {
    fopAcM_SetupActor(this, daObjPirateship::Act_c);

    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, mArcname);
    if (PVar1 == cPhs_COMPLEATE_e) {
        s32 dzbFileIndex = KAIZOKUSEN_INDEX_DZB_ROOM1A;
        if (strcmp(dComIfGp_getStartStageName(), "sea") == 0) {
            dzbFileIndex = KAIZOKUSEN_INDEX_DZB_ROOM1B;
        }
        PVar1 = MoveBGCreate(mArcname, dzbFileIndex, dBgS_MoveBGProc_TypicalRotY, 0x7500);
        mpBgW->SetRideCallback(ride_call_back);
        if (fopAcM_GetParam(this) & 0xF) {
            m2CE = 1;
        } else {
            m2CE = 0;
        }

        partsCreate();
        u8 uVar3 = (fopAcM_GetParam(this) >> 0x18) & 0xFF;
        m4FC = NULL;

        switch (uVar3) {
        case 0:
            if (dComIfGs_isEventBit(0x310) == 0) {
                m2CC = 0;
                m2CD = 0;
            } else {
                m2CC = 0;
                if (dComIfGs_isEventBit(1)) {
                    pirateCreate(create_idx_tbl_1stIsland);
                    m2CD = 1;
                } else {
                    m2CD = 0;
                }
            }
            break;

        case 1:
            pirateCreate(create_idx_tbl_umikz);
            m2CD = 1;
            m2CC = 1;
            CreateWave();
            break;

        case 2:
            if (dComIfGp_getStartStagePoint() == 0x12) {
                pirateCreate(create_idx_tbl_arriveMj);
            }
            m2CD = 1;
            m2CC = 1;
            break;

        case 3:
            m2CD = 1;
            m2CC = 1;
            break;

        case 4:
            pirateCreate(create_idx_tbl_Yuukaigo);
            m2CD = 1;
            m2CC = 1;
            break;

        default:
            m2CD = 1;
            m2CC = 1;
            break;
        }

        m4A8 = 0;
        m4A4 = 0;
        uVar3 = (fopAcM_GetParam(this) >> 0x10) & 0xFF;
        if (uVar3 != 0xff) {
            m4A8 = dPath_GetRoomPath(uVar3, fopAcM_GetRoomNo(this));
        }
        m32E = 0;
        m330 = 0x180;
        set_mtx();
        _execute();
    }
    return PVar1;
}

bool daObjPirateship::Act_c::_delete() {
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    DeleteWave();
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&m30C);
    mDoAud_seDeleteObject(&m318);
#endif
    BOOL iVar1 = MoveBGDelete();
    dComIfG_deleteObjectRes(mArcname);
    if (iVar1) {
        return true;
    }
    return false;
}

bool daObjPirateship::Act_c::_draw() {
    return MoveBGDraw();
}

/* 00001E8C-00001F50       .text Delete__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Delete(void* v_this) {
    return ((daObjPirateship::Act_c*)v_this)->_delete();
}

/* 00001F50-00001F74       .text Execute__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Execute(void* v_this) {
    return ((daObjPirateship::Act_c*)v_this)->_execute();
}

/* 00001F74-00001FAC       .text Draw__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Draw(void* v_this) {
    return ((daObjPirateship::Act_c*)v_this)->_draw();
}

/* 00001FAC-00001FB4       .text IsDelete__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::IsDelete(void*) {
    return TRUE;
}

actor_method_class daObjPirateship::Method::Table = {
    (process_method_func)daObjPirateship::Method::Create,
    (process_method_func)daObjPirateship::Method::Delete,
    (process_method_func)daObjPirateship::Method::Execute,
    (process_method_func)daObjPirateship::Method::IsDelete,
    (process_method_func)daObjPirateship::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Pirateship = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Pirateship,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjPirateship::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Pirateship,
    /* Actor SubMtd */ &daObjPirateship::Method::Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
