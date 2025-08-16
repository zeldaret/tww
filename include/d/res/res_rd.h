#ifndef RES_RD_H
#define RES_RD_H

#include "global.h" // IWYU pragma: keep

enum RD_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    RD_BCK_ATACK=0x6,
    RD_BCK_ATACK2WALK=0x7,
    RD_BCK_BEAM=0x8,
    RD_BCK_BEAM_END=0x9,
    RD_BCK_BEAM_HIT=0xA,
    RD_BCK_DAMAGE=0xB,
    RD_BCK_DEAD=0xC,
    RD_BCK_IKARI_SAMPLE=0xD,
    RD_BCK_KANOKEP=0xE,
    RD_BCK_SUWARIP=0xF,
    RD_BCK_SUWARU=0x10,
    RD_BCK_TACHIP=0x11,
    RD_BCK_TATSU=0x12,
    RD_BCK_WALK=0x13,
    RD_BCK_WALK2ATACK=0x14,
    
    /* BDLM */
    RD_BDL_RD=0x17,
    
    /* BRK */
    RD_BRK_BEAM=0x1A,
    RD_BRK_BEAM_END=0x1B,
    RD_BRK_BEAM_HIT=0x1C,
    RD_BRK_NML=0x1D,
    
    /* BTK */
    RD_BTK_RD_CLOSE=0x20,
    RD_BTK_RD_IKARI=0x21,
    RD_BTK_RD_NML=0x22,
    RD_BTK_RD_OPEN=0x23,
};

#endif /* RES_RD_H */
