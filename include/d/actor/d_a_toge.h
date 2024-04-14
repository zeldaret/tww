#ifndef D_A_TOGE_H
#define D_A_TOGE_H

#include "f_op/f_op_actor.h"
#include "d/d_stage.h"

class daToge_c : public fopAc_ac_c {
public:
    void set_mtx(); // weak but not inlined?

    BOOL _delete();
    BOOL CreateHeap();
    s32 Create();
    s32 _create();
    BOOL _execute();
    void set_collision();
    void search_wind();
    void toge_move();
    void toge_seStart(unsigned long);
    BOOL _draw();

    static const char m_arcname[];
public:
    /* Place member variables here */
        
    /* 0x290 */ request_of_phase_process_class m_Phs; /* inferred */
    /* 0x298 */ J3DModel *mpModel;
    /* 0x29C */ char pad29C[0x3C];
    /* 0x2D8 */ void* unk2D8;                    /* inferred */
    /* 0x2D8 */ char pad2D8[0x44];
    /* 0x31C */ void *unk31C;                  /* inferred */
    /* 0x320 */ char pad320[0xE8];                  /* maybe part of unk31C[0x3B]? */
    /* 0x408 */ dBgW* mpBgW1;                       /* inferred */
    /* 0x40C */ char pad40C[0x30];                  /* maybe part of unk408[0xD]? */
    /* 0x43C */ dBgW* mpBgW2;                       /* inferred */
};

#endif /* D_A_TOGE_H */
