/**
 * @file utils.h
 * @brief Utility macros and functions for embedded systems and algorithms
 * 
 * Collection of useful bit manipulation, math, and general utility macros.
 * Optimized for embedded systems with limited resources.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
 * BIT MANIPULATION MACROS
 * ============================================================================ */

/**
 * @brief Set a specific bit to 1
 * @param x Variable
 * @param n Bit position (0-indexed)
 */
#define BIT_SET(x, n)       ((x) |= (1U << (n)))

/**
 * @brief Clear a specific bit to 0
 * @param x Variable
 * @param n Bit position (0-indexed)
 */
#define BIT_CLEAR(x, n)     ((x) &= ~(1U << (n)))

/**
 * @brief Toggle a specific bit
 * @param x Variable
 * @param n Bit position (0-indexed)
 */
#define BIT_TOGGLE(x, n)    ((x) ^= (1U << (n)))

/**
 * @brief Check if a specific bit is set
 * @param x Variable
 * @param n Bit position (0-indexed)
 * @return Non-zero if bit is set, 0 otherwise
 */
#define BIT_CHECK(x, n)     ((x) & (1U << (n)))

/**
 * @brief Read a specific bit (returns 0 or 1)
 * @param x Variable
 * @param n Bit position (0-indexed)
 */
#define BIT_READ(x, n)      (((x) >> (n)) & 1U)

/**
 * @brief Write a specific bit
 * @param x Variable
 * @param n Bit position (0-indexed)
 * @param val Value (0 or 1)
 */
#define BIT_WRITE(x, n, val) \
    do { \
        if (val) BIT_SET(x, n); \
        else BIT_CLEAR(x, n); \
    } while(0)

/**
 * @brief Create a bitmask with n bits set
 */
#define BIT_MASK(n)         ((1U << (n)) - 1U)

/**
 * @brief Extract n bits starting from position p
 * @param x Variable
 * @param p Starting position (0-indexed)
 * @param n Number of bits
 */
#define BIT_EXTRACT(x, p, n) (((x) >> (p)) & BIT_MASK(n))

/**
 * @brief Set n bits starting from position p to value v
 */
#define BIT_SET_RANGE(x, p, n, v) \
    ((x) = ((x) & ~(BIT_MASK(n) << (p))) | (((v) & BIT_MASK(n)) << (p)))

/**
 * @brief Count number of set bits (Brian Kernighan's algorithm)
 */
static inline int popcount(uint32_t x) {
    int count = 0;
    while (x) {
        x &= (x - 1);  // Clear the least significant bit
        count++;
    }
    return count;
}

/**
 * @brief Check if x is a power of 2
 */
#define IS_POWER_OF_2(x)    (((x) > 0) && (((x) & ((x) - 1)) == 0))

/**
 * @brief Round up to next power of 2
 */
