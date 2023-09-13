#ifndef D_BG_S_MOVEBG_ACTOR_H
#define D_BG_S_MOVEBG_ACTOR_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "f_op/f_op_actor_mng.h"

class dBgW;
typedef void (*MoveBGActor_SetFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*,
                                    csXyz*);

class dBgS_MoveBgActor : public fopAc_ac_c {
public:
    /* 0x290 */ dBgW* mpBgW;
    /* 0x294 */ Mtx mBgMtx;

    dBgS_MoveBgActor();
    int MoveBGCreateHeap();
    int MoveBGCreate(char const*, int, MoveBGActor_SetFunc, u32);
    int MoveBGDelete();
    int MoveBGExecute();

    int MoveBGDraw() { return Draw(); }

    virtual int CreateHeap() { return 1; }
    virtual int Create() { return 1; }
    virtual int Execute(Mtx**) { return 1; }
    virtual int Draw() { return 1; }
    virtual int Delete() { return 1; }
    virtual int IsDelete() { return 1; }
    virtual int ToFore() { return 1; }
    virtual int ToBack() { return 1; }

    static const char* m_name;
    static int m_dzb_id;
    static MoveBGActor_SetFunc m_set_func;
};

#endif /* D_BG_S_MOVEBG_ACTOR_H */