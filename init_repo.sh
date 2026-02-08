#!/bin/bash

echo "正在执行初始化..."

# 1. 创建文件夹
mkdir -p C_Solutions
mkdir -p CPP_Solutions
mkdir -p Python_Scripts
mkdir -p Templates

# 2. 生成 Templates/baremetal.c (裸机/手撕代码模板)
cat <<EOT > Templates/baremetal.c
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
EOT

# 3. 生成 Templates/benchmark.c (性能测试模板)
cat <<EOT > Templates/benchmark.c
#include <stdio.h>
#include <time.h>
#define TIME_IT(func) do { clock_t s = clock(); func; clock_t e = clock(); printf("Time: %f s\n", (double)(e-s)/CLOCKS_PER_SEC); } while(0)
void test_func() { for(volatile int i=0; i<1000000; i++); }
int main() { TIME_IT(test_func()); return 0; }
EOT

# 4. 生成 Templates/acm_io.cpp (刷题 IO 模板)
cat <<EOT > Templates/acm_io.cpp
#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    if(cin >> n) cout << "Input: " << n << endl;
    return 0;
}
EOT

# 5. 生成 Templates/verifier.py (Python 对拍模板)
cat <<EOT > Templates/verifier.py
import random
with open("input.txt", "w") as f:
    f.write(" ".join([str(random.randint(0,100)) for _ in range(10)]))
print("Data generated.")
EOT

echo "✅ 初始化完成！"