#ifndef D_A_GHOSTSHIP_H
#define D_A_GHOSTSHIP_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cloth_packet.h"
#include "d/d_bg_s_acch.h"
#include "d/d_lib.h"

class daGhostship_c : public fopAc_ac_c {
public:
    bool checkInShip() { return mbCanEnterShip; }
    void getAlpha() {}
    void setMtx() {}

    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL _createHeap();
    void pathMove();
    void modeWaitInit();
    void modeWait();
    void modeRealize();
    BOOL _pathMove(cXyz*, cXyz*, cXyz*);
    void modePathMoveInit();
    void modePathMove();
    void modeProcCall();
    void createInit();
    void getArg();

public:
    /* 0x290 */ u32 mMode;
    /* 0x294 */ s32 mPathNo;
    /* 0x298 */ u8 moonPhase;
    /* 0x29C */ cXyz mCurPntPos;
    /* 0x2A8 */ s8 mPathPntNo;
    /* 0x2AC */ dPath* mPath;
    /* 0x2B0 */ u32 field_0x2B0;
    /* 0x2B4 */ cXyz mNextPntPos;
    /* 0x2C0 */ u32 field_0x2C0;
    /* 0x2C4 */ u32 field_0x2C4;
    /* 0x2C8 */ u32 field_0x2C8;
    /* 0x2CC */ request_of_phase_process_class mPhs;
    /* 0x2D4 */ request_of_phase_process_class mClothPhs;
    /* 0x2DC */ dCloth_packet_c* mpCloth;
    /* 0x2E0 */ dCloth_packet_c* mpCloth2;
    /* 0x2E4 */ J3DModel* mpModel;
    /* 0x2E8 */ mDoExt_btkAnm mBtk;
    /* 0x2FC */ f32 mAlpha;
    /* 0x300 */ dBgS_ObjAcch mAcch;
    /* 0x4C4 */ dBgS_AcchCir mCir;
    /* 0x504 */ dLib_wave_c mWave;
    /* 0x510 */ bool mbEnteredShip;
    /* 0x514 */ dLib_circle_path_c mPaths[0xC];
    /* 0x6C4 */ f32 field_0x6C4[0xC];
    /* 0x6F4 */ cXyz mPathPos;
    /* 0x700 */ u32 field_0x700;
    /* 0x704 */ f32 mPathSpeed;
    /* 0x708 */ bool mbCanEnterShip;

    static const u32 m_heapsize;
    static const char m_arc_name[];
    static const char m_cloth_arc_name[];
};

class daGhostship_HIO_c : public mDoHIO_entry_c {
public:
    daGhostship_HIO_c();
    ~daGhostship_HIO_c() {}

    /* 0x04 */ u8 field_0x04;
    /* 0x05 */ bool hideShip;
    /* 0x08 */ f32 shipAlpha;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 shipHideDist;
    /* 0x14 */ f32 shipEnterDist;
};

#endif /* D_A_GHOSTSHIP_H */
