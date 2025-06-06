//
// Generated by dtk
// Translation Unit: JASDSPInterface.cpp
//

#include "JSystem/JAudio/JASDSPInterface.h"
#include "JSystem/JAudio/JASCalc.h"
#include "JSystem/JAudio/JASDriverTables.h"
#include "JSystem/JAudio/JASSystemHeap.h"
#include "JSystem/JAudio/dspproc.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/os/OSCache.h"

JASystem::DSPInterface::DSPBuffer* JASystem::DSPInterface::CH_BUF;
JASystem::DSPInterface::FXBuffer* JASystem::DSPInterface::FX_BUF;
f32 JASystem::DSPInterface::sDSPVolume;

/* 8028A10C-8028A130       .text setDSPMixerLevel__Q28JASystem12DSPInterfaceFf */
void JASystem::DSPInterface::setDSPMixerLevel(f32 param_1) {
    sDSPVolume = param_1;
    DsetMixerLevel(param_1);
}

/* 8028A130-8028A144       .text getDSPHandle__Q28JASystem12DSPInterfaceFUc */
JASystem::DSPInterface::DSPBuffer* JASystem::DSPInterface::getDSPHandle(u8 param_1) {
    return CH_BUF + param_1;
}

/* 8028A144-8028A168       .text setFilterTable__Q28JASystem12DSPInterfaceFPsPsUl */
void JASystem::DSPInterface::setFilterTable(s16* dest, s16* src, u32 size) {
    for (int i = 0; i < size; i++) {
        *dest++ = *src++;
    }
}

/* 8028A168-8028A19C       .text flushBuffer__Q28JASystem12DSPInterfaceFv */
void JASystem::DSPInterface::flushBuffer() {
    DCFlushRange(CH_BUF, sizeof(DSPBuffer) * 64);
    DCFlushRange(FX_BUF, sizeof(FXBuffer) * 4);
}

/* 8028A19C-8028A1C4       .text invalChannelAll__Q28JASystem12DSPInterfaceFv */
void JASystem::DSPInterface::invalChannelAll() {
    DCInvalidateRange(CH_BUF, sizeof(DSPBuffer) * 64);
}

/* 8028A1C4-8028A240       .text clearBuffer__Q28JASystem12DSPInterfaceFv */
void JASystem::DSPInterface::clearBuffer() {
    for (u32 i = 0; i < 64; i++) {
        Calc::bzero(CH_BUF + i, sizeof(DSPBuffer));
    }
    for (u32 i = 0; i < 4; i++) {
        Calc::bzero(FX_BUF + i, sizeof(FXBuffer));
    }
}

u32 JASystem::DSPInterface::DOLBY2_DELAY_BUF[600];

/* 8028A240-8028A28C       .text setupBuffer__Q28JASystem12DSPInterfaceFv */
void JASystem::DSPInterface::setupBuffer() {
    DsetupTable(64, (u32)CH_BUF, (u32)&DSPRES_FILTER, (u32)&DSPADPCM_FILTER, (u32)FX_BUF);
    DsetDolbyDelay((u32)&DOLBY2_DELAY_BUF, 10);
}

/* 8028A28C-8028A368       .text initBuffer__Q28JASystem12DSPInterfaceFv */
void JASystem::DSPInterface::initBuffer() {
    CH_BUF = new(JASDram, 0x20) DSPBuffer[64];
    FX_BUF = new(JASDram, 0x20) FXBuffer[4];
    JUT_ASSERT(163, (CH_BUF != NULL) && (FX_BUF != NULL));
    for (u8 i = 0; i < 4; i++) {
        FX_BUF[i].setFXLine(NULL, NULL);
    }
    clearBuffer();
    setupBuffer();
    flushBuffer();
}

/* 8028A368-8028A378       .text getFXHandle__Q28JASystem12DSPInterfaceFUc */
JASystem::DSPInterface::FXBuffer* JASystem::DSPInterface::getFXHandle(u8 i) {
    return &FX_BUF[i];
}

u16 JASystem::DSPInterface::SEND_TABLE[] = {
    0x0D00, 0x0D60, 0x0DC0, 0x0E20,
    0x0E80, 0x0EE0, 0x0CA0, 0x0F40,
    0x0FA0, 0x0B00, 0x09A0, 0x0000,
};

/* 8028A378-8028A528       .text setFXLine__Q38JASystem12DSPInterface8FXBufferFPsPQ38JASystem12DSPInterface13FxlineConfig_ */
bool JASystem::DSPInterface::FXBuffer::setFXLine(s16* buffer, JASystem::DSPInterface::FxlineConfig_* config) {
    BOOL enable = OSDisableInterrupts();
    field_0x0 = 0;
    if (config) {
        field_0xa = config->field_0x4;
        field_0x8 = SEND_TABLE[config->field_0x2];
        field_0xe = config->field_0x8;
        field_0xc = SEND_TABLE[config->field_0x6];
        field_0x2 = config->field_0xc;
        OSReport("FX LINE Buffer %x/ SIZE %d\n", buffer, config->field_0xc);
        setFilterTable(field_0x10, config->field_0x10, 8);
    }
    if (buffer && config) {
        u32 bufsize = config->field_0xc * 0xa0;
        field_0x4 = buffer;
        Calc::bzero(buffer, bufsize);
        JUT_ASSERT(219, (reinterpret_cast<u32>(buffer) & 0x1f) == 0);
        JUT_ASSERT(220, (bufsize & 0x1f) == 0);
        DCFlushRange(buffer, bufsize);
    } else if (!config || buffer) {
        field_0x4 = buffer;
    }
    if (field_0x4) {
        field_0x0 = config->field_0x0;
    } else {
        field_0x0 = 0;
    }
    DCFlushRange(this, 0x20);
    OSRestoreInterrupts(enable);
    return true;
}

