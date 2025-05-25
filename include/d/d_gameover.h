#ifndef D_GAMEOVER_H
#define D_GAMEOVER_H

#include "d/d_com_inf_game.h"
#include "d/d_menu_save.h"
#include "f_op/f_op_msg_mng.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "SSystem/SComponent/c_phase.h"


class dDlst_Gameover_CAPTURE_c : public dDlst_base_c {
public:
    virtual ~dDlst_Gameover_CAPTURE_c() {}
    virtual void draw();
};

class dDlst_GameOverScrnDraw_c : public dDlst_base_c {
public:
    dDlst_GameOverScrnDraw_c() {
        field_0x338 = 0;
        field_0x33c = 0;
        field_0x330 = 0;
        field_0x334 = 0;

        field_0x32c = 8;
        mAlpha = 0.0f;
    }

    f32 acc(s16 param_0, s16 param_1, s16 param_2) {
        return ((f32)(param_1 - param_2) * (f32)(param_1 - param_2)) / ((f32)(param_0 - param_2) * (f32)(param_0 - param_2));
    }
    void deleteScreen() { delete scrn; }
    void setAlpha(f32 alpha) { mAlpha = alpha; }
    void stopEmitter0() {
        if (mpEmitter0 != NULL)
            mpEmitter0->becomeInvalidEmitter();
    }
    void stopEmitter1() {
        if (mpEmitter1 != NULL)
            mpEmitter1->becomeInvalidEmitter();
    }

    virtual ~dDlst_GameOverScrnDraw_c() {}
    void setScreen(const char*, JKRArchive*);
    void valueInit();
    BOOL animeOpen();
    BOOL animeClose();
    void setEmitter0(cXyz);
    void setEmitter1(cXyz);
    BOOL anime1(int);
    BOOL anime2(int);
    void setRotate(fopMsgM_pane_class*, f32);

    virtual void draw();

private:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class letter[8];
#if VERSION > VERSION_JPN
    /* 0x1C8 */ u8 field_0x1c8[0x318 - 0x1c8];
#endif
    /* Offsets below are for USA/PAL */
    /* 0x318 */ fopMsgM_pane_alpha_class blak;
    /* 0x320 */ JPABaseEmitter* mpEmitter0;
    /* 0x324 */ JPABaseEmitter* mpEmitter1;
    /* 0x328 */ f32 mAlpha;
    /* 0x32C */ s32 field_0x32c;
    /* 0x330 */ s32 field_0x330;
    /* 0x334 */ u32 field_0x334;
    /* 0x338 */ u32 field_0x338;
    /* 0x33C */ u16 field_0x33c;
    /* 0x33E */ s16 mRotate[8];
    /* 0x34E */ u8 field_0x34e[0x410 - 0x34E];
};

class dGameover_c : public msg_class {
public:
    void animeStart() { mAnimeStart = true; }
    void setBackAlpha(f32 alpha) { dgo_scrn_c->setAlpha(alpha); }

    cPhs_State _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();
    BOOL deleteCheck();

private:
    /* 0x0FC */ dMenu_save_c* dMs_c;
    /* 0x100 */ dDlst_GameOverScrnDraw_c* dgo_scrn_c;
    /* 0x104 */ dDlst_Gameover_CAPTURE_c* dgo_capture_c;
    /* 0x108 */ request_of_phase_process_class mPhs;
    /* 0x110 */ JKRExpHeap* mpHeap;
    /* 0x114 */ s16 field_0x114;
    /* 0x116 */ s16 field_0x116;
    /* 0x118 */ u8 mState;
    /* 0x119 */ bool mAnimeStart;
    /* 0x11C */ u8 field_0x11c;
};

#endif /* D_GAMEOVER_H */
