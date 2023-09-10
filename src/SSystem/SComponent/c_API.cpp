#include "SSystem/SComponent/c_API.h"
#include "dolphin/types.h"

extern u8 g_mDoGph_graphicInfo;
extern void mDoGph_Create();
extern void mDoGph_BeforeOfDraw();
extern void mDoGph_AfterOfDraw();
extern void mDoGph_Painter();
extern void mDoGph_BlankingON();
extern void mDoGph_BlankingOFF();

cAPIGph__Iface g_cAPI_Interface = {
    &g_mDoGph_graphicInfo, mDoGph_Create,     mDoGph_BeforeOfDraw, mDoGph_AfterOfDraw,
    mDoGph_Painter,        mDoGph_BlankingON, mDoGph_BlankingOFF,
};
