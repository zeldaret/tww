#ifndef M_DO_M_DO_MEMCARD_H
#define M_DO_M_DO_MEMCARD_H

#include "dolphin/os/OSMutex.h"
#include "global.h"

class mDoMemCd_Ctrl_c {
public:
    enum CardCommand {
        CARD_NO_COMMAND,
        CARD_RESTORE,
        CARD_STORE,
        CARD_FORMAT,
        CARD_ATTACH,
        CARD_DETACH,
    };

    /* 8001672C */ mDoMemCd_Ctrl_c();
    /* 80016730 */ void ThdInit();
    /* 800167D0 */ void main();
    /* 80016894 */ void update();
    /* 800169B4 */ void load();
    /* 80016A0C */ void restore();
    /* 80016AB0 */ s32 LoadSync(void*, u32, u32);
    /* 80016B58 */ void save(void*, u32, u32);
    /* 80016BD4 */ void store();
    /* 80016CE0 */ s32 SaveSync();
    /* 80016D74 */ u32 getStatus(u32);
    /* 80016E58 */ void command_format();
    /* 80016EA8 */ void format();
    /* 80016F2C */ s32 FormatSync();
    /* 80016FB8 */ void attach();
    /* 800170B8 */ void command_attach();
    /* 80017110 */ void detach();
    /* 80017148 */ s32 mount();
    /* 80017274 */ s32 loadfile();
    /* 800172D4 */ s32 checkspace();
    /* 80017360 */ void setCardState(s32);

    bool isCardCommNone() { return mCardCommand == CARD_NO_COMMAND; }

    /* 0x0000 */ u8 mData[0x1650];
    /* 0x1650 */ s32 mCardCommand;
    /* 0x1654 */ s32 mCardState;
    /* 0x1658 */ s32 field_0x1658;
    /* 0x165C */ s32 field_0x165c;
    /* 0x1660 */ s32 field_0x1660;
    /* 0x1664 */ OSMutex mMutex;
};  // Size: 0x167C

STATIC_ASSERT(sizeof(mDoMemCd_Ctrl_c) == 0x167C);

static int mDoMemCd_main(void*);

extern mDoMemCd_Ctrl_c g_mDoMemCd_control;

inline bool mDoMemCd_isCardCommNone() {
    return g_mDoMemCd_control.isCardCommNone();
}

inline void mDoMemCd_ThdInit() {
    g_mDoMemCd_control.ThdInit();
}

inline void mDoMemCd_save(void* i_data, u32 param_1, u32 param_2) {
    g_mDoMemCd_control.save(i_data,param_1,param_2);
}

#endif /* M_DO_M_DO_MEMCARD_H */