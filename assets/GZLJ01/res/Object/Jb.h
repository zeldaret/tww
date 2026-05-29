#ifndef RES_JB_H
#define RES_JB_H

enum dRes_INDEX_JB {
    /* BCKS */
    dRes_INDEX_JB_BCK_JB_APPEAR_e=0x7,
    dRes_INDEX_JB_BCK_JB_WAIT01_e=0x8,
    dRes_INDEX_JB_BCK_YJBSM00_e=0x9,
    /* BDLM */
    dRes_INDEX_JB_BDL_JB_e=0xC,
    /* BRK  */
    dRes_INDEX_JB_BRK_JB_LAMP_e=0xF,
    dRes_INDEX_JB_BRK_YJBSM00_e=0x10,
    dRes_INDEX_JB_BRK_LF_e=0x11,
    /* BMDM */
    dRes_INDEX_JB_BMD_YJBSM00_e=0x14,
    dRes_INDEX_JB_BMD_LF_e=0x15,
    /* BTK  */
    dRes_INDEX_JB_BTK_YJBSM00_e=0x18,
};

enum dRes_ID_JB {
    /* BCKS */
    dRes_ID_JB_BCK_JB_APPEAR_e=0x0,
    dRes_ID_JB_BCK_JB_WAIT01_e=0x1,
    dRes_ID_JB_BCK_YJBSM00_e=0x4,
    /* BDLM */
    dRes_ID_JB_BDL_JB_e=0x2,
    /* BRK  */
    dRes_ID_JB_BRK_JB_LAMP_e=0x3,
    dRes_ID_JB_BRK_YJBSM00_e=0x5,
    dRes_ID_JB_BRK_LF_e=0x8,
    /* BMDM */
    dRes_ID_JB_BMD_YJBSM00_e=0x6,
    dRes_ID_JB_BMD_LF_e=0x9,
    /* BTK  */
    dRes_ID_JB_BTK_YJBSM00_e=0x7,
};

enum JB_JNT {
    JB_JNT_CENTER_e=0x0,
    JB_JNT_BACKBONE1_e=0x1,
    JB_JNT_BACKBONE2_e=0x2,
    JB_JNT_NECK_e=0x3,
    JB_JNT_HEAD_e=0x4,
    JB_JNT_LJAW1_e=0x5,
    JB_JNT_LJAW2_e=0x6,
    JB_JNT_LJAW3_e=0x7,
    JB_JNT_UJAW_SCALE_e=0x8,
    JB_JNT_UJAW_e=0x9,
    JB_JNT_ANTENNA1_e=0xA,
    JB_JNT_ANTENNA2_e=0xB,
    JB_JNT_ANTENNA3_e=0xC,
    JB_JNT_ANTENNA4_e=0xD,
    JB_JNT_ANTENNA5_e=0xE,
    JB_JNT_ANTENNA6_e=0xF,
    JB_JNT_ANTENNA7_e=0x10,
    JB_JNT_ANTENNA8_e=0x11,
    JB_JNT_ANTENNA9_e=0x12,
    JB_JNT_JB_RING_e=0x13,
    JB_JNT_JB_CASE_e=0x14,
    JB_JNT_EYEL_e=0x15,
    JB_JNT_EYER_e=0x16,
    JB_JNT_EYELIDL_e=0x17,
    JB_JNT_EYELIDR_e=0x18,
    JB_JNT_THROAT1_e=0x19,
    JB_JNT_THROAT2_e=0x1A,
    JB_JNT_TONGUE1_e=0x1B,
    JB_JNT_TONGUE2_e=0x1C,
    JB_JNT_TONGUE3_e=0x1D,
    JB_JNT_TONGUE4_e=0x1E,
    JB_JNT_TONGUE5_e=0x1F,
    JB_JNT_TONGUE6_e=0x20,
    JB_JNT_FINL1_e=0x21,
    JB_JNT_FINL2_e=0x22,
    JB_JNT_FINL3_e=0x23,
    JB_JNT_FINL4_e=0x24,
    JB_JNT_FINR1_e=0x25,
    JB_JNT_FINR2_e=0x26,
    JB_JNT_FINR3_e=0x27,
    JB_JNT_FINR4_e=0x28,
    JB_JNT_WAIST1_e=0x29,
    JB_JNT_BFIN_e=0x2A,
    JB_JNT_WAIST2_e=0x2B,
};

enum YJBSM00_JNT {
    YJBSM00_JNT_YJBSM00_e=0x0,
    YJBSM00_JNT_A00_e=0x1,
    YJBSM00_JNT_JABUSUIMEN_e=0x2,
    YJBSM00_JNT_SPLASH_e=0x3,
};

enum LF_JNT {
    LF_JNT_HIKARI_e=0x0,
};

#endif /* !RES_JB_H */