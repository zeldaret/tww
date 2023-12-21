#ifndef D_TREE_H
#define D_TREE_H

#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

class cCcD_Obj;
class dCcMassS_HitInf;
class fopAc_ac_c;

class dTree_data_c {
public:
    ~dTree_data_c();
    dTree_data_c();

    void WorkCo(fopAc_ac_c*, u32, int);
    void WorkAt_NoCutAnim(fopAc_ac_c*, u32, int, dCcMassS_HitInf*, cCcD_Obj*);
    void WorkAt(fopAc_ac_c*, u32, int, dCcMassS_HitInf*);
    void hitCheck(fopAc_ac_c*, int);
    void animation(int);

    /* 0x000 */ u8 field_0x000;
    /* 0x001 */ u8 field_0x001;
    /* 0x002 */ u8 mAnimIdx;
    /* 0x003 */ s8 field_0x003;
    /* 0x004 */ cXyz mPos;
    /* 0x010 */ Mtx field_0x010;
    /* 0x040 */ Mtx field_0x040;
    /* 0x070 */ Mtx field_0x070;
    /* 0x0A0 */ Mtx mShadowMtx;
    /* 0x0D0 */ u8 field_0x0D0[0x100 - 0x0D0];
    /* 0x100 */ dTree_data_c* mpNext;
};

class dTree_anm_c {
public:
    ~dTree_anm_c();
    dTree_anm_c();

    /* 0x00 */ u8 field_0x00[0x02 - 0x00];
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ u8 field_0x06[0x08 - 0x06];
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0a;
    /* 0x0C */ f32 mAnimTimer;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ Mtx field_0x24;
    /* 0x54 */ u8 field_0x54[0x84 - 0x54];
};

class dTree_room_c {
public:
    dTree_room_c();

    void newData(dTree_data_c*);
    void deleteData();

    /* 0x0 */ dTree_data_c* mpHead;
};

class dTree_packet_c : public J3DPacket {
public:
    dTree_packet_c();

    void calc();
    void update();
    void setData(dTree_data_c*, int, cXyz&, u8, int);
    void newData(cXyz&, u8, int);
    void newAnm(s16);
    void setAnm(int, s16);
    void deleteRoom(s32 roomNo) { mRoom[roomNo].deleteData(); }

    virtual void draw();
    virtual ~dTree_packet_c();

    /* 0x0010 */ s16 field_0x0010;
    /* 0x0014 */ dTree_data_c mData[64];
    /* 0x4114 */ dTree_anm_c mAnm[72];
    /* 0x6634 */ dTree_room_c mRoom[64];
    /* 0x6734 */ u8 field_0x6734;
    /* 0x6736 */ s16 field_0x6736;
    /* 0x6738 */ s16 field_0x6738;
    /* 0x673C */ cXyz field_0x673c;
};

#endif /* D_TREE_H */
