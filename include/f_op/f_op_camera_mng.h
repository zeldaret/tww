#ifndef F_F_OP_CAMERA_MNG_H_
#define F_F_OP_CAMERA_MNG_H_

#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "f_op/f_op_camera.h"

/* void fopCamM_SetNear(camera_class* cam, f32 near) {
    cam->mNear = near;
}

void fopCamM_SetFar(camera_class* cam, f32 far) {
    cam->mFar = far;
}

void fopCamM_SetFovy(camera_class* cam, f32 fovy) {
    cam->mFovy = fovy;
}

void fopCamM_SetAspect(camera_class* cam, f32 aspect) {
    cam->mAspect = aspect;
}

void fopCamM_SetEye(camera_class* cam, f32 x, f32 y, f32 z) {
    cam->field_0xd8.mEye.set(x, y, z);
}

void fopCamM_SetCenter(camera_class* cam, f32 x, f32 y, f32 z) {
    cam->field_0xd8.mCenter.set(x, y, z);
}

void fopCamM_SetBank(camera_class* cam, s16 bank) {
    cam->mBank = bank;
} */

inline s16 fopCamM_GetAngleY(camera_class* i_camera) {
    return i_camera->mAngle.y;
}

inline f32 fopCamM_GetFovy(camera_class* i_camera) {
    return i_camera->mFovy;
}

fpc_ProcID fopCamM_Create(int i_cameraIdx, s16 pProcName, void* param_3);
void fopCamM_Management(void);
u32 fopCamM_GetParam(camera_class* pCamera);
void fopCamM_Init(void);

#endif
