#ifndef RES_SYAN_H
#define RES_SYAN_H

enum dRes_INDEX_SYAN {
    /* BCK  */
    dRes_INDEX_SYAN_BCK_SYAN_e=0x4,
    dRes_INDEX_SYAN_BCK_SYAN2_e=0x5,
    /* BDL  */
    dRes_INDEX_SYAN_BDL_SYAN_e=0x8,
};

enum dRes_ID_SYAN {
    /* BCK  */
    dRes_ID_SYAN_BCK_SYAN_e=0x4,
    dRes_ID_SYAN_BCK_SYAN2_e=0x5,
    /* BDL  */
    dRes_ID_SYAN_BDL_SYAN_e=0x8,
};

enum SYAN_JNT {
    SYAN_JNT_SYAN_e=0x0,
    SYAN_JNT_CHAIN_e=0x1,
    SYAN_JNT_JOINT5_e=0x2,
    SYAN_JNT_JOINT6_e=0x3,
    SYAN_JNT_JOINT7_e=0x4,
    SYAN_JNT_JOINT8_e=0x5,
    SYAN_JNT_DECO_e=0x6,
};

#endif /* !RES_SYAN_H */