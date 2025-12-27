#ifndef J3DSHAPEMTX_H
#define J3DSHAPEMTX_H

#include "JSystem/J3DGraphBase/J3DShape.h"
#include "dolphin/mtx/mtx.h"

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
    J3DShapeMtxMultiImm(u16 useMtxIndex, u16 useMtxNum, u16* useMtxIndexTable)
        : J3DShapeMtxImm(useMtxIndex), mUseMtxNum(useMtxNum), mUseMtxIndexTable(useMtxIndexTable) {}

    virtual ~J3DShapeMtxMultiImm() {}
    virtual u32 getType() const { return 'SMMI'; }
    virtual u32 getUseMtxNum() const { return mUseMtxNum; }
    virtual u16 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
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
    virtual void loadNrmMtx(int, u16, Mtx) const;

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
    virtual u16 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
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
    virtual u16 getUseMtxIndex(u16 i) const { return mUseMtxIndexTable[i]; }
    virtual void load() const;
    virtual void loadNrmMtx(int, u16) const {}
    virtual void loadNrmMtx(int, u16, Mtx) const;

private:
    /* 0x8 */ u16 mUseMtxNum;
    /* 0xC */ u16* mUseMtxIndexTable;
};

#endif /* J3DSHAPEMTX_H */
