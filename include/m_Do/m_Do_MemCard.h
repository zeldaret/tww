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

    mDoMemCd_Ctrl_c();
    void ThdInit();
    void main();
    void update();
    void load();
    void load2();
    void restore();
    s32 LoadSync(void*, u32, u32);
    s32 LoadSync2();
    void save(void*, u32, u32);
    void store();
    s32 SaveSync();
    u32 getStatus(u32);
    void command_format();
    void format();
    s32 FormatSync();
    void attach();
    void command_attach();
    void detach();
    s32 mount();
    s32 loadfile();
    s32 checkspace();
    void setCardState(s32);

    bool isCardCommNone() { return mCardCommand == CARD_NO_COMMAND; }

    /* 0x0000 */ u8 mData[0x1650];
    /* 0x1650 */ s32 mCardCommand;
    /* 0x1654 */ s32 mCardState;
    /* 0x1658 */ u8 mCardSlot;
    /* 0x1659 */ u8 field_0x1659;
    /* 0x165A */ u8 field_0x165A;
    /* 0x165B */ u8 field_0x165B;
    /* 0x165C */ s32 mCommand;
    /* 0x1660 */ s32 field_0x1660;
    /* 0x1664 */ OSMutex mMutex;
    /* 0x167C */ OSCond mCond;
    /* 0x1684 */ u32 field_0x1684[5];
};  // Size: 0x1698

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
