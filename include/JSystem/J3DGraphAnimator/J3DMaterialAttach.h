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
    s32 entryMatColorAnimator(J3DAnmColor*);
    s32 entryTexNoAnimator(J3DAnmTexPattern*);
    s32 entryTexMtxAnimator(J3DAnmTextureSRTKey*);
    s32 entryTevRegAnimator(J3DAnmTevRegKey*);
    int removeMatColorAnimator(J3DAnmColor*);
    int removeTexNoAnimator(J3DAnmTexPattern*);
    int removeTexMtxAnimator(J3DAnmTextureSRTKey*);
    int removeTevRegAnimator(J3DAnmTevRegKey*);
    s32 setMatColorAnimator(J3DAnmColor*, J3DMatColorAnm *);
    s32 setTexNoAnimator(J3DAnmTexPattern*, J3DTexNoAnm*);
    s32 setTexMtxAnimator(J3DAnmTextureSRTKey*, J3DTexMtxAnm*, J3DTexMtxAnm*);
    s32 setTevRegAnimator(J3DAnmTevRegKey*, J3DTevColorAnm*, J3DTevKColorAnm*);

    virtual ~J3DMaterialTable();

    J3DMaterial* getMaterialNodePointer(u16 idx) const { return mMaterialNodePointer[idx]; }

    J3DTexture* getTexture() const { return mTexture; }
    JUTNameTab* getTextureName() const { return mTextureName; }
    void setTexture(J3DTexture* pTexture) { mTexture = pTexture; }
    void setTextureName(JUTNameTab* pTextureName) { mTextureName = pTextureName; }

    JUTNameTab* getMaterialName() const { return mMaterialName; }

    u16 getMaterialNum() const { return mMaterialNum; }
    bool isLocked() { return field_0x20 == 1; }

private:
    friend class J3DJointTree;
    friend class J3DModelLoader;
    friend class J3DModelLoader_v26;
    friend class J3DModelLoader_v21;

    /* 0x04 */ u16 mMaterialNum;
    /* 0x08 */ J3DMaterial** mMaterialNodePointer;
    /* 0x0C */ JUTNameTab* mMaterialName;
    /* 0x10 */ u16 mUniqueMatNum;
    /* 0x14 */ J3DMaterial* field_0x14;
    /* 0x18 */ J3DTexture* mTexture;
    /* 0x1C */ JUTNameTab* mTextureName;
    /* 0x20 */ u16 field_0x20;
};  // Size: 0x24

#endif /* J3DMATERIALATTACH_H */
