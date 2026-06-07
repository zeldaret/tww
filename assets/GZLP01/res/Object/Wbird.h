#ifndef RES_WBIRD_H
#define RES_WBIRD_H

enum dRes_INDEX_WBIRD {
    /* BAS  */
    dRes_INDEX_WBIRD_BAS_KA_WAIT1_e=0x5,
    /* BCK  */
    dRes_INDEX_WBIRD_BCK_KA_WAIT1_e=0x8,
    /* BMD  */
    dRes_INDEX_WBIRD_BMD_KA_e=0xB,
};

enum dRes_ID_WBIRD {
    /* BAS  */
    dRes_ID_WBIRD_BAS_KA_WAIT1_e=0x5,
    /* BCK  */
    dRes_ID_WBIRD_BCK_KA_WAIT1_e=0x8,
    /* BMD  */
    dRes_ID_WBIRD_BMD_KA_e=0xB,
};

enum KA_JNT {
    KA_JNT_KA_ALL_ROOT_e=0x0,
    KA_JNT_KA_J_ROOT_e=0x1,
    KA_JNT_J_KA_SPIN1_e=0x2,
    KA_JNT_J_KA_LEG_L1_e=0x3,
    KA_JNT_J_KA_TOE_L1_e=0x4,
    KA_JNT_J_KA_LEG_R1_e=0x5,
    KA_JNT_J_KA_TOE_R1_e=0x6,
    KA_JNT_J_KA_NECK1_e=0x7,
    KA_JNT_J_KA_HEAD1_e=0x8,
    KA_JNT_J_KA_MOUTH1_e=0x9,
    KA_JNT_J_KA_WING_L1_e=0xA,
    KA_JNT_J_KA_WING_L2_e=0xB,
    KA_JNT_J_KA_WING_L3_e=0xC,
    KA_JNT_J_KA_WING_R1_e=0xD,
    KA_JNT_J_KA_WING_R2_e=0xE,
    KA_JNT_J_KA_WING_R3_e=0xF,
};

#endif /* !RES_WBIRD_H */