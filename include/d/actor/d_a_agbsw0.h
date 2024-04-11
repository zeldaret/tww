#ifndef D_A_AGBSW0_H
#define D_A_AGBSW0_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"

class daAgb_c;

struct agb_mail_struct {
    /* 0x00 */ u16 msgNo;
    /* 0x02 */ u8 swToSet;
    /* 0x03 */ u8 stageSaveTbl;
    /* 0x04 */ u8 roomNo;
    /* 0x05 */ u8 reactType;
    /* 0x06 */ u8 swToCheck;
    /* 0x07 */ u8 sfx;
};

class daAgbsw0_c : public fopAc_ac_c {
public:
    /* 0x290 */ f32 mOrigScaleX;
    /* 0x294 */ f32 mOrigScaleZ;
    /* 0x298 */ u8 field_0x298;
    /* 0x299 */ u8 field_0x299;
    /* 0x29A */ bool mNonCircular;
    /* 0x29B */ u8 field_0x29B;
    /* 0x29C */ u32 mTimer;
    /* 0x2A0 */ dCcD_Stts mStts;
    /* 0x2DC */ dCcD_Cyl mCyl;

    BOOL ExeSubA();
    BOOL ExeSubAT();
    BOOL ExeSubA2();
    BOOL ExeSubF();
    BOOL ExeSubF2();
    BOOL ExeSubM();
    BOOL ExeSubM2();
    BOOL ExeSubM3();
#if VERSION == VERSION_JPN
    u32 TriforceCheck();
#else
    u32 TriforceCheck(daAgb_c*);
#endif
    BOOL ExeSubMW();
    BOOL ExeSubT();
    BOOL ExeSubS();
    BOOL ExeSubR();
    BOOL ExeSubB();
    BOOL ExeSubD();
    BOOL ExeSubFA();
    BOOL HitCheck(fopAc_ac_c*);
    BOOL HitCheck(cXyz, f32);
    BOOL MoveCheck(s16);
    void MailSend(u16, u8, u8, u8, u8);

    u8 getSw0() {
        return fopAcM_GetParam(this) >> 0x10 & 0xFF;
    }
    u8 getSw1() {
        return fopAcM_GetParam(this) >> 0x18 & 0xFF;
    }
    u8 getType() {
        return current.angle.z & 0xFF;
    }
    u16 getMsgNo() {
        return fopAcM_GetParam(this) & 0xFFFF;
    }
    s16 getParamNo() {
        return current.angle.x & 0xFFFF;
    }

    void deleteSub() {}
    
    static void incTclDispose();
    static void incTclBeat();
    
    inline BOOL draw();
    inline int create();
    inline BOOL execute();
    
    static agb_mail_struct mMail;
    static u32 mSE;
    static u8 mFigureDispose;
    static u8 mFigureBeat;
    static u16 BeatedMsg[];
    static u16 DisposedMsg[];
}; // Size 0x40C

#endif /* D_A_AGBSW0_H */
