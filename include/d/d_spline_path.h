#ifndef D_SPLINE_PATH_H
#define D_SPLINE_PATH_H

#include "dolphin/types.h"

class cXyz;

class d2DBSplinePath {
public:
    void Last() {}

    void Init(s32, s32);
    void Step();
    void Calc(cXyz*);
    void Calc(f32*);
};

#endif /* D_SPLINE_PATH_H */
