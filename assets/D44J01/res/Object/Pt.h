#ifndef RES_PT_H
#define RES_PT_H

enum dRes_INDEX_PT {
    /* BCK  */
    dRes_INDEX_PT_BCK_ATACK_e=0x6,
    dRes_INDEX_PT_BCK_BWALK_e=0x7,
    dRes_INDEX_PT_BCK_HAPPY_e=0x8,
    dRes_INDEX_PT_BCK_JUMP_e=0x9,
    dRes_INDEX_PT_BCK_KOKE_e=0xA,
    dRes_INDEX_PT_BCK_SIRIMOTI_e=0xB,
    dRes_INDEX_PT_BCK_WAIT_e=0xC,
    /* BDLM */
    dRes_INDEX_PT_BDL_PT_e=0xF,
    /* BRK  */
    dRes_INDEX_PT_BRK_PT_e=0x12,
    /* BTP  */
    dRes_INDEX_PT_BTP_MABATAKI_e=0x15,
};

enum dRes_ID_PT {
    /* BCK  */
    dRes_ID_PT_BCK_ATACK_e=0x6,
    dRes_ID_PT_BCK_BWALK_e=0x7,
    dRes_ID_PT_BCK_HAPPY_e=0x8,
    dRes_ID_PT_BCK_JUMP_e=0x9,
    dRes_ID_PT_BCK_KOKE_e=0xA,
    dRes_ID_PT_BCK_SIRIMOTI_e=0xB,
    dRes_ID_PT_BCK_WAIT_e=0xC,
    /* BDLM */
    dRes_ID_PT_BDL_PT_e=0xF,
    /* BRK  */
    dRes_ID_PT_BRK_PT_e=0x12,
    /* BTP  */
    dRes_ID_PT_BTP_MABATAKI_e=0x15,
};

enum PT_JNT {
    PT_JNT_PT_CENTER_e=0x0,
    PT_JNT_KOSHI_e=0x1,
    PT_JNT_ASHILA_e=0x2,
    PT_JNT_ASHILB_e=0x3,
    PT_JNT_ASHIRA_e=0x4,
    PT_JNT_ASHIRB_e=0x5,
    PT_JNT_SHIPPO_e=0x6,
    PT_JNT_MUNE_e=0x7,
    PT_JNT_ATAMA_e=0x8,
    PT_JNT_MIMIL_e=0x9,
    PT_JNT_MIMIR_e=0xA,
    PT_JNT_UDELA_e=0xB,
    PT_JNT_UDELB_e=0xC,
    PT_JNT_UDERA_e=0xD,
    PT_JNT_UDERB_e=0xE,
    PT_JNT_FORK_e=0xF,
};

#endif /* !RES_PT_H */