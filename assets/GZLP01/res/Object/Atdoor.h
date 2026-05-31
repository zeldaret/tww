#ifndef RES_ATDOOR_H
#define RES_ATDOOR_H

enum dRes_INDEX_ATDOOR {
    /* BDL  */
    dRes_INDEX_ATDOOR_BDL_SDOOR01_e=0x4,
    /* DZB  */
    dRes_INDEX_ATDOOR_DZB_SDOOR01_e=0x7,
};

enum dRes_ID_ATDOOR {
    /* BDL  */
    dRes_ID_ATDOOR_BDL_SDOOR01_e=0x4,
    /* DZB  */
    dRes_ID_ATDOOR_DZB_SDOOR01_e=0x7,
};

enum SDOOR01_JNT {
    SDOOR01_JNT_DOOR_e=0x0,
    SDOOR01_JNT_DOOR01_e=0x1,
    SDOOR01_JNT_POLYSURFACE409_e=0x2,
};

#endif /* !RES_ATDOOR_H */