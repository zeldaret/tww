//
// Generated by dtk
// Translation Unit: d_a_mmusic.cpp
//

#include "d/actor/d_a_mmusic.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_save.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"

/* 00000078-0000009C       .text solidHeapCB__Q28daMmusic5Act_cFP10fopAc_ac_c */
bool daMmusic::Act_c::solidHeapCB(fopAc_ac_c* param) {
    bool uVar1;
    uVar1 = create_heap();
    return uVar1;
}

/* 0000009C-000000A4       .text create_heap__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::create_heap() {
    return true;
}

/* 000000A4-0000013C       .text Macore_is_playing__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::Macore_is_playing() {
    
    if (!dComIfGs_isStageBossEnemy(7) &&
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x2910) &&
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x2e02) &&
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x1610) &&
        dComIfGs_checkGetItem(LV3_SWORD))
    {
        return TRUE;
    }
    return FALSE;
}

/* 0000013C-000001A4       .text set_mtx__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000001A4-00000268       .text _create__Q28daMmusic5Act_cFv */
s32 daMmusic::Act_c::_create() {
    /* Nonmatching */
}

/* 00000268-000002B4       .text _delete__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_delete() {
    int iVar1;
    if (this->field_0x2A0 != 0) {
        *(unsigned int*)(iVar1 + 0x60) = 0xffffffff;  // should be an object, modify the field
        *(unsigned int*)(iVar1 + 0x20c) = *(unsigned int*)(iVar1 + 0x20c) | 1;
        *(unsigned int*)(field_0x2A0) = 0;
    }
    delete_se();
    return true;
}

/* 000002B4-000002C0       .text init_se__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::init_se() {
    (this->field_0x2D4) = 0x78;
}

/* 000002C0-000003D0       .text manage_se__Q28daMmusic5Act_cFi */
void daMmusic::Act_c::manage_se(int) {
    /* Nonmatching */
}

/* 000003D0-000003FC       .text delete_se__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::delete_se() {
    // JAIZelBasic::cbPracticeStop(JAIZelBasic::zel_basic);
}

/* 000003FC-00000554       .text _execute__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_execute() {
    /* Nonmatching */
}

/* 00000554-0000055C       .text _draw__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_draw() {
    return true;
}
