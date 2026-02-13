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
        
    };

    enum Mode_e {
        
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
    void isLivingEye();
    void isDead();
    void isDamageEye();
    void isDamageBombEye();
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
    /* 0x0290 */ cXyz field_0x0290[37];
    /* 0x044C */ u8 field_0x044C[0x056C - 0x044C];
    /* 0x056C */ s32 field_0x056C;
    /* 0x0570 */ u8 field_0x0570[0x0574 - 0x0570];
    /* 0x0574 */ u8 mSwitchNo;
    /* 0x0575 */ u8 field_0x0575[0x0580 - 0x0575];
    /* 0x0580 */ request_of_phase_process_class field_0x0580;
    /* 0x0588 */ mDoExt_McaMorf* mpMorf;
    /* 0x058C */ mDoExt_brkAnm field_0x058C;
    /* 0x05A4 */ dCcD_Sph field_0x05A4[6];
    /* 0x0CAC */ dCcD_Cps field_0x0CAC[17];
    /* 0x2164 */ dCcD_Stts field_0x2164;
    /* 0x21A0 */ cXyz field_0x21A0;
    /* 0x21AC */ cXyz field_0x21AC;
    /* 0x21B8 */ cXyz field_0x21B8;
    /* 0x21C4 */ cXyz field_0x21C4;
    /* 0x21D0 */ cXyz field_0x21D0;
    /* 0x21DC */ cXyz field_0x21DC;
    /* 0x21E8 */ cXyz field_0x21E8;
    /* 0x21F4 */ u8 field_0x21F4[0x220C - 0x21F4];
    /* 0x220C */ cXyz field_0x220C;
    /* 0x2218 */ dBgS_ObjAcch field_0x2218;
    /* 0x23DC */ dBgS_AcchCir field_0x23DC;
    /* 0x241C */ dPa_followEcallBack field_0x241C;
    /* 0x2430 */ u8 field_0x2430[0x2434 - 0x2430];
    /* 0x2434 */ cXyz field_0x2434;
    /* 0x2440 */ u8 field_0x2440[0x26C8 - 0x2440];
    /* 0x2440 */ JntHit_c* field_0x26C8;
    /* 0x26CC */ J3DModel* field_0x26CC;
    /* 0x26D0 */ mDoExt_brkAnm field_0x26D0;
    /* 0x26E8 */ mDoExt_btkAnm field_0x26E8;
    /* 0x26FC */ u8 field_0x26FC[0x2774 - 0x26FC];
    /* 0x2774 */ mDoExt_bckAnm field_0x2774[30];
    /* 0x2954 */ mDoExt_btkAnm field_0x2954[30];
    /* 0x2BAC */ mDoExt_brkAnm field_0x2BAC[30];
    /* 0x2E7C */ u8 field_0x2E7C[0x2EF4 - 0x2E7C];
    /* 0x2EF4 */ cXyz field_0x2EF4[30];
    /* 0x305C */ cXyz field_0x305C[30];
    /* 0x31C4 */ u8 field_0x31C4[0x31C8 - 0x31C4];
};  // Size: 0x31C8
STATIC_ASSERT(sizeof(daDaiocta_c) == 0x31C8);

class daDaiocta_HIO_c : public mDoHIO_entry_c {
public:
    daDaiocta_HIO_c();

public:
    /* 0x004 */ u8 field_0x004;
    /* 0x005 */ u8 field_0x005;
    /* 0x006 */ u8 field_0x006;
    /* 0x007 */ u8 field_0x007[0x008 - 0x007];
    /* 0x008 */ u8 field_0x008;
    /* 0x009 */ u8 field_0x009[0x00C - 0x009];
    /* 0x00C */ s16 field_0x00C;
    /* 0x00E */ s16 field_0x00E;
    /* 0x010 */ s16 field_0x010;
    /* 0x012 */ s16 field_0x012;
    /* 0x014 */ s16 field_0x014;
    /* 0x016 */ s16 field_0x016;
    /* 0x018 */ s16 field_0x018;
    /* 0x01A */ u8 field_0x01A[0x01C - 0x01A];
    /* 0x01C */ f32 field_0x01C;
    /* 0x020 */ f32 field_0x020;
    /* 0x024 */ f32 field_0x024;
    /* 0x028 */ f32 field_0x028;
    /* 0x02C */ f32 field_0x02C;
    /* 0x030 */ f32 field_0x030;
    /* 0x034 */ f32 field_0x034;
    /* 0x038 */ f32 field_0x038;
    /* 0x03C */ f32 field_0x03C;
    /* 0x040 */ f32 field_0x040;
    /* 0x044 */ f32 field_0x044;
    /* 0x048 */ f32 field_0x048;
    /* 0x04C */ f32 field_0x04C;
    /* 0x050 */ f32 field_0x050;
    /* 0x054 */ f32 field_0x054;
    /* 0x058 */ f32 field_0x058;
    /* 0x05C */ f32 field_0x05C;
    /* 0x060 */ f32 field_0x060;
    /* 0x064 */ f32 field_0x064;
    /* 0x068 */ f32 field_0x068;
    /* 0x06C */ f32 field_0x06C;
    /* 0x070 */ f32 field_0x070;
    /* 0x074 */ f32 field_0x074;
    /* 0x078 */ f32 field_0x078;
    /* 0x07C */ f32 field_0x07C;
    /* 0x080 */ f32 field_0x080;
    /* 0x084 */ f32 field_0x084;
    /* 0x088 */ f32 field_0x088;
    /* 0x08C */ f32 field_0x08C;
    /* 0x090 */ f32 field_0x090;
    /* 0x094 */ f32 field_0x094;
    /* 0x098 */ u8 field_0x098[0x09C - 0x098];
    /* 0x09C */ f32 field_0x09C;
    /* 0x0A0 */ f32 field_0x0A0;
    /* 0x0A4 */ f32 field_0x0A4;
    /* 0x0A8 */ f32 field_0x0A8;
    /* 0x0AC */ f32 field_0x0AC;
    /* 0x0B0 */ f32 field_0x0B0;
    /* 0x0B4 */ f32 field_0x0B4;
    /* 0x0B8 */ f32 field_0x0B8;
    /* 0x0BC */ u8 field_0x0BC[0x0C0 - 0x0BC];
    /* 0x0C0 */ f32 field_0x0C0;
    /* 0x0C4 */ f32 field_0x0C4;
    /* 0x0C8 */ f32 field_0x0C8;
    /* 0x0CC */ f32 field_0x0CC;
    /* 0x0D0 */ f32 field_0x0D0;
    /* 0x0D4 */ f32 field_0x0D4;
    /* 0x0D8 */ f32 field_0x0D8;
    /* 0x0DC */ u8 field_0x0DC[0x0E0 - 0x0DC];
    /* 0x0E0 */ f32 field_0x0E0;
    /* 0x0E4 */ f32 field_0x0E4;
    /* 0x0E8 */ f32 field_0x0E8;
    /* 0x0EC */ f32 field_0x0EC;
    /* 0x0F0 */ f32 field_0x0F0;
    /* 0x0F4 */ f32 field_0x0F4;
    /* 0x0F8 */ f32 field_0x0F8;
    /* 0x0FC */ f32 field_0x0FC;
    /* 0x100 */ f32 field_0x100;
    /* 0x104 */ f32 field_0x104;
};  // Size: 0x108
STATIC_ASSERT(sizeof(daDaiocta_HIO_c) == 0x108);

#endif /* D_A_DAIOCTA_H */
