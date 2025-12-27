#ifndef RES_CB_H
#define RES_CB_H

#include "global.h" // IWYU pragma: keep

enum CB_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    CB_BCK_BOW=0x4,
    CB_BCK_BOW02=0x5,
    CB_BCK_CALL_01=0x6,
    CB_BCK_CALL_02=0x7,
    CB_BCK_CALL_03=0x8,
    CB_BCK_FLY=0x9,
    CB_BCK_FLY02=0xA,
    CB_BCK_GRABWAIT=0xB,
    CB_BCK_HIT=0xC,
    CB_BCK_HOLD=0xD,
    CB_BCK_M_OPEN=0xE,
    CB_BCK_NUT_SOW=0xF,
    CB_BCK_OPEN=0x10,
    CB_BCK_OPENWAIT=0x11,
    CB_BCK_PLAY01=0x12,
    CB_BCK_PLAY02=0x13,
    CB_BCK_SHIP_WAIT=0x14,
    CB_BCK_SOW=0x15,
    CB_BCK_WAIT01=0x16,
    CB_BCK_WAIT02=0x17,
    CB_BCK_WAIT03=0x18,
    CB_BCK_WAIT04=0x19,
    CB_BCK_WALK01=0x1A,
    
    /* BDL */
    CB_BDL_CB=0x1D,
    CB_BDL_CB_CELLO=0x1E,
    CB_BDL_CB_FACE=0x1F,
    CB_BDL_CB_NUT=0x20,
    CB_BDL_CB_STICK=0x21,
    CB_BDL_PP=0x22,
};

#endif /* RES_CB_H */
