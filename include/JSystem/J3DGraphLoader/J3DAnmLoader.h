#ifndef J3DANMLOADER_H
#define J3DANMLOADER_H

#include "dolphin/types.h"

enum J3DAnmLoaderDataBaseFlag { J3DLOADER_UNK_FLAG0 };

class J3DAnmBase;
class J3DAnmClusterFull;
struct J3DAnmClusterFullData;
class J3DAnmClusterKey;
struct J3DAnmClusterKeyData;
class J3DAnmColorFull;
struct J3DAnmColorFullData;
class J3DAnmColorKey;
struct J3DAnmColorKeyData;
class J3DAnmTevRegKey;
struct J3DAnmTevRegKeyData;
class J3DAnmTexPattern;
struct J3DAnmTexPatternFullData;
class J3DAnmTextureSRTKey;
struct J3DAnmTextureSRTKeyData;
class J3DAnmTransformFull;
struct J3DAnmTransformFullData;
class J3DAnmTransformKey;
struct J3DAnmTransformKeyData;
class J3DAnmVisibilityFull;
struct J3DAnmVisibilityFullData;
class J3DAnmVtxColorFull;
struct J3DAnmVtxColorFullData;
class J3DAnmVtxColorKey;
struct J3DAnmVtxColorKeyData;

struct J3DAnmLoaderDataBase {
    static J3DAnmBase* load(const void*);
    static void setResource(J3DAnmBase*, const void*);
};

class J3DAnmLoader {
public:
    virtual J3DAnmBase* load(const void*) = 0;
    virtual void setResource(J3DAnmBase*, const void*) = 0;
    virtual ~J3DAnmLoader() {}
};

class J3DAnmFullLoader_v15 : public J3DAnmLoader {
public:
    J3DAnmFullLoader_v15();
    ~J3DAnmFullLoader_v15();
    J3DAnmBase* load(const void*);
    void setResource(J3DAnmBase*, const void*);
    void readAnmTransform(const J3DAnmTransformFullData*);
    void setAnmTransform(J3DAnmTransformFull*, const J3DAnmTransformFullData*);
    void readAnmColor(const J3DAnmColorFullData*);
    void setAnmColor(J3DAnmColorFull*, const J3DAnmColorFullData*);
    void readAnmTexPattern(const J3DAnmTexPatternFullData*);
    void setAnmTexPattern(J3DAnmTexPattern*, const J3DAnmTexPatternFullData*);
    void readAnmVisibility(const J3DAnmVisibilityFullData*);
    void setAnmVisibility(J3DAnmVisibilityFull*, const J3DAnmVisibilityFullData*);
    void readAnmCluster(const J3DAnmClusterFullData*);
    void setAnmCluster(J3DAnmClusterFull*, const J3DAnmClusterFullData*);
    void readAnmVtxColor(const J3DAnmVtxColorFullData*);
    void setAnmVtxColor(J3DAnmVtxColorFull*, const J3DAnmVtxColorFullData*);

    J3DAnmBase* mAnm;
};

class J3DAnmKeyLoader_v15 : public J3DAnmLoader {
public:
    J3DAnmKeyLoader_v15();
    ~J3DAnmKeyLoader_v15();
    J3DAnmBase* load(const void*);
    void setResource(J3DAnmBase*, const void*);
    void readAnmTransform(const J3DAnmTransformKeyData*);
    void setAnmTransform(J3DAnmTransformKey*, const J3DAnmTransformKeyData*);
    void readAnmTextureSRT(const J3DAnmTextureSRTKeyData*);
    void setAnmTextureSRT(J3DAnmTextureSRTKey*, const J3DAnmTextureSRTKeyData*);
    void readAnmColor(const J3DAnmColorKeyData*);
    void setAnmColor(J3DAnmColorKey*, const J3DAnmColorKeyData*);
    void readAnmCluster(const J3DAnmClusterKeyData*);
    void setAnmCluster(J3DAnmClusterKey*, const J3DAnmClusterKeyData*);
    void readAnmTevReg(const J3DAnmTevRegKeyData*);
    void setAnmTevReg(J3DAnmTevRegKey*, const J3DAnmTevRegKeyData*);
    void readAnmVtxColor(const J3DAnmVtxColorKeyData*);
    void setAnmVtxColor(J3DAnmVtxColorKey*, const J3DAnmVtxColorKeyData*);

    J3DAnmBase* mAnm;
};

#endif /* J3DANMLOADER_H */
