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

class J3DShapeMtx {
public:
    typedef void (J3DShapeMtx::*MtxLoadIndx)(int mtxNo, u16 index) const;

    J3DShapeMtx(u16 useMtxIndex) : mUseMtxIndex(useMtxIndex) {}

    void loadMtxIndx_PNGP(int, u16) const;
    void loadMtxIndx_PCPU(int, u16) const;
    void loadMtxIndx_NCPU(int, u16) const;
    void loadMtxIndx_PNCPU(int, u16) const;

    virtual ~J3DShapeMtx() {}
    virtual u32 getType() const { return 'SMTX'; }
    virtual u32 getUseMtxNum() const { return 1; }
    virtual u32 getUseMtxIndex(u16) const { return mUseMtxIndex; }
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, f32 (*)[3][3], f32 (*)[3][3]);

    static MtxLoadIndx sMtxLoadPipeline[4];
    static u32 sCurrentPipeline;
    static u8* sCurrentScaleFlag;
    static u8 sNBTFlag;

    static void setCurrentPipeline(u32 pipeline) { sCurrentPipeline = pipeline; }

protected:
    /* 0x04 */ u16 mUseMtxIndex;
};

class J3DShapeMtxImm : public J3DShapeMtx {
public:
    typedef void (J3DShapeMtxImm::*MtxLoadImm)(int mtxNo, u16 index) const;

    J3DShapeMtxImm(u16 useMtxIndex) : J3DShapeMtx(useMtxIndex) {}

    virtual ~J3DShapeMtxImm() {}
    virtual u32 getType() const { return 'SMIM'; }
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const;

    void loadMtxImm_PNGP(int, u16) const;
    void loadMtxImm_PCPU(int, u16) const;
    void loadMtxImm_NCPU(int, u16) const;
    void loadMtxImm_PNCPU(int, u16) const;
    void loadMtxImm_PNGP_LOD(int, u16) const;

    static MtxLoadImm sMtxLoadPipeline[4];
};

class J3DShapeMtxMultiImm : public J3DShapeMtxImm {
public:
    J3DShapeMtxMultiImm(u16 useMtxIndex) : J3DShapeMtxImm(useMtxIndex) {}

    virtual ~J3DShapeMtxMultiImm() {}
    virtual u32 getType() const { return 'SMMI'; }
    virtual u32 getUseMtxNum() const { return mUseMtxNum; }
    virtual u32 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const;

private:
    /* 0x8 */ u16 mUseMtxNum;
    /* 0xC */ u16* mUseMtxIndexTable;
};

class J3DShapeMtxConcatView : public J3DShapeMtxImm {
public:
    typedef void (J3DShapeMtxConcatView::*MtxLoadConcatView)(int mtxNo, u16 index) const;

    J3DShapeMtxConcatView(u16 useMtxIndex) : J3DShapeMtxImm(useMtxIndex) {}

    virtual ~J3DShapeMtxConcatView() {}
    virtual u32 getType() const { return 'SMCV'; }
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const {}
    virtual void loadNrmMtx(int, u16, f32 (*)[4]) const;

    void loadMtxConcatView_PNGP(int, u16) const;
    void loadMtxConcatView_PCPU(int, u16) const;
    void loadMtxConcatView_NCPU(int, u16) const;
    void loadMtxConcatView_PNCPU(int, u16) const;
    void loadMtxConcatView_PNGP_LOD(int, u16) const;

    static MtxLoadConcatView sMtxLoadPipeline[4];
    static Mtx * sMtxPtrTbl[2];
};

class J3DShapeMtxBBoardImm : public J3DShapeMtxImm {
public:
    J3DShapeMtxBBoardImm(u16 useMtxIndex) : J3DShapeMtxImm(useMtxIndex) {}

    virtual ~J3DShapeMtxBBoardImm() {}
    virtual u32 getType() const { return 'SMBB'; }
    virtual void load() const;
};

class J3DShapeMtxYBBoardImm : public J3DShapeMtxImm {
public:
    J3DShapeMtxYBBoardImm(u16 useMtxIndex) : J3DShapeMtxImm(useMtxIndex) {}

    virtual ~J3DShapeMtxYBBoardImm() {}
    virtual u32 getType() const { return 'SMYB'; }
    virtual void load() const;
};

class J3DShapeMtxYBBoardConcatView : public J3DShapeMtxYBBoardImm {
public:
    J3DShapeMtxYBBoardConcatView(u16 useMtxIndex) : J3DShapeMtxYBBoardImm(useMtxIndex) {}

    virtual ~J3DShapeMtxYBBoardConcatView() {}
    virtual void load() const;
};

class J3DShapeMtxBBoardConcatView : public J3DShapeMtxBBoardImm {
public:
    J3DShapeMtxBBoardConcatView(u16 useMtxIndex) : J3DShapeMtxBBoardImm(useMtxIndex) {}

    virtual ~J3DShapeMtxBBoardConcatView() {}
    virtual void load() const;
};

class J3DShapeMtxMulti : public J3DShapeMtx {
public:
    J3DShapeMtxMulti(u16 useMtxIndex, u16 useMtxNum, u16* useMtxIndexTable)
        : J3DShapeMtx(useMtxIndex), mUseMtxNum(useMtxNum), mUseMtxIndexTable(useMtxIndexTable) {}

    virtual ~J3DShapeMtxMulti() {}
    virtual u32 getType() const { return 'SMML'; }
    virtual u32 getUseMtxNum() const { return mUseMtxNum; }
    virtual u32 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, Mtx33*, Mtx33*);

private:
    /* 0x8 */ u16 mUseMtxNum;
    /* 0xC */ u16* mUseMtxIndexTable;
};

class J3DShapeMtxMultiConcatView : public J3DShapeMtxConcatView {
public:
    J3DShapeMtxMultiConcatView(u16 useMtxIndex, u16 useMtxNum, u16* useMtxIndexTable)
        : J3DShapeMtxConcatView(useMtxIndex), mUseMtxNum(useMtxNum),
          mUseMtxIndexTable(useMtxIndexTable) {}

    virtual ~J3DShapeMtxMultiConcatView() {}
    virtual u32 getType() const { return 'SMMI'; }
    virtual u32 getUseMtxNum() const { return mUseMtxNum; }
    virtual u32 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const {}
    virtual void loadNrmMtx(int, u16, f32 (*)[4]) const;

private:
    /* 0x8 */ u16 mUseMtxNum;
    /* 0xC */ u16* mUseMtxIndexTable;
};

#endif /* J3DSHAPEMTX_H */
