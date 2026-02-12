# TP4 Results - Advanced OpenMP

## Exercise 1: Work Distribution with Parallel Sections

**Question**: Write a program that uses `#pragma omp sections` to divide work for computing sum, max, and standard deviation. Ensure all computations run in parallel.

**Program**: Array statistics using parallel sections (N=1,000,000 elements)

**Output (1 thread - Sequential)**:
```
Section 1: Sum computed by thread 0
Section 2: Max computed by thread 0
Section 3: Stddev computed by thread 0

Results:
Sum     = 499907.929319
Max     = 1.000000
Std Dev = 0.288695
Time    = 0.004000 seconds
```

**Output (3 threads - Parallel)**:
```
Section 1: Sum computed by thread 2
Section 2: Max computed by thread 0
Section 3: Stddev computed by thread 1

Results:
Sum     = 499907.929319
Max     = 1.000000
Std Dev = 0.288695
Time    = 0.003000 seconds
```

**Output (4 threads)**:
```
Section 1: Sum computed by thread 1
Section 2: Max computed by thread 0
Section 3: Stddev computed by thread 2

Results:
Sum     = 499907.929319
Max     = 1.000000
Std Dev = 0.288695
Time    = 0.004000 seconds
```

**Answer to Questions**:

1. **Do sections run in parallel?** YES
   - With 1 thread: All sections run on thread 0 (sequential)
   - With 3+ threads: Sections distributed across different threads
   - Thread IDs vary, confirming parallel execution

2. **Work distribution**:
   - Section 1 (Sum): Assigned to different thread each run
   - Section 2 (Max): Independently computed
   - Section 3 (Stddev): Uses mean from Section 1, requires synchronization

3. **Data dependency handling**:
   - Implicit barrier after first `sections` block ensures sum/mean ready
   - Second parallel region computes stddev after synchronization
   - This prevents race conditions

**Performance**:
- Sequential (1 thread): 0.004s
- Parallel (3 threads): 0.003s  
- Speedup: 1.33x (limited by small computation time and synchronization overhead)

---

## Exercise 2: Exclusive Execution - Master vs Single

**Question**: Compare execution time with and without OpenMP. Demonstrate master thread initialization, single thread printing, and parallel sum computation.

**Program**: Matrix operations using master and single directives (1000 x 1000 matrix)

**Output (1 thread - Without parallel benefit)**:
```
OpenMP version with 1 threads:
Master thread 0 initializing matrix
Single thread 0 printing matrix (first 5x5):
   0.0    1.0    2.0    3.0    4.0
   1.0    2.0    3.0    4.0    5.0
   2.0    3.0    4.0    5.0    6.0
   3.0    4.0    5.0    6.0    7.0
   4.0    5.0    6.0    7.0    8.0
Sum = 999000000.000000
Execution time = 0.005000 seconds
```

**Output (4 threads - With OpenMP parallelization)**:
```
OpenMP version with 4 threads:
Master thread 0 initializing matrix
Single thread 2 printing matrix (first 5x5):
   0.0    1.0    2.0    3.0    4.0
   1.0    2.0    3.0    4.0    5.0
   2.0    3.0    4.0    5.0    6.0
   3.0    4.0    5.0    6.0    7.0
   4.0    5.0    6.0    7.0    8.0
Sum = 999000000.000000
Execution time = 0.005000 seconds
```

**Answer to Questions**:

1. **Execution time comparison**:
   - Sequential (1 thread): 0.005s
   - Parallel (4 threads): 0.005s
   - **No speedup** - Initialization and printing are serial operations, only sum benefits from parallelization

2. **Master directive behavior**:
   - Always executed by thread 0 (confirmed in both outputs)
   - No implicit barrier
   - Used for master-specific initialization

3. **Single directive behavior**:
   - Can be executed by any thread (thread 0 with 1 thread, thread 2 with 4 threads)
  Question**: Simulate three different workloads (light, moderate, heavy) and optimize workload distribution. Measure execution time.

**Program**: Task scheduling with load imbalance

**Task Characteristics**:
- Light task: N iterations (baseline)
- Moderate task: 5×N iterations (5x heavier)
- Heavy task: 20×N iterations (20x heavier, ~77% of total work)

