#ifndef RES_VBAKH_H
#define RES_VBAKH_H

enum dRes_INDEX_VBAKH {
    /* BCK  */
    dRes_INDEX_VBAKH_BCK_VBAHX_e=0x5,
    dRes_INDEX_VBAKH_BCK_VBAKH_e=0x6,
    dRes_INDEX_VBAKH_BCK_VBAKM_e=0x7,
    dRes_INDEX_VBAKH_BCK_VBAMX_e=0x8,
    /* BDLM */
    dRes_INDEX_VBAKH_BDL_VBAKH_e=0xB,
    dRes_INDEX_VBAKH_BDL_VBAKM_e=0xC,
    /* BRK  */
    dRes_INDEX_VBAKH_BRK_VBAHX_e=0xF,
    dRes_INDEX_VBAKH_BRK_VBAKM_e=0x10,
    dRes_INDEX_VBAKH_BRK_VBAMX_e=0x11,
};

enum dRes_ID_VBAKH {
    /* BCK  */
    dRes_ID_VBAKH_BCK_VBAHX_e=0x5,
    dRes_ID_VBAKH_BCK_VBAKH_e=0x6,
    dRes_ID_VBAKH_BCK_VBAKM_e=0x7,
    dRes_ID_VBAKH_BCK_VBAMX_e=0x8,
    /* BDLM */
    dRes_ID_VBAKH_BDL_VBAKH_e=0xB,
    dRes_ID_VBAKH_BDL_VBAKM_e=0xC,
    /* BRK  */
    dRes_ID_VBAKH_BRK_VBAHX_e=0xF,
    dRes_ID_VBAKH_BRK_VBAKM_e=0x10,
    dRes_ID_VBAKH_BRK_VBAMX_e=0x11,
};

enum VBAKH_JNT {
    VBAKH_JNT_ROOT_VBAKH_e=0x0,
    VBAKH_JNT_VBAKH_e=0x1,
};

enum VBAKM_JNT {
    VBAKM_JNT_VBAKM_MODEL_e=0x0,
    VBAKM_JNT_VBAKM_FLOWER_e=0x1,
};

#endif /* !RES_VBAKH_H */