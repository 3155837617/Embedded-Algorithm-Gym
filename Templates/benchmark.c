/**
 * @file benchmark.c
 * @brief Performance benchmarking template with timing macros
 * 
 * Use this template to measure and compare algorithm performance.
 * Includes macros for timing, memory tracking, and statistical analysis.
 * 
 * Compile: gcc -O2 benchmark.c -o benchmark
 * (Use -O2 or -O3 for realistic performance measurements)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ============================================================================
 * TIMING MACROS
 * ============================================================================ */

#define BENCHMARK_ITERATIONS 1000

// High-resolution timer (POSIX)
#if defined(__unix__) || defined(__APPLE__)
    #include <sys/time.h>
    typedef struct timeval benchmark_time_t;
    
    #define GET_TIME(t) gettimeofday(&(t), NULL)
    #define TIME_DIFF_US(start, end) \
        ((end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec))
#else
    // Fallback to clock() for portability
    typedef clock_t benchmark_time_t;
    
    #define GET_TIME(t) t = clock()
    #define TIME_DIFF_US(start, end) \
        (((double)(end - start) / CLOCKS_PER_SEC) * 1000000LL)
#endif

// Global timing variables
static benchmark_time_t __start_time, __end_time;
static long long __elapsed_us;

/**
 * @brief Start timing macro
 */
#define START_TIMER() \
    do { \
        GET_TIME(__start_time); \
    } while(0)

/**
 * @brief Stop timing macro and calculate elapsed time in microseconds
 */
#define STOP_TIMER() \
    do { \
        GET_TIME(__end_time); \
        __elapsed_us = TIME_DIFF_US(__start_time, __end_time); \
    } while(0)

/**
 * @brief Print elapsed time with label
 */
#define PRINT_TIME(label) \
    printf("%-30s: %lld us (%.3f ms)\n", label, __elapsed_us, __elapsed_us / 1000.0)

/**
 * @brief Get elapsed time in microseconds
 */
#define GET_ELAPSED_US() (__elapsed_us)

/* ============================================================================
 * MEMORY TRACKING MACROS
 * ============================================================================ */

static size_t __peak_memory = 0;
static size_t __current_memory = 0;

#define TRACK_MALLOC(ptr, size) \
    do { \
        __current_memory += (size); \
        if (__current_memory > __peak_memory) { \
            __peak_memory = __current_memory; \
        } \
    } while(0)

#define TRACK_FREE(size) \
    do { \
        __current_memory -= (size); \
    } while(0)

#define RESET_MEMORY_TRACKING() \
    do { \
        __peak_memory = 0; \
        __current_memory = 0; \
    } while(0)

#define PRINT_MEMORY_STATS() \
    printf("Peak memory usage: %zu bytes (%.2f KB)\n", \
           __peak_memory, __peak_memory / 1024.0)

/* ============================================================================
 * STATISTICAL MACROS
 * ============================================================================ */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Calculate average of an array
 */
static inline double calculate_average(long long* times, int count) {
    long long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += times[i];
    }
    return (double)sum / count;
}

/**
 * @brief Find minimum in array
 */
static inline long long find_minimum(long long* times, int count) {
    long long min = times[0];
    for (int i = 1; i < count; i++) {
        if (times[i] < min) min = times[i];
    }
    return min;
}

/**
 * @brief Find maximum in array
 */
static inline long long find_maximum(long long* times, int count) {
    long long max = times[0];
    for (int i = 1; i < count; i++) {
        if (times[i] > max) max = times[i];
    }
    return max;
}

/* ============================================================================
 * EXAMPLE ALGORITHMS TO BENCHMARK
 * ============================================================================ */

/**
 * @brief Example: Bubble Sort (O(n²) - inefficient)
 */
void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Example: Quick Sort (O(n log n) - efficient)
 */
void quick_sort_helper(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        
        int pi = i + 1;
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int* arr, int n) {
    quick_sort_helper(arr, 0, n - 1);
}

/* ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================ */

/**
 * @brief Generate random array for testing
 */
void generate_random_array(int* arr, int size, int max_value) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % max_value;
    }
}

/**
 * @brief Verify array is sorted
 */
int is_sorted(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

/* ============================================================================
 * MAIN BENCHMARK EXAMPLE
 * ============================================================================ */

int main(void) {
    srand(time(NULL));
    
    printf("=======================================================\n");
    printf("         ALGORITHM PERFORMANCE BENCHMARK\n");
    printf("=======================================================\n\n");
    
    // Test parameters
    const int SIZES[] = {100, 1000, 5000};
    const int NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);
    
    for (int s = 0; s < NUM_SIZES; s++) {
        int size = SIZES[s];
        printf("Testing with array size: %d\n", size);
        printf("-------------------------------------------------------\n");
        
        // Allocate test arrays
        int* arr1 = (int*)malloc(size * sizeof(int));
        int* arr2 = (int*)malloc(size * sizeof(int));
        
        if (!arr1 || !arr2) {
            fprintf(stderr, "Memory allocation failed!\n");
            return 1;
        }
        
        // Generate random data
        generate_random_array(arr1, size, 10000);
        
        // Test Bubble Sort
        memcpy(arr2, arr1, size * sizeof(int));
        START_TIMER();
        bubble_sort(arr2, size);
        STOP_TIMER();
        PRINT_TIME("Bubble Sort");
        printf("  Sorted correctly: %s\n", is_sorted(arr2, size) ? "YES" : "NO");
        
        // Test Quick Sort
        memcpy(arr2, arr1, size * sizeof(int));
        START_TIMER();
        quick_sort(arr2, size);
        STOP_TIMER();
        PRINT_TIME("Quick Sort");
        printf("  Sorted correctly: %s\n", is_sorted(arr2, size) ? "YES" : "NO");
        
        free(arr1);
        free(arr2);
        printf("\n");
    }
    
    printf("=======================================================\n");
    printf("Benchmark complete!\n");
    printf("=======================================================\n");
    
    return 0;
}

/* ============================================================================
 * USAGE TEMPLATE:
 * 
 * 1. Replace example algorithms with your own
 * 2. Use START_TIMER() before your code
 * 3. Use STOP_TIMER() after your code
 * 4. Use PRINT_TIME("Description") to display results
 * 5. For memory tracking:
 *    - TRACK_MALLOC(ptr, size) after malloc
 *    - TRACK_FREE(size) before free
 *    - PRINT_MEMORY_STATS() to display results
 * 
 * Example:
 *   START_TIMER();
 *   my_algorithm(data, size);
 *   STOP_TIMER();
 *   PRINT_TIME("My Algorithm");
 * 
 * ============================================================================ */