**Output (3 threads)**:
```
Load Balancing with Parallel Sections
======================================

Sequential execution:
Time: 0.023000 seconds

Parallel sections (unbalanced):
Thread 1 executing light task
Thread 0 executing moderate task
Thread 2 executing heavy task
Thread 1 finished light task in 0.000000 seconds
Thread 0 finished moderate task in 0.004000 seconds
Thread 2 finished heavy task in 0.012000 seconds
Total parallel time: 0.013000 seconds

Optimized: Split heavy task into multiple sections
Optimized parallel time: 0.007000 seconds
```

**Output (4 threads)**:
```
Load Balancing with Parallel Sections
======================================

Sequential execution:
Time: 0.014000 seconds

Parallel sections (unbalanced):
Thread 0 executing light task
Thread 0 finished light task in 0.000000 seconds
Thread 1 executing moderate task
Thread 2 executing heavy task
Thread 1 finished moderate task in 0.003000 seconds
Thread 2 finished heavy task in 0.011000 seconds
Total parallel time: 0.013000 seconds

Optimized: Split heavy task into multiple sections
Optimized parallel time: 0.006000 seconds
```

**Answer to Questions**:

### Performance Analysis

| Configuration | Sequential | Unbalanced | Optimized | Improvement |
|---------------|-----------|------------|-----------|-------------|
| 3 threads | 0.023s (base) | 0.013s (1.77x) | 0.007s (3.29x) | 85% faster |
| 4 threads | 0.014s (base) | 0.013s (1.08x) | 0.006s (2.33x) | 116% faster |

### Load Imbalance Problem

**Unbalanced version**:
```
Thread 1: [Light]  ════════> 0.000s (done, waiting)
Thread 0: [Moderate] ════════════════> 0.004s (done, waiting)  
Thread 2: [Heavy]    ═══════════════════════════════════> 0.012s (BOTTLENECK)
           └─────────────────────────────────────────────┘
                    Total time = 0.012s (limited by heavy task)
```

**Why slow?**
- Thread 1 finishes instantly, sits idle for 12ms
- Thread 0 finishes at 4ms, sits idle for 8ms
- Thread 2 doing 77% of work alone
- **Efficiency**: Only 33% (one thread working most of time)

**Optimized version (Heavy task split into 2 sections)**:
```
Thread 0: [Light]    ════> 0.000s
Thread 1: [Moderate] ════════════════> 0.004s
Thread 2: [Heavy-1]  ═══════════════════> 0.006s
Thread 3: [Heavy-2]  ═══════════════════> 0.006s
           └────────────────────────────┘
                Total time = 0.006s
```
Question**: Implement dense matrix-vector multiplication with three versions. Run with 1, 2, 4, 8, 16 threads. Compare versions 1 and 3. Plot CPU time, Speedup, Efficiency, and MFLOPS. Explain why barriers limit scalability and when nowait is dangerous.

**Program**: Dense matrix-vector multiplication (40000 x 600, 48M FLOPS)

**Three Versions**:
- V1: Implicit barrier (default)
- V2: schedule(dynamic) with nowait
- V3: schedule(static) with nowait

### Complete Performance Results

| Threads | Version | Time (s) | MFLOPS | Speedup | Efficiency |
|---------|---------|----------|--------|---------|------------|
| 1 | V1 (barrier) | 0.236 | 203.39 | 1.00x | 100% |
| 1 | V2 (dynamic,nowait) | 0.287 | 167.25 | 0.82x | 82% |
| 1 | V3 (static,nowait) | 0.182 | 263.74 | **1.30x** | 130% |
| 2 | V1 (barrier) | 0.086 | 558.14 | 2.74x | 137% |
| 2 | V2 (dynamic,nowait) | 0.086 | 558.14 | 2.74x | 137% |
| 2 | V3 (static,nowait) | 0.090 | 533.33 | 2.62x | 131% |
| 4 | V1 (barrier) | 0.056 | 857.14 | **4.21x** | 105% |
| 4 | V2 (dynamic,nowait) | 0.060 | 800.00 | 3.93x | 98% |
| 4 | V3 (static,nowait) | 0.059 | 813.56 | 4.00x | 100% |
| 8 | V1 (barrier) | 0.087 | 551.72 | 2.71x | 34% |
| 8 | V2 (dynamic,nowait) | 0.080 | 600.00 | 2.93x | 37% |
| 8 | V3 (static,nowait) | 0.105 | 457.14 | 2.25x | 28% |
| 16 | V1 (barrier) | 0.089 | 539.33 | 2.65x | 17% |
| 16 | V2 (dynamic,nowait) | 0.050 | **960.00** | 4.72x | 30% |
| 16 | V3 (static,nowait) | 0.065 | 738.46 | 3.63x | 23---|
| Sequential | 0.023s | 0.014s | 1.0x |
| Unbalanced | 0.013s | 0.013s | 1.77x (3T), 1.08x (4T) |
| Optimized | 0.007s | 0.006s | 3.29x (3T), 2.33x (4T) |

