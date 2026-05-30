#ifndef RES_HDAI1_H
#define RES_HDAI1_H

enum dRes_INDEX_HDAI1 {
    /* BDLM */
    dRes_INDEX_HDAI1_BDL_HDAI1_e=0x5,
    /* BRK  */
    dRes_INDEX_HDAI1_BRK_HDAI1_e=0x8,
    /* DZB  */
    dRes_INDEX_HDAI1_DZB_HDAI_e=0xB,
};

enum dRes_ID_HDAI1 {
    /* BDLM */
    dRes_ID_HDAI1_BDL_HDAI1_e=0x5,
    /* BRK  */
    dRes_ID_HDAI1_BRK_HDAI1_e=0x8,
    /* DZB  */
    dRes_ID_HDAI1_DZB_HDAI_e=0xB,
};

enum HDAI1_JNT {
    HDAI1_JNT_HDAI1_00_e=0x0,
    HDAI1_JNT_A00_e=0x1,
    HDAI1_JNT_POLYSURFACE2038_e=0x2,
    HDAI1_JNT_POLYSURFACE2039_e=0x3,
};

#endif /* !RES_HDAI1_H */