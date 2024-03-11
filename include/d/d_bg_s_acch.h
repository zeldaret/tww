#ifndef D_BG_D_BG_S_ACCH_H
#define D_BG_D_BG_S_ACCH_H

#include "SSystem/SComponent/c_m3d_g_cir.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "SSystem/SComponent/c_m3d_g_pla.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_roof_chk.h"
#include "d/d_bg_s_wtr_chk.h"
#include "SSystem/SComponent/c_sxyz.h"

class fopAc_ac_c;

class dBgS_AcchCir : public cBgS_PolyInfo {
private:
    /* 0x10 */ u32 m_flags;
    /* 0x14 */ cM3dGCir m_cir;
    /* 0x28 */ f32 m_wall_rr;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 m_wall_h;
    /* 0x34 */ f32 m_wall_r;
    /* 0x38 */ f32 m_wall_h_direct;
    /* 0x3C */ s16 m_wall_angle_y;

public:
    enum {
        /* 0x2 */ WALL_HIT = 2,
        /* 0x4 */ WALL_H_DIRECT = 4,
    };

    dBgS_AcchCir();
    void SetWallR(f32);
    void CalcWallRR() { m_wall_rr = m_wall_r*m_wall_r; }
    void SetWall(f32 i_halfHeight, f32 i_radius);

    virtual ~dBgS_AcchCir() {}

    f32 GetWallH() { return m_wall_h; }
    f32 GetWallR() { return m_wall_r; }
    s16 GetWallAngleY() { return m_wall_angle_y; }
    void SetWallH(f32 h) { m_wall_h = h; }
    void SetWallHDirect(f32 h) { m_flags |= WALL_H_DIRECT; m_wall_h_direct = h; }
    void ClrWallHDirect() { m_flags &= ~WALL_H_DIRECT; }
    bool ChkWallHit() { return m_flags & WALL_HIT; }
    void ClrWallHit() {
        m_flags &= ~WALL_HIT;
        ClearPi();
    }

    void SetCir(cXyz& pos) { m_cir.Set(pos.x, pos.z, pos.y + GetWallH(), m_wall_r); }
};  // Size: 0x40

class dBgS;
class dBgS_Acch : public cBgS_Chk, public dBgS_Chk {
public:
    enum {
        /* 0x000002 */ GRND_NONE = (1 << 1),
        /* 0x000004 */ WALL_NONE = (1 << 2),
        /* 0x000008 */ ROOF_NONE = (1 << 3),
        /* 0x000010 */ WALL_HIT = (1 << 4),
        /* 0x000020 */ GROUND_HIT = (1 << 5),
        /* 0x000040 */ GROUND_FIND = (1 << 6),
        /* 0x000080 */ GROUND_LANDING = (1 << 7),
        /* 0x000100 */ GROUND_AWAY = (1 << 8),
        /* 0x000200 */ ROOF_HIT = (1 << 9),
        /* 0x000400 */ WATER_NONE = (1 << 10),
        /* 0x000800 */ WATER_HIT = (1 << 11),
        /* 0x001000 */ WATER_IN = (1 << 12),
        /* 0x002000 */ LINE_CHECK = (1 << 13),
        /* 0x004000 */ LINE_CHECK_NONE = (1 << 14),
        /* 0x008000 */ CLR_SPEED_Y = (1 << 15),
        /* 0x010000 */ LINE_CHECK_HIT = (1 << 16),
        /* 0x020000 */ SEA_CHECK = (1 << 17),
        /* 0x040000 */ SEA_WATER_HEIGHT = (1 << 18),
        /* 0x080000 */ SEA_IN = (1 << 19),
    };

