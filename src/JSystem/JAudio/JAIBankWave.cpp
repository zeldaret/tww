//
// Generated by dtk
// Translation Unit: JAIBankWave.cpp
//

#include "JSystem/JAudio/JAIBankWave.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JAudio/JASWaveArcLoader.h"
#include "JSystem/JAudio/JASWaveBankMgr.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

s32* JAInter::BankWave::wsGroupNumber;
s32* JAInter::BankWave::wsLoadStatus;
s32 JAInter::BankWave::wsMax;

/* 80291220-80291230       .text setWsGroupNumber__Q27JAInter8BankWaveFll */
void JAInter::BankWave::setWsGroupNumber(s32 param_1, s32 param_2) {
    wsGroupNumber[param_1] = param_2;
}

/* 80291230-80291240       .text setWsLoadStatus__Q27JAInter8BankWaveFll */
void JAInter::BankWave::setWsLoadStatus(s32 param_1, s32 param_2) {
    wsLoadStatus[param_1] = param_2;
}

/* 80291240-8029144C       .text init__Q27JAInter8BankWaveFv */
void JAInter::BankWave::init() {
    /* Nonmatching */
    wsGroupNumber = new (JAIBasic::getCurrentJAIHeap(), 32) s32[wsMax];
    wsLoadStatus = new (JAIBasic::getCurrentJAIHeap(), 32) s32[wsMax];
    JASystem::WaveArcLoader::setCurrentDir(JAIGlobalParameter::getParamWavePath());
    JASystem::WaveBankMgr::init(0x100);
    JASystem::WaveArcLoader::init();
}

/* 8029144C-802914D4       .text setWaveScene__Q27JAInter8BankWaveFv */
void JAInter::BankWave::setWaveScene() {
    /* Nonmatching */
}

/* 802914D4-80291578       .text loadSecondStayWave__Q27JAInter8BankWaveFv */
void JAInter::BankWave::loadSecondStayWave() {
    /* Nonmatching */
}

/* 80291578-802915C4       .text setSceneSetFinishCallback__Q27JAInter8BankWaveFll */
void JAInter::BankWave::setSceneSetFinishCallback(s32, s32) {
    /* Nonmatching */
}

/* 802915C4-802915DC       .text finishSceneSet__Q27JAInter8BankWaveFUl */
void JAInter::BankWave::finishSceneSet(u32) {
    /* Nonmatching */
}

/* 802915DC-8029165C       .text loadSceneWave__Q27JAInter8BankWaveFll */
void JAInter::BankWave::loadSceneWave(s32, s32) {
    /* Nonmatching */
}

/* 8029165C-802916B0       .text loadGroupWave__Q27JAInter8BankWaveFll */
void JAInter::BankWave::loadGroupWave(s32, s32) {
    /* Nonmatching */
}

/* 802916B0-802916C0       .text getWaveLoadStatus__Q27JAInter8BankWaveFl */
s32 JAInter::BankWave::getWaveLoadStatus(s32) {
    /* Nonmatching */
}

/* 802916C0-80291704       .text checkAllWaveLoadStatus__Q27JAInter8BankWaveFv */
bool JAInter::BankWave::checkAllWaveLoadStatus() {
    /* Nonmatching */
}
