#ifndef RES_PGSW_H
#define RES_PGSW_H

enum dRes_INDEX_PGSW {
    /* BDLM */
    dRes_INDEX_PGSW_BDL_BPG_KEN1_e=0x4,
    /* BRK  */
    dRes_INDEX_PGSW_BRK_KIERU_KEN1_e=0x7,
};

enum dRes_ID_PGSW {
    /* BDLM */
    dRes_ID_PGSW_BDL_BPG_KEN1_e=0x4,
    /* BRK  */
    dRes_ID_PGSW_BRK_KIERU_KEN1_e=0x7,
};

enum BPG_KEN1_JNT {
    BPG_KEN1_JNT_WORLD_ROOT_e=0x0,
    BPG_KEN1_JNT_BPG_KEN1_e=0x1,
    BPG_KEN1_JNT_BPG_KEN2_e=0x2,
};

#endif /* !RES_PGSW_H */