static inline uint32_t next_power_of_2(uint32_t x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

/**
 * @brief Reverse bits in a 32-bit integer
 */
static inline uint32_t reverse_bits(uint32_t x) {
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    x = (x >> 16) | (x << 16);
    return x;
}

/**
 * @brief Find position of least significant bit set (0-indexed)
 * @return Position of LSB, or -1 if x is 0
 */
static inline int find_first_set(uint32_t x) {
    if (x == 0) return -1;
    int pos = 0;
    while (!(x & 1)) {
        x >>= 1;
        pos++;
    }
    return pos;
}

/* ============================================================================
 * MATHEMATICAL MACROS
 * ============================================================================ */

/**
 * @brief Minimum of two values
 */
#define MIN(a, b)           (((a) < (b)) ? (a) : (b))

/**
 * @brief Maximum of two values
 */
#define MAX(a, b)           (((a) > (b)) ? (a) : (b))

/**
 * @brief Absolute value
 */
#define ABS(x)              (((x) < 0) ? -(x) : (x))

/**
 * @brief Clamp value between min and max
 */
#define CLAMP(x, min, max)  (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

/**
 * @brief Swap two values
 */
#define SWAP(a, b) \
    do { \
        typeof(a) __tmp = (a); \
        (a) = (b); \
        (b) = __tmp; \
    } while(0)

/**
 * @brief Sign of a number (-1, 0, or 1)
 */
#define SIGN(x)             (((x) > 0) - ((x) < 0))

/**
 * @brief Check if number is even
 */
#define IS_EVEN(x)          (((x) & 1) == 0)

/**
 * @brief Check if number is odd
 */
#define IS_ODD(x)           (((x) & 1) == 1)

/**
 * @brief Align value to next multiple of alignment
 */
#define ALIGN_UP(x, align)  (((x) + (align) - 1) & ~((align) - 1))

/**
 * @brief Align value to previous multiple of alignment
 */
#define ALIGN_DOWN(x, align) ((x) & ~((align) - 1))

/**
 * @brief Check if value is aligned
 */
#define IS_ALIGNED(x, align) (((x) & ((align) - 1)) == 0)

/* ============================================================================
 * ARRAY MACROS
 * ============================================================================ */

/**
 * @brief Get number of elements in array
 */
#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief Iterate over array
 */
#define FOR_EACH(type, item, arr, size) \
    for (type* item = (arr); item < (arr) + (size); item++)

/**
 * @brief Zero out array
 */
#define ZERO_ARRAY(arr, size) \
    do { \
        for (size_t __i = 0; __i < (size); __i++) { \
            (arr)[__i] = 0; \
        } \
    } while(0)

/* ============================================================================
 * MEMORY MACROS
 * ============================================================================ */

/**
 * @brief Safe pointer check
 */
#define CHECK_PTR(ptr) \
    do { \
        if ((ptr) == NULL) { \
            return; \
        } \
    } while(0)

/**
 * @brief Safe pointer check with return value
 */
#define CHECK_PTR_RET(ptr, ret) \
    do { \
        if ((ptr) == NULL) { \
            return (ret); \
        } \
    } while(0)

/**
 * @brief Offset of field in struct (for container_of)
 */
#define OFFSET_OF(type, member) ((size_t)&(((type *)0)->member))

/**
 * @brief Get container structure from member pointer
 */
#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - OFFSET_OF(type, member)))

/* ============================================================================
 * DEBUGGING MACROS
 * ============================================================================ */

#ifdef DEBUG
    #include <stdio.h>
    
    /**
     * @brief Debug print macro
     */
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    
    /**
     * @brief Assert macro
     */
    #define ASSERT(cond) \
        do { \
            if (!(cond)) { \
                fprintf(stderr, "[ASSERT] %s:%d: Assertion '%s' failed\n", \
                        __FILE__, __LINE__, #cond); \
            } \
        } while(0)
#else
    #define DEBUG_PRINT(fmt, ...)
    #define ASSERT(cond)
#endif

/* ============================================================================
 * EMBEDDED-SPECIFIC MACROS
 * ============================================================================ */

/**
 * @brief Mark variable as volatile (for hardware registers)
 */
#define VOLATILE            volatile

/**
 * @brief Hardware register access
 */
#define REG32(addr)         (*(volatile uint32_t *)(addr))
#define REG16(addr)         (*(volatile uint16_t *)(addr))
#define REG8(addr)          (*(volatile uint8_t *)(addr))

/**
 * @brief Disable/Enable interrupts (ARM Cortex-M example)
 */
#if defined(__ARM_ARCH)
    #define DISABLE_INTERRUPTS() __asm volatile ("cpsid i" : : : "memory")
    #define ENABLE_INTERRUPTS()  __asm volatile ("cpsie i" : : : "memory")
#else
    #define DISABLE_INTERRUPTS()
    #define ENABLE_INTERRUPTS()
#endif

/**
 * @brief Memory barrier
 */
#define MEMORY_BARRIER()    __asm volatile ("" : : : "memory")

/**
 * @brief No operation (delay)
 */
#define NOP()               __asm volatile ("nop")

/* ============================================================================
 * OPTIMIZATION HINTS
 * ============================================================================ */

/**
 * @brief Branch prediction hints
 */
#if defined(__GNUC__)
    #define LIKELY(x)       __builtin_expect(!!(x), 1)
    #define UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
    #define LIKELY(x)       (x)
    #define UNLIKELY(x)     (x)
#endif

/**
 * @brief Function attributes
 */
#if defined(__GNUC__)
    #define ALWAYS_INLINE   __attribute__((always_inline)) inline
    #define NEVER_INLINE    __attribute__((noinline))
    #define PACKED          __attribute__((packed))
    #define ALIGNED(n)      __attribute__((aligned(n)))
    #define WEAK            __attribute__((weak))
    #define UNUSED          __attribute__((unused))
#else
    #define ALWAYS_INLINE   inline
    #define NEVER_INLINE
    #define PACKED
    #define ALIGNED(n)
    #define WEAK
    #define UNUSED
#endif

/* ============================================================================
 * CIRCULAR BUFFER MACROS (Common in embedded)
 * ============================================================================ */

/**
 * @brief Circular buffer increment
 */
#define CIRC_BUF_INC(idx, size) (((idx) + 1) & ((size) - 1))

/**
 * @brief Circular buffer decrement
 */
#define CIRC_BUF_DEC(idx, size) (((idx) - 1) & ((size) - 1))

/**
 * @brief Check if circular buffer is full
 */
#define CIRC_BUF_FULL(head, tail, size) \
    (CIRC_BUF_INC(head, size) == (tail))

/**
 * @brief Check if circular buffer is empty
 */
#define CIRC_BUF_EMPTY(head, tail) ((head) == (tail))

/**
 * @brief Count elements in circular buffer
 */
#define CIRC_BUF_COUNT(head, tail, size) \
    (((head) - (tail)) & ((size) - 1))

/* ============================================================================
 * COMPILE-TIME ASSERTIONS
 * ============================================================================ */

/**
 * @brief Compile-time assertion (C11)
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
    #define STATIC_ASSERT(cond, msg) \
        typedef char static_assertion_##msg[(cond) ? 1 : -1]
#endif

/* ============================================================================
 * COMMON CONSTANTS
 * ============================================================================ */

#ifndef NULL
    #define NULL ((void *)0)
#endif

#define KB(x)               ((x) * 1024)
#define MB(x)               ((x) * 1024 * 1024)

#define US_PER_MS           1000
#define MS_PER_SEC          1000
#define US_PER_SEC          1000000

#endif /* UTILS_H */

/* ============================================================================
 * USAGE EXAMPLES:
 * 
 * // Bit manipulation
 * uint32_t flags = 0;
 * BIT_SET(flags, 3);              // Set bit 3
 * if (BIT_CHECK(flags, 3)) { }    // Check if bit 3 is set
 * BIT_TOGGLE(flags, 3);           // Toggle bit 3
 * 
 * // Math operations
 * int x = 10, y = 20;
 * int min_val = MIN(x, y);
 * int max_val = MAX(x, y);
 * SWAP(x, y);
 * 
 * // Array operations
 * int arr[10];
 * size_t count = ARRAY_SIZE(arr);
 * ZERO_ARRAY(arr, count);
 * 
 * // Memory alignment
 * size_t addr = 0x1003;
 * size_t aligned = ALIGN_UP(addr, 4);  // Result: 0x1004
 * 
 * // Hardware register access
 * REG32(0x40000000) = 0x12345678;
 * uint32_t val = REG32(0x40000000);
 * 
 * ============================================================================ */
