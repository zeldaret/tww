#ifndef PTMF_H
#define PTMF_H

typedef struct __ptmf {
    long this_delta;  // self-explanatory
    long v_offset;    // vtable offset
    union {
        void* f_addr;    // function address
        long ve_offset;  // virtual function entry offset (of vtable)
    } f_data;
} __ptmf;

const __ptmf __ptmf_null;
long __ptmf_test(__ptmf* ptmf);
void __ptmf_cmpr(register __ptmf* this, register __ptmf* other);
void __ptmf_scall(...);

#endif /* PTMF_H */
