//
// Generated by dtk
// Translation Unit: d_envse.cpp
//

#include "f_op/f_op_kankyo.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "d/d_procname.h"
#include "d/d_stage.h"
#include "d/d_path.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_audio.h"

class dEnvSe_c : public kankyo_class {
public:
    BOOL execute();

    /* 0xF8 */ u32 field_0xf8;
    /* 0xFC */ u32 field_0xfc;
};

/* 8017D4C0-8017D4C8       .text dEnvSe_Draw__FP8dEnvSe_c */
static BOOL dEnvSe_Draw(dEnvSe_c* i_this) {
    return TRUE;
}

/* 8017D4C8-8017D700       .text dEnvSe_getNearPathPos__FP4cXyzP4cXyzP5dPath */
void dEnvSe_getNearPathPos(cXyz* r30, cXyz* r31, dPath* r26) {
    int i;
    int nearIdx = 0;
    BOOL spc[2] = {FALSE, FALSE};
    cXyz sp30[2];
    f32 sp8;
    f32 f31 = FLOAT_MAX;
    dPath__Point* point = r26->mpPnt;
    cM3dGLin lin;
    
    for (i = 0; i < r26->m_num; point++, i++) {
        sp8 = r31->abs2(point->mPos);
        if (f31 > sp8) {
            f31 = sp8;
            nearIdx = i;
        }
    }
    
    point = &r26->mpPnt[nearIdx];
    if (nearIdx != 0) {
        lin.set(point[-1].mPos, point[0].mPos);
        spc[0] = cM3d_Len3dSqPntAndSegLine(&lin, r31, &sp30[0], &sp8);
    }
    if (nearIdx != r26->m_num-1) {
        lin.set(point[0].mPos, point[1].mPos);
        spc[1] = cM3d_Len3dSqPntAndSegLine(&lin, r31, &sp30[1], &sp8);
    }
    
    if (spc[0]) {
        if (spc[1]) {
            if (sp30[1].abs2(*r31) > sp8) {
                *r30 = sp30[0];
            } else {
                *r30 = sp30[1];
            }
        } else {
            *r30 = sp30[0];
        }
    } else {
        if (spc[1]) {
            *r30 = sp30[1];
        } else {
            *r30 = point[0].mPos;;
        }
    }
}

