#ifndef RES_HR_H
#define RES_HR_H

#include "global.h" // IWYU pragma: keep

enum HR_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    HR_BCK_DAMAGE=0x6,
    HR_BCK_H_ANT=0x7,
    HR_BCK_H_WAIT01=0x8,
    HR_BCK_LOOK=0x9,
    HR_BCK_R_ANT=0xA,
    HR_BCK_R_WAIT01=0xB,
    HR_BCK_R_WAIT02=0xC,
    HR_BCK_TALK01=0xD,
    HR_BCK_TALK02=0xE,
    HR_BCK_TALK03=0xF,
    
    /* BDLM */
    HR_BDL_H_ANT=0x12,
    HR_BDL_H_BROW=0x13,
    HR_BDL_HR=0x14,
    HR_BDL_R_ANT=0x15,
    HR_BDL_R_BROW=0x16,
    
    /* BMT */
    HR_BMT_R_BODY=0x19,
    
    /* BTP */
    HR_BTP_MABA_H=0x1C,
    HR_BTP_MABA_R01=0x1D,
    HR_BTP_MABA_R02=0x1E,
};

#endif /* RES_HR_H */
