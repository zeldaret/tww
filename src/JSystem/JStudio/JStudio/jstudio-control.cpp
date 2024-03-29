//
// Generated by dtk
// Translation Unit: jstudio-control.cpp
//

#include "JSystem/JStudio/JStudio/jstudio-control.h"
#include "JSystem/JStudio/JStudio/jstudio-math.h"
#include "JSystem/JStudio/JStudio/jstudio-data.h"
#include "dolphin/types.h"
#include "string.h"

/* 8026E080-8026E110       .text __ct__Q27JStudio8TControlFv */
JStudio::TControl::TControl() {
    mTransformOnSet = false;
    mTransformOnGet = false;
    Vec aVStack_20 = {0.0f, 0.0f, 0.0f};
    transformOnSet_setOrigin(aVStack_20, 0.0f);
    transformOnGet_setOrigin(aVStack_20, 0.0f);
}

/* 8026E110-8026E180       .text __dt__Q27JStudio8TControlFv */
JStudio::TControl::~TControl() {}

/* 8026E180-8026E1C0       .text transformOnSet_setOrigin__Q27JStudio8TControlFRC3Vecf */
void JStudio::TControl::transformOnSet_setOrigin(const Vec& param_0, f32 param_1) {
    field_0x8c = param_0;
    mTransformOnSet_RotationY = param_1;
    JStudio::math::getTransformation_RyT(mTransformOnSet_Matrix, param_1, param_0);
}

/* 8026E1C0-8026E248       .text transformOnGet_setOrigin__Q27JStudio8TControlFRC3Vecf */
void JStudio::TControl::transformOnGet_setOrigin(const Vec& param_0, f32 param_1) {
    field_0x98 =  param_0;
    field_0xa8 = param_1;
    Mtx afStack_48;
    MTXTrans(afStack_48, -param_0.x, -param_0.y, -param_0.z);
    math::rotate_y(mTransformOnGet_Matrix, afStack_48, -param_1);
}

/* 8026E248-8026E290       .text __dt__Q27JStudio13TCreateObjectFv */
JStudio::TCreateObject::~TCreateObject() {}

/* 8026E290-8026E314       .text __dt__Q27JStudio8TFactoryFv */
JStudio::TFactory::~TFactory() {}

/* 8026E314-8026E360       .text appendCreateObject__Q27JStudio8TFactoryFPQ27JStudio13TCreateObject */
void JStudio::TFactory::appendCreateObject(JStudio::TCreateObject* param_0) {
    mList.Push_back(param_0);
}

/* 8026E360-8026E438       .text create__Q27JStudio8TFactoryFRCQ47JStudio3stb4data20TParse_TBlock_object */
JStudio::TObject* JStudio::TFactory::create(const JStudio::stb::data::TParse_TBlock_object& param_0) {
    JGadget::TContainerEnumerator<TCreateObject, -4> aTStack_368(&mList);
    while(aTStack_368) {
        TCreateObject& piVar1 = *aTStack_368;
        JStudio::TObject* obj = NULL;
        if (piVar1.create(&obj, param_0)) {
            return obj;
        }
    }
    return stb::TFactory::create(param_0);
}

/* 8026E438-8026E48C       .text __ct__Q27JStudio6TParseFPQ27JStudio8TControl */
JStudio::TParse::TParse(JStudio::TControl* param_0) : stb::TParse(param_0), field_0x04(&param_0->fvb_Control) {}

/* 8026E48C-8026E4FC       .text __dt__Q27JStudio6TParseFv */
JStudio::TParse::~TParse() {}

/* 8026E4FC-8026E56C       .text parseHeader__Q27JStudio6TParseFRCQ47JStudio3stb4data14TParse_THeaderUl */
bool JStudio::TParse::parseHeader(const JStudio::stb::data::TParse_THeader& param_0, u32 param_1) {
    const JStudio::stb::data::THeader::Target& target = param_0.get_target();
    if (memcmp(target.name, JStudio::data::ga8cSignature, sizeof(JStudio::data::ga8cSignature)) != 0) {
        return false;
    }
    if (target.target_version < 2) {
        return false;
    } 
    if (target.target_version > 3) {
        return false;
    }
    return true;
}

/* 8026E56C-8026E5B0       .text parseBlock_block__Q27JStudio6TParseFRCQ47JStudio3stb4data13TParse_TBlockUl */
bool JStudio::TParse::parseBlock_block(const JStudio::stb::data::TParse_TBlock& param_0, u32 param_1) {
    switch(param_0.get_type()) {
    case 'JFVB':
        return parseBlock_block_fvb_(param_0, param_1);
    default:
        return stb::TParse::parseBlock_block(param_0, param_1);
    }
}

/* 8026E5B0-8026E610       .text parseBlock_block_fvb___Q27JStudio6TParseFRCQ47JStudio3stb4data13TParse_TBlockUl */
bool JStudio::TParse::parseBlock_block_fvb_(const JStudio::stb::data::TParse_TBlock& param_0, u32 param_1) {
    const void* pContent = param_0.getContent();
    u32 uVar4 = param_1 & 0xf;
    if ((param_1 & 0x10) != 0) {
        uVar4 |= 0x10;
    }
    if ((param_1 & 0x20) != 0) {
        uVar4 |= 0x20;
    }
    if ((param_1 & 0x40) != 0) {
        uVar4 |= 0x40;
    }
    return field_0x04.parse(pContent, uVar4);
}
