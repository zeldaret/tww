#ifndef RES_OS_H
#define RES_OS_H

enum dRes_INDEX_OS {
    /* BCKS */
    dRes_INDEX_OS_BCK_OS_AWAKE_e=0x5,
    dRes_INDEX_OS_BCK_OS_MOVE01_e=0x6,
    /* BDLM */
    dRes_INDEX_OS_BDL_OS_e=0x9,
    /* BRK  */
    dRes_INDEX_OS_BRK_LINK_e=0xC,
    dRes_INDEX_OS_BRK_OS_AWAKE_e=0xD,
    dRes_INDEX_OS_BRK_TENMETU_e=0xE,
    dRes_INDEX_OS_BRK_TURN_OFF_e=0xF,
    dRes_INDEX_OS_BRK_TURN_ON_e=0x10,
};

enum dRes_ID_OS {
    /* BCKS */
    dRes_ID_OS_BCK_OS_AWAKE_e=0x5,
    dRes_ID_OS_BCK_OS_MOVE01_e=0x6,
    /* BDLM */
    dRes_ID_OS_BDL_OS_e=0x9,
    /* BRK  */
    dRes_ID_OS_BRK_LINK_e=0xC,
    dRes_ID_OS_BRK_OS_AWAKE_e=0xD,
    dRes_ID_OS_BRK_TENMETU_e=0xE,
    dRes_ID_OS_BRK_TURN_OFF_e=0xF,
    dRes_ID_OS_BRK_TURN_ON_e=0x10,
};

enum OS_JNT {
    OS_JNT_BODY1_JOINT_e=0x0,
    OS_JNT_BODY2_JOINT_e=0x1,
    OS_JNT_HEAD_JOINT_e=0x2,
    OS_JNT_TUNO1_JOINT_e=0x3,
    OS_JNT_TUNO2_JOINT_e=0x4,
    OS_JNT_TUNO3_JOINT_e=0x5,
    OS_JNT_TRIFORCE_JOINT_e=0x6,
};

#endif /* !RES_OS_H */