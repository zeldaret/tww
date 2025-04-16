#ifndef D_S_ROOM_H
#define D_S_ROOM_H

#include "f_op/f_op_scene.h"

class dStage_roomDt_c;
class mDoDvdThd_toMainRam_c;

class room_of_scene_class : public scene_class {
public:
    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ void * mpRoomData;
    /* 0x1D0 */ dStage_roomDt_c * mpRoomDt;
    /* 0x1D4 */ mDoDvdThd_toMainRam_c * sceneCommand;
    /* 0x1D8 */ bool mbHasRoomParticle;
    /* 0x1D9 */ bool mbReLoaded;
    /* 0x1DA */ bool mbSetMap;
    /* 0x1DB */ bool field_0x1db;
    /* 0x1DC */ u16 field_0x1dc;
};

#endif /* D_S_ROOM_H */
