#ifndef D_A_TAG_PHOTO_H
#define D_A_TAG_PHOTO_H

#include "f_op/f_op_actor.h"

class daTagPhoto_c : public fopAc_ac_c {
public:
    daTagPhoto_c();

    int getTagNo() { return mTagNo; }

    cPhs_State _create();
    void createHeap();
    void createInit();
    bool _delete();
    bool _draw();
    void setMode(unsigned char);
    bool _execute();
    void executeWait();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void talk(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setMessage(unsigned long);
    void getPrmTagNo();

public:
    /* Place member variables here */
    /* 0x290 */ u8 field_0x290[0x318 - 0x290];
    /* 0x318 */ u8 mTagNo;
    /* 0x31C */ u8 field_0x31C[0x320 - 0x31C];
};  // Size: 0x320

#endif /* D_A_TAG_PHOTO_H */