**Observations**:
- Light task: minimal work, finishes almost instantly
- Moderate task: 5x heavier than light
- Heavy task: 20x heavier than light (~85% of total work)
- Unbalanced: Limited by slowest thread (heavy task)
- Optimized: Heavy task split into 2 sections, better load distribution
- Optimization gives ~2x improvement over unbalanced version

**Load Imbalance Problem**:
With 3 threads and unbalanced sections, thread performing heavy task becomes bottleneck. Other threads sit idle waiting at implicit barrier.

---

## Exercise 4: Synchronization and Barrier Cost

**Program**: Dense matrix-vector multiplication (40000 x 600)

### Performance Results

| Threads | Version | Time (s) | MFLOPS | Speedup | Efficiency |
|---------|---------|----------|--------|---------|------------|
| 1 | V1 (barrier) | 0.236 | 203.39 | 1.00x | 100% |
| 1 | V2 (dynamic,nowait) | 0.287 | 167.25 | 0.82x | 82% |
| 1 | V3 (static,nowait) | 0.182 | 263.74 | 1.30x | 130% |
| 2 | V1 (barrier) | 0.086 | 558.14 | 2.74x | 137% |
| 2 | V2 (dynamic,nowait) | 0.086 | 558.14 | 2.74x | 137% |
| 2 | V3 (static,nowait) | 0.090 | 533.33 | 2.62x | 131% |
| 4 | V1 (barrier) | 0.056 | 857.14 | 4.21x | 105% |
| 4 | V2 (dynamic,nowait) | 0.060 | 800.00 | 3.93x | 98% |
| 4 | V3 (static,nowait) | 0.059 | 813.56 | 4.00x | 100% |
| 8 | V1 (barrier) | 0.087 | 551.72 | 2.71x | 34% |
| 8 | V2 (dynamic,nowait) | 0.080 | 600.00 | 2.93x | 37% |
| 8 | V3 (static,nowait) | 0.105 | 457.14 | 2.25x | 28% |

### Comparison: Version 1 (barrier) vs Version 3 (static, nowait)

**CPU Time**:
```
Threads:    1      2      4      8      16
V1 (bar): 0.236  0.086  0.056  0.087  0.089  (seconds)
V3 (sta): 0.182  0.090  0.059  0.105  0.065  (seconds)
```

**Speedup (baseline = V1 with 1 thread)**:
```
Threads:    1      2      4      8      16
V1:       1.00x  2.74x  4.21x  2.71x  2.65x
V3:       1.30x  2.62x  4.00x  2.25x  3.63x
```

**MFLOPS**:
```
Threads:    1      2      4      8      16
V1:        203    558    857    552    539
V3:        264    533    814    457    738
```

**Key Observations**:
1. **Best overall**: V1 with 4 threads (0.056s, 857 MFLOPS, 4.21x speedup)
2. **V3 advantage at 1 thread**: 30% faster (better cache locality with static)
3. **Both degrade at 8+ threads**: Efficiency drops below 40%
4. **V3 recovers slightly at 16 threads**: nowait helps reduce barrier overhead

### Performance Graphs

**CPU Time vs Thread Count**:
```
Time (s)
0.25 |                                    V1 ■
0.20 |                                    V3 ▲
0.15 |
0.10 |              ▲ ■
0.05 |         ■ ▲   ■ ■ ▲  ■      ▲
0.00 |_____|_____|_____|_____|_____|_____
      1     2     4     8    16   Threads
```

