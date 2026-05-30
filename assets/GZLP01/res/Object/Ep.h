#ifndef RES_EP_H
#define RES_EP_H

enum dRes_INDEX_EP {
    /* BDL  */
    dRes_INDEX_EP_BDL_EP_GA_e=0x3,
    dRes_INDEX_EP_BDL_OBM_SHOKUDAI1_e=0x4,
    dRes_INDEX_EP_BDL_VKTSD_e=0x5,
};

enum dRes_ID_EP {
    /* BDL  */
    dRes_ID_EP_BDL_EP_GA_e=0x3,
    dRes_ID_EP_BDL_OBM_SHOKUDAI1_e=0x4,
    dRes_ID_EP_BDL_VKTSD_e=0x5,
};

enum EP_GA_JNT {
    EP_GA_JNT_BODY_e=0x0,
};

enum OBM_SHOKUDAI1_JNT {
    OBM_SHOKUDAI1_JNT_OBM_SHOKUDAI1_e=0x0,
    OBM_SHOKUDAI1_JNT_POLYSURFACE3_e=0x1,
};

enum VKTSD_JNT {
    VKTSD_JNT_VKTSD_MODEL_e=0x0,
};

#endif /* !RES_EP_H */