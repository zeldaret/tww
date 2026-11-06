#ifndef J3DNODE_H
#define J3DNODE_H

#include "dolphin/types.h"

class J3DNode;
class J3DModelData;

typedef int (*J3DNodeCallBack)(J3DNode*, int);
// The second argument to a J3DNodeCallBack determines the timing that the callback was called at.
// In: Called after the current joint has been calced, but before its children and younger siblings have been calced.
// Out: Called after the current joint and its children have been calced, but before its younger siblings have been calced.
enum {
    J3DNodeCBCalcTiming_In = 0,
    J3DNodeCBCalcTiming_Out = 1,
};

class J3DNode {
public:
    virtual void init(J3DModelData*) {}
    virtual void entryIn() {}
    virtual void calcIn() {}
    virtual void calcOut() {}
    virtual u32 getType() const { return 'NNON'; }
    virtual ~J3DNode();

    J3DNode();
    void appendChild(J3DNode*);

    J3DNodeCallBack getCallBack() { return mCallBack; }
    void setCallBack(J3DNodeCallBack callback) { mCallBack = callback; }
    J3DNode* getChild() { return mChild; }
    // "Younger" sibling. The next node after this one that was appended to the same parent.
    J3DNode* getYounger() { return mYounger; }
    void setYounger(J3DNode* pYounger) { mYounger = pYounger; }

    /* 0x04 */ void* mCallBackUserData;
    /* 0x08 */ J3DNodeCallBack mCallBack;
    /* 0x0C */ void* field_0x8;
    /* 0x10 */ J3DNode* mChild;
    /* 0x14 */ J3DNode* mYounger;
};  // Size: 0x18

#endif /* J3DNODE_H */
