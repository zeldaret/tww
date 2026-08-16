#ifndef D_MENU_BASE_H
#define D_MENU_BASE_H

#include "d/d_drawlist.h"

class dMenu_base_c : public dDlst_base_c {
public:
    virtual ~dMenu_base_c() {}
    virtual void _create() {}
    virtual void _delete() {}
    virtual void _move() {}
    virtual void _draw() {}
    virtual bool _open() = 0;
    virtual bool _close() = 0;
    virtual void draw() {}
};

#endif //D_MENU_BASE_H
