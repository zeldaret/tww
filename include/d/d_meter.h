#ifndef D_METER_H
#define D_METER_H

#include "d/d_drawlist.h"

class J2DPane;
class fopAc_ac_c;
class fopMsgM_pane_class;
class msg_class;
class sub_meter_class;

class dMeter_HIO_c {
public:
    dMeter_HIO_c();
    virtual ~dMeter_HIO_c();
};

class dMeter_menuHIO_c {
public:
    dMeter_menuHIO_c();
    virtual ~dMeter_menuHIO_c();
};

class dMeter_msg_HIO_c {
public:
    dMeter_msg_HIO_c();
    virtual ~dMeter_msg_HIO_c();
};

class dMeter_message_HIO_c {
public:
    dMeter_message_HIO_c();
    virtual ~dMeter_message_HIO_c();
};

class dDlst_2DMETER1_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMETER1_c();
    virtual void draw();
};

class dDlst_2DMETER2_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMETER2_c();
    virtual void draw();
};

class dMeter_map_HIO_c {
public:
    dMeter_map_HIO_c();
    virtual ~dMeter_map_HIO_c();
};

class mapCtrlDisp_c {
public:
    void initMapCtrlDisp();
    void moveMapCtrlDisp();
};

class dMeter_info_c {
public:
    ~dMeter_info_c() {}
};

bool dMenu_flag();
void dMenu_flagSet(u8);

#endif /* D_METER_H */
