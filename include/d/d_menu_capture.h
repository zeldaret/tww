#ifndef D_MENU_CAPTURE_H
#define D_MENU_CAPTURE_H

#include "d/d_drawlist.h"
#include "d/d_menu_cloth.h"

extern dMCloth_c* cloth_c;

class dDlst_MENU_CLOTH_c : public dDlst_base_c {
public:
    virtual ~dDlst_MENU_CLOTH_c();

    virtual void draw();
};

class dDlst_MENU_CAPTURE_c : public dDlst_base_c {
public:
    dDlst_MENU_CAPTURE_c() { setDrawFlagOff(); }
    virtual ~dDlst_MENU_CAPTURE_c();

    virtual void draw();

    u8 checkDrawFlag() { return mStatus; }
    void setDrawFlagOff() { mStatus = 0; }
    void setDrawFlagOn() { mStatus = 1; }
    void setDrawFlagOn2() { mStatus = 2; }

public:
    /* 0x04 */ u8 mStatus;
};

#endif //D_MENU_CAPTURE_H
