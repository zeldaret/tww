#ifndef D_A_TAG_PHOTO_H
#define D_A_TAG_PHOTO_H

#include "f_op/f_op_actor.h"

class daTagPhoto_c : public fopAc_ac_c {
public:
    void getTagNo() {}

    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    void setMode(unsigned char);
    BOOL _execute();
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
};

#endif /* D_A_TAG_PHOTO_H */
