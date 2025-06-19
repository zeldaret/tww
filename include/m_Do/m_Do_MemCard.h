#ifndef M_DO_M_DO_MEMCARD_H
#define M_DO_M_DO_MEMCARD_H

#include "dolphin/os/OSMutex.h"
#include "global.h"
#include "m_Do/m_Do_MemCardRWmng.h"

class mDoMemCd_Ctrl_c {
public:
    enum CardCommand {
        CARD_NO_COMMAND,
        CARD_RESTORE,
        CARD_STORE,
        CARD_FORMAT,
        CARD_ATTACH,
        CARD_DETACH,
#if VERSION == VERSION_PAL
        CARD_RESTORE2,
#endif
    };

    mDoMemCd_Ctrl_c();
    void ThdInit();
    void main();
    void update();
    void load();
    void restore();
    s32 LoadSync(void*, u32, u32);
#if VERSION == VERSION_PAL
    void load2();
    void restore2();
    s32 LoadSync2();
#endif
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

    bool isCardCommNone() { return mCommand != CARD_NO_COMMAND; }
    u8 getNowSlot() { return mCardSlot; }
    u8* getPictDataPtr() { return mPictDataPtr; }
    u8* getPictWriteDataPtr() { return mPictDataWritePtr; }
    void setPictWriteDataPtr(u8* v) { mPictDataWritePtr = v; }
    void setPictDataPtr(u8* v) { mPictDataPtr = v; }
    void setCardSerialNo(u64 v) { mCardSerialNo = v; }
    void setDataVersion(u32 v) { mDataVersion = v; }
    u8 getCopyToPos() { return mCopyToPos; }
    void setCopyToPos(u8 pos) { mCopyToPos = pos; }

    void clearProbeStat() {}
    u64 getCardSerialNo() { return mCardSerialNo; }
    void getDataVersion() {}
    void getProbeStat() {}

    /* 0x0000 */ u8 mData[3 * sizeof(card_gamedata)];
    /* 0x1650 */ u8* mPictDataPtr;
    /* 0x1654 */ u8* mPictDataWritePtr;
    /* 0x1658 */ u8 mCardSlot;
    /* 0x1659 */ u8 mCopyToPos;
    /* 0x165A */ u8 field_0x165A;
    /* 0x165B */ u8 field_0x165B;
    /* 0x165C */ s32 mCommand;
    /* 0x1660 */ s32 field_0x1660;
    /* 0x1664 */ OSMutex mMutex;
    /* 0x167C */ OSCond mCond;
    /* 0x1684 */ u32 field_0x1684;
    /* 0x1688 */ u64 mCardSerialNo;
    /* 0x1690 */ u32 mDataVersion;
    /* 0x1694 */ u32 field_0x1694;
};  // Size: 0x1698

static int mDoMemCd_main(void*);

extern mDoMemCd_Ctrl_c g_mDoMemCd_control;

inline bool mDoMemCd_isCardCommNone() {
    return g_mDoMemCd_control.isCardCommNone();
}

inline void mDoMemCd_ThdInit() {
    g_mDoMemCd_control.ThdInit();
}

inline void mDoMemCd_Save(void* i_data, u32 param_1, u32 param_2) {
    g_mDoMemCd_control.save(i_data,param_1,param_2);
}

inline u8 mDoMemCd_getNowSlot() {
    return g_mDoMemCd_control.getNowSlot();
}

inline u64 mDoMemCd_getCardSerialNo() {
    return g_mDoMemCd_control.getCardSerialNo();
}

inline void mDoMemCd_setCardSerialNo(u64 v) {
    g_mDoMemCd_control.setCardSerialNo(v);
}

inline void mDoMemCd_setDataVersion(u32 v) {
    g_mDoMemCd_control.setDataVersion(v);
}

inline u8* mDoMemCd_getPictDataPtr() {
    return g_mDoMemCd_control.getPictDataPtr();
}

inline void mDoMemCd_setPictDataPtr(u8* v) {
    g_mDoMemCd_control.setPictDataPtr(v);
}

inline u8* mDoMemCd_getPictWriteDataPtr() {
    return g_mDoMemCd_control.getPictWriteDataPtr();
}

inline void mDoMemCd_setPictWriteDataPtr(u8* v) {
    g_mDoMemCd_control.setPictWriteDataPtr(v);
}

inline u8 mDoMemCd_getCopyToPos() {
    return g_mDoMemCd_control.getCopyToPos();
}

inline void mDoMemCd_setCopyToPos(u8 pos) {
    g_mDoMemCd_control.setCopyToPos(pos);
}

inline s32 mDoMemCd_SaveSync() {
    return g_mDoMemCd_control.SaveSync();
}

inline s32 mDoMemCd_FormatSync() {
    return g_mDoMemCd_control.FormatSync();
}

inline void mDoMemCd_UpDate() {
    g_mDoMemCd_control.update();
}

inline u32 mDoMemCd_getStatus(u32 status) {
    return g_mDoMemCd_control.getStatus(status);
}

inline void mDoMemCd_Format() {}
inline void mDoMemCd_Load() {}
inline void mDoMemCd_LoadSync(void*, u32, u32) {}
inline void mDoMemCd_clearProbeStat() {}
inline void mDoMemCd_getDataVersion() {}
inline void mDoMemCd_getProbeStat() {}

#endif /* M_DO_M_DO_MEMCARD_H */
