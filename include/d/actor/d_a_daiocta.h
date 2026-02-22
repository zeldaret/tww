#ifndef D_A_DAIOCTA_H
#define D_A_DAIOCTA_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class dCcD_SrcSph;
class dCcD_SrcCps;

class daDaiocta_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1
    };

    enum Mode_e {
        MODE_HIDE        = 0,
        MODE_APPEAR      = 1,
        MODE_WAIT        = 2,
        MODE_DAMAGE      = 3,
        MODE_DAMAGE_BOMB = 4,
        MODE_DELETE      = 5,
        MODE_DEMO        = 6,
        MODE_NULL
    };

    struct ModeEntry {
        typedef void (daDaiocta_c::*ModeProcFunc)(void);
        ModeProcFunc mInitFunc;
        ModeProcFunc mUpdFunc;
        char* mModeName;
    };

    u8 getSw() { return mSwitchNo; }

    void _coHit(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    BOOL createAwaHeap();
    BOOL createSuikomiHeap();
    BOOL createBodyHeap();
    BOOL createArrowHitHeap();
    void setMtx();
    void setSuikomiMtx();
    void setAwaMtx();
    void initMtx();
    void setEffect(unsigned short);
    void setAwaRandom(int);
    void initAwa();
    void execAwa();
    bool isLivingEye();
    bool isDead();
    bool isDamageEye();
    bool isDamageBombEye();
    void setRotEye();
    void setCollision();
    void modeHideInit();
    void modeHide();
    void modeAppearInit();
    void modeAppear();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDamageBombInit();
    void modeDamageBomb();
    void modeDemoInit();
    void modeDemo();
    void modeDeleteInit();
    void modeDelete();
    void modeProc(Proc_e, Mode_e);
    void setAnm();
    void setWater();
    bool _execute();
    void drawAwa();
    void drawSuikomi();
    void drawDebug();
    bool _draw();
    void getArg();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const s32 m_heapsize;
    static const char m_arc_name[];
    static const dCcD_SrcSph m_sph_src;
    static const dCcD_SrcCps m_cps_src;

public:
    // Offsets shown are for retail
    /* 0x0290 */ cXyz m0290[37];
    /* 0x044C */ u8 m044C[0x04E0 - 0x044C];
    /* 0x04E0 */ u32 m04E0[12];
    /* 0x0510 */ u8 m0510[0x056C - 0x0510];
    /* 0x056C */ s32 m056C;
    /* 0x0570 */ s8 m0570;
    /* 0x0571 */ s8 m0571;
    /* 0x0572 */ s8 m0572;
    /* 0x0573 */ u8 m0573;
    /* 0x0574 */ u8 mSwitchNo;
    /* 0x0575 */ u8 m575;
    /* 0x0576 */ u8 m0576[0x0578 - 0x0576];
    /* 0x0578 */ f32 m0578;
    /* 0x057C */ u8 m057C;
    /* 0x057D */ u8 m057D[0x0580 - 0x057D];
    /* 0x0580 */ request_of_phase_process_class mPh;
    /* 0x0588 */ mDoExt_McaMorf* mpMorf;
    /* 0x058C */ mDoExt_brkAnm mBrkAnm1;
    /* 0x05A4 */ dCcD_Sph mSph[6];
    /* 0x0CAC */ dCcD_Cps mCps[17];
    /* 0x2164 */ dCcD_Stts mStts;
    /* 0x21A0 */ cXyz m21A0;
    /* 0x21AC */ cXyz m21AC;
    /* 0x21B8 */ cXyz m21B8;
    /* 0x21C4 */ cXyz m21C4;
    /* 0x21D0 */ cXyz m21D0;
    /* 0x21DC */ cXyz m21DC;
    /* 0x21E8 */ cXyz m21E8;
    /* 0x21F4 */ cXyz m21F4;
    /* 0x2200 */ csXyz m2200;
    /* 0x2206 */ u8 m2206[0x2208 - 0x2206];
    /* 0x2208 */ f32 m2208;
    /* 0x220C */ cXyz m220C;
    /* 0x2218 */ dBgS_ObjAcch mAcch;
    /* 0x23DC */ dBgS_AcchCir mAcchCir;
#if VERSION > VERSION_DEMO
    /* 0x241C */ dPa_followEcallBack mParticleCB;
#else
                 JPABaseEmitter* mpEmitter;
#endif
    /* 0x2430 */ f32 m2430;
    /* 0x2434 */ cXyz m2434;
    /* 0x2440 */ fpc_ProcID m2440[12];
    /* 0x2470 */ u8 m2470[12];
    /* 0x247C */ u8 m247C[0x26BC - 0x247C];
    /* 0x26BC */ int m26BC;
    /* 0x26C0 */ u8 m26C0;
    /* 0x26C1 */ u8 m26C1;
    /* 0x26C2 */ u8 m26C2[0x26C4 - 0x26C2];
    /* 0x26C4 */ fpc_ProcID m26C4;
    /* 0x26C8 */ JntHit_c* m26C8;
    /* 0x26CC */ J3DModel* m26CC;
    /* 0x26D0 */ mDoExt_brkAnm mBrkAnm2;
    /* 0x26E8 */ mDoExt_btkAnm mBtkAnm;
    /* 0x26FC */ J3DModel* mpModels[30];
    /* 0x2774 */ mDoExt_bckAnm mBckAnms[30];
    /* 0x2954 */ mDoExt_btkAnm mBtkAnms[30];
    /* 0x2BAC */ mDoExt_brkAnm mBrkAnms[30];
    /* 0x2E7C */ int m2E7C[30];
    /* 0x2EF4 */ cXyz m2EF4[30];
    /* 0x305C */ cXyz m305C[30];
    /* 0x31C4 */ u8 m31C4;
    /* 0x31C5 */ u8 m31C5[0x31C8 - 0x31C5];
};  // Size: 0x31C8
STATIC_ASSERT(sizeof(daDaiocta_c) == DEMO_SELECT(0x31B8, 0x31C8));

