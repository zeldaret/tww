
#include "d/d_com_inf_game.h"
#include "d/d_letter.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_item_data.h"

/* 80197AB8-80197FE4       .text dKankyo_DayProc__Fv */
static void dKankyo_DayProc() {
    if (dComIfGs_isEventBit(0x1820))
        dLetter_autoStock(0x8b03);

    if (dComIfGs_isEventBit(0x1820) && dComIfGs_isEventBit(0x0b80))
        dLetter_autoStock(0xb203);

    dLetter_delivery(0xac03);
    dLetter_delivery(0xae03);
    dLetter_delivery(0xb003);
    dLetter_delivery(0xaf03);
    dLetter_delivery(0x9d03);

    u8 clamped = cLib_maxLimit(dComIfGs_getEventReg(0xcf03) + 1, 3);
    dComIfGs_setEventReg(0xcf03, clamped);
    clamped = cLib_maxLimit(dComIfGs_getEventReg(0xab03) + 1, 3);
    dComIfGs_setEventReg(0xab03, clamped);

    if (dComIfGs_isGetItemReserve(0x0F) && dComIfGs_checkReserveItem(MO_LETTER) == 0) {
        clamped = cLib_maxLimit(dComIfGs_getEventReg(0xccff) + 1, 2);
        dComIfGs_setEventReg(0xccff, clamped);
    }

    dComIfGs_setEventReg(0xbcff, 0);
    dComIfGs_setEventReg(0xcb03, 0);
    dComIfGs_setEventReg(0xca03, 0);
    dComIfGs_setEventReg(0xc903, 0);
    dComIfGs_offEventBit(0x1304);
    dComIfGs_offEventBit(0x1302);
    dComIfGs_offEventBit(0x1301);
    dComIfGs_offTmpBit(0x0120);
    dComIfGs_offTmpBit(0x0040);
    dComIfGs_offTmpBit(0x0020);
    dComIfGs_offTmpBit(0x0010);
    dComIfGs_offTmpBit(0x0008);
    dComIfGs_offTmpBit(0x0004);
    dComIfGs_offTmpBit(0x0002);
    dComIfGs_offTmpBit(0x0001);
    dComIfGs_offTmpBit(0x0180);
    dComIfGs_offTmpBit(0x0140);
    dComIfGs_offTmpBit(0x0580);
    dComIfGs_offTmpBit(0x0104);

    if (dComIfGs_getEventReg(0xc103) == 1)
        dComIfGs_setEventReg(0xc103, 2);

    if (dComIfGs_isEventBit(0x1f10)) {
        u8 reg = dComIfGs_getEventReg(0xbb07);
        if (reg == 7) {
            dComIfGs_onEventBit(0x1f08);
        } else {
            clamped = cLib_maxLimit(reg + 1, 7);
            dComIfGs_setEventReg(0xbb07, clamped);
        }
    }

    if (dComIfGs_getEventReg(0xc407) == 6)
        dComIfGs_setEventReg(0xc407, 7);

    u8 reg = dComIfGs_getEventReg(0xb907);
    if (reg & 1)
        dComIfGs_setEventReg(0xb907, reg + 1);

    dComIfGs_offEventBit(0x2680);

#if VERSION != VERSION_JPN
    if (dComIfGs_isEventBit(0x2a20)) {
#endif
        clamped = cLib_maxLimit(dComIfGs_getEventReg(0xa60f) + 1, 3);
        dComIfGs_setEventReg(0xa60f, clamped);
#if VERSION != VERSION_JPN
    }
#endif

    if (dKy_get_dayofweek() == 5) {
        dComIfGs_offEventBit(0x2080);
        dComIfGs_offEventBit(0x2004);
        dComIfGs_offEventBit(0x2002);
        dComIfGs_offEventBit(0x2804);
        dComIfGs_offEventBit(0x2802);
        dComIfGs_offEventBit(0x2801);
        dComIfGs_offEventBit(0x2980);
        dComIfGs_offEventBit(0x2940);
        dComIfGs_offEventBit(0x3b01);
        dComIfGs_offEventBit(0x3c80);
        dComIfGs_offEventBit(0x3c40);
        dComIfGs_offEventBit(0x3c20);
        dComIfGs_offEventBit(0x3c10);
        dComIfGs_offEventBit(0x3c08);
        dComIfGs_offEventBit(0x3c04);
        dComIfGs_offEventBit(0x3c02);
    }
    
    dComIfGs_offTmpBit(0x0208);
    if (dComIfGs_isEventBit(0x2f01))
        dComIfGs_onEventBit(0x3080);
    dComIfGs_offTmpBit(0x0302);
    dComIfGs_offTmpBit(0x0301);
}
