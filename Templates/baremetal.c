/**
 * @file baremetal.c
 * @brief Bare-metal C template - NO standard library dependencies
 * 
 * Use this template for embedded systems or when stdlib is not available.
 * All functions must be implemented manually.
 * 
 * Compile: gcc -nostdlib -ffreestanding baremetal.c
 * (May need custom linker script for actual bare-metal deployment)
 */

/* ============================================================================
 * CUSTOM IMPLEMENTATIONS (No stdlib!)
 * ============================================================================ */

/**
 * @brief Custom implementation of memset
 * @param ptr Pointer to memory block
 * @param value Value to set (converted to unsigned char)
 * @param num Number of bytes to set
 * @return Pointer to memory block
 */
void* my_memset(void* ptr, int value, unsigned long num) {
    unsigned char* p = (unsigned char*)ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

/**
 * @brief Custom implementation of memcpy
 * @param dest Destination pointer
 * @param src Source pointer
 * @param num Number of bytes to copy
 * @return Pointer to destination
 */
void* my_memcpy(void* dest, const void* src, unsigned long num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    while (num--) {
        *d++ = *s++;
    }
    return dest;
}

/**
 * @brief Custom implementation of strlen
 * @param str Null-terminated string
 * @return Length of string (excluding null terminator)
 */
unsigned long my_strlen(const char* str) {
    unsigned long len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

/**
 * @brief Custom implementation of strcmp
 * @param s1 First string
 * @param s2 Second string
 * @return 0 if equal, <0 if s1<s2, >0 if s1>s2
 */
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

/* ============================================================================
 * MEMORY MANAGEMENT (Static allocation example)
 * ============================================================================ */

#define HEAP_SIZE 4096
#define ALIGNMENT 4  // 4-byte alignment

static unsigned char heap_memory[HEAP_SIZE];
static unsigned long heap_index = 0;

/**
 * @brief Simple bump allocator (no free support)
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or NULL if out of memory
 * 
 * WARNING: This is a simplified allocator. Cannot free individual blocks.
 */
void* simple_alloc(unsigned long size) {
    // Align to ALIGNMENT-byte boundary
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    
    if (heap_index + size > HEAP_SIZE) {
        return (void*)0; // NULL - out of memory
    }
    
    void* ptr = &heap_memory[heap_index];
    heap_index += size;
    return ptr;
}

/**
 * @brief Reset the entire heap (free all allocations)
 * 
 * Use this to reset all memory at once (useful for problem-solving iterations)
 */
void reset_heap(void) {
    heap_index = 0;
    my_memset(heap_memory, 0, HEAP_SIZE);
}

/* ============================================================================
 * YOUR ALGORITHM IMPLEMENTATION HERE
 * ============================================================================ */

/**
 * @brief Example: Reverse a string in-place
 * @param str String to reverse
 * @param len Length of string
 */
void reverse_string(char* str, unsigned long len) {
    unsigned long i = 0;
    unsigned long j = len - 1;
    
    while (i < j) {
        // Swap characters
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/**
 * @brief Example: Find maximum element in array
 * @param arr Array of integers
 * @param size Size of array
 * @return Maximum element (or 0 if size is 0)
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int find_max(const int* arr, unsigned long size) {
    if (size == 0) return 0;
    
    int max = arr[0];
    for (unsigned long i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* ============================================================================
 * ENTRY POINT (bare-metal doesn't have main, but for testing purposes)
 * ============================================================================ */

#ifdef TESTING
/**
 * @brief Test entry point (only compiled when TESTING is defined)
 * 
 * Compile with: gcc -DTESTING baremetal.c -o test
 */
int main(void) {
    // Example test
    char test_str[] = "hello";
    reverse_string(test_str, 5);
    // Result should be "olleh"
    
    int test_arr[] = {3, 7, 2, 9, 1};
    int max = find_max(test_arr, 5);
    // Result should be 9
    
    return 0;
}
#endif

/* ============================================================================
 * NOTES:
 * - No printf/scanf - implement your own I/O if needed
 * - No malloc/free - use static allocation or custom allocator
 * - No assert - implement error handling manually
 * - Be mindful of stack size - avoid large local arrays
 * - Consider using fixed-size data structures
 * 
 * Big-O Analysis Checklist:
 * [ ] What's the time complexity?
 * [ ] What's the space complexity?
 * [ ] Can it be optimized?
 * [ ] Are there any edge cases?
 * ============================================================================ */
