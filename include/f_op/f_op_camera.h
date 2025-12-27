#ifndef F_F_OP_CAMERA_H_
#define F_F_OP_CAMERA_H_

#include "d/d_camera.h"
#include "f_op/f_op_view.h"

typedef struct leafdraw_method_class leafdraw_method_class;

class camera_process_class : public view_class {
public:
    /* 0x210 */ create_tag_class draw_tag;
    /* 0x224 */ leafdraw_method_class* mpMtd;
    /* 0x228 */ u8 field_0x228[4];
    /* 0x22C */ s8 mPrm1;
    /* 0x22D */ s8 mPrm2;
    /* 0x22E */ s8 mPrm3;
    /* 0x22F */ s8 field_0x22f;
    /* 0x230 */ csXyz mAngle;
    /* 0x238 */ int field_0x238;
}; // size = 0x23C
STATIC_ASSERT(sizeof(camera_process_class) == 0x23C);

class camera_class : public camera_process_class {
public:
    /* 0x23C */ request_of_phase_process_class phase_request;
    /* 0x244 */ dCamera_c mCamera;
}; // size = 0xA44
STATIC_ASSERT(sizeof(camera_class) == 0xA44);

struct camera_process_profile_definition {
    /* 0x00 */ view_process_profile_definition base;
    /* 0x3C */ leafdraw_method_class* sub_method; // Subclass methods
};

extern leafdraw_method_class g_fopCam_Method;

#endif
