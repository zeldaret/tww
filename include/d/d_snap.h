#ifndef D_SNAP_H
#define D_SNAP_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"

enum {
    /* 0x00 */ DSNAP_TYPE_UNK00,
    /* 0x01 */ DSNAP_TYPE_UNK01,
    /* 0x02 */ DSNAP_TYPE_UNK02,
    /* 0x03 */ DSNAP_TYPE_UNK03,
    /* 0x04 */ DSNAP_TYPE_UNK04,
    /* 0x05 */ DSNAP_TYPE_UNK05,
    /* 0x06 */ DSNAP_TYPE_UNK06,
    /* 0x07 */ DSNAP_TYPE_UNK07,
    /* 0x08 */ DSNAP_TYPE_UNK08,
    /* 0x09 */ DSNAP_TYPE_UNK09,
    /* 0x0A */ DSNAP_TYPE_UNK0A,
    /* 0x0B */ DSNAP_TYPE_UNK0B,
    /* 0x0C */ DSNAP_TYPE_UNK0C,
    /* 0x0D */ DSNAP_TYPE_UNK0D,
    /* 0x0E */ DSNAP_TYPE_UNK0E,
    /* 0x0F */ DSNAP_TYPE_UNK0F,
    /* 0x10 */ DSNAP_TYPE_UNK10,
    /* 0x11 */ DSNAP_TYPE_UNK11,
    /* 0x12 */ DSNAP_TYPE_UNK12,
    /* 0x13 */ DSNAP_TYPE_UNK13,
    /* 0x14 */ DSNAP_TYPE_UNK14,
    /* 0x15 */ DSNAP_TYPE_UNK15,
    /* 0x16 */ DSNAP_TYPE_UNK16,
    /* 0x17 */ DSNAP_TYPE_UNK17,
    /* 0x18 */ DSNAP_TYPE_UNK18,
    /* 0x19 */ DSNAP_TYPE_UNK19,
    /* 0x1A */ DSNAP_TYPE_UNK1A,
    /* 0x1B */ DSNAP_TYPE_UNK1B,
    /* 0x1C */ DSNAP_TYPE_UNK1C,
    /* 0x1D */ DSNAP_TYPE_UNK1D,
    /* 0x1E */ DSNAP_TYPE_UNK1E,
    /* 0x1F */ DSNAP_TYPE_UNK1F,
    /* 0x20 */ DSNAP_TYPE_UNK20,
    /* 0x21 */ DSNAP_TYPE_UNK21,
    /* 0x22 */ DSNAP_TYPE_UNK22,
    /* 0x23 */ DSNAP_TYPE_UNK23,
    /* 0x24 */ DSNAP_TYPE_UNK24,
    /* 0x25 */ DSNAP_TYPE_UNK25,
    /* 0x26 */ DSNAP_TYPE_UNK26,
    /* 0x27 */ DSNAP_TYPE_UNK27,
    /* 0x28 */ DSNAP_TYPE_UNK28,
    /* 0x29 */ DSNAP_TYPE_UNK29,
    /* 0x2A */ DSNAP_TYPE_UNK2A,
    /* 0x2B */ DSNAP_TYPE_UNK2B,
    /* 0x2C */ DSNAP_TYPE_UNK2C,
    /* 0x2D */ DSNAP_TYPE_UNK2D,
    /* 0x2E */ DSNAP_TYPE_UNK2E,
    /* 0x2F */ DSNAP_TYPE_UNK2F,
    /* 0x30 */ DSNAP_TYPE_UNK30,
    /* 0x31 */ DSNAP_TYPE_UNK31,
    /* 0x32 */ DSNAP_TYPE_UNK32,
    /* 0x33 */ DSNAP_TYPE_UNK33,
    /* 0x34 */ DSNAP_TYPE_UNK34,
    /* 0x35 */ DSNAP_TYPE_UNK35,
    /* 0x36 */ DSNAP_TYPE_UNK36,
    /* 0x37 */ DSNAP_TYPE_UNK37,
    /* 0x38 */ DSNAP_TYPE_UNK38,
    /* 0x39 */ DSNAP_TYPE_UNK39,
    /* 0x3A */ DSNAP_TYPE_UNK3A,
    /* 0x3B */ DSNAP_TYPE_UNK3B,
    /* 0x3C */ DSNAP_TYPE_UNK3C,
    /* 0x3D */ DSNAP_TYPE_UNK3D,
    /* 0x3E */ DSNAP_TYPE_UNK3E,
    /* 0x3F */ DSNAP_TYPE_UNK3F,
    /* 0x40 */ DSNAP_TYPE_UNK40,
    /* 0x41 */ DSNAP_TYPE_UNK41,
    /* 0x42 */ DSNAP_TYPE_UNK42,
    /* 0x43 */ DSNAP_TYPE_UNK43,
    /* 0x44 */ DSNAP_TYPE_UNK44,
    /* 0x45 */ DSNAP_TYPE_UNK45,
    /* 0x46 */ DSNAP_TYPE_UNK46,
    /* 0x47 */ DSNAP_TYPE_UNK47,
    /* 0x48 */ DSNAP_TYPE_UNK48,
    /* 0x49 */ DSNAP_TYPE_UNK49,
    /* 0x4A */ DSNAP_TYPE_UNK4A,
    /* 0x4B */ DSNAP_TYPE_UNK4B,
    /* 0x4C */ DSNAP_TYPE_UNK4C,
    /* 0x4D */ DSNAP_TYPE_JI1,
    /* 0x4E */ DSNAP_TYPE_UNK4E,
    /* 0x4F */ DSNAP_TYPE_UNK4F,
    /* 0x50 */ DSNAP_TYPE_UNK50,
    /* 0x51 */ DSNAP_TYPE_UNK51,
    /* 0x52 */ DSNAP_TYPE_UNK52,
    /* 0x53 */ DSNAP_TYPE_UNK53,
    /* 0x54 */ DSNAP_TYPE_UNK54,
    /* 0x55 */ DSNAP_TYPE_KAMOME,
    /* 0x56 */ DSNAP_TYPE_UNK56,
    /* 0x57 */ DSNAP_TYPE_UNK57,
    /* 0x58 */ DSNAP_TYPE_UNK58,
    /* 0x59 */ DSNAP_TYPE_UNK59,
    /* 0x5A */ DSNAP_TYPE_UNK5A,
    /* 0x5B */ DSNAP_TYPE_UNK5B,
    /* 0x5C */ DSNAP_TYPE_UNK5C,
    /* 0x5D */ DSNAP_TYPE_UNK5D,
    /* 0x5E */ DSNAP_TYPE_UNK5E,
    /* 0x5F */ DSNAP_TYPE_UNK5F,
    /* 0x60 */ DSNAP_TYPE_UNK60,
    /* 0x61 */ DSNAP_TYPE_UNK61,
    /* 0x62 */ DSNAP_TYPE_UNK62,
    /* 0x63 */ DSNAP_TYPE_UNK63,
    /* 0x64 */ DSNAP_TYPE_UNK64,
    /* 0x65 */ DSNAP_TYPE_UNK65,
    /* 0x66 */ DSNAP_TYPE_UNK66,
    /* 0x67 */ DSNAP_TYPE_UNK67,
    /* 0x68 */ DSNAP_TYPE_UNK68,
    /* 0x69 */ DSNAP_TYPE_UNK69,
    /* 0x6A */ DSNAP_TYPE_UNK6A,
    /* 0x6B */ DSNAP_TYPE_UNK6B,
    /* 0x6C */ DSNAP_TYPE_UNK6C,
    /* 0x6D */ DSNAP_TYPE_UNK6D,
    /* 0x6E */ DSNAP_TYPE_UNK6E,
    /* 0x6F */ DSNAP_TYPE_UNK6F,
    /* 0x70 */ DSNAP_TYPE_UNK70,
    /* 0x71 */ DSNAP_TYPE_UNK71,
    /* 0x72 */ DSNAP_TYPE_UNK72,
    /* 0x73 */ DSNAP_TYPE_UNK73,
    /* 0x74 */ DSNAP_TYPE_UNK74,
    /* 0x75 */ DSNAP_TYPE_UNK75,
    /* 0x76 */ DSNAP_TYPE_UNK76,
    /* 0x77 */ DSNAP_TYPE_UNK77,
    /* 0x78 */ DSNAP_TYPE_UNK78,
    /* 0x79 */ DSNAP_TYPE_UNK79,
    /* 0x7A */ DSNAP_TYPE_UNK7A,
    /* 0x7B */ DSNAP_TYPE_UNK7B,
    /* 0x7C */ DSNAP_TYPE_UNK7C,
    /* 0x7D */ DSNAP_TYPE_UNK7D,
    /* 0x7E */ DSNAP_TYPE_UNK7E,
    /* 0x7F */ DSNAP_TYPE_UNK7F,
    /* 0x80 */ DSNAP_TYPE_BS,
    /* 0x81 */ DSNAP_TYPE_UNK81,
    /* 0x82 */ DSNAP_TYPE_UNK82,
    /* 0x83 */ DSNAP_TYPE_UNK83,
    /* 0x84 */ DSNAP_TYPE_UNK84,
    /* 0x85 */ DSNAP_TYPE_UNK85,
    /* 0x86 */ DSNAP_TYPE_UNK86,
    /* 0x87 */ DSNAP_TYPE_UNK87,
    /* 0x88 */ DSNAP_TYPE_UNK88,
    /* 0x89 */ DSNAP_TYPE_UNK89,
    /* 0x8A */ DSNAP_TYPE_MD,
    /* 0x8B */ DSNAP_TYPE_UNK8B,
    /* 0x8C */ DSNAP_TYPE_UNK8C,
    /* 0x8D */ DSNAP_TYPE_UNK8D,
    /* 0x8E */ DSNAP_TYPE_UNK8E,
    /* 0x8F */ DSNAP_TYPE_UNK8F,
    /* 0x90 */ DSNAP_TYPE_UNK90,
    /* 0x91 */ DSNAP_TYPE_UNK91,
    /* 0x92 */ DSNAP_TYPE_UNK92,
    /* 0x93 */ DSNAP_TYPE_UNK93,
    /* 0x94 */ DSNAP_TYPE_UNK94,
    /* 0x95 */ DSNAP_TYPE_UNK95,
    /* 0x96 */ DSNAP_TYPE_UNK96,
    /* 0x97 */ DSNAP_TYPE_UNK97,
    /* 0x98 */ DSNAP_TYPE_BTSW,
    /* 0x99 */ DSNAP_TYPE_DR,
    /* 0x9A */ DSNAP_TYPE_UNK9A,
    /* 0x9B */ DSNAP_TYPE_UNK9B,
    /* 0x9C */ DSNAP_TYPE_UNK9C,
    /* 0x9D */ DSNAP_TYPE_UNK9D,
    /* 0x9E */ DSNAP_TYPE_UNK9E,
    /* 0x9F */ DSNAP_TYPE_UNK9F,
    /* 0xA0 */ DSNAP_TYPE_UNKA0,
    /* 0xA1 */ DSNAP_TYPE_UNKA1,
    /* 0xA2 */ DSNAP_TYPE_UNKA2,
    /* 0xA3 */ DSNAP_TYPE_UNKA3,
    /* 0xA4 */ DSNAP_TYPE_UNKA4,
    /* 0xA5 */ DSNAP_TYPE_UNKA5,
    /* 0xA6 */ DSNAP_TYPE_UNKA6,
    /* 0xA7 */ DSNAP_TYPE_UNKA7,
    /* 0xA8 */ DSNAP_TYPE_UNKA8,
    /* 0xA9 */ DSNAP_TYPE_UNKA9,
    /* 0xAA */ DSNAP_TYPE_BK,
    /* 0xAB */ DSNAP_TYPE_UNKAB,
    /* 0xAC */ DSNAP_TYPE_UNKAC,
    /* 0xAD */ DSNAP_TYPE_UNKAD,
    /* 0xAE */ DSNAP_TYPE_UNKAE,
    /* 0xAF */ DSNAP_TYPE_UNKAF,
    /* 0xB0 */ DSNAP_TYPE_UNKB0,
    /* 0xB1 */ DSNAP_TYPE_UNKB1,
    /* 0xB2 */ DSNAP_TYPE_UNKB2,
    /* 0xB3 */ DSNAP_TYPE_UNKB3,
    /* 0xB4 */ DSNAP_TYPE_UNKB4,
    /* 0xB5 */ DSNAP_TYPE_UNKB5,
    /* 0xB6 */ DSNAP_TYPE_AM2,
    /* 0xB7 */ DSNAP_TYPE_AM,
    /* 0xB8 */ DSNAP_TYPE_UNKB8,
    /* 0xB9 */ DSNAP_TYPE_RD,
    /* 0xBA */ DSNAP_TYPE_UNKBA,
    /* 0xBB */ DSNAP_TYPE_UNKBB,
    /* 0xBC */ DSNAP_TYPE_UNKBC,
    /* 0xBD */ DSNAP_TYPE_UNKBD,
    /* 0xBE */ DSNAP_TYPE_UNKBE,
    /* 0xBF */ DSNAP_TYPE_UNKBF,
    /* 0xC0 */ DSNAP_TYPE_UNKC0,
    /* 0xC1 */ DSNAP_TYPE_UNKC1,
    /* 0xC2 */ DSNAP_TYPE_UNKC2,
    /* 0xC3 */ DSNAP_TYPE_UNKC3,
    /* 0xC4 */ DSNAP_TYPE_UNKC4,
    /* 0xC5 */ DSNAP_TYPE_UNKC5,
    /* 0xC6 */ DSNAP_TYPE_UNKC6,
    /* 0xC7 */ DSNAP_TYPE_UNKC7,
    /* 0xC8 */ DSNAP_TYPE_UNKC8,
    /* 0xC9 */ DSNAP_TYPE_UNKC9,
    /* 0xCA */ DSNAP_TYPE_UNKCA,
    /* 0xCB */ DSNAP_TYPE_UNKCB,
    /* 0xCC */ DSNAP_TYPE_UNKCC,
    /* 0xCD */ DSNAP_TYPE_UNKCD,
    /* 0xCE */ DSNAP_TYPE_UNKCE,
    /* 0xCF */ DSNAP_TYPE_UNKCF,
    /* 0xD0 */ DSNAP_TYPE_LAST_INDEX,
};

class dSnap_Obj {
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 */ uint mActorPID;
    /* 0x18 */ u8 mPhoto;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ s16 mCullAngle;
    /* 0x1E */ s16 mAngleY;
    /* 0x20 */ s32 mCapturedPixels;
    /* 0x24 */ f32 mCapturedRatio;
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
