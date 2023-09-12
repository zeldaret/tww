#ifndef D_PARTICLE
#define D_PARTICLE

#include "JSystem/JParticle/JPAParticle.h"

class mDoDvdThd_toMainRam_c;
class dPa_levelEcallBack;
class dKy_tevstr_c;
class cBgS_PolyInfo;
class JPADrawInfo;
class dPa_modelControl_c;
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
	JPABaseEmitter * set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*, s8, GXColor const*, GXColor const*, cXyz const*);
	void setBombSmoke(u16, cXyz const*, csXyz const*, cXyz const*, u8);
	void setSimpleLand(int, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
	void setSimpleLand(cBgS_PolyInfo&, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
	void checkAtrCodeEffect(int);
	void setNormalStripes(u16, cXyz const*, csXyz const*, cXyz const*, u8, u16);
	void newSimple(u16, u8);
	void setSimple(u16, cXyz const*, u8, GXColor const&, GXColor const&, int);
	void getSimple(u16);

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