#!/usr/bin/env python3
"""
verifier.py - Test case generation and verification tool

Use this script to:
1. Generate random test cases
2. Verify algorithm outputs
3. Compare different implementations
4. Stress test your solutions

Usage:
    python3 verifier.py
"""

import random
import subprocess
import sys
import time
from typing import List, Tuple, Callable, Any

# ============================================================================
# CONFIGURATION
# ============================================================================

EXECUTABLE_PATH = "./solution"  # Path to your compiled solution
TIMEOUT_SECONDS = 5             # Max execution time per test
RANDOM_SEED = 42                # Seed for reproducibility (None for random)

# ============================================================================
# TEST CASE GENERATORS
# ============================================================================

def generate_random_array(size: int, min_val: int = -1000, max_val: int = 1000) -> List[int]:
    """Generate a random array of integers."""
    return [random.randint(min_val, max_val) for _ in range(size)]


def generate_sorted_array(size: int, ascending: bool = True) -> List[int]:
    """Generate a sorted array."""
    arr = list(range(size))
    return arr if ascending else arr[::-1]


def generate_edge_cases() -> List[List[int]]:
    """Generate common edge cases."""
    return [
        [],                          # Empty array
        [1],                         # Single element
        [1, 1, 1, 1],               # All same
        [-5, -3, -1],               # All negative
        [0, 0, 0],                  # All zeros
        [1, 2, 3, 4, 5],            # Already sorted
        [5, 4, 3, 2, 1],            # Reverse sorted
        [1, -1, 2, -2, 3, -3],      # Alternating signs
    ]


def generate_string_cases(length: int = 10, charset: str = "abcdefghijklmnopqrstuvwxyz") -> str:
    """Generate random string."""
    return ''.join(random.choice(charset) for _ in range(length))


def generate_graph(num_vertices: int, num_edges: int, directed: bool = False) -> List[Tuple[int, int]]:
    """Generate random graph as edge list."""
    edges = set()
    while len(edges) < num_edges:
        u = random.randint(0, num_vertices - 1)
        v = random.randint(0, num_vertices - 1)
        if u != v:
            edge = (u, v) if directed else tuple(sorted([u, v]))
            edges.add(edge)
    return list(edges)


def generate_tree(num_nodes: int) -> List[Tuple[int, int]]:
    """Generate random tree (connected acyclic graph)."""
    if num_nodes <= 1:
        return []
    
    edges = []
    for i in range(1, num_nodes):
        parent = random.randint(0, i - 1)
        edges.append((parent, i))
    
    return edges

# ============================================================================
# VERIFICATION FUNCTIONS
# ============================================================================

def verify_sorted(arr: List[int], ascending: bool = True) -> bool:
    """Verify if array is sorted."""
    if len(arr) <= 1:
        return True
    
    for i in range(len(arr) - 1):
        if ascending:
            if arr[i] > arr[i + 1]:
                return False
        else:
            if arr[i] < arr[i + 1]:
                return False
    return True


def verify_permutation(original: List[int], result: List[int]) -> bool:
    """Verify if result is a permutation of original."""
    return sorted(original) == sorted(result)


def verify_binary_search(arr: List[int], target: int, result: int) -> bool:
    """Verify binary search result."""
    if result == -1:
        return target not in arr
    return 0 <= result < len(arr) and arr[result] == target

# ============================================================================
# SOLUTION EXECUTION
# ============================================================================

def run_solution(input_data: str, executable: str = EXECUTABLE_PATH) -> Tuple[str, float, int]:
    """
    Run the solution executable with given input.
    
    Returns:
        (output, execution_time, return_code)
    """
    try:
        start_time = time.time()
        process = subprocess.run(
            [executable],
            input=input_data,
            capture_output=True,
            text=True,
            timeout=TIMEOUT_SECONDS
        )
        execution_time = time.time() - start_time
        
        return process.stdout.strip(), execution_time, process.returncode
        
    except subprocess.TimeoutExpired:
        return "TIMEOUT", TIMEOUT_SECONDS, -1
    except FileNotFoundError:
        print(f"Error: Executable '{executable}' not found!")
        print("Please compile your solution first.")
        sys.exit(1)
    except Exception as e:
        return f"ERROR: {str(e)}", 0.0, -1

# ============================================================================
# BRUTE FORCE REFERENCE SOLUTIONS
# ============================================================================

def brute_force_max_subarray(arr: List[int]) -> int:
    """Find maximum subarray sum (O(n^2) brute force)."""
    if not arr:
        return 0
    
    max_sum = float('-inf')
    for i in range(len(arr)):
        current_sum = 0
        for j in range(i, len(arr)):
            current_sum += arr[j]
            max_sum = max(max_sum, current_sum)
    
    return max_sum


def brute_force_sorting(arr: List[int]) -> List[int]:
    """Simple bubble sort for verification."""
    arr = arr.copy()
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

# ============================================================================
# TEST RUNNERS
# ============================================================================

