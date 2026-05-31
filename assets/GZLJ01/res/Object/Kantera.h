#ifndef RES_KANTERA_H
#define RES_KANTERA_H

enum dRes_INDEX_KANTERA {
    /* BCK  */
    dRes_INDEX_KANTERA_BCK_MO_KANTERA_e=0x6,
    /* BMD  */
    dRes_INDEX_KANTERA_BMD_GA_e=0x9,
    /* BMDM */
    dRes_INDEX_KANTERA_BMD_LF_e=0xC,
    dRes_INDEX_KANTERA_BMD_MK_KANTERA_e=0xD,
    /* BRK  */
    dRes_INDEX_KANTERA_BRK_LF_e=0x10,
    dRes_INDEX_KANTERA_BRK_MK_KANTERA_e=0x11,
};

enum dRes_ID_KANTERA {
    /* BCK  */
    dRes_ID_KANTERA_BCK_MO_KANTERA_e=0x6,
    /* BMD  */
    dRes_ID_KANTERA_BMD_GA_e=0x9,
    /* BMDM */
    dRes_ID_KANTERA_BMD_LF_e=0xC,
    dRes_ID_KANTERA_BMD_MK_KANTERA_e=0xD,
    /* BRK  */
    dRes_ID_KANTERA_BRK_LF_e=0x10,
    dRes_ID_KANTERA_BRK_MK_KANTERA_e=0x11,
};

enum GA_JNT {
    GA_JNT_BODY_e=0x0,
};

enum LF_JNT {
    LF_JNT_HIKARI_e=0x0,
};

enum MK_KANTERA_JNT {
    MK_KANTERA_JNT_TOTTE_e=0x0,
    MK_KANTERA_JNT_KANTERA_e=0x1,
    MK_KANTERA_JNT_FIRE_e=0x2,
};

#endif /* !RES_KANTERA_H */