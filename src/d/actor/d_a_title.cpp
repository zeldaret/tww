/**
 * d_a_title.cpp
 * Title Screen manager & logo
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_title.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_op/f_op_scene_mng.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_Reset.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "stdio.h"

#if VERSION <= VERSION_JPN
#include "d/res/res_tlogo.h"
#endif
#if VERSION == VERSION_USA
#include "d/res/res_tlogoe.h"
#endif
#if VERSION == VERSION_PAL
#include "d/res/res_tlogoe0.h"
#endif

// Note: For VERSION_PAL the "TlogoE0" string literal is modified at runtime.
#define ARCNAME VERSION_SELECT("Tlogo", "Tlogo", "TlogoE", "TlogoE0")

namespace {
    struct Attr_c {
        /* 0x00 */ f32 field_0x00;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ f32 field_0x0C;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
    };

    // TODO: Figure out magic numbers
    static const Attr_c L_attr = {
        0.0f,
        0.0f,
        0.9f,
        0.1f,
        -57.0f,
#if VERSION <= VERSION_JPN
        -19.0f,
#else
        -3.0f,
#endif
        1.0f,
        1.0f,
        120.0f,
        10.0f,
        120.0f,
        10.0f,
#if VERSION <= VERSION_JPN
        78.0f,
        8.0f,
#else
        85.0f,
        5.0f,
#endif
    };

    inline const Attr_c & attr() { return L_attr; }
}

