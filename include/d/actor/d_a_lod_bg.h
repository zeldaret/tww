#ifndef D_A_LOD_BG_H
#define D_A_LOD_BG_H

#include "f_op/f_op_actor.h"

class J3DModelData;
class mDoDvdThd_mountXArchive_c;
class JKRArchive;
class JKRExpHeap;

class daLodbg_c : public fopAc_ac_c {
public:
    inline void createHeap();
    inline BOOL draw();
    inline BOOL execute();
    void setExecute(int (daLodbg_c::*)()) {}

    void deleteModelData();
    void loadModelData(const char*, J3DModelData*&, JKRSolidHeap*&, unsigned long&);
    void createModelData();
    void execCreateWait();
    void execReadWait();
    void execDeleteWait();
    
    static s32 sObjectCount;
    static JKRExpHeap* sLocalHeap;

public:
    /* 0x290 */ int (daLodbg_c::*mExecFunc)();
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ J3DModel* mpModel2[2];
    /* 0x2A8 */ u8 mAlpha;
    /* 0x2A9 */ u8 mDrawModel2;
    /* 0x2AA */ u8 m2AA[0x2AC - 0x2AA];
    /* 0x2AC */ J3DModelData* mpModelData;
    /* 0x2B0 */ J3DModelData* mpModelData2;
    /* 0x2B4 */ mDoDvdThd_mountXArchive_c* mpMountCommand;
    /* 0x2B8 */ JKRArchive* mpArchive;
    /* 0x2BC */ u32 m2BC;
    /* 0x2C0 */ u32 m2C0;
    /* 0x2C4 */ JKRSolidHeap* mpHeap;
    /* 0x2C8 */ JKRSolidHeap* mpHeap2;
};

#endif /* D_A_LOD_BG_H */
