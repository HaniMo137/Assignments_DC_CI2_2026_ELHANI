# TP2 Benchmark Results

## Exercise 1: Loop Optimizations

**-O0 Results (double type)**
| U | Time (ms) |
|---|-----------|
| 1 | 137.97 |
| 2 | 129.67 (best) |
| 4 | 131.63 |
| 8 | 133.42 |
| 16 | 133.48 |
| 32 | 131.90 |

**-O2 Results (double type)**
| U | Time (ms) |
|---|-----------|
| 1 | 35.84 |
| 2 | 32.52 (best) |
| 4 | 32.69 |
| 8 | 33.21 |
| 16 | 33.16 |
| 32 | 33.14 |

Best: U=2 for both. Compiler speedup: 3.85x. Manual unrolling at -O2: 9% improvement.

---

## Exercise 2: Instruction Scheduling

**-O0**
- Sequential: 83.23 ms
- Independent: 9.61 ms (8.66x speedup)
- Mixed: 14.00 ms (5.94x speedup)

**-O2**
- Sequential: 30.22 ms
- Independent: 4.57 ms (6.62x speedup)
- Mixed: 5.61 ms (5.39x speedup)

Breaking dependencies gives large speedup even at -O2.

---

## Exercise 3: Amdahl's Law

**Max Speedup by Sequential Fraction**
| f | Max | 8 procs | 32 procs |
|---|-----|---------|----------|
| 1% | 100x | 7.48x | 24.43x |
| 5% | 20x | 5.93x | 12.55x |
| 10% | 10x | 4.71x | 7.80x |
| 25% | 4x | 2.91x | 3.66x |

5% sequential code limits speedup to 20x maximum.

---

## Exercise 4: Sequential Noise

**256×256 matrix, 3 iterations**

-O0: Matmul 139.5 ms, with 5000 noise: 143.15 ms total
-O2: Matmul 45.09 ms, with 5000 noise: 38.54 ms total

Compiler gives 3.09x speedup. Sequential overhead becomes more significant with optimization.
