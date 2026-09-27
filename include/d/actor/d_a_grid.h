#ifndef D_A_GRID_H
#define D_A_GRID_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "m_Do/m_Do_hostIO.h"

class daHo_packet_c : public J3DMatPacket {
public:
    daHo_packet_c() {
        field_0x18a2 = 0;
        field_0x189c = 0;
        field_0x18a0 = 0;
        field_0x189e = 0;
        mAlpha = 0xFF;
        setShapePacket(&mShapePacket);
    }

    void setBackNrm();
    void setNrmMtx(cXyz&);
    void setNrmVtx(cXyz*, int, int);
    void setTopNrmVtx(cXyz*);

    virtual void draw();
    virtual ~daHo_packet_c() {}

    cXyz* getPos() { return mPos[field_0x18a2]; }
    cXyz* getNrm() { return mNrm[field_0x18a2]; }
    cXyz* getBackNrm() { return mBackNrm[field_0x18a2]; } // not in debug map due to not being used in that version
    void changeCurrentPos() { field_0x18a2 ^= 1; }
    void setAlpha(u8 i_alpha) { mAlpha = i_alpha; }
    u8 getAlpha() { return mAlpha; }
    void setTevStr(dKy_tevstr_c* i_tevstr) { mpTevStr = i_tevstr; }
    MtxP getMtx() { return mMtx; }

public:
    /* 0x003C */ J3DShapePacket mShapePacket;
    /* 0x0080 */ Mtx mMtx;
    /* 0x00B0 */ dKy_tevstr_c* mpTevStr;
    /* 0x00B4 */ cXyz mPos[2][85];
    /* 0x08AC */ cXyz mNrm[2][85];
    /* 0x10A4 */ cXyz mBackNrm[2][85];
    /* 0x189C */ s16 field_0x189c;
    /* 0x189E */ s16 field_0x189e;
    /* 0x18A0 */ s16 field_0x18a0;
    /* 0x18A2 */ u8 field_0x18a2;
    /* 0x18A3 */ u8 mAlpha;
};

class daGrid_c : public fopAc_ac_c {
public:
    daGrid_c() {}

    void force_calc_wind_rel_angle(s16 i_angle) {
        mForceWindRelAngle = i_angle;
        mIsForceWindRelAngle = TRUE;
    }

    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x0290 */ request_of_phase_process_class mClothPhase;
    /* 0x0298 */ request_of_phase_process_class mShipPhase;
    /* 0x02A0 */ daHo_packet_c mPacket;
    /* 0x1B44 */ u32 field_0x1b44;
    /* 0x1B48 */ s8 field_0x1b48;
    /* 0x1B49 */ u8 field_0x1b49;
    /* 0x1B4A */ s16 field_0x1b4a;
    /* 0x1B4C */ s16 field_0x1b4c;
    /* 0x1B4E */ s16 field_0x1b4e;
    /* 0x1B50 */ u8 field_0x1B50[0x1B54 - 0x1B50];
    /* 0x1B54 */ f32 field_0x1b54[85];
    /* 0x1CA8 */ cXyz field_0x1ca8[85];
    /* 0x20A4 */ u8 field_0x20A4[0x2200 - 0x20A4];
    /* 0x2200 */ f32 field_0x2200;
    /* 0x2204 */ f32 field_0x2204;
    /* 0x2208 */ f32 field_0x2208;
    /* 0x220C */ u8 field_0x220C[0x2210 - 0x220C];
    /* 0x2210 */ s16 field_0x2210;
    /* 0x2212 */ s16 field_0x2212;
    /* 0x2214 */ s16 field_0x2214;
    /* 0x2216 */ s16 mForceWindRelAngle;
    /* 0x2218 */ u8 mIsForceWindRelAngle;
};

#endif /* D_A_GRID_H */
