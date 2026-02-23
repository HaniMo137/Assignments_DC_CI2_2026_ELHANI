# Parallel Computing Assignments - DC_CI2_2026_ELHANI

This repository contains practical assignments for Distributed and Parallel Computing, covering performance optimization, OpenMP, MPI, and high-performance computing benchmarks.

## Repository Structure

```
Assignments_DC_CI2_2026_ELHANI/
├── TP1/    Memory Access & Matrix Multiplication Optimization
├── TP2/    Loop Optimizations & Performance Analysis
├── TP3/    OpenMP Fundamentals
├── TP4/    Advanced OpenMP (Sections, Synchronization, Barriers)
└── TP5/    MPI Programming (Message Passing Interface)
```

Each TP contains:
- **Source code (.c files)**: Complete implementations of exercises
- **Makefiles**: Build automation for compiling programs
- **RESULTS.md**: Execution results, performance analysis, and answers to assignment questions
- **PDF files**: Original assignment instructions

---

## TP1: Memory Access & Matrix Optimization

**Focus:** Cache optimization, memory access patterns, matrix multiplication techniques

### Exercises:
1. **Impact of Memory Access Stride** - Cache performance analysis
2. **Optimizing Matrix Multiplication** - Compiler optimization effects
3. **Matrix Multiplication per Block** - Cache blocking techniques
4. **Memory Debugging with Valgrind** - Memory leak detection
5. **HPL Benchmark** - High-Performance Linpack

**Technologies:** C, Valgrind, Python (visualization)

---

## TP2: Loop Optimizations & Performance Analysis

**Focus:** Loop unrolling, instruction scheduling, Amdahl's Law, sequential noise

### Exercises:
1. **Loop Optimizations** - Unrolling effects at different optimization levels
2. **Instruction Scheduling** - Pipeline optimization and ILP
3. **Sequential Fraction and Scaling** - Amdahl's Law and Gustafson's Law
4. **Sequential Noise and MatMul** - Impact of sequential operations on parallel speedup

**Technologies:** GCC optimization flags, performance measurement
**Documentation:** [TP2/RESULTS.md](TP2/RESULTS.md)

---

## TP3: OpenMP Fundamentals

**Focus:** Basic parallel programming with OpenMP directives

### Exercises:
1. **Hello World** - Thread management basics
2. **PI Calculation (Parallel)** - Manual parallelization with thread IDs
3. **PI Calculation (Loop)** - Using `parallel for` and reduction
4. **Matrix Multiplication** - Nested loop parallelization with `collapse(2)`
5. **Jacobi Method** - Iterative algorithm with convergence checking

**Key Concepts:** 
- Thread creation and management
- Work distribution (`parallel for`, `collapse`)
- Reduction operations
- Scheduling policies (static, dynamic, guided)

**Documentation:** [TP3/RESULTS.md](TP3/RESULTS.md)

---

## TP4: Advanced OpenMP

**Focus:** Sections, master/single directives, load balancing, barrier synchronization

### Exercises:
1. **Sections Directive** - Array statistics with independent sections
2. **Master vs Single** - Matrix operations demonstrating synchronization differences
3. **Load Balancing** - Three tasks with varying workloads
4. **Barrier Synchronization** - Matrix-vector multiplication with barrier analysis

**Key Concepts:**
- `sections`, `section` directives
- `master` vs `single` directives
- `nowait` clause for optimization
- Explicit `barrier` usage
- Load balancing strategies

**Performance Results:** Benchmarked with 1, 2, 4, 8, and 16 threads
**Documentation:** [TP4/RESULTS.md](TP4/RESULTS.md)

---

## TP5: MPI Programming

**Focus:** Message Passing Interface for distributed computing

### Exercises:
1. **Hello World** - MPI initialization and rank identification
2. **Ping-Pong** - Point-to-point communication with `MPI_Send`/`MPI_Recv`
3. **Collective Operations** - `MPI_Bcast` and `MPI_Reduce` demonstrations
4. **Parallel PI Calculation** - Distributed computation with result aggregation

**Key Concepts:**
- MPI initialization (`MPI_Init`, `MPI_Finalize`)
- Rank and communicator management
- Point-to-point communication
- Collective operations (broadcast, reduce)
- Message tags and status handling

**Environment:** OpenMPI 4.x on WSL2 Ubuntu 24.04
**Documentation:** [TP5/RESULTS.md](TP5/RESULTS.md)

---

## Quick Start Guide

### Prerequisites
- **GCC** with OpenMP support (`-fopenmp`)
- **MPI Implementation** (OpenMPI or MPICH for TP5)
- **Make** build tool
- **WSL2** (for Windows users running MPI programs)

### Building and Running

Each exercise folder contains a Makefile:

```bash
# Navigate to exercise directory
cd TPX/EXN/

# Compile
make

# Run (usually tests multiple thread/process counts)
make run

# Clean build artifacts
make clean
```

### Setting Thread Count (OpenMP)

```bash
export OMP_NUM_THREADS=4
./program_name
```

### Running MPI Programs

```bash
mpirun -np 4 --allow-run-as-root ./program_name
```

---

## Performance Highlights

### TP3 - OpenMP Scaling (Jacobi Method, 500x500 grid)
- **1 thread:** 0.285s (baseline)
- **4 threads:** 0.135s (2.11x speedup)
- **8 threads:** 0.067s (4.26x speedup, 53% efficiency)

### TP4 - Barrier Impact (Matrix-Vector 2000x2000)
- **With barriers:** 0.183s (8 threads)
- **With nowait:** 0.177s (3.3% improvement)

### TP5 - MPI PI Calculation (1M intervals)
- **1 process:** 0.0043s
- **4 processes:** 0.0022s (1.95x speedup)
- **8 processes:** 0.0015s (2.87x speedup)

---

## Key Learnings

1. **Memory Access Patterns Matter** (TP1): Stride affects cache utilization dramatically
2. **Compiler Optimizations** (TP1-2): `-O2` can provide orders of magnitude improvements
3. **Amdahl's Law** (TP2): Sequential fraction limits maximum speedup
4. **OpenMP Simplicity** (TP3): Single directive can parallelize complex loops
5. **Synchronization Cost** (TP4): Barriers and unnecessary waits reduce performance
6. **MPI Scalability** (TP5): Distributed computing enables true multi-node parallelism

---

## Technologies & Tools

- **Languages:** C
- **Parallel APIs:** OpenMP 4.5+, MPI 3.0+
- **Compilers:** GCC 11+, MinGW-w64 (Windows)
- **Profiling:** Valgrind, gprof
- **Visualization:** Python (matplotlib), Jupyter notebooks
- **Build System:** GNU Make

---

## Author

**El hani Mohammed-Rida** - DC_CI2_2026  
Academic Year: 2025-2026

---

## License

Educational use only. Part of Parallel Computing course assignments.