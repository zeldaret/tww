#ifndef J3DMATERIALATTACH_H
#define J3DMATERIALATTACH_H

#include "dolphin/types.h"

class J3DMaterial;
class J3DTexture;
class J3DAnmColor;
class J3DAnmTexPattern;
class J3DAnmTextureSRTKey;
class J3DAnmTevRegKey;
class J3DMatColorAnm;
class J3DTexNoAnm;
class J3DTexMtxAnm;
class J3DTevColorAnm;
class J3DTevKColorAnm;
class JUTNameTab;

class J3DMaterialTable {
public:
    void clear();
    J3DMaterialTable();
    int removeMatColorAnimator(J3DAnmColor*);
    int removeTexNoAnimator(J3DAnmTexPattern*);
    int removeTexMtxAnimator(J3DAnmTextureSRTKey*);
    int removeTevRegAnimator(J3DAnmTevRegKey*);
    void createTexMtxForAnimator(J3DAnmTextureSRTKey*);
    void entryMatColorAnimator(J3DAnmColor*);
    void entryTexNoAnimator(J3DAnmTexPattern*);
    void entryTexMtxAnimator(J3DAnmTextureSRTKey*);
    void entryTevRegAnimator(J3DAnmTevRegKey*);
    void setMatColorAnimator(J3DAnmColor*, J3DMatColorAnm *);
    void setTexNoAnimator(J3DAnmTexPattern*, J3DTexNoAnm*);
    void setTexMtxAnimator(J3DAnmTextureSRTKey*, J3DTexMtxAnm*, J3DTexMtxAnm*);
    void setTevRegAnimator(J3DAnmTevRegKey*, J3DTevColorAnm*, J3DTevKColorAnm*);

    virtual ~J3DMaterialTable();

    J3DMaterial* getMaterialNodePointer(u16 idx) const { return mMaterialNodePointer[idx]; }

    J3DTexture* getTexture() const { return mTexture; }
    JUTNameTab* getTextureName() const { return mTextureName; }

    JUTNameTab* getMaterialName() const { return mMaterialName; }

    u16 getMaterialNum() const { return mMaterialNum; }

private:
    /* 0x04 */ u16 mMaterialNum;
    /* 0x06 */ u16 mUniqueMatNum;
    /* 0x08 */ J3DMaterial** mMaterialNodePointer;
    /* 0x0C */ JUTNameTab* mMaterialName;
    /* 0x10 */ u32 field_0x10;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ J3DTexture* mTexture;
    /* 0x1C */ JUTNameTab* mTextureName;
};  // Size: 0x20

#endif /* J3DMATERIALATTACH_H */