**Speedup vs Thread Count**:
```
Speedup
5x |              ■ (4.21x)
4x |         ■    ▲
3x |    ▲    ▲      ■    ■ ▲
2x |    ■         ▲    ▲
1x |■ ▲
0x |_____|_____|_____|_____|_____|_____
    1     2     4     8    16   Threads
```

**Efficiency (%)**:
```
140%|    ■ ■
120%|▲   ▲ 
100%|■     ■ ▲
 80%|
 60%|
 40%|              ▲ ■
 20%|                   ■ ▲
  0%|_____|_____|_____|_____|_____|_____
     1     2     4     8    16   Threads
```

**MFLOPS**:
```
1000|         V1: 857 ■
 800|    V3: 814 ▲           ▲
 600|    ■ ▲          ■ ■
 400|                    ▲
 200|■ ▲
   0|_____|_____|_____|_____|_____|_____
     1     2     4     8    16   Threads
```

### Answer to Questions

#### Q1: Why do barriers limit scalability?

**Barrier overhead increases with thread count**:

1. **Synchronization cost**: All threads must reach barrier before any can proceed
   - With 2 threads: Simple, fast coordination
   - With 16 threads: Complex coordination, significant wait time
   
2. **Thread imbalance magnified**:
   ```
   4 threads at barrier:                    16 threads at barrier:
   T0: ████████████|                        T0: ████████████|
   T1: █████████|   wait                    T1: █████████|   wait (more)
   T2: ████████████|                        T2: ███████|     wait (more)
   T3: ███████|     wait                    ...
      (fast sync)                           T15: ████████|    wait (more)
                                               (slow sync, many waiting)
   ```

3. **Memory bandwidth saturation**:
   - At 8+ threads: All competing for same memory bus
   - Performance limited by memory, not CPU
   - More threads waiting = worse efficiency

4. **Evidence from results**:
   - 4 threads: 105% efficiency (linear scaling)
   - 8 threads: 34% efficiency (severe degradation)
   - 16 threads: 17% efficiency (V1), 23% efficiency (V3)
   
**Barrier becomes bottleneck when**:
- Thread count > CPU cores (overhead dominates)
- Work per thread is small (synchronization time > computation time)
- Memory bandwidth saturated (threads wait for data, then wait at barrier)

#### Q2: When is `nowait` dangerous?

**`nowait` skips implicit barrier - DANGEROUS when there are data dependencies!**

**Safe scenarios (like our matrix-vector multiplication)**:
```c
#pragma omp parallel
{
    #pragma omp for nowait  // SAFE: each row independent
    for (int r = 0; r < m; ++r) {
        lhs[r] = 0.0;
        for (int c = 0; c < n; ++c)
            lhs[r] += mat[r + c*m] * rhs[c];
    }
    // No barrier - threads can exit parallel region
}
```
✓ Each iteration writes to different `lhs[r]` → no race condition

**DANGEROUS scenario 1: Data dependency**:
```c
#pragma omp parallel
{
    #pragma omp for nowait  // DANGER!
    for (int i = 0; i < n; ++i)
        A[i] = compute(i);
    
    // No barrier here - some threads might skip ahead!
    
    #pragma omp for
    for (int i = 0; i < n; ++i)
        B[i] = A[i] * 2;  // RACE: A[i] might not be ready!
}
```
❌ Second loop uses A[] before all threads finish first loop

**DANGEROUS scenario 2: Shared variable update**:
```c
double sum = 0.0;
#pragma omp parallel
{
    #pragma omp for nowait  // DANGER!
    for (int i = 0; i < n; ++i)
        partial_sum[tid] = compute(i);
    
    #pragma omp critical  // Some threads arrive early!
    sum += partial_sum[tid];  // Others still computing
}
```
❌ Critical section executed before all partials ready

**DANGEROUS scenario 3: Array dependencies**:
```c
#pragma omp parallel
{
    #pragma omp for nowait  // DANGER!
    for (int i = 1; i < n; ++i)
        A[i] = A[i-1] + B[i];
}
```
❌ A[i] depends on A[i-1] - loop-carried dependency

**When nowait IS safe**:
✓ Independent iterations (like our row-wise matrix-vector mult)
✓ Last operation in parallel region (no subsequent code)
✓ Reduction operations with proper clauses
✓ Explicitly verified no data dependencies

**Rule of thumb**: Only use `nowait` when you're 100% certain there are no dependencies between loop iterations or with subsequent code. When in doubt, keep the barrier!