/* 00000078-00000638       .text proc_init3D__14daTitle_proc_cFv */
void daTitle_proc_c::proc_init3D() {
    m_solid_heap = mDoExt_createSolidHeapFromGameToCurrent(0x40000U, 0x20);

    J3DModelData* modelData_ship = (J3DModelData*)dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BDL_TITLE_SHIP, TLOGO_BDL_TITLE_SHIP, TLOGOE_BDL_TITLE_SHIP, TLOGOE0_BDL_TITLE_SHIP));
    JUT_ASSERT(VERSION_SELECT(0xD1, 0xD1, 0xFC, 0xFC), modelData_ship != NULL);

    mModel_ship = mDoExt_J3DModel__create(modelData_ship, 0x80000U, 0x37441423U);
    JUT_ASSERT(VERSION_SELECT(0xD6, 0xD6, 0x101, 0x101), mModel_ship != NULL);

    J3DModelData* modelData_sub = (J3DModelData*)dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BDL_SUBTITLE_START_ANIM, TLOGO_BDL_SUBTITLE_START_ANIM, TLOGOE_BDL_SUBTITLE_START_ANIM_E, TLOGOE0_BDL_SUBTITLE_START_ANIM_E));
    JUT_ASSERT(VERSION_SELECT(0xDA, 0xDA, 0x105, 0x105), modelData_sub != NULL);

    mModel_subtitle = mDoExt_J3DModel__create(modelData_sub, 0x80000U, 0x37441422U);
    JUT_ASSERT(VERSION_SELECT(0xDF, 0xDF, 0x10A, 0x10A), mModel_subtitle != NULL);

    J3DModelData* modelData_kirari = (J3DModelData*)dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BDL_SUBTITLE_KIRARI, TLOGO_BDL_SUBTITLE_KIRARI, TLOGOE_BDL_SUBTITLE_KIRARI_E, TLOGOE0_BDL_SUBTITLE_KIRARI_E));
    JUT_ASSERT(VERSION_SELECT(0xE3, 0xE3, 0x10E, 0x10E), modelData_kirari != NULL);

    mModel_kirari = mDoExt_J3DModel__create(modelData_kirari, 0x80000U, 0x37441422U);
    JUT_ASSERT(VERSION_SELECT(0xE8, 0xE8, 0x113, 0x113), mModel_kirari != NULL);

    J3DAnmTransform* bck_ship = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BCK_TITLE_SHIP, TLOGO_BCK_TITLE_SHIP, TLOGOE_BCK_TITLE_SHIP, TLOGOE0_BCK_TITLE_SHIP)));
    JUT_ASSERT(VERSION_SELECT(0xED, 0xED, 0x118, 0x118), bck_ship != NULL);

    BOOL ok_bck = mBckShip.init(modelData_ship, bck_ship, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    JUT_ASSERT(VERSION_SELECT(0xF4, 0xF4, 0x11F, 0x11F), ok_bck != FALSE);

    J3DAnmColor* bpk_ship = static_cast<J3DAnmColor*>(dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BPK_TITLE_SHIP, TLOGO_BPK_TITLE_SHIP, TLOGOE_BPK_TITLE_SHIP, TLOGOE0_BPK_TITLE_SHIP)));
    JUT_ASSERT(VERSION_SELECT(0xF9, 0xF9, 0x124, 0x124), bpk_ship != NULL);

    BOOL ok_bpk = mBpkShip.init(modelData_ship, bpk_ship, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    JUT_ASSERT(VERSION_SELECT(0xFF, 0xFF, 0x12A, 0x12A), ok_bpk != FALSE);

    mBpkShip.setFrame(0.0f);
    mBpkShip.setPlaySpeed(1.0f);

    J3DAnmTextureSRTKey* btk_sub = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BTK_SUBTITLE_START_ANIM, TLOGO_BTK_SUBTITLE_START_ANIM, TLOGOE_BTK_SUBTITLE_START_ANIM_E, TLOGOE0_BTK_SUBTITLE_START_ANIM_E)));
    JUT_ASSERT(VERSION_SELECT(0x106, 0x106, 0x131, 0x131), btk_sub != NULL);

    BOOL ok_btk_subtitle = mBtkSub.init(modelData_sub, btk_sub, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    JUT_ASSERT(VERSION_SELECT(0x10D, 0x10D, 0x138, 0x138), ok_btk_subtitle != FALSE);

    J3DAnmTextureSRTKey* btk_kirari = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(ARCNAME, VERSION_SELECT(TLOGO_BTK_SUBTITLE_KIRARI, TLOGO_BTK_SUBTITLE_KIRARI, TLOGOE_BTK_SUBTITLE_KIRARI_E, TLOGOE0_BTK_SUBTITLE_KIRARI_E)));
    JUT_ASSERT(VERSION_SELECT(0x112, 0x112, 0x13D, 0x13D), btk_kirari != NULL);

    BOOL ok_btk_kirari = mBtkKirari.init(modelData_kirari, btk_kirari, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    JUT_ASSERT(VERSION_SELECT(0x119, 0x119, 0x144, 0x144), ok_btk_kirari != FALSE);

    mDoExt_restoreCurrentHeap();
    set_mtx();
}

/* 00000638-00000900       .text proc_init2D__14daTitle_proc_cFv */
void daTitle_proc_c::proc_init2D() {
    m_exp_heap = fopMsgM_createExpHeap(0x30000U);
    JUT_ASSERT(VERSION_SELECT(0x122, 0x122, 0x14D, 0x14D), m_exp_heap != NULL);

    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);

    m_Screen = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(0x128, 0x128, 0x153, 0x153), m_Screen != NULL);

    dRes_info_c* resInfo = dComIfG_getObjectResInfo(ARCNAME);
    JUT_ASSERT(VERSION_SELECT(0x12A, 0x12A, 0x155, 0x155), resInfo != NULL);

    m_Screen->set(VERSION_SELECT("title_logo.blo", "title_logo.blo", "title_logo_e.blo", "title_logo_e.blo"), resInfo->getArchive());

    m0A0[2] = m_Screen->search('pres');
    m0A0[3] = m_Screen->search('nint');
    m0A0[0] = m_Screen->search('zeld');
    m0A0[1] = m_Screen->search('zelj');
    m0A0[4] = m_Screen->search('eft1');
    m0A0[5] = m_Screen->search('eft2');

    for (s32 i = 0; i < (s32)ARRAY_SIZE(pane); i++) {
        fopMsgM_setPaneData(&pane[i], m0A0[i]);
        fopMsgM_setNowAlpha(&pane[i], 0.0f);
        fopMsgM_setAlpha(&pane[i]);
    }

    mDoExt_setCurrentHeap(oldHeap);
}

