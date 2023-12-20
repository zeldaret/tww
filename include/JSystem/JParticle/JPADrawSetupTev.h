#ifndef JPADRAWSETUPTEV_H
#define JPADRAWSETUPTEV_H

#include "dolphin/types.h"

class JPABaseShape;
class JPAExTexShape;

class JPADrawSetupTev {
public:
    void setupTev(JPABaseShape* param_1, JPAExTexShape* param_2);

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
};

#endif /* JPADRAWSETUPTEV_H */
