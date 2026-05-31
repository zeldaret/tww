#ifndef RES_HHBOT_H
#define RES_HHBOT_H

enum dRes_INDEX_HHBOT {
    /* BDL  */
    dRes_INDEX_HHBOT_BDL_HHBOT1_e=0x4,
    dRes_INDEX_HHBOT_BDL_HHBOT2_e=0x5,
    /* DZB  */
    dRes_INDEX_HHBOT_DZB_HHBOT1_e=0x8,
    dRes_INDEX_HHBOT_DZB_HHBOT2_e=0x9,
};

enum dRes_ID_HHBOT {
    /* BDL  */
    dRes_ID_HHBOT_BDL_HHBOT1_e=0x4,
    dRes_ID_HHBOT_BDL_HHBOT2_e=0x5,
    /* DZB  */
    dRes_ID_HHBOT_DZB_HHBOT1_e=0x8,
    dRes_ID_HHBOT_DZB_HHBOT2_e=0x9,
};

enum HHBOT1_JNT {
    HHBOT1_JNT_POLYSURFACE2_e=0x0,
};

enum HHBOT2_JNT {
    HHBOT2_JNT_WORLD_ROOT_e=0x0,
    HHBOT2_JNT_BOTAN_e=0x1,
    HHBOT2_JNT_JOINT2_e=0x2,
};

#endif /* !RES_HHBOT_H */