/* 00000900-00000A78       .text __ct__14daTitle_proc_cFv */
daTitle_proc_c::daTitle_proc_c() {
    m_solid_heap = NULL;
    m_exp_heap = NULL;
    m01C = 120;
    mEnterMode = 0;
    m098 = -50;

    m094 = (f32)(m098 * m098) * -attr().field_0x0C;
    m020 = (s32)(cM_rndF(attr().field_0x28) + attr().field_0x2C);
    m024 = (s32)(cM_rndF(attr().field_0x20) + attr().field_0x24 + 130.0f);

    m02C = 0;
    m018 = 0;
    m090 = 0;
    mpEmitter2 = NULL;
    mpEmitter = NULL;
}

/* 00000C1C-00000D7C       .text __dt__14daTitle_proc_cFv */
daTitle_proc_c::~daTitle_proc_c() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);
    delete m_Screen;
    m_Screen = NULL;
    mDoExt_destroySolidHeap(m_solid_heap);
    m_solid_heap = NULL;
    mDoExt_setCurrentHeap(oldHeap);
    fopMsgM_destroyExpHeap(m_exp_heap);
}

/* 00000D7C-00000D94       .text setEnterMode__14daTitle_proc_cFv */
void daTitle_proc_c::setEnterMode() {
    if (mEnterMode == 1) {
        mEnterMode = 2;
    }
}

/* 00000D94-00000F20       .text set_mtx__14daTitle_proc_cFv */
void daTitle_proc_c::set_mtx() {
    cXyz pos;
    cXyz scale(attr().field_0x08, attr().field_0x08, attr().field_0x08);
    mModel_ship->setBaseScale(scale);

    pos.set(m094 + attr().field_0x00, attr().field_0x04, 0.0f);
    mDoMtx_stack_c::transS(pos.x, pos.y, 1000.0f);
    mDoMtx_stack_c::ZXYrotM(0, 0x4000, 0);
    mModel_ship->setBaseTRMtx(mDoMtx_stack_c::get());

    scale.set(attr().field_0x18, attr().field_0x1C, 1.0f);
    mModel_subtitle->setBaseScale(scale);
    mModel_kirari->setBaseScale(scale);

    pos.set(attr().field_0x10, attr().field_0x14, 0.0f);
    mDoMtx_stack_c::transS(pos.x, pos.y, -10000.0f);
    mDoMtx_stack_c::ZXYrotM(0, -0x8000, 0);
    mModel_subtitle->setBaseTRMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::transS(pos.x, pos.y, -10010.0f);
    mDoMtx_stack_c::ZXYrotM(0, -0x8000, 0);
    mModel_kirari->setBaseTRMtx(mDoMtx_stack_c::get());
}


