//
// Generated by dtk
// Translation Unit: f_pc_manager.cpp
//

#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_creator.h"
#include "f_pc/f_pc_draw.h"
#include "f_pc/f_pc_deletor.h"
#include "f_pc/f_pc_fstcreate_req.h"
#include "f_pc/f_pc_layer_iter.h"
#include "f_pc/f_pc_line.h"
#include "f_pc/f_pc_pause.h"
#include "f_pc/f_pc_priority.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_Reset.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_API_graphic.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/JAudio/JAIStreamMgr.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/dvd/dvd.h"
#include "dolphin/gx/GX.h"

#include "assets/black_tex.h"
#include "assets/msg_data.h"
#if VERSION == VERSION_PAL
#include "assets/msg_data_ge.h"
#include "assets/msg_data_fr.h"
#include "assets/msg_data_sp.h"
#include "assets/msg_data_it.h"
#endif
#include "assets/font_data.h"

/* 8003E318-8003E338       .text fpcM_Draw__FPv */
BOOL fpcM_Draw(void* i_proc) {
    return fpcDw_Execute((base_process_class*)i_proc);
}

/* 8003E338-8003E370       .text fpcM_DrawIterater__FPFPvPv_i */
BOOL fpcM_DrawIterater(fpcM_DrawIteraterFunc i_drawIterFunc) {
    return fpcLyIt_OnlyHere(fpcLy_RootLayer(), (fpcLyIt_OnlyHereFunc)i_drawIterFunc, NULL);
}

/* 8003E370-8003E390       .text fpcM_Execute__FPv */
BOOL fpcM_Execute(void* i_proc) {
    return fpcEx_Execute((base_process_class*)i_proc);
}

/* 8003E390-8003E3B0       .text fpcM_Delete__FPv */
BOOL fpcM_Delete(void* i_proc) {
    return fpcDt_Delete((base_process_class*)i_proc);
}

/* 8003E3B0-8003E3D0       .text fpcM_IsCreating__FUi */
BOOL fpcM_IsCreating(fpc_ProcID pID) {
    return fpcCt_IsCreatingByID(pID);
}

struct BMG_INF1 : JUTDataBlockHeader {
    /* 0x08 */ u8 m08[0x10 - 0x08];
    /* 0x10 */ u32 entries[6];
};

/* 8003E3D0-8003E9F0       .text messageSet__FUl */
void messageSet(u32 status) {
#if VERSION == VERSION_PAL
    BMG_INF1* inf1;
    if (dComIfGs_getPalLanguage() == 1) {
        inf1 = (BMG_INF1*)&msg_data_ge[0x20];
    } else if (dComIfGs_getPalLanguage() == 2) {
        inf1 = (BMG_INF1*)&msg_data_fr[0x20];
    } else if (dComIfGs_getPalLanguage() == 3) {
        inf1 = (BMG_INF1*)&msg_data_sp[0x20];
    } else if (dComIfGs_getPalLanguage() == 4) {
        inf1 = (BMG_INF1*)&msg_data_it[0x20];
    } else {
        inf1 = (BMG_INF1*)&msg_data[0x20]; // English
    }
#else
    BMG_INF1* inf1 = (BMG_INF1*)&msg_data[0x20];
#endif
    const char * msg = (const char*)((u8*)inf1->getNext() + sizeof(JUTDataBlockHeader) + inf1->entries[status]);

    J2DTextBox * tpane = new J2DTextBox('TXT1', JGeometry::TBox2<f32>(0.0f, 0.0f, 660.0f, 200.0f), (ResFONT*)font_data, msg, HBIND_CENTER, VBIND_CENTER);
    JUT_ASSERT(VERSION_SELECT(0x12b, 0x141, 0x141), tpane != NULL);

    J2DTextBox * spane = new J2DTextBox('TXT2', JGeometry::TBox2<f32>(0.0f, 0.0f, 660.0f, 200.0f), (ResFONT*)font_data, msg, HBIND_CENTER, VBIND_CENTER);
    JUT_ASSERT(VERSION_SELECT(0x133, 0x149, 0x149), spane != NULL);

    J2DPicture * ppane = new J2DPicture('PIC1', JGeometry::TBox2<f32>(0.0f, 0.0f, 665.0f, 530.0f), (ResTIMG*)black_tex, NULL);
    JUT_ASSERT(VERSION_SELECT(0x138, 0x14e, 0x14e), ppane != NULL);

    J2DTextBox::TFontSize size;
    size.mSizeX = 27.0f;
    size.mSizeY = 27.0f;
    tpane->setFontSize(size);
    tpane->setCharColor(JUtility::TColor(0xFF, 0xC8, 0x00, 0xFF));
    tpane->setGradColor(JUtility::TColor(0xFF, 0xB4, 0x00, 0xFF));
    tpane->setCharSpace(0.0f);
    tpane->setLineSpace(27.0f);
    tpane->setBlack(JUtility::TColor(0xFF, 0xFF, 0xFF, 0x00));

    spane->setFontSize(size);
    spane->setCharColor(JUtility::TColor(0x00, 0x00, 0x00, 0xC8));
    spane->setGradColor(JUtility::TColor(0x00, 0x00, 0x00, 0xC8));
    spane->setCharSpace(0.0f);
    spane->setLineSpace(27.0f);

    ppane->setAlpha(130);

#if VERSION != VERSION_JPN
    JUTResFont * font = new JUTResFont((ResFONT*)font_data, NULL);
#endif

    s16 height = 27;
#if VERSION != VERSION_JPN
    f32 maxWidth = 0.0f;
    s32 curLine = 0;
    f32 lineWidth[6];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(lineWidth); i++) {
        lineWidth[i] = 0.0f;
    }
