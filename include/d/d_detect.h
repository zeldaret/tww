#ifndef D_D_DETECT_H
#define D_D_DETECT_H

#include "SSystem/SComponent/c_xyz.h"

class dDetectPlace_c {
public:
    dDetectPlace_c();
    ~dDetectPlace_c();
    bool chk_enable() const;

    /* 0x00 */ cXyz mPos;
    /* 0x0C */ s16 mTimer;
};

class dDetect_c {
public:
    struct Attr_c {
        /* 0x00 */ f32 maxDistXZ;
        /* 0x04 */ f32 maxY;
        /* 0x08 */ f32 minY;
    };

    dDetect_c();
    ~dDetect_c();

    void proc();
    bool chk_quake(const cXyz*) const;
    void set_quake(const cXyz*);
    bool chk_quake_area(const cXyz*) const;
    static void* search_tag_light(void*, void*);
    bool chk_light(const cXyz*) const;
    bool chk_attention(cXyz*) const;

    inline const Attr_c& attr() const { return M_attr; }

    static const Attr_c M_attr;

    /* 0x00 */ dDetectPlace_c mPlace[1];
    /* 0x10 */ s16 mTimer;
};  // Size: 0x14

#endif /* D_D_DETECT_H */
