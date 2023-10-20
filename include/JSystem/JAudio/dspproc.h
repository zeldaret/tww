#ifndef DSPPROC_H
#define DSPPROC_H

#include "dolphin/types.h"

void DSPReleaseHalt2(u32);
void DSPReleaseHalt();
void setup_callback(u16);
void DsetupTable(u32, u32, u32, u32, u32);
void DsetMixerLevel(f32);
void DsyncFrame(u32, u32, u32);
void dummy_callback(u16);
void DsetDolbyDelay(u32, u16);

#endif /* DSPPROC_H */
