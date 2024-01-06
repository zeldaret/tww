#ifndef D_SNAP_H
#define D_SNAP_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"

class dSnap_Obj {
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 */ s32 mActorPID;
    /* 0x18 */ u8 mPhoto;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ s16 field_0x1c;
    /* 0x1E */ s16 mAngleY;
    /* 0x20 */ s32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 mMinX;
    /* 0x2A */ s16 mMinY;
    /* 0x2C */ s16 mMaxX;
    /* 0x2E */ s16 mMaxY;
    /* 0x30 */ /* vtable */

public:
    dSnap_Obj();
    virtual ~dSnap_Obj() {}

    void DebugArea2D() {}
    void GetActor() const {}
    void GetArg() const {}
    void GetDRRatio() {}
    void GetLen(Vec&) const {}
    s16 GetMinX() { return mMinX; }
    s16 GetMinY() { return mMinY; }
    s16 GetMaxX() { return mMaxX; }
    s16 GetMaxY() { return mMaxY; }
    int GetPhoto() const { return mPhoto; }
    void GetPoint() {}
    void SetDRRatio(f32) {}
    void SetPoint(s32) {}
    void drawCamRange() {}

    f32 CalcArea2D();
    void draw();
    void SetGeo(const Vec& center, f32 radius, f32 height, s16 r5);
    void SetGeoSph(const Vec& center, f32 radius);
    void SetInf(u8, const fopAc_ac_c*, u8, u8, s16);
    void SetAreaClear();
    void SetArea(s16, s16);
    bool ChkPhoto(int);
    bool ChkSuccess(s32, f32);
    bool ChkCamCull() const;
};

STATIC_ASSERT(sizeof(dSnap_Obj) == 0x34);

class dSnap_RegistObjElm {
public:
    /* 0x00 */ dSnap_Obj m_obj;
    /* 0x34 */ f32 field_0x34;

public:
    dSnap_RegistObjElm() {}
    virtual ~dSnap_RegistObjElm() {}
    void Init();
    void Regist(const dSnap_Obj&);
};

class dSnap_packet : public J3DPacket {
public:
    virtual ~dSnap_packet() {}

    void DebugDraw() {}
    int GetResult() { return mResult; }
    u8 GetResultDetail() { return mResultDetail; }

    void Create();
    void ReleaseShutter();
    u32 ChkReleaseShutter();
    void Execute();
    int Regist(const dSnap_Obj&);
    virtual void draw();
    void ClearAlphaBuffer();
    void Judge();
    int FindPhoto(int, int);
    int JudgePost();
    int JudgeBikutsuki();
    int JudgeCoupleLook();
    int JudgeGF();
    int JudgeGenzo();
    int JudgeObasan4();
    int JudgeTestM();
    int JudgeGene();
    int JudgeFigure(int);
    void SetResult();

    /* 0x010 */ int field_0x10;
    /* 0x014 */ int field_0x14;
    /* 0x018 */ dSnap_RegistObjElm m_tbl[0x3F];
    /* 0xEDC */ int mFlag;
    /* 0xEE0 */ int mResult;
    /* 0xEE4 */ u8 mResultDetail;

    static int (dSnap_packet::*m_judge_tbl[])();
};

int dSnap_PhotoIndex2TableIndex(int);
u8 dSnap_GetFigRoomId(int);
void dSnap_MatDl();
void dSnap_AlphaClearDL();
void dSnap_Create();
void dSnap_ReleaseShutter();
void dSnap_Execute();
int dSnap_GetResult();
u8 dSnap_GetResultDetail();
void dSnap_RegistSnapObj(dSnap_Obj&);
void dSnap_RegistFig(u8, fopAc_ac_c*, f32, f32, f32);
void dSnap_RegistFig(u8, fopAc_ac_c*, const Vec&, s16, f32, f32, f32);
void dSnap_DebugDraw();
void dSnap_Delete();

inline void dSnap_AlphaClearDebug() {}
inline void dSnap_FigChkSizeNone(int) {}
inline void dSnap_MatDLDebug() {}
inline void dSnap_project(Vec*, Vec*) {}

#endif /* D_SNAP_H */
