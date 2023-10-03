#ifndef D_SNAP_H
#define D_SNAP_H

#include "f_op/f_op_actor.h"

class dSnap_Obj;

void dSnap_PhotoIndex2TableIndex(int);
void dSnap_GetFigRoomId(int);
void dSnap_MatDl();
void dSnap_AlphaClearDL();
void dSnap_Create();
void dSnap_ReleaseShutter();
void dSnap_Execute();
void dSnap_GetResult();
void dSnap_GetResultDetail();
void dSnap_RegistSnapObj(dSnap_Obj&);
void dSnap_RegistFig(unsigned char, fopAc_ac_c*, float, float, float);
void dSnap_RegistFig(unsigned char, fopAc_ac_c*, const Vec&, short, float, float, float);
void dSnap_DebugDraw();
void dSnap_Delete();

#endif /* D_SNAP_H */