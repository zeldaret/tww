#ifndef D_SNAP_H
#define D_SNAP_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"

class dSnap_Obj {
public:
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s32 mBsPcId;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ s16 field_0x1c;
    /* 0x1E */ s16 field_0x1e;
    /* 0x20 */ s32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2a;
    /* 0x2C */ s16 field_0x2c;
    /* 0x2E */ s16 field_0x2e;

public:
    dSnap_Obj();
    virtual ~dSnap_Obj() {}

    void CalcArea2D();
    void draw();
    void SetGeo(const Vec&, f32, f32, s16);
    void SetGeoSph(const Vec & c, f32 r);
    void SetInf(u8, const fopAc_ac_c*, u8, u8, s16);
    void SetAreaClear();
    void SetArea(s16, s16);
    void ChkPhoto(int);
    void ChkSuccess(s32, f32);
    void ChkCamCull() const;
};

class dSnap_RegistObjElm {
public:
    /* 0x00 */ dSnap_Obj field_0x0;
    /* 0x34 */ u8 field_0x34[4];

    dSnap_RegistObjElm();
    virtual ~dSnap_RegistObjElm();
    void Init();
    void Regist(const dSnap_Obj&);
};

class dSnap_packet : public J3DPacket {
public:
    virtual ~dSnap_packet();
    void Create();
    void ReleaseShutter();
    void ChkReleaseShutter();
    void Execute();
    void Regist(const dSnap_Obj&);
    virtual void draw();
    void ClearAlphaBuffer();
    void Judge();
    void FindPhoto(int, int);
    void JudgePost();
    void JudgeBikutsuki();
    void JudgeCoupleLook();
    void JudgeGF();
    void JudgeGenzo();
    void JudgeObasan4();
    void JudgeTestM();
    void JudgeGene();
    void JudgeFigure(int);
    void SetResult();

    /* 0x010 */ u8 field_0x10[0x18 - 0x10];
    /* 0x018 */ dSnap_RegistObjElm field_0x18[0x3f];
    /* 0xEDC */ int field_0xedc;
    /* 0xEE0 */ int field_0xee0;
    /* 0xEE4 */ u8 field_0xee4;

    static void (dSnap_packet::*m_judge_tbl[])();
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
