#ifndef RES_MT_H
#define RES_MT_H

#include "global.h" // IWYU pragma: keep

enum MT_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    MT_BCK_ATTACK=0x7,
    MT_BCK_SUKI=0x8,
    MT_BCK_TUKKOMI=0x9,
    MT_BCK_WAIT1=0xA,
    
    /* BDLM */
    MT_BDL_KBA=0xD,
    MT_BDL_KBB=0xE,
    MT_BDL_KBC=0xF,
    MT_BDL_KBD=0x10,
    MT_BDL_KBE=0x11,
    MT_BDL_MAGT_F=0x12,
    MT_BDL_MG_BODY=0x13,
    MT_BDL_MG_HEAD=0x14,
    MT_BDL_MG_TAIL=0x15,
    
    /* BRK */
    MT_BRK_FUKKATU_B=0x18,
    MT_BTK_FUKKATU_B=0x19,
    MT_BRK_FUKKATU_H=0x1A,
    MT_BTK_FUKKATU_H=0x1B,
    MT_BRK_FUKKATU_T=0x1C,
    MT_BTK_FUKKATU_T=0x1D,
    MT_BRK_MAGT_F=0x1E,
    MT_BRK_MG_BODY=0x1F,
    MT_BRK_MG_BODY1=0x20,
    MT_BRK_MG_HEAD=0x21,
    MT_BRK_MG_HEAD1=0x22,
    MT_BRK_MG_TAIL=0x23,
    MT_BRK_MG_TAIL1=0x24,
    MT_BRK_SYOUKA_B=0x25,
    MT_BRK_SYOUKA_H=0x26,
    MT_BRK_SYOUKA_T=0x27,
    
    /* BTK */
    MT_BTK_MAGT_F=0x2A,
    MT_BTK_MG_BODY=0x2B,
    MT_BTK_MG_BODY1=0x2C,
    MT_BTK_MG_HEAD=0x2D,
    MT_BTK_MG_HEAD1=0x2E,
    MT_BTK_MG_TAIL=0x2F,
    MT_BTK_MG_TAIL1=0x30,
    MT_BTK_SYOUKA_B=0x31,
    MT_BTK_SYOUKA_H=0x32,
    MT_BTK_SYOUKA_T=0x33,
    
    /* BTP */
    MT_BTP_MG_MABA=0x36,
    MT_BTP_MG_TOJI=0x37,
};

#endif /* RES_MT_H */
