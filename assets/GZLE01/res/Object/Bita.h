#ifndef RES_BITA_H
#define RES_BITA_H

enum dRes_INDEX_BITA {
    /* BDLM */
    dRes_INDEX_BITA_BDL_EF_BTDITA0_e=0x5,
    dRes_INDEX_BITA_BDL_EF_BTDITA1_e=0x6,
    dRes_INDEX_BITA_BDL_MBIT1_e=0x7,
    dRes_INDEX_BITA_BDL_MBIT2_e=0x8,
    /* BRK  */
    dRes_INDEX_BITA_BRK_EF_BTDITA0_e=0xB,
    dRes_INDEX_BITA_BRK_EF_BTDITA1_e=0xC,
    /* DZB  */
    dRes_INDEX_BITA_DZB_MBIT1_e=0xF,
    dRes_INDEX_BITA_DZB_MBIT2_e=0x10,
};

enum dRes_ID_BITA {
    /* BDLM */
    dRes_ID_BITA_BDL_EF_BTDITA0_e=0x5,
    dRes_ID_BITA_BDL_EF_BTDITA1_e=0x6,
    dRes_ID_BITA_BDL_MBIT1_e=0x7,
    dRes_ID_BITA_BDL_MBIT2_e=0x8,
    /* BRK  */
    dRes_ID_BITA_BRK_EF_BTDITA0_e=0xB,
    dRes_ID_BITA_BRK_EF_BTDITA1_e=0xC,
    /* DZB  */
    dRes_ID_BITA_DZB_MBIT1_e=0xF,
    dRes_ID_BITA_DZB_MBIT2_e=0x10,
};

enum EF_BTDITA0_JNT {
    EF_BTDITA0_JNT_MBIT1_00_e=0x0,
    EF_BTDITA0_JNT_A00_e=0x1,
    EF_BTDITA0_JNT_ITA1_e=0x2,
};

enum EF_BTDITA1_JNT {
    EF_BTDITA1_JNT_MBIT2_00_e=0x0,
    EF_BTDITA1_JNT_A00_e=0x1,
    EF_BTDITA1_JNT_ITA2_e=0x2,
};

enum MBIT1_JNT {
    MBIT1_JNT_MBIT1_00_e=0x0,
    MBIT1_JNT_A00_e=0x1,
    MBIT1_JNT_ITA1_e=0x2,
};

enum MBIT2_JNT {
    MBIT2_JNT_MBIT2_00_e=0x0,
    MBIT2_JNT_A00_e=0x1,
    MBIT2_JNT_ITA2_e=0x2,
};

#endif /* !RES_BITA_H */