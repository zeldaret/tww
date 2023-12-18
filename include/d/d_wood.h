#ifndef D_WOOD_H
#define D_WOOD_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"

class dCcMassS_HitInf;
class cCcD_Obj;
class fopAc_ac_c;

namespace dWood {
enum AnmID_e {};
class Anm_c;
class Packet_c;
class Unit_c {
public:
    Unit_c();
    ~Unit_c();

    void set_ground();
    void set_mtx(Anm_c*);
    void clear();
    void cc_hit_before_cut(Packet_c*);
    void cc_hit_after_cut(Packet_c*);
    void proc(Packet_c*);

    /* 0x000 */ cXyz mPos;
    /* 0x00C */ u8 field_0x00C[0x010 - 0x00C];
    /* 0x010 */ u32 mFlags;
    /* 0x014 */ int mAnmIdx;
    /* 0x018 */ Mtx field_0x018;
    /* 0x048 */ Mtx field_0x048;
    /* 0x078 */ Mtx field_0x078;
    /* 0x0A8 */ Mtx field_0x0a8;
    /* 0x0D8 */ Unit_c* mpNext;
    /* 0x0DC */ u8 field_0xdc[0x18C - 0xDC];
};

STATIC_ASSERT(sizeof(Unit_c) == 0x18C);

class Anm_c {
public:
    enum Mode_e {};

    Anm_c();
    void play(Packet_c*);
    void copy_angamp(const Anm_c*);
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

    /* 0x00 */ u8 field_0x00[0x60 - 0x00];
    /* 0x60 */ int field_0x60;
    /* 0x64 */ s16 field_0x64;
    /* 0x66 */ u8 field_0x66[0x8A - 0x66];
    /* 0x8A */ u8 field_0x8a;
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

    void delete_room(int);
    void put_unit(const cXyz&, int);
    void calc_cc();
    void calc();
    void update();
    void search_empty_UnitID() const;
    void search_anm(Anm_c::Mode_e);

    virtual void draw();
    virtual ~Packet_c();

    /* 0x00010 */ Unit_c mUnit[200];
    /* 0x13570 */ Anm_c mAnm[72];
    /* 0x15CD0 */ Room_c mRoom[64];
};

STATIC_ASSERT(sizeof(Packet_c) == 0x15DD0);
};  // namespace dWood

#endif /* D_WOOD_H */
