//
// Generated by dtk
// Translation Unit: d_gameover.cpp
//

#include "d/d_menu_save.h"
#include "d/d_drawlist.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter.h"
#include "d/d_procname.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_Reset.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "SSystem/SComponent/c_phase.h"

class dDlst_Gameover_CAPTURE_c : public dDlst_base_c {
public:
    virtual ~dDlst_Gameover_CAPTURE_c() {}
    virtual void draw();
};

class dDlst_GameOverScrnDraw_c : public dDlst_base_c {
public:
    dDlst_GameOverScrnDraw_c() {
        field_0x338 = 0;
        field_0x33c = 0;
        field_0x330 = 0;
        field_0x334 = 0;

        field_0x32c = 8;
        mAlpha = 0.0f;
    }

    virtual ~dDlst_GameOverScrnDraw_c() {}
    void setScreen(const char*, JKRArchive*);
    void valueInit();
    BOOL animeOpen();
    BOOL animeClose();
    void setEmitter0(cXyz);
    void setEmitter1(cXyz);
    BOOL anime1(int);
    void anime2(int);
    void setRotate(fopMsgM_pane_class*, f32);

    virtual void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class letter[8];
    /* 0x1C8 */ u8 field_0x1c8[0x318 - 0x1c8];
    /* 0x318 */ fopMsgM_pane_alpha_class blak;
    /* 0x320 */ JPABaseEmitter* mpEmitter0;
    /* 0x324 */ JPABaseEmitter* mpEmitter1;
    /* 0x328 */ f32 mAlpha;
    /* 0x32C */ s32 field_0x32c;
    /* 0x330 */ s32 field_0x330;
    /* 0x334 */ u32 field_0x334;
    /* 0x338 */ u32 field_0x338;
    /* 0x33C */ u16 field_0x33c;
    /* 0x33E */ s16 mRotate[8];
    /* 0x34E */ u8 field_0x34e[0x410 - 0x34E];
};

class dGameover_c : public msg_class {
public:
    s32 _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();
    BOOL deleteCheck();

public:
    /* 0x0FC */ dMenu_save_c* dMs_c;
    /* 0x100 */ dDlst_GameOverScrnDraw_c* dgo_scrn_c;
    /* 0x104 */ dDlst_Gameover_CAPTURE_c* dgo_capture_c;
    /* 0x108 */ request_of_phase_process_class mPhs;
    /* 0x110 */ JKRExpHeap* mpHeap;
    /* 0x114 */ s16 field_0x114;
    /* 0x116 */ s16 field_0x116;
    /* 0x118 */ u8 mState;
    /* 0x119 */ u8 field_0x119;
    /* 0x11C */ u8 field_0x11c;
};

