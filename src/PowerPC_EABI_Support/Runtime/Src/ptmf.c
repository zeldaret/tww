#include "ptmf.h"

const __ptmf __ptmf_null = { 0, 0, 0 };

asm long __ptmf_test(register __ptmf* ptmf) {
    lwz r5, __ptmf.this_delta(ptmf)
    lwz r6, __ptmf.v_offset(ptmf)
    lwz r7, __ptmf.f_data(ptmf)
    li r3, 0x1
    cmpwi r5, 0x0
    cmpwi cr6, r6, 0x0
    cmpwi cr7, r7, 0x0
    bnelr
    bnelr cr6
    bnelr cr7
    li r3, 0x0
    blr
};

asm void __ptmf_cmpr(register __ptmf* lhs, register __ptmf* rhs) {
    lwz r5, __ptmf.this_delta(lhs)
    lwz r6, __ptmf.this_delta(rhs)
    lwz r7, __ptmf.v_offset(lhs)
    lwz r8, __ptmf.v_offset(rhs)
    lwz r9, __ptmf.f_data(lhs)
    lwz r10, __ptmf.f_data(rhs)
    li r3, 0x1
    cmpw r5, r6
    cmpw cr6, r7, r8
    cmpw cr7, r9, r10
    bnelr
    bnelr cr6
    bnelr cr7
    li r3, 0x0
    blr
};

asm void __ptmf_scall(...) {
    nofralloc;
    lwz r0, __ptmf.this_delta(r12)
    lwz r11, __ptmf.v_offset(r12)
    lwz r12, __ptmf.f_data(r12)
    add r3, r3, r0
    cmpwi r11, 0x0
    blt do_call
    lwzx r12, r3, r12
    lwzx r12, r12, r11
do_call:
    mtctr r12
    bctr
};
