#ifndef RES_DEMO44_H
#define RES_DEMO44_H

enum DEMO44_RES_FILE_ID {
    /* BCKS */
    DEMO44_BCK_FN_SET=0x0,
    DEMO44_BCK_18_FN_CUT17_TALK_L=0x3,
    DEMO44_BCK_BLACKBOX_STOP=0xA,
    DEMO44_BCK_20_CL_IKITOMEA_O=0x10,
    DEMO44_BCK_20_CL_IKITOMEB_O=0x11,
    
    /* BDL */
    DEMO44_BDL_FN_COMP=0x1,
    
    /* BDLM */
    DEMO44_BDL_GDEMO20_2=0x4,
    DEMO44_BDL_BLACK_PLANE=0x7,
    DEMO44_BDL_BLACKFADEBOX=0x9,
    DEMO44_BDL_B_AWA_LB=0xF,
    
    /* BRK */
    DEMO44_BRK_GDEMO20_2=0x5,
    DEMO44_BRK_WHITE_OUT120F=0xB,
    DEMO44_BRK_WHITE_IN120F=0xC,
    DEMO44_BRK_WHITE_IN30F=0xD,
    DEMO44_BRK_WHITE1F=0xE,
    
    /* STB */
    DEMO44_STB_WARP_OUT=0x6,
};

enum DEMO44_RES_FILE_INDEX {
    /* BCKS */
    DEMO44_INDEX_BCK_FN_SET=0x7,
    DEMO44_INDEX_BCK_18_FN_CUT17_TALK_L=0x8,
    DEMO44_INDEX_BCK_BLACKBOX_STOP=0x9,
    DEMO44_INDEX_BCK_20_CL_IKITOMEA_O=0xA,
    DEMO44_INDEX_BCK_20_CL_IKITOMEB_O=0xB,
    
    /* BDL */
    DEMO44_INDEX_BDL_FN_COMP=0xE,
    
    /* BDLM */
    DEMO44_INDEX_BDL_GDEMO20_2=0x11,
    DEMO44_INDEX_BDL_BLACK_PLANE=0x12,
    DEMO44_INDEX_BDL_BLACKFADEBOX=0x13,
    DEMO44_INDEX_BDL_B_AWA_LB=0x14,
    
    /* BRK */
    DEMO44_INDEX_BRK_GDEMO20_2=0x17,
    DEMO44_INDEX_BRK_WHITE_OUT120F=0x18,
    DEMO44_INDEX_BRK_WHITE_IN120F=0x19,
    DEMO44_INDEX_BRK_WHITE_IN30F=0x1A,
    DEMO44_INDEX_BRK_WHITE1F=0x1B,
    
    /* STB */
    DEMO44_INDEX_STB_WARP_OUT=0x1E,
};

#endif /* RES_DEMO44_H */