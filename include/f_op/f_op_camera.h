#ifndef F_F_OP_CAMERA_H_
#define F_F_OP_CAMERA_H_

#include "d/d_cam_param.h"
#include "d/d_camera.h"
#include "f_op/f_op_view.h"
#include "global.h"

typedef struct leafdraw_method_class leafdraw_method_class;

class camera_process_class : public view_class {
public:
    /* 0x210 */ create_tag_class mDwTg;
    /* 0x224 */ leafdraw_method_class* mpMtd;
    /* 0x228 */ u8 field_0x228[4];
    /* 0x22C */ s8 mPrm1;
    /* 0x22D */ s8 mPrm2;
    /* 0x22E */ s8 mPrm3;
    /* 0x22F */ s8 field_0x22f;
    /* 0x230 */ csXyz mAngle;
    /* 0x238 */ int field_0x238;
};

class camera_class : public camera_process_class {
public:
    /* 0x23C */ int field_0x23c;
    /* 0x240 */ int field_0x244;
     /* 0x244 */ dCamera_c mCamera;
};

struct camera_process_profile_definition {
    /* 0x00 */ view_process_profile_definition mBase;
    /* 0x3C */ leafdraw_method_class* mSubMtd; // Subclass methods
};

#endif