#endif
    for (; *msg != '\0'; msg++) {
        if (*msg == '\n') {
            height += 27;
#if VERSION != VERSION_JPN
            curLine++;
#endif
            continue;
        }

#if VERSION != VERSION_JPN
        lineWidth[curLine] += font->JUTFont::getWidth((u8)*msg);
#endif
    }

#if VERSION != VERSION_JPN
    for (s32 i = 0; i < (s32)ARRAY_SIZE(lineWidth); i++) {
        f32 width = lineWidth[i];
        if (maxWidth < width)
            maxWidth = width;
    }
#endif

#if VERSION == VERSION_JPN
    f32 x = -9.5f;
#else
    f32 x = (659.0f - maxWidth) / 2.0f + -9.0f;
#endif
    f32 y = (524 - height) / 2.0f + -21.0f;

    ppane->draw(-12.0f, -24.0f, 665.0f, 530.0f, false, false, false);
#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 0) {
        spane->draw(x + 2.0f, y + 10.0f + 2.0f, 660.0f, HBIND_LEFT);
        tpane->draw(x, y + 10.0f, 660.0f, HBIND_LEFT);
    } else {
        spane->draw(-7.0f, y + 10.0f + 2.0f, 660.0f, HBIND_CENTER);
        tpane->draw(-9.0f, y + 10.0f, 660.0f, HBIND_CENTER);
    }
#else
    spane->draw(x + 2.0f, y + 10.0f + 2.0f, 660.0f, VERSION_SELECT(HBIND_CENTER, HBIND_LEFT, HBIND_LEFT));
    tpane->draw(x, y + 10.0f, 660.0f, VERSION_SELECT(HBIND_CENTER, HBIND_LEFT, HBIND_LEFT));
#endif

#if VERSION != VERSION_JPN
    delete font;
#endif
    delete ppane;
    delete tpane;
    delete spane;
}

/* 8003E9F0-8003EBD4       .text drawDvdCondition__Fl */
void drawDvdCondition(long status) {
#if VERSION == VERSION_PAL
    JUtility::TColor backColor = g_clearColor;
#else
    JFWDisplay::getManager()->setFader(NULL);
    JUtility::TColor backColor = mDoGph_gInf_c::getBackColor();
#endif
    JFWDisplay::getManager()->setClearColor(backColor);
    JFWDisplay::getManager()->beginRender();
    GXSetAlphaUpdate(GX_FALSE);
    j3dSys.drawInit();

    J2DOrthoGraph draw2D(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0);
    draw2D.setOrtho(-9.0f, -21.0f, 659.0f, 524.0f, -1.0f, 1.0f);
    draw2D.setPort();
    dComIfGp_setCurrentGrafPort(&draw2D);

    if (status == 4) {
        messageSet(2);
    } else if (status == 5) {
        messageSet(1);
    } else if (status == 6) {
        messageSet(3);
    } else if (status == 11) {
        messageSet(4);
    } else if (status == 1) {
        messageSet(0);
    } else if (status == -1) {
        messageSet(5);
#if VERSION != VERSION_JPN
        JAInter::StreamLib::stop();
#endif
    } else {
        JUT_WARN(VERSION_SELECT(423, 481, 478), "Dvd Error !! <%d>\n", status);
    }

    JFWDisplay::getManager()->endRender();
#if VERSION == VERSION_PAL
    JFWDisplay::getManager()->setFader(NULL);
#endif
}

