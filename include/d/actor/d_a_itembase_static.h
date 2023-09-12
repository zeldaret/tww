#ifndef D_A_ITEMBASE_STATIC_H
#define D_A_ITEMBASE_STATIC_H

#include "f_op/f_op_actor.h"

void getItemNo();
void getHeight();
void getR();
void hide();
void show();
void changeDraw();
void chkDraw();
void dead();
void chkDead();
void setLoadError();
void CheckItemCreateHeap(fopAc_ac_c*);
s32 CheckFieldItemCreateHeap(fopAc_ac_c*);

#endif /* D_A_ITEMBASE_STATIC_H */