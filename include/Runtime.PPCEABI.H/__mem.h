#ifndef RUNTIME_MEM_H
#define RUNTIME_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

__declspec(section ".init") void* memcpy(void* dest, const void* src, size_t n);
__declspec(section ".init") void __fill_mem(void* dest, int val, size_t count);
__declspec(section ".init") void* memset(void* dest, int val, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* RUNTIME_MEM_H */
