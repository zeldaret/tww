#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include "f_pc/f_pc_base.h"
#include "global.h"

class cBgS_GrpPassChk {
public:
    virtual ~cBgS_GrpPassChk() {}
};

class cBgS_PolyPassChk;

class cBgS_Chk {
private:
    /* 0x0 */ cBgS_PolyPassChk* mPolyPassChk;
    /* 0x4 */ cBgS_GrpPassChk* mGrpPassChk;
    /* 0x8 */ fpc_ProcID mActorPid;
    /* 0xC */ u8 unk_0x0C;
    /* 0x10 */  // __vtable__

public:
    cBgS_Chk() {
        mPolyPassChk = NULL;
        mGrpPassChk = NULL;
        unk_0x0C = 1;
    }
    void SetExtChk(cBgS_Chk& other) {
        mPolyPassChk = other.mPolyPassChk;
        mGrpPassChk = other.mGrpPassChk;
        mActorPid = other.mActorPid;
        unk_0x0C = other.unk_0x0C;
    }
    bool ChkSameActorPid(fpc_ProcID) const;

    void SetActorPid(fpc_ProcID pid) { mActorPid = pid; }
    fpc_ProcID GetActorPid() const { return mActorPid; }
    void SetPolyPassChk(cBgS_PolyPassChk* p_chk) { mPolyPassChk = p_chk; }
    void SetGrpPassChk(cBgS_GrpPassChk* p_chk) { mGrpPassChk = p_chk; }
    cBgS_PolyPassChk* GetPolyPassChk() const { return mPolyPassChk; }
    cBgS_GrpPassChk* GetGrpPassChk() const { return mGrpPassChk; }

    virtual ~cBgS_Chk();
};  // Size: 0x14

STATIC_ASSERT(sizeof(cBgS_Chk) == 0x14);

#endif /* C_BG_S_CHK_H */
