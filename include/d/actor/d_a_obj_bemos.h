#ifndef D_A_OBJ_BEMOS_H
#define D_A_OBJ_BEMOS_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;
class daBeam_c;

class daBemos_c : public fopAc_ac_c {
    typedef BOOL (daBemos_c::*EyeProc)();

public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    bool checkEyeProc(EyeProc proc) {
        return m290 == proc;
    }
    void setEyeProc(EyeProc proc) {
        m290 = proc;
    }

    void set_mtx();
    BOOL CreateHeap1();
    BOOL CreateHeap2();
    BOOL CreateHeap3();
    BOOL CreateHeap();
    BOOL CreateInit1();
    BOOL CreateInit2();
    BOOL CreateInit3();
    cPhs_State CreateInit();
    BOOL blue_range_check(int, csXyz*);
    BOOL red_range_check(int, csXyz*);
    BOOL yellow_range_check(int, csXyz*);
    BOOL blue_eye_wait_init();
    BOOL blue_eye_wait();
    BOOL blue_eye_charge_init();
    BOOL blue_eye_charge();
    BOOL blue_eye_search_init();
    BOOL blue_eye_search();
    BOOL red_eye_wait_init();
    BOOL red_eye_wait();
    BOOL red_eye_charge_init();
    BOOL red_eye_charge();
    BOOL red_eye_search_init();
    BOOL red_eye_search();
    BOOL eye_break_init();
    BOOL eye_break();
    BOOL eye_dummy();
    BOOL yellow_eye_wait_init();
    BOOL yellow_eye_wait();
    BOOL yellow_eye_search_init();
    BOOL yellow_eye_search();
    void event_move();
    void guard_proc();
    daBeam_c* getBeamActor();

    static const char m_arcname[];

public:
    /* 0x290 */ EyeProc m290;
    /* 0x29C */ csXyz m29C;
    /* 0x2A2 */ u8 m2A2[0x2A4 - 0x2A2];
    /* 0x2A4 */ cXyz m2A4;
    /* 0x2B0 */ request_of_phase_process_class mPhase;
    /* 0x2B8 */ J3DModel* m2B8;
    /* 0x2BC */ J3DModel* m2BC;
    /* 0x2C0 */ J3DModel* m2C0;
    /* 0x2C4 */ u8 m2C4[0x2C8 - 0x2C4];
    /* 0x2C8 */ mDoExt_brkAnm mBrkAnm1;
    /* 0x2E0 */ J3DAnmTevRegKey* m_sch_brk;
    /* 0x2E4 */ mDoExt_brkAnm mBrkAnm2;
    /* 0x2FC */ JPABaseEmitter* m2FC;
    /* 0x300 */ JPABaseEmitter* m300;
    /* 0x304 */ JPABaseEmitter* m304;
    /* 0x308 */ JPABaseEmitter* m308;
    /* 0x30C */ JPABaseEmitter* m30C;
    /* 0x310 */ u8 m310;
    /* 0x311 */ u8 m311[0x314 - 0x311];
    /* 0x314 */ cXyz m314;
    /* 0x320 */ f32 m320;
    /* 0x324 */ u8 m324[0x354 - 0x324];
    /* 0x354 */ cXyz m354;
    /* 0x360 */ cXyz m360;
    /* 0x36C */ cXyz m36C;
    /* 0x378 */ dCcD_Stts mSttsCyl;
    /* 0x3B4 */ dCcD_Cyl mCyl;
    /* 0x4E4 */ dCcD_Stts mSttsSph;
    /* 0x520 */ dCcD_Sph mSph;
    /* 0x64C */ dBgS_ObjGndChk mGndChk;
    /* 0x6A0 */ f32 m6A0;
    /* 0x6A4 */ s32 m6A4;
    /* 0x6A8 */ s32 m6A8;
    /* 0x6AC */ s16 m6AC;
    /* 0x6AE */ s16 m6AE;
    /* 0x6B0 */ s16 m6B0;
    /* 0x6B2 */ s16 m6B2;
    /* 0x6B4 */ u8 m6B4[0x6B6 - 0x6B4];
    /* 0x6B6 */ s16 m6B6;
    /* 0x6B8 */ u8 m6B8;
    /* 0x6B9 */ u8 m6B9;
    /* 0x6BA */ u8 m6BA;
    /* 0x6BB */ u8 m6BB;
    /* 0x6BC */ u8 m6BC;
    /* 0x6BD */ u8 m6BD;
    /* 0x6BE */ u8 m6BE[0x6BF - 0x6BE];
    /* 0x6BF */ u8 m6BF;
    /* 0x6C0 */ u8 m6C0;
    /* 0x6C1 */ u8 m6C1[0x6C4 - 0x6C1];
}; // Size: 0x6C4

class daBemos_HIO_c : public JORReflexible {
public:
    daBemos_HIO_c();
    virtual ~daBemos_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05[0x08 - 0x05];
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ s16 m28;
    /* 0x2A */ s16 m2A;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ s16 m40;
    /* 0x42 */ s16 m42;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ u8 m4C;
    /* 0x4D */ u8 m4D[0x50 - 0x4D];
};  // Size: 0x50

#endif /* D_A_OBJ_BEMOS_H */
