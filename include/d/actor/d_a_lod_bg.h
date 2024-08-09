#ifndef D_A_LOD_BG_H
#define D_A_LOD_BG_H

#include "f_op/f_op_actor.h"

class J3DModelData;
class mDoDvdThd_mountXArchive_c;
class JKRArchive;
class JKRExpHeap;

class daLodbg_c : public fopAc_ac_c {
public:
    daLodbg_c();
    ~daLodbg_c();
    BOOL createHeap();
    BOOL draw();
    inline BOOL execute();
    inline s32 getRoomNo(); // fake, debug maps are old but some inline here appears to be there
    void setExecute(BOOL (daLodbg_c::*func)()) { mExecuteFunc = func; }

    void deleteModelData();
    BOOL loadModelData(const char*, J3DModelData*&, JKRSolidHeap*&, unsigned long&);
    BOOL createModelData();
    BOOL execCreateWait();
    BOOL execReadWait();
    BOOL execDeleteWait();

    static s32 sObjectCount;
    static JKRExpHeap* sLocalHeap;
    static const char LodAllPath[];

public:
    /* 0x290 */ BOOL (daLodbg_c::*mExecuteFunc)();
    /* 0x29C */ J3DModel* mModel;
    /* 0x2A0 */ J3DModel* mModel2[2];
    /* 0x2A8 */ u8 mAlpha;
    /* 0x2A9 */ bool mDrawModel2;
    /* 0x2AA */ u8 m2AA[0x2AC - 0x2AA];
    /* 0x2AC */ J3DModelData* mModelData;
    /* 0x2B0 */ J3DModelData* mModelData2;
    /* 0x2B4 */ mDoDvdThd_mountXArchive_c* mMountCommand;
    /* 0x2B8 */ JKRArchive* mArchive;
    /* 0x2BC */ u32 mDataSize;
    /* 0x2C0 */ u32 mDataSize2;
    /* 0x2C4 */ JKRSolidHeap* mDataHeap;
    /* 0x2C8 */ JKRSolidHeap* mDataHeap2;
};

#endif /* D_A_LOD_BG_H */
