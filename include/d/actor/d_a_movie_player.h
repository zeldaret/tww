#ifndef D_A_MOVIE_PLAYER_H
#define D_A_MOVIE_PLAYER_H

#include "f_op/f_op_actor.h"
#include "d/d_drawlist.h"
#include "dolphin/dvd/dvd.h"

class daMP_c : public fopAc_ac_c {
public:
    u32 daMP_c_Get_arg_data();
    int daMP_c_Init();
    BOOL daMP_c_Finish();
    BOOL daMP_c_Main();
    BOOL daMP_c_Draw();
    static int daMP_c_Callback_Init(fopAc_ac_c*);
    static BOOL daMP_c_Callback_Finish(daMP_c*);
    static BOOL daMP_c_Callback_Main(daMP_c*);
    static BOOL daMP_c_Callback_Draw(daMP_c*);

public:
    /* 0x290 */ u32 (*mpCallBack1)();
    /* 0x294 */ u32 (*mpCallBack2)(f32);
};

class daMP_Dlst_base_c : public dDlst_base_c {
    void draw();
};

struct daMP_THPReadBuffer {
    /* 0x00 */ void* m00;
    /* 0x04 */ s32 m04;
};

struct daMP_Player_c { // Fake name
    /* 0x00 */ DVDFileInfo mFileInfo;
    /* 0x3C */ u8 m3C[0x50 - 0x3C];
    /* 0x50 */ u32 m50;
    /* 0x54 */ u8 m54[0x64 - 0x54];
    /* 0x64 */ s32 m64;
    /* 0x68 */ u8 m68[0xA6 - 0x68];
    /* 0xA6 */ u8 mA6;
    /* 0xA7 */ u8 mA7[0xA8 - 0xA7];
    /* 0xA8 */ s32 mA8;
    /* 0xAC */ u8 mAC[0xB8 - 0xAC];
    /* 0xB8 */ s32 mB8;
    /* 0xBC */ s32 mBC;
    /* 0xC0 */ s32 mC0;
};

struct THPVideoInfo {
    /* 0x00 */ u8 m00[0x0C - 0x00];
};

struct THPAudioInfo {
    /* 0x00 */ u8 m00[0x10 - 0x00];
};

inline s32 daMP_NEXT_READ_SIZE(daMP_THPReadBuffer* readBuf) {
    return *(s32*)readBuf->m00;
}

void daMP_PrepareReady(int);

#endif /* D_A_MOVIE_PLAYER_H */