def test_single_case(test_input: str, expected_output: str = None, 
                     description: str = "Test") -> bool:
    """Run a single test case."""
    print(f"\n{description}")
    print(f"Input: {test_input[:100]}..." if len(test_input) > 100 else f"Input: {test_input}")
    
    output, exec_time, return_code = run_solution(test_input)
    
    print(f"Output: {output}")
    print(f"Execution time: {exec_time * 1000:.2f} ms")
    
    if return_code != 0:
        print(f"⚠️  Warning: Non-zero return code ({return_code})")
    
    if expected_output is not None:
        if output == expected_output:
            print("✅ PASSED")
            return True
        else:
            print(f"❌ FAILED - Expected: {expected_output}")
            return False
    
    print("⚪ Output not verified (no expected output provided)")
    return True


def stress_test(test_generator: Callable, num_tests: int = 100,
                verifier: Callable = None) -> Tuple[int, int]:
    """
    Run stress tests with random inputs.
    
    Args:
        test_generator: Function that generates test input string
        num_tests: Number of tests to run
        verifier: Optional function to verify output
        
    Returns:
        (passed, failed) counts
    """
    print(f"\n{'='*60}")
    print(f"STRESS TEST: Running {num_tests} random test cases")
    print(f"{'='*60}")
    
    passed = 0
    failed = 0
    
    for i in range(num_tests):
        test_input = test_generator()
        output, exec_time, return_code = run_solution(test_input)
        
        if return_code != 0 or output == "TIMEOUT" or output.startswith("ERROR"):
            failed += 1
            print(f"Test {i+1}: ❌ FAILED (return code: {return_code})")
        elif verifier is not None:
            if verifier(test_input, output):
                passed += 1
            else:
                failed += 1
                print(f"Test {i+1}: ❌ FAILED (verification failed)")
        else:
            passed += 1
        
        if (i + 1) % 10 == 0:
            print(f"Progress: {i+1}/{num_tests} tests completed...")
    
    print(f"\n{'='*60}")
    print(f"RESULTS: {passed} passed, {failed} failed")
    print(f"{'='*60}")
    
    return passed, failed

# ============================================================================
# EXAMPLE USAGE
# ============================================================================

def example_sorting_test():
    """Example: Test a sorting algorithm."""
    print("\n" + "="*60)
    print("EXAMPLE: Testing Sorting Algorithm")
    print("="*60)
    
    # Edge cases
    edge_cases = generate_edge_cases()
    
    for i, test_case in enumerate(edge_cases):
        test_input = f"{len(test_case)}\n" + " ".join(map(str, test_case))
        expected = " ".join(map(str, sorted(test_case)))
        test_single_case(test_input, expected, f"Edge Case {i+1}")
    
    # Random tests
    def gen_random_test():
        size = random.randint(1, 20)
        arr = generate_random_array(size)
        return f"{size}\n" + " ".join(map(str, arr))
    
    stress_test(gen_random_test, num_tests=10)


def example_comparison_test():
    """Example: Compare your solution with brute force."""
    print("\n" + "="*60)
    print("EXAMPLE: Comparing Solution with Brute Force")
    print("="*60)
    
    for test_num in range(5):
        arr = generate_random_array(random.randint(5, 15))
        
        # Brute force answer
        expected = brute_force_sorting(arr)
        
        # Your solution
        test_input = f"{len(arr)}\n" + " ".join(map(str, arr))
        output, exec_time, _ = run_solution(test_input)
        
        result = list(map(int, output.split())) if output and len(output) > 0 and output[0].isdigit() else []
        
        if result == expected:
            print(f"Test {test_num + 1}: ✅ PASSED ({exec_time*1000:.2f} ms)")
        else:
            print(f"Test {test_num + 1}: ❌ FAILED")
            print(f"  Input: {arr}")
            print(f"  Expected: {expected}")
            print(f"  Got: {result}")

# ============================================================================
# MAIN
# ============================================================================

def main():
    """Main entry point for the verifier."""
    if RANDOM_SEED is not None:
        random.seed(RANDOM_SEED)
        print(f"Using random seed: {RANDOM_SEED}")
    
    print("="*60)
    print("ALGORITHM VERIFIER AND TEST GENERATOR")
    print("="*60)
    
    # ========================================
    # CUSTOMIZE YOUR TESTS HERE
    # ========================================
    
    # Example: Manual test cases
    test_single_case(
        test_input="5\n3 1 4 1 5",
        expected_output="1 1 3 4 5",
        description="Manual Test: Sort [3,1,4,1,5]"
    )
    
    # Uncomment to run example tests:
    # example_sorting_test()
    # example_comparison_test()
    
    print("\n" + "="*60)
    print("Testing complete!")
    print("="*60)


if __name__ == "__main__":
    main()

# ============================================================================
# USAGE TIPS:
#
# 1. Compile your solution first:
#    gcc solution.c -o solution
#    g++ solution.cpp -o solution
#
# 2. Set EXECUTABLE_PATH to your compiled binary
#
# 3. Customize the test generators for your specific problem
#
# 4. Add verification functions to check correctness
#
# 5. Use stress tests to find edge cases and bugs
#
# 6. Compare against brute force for small inputs
#
# ============================================================================