/* 00000F20-0000172C       .text calc_2d_alpha__14daTitle_proc_cFv */
void daTitle_proc_c::calc_2d_alpha() {
    cXyz pos;
    m018 += 1;
    if (m018 >= 200 && getEnterMode() == 0) {
        mEnterMode = 1;
    }

    if (getEnterMode() == 0) {
        if (m098 < 0) {
            m098 += 1;
        }

        if (mpEmitter == NULL) {
            pos.set(
                ((this->pane[4].mPosTopLeftOrig.x - 320.0f) - this->m094) + attr().field_0x30,
                (this->pane[4].mPosTopLeftOrig.y - 240.0f) + attr().field_0x34,
                0.0f
            );

            mpEmitter = dComIfGp_particle_set2Dback(dPa_name::ID_SCENE_83F9, &pos);
        } else {
            pos.set(
                ((this->pane[4].mPosTopLeftOrig.x - 320.0f) - this->m094) + attr().field_0x30,
                (this->pane[4].mPosTopLeftOrig.y - 240.0f) + attr().field_0x34,
                0.0f
            );

            mpEmitter->setGlobalTranslation(pos);
        }

        // Interpolation?
        if (m018 <= 30) {
            fopMsgM_setNowAlpha(&pane[0], 0.0f);
        } else if (m018 <= 80) {
            fopMsgM_setNowAlpha(&pane[0], (f32)(m018 - 30) / 50.0f);
        } else {
            fopMsgM_setNowAlpha(&pane[0], 1.0f);
        }

#if VERSION <= VERSION_JPN
        if (m018 <= 75) {
            fopMsgM_setNowAlpha(&pane[1], 0.0f);
        } else if (m018 <= 130) {
            f32 f1 = m018 - 75;
            fopMsgM_setNowAlpha(&pane[1], f1 / 55);
        } else {
            fopMsgM_setNowAlpha(&pane[1], 1.0f);
        }
#else
        fopMsgM_setNowAlpha(&pane[1], 0.0f);
#endif

        if (m018 == 80) {
            if (daTitle_Kirakira_Sound_flag == true) {
                mDoAud_seStart(JA_SE_TITLE_KIRA);
                daTitle_Kirakira_Sound_flag = false;
            }

            m00C.set(pane[4].mPosTopLeftOrig.x - 320.0f, pane[4].mPosTopLeftOrig.y - 240.0f, 0.0f);

            mpEmitter2 = dComIfGp_particle_set2Dfore(dPa_name::ID_SCENE_83FB, &m00C);
        } else if (m018 > 80 && m018 <= 115 && mpEmitter2 != NULL) {
            m00C.x += (pane[5].mPosTopLeftOrig.x - pane[4].mPosTopLeftOrig.x) / 35.0f;

            mpEmitter2->setGlobalTranslation(m00C.x, m00C.y, m00C.z);
        }

        if (m018 >= 80) {
            mBtkSub.play();
        }

        // Interpolation?
        if (m018 <= 150) {
            fopMsgM_setNowAlpha(&pane[3], 0.0f);
        } else if (m018 <= 170) {
            fopMsgM_setNowAlpha(&pane[3], (m018 - 150) / 20.0f);
        } else {
            fopMsgM_setNowAlpha(&pane[3], 1.0f);
        }

        if (m018 <= 160) {
            fopMsgM_setNowAlpha(&pane[2], 0.0f);
        } else if (m018 <= 180) {
            fopMsgM_setNowAlpha(&pane[2], (m018 - 160) / 20.0f);
        } else {
            fopMsgM_setNowAlpha(&pane[2], 1.0f);
        }
    } else {
        if (mpEmitter == NULL) {
            pos.set(pane[4].mPosTopLeftOrig.x - 320.0f, pane[4].mPosTopLeftOrig.y - 240.0f, 0.0f);
            mpEmitter = dComIfGp_particle_set2Dback(dPa_name::ID_SCENE_83F9, &pos);
        } else {
            pos.set(
                ((pane[4].mPosTopLeftOrig.x - 320.0f) - m094) + attr().field_0x30,
                (pane[4].mPosTopLeftOrig.y - 240.0f) + attr().field_0x34,
                0.0f
            );

            mpEmitter->setGlobalTranslation(pos.x, pos.y, 0.0f);
        }

        fopMsgM_setNowAlpha(&pane[0], 1.0f);
        fopMsgM_setNowAlpha(&pane[1], VERSION_SELECT(1.0f, 1.0f, 0.0f, 0.0f));

        if (mpEmitter2 != NULL) {
            mpEmitter2->becomeInvalidEmitter();
            mpEmitter2 = NULL;
        }

        mBtkSub.setFrame(mBtkSub.getEndFrame());
        fopMsgM_setNowAlpha(&pane[3], 1.0f);
        if (m028 >= 100) {
            m028 = 0;
        } else {
            m028 += 1;
        }

        if (m028 >= 50) {
            fopMsgM_setNowAlpha(&pane[2], (m028 - 50) / 50.0f);
        } else {
            fopMsgM_setNowAlpha(&pane[2], (50 - m028) / 50.0f);
        }
    }

    if (m020 == 0) {
        m020 = (s32)(cM_rndF(attr().field_0x28) + attr().field_0x2C);
        pos.set(pane[4].mPosTopLeftOrig.x - 320.0f, pane[4].mPosTopLeftOrig.y - 240.0f, 0.0f);

        csXyz angle;
        angle.x = (s16)cM_rndFX(32768.0f);
        angle.y = 0;
        angle.z = (s16)cM_rndFX(4000.0f);

        dComIfGp_particle_set2Dback(dPa_name::ID_SCENE_83FA, &pos, &angle);
    } else {
        m020 -= 1;
    }

    if (m024 == 0) {
        m02C += 1;

        if (m02C <= 20) {
            mBtkKirari.setFrame((f32)m02C);
        } else {
            m02C = 0;
            mBtkKirari.setFrame(0.0f);
            m024 = cM_rndF(attr().field_0x20) + attr().field_0x24;
        }
    } else {
        m024 -= 1;
    }

    if (m098 <= 0) {
        m094 = (m098 * m098) * -attr().field_0x0C;
        mBpkShip.setFrame(100.0f + (f32)(m098 * 2));
    } else {
        m094 = (m098 * m098) * attr().field_0x0C;
        mBpkShip.setFrame(100.0f - (f32)(m098 * 2));
    }

}

