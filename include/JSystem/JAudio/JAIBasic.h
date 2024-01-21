#ifndef JAIBASIC_H
#define JAIBASIC_H

#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/mtx/vec.h"
#include "JSystem/JAudio/JAIBankWave.h"

class JAISound;
class JKRSolidHeap;

namespace JAInter {
    class Actor;
    class Camera;
}

namespace JASystem {
    class TTrack;
}

class JAIBasic {
public:
    JAIBasic();
    virtual JAISound* makeSound(u32);
    virtual BOOL getMapInfoFxline(u32);
    virtual BOOL getMapInfoGround(u32);
    virtual f32 getMapInfoFxParameter(u32);
    virtual void setSeExtParameter(JAISound*);
    virtual void setRegisterTrackCallback();
    virtual void initStream();
    void initDriver(JKRSolidHeap*, u32, u8);
    void initInterface(u8);
    void initInterfaceMain();
    void initHeap();
    void initArchive();
    void initResourcePath();
    void setCameraInfo(Vec*, Vec*, f32(*)[4], u32);
    void initAudioThread(JKRSolidHeap*, u32, u8);
    void initCamera();
    BOOL initReadFile();
    void processFrameWork();
    void startSoundVec(u32, JAISound**, Vec*, u32, u32, u8);
    void startSoundActor(u32, JAISound**, JAInter::Actor*, u32, u8);
    void startSoundDirectID(u32, JAISound**, JAInter::Actor*, u32, u8);
    void startSoundBasic(u32, JAISound**, JAInter::Actor*, u32, u8, void*);
    void stopSoundHandle(JAISound*, u32);
    void stopPlayingCategoryObjectSe(u8, void*);
    void stopAllSe(u8, void*);
    void stopActorSoundOneBuffer(void*, JAISound*);
    void stopIDSoundOneBuffer(u32, JAISound*);
    void stopIDActorSoundOneBuffer(u32, void*, JAISound*);
    void stopAllSound(void*);
    void stopAllSound(u32);
    void stopAllSound(u32, void*);
    void deleteObject(void*);
    int getSoundOffsetNumberFromID(u32);
    void setSeCategoryVolume(u8, u8);
    static u16 setParameterSeqSync(JASystem::TTrack*, u16);
    bool allocStreamBuffer(void*, s32);
    bool deallocStreamBuffer();

    /* 0x04 */ JAInter::Camera* mAudioCamera;
    /* 0x08 */ JKRSolidHeap* field_0x8;
    /* 0x0C */ u8 initLoadFileSw;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ struct {
        u8 flag1 : 1;
        u8 flag2 : 1;
        u8 flag3 : 1;
        u8 flag4 : 1;
        u8 flag5 : 1;
        u8 flag6 : 1;
        u8 flag7 : 1;
        u8 flag8 : 1;
    } field_0xe;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ int field_0x14;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ u8** field_0x1c;

    static JAIBasic* getInterface() { return msBasic; }
    static JKRSolidHeap* getCurrentJAIHeap() {
        JUT_ASSERT_MSG(148, msCurrentHeap, "JAIBasicのカレントヒープがありません（mCurrentHeap==NULL）\n");
        return msCurrentHeap;
    }

    bool checkAllWaveLoadStatus() {
        return JAInter::BankWave::checkAllWaveLoadStatus();
    }

    // TODO
    void addInitOnCodeSeScene(u32, u32) {}
    void checkEnablePrepare(u32) {}
    void getAudioCamera() {}
    void getInitDataInfo() {}
    void getInitOnCodeSeScene() {}
    void getSceneSetFlag() {}
    void getSeSoundHandle() {}
    void getWaveLoadStatus(s32) {}
    void initAudio(JKRSolidHeap*, u32, u8) {}
    void loadSceneWave(s32, s32) {}
    void prepareSoundVec(u32, JAISound**, Vec*, u32, u32, u8) {}
    void setInitDataInfo(char*) {}
    void setInitOnCodeSeScene(u32*) {}

    static JAIBasic* msBasic;
    static JKRSolidHeap* msCurrentHeap;
};

#endif /* JAIBASIC_H */