/* 8017D700-8017DAE0       .text execute__8dEnvSe_cFv */
BOOL dEnvSe_c::execute() {
    int roomNo = dComIfGp_roomControl_getStayNo();
    dStage_roomDt_c* fili_p = dComIfGp_roomControl_getStatusRoomDt(roomNo);
    if (fili_p == NULL) {
        return TRUE;
    }
    dStage_SoundInfo_c* soundInf = fili_p->getSoundInf();
    if (soundInf == NULL) {
        return TRUE;
    }
    
    int i = soundInf->num;
    stage_sound_data* sound_data = soundInf->m_entries;
    cXyz sp2c = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0))->mCamera.Eye();
    
    for (; i != 0; sound_data++, i--) {
        dPath* path;
        if (sound_data->field_0x17 == 0) {
            mDoAud_initSeaEnvPos();
            path = dPath_GetRoomPath(sound_data->field_0x18, roomNo);
            while (path != NULL) {
                dEnvSe_getNearPathPos(&mPos, &sp2c, path);
                mDoAud_registSeaEnvPos(&mPos);
                path = dPath_GetNextRoomPath(path, roomNo);
            }
            mDoAud_seaEnvSePlay(sound_data->field_0x14);
        } else if (sound_data->field_0x17 == 1) {
            f32 f31 = FLOAT_MAX;
            int r27;
            mPos = sp2c;
            path = dPath_GetRoomPath(sound_data->field_0x18, roomNo);
            while (path != NULL) {
                cXyz sp20;
                dEnvSe_getNearPathPos(&sp20, &sp2c, path);
                f32 f1 = sp20.abs2(sp2c);
                if (f1 < f31) {
                    f31 = f1;
                    r27 = path->mArg0;
                    mPos = sp20;
                }
                path = dPath_GetNextRoomPath(path, roomNo);
            }
            if (field_0xf8 == 0) {
                mDoAud_startSeaShoreSE(&mPos, r27);
                field_0xfc = r27;
            } else {
                mDoAud_continueSeaShoreSE(&mPos, field_0xfc);
            }
            dComIfGp_setWaveFrame(field_0xf8);
            if (field_0xf8 == 99) {
                field_0xf8 = 0;
            } else {
                field_0xf8++;
            }
        } else if (sound_data->field_0x17 == 2) {
            mDoAud_initRiverPos();
            path = dPath_GetRoomPath(sound_data->field_0x18, roomNo);
            while (path != NULL) {
                dEnvSe_getNearPathPos(&mPos, &sp2c, path);
                mDoAud_registRiverPos(&mPos);
                path = dPath_GetNextRoomPath(path, roomNo);
            }
            mDoAud_riverSePlay(sound_data->field_0x14, dComIfGp_getReverb(roomNo));
        } else if (sound_data->field_0x17 == 3) {
            f32 f31 = FLOAT_MAX;
            mPos = sp2c;
            path = dPath_GetRoomPath(sound_data->field_0x18, roomNo);
            while (path != NULL) {
                cXyz sp14;
                dEnvSe_getNearPathPos(&sp14, &sp2c, path);
                f32 f1 = sp14.abs2(sp2c);
                if (f1 < f31) {
                    f31 = f1;
                    mPos = sp14;
                }
                path = dPath_GetNextRoomPath(path, roomNo);
            }
            mDoAud_waterfallSePlay(sound_data->field_0x14, &mPos, dComIfGp_getReverb(roomNo));
        } else if (sound_data->field_0x17 == 4) {
            mDoAud_initWindowPos();
            path = dPath_GetRoomPath(sound_data->field_0x18, roomNo);
            while (path != NULL) {
                dEnvSe_getNearPathPos(&mPos, &sp2c, path);
                mDoAud_registWindowPos(&mPos);
                path = dPath_GetNextRoomPath(path, roomNo);
            }
        }
    }
    
    return TRUE;
}

/* 8017DAE0-8017DB00       .text dEnvSe_Execute__FP8dEnvSe_c */
static BOOL dEnvSe_Execute(dEnvSe_c* i_this) {
    return i_this->execute();
}

/* 8017DB00-8017DB08       .text dEnvSe_IsDelete__FP8dEnvSe_c */
static BOOL dEnvSe_IsDelete(dEnvSe_c* i_this) {
    return TRUE;
}

/* 8017DB08-8017DB38       .text dEnvSe_Delete__FP8dEnvSe_c */
static BOOL dEnvSe_Delete(dEnvSe_c* i_this) {
    mDoAud_seDeleteObject(&i_this->mPos);
    return TRUE;
}

/* 8017DB38-8017DB40       .text dEnvSe_Create__FP12kankyo_class */
static cPhs_State dEnvSe_Create(kankyo_class*) {
    return cPhs_COMPLEATE_e;
}

kankyo_method_class l_dEnvSe_Method = {
    (process_method_func)dEnvSe_Create,
    (process_method_func)dEnvSe_Delete,
    (process_method_func)dEnvSe_Execute,
    (process_method_func)dEnvSe_IsDelete,
    (process_method_func)dEnvSe_Draw,
};

kankyo_process_profile_definition g_profile_ENVSE = {
    fpcLy_CURRENT_e,
    2,
    fpcPi_CURRENT_e,
    PROC_ENVSE,
    &g_fpcLf_Method.base,
    sizeof(dEnvSe_c),
    0,
    0,
    &g_fopKy_Method,
    0xA9,
    &l_dEnvSe_Method,
};
