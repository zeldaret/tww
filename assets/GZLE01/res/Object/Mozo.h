#ifndef RES_MOZO_H
#define RES_MOZO_H

enum dRes_INDEX_MOZO {
    /* BCKS */
    dRes_INDEX_MOZO_BCK_MOZ_e=0x6,
    /* BDLM */
    dRes_INDEX_MOZO_BDL_MOZ_e=0x9,
    /* BRK  */
    dRes_INDEX_MOZO_BRK_MOZ_e=0xC,
    /* BTK  */
    dRes_INDEX_MOZO_BTK_MOZ_e=0xF,
};

enum dRes_ID_MOZO {
    /* BCKS */
    dRes_ID_MOZO_BCK_MOZ_e=0x6,
    /* BDLM */
    dRes_ID_MOZO_BDL_MOZ_e=0x9,
    /* BRK  */
    dRes_ID_MOZO_BRK_MOZ_e=0xC,
    /* BTK  */
    dRes_ID_MOZO_BTK_MOZ_e=0xF,
};

enum MOZ_JNT {
    MOZ_JNT_MOZ_CENTER_e=0x0,
    MOZ_JNT_KUBI_J_e=0x1,
    MOZ_JNT_ATAMA_J_e=0x2,
    MOZ_JNT_AGOA_J_e=0x3,
    MOZ_JNT_AGOB_J_e=0x4,
    MOZ_JNT_AGOC_J_e=0x5,
    MOZ_JNT_EYE_J_e=0x6,
    MOZ_JNT_HANA_J_e=0x7,
    MOZ_JNT_UDEL_J_e=0x8,
    MOZ_JNT_UDER_J_e=0x9,
};

#endif /* !RES_MOZO_H */