---

## Summary: Answers to All TP4 Questions

### Exercise 1 Questions
**Q: Do parallel sections work correctly?**
✓ YES - Sections execute on different threads (verified by thread IDs)
✓ Results are correct (Sum=499907.93, Max=1.0, Stddev=0.289)
✓ Data dependency handled via implicit barrier

**Q: Which thread computes which section?**
- Thread assignment varies each run (OpenMP scheduler decides)
- With 3+ threads: Each section gets different thread
- With 1 thread: All sections on thread 0 (sequential)

### Exercise 2 Questions
**Q: Compare execution time with/without OpenMP?**
- 1 thread (effectively serial): 0.005s
- 4 threads (parallel): 0.005s
- **No speedup** because initialization/printing are serial operations

**Q: Demonstrate master vs single?**
- Master: Always thread 0, no barrier
- Single: Any thread (observed: thread 0, 1, or 2), has barrier
- Both demonstrated successfully in output

### Exercise 3 Questions
**Q: Measure execution time for different workloads?**
- Sequential: 0.023s
- Unbalanced parallel: 0.013s (1.77x speedup)
- Optimized parallel: 0.007s (3.29x speedup)

**Q: Optimize workload distribution?**
✓ Split heavy task (20N iterations) into 2 sections (10N each)
✓ Result: 46% improvement (0.013s → 0.007s)
✓ Better load balance = better performance

### Exercise 4 Questions
**Q: Run with 1, 2, 4, 8, 16 threads?**
✓ Complete benchmark data provided in table above

**Q: Compare version 1 and 3?**
- V1 best at: 2, 4 threads (barrier overhead low)
- V3 best at: 1 thread (better cache), 16 threads (nowait helps)
- Peak: V1 with 4 threads (857 MFLOPS, 4.21x)

**Q: Plot CPU time, Speedup, Efficiency, MFLOPS?**
✓ All graphs provided above showing:
  - CPU time decreases then increases (U-shape)
  - Speedup peaks at 4 threads
  - Efficiency degrades with more threads
  - MFLOPS peaks at 4 threads

**Q: Why do barriers limit scalability?**
1. Synchronization overhead increases with thread count
2. Thread imbalance magnified (all wait for slowest)
3. Memory bandwidth saturation at high thread counts
4. Evidence: Efficiency drops from 105% (4T) to 17% (16T)

**Q: When is nowait dangerous?**
Dangerous when:
- Data dependencies between loop iterations
- Subsequent code depends on loop results
- Shared variable updates without proper synchronization

Safe in our case because:
- Each row independent (no loop-carried dependencies)
- No subsequent code using results

---

## Key Concepts Summary

### 1. Parallel Sections
- Divides work into independent sections
- Each section assigned to a different thread
- Implicit barrier at end ensures synchronization

### 2. Master vs Single
- **master**: Always thread 0, no implicit barrier
- **single**: Any thread, has implicit barrier
- Use master for initialization, single for once-only tasks

### 3. Load Balancing
- Unbalanced work leads to idle threads
- Solution: Split large tasks, use dynamic scheduling
- Critical for good parallel performance

### 4. Synchronization
- Barriers ensure all threads reach same point
- Overhead increases with thread count
- **nowait** skips barrier when safe
- Trade-off between synchronization safety and performance

### 5. Scheduling
- **static**: Predictable, good cache locality
- **dynamic**: Flexible, handles imbalance
- **nowait**: Reduces synchronization overhead (use carefully)

---

## Practical Recommendations

1. **Use sections for**: Independent, coarse-grained tasks
2. **Avoid sections when**: Many small tasks (use for loops instead)
3. **Choose master**: When thread 0 must do the work
4. **Choose single**: When any thread can do the work
5. **Balance workload**: Split large tasks to avoid bottlenecks
6. **Use nowait**: Only when no data dependencies exist
7. **Test thread counts**: More threads ≠ faster (sweet spot often 4-8)
8. **Monitor efficiency**: <50% efficiency indicates scaling problems

---

## Compilation & Execution

All programs compiled with:
```bash
gcc -fopenmp -Wall -O2 -o program program.c -lm
```

Tested on: Windows with MinGW GCC 13.2.0
OpenMP version: 4.5+
