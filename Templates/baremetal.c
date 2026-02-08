/* 裸机/手撕代码模板 - 模拟无标准库环境 */
#define NULL ((void *)0)
typedef unsigned long size_t;

// 手动实现 memcpy
void* my_memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    while (n--) *d++ = *s++;
    return dest;
}
