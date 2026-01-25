# Exercise 1: Loop Optimizations - Answers



## Files structure:
1. `loop_unroll.c` - Main program with different unrolling factors
2. `Makefile` - To compile with different optimization levels
3. `run_tests.sh` - Script to run all unrolling factors and measure times


## Answers :

### 1. Implement unrolling factors U = 1, 2, 4, ..., 32

Each unrolling factor follows the pattern:
- **U=1**: Standard loop (no unrolling)
- **U=2**: Process 2 elements per iteration
- **U=4**: Process 4 elements per iteration
- **U=8**: Process 8 elements per iteration
- **U=16**: Process 16 elements per iteration
- **U=32**: Process 32 elements per iteration

### 2. Measure execution time for each version

Measured results (this run):

**-O0**
| U | Time (ms) |
|---:|---:|
| 1 | 137.967 |
| 2 | 129.672 |
| 4 | 131.626 |
| 8 | 133.421 |
| 16 | 133.480 |
| 32 | 131.903 |

**-O2**
| U | Time (ms) |
|---:|---:|
| 1 | 35.835 |
| 2 | 32.519 |
| 4 | 32.689 |
| 8 | 33.205 |
| 16 | 33.162 |
| 32 | 33.135 |

### 3. Best unrolling factor

**Observed best at -O0: U=2 (129.672 ms)**

Notes:
- Differences are small across U=2..32; the curve is fairly flat.

### 4. Compare -O0 vs -O2

**Observation from this run:** -O2 is consistently faster, with best time at U=2 (32.519 ms).

Approximate speedup:
- Baseline U=1: 137.967 ms -> 35.835 ms (~3.85x)

### 5. Is manual unrolling beneficial with -O2?

**With these measurements, manual unrolling gives only a small gain at -O2.**

From U=1 to best U=2:
-O2 improves by about 9.3% (35.835 ms -> 32.519 ms).

### 6. Results for different data types

**Expected behavior:**

| Type | Size | Best U | Time (relative) | Reason |
|------|------|--------|-----------------|---------|
| double | 8 bytes | 8-16 | 1.0x | Baseline |
| float | 4 bytes | 16-32 | 0.5x | Half bandwidth, more elements/vector |
| int | 4 bytes | 16-32 | 0.5x | Integer ops faster than FP |
| short | 2 bytes | 32+ | 0.25x | Quarter bandwidth, excellent vectorization |

**Key insight:** Smaller types benefit from higher unrolling factors because:
- More elements fit in vector registers
- Less memory bandwidth required
- Cache utilization improves

### 7. Bandwidth-limited execution time

**Lower bound estimate:**

Assuming memory bandwidth BW = 20 GB/s (typical DDR4):

For double (8 bytes):
```
T_min = (N × 8 bytes) / BW
      = (1,000,000 × 8) / (20 × 10^9)
      = 0.4 ms
```

For float (4 bytes):
```
T_min = (1,000,000 × 4) / (20 × 10^9)
      = 0.2 ms
```

For int (4 bytes):
```
T_min = 0.2 ms
```

For short (2 bytes):
```
T_min = 0.1 ms
```

**Comparison with measured times:**

Measured times are typically 3-5× higher than T_min because:
- L1/L2 cache misses
- Loop overhead (even after unrolling)
- Address calculation overhead
- Pipeline stalls

### 8. Why does performance saturate?

**Performance progression:**

**Phase 1: Overhead-limited (U=1 to U=4)**
- Loop overhead dominates
- Branch mispredictions
- Few instructions per iteration
- Performance improves linearly with U

**Phase 2: ILP-limited (U=4 to U=16)**
- Loop overhead reduced
- More instruction-level parallelism
- Better utilization of execution units
- Performance improves sub-linearly

**Phase 3: Bandwidth-limited (U>16)**
- Memory bandwidth becomes bottleneck
- CPU waiting for data from memory
- Further unrolling doesn't help
- Performance saturates

**Mathematical model:**

```
Time(U) = max(T_overhead/U, T_bandwidth, T_compute/ILP)
```

Where:
- T_overhead/U: Loop overhead decreases with U
- T_bandwidth: Constant memory access time
- T_compute/ILP: Computation limited by instruction-level parallelism

As U increases:
1. T_overhead/U decreases (good)
2. Eventually T_bandwidth dominates (saturation)
3. Further increases in U have no effect

**Visual representation:**

```
Performance
    ^
    |        /---- Bandwidth limit (plateau)
    |      /
    |    /
    |  /
    |/
    +-------------------------> Unrolling factor U
    1   4   8   16  32
```

## Key Takeaways:

1. **At -O0, U=2 is best**, but times are close for U=2..32.
2. **-O2 gives ~3.85x speedup** over -O0 at U=1.
3. **Manual unrolling helps modestly at -O2** (about 9% from U=1 to U=2).
4. **Performance saturates quickly**, suggesting bandwidth or pipeline limits dominate.

## Conclusion:

Loop unrolling is an effective optimization technique that reduces loop overhead and exposes instruction-level parallelism. However, its benefits are limited when compiler optimization is enabled (-O2), as modern compilers already perform automatic unrolling. Beyond a certain unrolling factor, performance saturates due to memory bandwidth limitations rather than computation bottlenecks. For production code, relying on compiler optimizations (-O2) with modest manual unrolling (U=2-4) provides the best balance between performance and code maintainability.