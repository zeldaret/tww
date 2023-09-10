#ifndef C_API_H
#define C_API_H

#include "dolphin/types.h"

typedef void (*cAPIGph_Mthd)(void);

struct cAPIGph__Iface
{
    u8 * mpGInfo;
    cAPIGph_Mthd mpCreate;
    cAPIGph_Mthd mpBeforeOfDraw;
    cAPIGph_Mthd mpAfterOfDraw;
    cAPIGph_Mthd mpPainter;
    cAPIGph_Mthd mpBlankingOn;
    cAPIGph_Mthd mpBlankingOff;
};

extern cAPIGph__Iface g_cAPI_Interface;

#endif /* C_API_H */