/* 0000172C-00001880       .text proc_execute__14daTitle_proc_cFv */
void daTitle_proc_c::proc_execute() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);
    if (m01C > 0) {
        m01C -= 1;

        if (m01C == 0) {
            mDoAud_seStart(JA_SE_TITLE_WIND);
        }
    } else {
        calc_2d_alpha();
    }

    if ((CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_START(0)) && mEnterMode == 0) {
        mEnterMode = 1;
        m01C = 0;
        m098 = 0;
    }

    for (int paneIdx = 0; paneIdx < 4; paneIdx++) {
        fopMsgM_setAlpha(&pane[paneIdx]);
    }

    mDoExt_setCurrentHeap(oldHeap);

    if (mEnterMode == 2) {
        mEnterMode = 3;
    } else if (mEnterMode == 3) {
        m098 += 1;
    }

    mBckShip.play();
    set_mtx();
}

/* 00001880-000019E0       .text model_draw__14daTitle_proc_cFv */
void daTitle_proc_c::model_draw() {
    dComIfGd_setList2D();

#if VERSION > VERSION_JPN
    if (mBtkSub.getFrame() != 0.0f) {
#endif
        mBtkKirari.entry(mModel_kirari->getModelData());
        mDoExt_modelUpdateDL(mModel_kirari);
        mBtkKirari.remove(mModel_kirari->getModelData());

        mBtkSub.entry(mModel_subtitle->getModelData());
        mDoExt_modelUpdateDL(mModel_subtitle);
        mBtkSub.remove(mModel_subtitle->getModelData());
#if VERSION > VERSION_JPN
    }
#endif

#if VERSION > VERSION_JPN
    if (mBpkShip.getFrame() != 0.0f) {
#endif
        mBckShip.entry(mModel_ship->getModelData());
        mBpkShip.entry(mModel_ship->getModelData());
        mDoExt_modelUpdateDL(mModel_ship);
        mBpkShip.remove(mModel_ship->getModelData());
        mBckShip.remove(mModel_ship->getModelData());
#if VERSION > VERSION_JPN
    }
#endif

    dComIfGd_setList();
}

/* 000019E0-00001A5C       .text proc_draw__14daTitle_proc_cFv */
void daTitle_proc_c::proc_draw() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);

    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    m_Screen->draw(0.0f, 0.0f, graf);

    mDoExt_setCurrentHeap(oldHeap);
}

daTitle_c::~daTitle_c() {
    if (mpTitleProc != NULL) {
        delete mpTitleProc;
    }

    dComIfG_resDelete(&mPhs, ARCNAME);
}

