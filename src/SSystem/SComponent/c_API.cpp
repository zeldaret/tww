#include "SSystem/SComponent/c_API.h"
#include "dolphin/types.h"

extern u8 g_mDoGph_graphicInfo;
extern bool mDoGph_Create();
extern bool mDoGph_BeforeOfDraw();
extern bool mDoGph_AfterOfDraw();
extern bool mDoGph_Painter();
extern bool mDoGph_BlankingON();
extern bool mDoGph_BlankingOFF();

cAPIGph__Iface g_cAPI_Interface = {
    &g_mDoGph_graphicInfo, mDoGph_Create,     mDoGph_BeforeOfDraw, mDoGph_AfterOfDraw,
    mDoGph_Painter,        mDoGph_BlankingON, mDoGph_BlankingOFF,
};
