#ifndef RES_VMC_H
#define RES_VMC_H

enum dRes_INDEX_VMC {
    /* BCK  */
    dRes_INDEX_VMC_BCK_VMCWG_e=0x6,
    dRes_INDEX_VMC_BCK_VMCWH_e=0x7,
    /* BDL  */
    dRes_INDEX_VMC_BDL_VMCBS_e=0xA,
    /* BDLM */
    dRes_INDEX_VMC_BDL_VMCWD_e=0xD,
    /* DZB  */
    dRes_INDEX_VMC_DZB_VMCBS_e=0x10,
    dRes_INDEX_VMC_DZB_VMCWD_e=0x11,
};

enum dRes_ID_VMC {
    /* BCK  */
    dRes_ID_VMC_BCK_VMCWG_e=0x6,
    dRes_ID_VMC_BCK_VMCWH_e=0x7,
    /* BDL  */
    dRes_ID_VMC_BDL_VMCBS_e=0xA,
    /* BDLM */
    dRes_ID_VMC_BDL_VMCWD_e=0xD,
    /* DZB  */
    dRes_ID_VMC_DZB_VMCBS_e=0x10,
    dRes_ID_VMC_DZB_VMCWD_e=0x11,
};

enum VMCBS_JNT {
    VMCBS_JNT_MC_BASE_MODEL_e=0x0,
};

enum VMCWD_JNT {
    VMCWD_JNT_CENTER_e=0x0,
    VMCWD_JNT_BACKBONE_e=0x1,
    VMCWD_JNT_NECK_e=0x2,
    VMCWD_JNT_LEAFL_e=0x3,
    VMCWD_JNT_LEAFR_e=0x4,
    VMCWD_JNT_BRANCH_e=0x5,
};

#endif /* !RES_VMC_H */