/* 8028A528-8028A574       .text allocInit__Q38JASystem12DSPInterface9DSPBufferFv */
void JASystem::DSPInterface::DSPBuffer::allocInit() {
    field_0xc = 0;
    field_0x2 = 0;
    field_0x10a = 0;
    field_0x0 = 0;
    field_0x58 = 0;
    initFilter();
    flushChannel();
}

/* 8028A574-8028A5D8       .text playStart__Q38JASystem12DSPInterface9DSPBufferFv */
void JASystem::DSPInterface::DSPBuffer::playStart() {
    field_0x10c = 0;
    field_0x60 = 0;
    field_0x8 = 1;
    field_0x66 = 0;
    int i;
    for (i = 0; i < 4; i++) {
        field_0x78[i] = 0;
        field_0xa8[i] = 0;
    }
    for (i = 0; i < 20; i++) {
        field_0x80[i] = 0;
    }
    field_0x0 = 1;
}

u16 JASystem::DSPInterface::JAS_DSP_PREFIX = 0xF355;

/* 8028A5D8-8028A6FC       .text setWaveInfo__Q38JASystem12DSPInterface9DSPBufferFPQ38JASystem6Driver5Wave_UlUl */
void JASystem::DSPInterface::DSPBuffer::setWaveInfo(JASystem::Driver::Wave_* param_1, u32 param_2, u32 param_3) {
    static u8 COMP_BLOCKSAMPLES[8] = {
        0x10, 0x10, 0x01, 0x01, 0x01, 0x10, 0x10, 0x01,
    };
    static u8 COMP_BLOCKBYTES[8] = {
        0x09, 0x05, 0x08, 0x10, 0x01, 0x01, 0x01, 0x01,
    };

    field_0x118 = param_2;
    field_0x64 = COMP_BLOCKSAMPLES[param_1->field_0x1];
    field_0x100 = COMP_BLOCKBYTES[param_1->field_0x1];
    field_0x68 = 0;
    if (field_0x100 < 4) {
        return;
    }
    field_0x11c = param_1->field_0x1c;
    field_0x102 = param_1->field_0x10;
    if (field_0x102) {
        if (param_3 == 1) {
            param_3 = param_1->field_0x14;
        }
        field_0x110 = param_1->field_0x14;
        field_0x114 = param_1->field_0x18;
        field_0x104 = param_1->field_0x20;
        field_0x106 = param_1->field_0x22;
    } else {
        field_0x114 = field_0x11c;
    }
    if (param_3 && field_0x114 > param_3) {
        switch (param_1->field_0x1) {
        case 0:
        case 1:
            field_0x68 = param_3;
            field_0x118 += (param_3 * field_0x100 >> 4);
            field_0x110 -= param_3;
            field_0x114 -= param_3;
            break;
        case 2:
        case 3:
            field_0x68 = param_3;
            break;
        }
    }
    for (int i = 0; i < 16; i++) {
        field_0xb0[i] = 0;
    }
}

/* 8028A6FC-8028A714       .text setOscInfo__Q38JASystem12DSPInterface9DSPBufferFUl */
void JASystem::DSPInterface::DSPBuffer::setOscInfo(u32 param_1) {
    field_0x118 = 0;
    field_0x64 = 16;
    field_0x100 = param_1;
}

/* 8028A714-8028A740       .text initAutoMixer__Q38JASystem12DSPInterface9DSPBufferFv */
void JASystem::DSPInterface::DSPBuffer::initAutoMixer() {
    if (field_0x58) {
        field_0x54 = field_0x56;
        return;
    }
    field_0x54 = 0;
    field_0x58 = 1;
}

/* 8028A740-8028A764       .text setAutoMixer__Q38JASystem12DSPInterface9DSPBufferFUsUcUcUcUc */
void JASystem::DSPInterface::DSPBuffer::setAutoMixer(u16 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5) {
    field_0x50 = param_2 << 8 | param_3;
    field_0x52 = param_4 << 8;
    field_0x56 = param_1;
    field_0x58 = 1;
}

/* 8028A764-8028A77C       .text setPitch__Q38JASystem12DSPInterface9DSPBufferFUs */
void JASystem::DSPInterface::DSPBuffer::setPitch(u16 param_1) {
    if (param_1 >= 0x7fff) {
        param_1 = 0x7fff;
    }
    field_0x4 = param_1;
}

