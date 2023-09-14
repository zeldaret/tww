#ifndef D_PARTICLE
#define D_PARTICLE

#include "JSystem/JParticle/JPAParticle.h"

class mDoDvdThd_toMainRam_c;
class dPa_levelEcallBack;
class dKy_tevstr_c;
class cBgS_PolyInfo;
class JPADrawInfo;
class JKRHeap;
class JPABaseEmitter;
class JPAEmitterManager;
struct csXyz;

class dPa_simpleData_c {
public:
    ~dPa_simpleData_c();
    dPa_simpleData_c();

    /* 0x00 */ Vec mPos;
    /* 0x0C */ GXColor mPrmColor;
    /* 0x10 */ u8 mEnvColor[3];
    /* 0x13 */ u8 mbAffectedByWind;
};

class dPa_simpleEcallBack {
public:
    dPa_simpleEcallBack();
    ~dPa_simpleEcallBack();

    void executeAfter(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    void create(JPAEmitterManager*, u16, u8);
    void createEmitter(JPAEmitterManager*);
    void set(cXyz const*, u8, GXColor const&, GXColor const&, int);

    /* 0x000 */ void* vtbl;
    /* 0x004 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x008 */ u16 mResID;
    /* 0x00A */ u8 mGrpID;
    /* 0x00B */ u8 mbIsSmoke;
    /* 0x00C */ s16 mCount;
    /* 0x00E */ u8 field_0x00E[0x010 - 0x00E];
    /* 0x010 */ dPa_simpleData_c mSimpleData[32];
};

class dPa_modelControl_c {
public:
    dPa_modelControl_c(J3DModelData*);
    ~dPa_modelControl_c();

    void newModel(J3DModelData*);
    void draw();

    /* 0x00 */ node_list_class parent;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* field_0x14;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ void* field_0x1c;
    /* 0x20 */ void* field_0x20;
    /* 0x24 */ void* field_0x24;
    /* 0x28 */ void* field_0x28;
    /* 0x2C */ void* field_0x2c;
    /* 0x30 */ void* field_0x30;
    /* 0x34 */ void* field_0x34;
    /* 0x38 */ void* field_0x38;
    /* 0x3C */ void* field_0x3c;
    /* 0x40 */ void* field_0x40;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ void* field_0x48;
    /* 0x4C */ void* field_0x4c;
    /* 0x50 */ void* field_0x50;
    /* 0x54 */ void* field_0x54;
    /* 0x58 */ void* field_0x58;
    /* 0x5C */ void* field_0x5c;
    /* 0x60 */ void* field_0x60;
    /* 0x64 */ void* field_0x64;
    /* 0x68 */ void* field_0x68;
    /* 0x6C */ void* field_0x6c;
    /* 0x70 */ void* field_0x70;
    /* 0x74 */ void* field_0x74;
    /* 0x78 */ void* field_0x78;
    /* 0x7C */ void* field_0x7c;
    /* 0x80 */ void* field_0x80;
    /* 0x84 */ J3DVertexData mVertexData;
};

class dPa_control_c {
public:
    dPa_control_c();

    void getRM_ID(u16);
    void swapFrameBufferTexture();
    void createCommon(void const*);
    void createRoomScene(void const*);
    void readScene(u8, mDoDvdThd_toMainRam_c**);
    void createScene(void const*);
    void removeRoomScene();
    void removeScene();
    void calc3D();
    void calc2D();
    void calcMenu();
    void draw(JPADrawInfo*, u8);
    JPABaseEmitter* set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*,
                        s8, GXColor const*, GXColor const*, cXyz const*);
    void setBombSmoke(u16, cXyz const*, csXyz const*, cXyz const*, u8);
    void setSimpleLand(int, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
    void setSimpleLand(cBgS_PolyInfo&, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*,
                       int*, int);
    void checkAtrCodeEffect(int);
    void setNormalStripes(u16, cXyz const*, csXyz const*, cXyz const*, u8, u16);
    void newSimple(u16, u8);
    void setSimple(u16, cXyz const*, u8, GXColor const&, GXColor const&, int);
    void getSimple(u16);

    void drawModelParticle() { mModelCtrl->draw(); }

    /* 0x0000 */ JKRHeap* mpHeap;
    /* 0x0004 */ JPAResourceManager* mpCommonResMgr;
    /* 0x0008 */ dPa_modelControl_c* mModelCtrl;
    /* 0x000C */ JKRHeap* mpSceneHeap;
    /* 0x0010 */ void* mpData;
    /* 0x0014 */ JPAResourceManager* mpSceneResMgr;
    /* 0x0018 */ u8 mSceneNo;
    /* 0x0019 */ u8 mCount;
    /* 0x001A */ u8 mNumSimple;
    /* 0x001B */ u8 mNumSimpleCommon;
    /* 0x001C */ dPa_simpleEcallBack mSimpleCallbacks[25];
};

#endif /* D_PARTICLE */