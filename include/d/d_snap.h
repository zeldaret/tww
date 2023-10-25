#ifndef D_SNAP_H
#define D_SNAP_H

#include "f_op/f_op_actor.h"

class dSnap_Obj {
public:
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s32 mBsPcId;
    /* 0x18 */ u32 field_0x18[6];

public:
    dSnap_Obj();
    virtual ~dSnap_Obj() {}

    void SetGeoSph(const Vec & c, f32 r);
    void SetInf(u8, const fopAc_ac_c*, u8, u8, s16);
};

STATIC_ASSERT(sizeof(dSnap_Obj) == 0x34);

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