/* 8028A77C-8028A788       .text setMixerInitDelayMax__Q38JASystem12DSPInterface9DSPBufferFUc */
void JASystem::DSPInterface::DSPBuffer::setMixerInitDelayMax(u8 param_1) {
    field_0xe = param_1;
}

/* 8028A788-8028A7AC       .text setMixerInitVolume__Q38JASystem12DSPInterface9DSPBufferFUcsUc */
void JASystem::DSPInterface::DSPBuffer::setMixerInitVolume(u8 param_1, s16 param_2, u8 param_3) {
    u16* tmp = field_0x10[param_1];
    tmp[2] = param_2;
    tmp[1] = param_2;
    tmp[3] = param_3 << 8 | param_3;
}

/* 8028A7AC-8028A7DC       .text setMixerVolume__Q38JASystem12DSPInterface9DSPBufferFUcsUc */
void JASystem::DSPInterface::DSPBuffer::setMixerVolume(u8 param_1, s16 param_2, u8 param_3) {
    if (field_0x10a) {
        return;
    }
    u16* tmp = field_0x10[param_1];
    tmp[1] = param_2;
    tmp[3] = param_3 << 8 | tmp[3] & 0xff;
}

/* 8028A7DC-8028A7F8       .text setMixerVolumeOnly__Q38JASystem12DSPInterface9DSPBufferFUcs */
void JASystem::DSPInterface::DSPBuffer::setMixerVolumeOnly(u8 param_1, s16 param_2) {
    if (field_0x10a) {
        return;
    }
    field_0x10[param_1][1] = param_2;
}

/* 8028A7F8-8028A804       .text setPauseFlag__Q38JASystem12DSPInterface9DSPBufferFUc */
void JASystem::DSPInterface::DSPBuffer::setPauseFlag(u8 param_1) {
    field_0xc = param_1;
}

/* 8028A804-8028A828       .text flushChannel__Q38JASystem12DSPInterface9DSPBufferFv */
void JASystem::DSPInterface::DSPBuffer::flushChannel() {
    DCFlushRange(this, sizeof(*this));
}

/* 8028A828-8028A884       .text initFilter__Q38JASystem12DSPInterface9DSPBufferFv */
void JASystem::DSPInterface::DSPBuffer::initFilter() {
    int i;
    for (i = 0; i < 8; i++) {
        field_0x120[i] = 0;
    }
    field_0x120[0] = 0x7fff;
    for (i = 0; i < 4; i++) {
        field_0x148[i] = 0;
    }
    field_0x148[0] = 0x7fff;
    field_0x150 = 0;
}

/* 8028A884-8028A8BC       .text setFilterMode__Q38JASystem12DSPInterface9DSPBufferFUs */
void JASystem::DSPInterface::DSPBuffer::setFilterMode(u16 param_1) {
    u8 r30 = param_1 & 0x20;
    u8 r31 = param_1 & 0x1f;
    if (r30) {
        if (r31 > 0x14) {
            r31 = 0x14;
        }
    } else {
        if (r31 > 0x18) {
            r31 = 0x18;
        }
    }
    field_0x108 = r30 + r31;
}

/* 8028A8BC-8028A8E4       .text setIIRFilterParam__Q38JASystem12DSPInterface9DSPBufferFPs */
void JASystem::DSPInterface::DSPBuffer::setIIRFilterParam(s16* param_1) {
    setFilterTable(field_0x148, param_1, 4);
}

/* 8028A8E4-8028A90C       .text setFIR8FilterParam__Q38JASystem12DSPInterface9DSPBufferFPs */
void JASystem::DSPInterface::DSPBuffer::setFIR8FilterParam(s16* param_1) {
    setFilterTable(field_0x120, param_1, 8);
}

/* 8028A90C-8028A914       .text setDistFilter__Q38JASystem12DSPInterface9DSPBufferFs */
void JASystem::DSPInterface::DSPBuffer::setDistFilter(s16 param_1) {
    field_0x150 = param_1;
}

/* 8028A914-8028A934       .text setBusConnect__Q38JASystem12DSPInterface9DSPBufferFUcUc */
void JASystem::DSPInterface::DSPBuffer::setBusConnect(u8 param_1, u8 param_2) {
    static const u16 connect_table[12] = {
        0x0000, 0x0D00, 0x0D60, 0x0DC0, 0x0E20, 0x0E80,
        0x0EE0, 0x0CA0, 0x0F40, 0x0FA0, 0x0B00, 0x09A0,
    };
    u16* tmp = field_0x10[param_1];
    tmp[0] = connect_table[param_2];
}

/* 8028A934-8028A978       .text DSP_CreateMap2__FUl */
u16 DSP_CreateMap2(u32 param_1) {
    u16 var1 = 0;
    JASystem::DSPInterface::DSPBuffer* buffer = &JASystem::DSPInterface::CH_BUF[param_1 << 4];
    for (int i = 0; i < 16; i++) {
        var1 <<= 1;
        if (buffer->field_0x0) {
            var1 |= 1;
        }
        buffer++;
    }
    return var1;
}
