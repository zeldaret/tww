#ifndef D_FLOWER_H
#define D_FLOWER_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"

class dCcMassS_HitInf;
class cCcD_Obj;
class fopAc_ac_c;

class dFlower_data_c {
public:
    dFlower_data_c();
    ~dFlower_data_c();

    void WorkCo(fopAc_ac_c*, u32, int);
    void WorkAt_NoCutAnim(fopAc_ac_c*, u32, int, dCcMassS_HitInf*, cCcD_Obj*);
    void WorkAt(fopAc_ac_c*, u32, int, dCcMassS_HitInf*);
    void hitCheck(fopAc_ac_c*, int);

    /* 0x00 */ u8 field_0x00[0x04 - 0x00];
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ u8 field_0x10[0x44 - 0x10];
};

class dFlower_anm_c {
public:
    dFlower_anm_c();

    /* 0x00 */ u8 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ u8 field_0x6[0x38 - 0x6];
};

class dFlower_room_c {
public:
    void newData(dFlower_data_c*);
    void deleteData();

    dFlower_room_c();

    /* 0x0 */ dFlower_data_c* field_0x0;
};

class dFlower_packet_c : public J3DPacket {
public:
    dFlower_packet_c();

    void calc();
    void update();
    void setData(dFlower_data_c*, int, s8, cXyz&, int, s8);
    void newData(s8, cXyz&, int, s8);
    void newAnm();
    void setAnm(int, s16);
    void deleteRoom(s32 roomNo) { mRoom[roomNo].deleteData(); }

    virtual void draw();
    virtual ~dFlower_packet_c();

    /* 0x0010 */ s16 field_0x0010;
    /* 0x0012 */ u8 field_0x0012[0x0014 - 0x0012];
    /* 0x0014 */ dFlower_data_c mData[200];
    /* 0x3534 */ dFlower_anm_c mAnm[72];
    /* 0x44F4 */ dFlower_room_c mRoom[64];
    /* 0x45F4 */ u8 field_0x45f4;
    /* 0x45F5 */ u8 field_0x45F5[0x45F8 - 0x45F5];
    /* 0x45F8 */ s16 field_0x45f8;
    /* 0x45FA */ u8 field_0x45FA[0x45FC - 0x45FA];
    /* 0x45FC */ cXyz field_0x45fc;
    /* 0x4608 */ f32* field_0x4608;
    /* 0x460C */ GXColor* field_0x460c;
    /* 0x4610 */ f32* field_0x4610;
    /* 0x4614 */ void* field_0x4614;
    /* 0x4618 */ void* field_0x4618;
    /* 0x461C */ void* field_0x461c;
    /* 0x4620 */ void* field_0x4620;
    /* 0x4624 */ void* field_0x4624;
    /* 0x4628 */ void* field_0x4628;
};

#endif /* D_FLOWER_H */