#ifndef D_OVLP_FADE_H
#define D_OVLP_FADE_H

#include "f_op/f_op_overlap_mng.h"

class overlap1_class : public overlap_task_class {
public:
    /* 0xCC */ s32 mFadeOutTime;
    /* 0xD0 */ s32 mFadeInTime;
};

#endif /* D_OVLP_FADE_H */
