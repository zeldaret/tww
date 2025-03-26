#ifndef D_A_IB_H
#define D_A_IB_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"

class daIball_c : public fopAc_ac_c {
public:
    enum Mode {
        MODE_WAIT  = 0x0,
        MODE_WATER = 0x1,
    };
    
    typedef void (daIball_c::*ModeFunc)();
    
    void setPointLight();
    void createDisappearEffect(int, int);
    BOOL createItem();
    BOOL dead();
    void checkGeo();
    void mode_wait_init();
    void mode_wait();
    void mode_water_init();
    void mode_water();
    void animControl();
    void damage();
    void set_mtx();
    void CreateInit();
    BOOL _daIball_draw();
    BOOL _daIball_execute();
    BOOL _daIball_delete();
    cPhs_State _daIball_create();
    BOOL CreateHeap();
    
    static void init();
    static void regist(fopAc_ac_c*);
    static void remove(fopAc_ac_c*);
    static void remove_old();
    
    static u32 m_ib_actor[5];
    
    static const char m_arcname[];
    static dCcD_SrcCyl m_cyl_src;

public:
    /* 0x290 */ dBgS_ObjAcch mAcch;
    /* 0x454 */ dBgS_AcchCir mAcchCir;
    /* 0x494 */ dCcD_Stts mStts;
    /* 0x4D0 */ dCcD_Cyl mCyl;
    /* 0x600 */ J3DModel* mpModel;
    /* 0x604 */ mDoExt_btkAnm mBtkAnm;
    /* 0x618 */ mDoExt_brkAnm mBrkAnm[2];
    /* 0x648 */ mDoExt_bckAnm mBckAnm;
    /* 0x658 */ dPa_rippleEcallBack mRippleCb;
    /* 0x66C */ int mTimer;
    /* 0x670 */ u8 m670[0x674 - 0x670];
    /* 0x674 */ int mPlaySpeedIdx;
    /* 0x678 */ u8 m678[0x67C - 0x678];
    /* 0x67C */ f32 mPrevSpeedY;
    /* 0x680 */ u8 mMode;
    /* 0x681 */ bool mbPlayedSe;
    /* 0x682 */ u8 m682[0x684 - 0x682];
    /* 0x684 */ LIGHT_INFLUENCE mLight;
    /* 0x6A4 */ f32 mLightFlickerMult;
};

namespace daIball_prm {
    inline s8 getItemBitNo(daIball_c* ib) { return (fopAcM_GetParam(ib) >> 0x10) & 0xFF; }
    inline u16 getAdId(daIball_c* ib) { return fopAcM_GetParam(ib) & 0xFFFF; }
};

#endif /* D_A_IB_H */
