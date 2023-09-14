#ifndef J2DPANE_H
#define J2DPANE_H

#include "JSystem/JGeometry.h"
#include "JSystem/JSupport/JSUList.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx/mtx.h"

class J2DAnmBase;
class J2DAnmColor;
class J2DAnmTransform;
class J2DAnmTevRegKey;
class J2DAnmTextureSRTKey;
class J2DAnmVisibilityFull;
class J2DAnmVtxColor;
class J2DGrafContext;
class J2DScreen;
class J2DAnmTexPattern;
class JKRArchive;
class JSURandomInputStream;
struct ResFONT;
struct ResTIMG;

enum J2DRotateAxis {
    /* 0x78 */ ROTATE_X = 'x',
    /* 0x79 */ ROTATE_Y = 'y',
    /* 0x7A */ ROTATE_Z = 'z'
};

enum J2DBasePosition {
    J2DBasePosition_0,
    J2DBasePosition_1,
    J2DBasePosition_2,
    J2DBasePosition_3,
    J2DBasePosition_4,
};

struct J2DPaneHeader {
    /* 0x0 */ u32 mMagic;
    /* 0x4 */ u32 mSize;
};

class J2DPane {
public:
    J2DPane();
    J2DPane(J2DPane*, bool, u32, const JGeometry::TBox2<f32>&);
    J2DPane(u32, const JGeometry::TBox2<f32>&);
    J2DPane(J2DPane* other, JSURandomInputStream* stream, u8 arg3);
    J2DPane(J2DPane*, JSURandomInputStream*);
    void initiate();
    void initialize(J2DPane*, bool, u64, const JGeometry::TBox2<f32>&);
    void initialize(u64 tag, const JGeometry::TBox2<f32>& dim);
    void makePaneStream(J2DPane* other, JSURandomInputStream* stream);
    void changeUseTrans(J2DPane* other);
    bool appendChild(J2DPane* child);
    bool insertChild(J2DPane* before, J2DPane* child);
    void draw(f32 a1, f32 a2, const J2DGrafContext* ctx, bool a4);
    void place(const JGeometry::TBox2<f32>& dim);
    JGeometry::TBox2<f32>& getBounds();
    void rotate(f32 offsetX, f32 offsetY, J2DRotateAxis axis, f32 angle);
    void rotate(f32 angle);
    void clip(const JGeometry::TBox2<f32>& bounds);
    void setBasePosition(J2DBasePosition position);
    void setInfluencedAlpha(bool arg1, bool arg2);
    JGeometry::TVec3<f32> getGlbVtx(u8 arg1) const;
    J2DPane* getFirstChildPane();
    J2DPane* getNextChildPane();
    J2DPane* getParentPane();
    void makePaneExStream(J2DPane* other, JSURandomInputStream* stream);
    void* getPointer(JSURandomInputStream* stream, u32 size, JKRArchive* archive);
    void animationTransform();
    void updateTransform(const J2DAnmTransform* transform);

    virtual ~J2DPane();
    virtual void move(f32 x, f32 y);
    virtual void add(f32 x, f32 y);
    virtual void resize(f32 x, f32 y);
    virtual bool setConnectParent(bool connected);
    virtual void update();
    virtual void calcMtx();
    virtual void drawSelf(f32 arg1, f32 arg2);
    virtual void drawSelf(f32 arg1, f32 arg2, Mtx* mtx){};
    virtual void makeMatrix(f32, f32);
    virtual J2DPane* search(u32 tag);
    virtual u16 getTypeID() { return 16; }

    JSUTree<J2DPane>* getFirstChild() { return mPaneTree.getFirstChild(); }
    JSUTree<J2DPane>* getEndChild() { return mPaneTree.getEndChild(); }
    const JSUTree<J2DPane>* getPaneTree() { return &mPaneTree; }
    u8 getAlpha() const { return mAlpha; }

public:
    /* 0x04 */ u32 mMagic;
    /* 0x08 */ int mTag;
    /* 0x0C */ JGeometry::TBox2<f32> mBounds;
    /* 0x1C */ JGeometry::TBox2<f32> mScreenPos;
    /* 0x2C */ JGeometry::TBox2<f32> mBox;
    /* 0x3C */ Mtx mMtx;
    /* 0x6C */ Mtx mDrawMtx;
    /* 0x9C */ cXy mBasePosition;
    /* 0xA4 */ f32 mRotation;
    /* 0xA8 */ u8 mRotationAxis;
    /* 0xA9 */ u8 m2DBasePosition;
    /* 0xAA */ bool mVisible;
    /* 0xAB */ u8 mCullMode;
    /* 0xAC */ u8 mAlpha;
    /* 0xAD */ u8 mDrawAlpha;
    /* 0xAE */ u8 field_0xae;
    /* 0xAF */ u8 field_0xaf;
    /* 0xB0 */ JSUTree<J2DPane> mPaneTree;
};

#endif /* J2DPANE_H */
