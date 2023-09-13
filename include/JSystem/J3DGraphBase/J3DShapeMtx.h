#ifndef J3DSHAPEMTX_H
#define J3DSHAPEMTX_H

#include "dolphin/mtx/mtxvec.h"

class J3DTexMtx;
class J3DTexGenBlock;

class J3DTexMtxObj {
public:
    Mtx& getMtx(u16 idx) { return mpTexMtx[idx]; }

private:
    /* 0x00 */ Mtx* mpTexMtx;
};

class J3DDifferedTexMtx {
public:
    static void loadExecute(f32 const (*)[4]);

    static inline void load(Mtx m) {
        if (sTexGenBlock != NULL)
            loadExecute(m);
    }

    static J3DTexGenBlock* sTexGenBlock;
    static J3DTexMtxObj* sTexMtxObj;
};

extern u8 struct_804515B0;
extern u8 struct_804515B1;
extern u8 struct_804515B2;
extern u8 struct_804515B3;

class J3DShapeMtx {
public:
    J3DShapeMtx(u16 useMtxIndex) : mUseMtxIndex(useMtxIndex) {}

    void resetMtxLoadCache();
    void loadMtxIndx_PNGP(int, u16) const;
    void loadMtxIndx_PCPU(int, u16) const;
    void loadMtxIndx_NCPU(int, u16) const;
    void loadMtxIndx_PNCPU(int, u16) const;

    virtual ~J3DShapeMtx();
    virtual u32 getType() const;
    virtual u32 getUseMtxNum() const;
    virtual u32 getUseMtxIndex(u16) const;
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, f32 (*)[3][3], f32 (*)[3][3]);

    static u8 sMtxLoadPipeline[48];
    static u16 sMtxLoadCache[10 + 2 /* padding */];
    static u32 sCurrentPipeline;
    // static J3DScaleFlag sCurrentScaleFlag;
    static u8* sCurrentScaleFlag;
    static u8 sNBTFlag;
    static u32 sTexMtxLoadType;

    static void setCurrentPipeline(u32 pipeline) { sCurrentPipeline = pipeline; }
    static void setLODFlag(u8 flag) { struct_804515B1 = flag; }
    static u8 getLODFlag() { return struct_804515B1; }
    static void resetMtxLoadCache();

private:
    /* 0x04 */ u16 mUseMtxIndex;
};

class J3DShapeMtxConcatView : public J3DShapeMtx {
public:
    J3DShapeMtxConcatView(u16 useMtxIndex) : J3DShapeMtx(useMtxIndex) {}

    virtual ~J3DShapeMtxConcatView();
    virtual u32 getType() const;
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const;
    virtual void loadNrmMtx(int, u16, f32 (*)[4]) const;

    void loadMtxConcatView_PNGP(int, u16) const;
    void loadMtxConcatView_PCPU(int, u16) const;
    void loadMtxConcatView_NCPU(int, u16) const;
    void loadMtxConcatView_PNCPU(int, u16) const;
    void loadMtxConcatView_PNGP_LOD(int, u16) const;

    static u8 sMtxLoadPipeline[48];
    static u8 sMtxLoadLODPipeline[48];
    static u8 sMtxPtrTbl[8];
};

class J3DShapeMtxYBBoardConcatView : public J3DShapeMtxConcatView {
public:
    J3DShapeMtxYBBoardConcatView(u16 useMtxIndex) : J3DShapeMtxConcatView(useMtxIndex) {}

    virtual ~J3DShapeMtxYBBoardConcatView();
    virtual u32 getType() const;
    virtual void load() const;
};

class J3DShapeMtxBBoardConcatView : public J3DShapeMtxConcatView {
public:
    J3DShapeMtxBBoardConcatView(u16 useMtxIndex) : J3DShapeMtxConcatView(useMtxIndex) {}

    virtual ~J3DShapeMtxBBoardConcatView();
    virtual u32 getType() const;
    virtual void load() const;
};

class J3DShapeMtxMulti : public J3DShapeMtx {
public:
    J3DShapeMtxMulti(u16 useMtxIndex, u16 useMtxNum, u16* useMtxIndexTable)
        : J3DShapeMtx(useMtxIndex), mUseMtxNum(useMtxNum), mUseMtxIndexTable(useMtxIndexTable) {}

    virtual ~J3DShapeMtxMulti();
    virtual u32 getType() const;
    virtual u32 getUseMtxNum() const;
    virtual u32 getUseMtxIndex(u16) const;
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, f32 (*)[3][3], f32 (*)[3][3]);

private:
    /* 0x6 */ u16 mUseMtxNum;
    /* 0x8 */ u16* mUseMtxIndexTable;
};

class J3DShapeMtxMultiConcatView : public J3DShapeMtxConcatView {
public:
    J3DShapeMtxMultiConcatView(u16 useMtxIndex, u16 useMtxNum, u16* useMtxIndexTable)
        : J3DShapeMtxConcatView(useMtxIndex), mUseMtxNum(useMtxNum),
          mUseMtxIndexTable(useMtxIndexTable) {}

    virtual ~J3DShapeMtxMultiConcatView();
    virtual u32 getType() const;
    virtual u32 getUseMtxNum() const;
    virtual u32 getUseMtxIndex(u16) const;
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const;
    virtual void loadNrmMtx(int, u16, f32 (*)[4]) const;

private:
    /* 0x6 */ u16 mUseMtxNum;
    /* 0x8 */ u16* mUseMtxIndexTable;
};

#endif /* J3DSHAPEMTX_H */