/* 8018E1CC-8018E4B4       .text draw__24dDlst_Gameover_CAPTURE_cFv */
void dDlst_Gameover_CAPTURE_c::draw() {
    /* Nonmatching */
    GXTexObj texObj;

    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(mDoGph_gInf_c::getZbufferTex(), GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&texObj, mDoGph_gInf_c::getFrameBufferTex(), 320, 240, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_OR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    GXSetFogRangeAdj(GX_FALSE, 0, NULL);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_TRUE);

    Mtx44 mtx;
    C_MTXOrtho(mtx, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 10.0f);
    GXSetProjection(mtx, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(mDoMtx_getIdentity(), GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S8, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s8(0, 0, 251);
    GXTexCoord2s8(0, 0);
    GXPosition3s8(1, 0, 251);
    GXTexCoord2s8(1, 0);
    GXPosition3s8(1, 1, 251);
    GXTexCoord2s8(1, 1);
    GXPosition3s8(0, 1, 251);
    GXTexCoord2s8(0, 1);
    GXEnd();
}

/* 8018E4B4-8018E77C       .text _create__11dGameover_cFv */
s32 dGameover_c::_create() {
    s32 rt = dComIfG_resLoad(&mPhs, "Gover");
    if (dMenu_flag() || (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 4) || dComIfGp_getMesgStatus() != 0)
        return cPhs_INIT_e;

    if (rt == cPhs_COMPLEATE_e) {
        dComIfGs_addDeathCount();
        dRes_info_c* resInfo = dComIfG_getObjectResInfo("Gover");
        JUT_ASSERT(0xa0, resInfo != NULL);

        mpHeap = dComIfGp_getExpHeap2D();
        dComIfGp_setHeapLockFlag(4);
        JKRHeap* oldHeap = mDoExt_setCurrentHeap(mpHeap);

        dgo_scrn_c = new dDlst_GameOverScrnDraw_c();
        dgo_scrn_c->setScreen("gameover.blo", resInfo->getArchive());

        dMs_c = new dMenu_save_c();
        JUT_ASSERT(0xb6, dMs_c != NULL);
        dMs_c->field_0x0537 = 2;
        dMs_c->_create();

        dgo_capture_c = new dDlst_Gameover_CAPTURE_c();
        JUT_ASSERT(0xbb, dgo_capture_c != NULL);

        mDoExt_setCurrentHeap(oldHeap);
    } else {
        return rt;
    }

    field_0x114 = 90;
    field_0x116 = g_menuHIO.field_0xb6;
    field_0x119 = 0;
    return cPhs_COMPLEATE_e;
}

/* 8018E77C-8018E9D4       .text _execute__11dGameover_cFv */
BOOL dGameover_c::_execute() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(mpHeap);

    if (mState == 3) {
        if (dMs_c->_open()) {
            mState = 4;
            dComIfGs_setLife(12);
        }
    } else if (mState == 4) {
        dMs_c->_move();
        if (dMs_c->field_0x0531 == 3)
            mState = 5;
    } else if (mState == 5) {
        if (dMs_c->_close()) {
            if (dMs_c->field_0x0538 == 0) {
                dComIfGp_setGameoverStatus(3);
                dMenu_flagSet(0);
                mDoRst::onReset();
            } else if (dMs_c->field_0x0538 == 1) {
                dComIfGp_setGameoverStatus(2);
                dMenu_flagSet(0);
            }

            if (dgo_scrn_c->mpEmitter1 != NULL)
                dgo_scrn_c->mpEmitter1->becomeInvalidEmitter();
            mState = 6;
        }
    } else if (mState != 6 && field_0x119) {
        if (field_0x114 == 90) {
            if (dgo_scrn_c->animeOpen() == 1) {
                cXyz zero(0.0f, 0.0f, 0.0f);
                dgo_scrn_c->setEmitter0(zero);
                dgo_scrn_c->setEmitter1(zero);
                field_0x114--;
            }
        } else if (field_0x114 > 0) {
            field_0x114--;
            if (field_0x114 == 0)
                dgo_scrn_c->valueInit();
        } else {
            if (dgo_scrn_c->animeClose() == 1) {
                if (dgo_scrn_c->mpEmitter0 != NULL)
                    dgo_scrn_c->mpEmitter0->becomeInvalidEmitter();
                if (field_0x116-- <= 0) {
                    mState = 3;
                    dMenu_flagSet(1);
                }
            }
        }
    }

    mDoExt_setCurrentHeap(oldHeap);
    return TRUE;
}

/* 8018E9D4-8018EA58       .text _draw__11dGameover_cFv */
BOOL dGameover_c::_draw() {
    if (dgo_capture_c != NULL && dMenu_flag())
        dComIfGd_set2DOpa(dgo_capture_c);

    dComIfGd_set2DOpa(dgo_scrn_c);
    dMs_c->_draw2();
    return TRUE;
}

/* 8018EA58-8018EB54       .text _delete__11dGameover_cFv */
BOOL dGameover_c::_delete() {
    /* Nonmatching */
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(mpHeap);

    delete dgo_scrn_c->scrn;
    delete dgo_scrn_c;
    dMs_c->_delete();
    delete dMs_c;
    delete dgo_capture_c;
    mpHeap->freeAll();
    dComIfGp_offHeapLockFlag();
    mDoExt_setCurrentHeap(oldHeap);
    dComIfG_resDelete(&mPhs, "Gover");
    return TRUE;
}

/* 8018EB54-8018EB68       .text deleteCheck__11dGameover_cFv */
BOOL dGameover_c::deleteCheck() {
    return mState == 6;
}

static s16 dGover_tex_number = 8;

/* 8018EB68-8018EC9C       .text setScreen__24dDlst_GameOverScrnDraw_cFPCcP10JKRArchive */
void dDlst_GameOverScrnDraw_c::setScreen(const char* filename, JKRArchive* arc) {
    scrn = new J2DScreen();
    scrn->set(filename, arc);

    const static u32 labelt[] = {
        'txg',
        'txa',
        'txm',
        'txe1',
        'txo',
        'txv',
        'txe2',
        'txr',
    };

    for (s32 i = 0; i < dGover_tex_number; i++)
        fopMsgM_setPaneData(&letter[i], scrn->search(labelt[i]));
    fopMsgM_setPaneData(&blak, scrn->search('blak'));
    blak.mInitAlpha = 0xFF;
}

/* 8018EC9C-8018ECD8       .text valueInit__24dDlst_GameOverScrnDraw_cFv */
void dDlst_GameOverScrnDraw_c::valueInit() {
    field_0x32c = dGover_tex_number;
    field_0x330 = 0;
    for (s32 i = 0; i < dGover_tex_number; i++)
        letter[i].mUserArea = 0;
}

/* 8018ECD8-8018EEC8       .text animeOpen__24dDlst_GameOverScrnDraw_cFv */
BOOL dDlst_GameOverScrnDraw_c::animeOpen() {
    const static f32 x[8] = {
        -175.0f, -130.0f, -80.0f, -30.0f,
        32.0f, 75.0f, 120.0f, 160.0f
    };
    
    u8 var_r31 = 0;
    s16 var_r30 = -1;
    if (field_0x32c >= 0) {
        if (field_0x330 != 0) {
            field_0x330 -= 1;
        } else {
            s32 rand = cM_rndF(field_0x32c);
            if (rand >= field_0x32c - 1) {
                rand = field_0x32c - 1;
            }

            for (int i = 0; i < dGover_tex_number; i++) {
                if (letter[i].mUserArea == 0) {
                    if (rand == 0) {
                        anime1(i);
                        var_r30 = i;
                        break;
                    } else {
                        rand -= 1;
                    }
                }
            }

            field_0x32c -= 1;
            field_0x330 = (field_0x32c * field_0x32c) / 5;
        }
    }


    for (int i = 0; i < dGover_tex_number; i++) {
        s16 userArea = letter[i].mUserArea;

        if (userArea >= 0 && userArea < 9) {
            if (userArea >= 1 && var_r30 != i) {
                anime1(i);
                if (letter[i].mUserArea == 5) {
                    dComIfGp_particle_set2Dfore(0x2E, &cXyz(x[i], 50.0f, 0.0f));
                }
            }

            var_r31 = 1;
        }
    }

    return var_r31 == 0 ? TRUE : FALSE;
}

/* 8018EEC8-8018F05C       .text animeClose__24dDlst_GameOverScrnDraw_cFv */
BOOL dDlst_GameOverScrnDraw_c::animeClose() {
    u8 var_r31 = 0;
    s16 var_r30 = -1;

    if (field_0x32c >= 0) {
        if (field_0x330 != 0) {
            field_0x330 = 0;
        } else {
            s32 rand = cM_rndF(field_0x32c);
            if (rand >= field_0x32c - 1) {
                rand = field_0x32c - 1;
            }

            for (int i = 0; i < dGover_tex_number; i++) {
                if (letter[i].mUserArea == 0) {
                    if (rand == 0) {
                        anime2(i);
                        var_r30 = i;
                        break;
                    } else {
                        rand -= 1;
                    }
                }
            }

            field_0x330 = (s32)cM_rndF(3.0f) + 1;

            if (field_0x330 >= 3) {
                field_0x330 = 3;
            }

            field_0x32c -= 1;
        }
    }

    for (int i = 0; i < dGover_tex_number; i++) {
        s16 userArea = letter[i].mUserArea;

        if (userArea >= 0 && userArea < 7) {
            if (userArea >= 1 && var_r30 != i) {
                anime2(i);
            }

            var_r31 = 1;
        }
    }

    return var_r31 == 0 ? TRUE : FALSE;
}

/* 8018F05C-8018F0CC       .text setEmitter0__24dDlst_GameOverScrnDraw_cF4cXyz */
void dDlst_GameOverScrnDraw_c::setEmitter0(cXyz pos) {
    mpEmitter0 = dComIfGp_particle_set2Dfore(0x2f, &pos);
}

/* 8018F0CC-8018F13C       .text setEmitter1__24dDlst_GameOverScrnDraw_cF4cXyz */
void dDlst_GameOverScrnDraw_c::setEmitter1(cXyz pos) {
    mpEmitter1 = dComIfGp_particle_set2DmenuFore(0x30, &pos);
}

// Fake inline
inline f32 temp(s16 y, f32 div) {
    return (f32)y * (f32)y / div;
}

/* 8018F13C-8018F334       .text anime1__24dDlst_GameOverScrnDraw_cFi */
BOOL dDlst_GameOverScrnDraw_c::anime1(int idx) {
    /* Fakematch */

    BOOL ret = FALSE;

    if (letter[idx].mUserArea < 5) {
        if (letter[idx].mUserArea == 0)
            fopMsgM_setInitAlpha(&letter[idx]);

        letter[idx].mUserArea++;
        s16 userArea = letter[idx].mUserArea;
        fopMsgM_paneTrans(&letter[idx], 0.0f, (1.0f - temp(letter[idx].mUserArea, 25.0f)) * -288.0f);
    } else if (letter[idx].mUserArea < 7) {
        letter[idx].mUserArea++;
        fopMsgM_paneTrans(&letter[idx], 0.0f, (temp(letter[idx].mUserArea - 5, 4.0f)) * -9.0f);
    } else if (letter[idx].mUserArea < 9) {
        letter[idx].mUserArea++;
        fopMsgM_paneTrans(&letter[idx], 0.0f, (1.0f - temp(letter[idx].mUserArea - 7, 4.0f)) * -9.0f);
        if (letter[idx].mUserArea == 9)
            mDoAud_seStart(JA_SE_EXIT_GAME_OVER);
    }

    if (letter[idx].mUserArea == 9)
        ret = TRUE;

    return ret;
}

/* 8018F334-8018F4A8       .text anime2__24dDlst_GameOverScrnDraw_cFi */
void dDlst_GameOverScrnDraw_c::anime2(int) {
    /* Nonmatching */
}

/* 8018F4A8-8018F548       .text setRotate__24dDlst_GameOverScrnDraw_cFP18fopMsgM_pane_classf */
void dDlst_GameOverScrnDraw_c::setRotate(fopMsgM_pane_class* pane, f32 angle) {
    /* Nonmatching */
    J2DPane* j2dpane = pane->pane;
    j2dpane->mBasePosition.set((s32)pane->mSize.x / 2.0f, (s32)pane->mSize.y / 2.0f);
    j2dpane->mRotationAxis = 'z';
    j2dpane->mRotation = angle;
    j2dpane->calcMtx();
}

/* 8018F548-8018F5EC       .text draw__24dDlst_GameOverScrnDraw_cFv */
void dDlst_GameOverScrnDraw_c::draw() {
    for (s32 i = 0; i < dGover_tex_number; i++)
        fopMsgM_setAlpha(&letter[i]);
    fopMsgM_setNowAlpha(&blak, mAlpha);
    fopMsgM_setAlpha(&blak);

    J2DOrthoGraph* port = dComIfGp_getCurrentGrafPort();
    port->setPort();
    scrn->draw(0.0f, 0.0f, port);
}

/* 8018F5EC-8018F60C       .text dGameover_Draw__FP11dGameover_c */
static BOOL dGameover_Draw(dGameover_c* i_this) {
    return i_this->_draw();
}

/* 8018F60C-8018F62C       .text dGameover_Execute__FP11dGameover_c */
static BOOL dGameover_Execute(dGameover_c* i_this) {
    return i_this->_execute();
}

/* 8018F62C-8018F634       .text dGameover_IsDelete__FP11dGameover_c */
static BOOL dGameover_IsDelete(dGameover_c* i_this) {
    return TRUE;
}

/* 8018F634-8018F654       .text dGameover_Delete__FP11dGameover_c */
static BOOL dGameover_Delete(dGameover_c* i_this) {
    return i_this->_delete();
}

/* 8018F654-8018F674       .text dGameover_Create__FP9msg_class */
static s32 dGameover_Create(msg_class* i_this) {
    return ((dGameover_c*)i_this)->_create();
}

msg_method_class l_dGameover_Method = {
    (process_method_func)dGameover_Create,
    (process_method_func)dGameover_Delete,
    (process_method_func)dGameover_Execute,
    (process_method_func)dGameover_IsDelete,
    (process_method_func)dGameover_Draw,
};

msg_process_profile_definition g_profile_GAMEOVER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 12,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_GAMEOVER,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dGameover_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Priority     */ 0x01DE,
    /* Msg SubMtd   */ &l_dGameover_Method,
};
