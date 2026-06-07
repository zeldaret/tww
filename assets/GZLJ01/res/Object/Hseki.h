#ifndef RES_HSEKI_H
#define RES_HSEKI_H

enum dRes_INDEX_HSEKI {
    /* BDLM */
    dRes_INDEX_HSEKI_BDL_HMON1_e=0x4,
    dRes_INDEX_HSEKI_BDL_HMON2_e=0x5,
    /* BRK  */
    dRes_INDEX_HSEKI_BRK_HMON1_e=0x8,
    dRes_INDEX_HSEKI_BRK_HMON2_e=0x9,
};

enum dRes_ID_HSEKI {
    /* BDLM */
    dRes_ID_HSEKI_BDL_HMON1_e=0x4,
    dRes_ID_HSEKI_BDL_HMON2_e=0x5,
    /* BRK  */
    dRes_ID_HSEKI_BRK_HMON1_e=0x8,
    dRes_ID_HSEKI_BRK_HMON2_e=0x9,
};

enum HMON1_JNT {
    HMON1_JNT_MONO_e=0x0,
};

enum HMON2_JNT {
    HMON2_JNT_MONO_e=0x0,
};

#endif /* !RES_HSEKI_H */