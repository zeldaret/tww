#ifndef J2DSCREEN_H
#define J2DSCREEN_H

#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JUtility/TColor.h"
#include "dolphin/gx/GX.h"

class JKRArchive;

class J2DScreen : public J2DPane {
public:
    J2DScreen(J2DPane* parent, bool visible, u32 tag, const JGeometry::TBox2<f32>& bounds)
        : J2DPane(parent, visible, tag, bounds)
        , mColor()
    {
        mbClipToParent = false;
    }

    J2DScreen()
        : J2DPane(NULL, true, 'root', JGeometry::TBox2<f32>(0.0f, 0.0f, 640.0f, 480.0f))
        , mColor()
    {
        mbClipToParent = false;
    }

    virtual ~J2DScreen();
    virtual u16 getTypeID() { return 0x08; }
    virtual void calcMtx() { makeMatrix(mBounds.i.x, mBounds.i.y); }
    virtual void drawSelf(f32 x, f32 y, Mtx* mtx);
    virtual J2DPane* search(u32 tag);
    virtual J2DPane* createPane(J2DPane::J2DScrnBlockHeader const & header, JSURandomInputStream * pStream, J2DPane * pParent);

    void draw(f32 x, f32 y, const J2DGrafContext * pCtx);
    bool set(const char *pName, JKRArchive * pArc);
    bool set(JSURandomInputStream * pStream);

    void setScissor(bool v) { mbClipToParent = v; }

protected:
    s32 makeHierarchyPanes(J2DPane * pParent, JSURandomInputStream * pStream);
    bool checkSignature(JSURandomInputStream * pStream);
    bool getScreenInformation(JSURandomInputStream * pStream);

private:
    /* 0xCC */ bool mbClipToParent;
    /* 0xCD */ u8 pad_0xcd[3];
    /* 0xD0 */ JUtility::TColor mColor;
};

STATIC_ASSERT(sizeof(J2DScreen) == 0xD4);

#endif /* J2DSCREEN_H */
