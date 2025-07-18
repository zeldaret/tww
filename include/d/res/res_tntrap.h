#ifndef RES_TNTRAP_H
#define RES_TNTRAP_H

#include "global.h"

enum TNTRAP_RES_FILE_ID { // IDs and indexes are synced
    /* DZB */
    TNTRAP_DZB_TN_WALL01=0x3,
};
enum TNTRAP_ACTION_IDX{
    TRAP_OFF_WAIT,
    TRAP_ON_WAIT,
    DEMO_REGIST_WAIT,
    DEMO_WAIT,
    DEMO_WAIT2,
    DEMO_END,
    HIDE_WAIT
};

#endif /* RES_TNTRAP_H */
