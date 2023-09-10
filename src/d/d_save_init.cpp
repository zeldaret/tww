/**
 * d_save_init.cpp
 *
 */

#include "d/d_save_init.h"
#include "d/d_com_inf_game.h"

// move later
struct daNpc_Kg1_c {
    static u8 m_highscore;
};

/* 8005EF88-8005EFDC       .text setInitEventBit__Fv */
void setInitEventBit() {
    dComIfGs_setEventReg(0xBEFF, daNpc_Kg1_c::m_highscore);
    dComIfGs_setEventReg(0x7EFF, 0xE);
}
