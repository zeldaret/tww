#ifndef RES_FA_H
#define RES_FA_H

enum dRes_INDEX_FA {
    /* BCK  */
    dRes_INDEX_FA_BCK_FA_e=0x4,
    /* BDL  */
    dRes_INDEX_FA_BDL_FA_e=0x7,
};

enum dRes_ID_FA {
    /* BCK  */
    dRes_ID_FA_BCK_FA_e=0x4,
    /* BDL  */
    dRes_ID_FA_BDL_FA_e=0x7,
};

enum FA_JNT {
    FA_JNT_CENTER_e=0x0,
    FA_JNT_NECK_e=0x1,
    FA_JNT_WINGL1_e=0x2,
    FA_JNT_WINGR_e=0x3,
};

#endif /* !RES_FA_H */