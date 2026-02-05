# TP3 - OpenMP Execution Results

## Exercise 1: Hello World

```bash
Running with 4 threads:
Hello from the rank 0 thread
Hello from the rank 3 thread
Hello from the rank 2 thread
Hello from the rank 1 thread
Parallel execution of hello_world with 4 threads

Running with 2 threads:
Hello from the rank 0 thread
Hello from the rank 1 thread
Parallel execution of hello_world with 2 threads
```

## Exercise 2: PI Calculation (Parallel Construct)

Manual parallelization using thread ID-based striding:

```bash
Running with 1 thread:
PI = 3.141592653598162
CPU time = 0.000182 seconds

Running with 4 threads:
PI = 3.141592653598116
CPU time = 0.000341 seconds

Running with 8 threads:
PI = 3.141592653598135
CPU time = 0.001108 seconds
```

## Exercise 3: PI Calculation (Loop Construct)

Using `#pragma omp parallel for` with reduction:

```bash
Running with 1 thread:
PI = 3.141592653598162
CPU time = 0.000482 seconds

Running with 4 threads:
PI = 3.141592653598127
CPU time = 0.001281 seconds

Running with 8 threads:
PI = 3.141592653598126
CPU time = 0.001333 seconds
```

**Note:** Exercise 3 (parallel for) is simpler to implement than Exercise 2 (manual parallelization), requiring only one line added to parallelize.

## Exercise 4: Matrix Multiplication

Parallel matrix multiplication using `collapse(2)` directive with different scheduling policies (static, dynamic, guided).

Results available in `EX4/benchmark_results.txt`.

## Exercise 5: Jacobi Method

Parallel implementation of Jacobi iterative method for solving linear systems using 2D grid (500x500, 500 iterations):

**1 Thread:**
```
Execution time: 0.284518 seconds
Iterations per second: 1757.36
```

**4 Threads:**
```
Execution time: 0.134857 seconds
Iterations per second: 3707.63
Speedup: 2.11x
```

**8 Threads:**
```
Execution time: 0.066847 seconds
Iterations per second: 7479.80
Speedup: 4.26x
```

**Key Concepts Demonstrated:**
- `collapse(2)` directive for nested loop parallelization
- `reduction(max:...)` for finding maximum convergence difference
- Iterative algorithm parallelization with convergence checking
- Good scaling efficiency (53% at 8 threads)
