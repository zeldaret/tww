#ifndef D_A_TAG_ATTENTION_H
#define D_A_TAG_ATTENTION_H

#include "SSystem/SComponent/c_math.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daTagAttention {
    class Act_c : public fopAc_ac_c {
    public:
        bool chk_inside(cXyz* pos) const {
            if (!m_b0x290){
                return false;
            }

            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            cXyz plyrToObjVec = player->current.pos-current.pos;
            if (subtype == 0){
                // spherical collision check
                f32 distance = plyrToObjVec.abs();
                
                if (distance > scale.x * 100.0f) {
                    return false;
                }
            }else{
                // box collision check
                if (current.angle.y){
                    s16 yRotAngle = current.angle.y;
                    f32 x =
                        plyrToObjVec.x * cM_scos(yRotAngle) -
                        plyrToObjVec.z * cM_ssin(yRotAngle);
                    f32 z =
                        plyrToObjVec.x * cM_ssin(yRotAngle) +
                        plyrToObjVec.z * cM_scos(yRotAngle);
                    plyrToObjVec.x = x;
                    plyrToObjVec.z = z;
                }

                if ((plyrToObjVec.x < -scale.x * 100.0f) || (plyrToObjVec.x > scale.x * 100.0f)){
                    return false;
                }
                if ((plyrToObjVec.y < -scale.y * 100.0f) || (plyrToObjVec.y > scale.y * 100.0f)){
                    return false;
                }
                if ((plyrToObjVec.z < -scale.z * 100.0f) || (plyrToObjVec.z > scale.z * 100.0f)){
                    return false;
                }
            }

            *pos = current.pos;
            return true;
        }

        int prm_get_Type() const
        {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }

        int prm_get_swSave() const
        {
            return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }
    
        cPhs_State _create();
        bool _execute();

        enum Prm_e {
            PRM_TYPE_W = 0x02,
            PRM_TYPE_S = 0x08,
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };

    public:
        /* 0x290 */ bool m_b0x290;
        /* padding */ s8 mPad[8];
        /* 0x2B8 */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Sph mSph;
    };
};

#endif /* D_A_TAG_ATTENTION_H */
