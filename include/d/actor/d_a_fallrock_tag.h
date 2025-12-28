#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

struct daFallRockTag_mData {
    f32 placeholder1;
    f32 placeholder2;
    f32 placeholder3;
    f32 placeholder4;
    f32 placeholder5;
    s16 placeholder6;
    s16 placeholder7;
    s16 placeholder8;
    s16 placeholder9;  
};

class daFallRockTag_c : public fopAc_ac_c {
public:
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    //void getData(); // weak but not inlined?
    const daFallRockTag_mData* getData();
    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);
    inline ~daFallRockTag_c();

public:
    /* Place member variables here */
    static f32 m_div_num;//what the hell, why size 8?!
    static daFallRockTag_mData m_data;

    
    /* 0x290 request??? */ request_of_phase_process_class mPhs;
    s32 field9_0x298;
    u8 another_padding[2];
    /*0x29e*/ u8 mParameters;
};

#endif /* D_A_FALLROCK_TAG_H */
