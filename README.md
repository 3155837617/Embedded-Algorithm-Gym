# Embedded-Algorithm-Gym
# Embedded Algorithm Gym 🏋️‍♂️

> **Data Structures & Algorithms Training Ground for Embedded System Engineers**
> 
> *Targeting: Firmware Development, Motor Control, and Real-Time Systems.*

## 📖 Introduction
This repository serves as a rigorous practice environment for mastering algorithms and data structures with a focus on **Embedded Systems constraints**. Unlike general software engineering practice, the solutions here emphasize:
- **Memory Safety**: Strict manual management (`malloc`/`free`) and pointer arithmetic.
- **Resource Efficiency**: Analysis of Time ($O(T)$) and Space ($O(S)$) complexity.
- **Bare-Metal Simulation**: Implementation of standard library functions (e.g., `memcpy`, `memset`) from scratch.

## 🛠 Directory Structure

| Folder | Description | Focus Area |
| :--- | :--- | :--- |
| **`C_Solutions/`** | Core algorithms implemented in C99. | Pointers, Bit Manipulation, Linked Lists, ISR simulation. |
| **`CPP_Solutions/`** | Object-Oriented solutions & LeetCode style. | STL usage, Template programming, Design Patterns. |
| **`Python_Scripts/`** | Rapid prototyping & verification. | Algorithm logic verification, Test case generation. |
| **`Templates/`** | Standardized templates for practice. | **Benchmarking**, **Bare-metal**, **IO**. |

## 🚀 Workflow & Standards

### 1. Whiteboard Mode (Recommended) ✍️
To simulate real technical interviews, it is recommended to **disable Copilot/IntelliSense** during the initial coding phase.
- Focus on syntax accuracy and API memory.
- Manually trace the code logic before compilation.

### 2. Coding Standards (Embedded Specific)
- **No Magic Numbers**: Use `#define` or `const` for all constants.
- **Pointer Safety**: Always check for `NULL` before dereferencing.
- **Variable Scope**: Use `static` for file-scope variables to limit visibility.
- **Volatile Usage**: Correctly apply `volatile` for variables modified in ISRs (Interrupt Service Routines).

### 3. How to Use Templates
This repository includes specialized templates in the `Templates/` directory:

* **`baremetal.c`**: Simulates a no-stdlib environment. Use this for "implement memcpy" style questions.
* **`benchmark.c`**: Includes `TIME_IT` macros to measure execution time of sorting/searching algorithms.
* **`verifier.py`**: A Python script to generate random test cases for stress testing your C code.

## 📝 Study Roadmap (Motor Control & Embedded)

- [ ] **Bit Manipulation**: Register setting/clearing, Endianness check.
- [ ] **Memory Management**: Stack vs Heap, Buffer overflow protection, Ring Buffer implementation.
- [ ] **Pointers**: Double pointers, Function pointers (Callbacks), Void pointers.
- [ ] **Real-Time Concepts**: Interrupt concurrency, Volatile, Atomic operations.
- [ ] **Control Algorithms**: PID implementation, Moving Average Filter, Kalman Filter (Simplified).

## ⚖️ License
MIT License. Feel free to use this for your own study.

---
*Created by [励步野] - Master's Student in Motor Control & Embedded Systems.*