    dBgS_Acch();
    void Init();
    void Set(fopAc_ac_c*, int, dBgS_AcchCir*);
    void Set(cXyz* pos, cXyz* old_pos, fopAc_ac_c* actor, int tbl_size, dBgS_AcchCir* acchCir,
             cXyz* speed = NULL, csXyz* angle = NULL, csXyz* shape_angle = NULL);
    void GroundCheckInit(dBgS&);
    void GroundCheck(dBgS&);
    f32 GroundRoofProc(dBgS&);
    void LineCheck(dBgS&);
    void CrrPos(dBgS&);
    f32 GetWallAllR();
    void SetWallCir();
    void CalcWallBmdCyl();
    void SetGroundUpY(f32);
    f32 GetWallAllLowH();
    f32 GetWallAllLowH_R();
    f32 GetSpeedY();
    f32 GetWallAddY(Vec&);
    void SetNowActorInfo(int bg_index, void* bgw, uint apid) {
        m_bg_index = bg_index;
        field_0x78 = bgw;
        field_0x7c = apid;
    }
    void SetWallPolyIndex(int, int);
    void CalcMovePosWork();
    void CalcWallRR() {
        for (s32 i = 0; i < m_tbl_size; i++)
            pm_acch_cir[i].CalcWallRR();
    }
    void SetGndThinCellingOff();
    void ClrGndThinCellingOff();
    bool ChkGndThinCellingOff();
    void OnWallSort();
    bool ChkWallSort();
    bool ChkLineDown();
    bool GetOnePolyInfo(cBgS_PolyInfo*);
    f32 GetWallAddY(Vec&, int);

    virtual ~dBgS_Acch();

