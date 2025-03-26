//
// Generated by dtk
// Translation Unit: d_a_tpota.cpp
//

#include "d/actor/d_a_tpota.h"
#include "d/d_procname.h"
#include "JSystem/JGeometry.h"

#include "JSystem/JParticle/JPAParticle.h"
#include "d/d_particle.h"
#include "d/d_com_inf_game.h"


const u16 l_daTpota_idx_table[2] = {0x82AE, 0x82AF};
/* 00000078-000001D0       .text _create__9daTpota_cFv */
s32 daTpota_c::_create() {
    fopAcM_SetupActor(this, daTpota_c);
    int count = 0;
    JPABaseEmitter* emitter;

    do {
        position[count] = current.pos;
        angle[count] = current.angle;
    
        emitter = dComIfGp_particle_set(
            l_daTpota_idx_table[count],
            &position[count], 
            &angle[count], 
            NULL, 0xff, NULL, -1, NULL, NULL, NULL
        );
        emitters[count] = emitter;
        count++;
    }while (count < 2);
    return 4;
}

/* 00000250-00000298       .text _delete__9daTpota_cFv */
bool daTpota_c::_delete() {
    int count = 0;
    while (count < 2) {
        if (emitters[count] != NULL) {
            emitters[count]->becomeInvalidEmitter();
            emitters[count] = 0;
        }
        count++;
    }
    return 1;
}

/* 00000298-000002FC       .text make_ripple__9daTpota_cF4cXyz */
void daTpota_c::make_ripple(cXyz i_position) {
    dComIfGp_particle_set(dPa_name::ID_SCENE_82B0, &i_position,
        NULL, NULL, 0xff, NULL, -1, NULL, NULL, NULL);
    return;
}



/* 000002FC-00000354       .text check_water_h__9daTpota_cFP15JPABaseParticlef */
int daTpota_c::check_water_h(JPABaseParticle* i_ptcl, float i_position_y) {
    
    unknown_struct* unknown_struct = field_0x2C4;
    int ret = 0;
    if (i_position_y <= -230.0f) {
        for (int i = 0; i < ARRAY_SIZE(field_0x2C4); i++, unknown_struct++) {
            if (unknown_struct->ptcl == i_ptcl) {
                if (unknown_struct->pos_y > -230.0f) {
                    ret = 1;
                }
                break;
            }
        }
    }
    return ret;
}

/* 00000354-00000380       .text clear_splash__9daTpota_cFv */
void daTpota_c::clear_splash() {
    unknown_struct* unknown_struct = field_0x2C4;
    int count = 30;

    while (count != 0) {
        unknown_struct->ptcl = NULL;
        unknown_struct->pos_y = 0.0;
        unknown_struct++;
        count--;
    }
    return;
}

/* 00000380-000003F4       .text renew_splash__9daTpota_cFv */
void daTpota_c::renew_splash() {
    

    if (emitters[1] != NULL) {
        JSUPtrList* list = &emitters[1]->mActiveParticles;
        unknown_struct *unknown_struct = field_0x2C4;
        if(list != NULL){
            clear_splash();
            for (JSUPtrLink* link = list->getFirstLink(); link != NULL && (link != NULL); link = link->getNext()){
                JPABaseParticle* particle = (JPABaseParticle*)link->getObjectPtr();
                JGeometry::TVec3<f32> position;
                particle->getGlobalPosition(position);
                unknown_struct->ptcl = particle;
                unknown_struct->pos_y = position.y;
                unknown_struct++;
            }   
            
        }

    }
    return;
}

/* 000003F4-000004C8       .text _execute__9daTpota_cFv */
bool daTpota_c::_execute() {
    float local_38;
    if (emitters[1] != NULL){
        JSUPtrList* list = &emitters[1]->mActiveParticles;
        if(list != NULL){
            for (JSUPtrLink* link = list->getFirstLink(); link != NULL && (link != NULL);
            link = link->getNext()){
                JPABaseParticle* particle = (JPABaseParticle *)link->getObjectPtr();
                JGeometry::TVec3<f32> position;
                particle->getGlobalPosition(position);
                int idk = check_water_h(particle, position.y);
                if(idk != 0){
                    cXyz local_48;
                    local_48.x = position.x;
                    local_48.y = -230.0;
                    local_48.z = position.z;
                    make_ripple(local_48);
                }
            }
        }
        renew_splash();
    }
    return 1;
}


/* 000004C8-000004D0       .text _draw__9daTpota_cFv */
bool daTpota_c::_draw() {
    return TRUE;
}

namespace {
/* 000004D0-000004F0       .text Mthd_Create__23@unnamed@d_a_tpota_cpp@FPv */
s32 Mthd_Create(void* i_this) {
    return static_cast<daTpota_c*>(i_this)->_create();
}

/* 000004F0-00000514       .text Mthd_Delete__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<daTpota_c*>(i_this)->_delete();
}

/* 00000514-00000538       .text Mthd_Execute__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<daTpota_c*>(i_this)->_execute();
}


/* 00000538-0000055C       .text Mthd_Draw__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<daTpota_c*>(i_this)->_draw();
}

/* 0000055C-00000564       .text Mthd_IsDelete__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Tpota_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Tpota = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Tpota,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTpota_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00F8,
    /* Actor SubMtd */ &Tpota_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
