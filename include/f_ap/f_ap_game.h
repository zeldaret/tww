#ifndef F_AP_GAME_H
#define F_AP_GAME_H

#include "JSystem/JUtility/TColor.h"
#include "m_Do/m_Do_hostIO.h"

void fapGm_After();
void fapGm_Create();
void fapGm_Execute();

class fapGm_HIO_c : public JORReflexible {
public:
    fapGm_HIO_c();
    virtual ~fapGm_HIO_c();

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 mDisplayMeter;
    /* 0x07 */ u8 mDisplayFlag;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ u8 field_0x0a;
    /* 0x0B */ u8 field_0x0b;
    /* 0x0C */ f32 mAspectRatio;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ s8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ u8 field_0x1c;
    /* 0x1D */ u8 field_0x1d;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ JUtility::TColor field_0x20;
    /* 0x24 */ f32 mTriggerThreshLo;
    /* 0x28 */ f32 mTriggerThreshHi;
    /* 0x2C */ s16 mFbWidth;
    /* 0x2E */ s16 mEfbHeight;
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31;
    /* 0x32 */ u8 field_0x32;
    /* 0x33 */ u8 field_0x33;
    /* 0x34 */ u8 field_0x34;
    /* 0x35 */ u8 field_0x35;
    /* 0x36 */ u8 field_0x36;
    /* 0x37 */ u8 field_0x37;
    /* 0x38 */ u8 field_0x38;
    /* 0x39 */ u8 field_0x39;
    /* 0x3A */ u8 field_0x3a;
    /* 0x3B */ u8 field_0x3b;
    /* 0x3C */ JUtility::TColor field_0x3c;
    /* 0x40 */ JUtility::TColor field_0x40;
    /* 0x44 */ JUtility::TColor field_0x44;
    /* 0x48 */ JUtility::TColor field_0x48;
    /* 0x4C */ u16 field_0x4c;
    /* 0x4E */ u16 field_0x4e;
    /* 0x50 */ u16 field_0x50;
    /* 0x52 */ u16 field_0x52;
    /* 0x54 */ u16 field_0x54;
    /* 0x56 */ u8 field_0x56;
};  // Size: 0x58

extern fapGm_HIO_c g_HIO;

inline bool fapGmHIO_isPrint() { return !!(g_HIO.mDisplayFlag & 0x01); }
inline bool fapGmHIO_isMenu() { return !!(g_HIO.mDisplayFlag & 0x02); }
inline bool fapGmHIO_getMeter() { return g_HIO.mDisplayMeter; }
inline s16 fapGmHIO_getFbWidth() { return g_HIO.mFbWidth; }
inline s16 fapGmHIO_getEfbHeight() { return g_HIO.mEfbHeight; }
inline f32 fapGmHIO_getAspectRatio() { return g_HIO.mAspectRatio; }

#endif /* F_AP_GAME_H */