cPhs_State daTitle_c::create() {
    fopAcM_SetupActor(this, daTitle_c);

#if VERSION == VERSION_PAL
    // Use sprintf to modify the supposedly read-only "TlogoE0" string literal.
    sprintf(ARCNAME, "TlogoE%d\0", dComIfGs_getPalLanguage());
#endif

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, ARCNAME);

    if (phase_state == cPhs_COMPLEATE_e) {
        mpTitleProc = new daTitle_proc_c();

        if (mpTitleProc == NULL) {
            return cPhs_ERROR_e;
        }

        mpTitleProc->proc_init2D();
        mpTitleProc->proc_init3D();
        m29C = false;
    }

    return phase_state;
}

BOOL daTitle_c::draw() {
    mpTitleProc->model_draw();
    dComIfGd_set2DOpa(mpTitleProc);

    return TRUE;
}

BOOL daTitle_c::execute() {
    if (!fopOvlpM_IsPeek()) {
#if VERSION > VERSION_DEMO
        mDoGph_gInf_c::setFadeColor((JUtility::TColor&)g_blackColor);
#endif

        if ((CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_START(0)) && mpTitleProc->getEnterMode() == 1) {
            mpTitleProc->setEnterMode();
        } else if(mpTitleProc->getEnterMode() == 3) {
            scene_class* stageProc = fopScnM_SearchByID(dStage_roomControl_c::getProcID());
            JUT_ASSERT(VERSION_SELECT(0x2B1, 0x2B1, 0x2EF, 0x2EF), stageProc != NULL);

            if (!m29C && fopScnM_ChangeReq(stageProc, PROC_NAME_SCENE, 0, 5)) {
                mDoAud_seStart(JA_SE_OP_ENTER_GAME);
                m29C = true;
            }
        } else if (
#if VERSION > VERSION_JPN
            !mDoRst::isReset() &&
#endif
            dComIfGp_isEnableNextStage()
        ) {
            scene_class* stageProc = fopScnM_SearchByID(dStage_roomControl_c::getProcID());
            JUT_ASSERT(VERSION_SELECT(0x2BD, 0x2BD, 0x2FC, 0x2FC), stageProc != NULL);

            if (!m29C) {
                s16 procName = fpcM_GetName(stageProc) == PROC_OPENING_SCENE ? PROC_OPEN2_SCENE : PROC_TITLE_SCENE;
                fopScnM_ChangeReq(stageProc, procName, 1, 5);
                m29C = true;
            }
        }
    }

    mpTitleProc->proc_execute();
    return TRUE;
}

/* 00001A5C-00001AAC       .text daTitle_Draw__FP9daTitle_c */
static BOOL daTitle_Draw(daTitle_c* i_this) {
    return i_this->draw();
}

/* 00001AAC-00001CF8       .text daTitle_Execute__FP9daTitle_c */
static BOOL daTitle_Execute(daTitle_c* i_this) {
    return i_this->execute();
}

/* 00001CF8-00001D00       .text daTitle_IsDelete__FP9daTitle_c */
static BOOL daTitle_IsDelete(daTitle_c* i_this) {
    return TRUE;
}

/* 00001D00-00001D70       .text daTitle_Delete__FP9daTitle_c */
static BOOL daTitle_Delete(daTitle_c* i_this) {
    i_this->~daTitle_c();

    return TRUE;
}

/* 00001D70-00001E28       .text daTitle_Create__FP10fopAc_ac_c */
static cPhs_State daTitle_Create(fopAc_ac_c* i_this) {
    return static_cast<daTitle_c*>(i_this)->create();
}

/* 00001E28-00001E48       .text draw__14daTitle_proc_cFv */
void daTitle_proc_c::draw() {
    proc_draw();
}

static actor_method_class l_daTitle_Method = {
    (process_method_func)daTitle_Create,
    (process_method_func)daTitle_Delete,
    (process_method_func)daTitle_Execute,
    (process_method_func)daTitle_IsDelete,
    (process_method_func)daTitle_Draw,
};

actor_process_profile_definition g_profile_TITLE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TITLE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTitle_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TITLE,
    /* Actor SubMtd */ &l_daTitle_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
