#ifndef D_TREE_H
#define D_TREE_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_particle.h"
#include "dolphin/mtx/mtx.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

class cCcD_Obj;
class dCcMassS_HitInf;
class fopAc_ac_c;

extern u8 g_dTree_shadowPos[4][3];
extern u8 g_dTree_shadowTexCoord[4][2];
extern u8 g_dTree_shadowMatDL[];
extern u8 g_dTree_Oba_kage_32DL[];
extern const u32 g_dTree_shadowMatDL_SIZE;
extern const u32 g_dTree_Oba_kage_32DL_SIZE;

class dTree_data_c {
public:
    ~dTree_data_c();
    dTree_data_c();

    void WorkCo(fopAc_ac_c*, u32, int);
    void WorkAt_NoCutAnim(fopAc_ac_c*, u32, int, dCcMassS_HitInf*, cCcD_Obj*);
    void WorkAt(fopAc_ac_c*, u32, int, dCcMassS_HitInf*);
    BOOL hitCheck(fopAc_ac_c*, int);
    void animation(int);

    /* 0x000 */ u8 mState;
    /* 0x001 */ u8 field_0x001;
    /* 0x002 */ s8 mAnimIdx;
    /* 0x003 */ u8 field_0x003;
    /* 0x004 */ cXyz mPos;
    /* 0x010 */ Mtx field_0x010;
    /* 0x040 */ Mtx field_0x040;
    /* 0x070 */ Mtx field_0x070;
    /* 0x0A0 */ Mtx mShadowMtx;
    /* 0x0D0 */ Mtx field_0x0d0;
    /* 0x100 */ dTree_data_c* mpNext;

    static dPa_smokeEcallBack mSmokeEcallback;
};

class dTree_anm_c {
public:
    ~dTree_anm_c();
    dTree_anm_c();

    /* 0x00 */ u8 mState;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0a;
    /* 0x0C */ f32 mAnimTimer;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ Mtx field_0x24;
    /* 0x54 */ Mtx field_0x54;
};

class dTree_room_c {
public:
    dTree_room_c();

    void newData(dTree_data_c*);
    void deleteData();

    dTree_data_c* getData() { return mpData; }

private:
    /* 0x0 */ dTree_data_c* mpData;
};

class dTree_packet_c : public J3DPacket {
public:
    dTree_packet_c();

    void calc();
    void update();
    void setData(dTree_data_c*, int, cXyz&, u8, int);
    dTree_data_c* newData(cXyz&, u8, int);
    s32 newAnm(s16);
    void setAnm(int, s16);
    void deleteRoom(int roomNo) { mRoom[roomNo].deleteData(); }
    void deleteAnm(int idx) { mAnm[idx].mState = 0; }

    dTree_anm_c* getAnm() { return mAnm; }
    dTree_anm_c* getAnm(int idx) { return &mAnm[idx]; }
    dTree_data_c* getData() { return mData; }

    void setPlayerCutFlg(int i_flg) { mPlayerCutFlg = i_flg; }
    void setPlayerSwordTop(cXyz& i_pos) { mPlayerSwordTop = i_pos; }
    void setPlayerSwordMoveAngY(s16 i_ang) { mPlayerSwordMoveAngY = i_ang; }
    cXyz& getPlayerSwordTop() { return mPlayerSwordTop; }
    void setPlayerSwordAngY(s16 i_ang) { mPlayerSwordAngY = i_ang;}
    s16 getPlayerSwordMoveAngY() { return mPlayerSwordMoveAngY; }

    // TODO
    void getNum() {}

    virtual void draw();
    virtual ~dTree_packet_c();

private:
    /* 0x0010 */ u16 mNextIdx;
    /* 0x0014 */ dTree_data_c mData[64];
    /* 0x4114 */ dTree_anm_c mAnm[72];
    /* 0x6634 */ dTree_room_c mRoom[64];
    /* 0x6734 */ bool mPlayerCutFlg;
    /* 0x6736 */ s16 mPlayerSwordAngY;
    /* 0x6738 */ s16 mPlayerSwordMoveAngY;
    /* 0x673C */ cXyz mPlayerSwordTop;
};

#endif /* D_TREE_H */
