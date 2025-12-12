#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

struct daFallRockTag_mData {
    s32 placehloder1;
    s32 placehloder2;
    s32 placehloder3;
    s32 placehloder4;
    s32 placehloder5;
    s32 placehloder6;
    s32 placehloder7;
    
};

class daFallRockTag_c : public fopAc_ac_c {
public:
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    //void getData(); // weak but not inlined?
    const daFallRockTag_mData* getData();
    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);

public:
    /* Place member variables here */
    static f32 m_div_num;//what the hell, why size 8?!
    static daFallRockTag_mData m_data;

    /* 0x290 padding */
    u8 padding_0x290[8];
    s32 field9_0x298;
    u8 another_padding[2];
    /*0x29e*/ u8 mParameters;
    
    
   

};

#endif /* D_A_FALLROCK_TAG_H */
