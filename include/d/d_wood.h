#ifndef D_WOOD_H
#define D_WOOD_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "d/d_kankyo.h"

class dCcMassS_HitInf;
class cCcD_Obj;
class fopAc_ac_c;

namespace dWood {

enum AnmID_e {
    AnmID_Norm0,
    AnmID_Norm1,
    AnmID_Norm2,
    AnmID_Norm3,
    AnmID_Norm4,
    AnmID_Norm5,
    AnmID_Norm6,
    AnmID_Norm7,

    AnmID_Norm_Max = 8,
    AnmID_Norm_Invalid = -1
};

class Anm_c;
class Packet_c;
class Unit_c {
public:
    Unit_c();

    enum State_e {
        STATE_ACTIVE = 1 << 0,
        STATE_FRUSTUM_CULLED = 1 << 1,
        STATE_CUT = 1 << 2,
    };

    bool set_ground();
    void set_mtx(Anm_c*);
    void clear();
    void cc_hit_before_cut(Packet_c*);
    void cc_hit_after_cut(Packet_c*);
    void proc(Packet_c*);

    /* 0x000 */ cXyz mPos;
    /* 0x00C */ s16 mAnimCooldown; // In frames. Animations will not change unless this is 0.
    /* 0x00E */ u8 field_0x00C[0x010 - 0x00E];
    /* 0x010 */ State_e mFlags;
    /* 0x014 */ AnmID_e mAnmIdx;
    /* 0x018 */ Mtx mModelViewMtx;
    /* 0x048 */ Mtx mTrunkModelViewMtx;
    /* 0x078 */ Mtx mShadowModelMtx;
    /* 0x0A8 */ Mtx mShadowModelViewMtx;
    /* 0x0D8 */ Unit_c* mpNext;

    /* 0x0DC */ dKy_tevstr_c mTevStr;
};

STATIC_ASSERT(sizeof(Unit_c) == 0x18C);
class Anm_c {
public:
    enum Mode_e {
        Mode_Cut = 0,      // Chopping down
        Mode_PushInto = 1, // Attacked or collided with, but not chopped
        Mode_PushBack = 2, // Second half of PushInto, returning to normal
        Mode_Fan = 3,      // When hit with fan (does nothing)
        Mode_Norm = 4,     // Idle animation
        Mode_ToNorm = 5,   // Transition to idle from any other animation

        Mode_Max
    };

    Anm_c();
    void play(Packet_c*);
    void copy_angamp(const Anm_c*);
    
    // Animations are assigned from the Packet to specific Wood instances (Bushes) when a new animation starts
    // Each animation mode has an mode_*_init() function which is called when the animation is started
    // The mode_*() function is called to update the animation each frame, until finished
    // Their are 8 pre-allocated "normal" animations. When not animating, each unit is assigned one of the 8.

    void mode_cut_init(const Anm_c*, short);
    void mode_cut(Packet_c*);
    void mode_push_into_init(const Anm_c*, short);
    void mode_push_into(Packet_c*);
    void mode_push_back_init();
    void mode_push_back(Packet_c*);
    void mode_fan(Packet_c*);
    void mode_norm_init();
    void mode_norm(Packet_c*);
    void mode_norm_set_wind(float, short);
    void mode_to_norm_init(AnmID_e);
    void mode_to_norm(Packet_c*);

    inline AnmID_e mode_to_norm_get_AnmID() { return (AnmID_e)mNormAnimIdx; }
    inline void mode_to_norm_set_AnmID(AnmID_e anmID)  { mNormAnimIdx = anmID; }

    Mode_e get_mode() { return mMode; }

    /* 0x00 */ Mtx mModelMtx;
    /* 0x30 */ Mtx mTrunkModelMtx;

    /* 0x60 */ Mode_e mMode;

    /* 0x64 */ s16 mCountdown;
    /* 0x66 */ s16 mWindDir;     // The direction from the wind or actor who instigated this animation
    /* 0x68 */ float mWindPow;   // 0.0 - 1.0
    /* 0x6c */ float mPosOffsetY;
    /* 0x70 */ float mPosOffsetZ;
    /* 0x74 */ float mVelY;

    /* 0x78 */ s16 mPhaseY[2];
    /* 0x7c */ s16 mPhaseX[2];
    /* 0x80 */ s16 mAmpY[2];
    /* 0x84 */ s16 mAmpX[2];
    
    /* 0x88 */ s16 mNormAnimIdx;

    /* 0x8A */ u8 mAlphaScale;

    static s32 M_init_num;
};

STATIC_ASSERT(sizeof(Anm_c) == 0x8C);

class Room_c {
public:
    Room_c();
    void entry_unit(Unit_c*);
    void delete_all_unit();

    /* 0x0 */ Unit_c* mpUnit;
};

class Packet_c : public J3DPacket {
public:
    Packet_c();

    void delete_room(int room_no);
    s32 put_unit(const cXyz& pos, int room_no);
    void calc_cc();
    void calc();
    void update();
    s32 search_empty_UnitID() const;
    AnmID_e search_anm(Anm_c::Mode_e mode);

    inline Anm_c* get_anm_p(AnmID_e idx) { return &mAnm[idx]; }

    virtual void draw();
    virtual ~Packet_c() {};

    /* 0x00010 */ Unit_c mUnit[200];
    /* 0x13570 */ Anm_c mAnm[72];
    /* 0x15CD0 */ Room_c mRoom[64];
};

STATIC_ASSERT(sizeof(Packet_c) == 0x15DD0);
};  // namespace dWood

#endif /* D_WOOD_H */