    cXyz* GetPos() { return pm_pos; }
    cXyz* GetOldPos() { return pm_old_pos; }
    f32 GetGroundH() { return m_ground_h; }
    f32 GetRoofHeight() { return m_roof_crr_height; }
    f32 GetSeaHeight() { return m_sea_height; }
    void SetLin() { m_lin.SetStartEnd(*pm_old_pos, *pm_pos); }
    bool ChkGroundFind() { return m_flags & GROUND_FIND; }
    bool ChkGroundHit() { return m_flags & GROUND_HIT; }
    bool ChkGroundLanding() { return m_flags & GROUND_LANDING; }
    void ClrGroundLanding() { m_flags &= ~GROUND_LANDING; }
    void ClrGroundAway() { m_flags &= ~GROUND_AWAY; }
    void ClrWallHit() { m_flags &= ~WALL_HIT; }
    void SetWallNone() { m_flags |= WALL_NONE; }
    void SetRoofNone() { m_flags |= ROOF_NONE; }
    void SetRoofHit() { m_flags |= ROOF_HIT; }
    void SetWaterNone() { m_flags |= WATER_NONE; }
    bool ChkWallHit() { return m_flags & WALL_HIT; }
    void OffLineCheckHit() { m_flags &= ~LINE_CHECK_HIT; }
    void OffLineCheck() { m_flags &= ~LINE_CHECK; }
    bool ChkLineCheckNone() { return m_flags & LINE_CHECK_NONE; }
    bool ChkLineCheck() { return m_flags & LINE_CHECK; }
    void ClrRoofHit() { m_flags &= ~ROOF_HIT; }
    void ClrWaterHit() { m_flags &= ~WATER_HIT; }
    void SetWaterHit() { m_flags |= WATER_HIT; }
    void ClrWaterIn() { m_flags &= ~WATER_IN; }
    void SetWaterIn() { m_flags |= WATER_IN; }
    const u32 MaskWaterIn() { return m_flags & WATER_IN; }
    const bool ChkWaterIn() { return MaskWaterIn();}
    void ClrGroundFind() { m_flags &= ~GROUND_FIND; }
    u32 MaskRoofHit() { return m_flags & ROOF_HIT; }
    bool ChkRoofHit() { return MaskRoofHit(); }
    bool ChkClrSpeedY() { return m_flags & CLR_SPEED_Y; }
    void SetGroundFind() { m_flags |= GROUND_FIND; }
    void SetGroundHit() { m_flags |= GROUND_HIT; }
    void ClrGroundHit() { m_flags &= ~GROUND_HIT; }
    void SetGroundLanding() { m_flags |= GROUND_LANDING; }
    void SetGroundAway() { m_flags |= GROUND_AWAY; }
    const u32 MaskWaterHit() { return m_flags & WATER_HIT; }
    const bool ChkWaterHit() { return MaskWaterHit(); }
    void ClrWaterNone() { m_flags &= ~WATER_NONE; }
    void SetWaterCheckOffset(f32 offset) { m_water_check_offset = offset; }
    void OnLineCheck() { m_flags |= LINE_CHECK; }
    void ClrRoofNone() { m_flags &= ~ROOF_NONE; }
    void SetRoofCrrHeight(f32 height) { m_roof_crr_height = height; }
    void SetGrndNone() { m_flags |= GRND_NONE; }
    void ClrGrndNone() { m_flags &= ~GRND_NONE; }
    void SetGroundCheckOffset(f32 offset) { m_ground_check_offset = offset; }
    void SetWallHit() { m_flags |= WALL_HIT; }
    void ClrWallNone() { m_flags &= ~WALL_NONE; }
    void OnSeaCheckOn() { m_flags |= SEA_CHECK; }
    bool ChkSeaCheckOn() { return m_flags & SEA_CHECK;}
    void OnSeaWaterHeight() { m_flags |= SEA_WATER_HEIGHT; }
    bool ChkSeaWaterHeight() { return m_flags & SEA_WATER_HEIGHT; }
    bool ChkSeaIn() { return m_flags & SEA_IN;}
    cM3dGCyl* GetWallBmdCylP() { return &m_wall_cyl; }

public:
    /* 0x028 */ u32 m_flags;
    /* 0x02C */ cXyz* pm_pos;
    /* 0x030 */ cXyz* pm_old_pos;
    /* 0x034 */ cXyz* pm_speed;
    /* 0x038 */ csXyz* pm_angle;
    /* 0x03C */ csXyz* pm_shape_angle;
    /* 0x040 */ cM3dGLin m_lin;
    /* 0x05C */ cM3dGCyl m_wall_cyl;
    /* 0x074 */ int m_bg_index;
    /* 0x078 */ void* field_0x78;
    /* 0x07C */ u32 field_0x7c;
    /* 0x080 */ fopAc_ac_c* m_my_ac;
    /* 0x084 */ int m_tbl_size;
    /* 0x088 */ dBgS_AcchCir* pm_acch_cir;
    /* 0x08C */ f32 m_ground_up_h;
    /* 0x090 */ f32 m_ground_up_h_diff;
    /* 0x094 */ f32 m_ground_h;
    /* 0x098 */ f32 m_ground_check_offset;
    /* 0x09C */ cM3dGPla m_pla;
    /* 0x0B0 */ u8 field_0xb0;
    /* 0x0B4 */ f32 field_0xb4;
    /* 0x0B8 */ f32 field_0xb8;
    /* 0x0BC */ f32 m_roof_y;
    /* 0x0C0 */ f32 m_roof_crr_height;
    /* 0x0C4 */ f32 m_roof_height;
    /* 0x0C8 */ f32 m_water_check_offset;
    /* 0x0CC */ cBgS_PolyInfo* pm_out_poly_info;
    /* 0x0D0 */ f32 m_sea_height;
    /* 0x0D4 */ dBgS_GndChk m_gnd;
    /* 0x128 */ dBgS_RoofChk m_roof;
    /* 0x174 */ dBgS_WtrChk m_wtr;
};  // Size: 0x1C4

STATIC_ASSERT(sizeof(dBgS_Acch) == 0x1C4);

class dBgS_LinkAcch : public dBgS_Acch {
public:
    dBgS_LinkAcch() { SetLink(); }

    virtual ~dBgS_LinkAcch() {}
};

class dBgS_ObjAcch : public dBgS_Acch {
public:
    dBgS_ObjAcch() {
        SetObj();
    }

    virtual ~dBgS_ObjAcch() {}
};  // Size: 0x1C4

#endif /* D_BG_D_BG_S_ACCH_H */