/* 8003EBD4-8003EC84       .text checkDvdCondition__Fv */
int checkDvdCondition() {
    static int l_dvdError = 0;
    
    int status = DVDGetDriveStatus();
    if (status != 0 && status != 1)
        l_dvdError = 1;

    if (l_dvdError != 0) {
        if (status == 0) {
            l_dvdError = 0;
        } else if (mDoRst::isReset()) {
            mDoRst::offReset();
            mDoRst_reset(1, 0x80000000, 0);
        } else {
            drawDvdCondition(status);
        }
    }

    return l_dvdError;
}

/* 8003EC84-8003ED90       .text fpcM_Management__FPFv_vPFv_v */
void fpcM_Management(fpcM_ManagementFunc callBack1, fpcM_ManagementFunc callBack2) {
    MtxInit();

    if (checkDvdCondition())
        return;

    cAPIGph_Painter();
    fpcDt_Handler();
    if (!fpcPi_Handler())
        JUT_ASSERT(VERSION_SELECT(490, 548, 547), 0);

    if (!fpcCt_Handler())
        JUT_ASSERT(VERSION_SELECT(494, 552, 551), 0);

    if (callBack1 != NULL)
        callBack1();

    fpcEx_Handler((fpcLnIt_QueueFunc)fpcM_Execute);
    fpcDw_Handler((fpcDw_HandlerFuncFunc)fpcM_DrawIterater, (fpcDw_HandlerFunc)fpcM_Draw);

    if (callBack2 != NULL)
        callBack2();
}

/* 8003ED90-8003EDCC       .text fpcM_Init__Fv */
void fpcM_Init() {
    static layer_class rootlayer;
    static node_list_class queue[10];

    fpcLy_Create(&rootlayer, NULL, queue, 10);
    fpcLn_Create();
}

/* 8003EDCC-8003EE20       .text fpcM_FastCreate__FsPFPv_iPvPv */
base_process_class* fpcM_FastCreate(s16 i_procTypeID, FastCreateReqFunc i_createReqFunc,
                                    void* i_createData, void* i_data) {
    return fpcFCtRq_Request(fpcLy_CurrentLayer(), i_procTypeID, (fstCreateFunc)i_createReqFunc,
                            i_createData, i_data);
}


/* 8003EE20-8003EE44       .text fpcM_IsPause__FPvUc */
s32 fpcM_IsPause(void* i_proc, u8 i_flag) {
    return fpcPause_IsEnable((base_process_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE44-8003EE68       .text fpcM_PauseEnable__FPvUc */
void fpcM_PauseEnable(void* i_proc, u8 i_flag) {
    fpcPause_Enable((process_node_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE68-8003EE8C       .text fpcM_PauseDisable__FPvUc */
void fpcM_PauseDisable(void* i_proc, u8 i_flag) {
    fpcPause_Disable((process_node_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE8C-8003EF00       .text fpcM_JudgeInLayer__FUiPFPvPv_PvPv */
void* fpcM_JudgeInLayer(uint i_layerID, fpcCtIt_JudgeFunc i_judgeFunc, void* i_data) {
    layer_class* layer = fpcLy_Layer(i_layerID);
    if (layer != NULL) {
        void* ret = fpcCtIt_JudgeInLayer(i_layerID, i_judgeFunc, i_data);
        if (ret == NULL) {
            ret = fpcLyIt_Judge(layer, i_judgeFunc, i_data);
        }
        return ret;
    } else {
        return NULL;
    }
}
