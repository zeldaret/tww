#include "SSystem/SComponent/c_API.h"
#include "dolphin/types.h"
#include "m_Do/m_Do_graphic.h"

cAPIGph__Iface g_cAPI_Interface = {
    /* mpGInfo        */ &g_mDoGph_graphicInfo,
    /* mpCreate       */ (cAPIGph_Mthd)mDoGph_Create,
    /* mpBeforeOfDraw */ (cAPIGph_Mthd)mDoGph_BeforeOfDraw,
    /* mpAfterOfDraw  */ (cAPIGph_Mthd)mDoGph_AfterOfDraw,
    /* mpPainter      */ (cAPIGph_Mthd)mDoGph_Painter,
    /* mpBlankingOn   */ (cAPIGph_Mthd)mDoGph_BlankingON,
    /* mpBlankingOff  */ (cAPIGph_Mthd)mDoGph_BlankingOFF,
};
