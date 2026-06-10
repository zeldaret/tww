#ifndef RES_HMOS_H
#define RES_HMOS_H

enum dRes_INDEX_HMOS {
    /* BDL  */
    dRes_INDEX_HMOS_BDL_HMOS1_e=0x5,
    dRes_INDEX_HMOS_BDL_HMOS2_e=0x6,
    dRes_INDEX_HMOS_BDL_HMOS3_e=0x7,
    dRes_INDEX_HMOS_BDL_HMOSUP1_e=0x8,
    dRes_INDEX_HMOS_BDL_HMOSUP2_e=0x9,
    /* BDLM */
    dRes_INDEX_HMOS_BDL_HMOS2T_e=0xC,
    /* BRK  */
    dRes_INDEX_HMOS_BRK_HMOS2T_e=0xF,
    dRes_INDEX_HMOS_BRK_HMOSUP1_e=0x10,
    dRes_INDEX_HMOS_BRK_HMOSUP2_e=0x11,
};

enum dRes_ID_HMOS {
    /* BDL  */
    dRes_ID_HMOS_BDL_HMOS1_e=0x5,
    dRes_ID_HMOS_BDL_HMOS2_e=0x6,
    dRes_ID_HMOS_BDL_HMOS3_e=0x7,
    dRes_ID_HMOS_BDL_HMOSUP1_e=0x8,
    dRes_ID_HMOS_BDL_HMOSUP2_e=0x9,
    /* BDLM */
    dRes_ID_HMOS_BDL_HMOS2T_e=0xC,
    /* BRK  */
    dRes_ID_HMOS_BRK_HMOS2T_e=0xF,
    dRes_ID_HMOS_BRK_HMOSUP1_e=0x10,
    dRes_ID_HMOS_BRK_HMOSUP2_e=0x11,
};

enum HMOS1_JNT {
    HMOS1_JNT_SITA_e=0x0,
};

enum HMOS2_JNT {
    HMOS2_JNT_SITA_e=0x0,
};

enum HMOS3_JNT {
    HMOS3_JNT_MONO_e=0x0,
};

enum HMOSUP1_JNT {
    HMOSUP1_JNT_UE_e=0x0,
};

enum HMOSUP2_JNT {
    HMOSUP2_JNT_UE_e=0x0,
};

enum HMOS2T_JNT {
    HMOS2T_JNT_PCYLINDER30_e=0x0,
};

#endif /* !RES_HMOS_H */