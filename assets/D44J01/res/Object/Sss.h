#ifndef RES_SSS_H
#define RES_SSS_H

enum dRes_INDEX_SSS {
    /* BCK  */
    dRes_INDEX_SSS_BCK_SSS_HIRAKU_e=0x5,
    dRes_INDEX_SSS_BCK_SSS_TOJIRU_e=0x6,
    /* BMD  */
    dRes_INDEX_SSS_BMD_SSS_HAND_e=0x9,
    /* TEX  */
    dRes_INDEX_SSS_BTI_SSS_e=0xC,
};

enum dRes_ID_SSS {
    /* BCK  */
    dRes_ID_SSS_BCK_SSS_HIRAKU_e=0x5,
    dRes_ID_SSS_BCK_SSS_TOJIRU_e=0x6,
    /* BMD  */
    dRes_ID_SSS_BMD_SSS_HAND_e=0x9,
    /* TEX  */
    dRes_ID_SSS_BTI_SSS_e=0xC,
};

enum SSS_HAND_JNT {
    SSS_HAND_JNT_UDE_e=0x0,
    SSS_HAND_JNT_NAKAYUBI_e=0x1,
    SSS_HAND_JNT_YUBI1_e=0x2,
    SSS_HAND_JNT_YUBI2_e=0x3,
};

#endif /* !RES_SSS_H */