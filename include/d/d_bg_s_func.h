#ifndef D_BG_S_FUNC_H
#define D_BG_S_FUNC_H

#include "SSystem/SComponent/c_xyz.h"

class dBgS_SplGrpChk;

f32 dBgS_ObjGndChk_Func(cXyz&);
f32 dBgS_ObjGndChk_Wtr_Func(cXyz&);
BOOL dBgS_SplGrpChk_In_ObjGnd(cXyz&, dBgS_SplGrpChk*, f32);
f32 dBgS_GetWaterHeight(cXyz&);
u32 dBgS_GetGndMtrlSndId_Func(cXyz, f32);

#endif /* D_BG_S_FUNC_H */
