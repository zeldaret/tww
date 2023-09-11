#ifndef D_MAGMA_H
#define D_MAGMA_H

#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

class dMagma_ball_c;
class dMagma_floor_c {
public:
	void draw();
	void calc(int);
	void update();
	void create(cXyz&, cXyz&, s16, u8, int);
	void remove();

	~dMagma_floor_c();
	dMagma_floor_c();

	/* 0x00 */ dMagma_ball_c** mpBalls;
	/* 0x04 */ u8 mBallNum;
	/* 0x05 */ u8 mPathNo;
	/* 0x06 */ u8 field_0x06[0x08 - 0x06];
	/* 0x08 */ cXyz mBallPos;
	/* 0x14 */ f32 field_0x14;
	/* 0x18 */ f32 field_0x18;
	/* 0x1C */ Mtx mPosMtx;
	/* 0x4C */ Mtx mTexMtx0;
	/* 0x7C */ Mtx mBallPostMtx0;
	/* 0xAC */ dMagma_floor_c* mpNext;
};

class dMagma_room_c{
public:
	void newFloor(dMagma_floor_c*);
	void deleteFloor();

	dMagma_room_c();

	/* 0x0 */ dMagma_floor_c* mpFirst;
};

class dMagma_packet_c : public J3DPacket {
public:
	dMagma_packet_c();
	void calc();
	void update();
	void checkYpos(cXyz&);
	void newFloor(cXyz&, cXyz&, int, s16);

    virtual void draw();
    virtual ~dMagma_packet_c();
	
	/* 0x010 */ dMagma_floor_c mFloor[8];
	/* 0x590 */ dMagma_room_c mRoom[64];
	/* 0x690 */ GXColor mColor1;
	/* 0x694 */ f32 mTimer;
};

#endif /* D_MAGMA_H */