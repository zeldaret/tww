#ifndef RES_GMJWP_H
#define RES_GMJWP_H

enum dRes_INDEX_GMJWP {
    /* BCK  */
    dRes_INDEX_GMJWP_BCK_GMJWP01_e=0x6,
    /* BDLM */
    dRes_INDEX_GMJWP_BDL_GMJWP00_e=0x9,
    /* BRK  */
    dRes_INDEX_GMJWP_BRK_GMJWP01_e=0xC,
    /* BTK  */
    dRes_INDEX_GMJWP_BTK_GMJWP00_e=0xF,
    dRes_INDEX_GMJWP_BTK_GMJWP02_e=0x10,
};

enum dRes_ID_GMJWP {
    /* BCK  */
    dRes_ID_GMJWP_BCK_GMJWP01_e=0x6,
    /* BDLM */
    dRes_ID_GMJWP_BDL_GMJWP00_e=0x9,
    /* BRK  */
    dRes_ID_GMJWP_BRK_GMJWP01_e=0xC,
    /* BTK  */
    dRes_ID_GMJWP_BTK_GMJWP00_e=0xF,
    dRes_ID_GMJWP_BTK_GMJWP02_e=0x10,
};

enum GMJWP00_JNT {
    GMJWP00_JNT_ROOT_e=0x0,
    GMJWP00_JNT_GMJWP00_e=0x1,
    GMJWP00_JNT_CYLINDER_e=0x2,
    GMJWP00_JNT_CYLINDER_1_e=0x3,
    GMJWP00_JNT_LINE_e=0x4,
    GMJWP00_JNT_LINE_1_e=0x5,
    GMJWP00_JNT_MAIN_e=0x6,
    GMJWP00_JNT_MAIN_1_e=0x7,
};

#endif /* !RES_GMJWP_H */