#ifndef M_DO_GBA_COM_H
#define M_DO_GBA_COM_H

#include "global.h"

class mDoGaC_DataManag_c {
public:
    /* 0x0 */ void* mpData;
    /* 0x4 */ u8 mStatus;
    /* 0x5 */ u8 field_0x5;
};

struct mDoGaC_unk_data {
    /* 0x00 */ u32* field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ u8 field_0x8;
    /* 0x0C */ u32 field_0xc;
};

class mDoGaC_agbCom_c {
public:
    void mDoGaC_Initial(mDoGaC_DataManag_c*, u8);
    void mDoGaC_ComOpen();
    void mDoGaC_ComClose();
    void mDoGaC_ComStart();
    void mDoGaC_ComStop();
    void mDoGaC_GbaReboot();
    void mDoGaC_GbaReset();
    void mDoGaC_ComRestart();
    void mDoGaC_Connect();
    void mDoGaC_ConnectSleep();
    void mDoGaC_ConnectWake();
    int mDoGaC_GbaLink();
    int mDoGaC_SendDataSet(u32*, int, u8, u32);
    void mDoGaC_SendDataWrite();
    int mDoGaC_SendEntry(u8, u32);
    int mDoGaC_SendStatusCheck(u8);
    int mDoGaC_SendEndCheck(u8);
    BOOL mDoGaC_RecvStatusCheck(u8);
    void mDoGaC_DataStatusReset(u8);
    int mDoGaC_StatusSendSet(u8);
    void mDoGaC_ProbeCheck0();
    void mDoGaC_ProbeCheck1();
    void mDoGaC_CodeExchange0();
    void mDoGaC_CodeExchange1();
    void mDoGaC_CodeExchange2();
    void mDoGaC_CodeExchange3();
    void mDoGaC_CodeExchange4();
    void mDoGaC_ContextCheck();
    void mDoGaC_ContextSend();
    void mDoGaC_ContextRead();
    void mDoGaC_GbaWrite();
    void mDoGaC_WriteResult();
    void mDoGaC_GbaRead();
    void mDoGaC_ReadResult();

    mDoGaC_agbCom_c() {}
    ~mDoGaC_agbCom_c() {}

    u8 getEnable() { return mEnable; }
    void onEnable() { mEnable = 1; }
    u8 getReConnect() { return mReConnect; }
    u8 getPortNo() { return mPortNo; }
    void setPortNo(u8 port) { mPortNo = port; }
    u8 getDataStatus(u8 param_0) { return mpDataManager[param_0].mStatus; }

    /* 0x000 */ u8 mEnable;
    /* 0x001 */ u8 field_0x1;
    /* 0x002 */ u8 field_0x2;
    /* 0x003 */ u8 mReConnect;
    /* 0x004 */ u8 field_0x4;
    /* 0x005 */ u8 field_0x5;
    /* 0x006 */ u8 field_0x6;
    /* 0x007 */ u8 field_0x7;
    /* 0x008 */ u8 field_0x8;
    /* 0x009 */ u8 field_0x9;
    /* 0x00A */ u8 field_0xa;
    /* 0x00B */ u8 field_0xb;
    /* 0x00C */ mDoGaC_unk_data field_0xc[16];
    /* 0x10C */ u8 mDataManagerCount;
    /* 0x10D */ u8 mPortNo;
    /* 0x10E */ u8 field_0x10e;
    /* 0x10F */ u8 field_0x10F[0x110 - 0x10F];
    /* 0x110 */ mDoGaC_DataManag_c* mpDataManager;
    /* 0x114 */ u32 field_0x114;
    /* 0x118 */ u32 field_0x118;
    /* 0x11C */ u32 field_0x11C;
#if VERSION > VERSION_DEMO
    /* 0x120 */ u32 field_0x120;
    /* 0x124 */ u8 field_0x124[0x128 - 0x124];
#endif
    struct {
        u8 field_0x0;
        union {
            u32 U32;
            struct {
                u32 _12c_0 : 2;
                u32 _12c_2 : 15;
            } U32bits;
            struct {
                u8 _12c_0 : 2;
                u8 _12c_2 : 6;
            } U8;
            struct {
                u16 _12c;
                u16 _12e_0 : 1;
                u16 _12e_1 : 15;
            } U16;
        } field_0x4;
    } field_0x128[1];
};

extern mDoGaC_agbCom_c g_mDoGaC_gbaCom;
extern mDoGaC_DataManag_c TestDataManager[16];

u32 BigLittleChange(u32);

inline void mDoGaC_Initial(mDoGaC_DataManag_c* i_dataMngP, u8 i_dataMngCount) {
    g_mDoGaC_gbaCom.mDoGaC_Initial(i_dataMngP, i_dataMngCount);
}

inline int mDoGaC_GbaLink() {
    return g_mDoGaC_gbaCom.mDoGaC_GbaLink();
}

inline u8 mDoGaC_getComEnable() {
    return g_mDoGaC_gbaCom.getEnable();
};

inline void mDoGaC_onComEnable() {
    g_mDoGaC_gbaCom.onEnable();
}

inline void mDoGaC_ComStart() {
    g_mDoGaC_gbaCom.mDoGaC_ComStart();
}

inline u8 mDoGaC_getPortNo() {
    return g_mDoGaC_gbaCom.getPortNo();
}

inline void mDoGaC_setPortNo(u8 port) {
    g_mDoGaC_gbaCom.setPortNo(port);
}

inline void mDoGaC_GbaReboot() {
    g_mDoGaC_gbaCom.mDoGaC_GbaReboot();
}

inline int mDoGac_SendDataSet(u32* param_0, int param_1, u8 param_2, u32 param_3) {
    return g_mDoGaC_gbaCom.mDoGaC_SendDataSet(param_0, param_1, param_2, param_3);
}

inline int mDoGac_SendEndCheck(u8 param_0) {
    return g_mDoGaC_gbaCom.mDoGaC_SendEndCheck(param_0);
}

inline void mDoGaC_SendEntry(u8 param_0, u32 param_1) {
    g_mDoGaC_gbaCom.mDoGaC_SendEntry(param_0, param_1);
}

inline BOOL mDoGac_SendStatusCheck(u8 param_0) {
    return g_mDoGaC_gbaCom.mDoGaC_SendStatusCheck(param_0);
}

inline BOOL mDoGaC_RecvStatusCheck(u8 param_0) {
    return g_mDoGaC_gbaCom.mDoGaC_RecvStatusCheck(param_0);
}

inline void mDoGaC_DataStatusReset(u8 param_0) {
    g_mDoGaC_gbaCom.mDoGaC_DataStatusReset(param_0);
}

inline u8 mDoGaC_getDataStatus(u8 param_0) {
    return g_mDoGaC_gbaCom.getDataStatus(param_0);
}

inline void mDoGaC_Connect() {
    g_mDoGaC_gbaCom.mDoGaC_Connect();
}

inline void mDoGaC_ConnectWake() {
    g_mDoGaC_gbaCom.mDoGaC_ConnectWake();
}

inline void mDoGaC_ConnectSleep() {
    g_mDoGaC_gbaCom.mDoGaC_ConnectSleep();
}

inline u8 mDoGaC_getReConnect() {
    return g_mDoGaC_gbaCom.getReConnect();
}

#endif /* M_DO_GBA_COM_H */
