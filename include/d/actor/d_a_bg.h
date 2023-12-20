#ifndef D_A_BG_H
#define D_A_BG_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class J3DModelData;
class J3DAnmTextureSRTKey;
class J3DAnmTevRegKey;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

class daBg_btkAnm_c {
public:
    BOOL create(J3DModelData*, J3DAnmTextureSRTKey*);
    void entry(J3DModelData*);
    void play();

public:
    /* 0x00 */ mDoExt_btkAnm * anm;
    /* 0x04 */ u8 special;
};

class daBg_brkAnm_c {
public:
    BOOL create(J3DModelData*, J3DAnmTevRegKey*);
    void entry(J3DModelData*);
    void play();

public:
    /* 0x00 */ mDoExt_brkAnm * anm;
    /* 0x04 */ u8 special;
};

class daBg_c : public fopAc_ac_c {
public:
    void calcRoomMemory(char**, long*, char**, long*) {}
    void getRoomMemory(int) {}
    void initRoomMemory() {}

    ~daBg_c();
    const char * setArcName();
    inline BOOL createHeap();
    s32 create();
    inline BOOL execute();
    inline BOOL draw();
    inline BOOL isDelete();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ struct BgModel {
        J3DModel * model;
        daBg_btkAnm_c * btk;
        daBg_brkAnm_c * brk;
        dKy_tevstr_c * mpTevStr;
    } bg[4];
    /* 0x2D8 */ dBgW * bgw;
    /* 0x2DC */ u8 mUnloadTimer;
};

// inline void searchRoomMemory(int) {}
// inline void searchRoomNo(int, readRoom_c*) {}

#endif /* D_A_BG_H */
