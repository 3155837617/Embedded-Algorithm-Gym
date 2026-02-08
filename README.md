# Embedded-Algorithm-Gym 🏋️‍♂️
**Data Structures and Algorithms Practice for Embedded Systems Interviews**

A comprehensive repository for mastering algorithms with a focus on embedded systems constraints and interview preparation.

---

## 📚 Interview Preparation Guide

### Why This Repository?
Embedded systems interviews demand:
- Deep understanding of **memory management** (malloc/free, stack vs heap)
- **Big-O complexity analysis** (time and space)
- Writing code **without standard libraries** (bare-metal scenarios)
- Optimization for **resource-constrained environments**

### 🎯 Whiteboard Mode (Recommended)
For authentic interview practice:
- **Disable autocomplete** in your IDE/editor
  - VSCode: Set `"editor.quickSuggestions": false`
  - Vim: `:set complete=`
  - CLion/IntelliJ: Disable "Code Completion"
- **No syntax highlighting** (optional hardcore mode)
- **Time yourself** - aim for 30-45 minutes per problem
- **Write on paper first**, then implement

### 🧠 Core Focus Areas

#### 1. Memory Management
- **Always** consider malloc/free patterns
- Watch for memory leaks in linked lists, trees, graphs
- Understand stack limitations (avoid large local arrays)
- Practice allocating/deallocating dynamic structures

#### 2. Big-O Analysis
Before coding ANY solution, analyze:
- **Time Complexity**: Best, Average, Worst case
- **Space Complexity**: Auxiliary space, call stack depth
- **Trade-offs**: Time vs Space
- Common patterns:
  - O(1): Hash table lookup, array access
  - O(log n): Binary search, balanced trees
  - O(n): Linear scan, single loop
  - O(n log n): Merge sort, heap operations
  - O(n²): Nested loops, bubble sort

#### 3. Embedded Constraints
- Limited RAM (think KB, not GB)
- No dynamic allocation on some systems
- Bit-level manipulation is your friend
- Fixed-point arithmetic over floating-point
- Cache-aware programming

---

## 📁 Repository Structure

```
Embedded-Algorithm-Gym/
├── C_Solutions/          # Algorithm implementations in C
├── CPP_Solutions/        # C++ solutions with STL where appropriate
├── Python_Scripts/       # Python for rapid prototyping/testing
└── Templates/            # Reusable templates for different scenarios
    ├── baremetal.c       # No stdlib, bare-metal template
    ├── benchmark.c       # Timing and profiling macros
    ├── acm_io.cpp        # Fast I/O for Online Judge problems
    ├── verifier.py       # Test case generation and verification
    └── utils.h           # Bit manipulation and common macros
```

---

## 🚀 Quick Start

### Prerequisites
```bash
# GCC/G++ compiler
gcc --version
g++ --version

# Python 3.x
python3 --version

# Make (optional)
make --version
```

### Using Templates

#### Bare-Metal C Template
```bash
cp Templates/baremetal.c C_Solutions/my_problem.c
# Edit and implement - no stdlib dependencies!
gcc -nostdlib -ffreestanding my_problem.c -o my_problem
```

#### Benchmark Template
```bash
cp Templates/benchmark.c C_Solutions/sort_benchmark.c
# Add your algorithm and use START_TIMER/STOP_TIMER macros
gcc -O2 sort_benchmark.c -o sort_benchmark
```

#### ACM/OJ Style (C++)
```bash
cp Templates/acm_io.cpp CPP_Solutions/contest_problem.cpp
# Fast I/O for competitive programming
g++ -std=c++17 -O2 contest_problem.cpp -o contest_problem
```

#### Test Generation (Python)
```bash
cp Templates/verifier.py Python_Scripts/my_verifier.py
# Generate test cases and verify outputs
python3 my_verifier.py
```

---

## 💡 Best Practices

### Before Writing Code
1. **Clarify requirements** - Ask about edge cases
2. **Design first** - Sketch data structures on paper
3. **Analyze complexity** - Propose Big-O before coding
4. **Discuss trade-offs** - Memory vs speed, readability vs performance

### While Coding
- **Comment your malloc/free** pairs
- **Check return values** (malloc can fail!)
- **Handle edge cases**: NULL pointers, empty inputs, single elements
- **Use meaningful variable names** (even in interviews)

### After Coding
- **Trace through examples** - Walk through with test cases
- **Check memory leaks** - Every malloc needs a free
- **Verify Big-O** - Does implementation match your analysis?
- **Test edge cases** - Empty, single element, maximum size

---

## 🎓 Interview Tips

### Communication
- **Think out loud** - Explain your thought process
- **Ask questions** - Clarify ambiguities
- **Discuss alternatives** - Show you know multiple approaches

### Common Pitfalls
- Off-by-one errors in loops
- Integer overflow in calculations
- Uninitialized variables
- Forgetting to free memory
- Not checking malloc return values

### Embedded-Specific Questions
Be ready to discuss:
- Stack vs heap allocation
- Static vs dynamic memory
- Interrupt-safe code
- Volatile keyword usage
- Memory alignment
- Cache coherency
- Fixed-point arithmetic

---

## 📖 Topics to Master

### Data Structures
- Arrays, Linked Lists, Stacks, Queues
- Hash Tables (implement without stdlib)
- Binary Trees, BSTs, Heaps
- Graphs (adjacency list/matrix)
- Tries, Union-Find

### Algorithms
- Sorting: Quick, Merge, Heap, Counting
- Searching: Binary Search variants
- Graph: BFS, DFS, Dijkstra
- Dynamic Programming
- Bit Manipulation
- Two Pointers, Sliding Window

### Embedded Specific
- Circular buffers (ring buffers)
- State machines
- Bit fields and unions
- Memory pools
- Fixed-size allocators

---

## 🔗 Resources

### Online Judges
- [LeetCode](https://leetcode.com) - Algorithm problems
- [HackerRank](https://hackerrank.com) - Embedded/Systems track
- [Codeforces](https://codeforces.com) - Competitive programming

### Books
- "Cracking the Coding Interview" - Gayle Laakmann McDowell
- "Programming Pearls" - Jon Bentley
- "The Art of Computer Programming" - Donald Knuth

### Embedded Systems
- "Making Embedded Systems" - Elecia White
- "Embedded C Coding Standard" - Barr Group

---

## 🤝 Contributing
Feel free to add your solutions, improve templates, or suggest better practices!

---

## 📄 License
See LICENSE file for details.

---

**Happy Coding! Remember: Practice with constraints makes you a better embedded systems engineer! 💪**
