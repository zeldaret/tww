#ifndef D_A_BG_H
#define D_A_BG_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

class daBg_c : public fopAc_ac_c {
public:
    void calcRoomMemory(char**, long*, char**, long*) {}
    void draw() {}
    void execute() {}
    void getRoomMemory(int) {}
    void initRoomMemory() {}
    void isDelete() {}

public:
    /* 0x290 */ void* m290;
    /* 0x294 */ void* m294;
    /* 0x298 */ daBg___Bg mBg[4];
    /* 0x2D8 */ dBgW* mpBgW;
    /* 0x2DC */ u8 mUnloadTimer;
    /* 0x2DD */ u8 m2DD[0x2E0 - 0x2DD];
};

#endif /* D_A_BG_H */
