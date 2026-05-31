#ifndef RES_AM2_H
#define RES_AM2_H

enum dRes_INDEX_AM2 {
    /* BCK  */
    dRes_INDEX_AM2_BCK_BURUBURU_e=0x6,
    dRes_INDEX_AM2_BCK_DAMAGE_e=0x7,
    dRes_INDEX_AM2_BCK_DEAD1_e=0x8,
    dRes_INDEX_AM2_BCK_DEAD2_e=0x9,
    dRes_INDEX_AM2_BCK_DEAD3_e=0xA,
    dRes_INDEX_AM2_BCK_JUMP_e=0xB,
    dRes_INDEX_AM2_BCK_MAHI_e=0xC,
    dRes_INDEX_AM2_BCK_SLEEP_e=0xD,
    dRes_INDEX_AM2_BCK_START_e=0xE,
    dRes_INDEX_AM2_BCK_WAIT_e=0xF,
    /* BDLM */
    dRes_INDEX_AM2_BDL_AM2_e=0x12,
    /* BRK  */
    dRes_INDEX_AM2_BRK_AM2_e=0x15,
    /* BTK  */
    dRes_INDEX_AM2_BTK_AM2_e=0x18,
};

enum dRes_ID_AM2 {
    /* BCK  */
    dRes_ID_AM2_BCK_BURUBURU_e=0x6,
    dRes_ID_AM2_BCK_DAMAGE_e=0x7,
    dRes_ID_AM2_BCK_DEAD1_e=0x8,
    dRes_ID_AM2_BCK_DEAD2_e=0x9,
    dRes_ID_AM2_BCK_DEAD3_e=0xA,
    dRes_ID_AM2_BCK_JUMP_e=0xB,
    dRes_ID_AM2_BCK_MAHI_e=0xC,
    dRes_ID_AM2_BCK_SLEEP_e=0xD,
    dRes_ID_AM2_BCK_START_e=0xE,
    dRes_ID_AM2_BCK_WAIT_e=0xF,
    /* BDLM */
    dRes_ID_AM2_BDL_AM2_e=0x12,
    /* BRK  */
    dRes_ID_AM2_BRK_AM2_e=0x15,
    /* BTK  */
    dRes_ID_AM2_BTK_AM2_e=0x18,
};

enum AM2_JNT {
    AM2_JNT_BODY_e=0x0,
    AM2_JNT_COA_e=0x1,
    AM2_JNT_EYE_e=0x2,
    AM2_JNT_TOGE_e=0x3,
};

#endif /* !RES_AM2_H */