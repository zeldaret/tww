
#include "d/d_com_inf_game.h"
#include "d/d_letter.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_item_data.h"

/* 80197AB8-80197FE4       .text dKankyo_DayProc__Fv */
static void dKankyo_DayProc() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820))
        dLetter_autoStock(dSv_event_flag_c::LETTER_ARYLL);

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820) && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80))
        dLetter_autoStock(dSv_event_flag_c::LETTER_TINGLE);

    dLetter_delivery(dSv_event_flag_c::LETTER_BAITOS_MOM);
    dLetter_delivery(dSv_event_flag_c::LETTER_HOSKITS_GIRLFRIEND);
    dLetter_delivery(dSv_event_flag_c::LETTER_SILVER_MEMBERSHIP);
    dLetter_delivery(dSv_event_flag_c::LETTER_GOLD_MEMBERSHIP);
    dLetter_delivery(dSv_event_flag_c::LETTER_GRANDMA);

    u8 clamped = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_CF03) + 1, 3);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_CF03, clamped);
    clamped = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_AB03) + 1, 3);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_AB03, clamped);

    if (dComIfGs_isGetItemReserve(0x0F) && dComIfGs_checkReserveItem(MO_LETTER) == 0) {
        clamped = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_CCFF) + 1, 2);
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_CCFF, clamped);
    }

    dComIfGs_setEventReg(dSv_event_flag_c::UNK_BCFF, 0);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_CB03, 0);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_CA03, 0);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_C903, 0);
    dComIfGs_offEventBit(dSv_event_flag_c::UNK_1304);
    dComIfGs_offEventBit(dSv_event_flag_c::UNK_1302);
    dComIfGs_offEventBit(dSv_event_flag_c::UNK_1301);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0120);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0040);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0020);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0010);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0008);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0004);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0002);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0001);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0180);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0140);
#if VERSION > VERSION_DEMO
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0580);
#endif
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0104);

    if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C103) == 1)
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_C103, 2);

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F10)) {
        u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BB07);
        if (reg == 7) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1F08);
        } else {
            clamped = cLib_maxLimit(reg + 1, 7);
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_BB07, clamped);
        }
    }

    if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C407) == 6)
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_C407, 7);

    u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_B907);
    if (reg & 1)
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_B907, reg + 1);

    dComIfGs_offEventBit(dSv_event_flag_c::UNK_2680);

#if VERSION > VERSION_JPN
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A20)) {
#endif
        clamped = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_A60F) + 1, 3);
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_A60F, clamped);
#if VERSION > VERSION_JPN
    }
#endif

    if (dKy_get_dayofweek() == 5) {
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2080);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2004);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2002);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2804);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2802);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2801);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2980);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_2940);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3B01);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C80);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C40);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C20);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C10);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C08);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C04);
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3C02);
    }
    
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0208);
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F01))
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3080);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0302);
    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0301);
}
