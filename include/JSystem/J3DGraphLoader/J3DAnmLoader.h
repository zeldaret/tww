#ifndef J3DANMLOADER_H
#define J3DANMLOADER_H

#include "dolphin/types.h"

enum J3DAnmLoaderDataBaseFlag { J3DLOADER_UNK_FLAG0 };

class J3DAnmBase;

struct J3DAnmLoaderDataBase {
    static void* load(void const*, J3DAnmLoaderDataBaseFlag);
    static void* load(void const*);
    static void setResource(J3DAnmBase*, void const*);
};

#endif /* J3DANMLOADER_H */
