#ifndef C_RND_H
#define C_RND_H

#include "dolphin/types.h"

struct cM_rnd_c {
    /* 0x0 */ int m0;
    /* 0x4 */ int m4;
    /* 0x8 */ int m8;

    void init(int a, int b, int c) {
        m0 = a;
        m4 = b;
        m8 = c;
    }
    int get();
    f32 getF(f32);
    f32 getFX(f32);
    f32 getValue(f32, f32);
};

#endif /* C_RND_H */
