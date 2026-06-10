#ifndef RES_HLIFT_H
#define RES_HLIFT_H

enum dRes_INDEX_HLIFT {
    /* BDL  */
    dRes_INDEX_HLIFT_BDL_HLIFT_e=0x4,
    dRes_INDEX_HLIFT_BDL_HLIFTB_e=0x5,
    dRes_INDEX_HLIFT_BDL_HLIFTC_e=0x6,
    /* DZB  */
    dRes_INDEX_HLIFT_DZB_HLIFT_e=0x9,
    dRes_INDEX_HLIFT_DZB_HLIFTB_e=0xA,
};

enum dRes_ID_HLIFT {
    /* BDL  */
    dRes_ID_HLIFT_BDL_HLIFT_e=0x4,
    dRes_ID_HLIFT_BDL_HLIFTB_e=0x5,
    dRes_ID_HLIFT_BDL_HLIFTC_e=0x6,
    /* DZB  */
    dRes_ID_HLIFT_DZB_HLIFT_e=0x9,
    dRes_ID_HLIFT_DZB_HLIFTB_e=0xA,
};

enum HLIFT_JNT {
    HLIFT_JNT_MONO_e=0x0,
};

enum HLIFTB_JNT {
    HLIFTB_JNT_MONO_e=0x0,
};

enum HLIFTC_JNT {
    HLIFTC_JNT_PPLANE1_e=0x0,
};

#endif /* !RES_HLIFT_H */