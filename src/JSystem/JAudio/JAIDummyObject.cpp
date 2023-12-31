//
// Generated by dtk
// Translation Unit: JAIDummyObject.cpp
//

#include "JSystem/JAudio/JAIDummyObject.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JAudio/JAISound.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

JAInter::DummyVec* JAInter::DummyObjectMgr::deadObjectFreePointer;
JAInter::DummyVec* JAInter::DummyObjectMgr::deadObjectUsedPointer;
JAInter::DummyVec* JAInter::DummyObjectMgr::deadObjectObject;

/* 802919A0-80291B40       .text init__Q27JAInter14DummyObjectMgrFv */
void JAInter::DummyObjectMgr::init() {
    deadObjectObject = new (JAIBasic::getCurrentJAIHeap(), 0x20) DummyVec[JAIGlobalParameter::getParamDummyObjectMax()];
    JUT_ASSERT_MSG(37, deadObjectObject, "JAIDummyObjectMgr::init Cannot Alloc Heap!!\n");
    deadObjectFreePointer = deadObjectObject;
    deadObjectUsedPointer = NULL;
    deadObjectObject[0].field_0x0 = NULL;
    deadObjectObject[0].field_0x4 = deadObjectObject + 1;
    int i;
    for (i = 1; i < JAIGlobalParameter::getParamDummyObjectMax() - 1; i++) {
        deadObjectObject[i].field_0x0 = deadObjectObject + (i - 1);
        deadObjectObject[i].field_0x4 = deadObjectObject + (i + 1);
    }
    deadObjectObject[i].field_0x0 = deadObjectObject + (i - 1);
    deadObjectObject[i].field_0x4 = NULL;
}

/* 80291B40-80291BAC       .text getPointer__Q27JAInter14DummyObjectMgrFUlb */
JAInter::DummyVec* JAInter::DummyObjectMgr::getPointer(u32 param_1, bool param_2) {
    DummyVec** r5 = &deadObjectFreePointer;
    DummyVec** r6 = &deadObjectUsedPointer;
    DummyVec* r7;
    if (deadObjectFreePointer) {
        r7 = *r5;
        *r5 = r7->field_0x4;
        if (*r6) {
            r7->field_0x4 = *r6;
            (*r6)->field_0x0 = r7;
        } else {
            r7->field_0x4 = NULL;
        }
        r7->field_0x0 = NULL;
        *r6 = r7;
        r7->field_0x18 = param_1;
        r7->field_0x1c = param_2;
        r7->field_0x8 = NULL;
    } else {
        r7 = NULL;
    }
    return r7;
}

/* 80291BAC-80291C20       .text releasePointer__Q27JAInter14DummyObjectMgrFPQ27JAInter8DummyVec */
void JAInter::DummyObjectMgr::releasePointer(DummyVec* param_1) {
    DummyVec** r5 = &deadObjectFreePointer;
    DummyVec** r4 = &deadObjectUsedPointer;
    if (deadObjectUsedPointer != param_1) {
        param_1->field_0x0->field_0x4 = param_1->field_0x4;
        if (param_1->field_0x4) {
            param_1->field_0x4->field_0x0 = param_1->field_0x0;
        }
    } else {
        *r4 = param_1->field_0x4;
        if (param_1->field_0x4) {
            param_1->field_0x4->field_0x0 = NULL;
        }
    }
    param_1->field_0x4 = *r5;
    if (param_1->field_0x4) {
        param_1->field_0x4->field_0x0 = param_1;
    }
    *r5 = param_1;
}

/* 80291C20-80291CCC       .text check__Q27JAInter14DummyObjectMgrFv */
void JAInter::DummyObjectMgr::check() {
    DummyVec* r31 = deadObjectUsedPointer;
    while (r31) {
        DummyVec* r30 = r31->field_0x4;
        r31->field_0x18--;
        if (r31->field_0x18 == 0 || (!r31->field_0x1c && r31->field_0x8 == NULL)) {
            if (r31->field_0x1c == true) {
                JAIBasic::getInterface()->stopAllSound(&r31->field_0xc);
            } else if (r31->field_0x8) {
                r31->field_0x8->stop(0);
            }
            releasePointer(r31);
        }
        r31 = r30;
    }
}