class daDaiocta_HIO_c : public mDoHIO_entry_c {
public:
    daDaiocta_HIO_c();

public:
    /* 0x004 */ u8 m004;
    /* 0x005 */ u8 m005;
    /* 0x006 */ u8 m006;
    /* 0x007 */ u8 m007;
    /* 0x008 */ u8 m008;
    /* 0x009 */ u8 m009[0x00A - 0x009];
    /* 0x00A */ s16 m00A;
    /* 0x00C */ s16 m00C;
    /* 0x00E */ s16 m00E;
    /* 0x010 */ s16 m010;
    /* 0x012 */ s16 m012;
    /* 0x014 */ s16 m014;
    /* 0x016 */ s16 m016;
    /* 0x018 */ s16 m018;
    /* 0x01A */ u8 m01A[0x01C - 0x01A];
    /* 0x01C */ f32 m01C[6];
    /* 0x034 */ f32 m034[10];
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ f32 m068;
    /* 0x06C */ f32 m06C;
    /* 0x070 */ f32 m070;
    /* 0x074 */ f32 m074;
    /* 0x078 */ f32 m078;
    /* 0x07C */ f32 m07C;
    /* 0x080 */ f32 m080;
    /* 0x084 */ f32 m084;
    /* 0x088 */ f32 m088;
    /* 0x08C */ f32 m08C;
    /* 0x090 */ f32 m090;
    /* 0x094 */ f32 m094;
    /* 0x098 */ f32 m098[9];
    /* 0x0BC */ f32 m0BC[9];
    /* 0x0E0 */ f32 m0E0;
    /* 0x0E4 */ f32 m0E4;
    /* 0x0E8 */ f32 m0E8;
    /* 0x0EC */ f32 m0EC;
    /* 0x0F0 */ f32 m0F0;
    /* 0x0F4 */ f32 m0F4;
    /* 0x0F8 */ f32 m0F8;
    /* 0x0FC */ cXyz m0FC;
};  // Size: 0x108
STATIC_ASSERT(sizeof(daDaiocta_HIO_c) == DEMO_SELECT(0x10C, 0x108));

#endif /* D_A_DAIOCTA_H */
