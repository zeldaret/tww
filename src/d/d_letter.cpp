//
// Generated by dtk
// Translation Unit: d_letter.cpp
//

#include "d/d_letter.h"
#include "d/d_com_inf_game.h"

enum dLetterStts_e {
    NOSEND_e,
    SEND_e,
    STOCK_e,
    READ_e,
};

/* 801990CC-80199108       .text dLetter_isNoSend__FUs */
bool dLetter_isNoSend(u16 idx) {
    return dComIfGs_getEventReg(idx) == NOSEND_e;
}

/* 80199108-8019913C       .text dLetter_send__FUs */
void dLetter_send(u16 idx) {
    dComIfGs_setEventReg(idx, SEND_e);
}

/* 8019913C-8019917C       .text dLetter_isSend__FUs */
bool dLetter_isSend(u16 idx) {
    return dComIfGs_getEventReg(idx) == SEND_e;
}

/* 8019917C-801991B0       .text dLetter_stock__FUs */
void dLetter_stock(u16 idx) {
    dComIfGs_setEventReg(idx, STOCK_e);
}

/* 801991B0-801991F0       .text dLetter_isStock__FUs */
bool dLetter_isStock(u16 idx) {
    return dComIfGs_getEventReg(idx) == STOCK_e;
}

/* 801991F0-80199224       .text dLetter_read__FUs */
void dLetter_read(u16 idx) {
    dComIfGs_setEventReg(idx, READ_e);
}

/* 80199224-80199264       .text dLetter_isRead__FUs */
bool dLetter_isRead(u16 idx) {
    return dComIfGs_getEventReg(idx) == READ_e;
}

/* 80199264-801992A0       .text dLetter_delivery__FUs */
void dLetter_delivery(u16 idx) {
    if (dLetter_isSend(idx))
        dLetter_stock(idx);
}

/* 801992A0-801992DC       .text dLetter_autoStock__FUs */
void dLetter_autoStock(u16 idx) {
    if (dLetter_isNoSend(idx))
        dLetter_stock(idx);
}

/* 801992DC-80199308       .text dLetter_isDelivery__FUs */
bool dLetter_isDelivery(u16 idx) {
    return !dLetter_isNoSend(idx);
}

