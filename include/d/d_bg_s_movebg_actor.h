#ifndef D_BG_S_MOVEBG_ACTOR_H
#define D_BG_S_MOVEBG_ACTOR_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "f_op/f_op_actor_mng.h"

class dBgW;
typedef void (*MoveBGActor_SetFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_Typical(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_RotY(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_TypicalRotY(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_Trans(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);

class dBgS_MoveBgActor : public fopAc_ac_c {
public:
    /* 0x290 */ dBgW* mpBgW;
    /* 0x294 */ Mtx mBgMtx;
    /* 0x2C4 */ /* vtable */

    dBgS_MoveBgActor();
    int MoveBGCreateHeap();
    int MoveBGCreate(char const* resName, int resIndex, MoveBGActor_SetFunc callback, u32 resSize);
    int MoveBGDelete();
    int MoveBGExecute();

    int MoveBGDraw() { return Draw(); }
    int MoveBGIsDelete() { return IsDelete(); }

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
};  // Size: 0x2C8

STATIC_ASSERT(sizeof(dBgS_MoveBgActor) == 0x2C8);

#endif /* D_BG_S_MOVEBG_ACTOR_H */
