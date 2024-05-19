#ifndef D_A_OBJ
#define D_A_OBJ

#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"

class dBgS_GndChk;
class cBgS_PolyInfo;

namespace daObj {
    template <typename T>
    int PrmAbstract(const fopAc_ac_c* actor, T width, T shift) {
        u32 param = fopAcM_GetParam((fopAc_ac_c*)actor);
        return ((1 << width) - 1) & (param >> shift);
    }
    
    void make_land_effect(fopAc_ac_c*, dBgS_GndChk*, float);
    void get_wind_spd(fopAc_ac_c*, float);
    cXyz& get_path_spd(cBgS_PolyInfo&, float);
    void posMoveF_stream(fopAc_ac_c*, const cXyz*, const cXyz*, float, float);
    void posMoveF_grade(fopAc_ac_c*, const cXyz*, const cXyz*, float, float, const cXyz*, float, float, const cXyz*);
    void quat_rotBaseY(Quaternion*, const cXyz&);
    void quat_rotBaseY2(Quaternion*, const cXyz&);
    void quat_rotBaseZ(Quaternion*, const cXyz&);
    void quat_rotVec(Quaternion*, const cXyz&, const cXyz&);
    void SetCurrentRoomNo(fopAc_ac_c*, dBgS_GndChk*);
    void HitSeStart(const cXyz*, int, const dCcD_GObjInf*, unsigned long);
    void HitEff_sub_kikuzu(const cXyz*, const cXyz*, const dKy_tevstr_c*);
    void HitEff_kikuzu(const fopAc_ac_c*, const dCcD_Cyl*);
    void HitEff_hibana(const cXyz*, const cXyz*);
    void HitEff_hibana(const fopAc_ac_c*, const dCcD_Cyl*);
};

#endif /* D_A_OBJ */
