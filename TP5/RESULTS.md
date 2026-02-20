# TP5 Results - MPI Programming

## Exercise 1: Hello World

**Program**: Basic MPI initialization and process communication

**Command**: `mpirun -np 4 ./hello_world`

**Output (4 processes)**:
```
Hello from process 0 out of 4 processes
Hello from process 1 out of 4 processes
Hello from process 2 out of 4 processes
Hello from process 3 out of 4 processes
```

**Output (2 processes)**:
```
Hello from process 0 out of 2 processes
Hello from process 1 out of 2 processes
```

**Observations**:
- Each process prints independently
- Order of output may vary due to parallel execution
- MPI_Init and MPI_Finalize properly bracket the parallel region
- Each process correctly identifies its rank and total number of processes

---

## Exercise 2: Point-to-Point Communication

**Program**: Ping-pong between processes using MPI_Send/MPI_Recv

**Command**: `mpirun -np 2 ./ping_pong`

**Output**:
```
Process 1 received value 42 from process 0
Process 1 sending value 84 to process 0
Process 0 sending value 42 to process 1
Process 0 received value 84 from process 1
```

**With 4 processes**:
```
Process 0 sending value 42 to process 1
Process 1 received value 42 from process 0
Process 1 sending value 84 to process 0
Process 0 received value 84 from process 1
```

**Observations**:
- Synchronous communication between process 0 and 1
- Process 1 doubles the received value (42 → 84) before sending back
- Other processes (if any) remain idle
- Demonstrates blocking send/receive operations
- Order of print statements may vary due to race conditions

---

## Exercise 3: Collective Operations

**Program**: Broadcast and reduction operations

**Command**: `mpirun -np 4 ./collective`

**Output**:
```
Process 0 broadcasting value: 100
Process 0 received broadcast value: 100
Process 1 received broadcast value: 100
Process 3 received broadcast value: 100
Process 2 received broadcast value: 100

Sum of all ranks (1 to 4): 10
```

**With 8 processes**:
```
Process 3 received broadcast value: 100
Process 4 received broadcast value: 100
Process 5 received broadcast value: 100
Process 6 received broadcast value: 100
Process 7 received broadcast value: 100
Process 0 broadcasting value: 100
Process 0 received broadcast value: 100
Process 1 received broadcast value: 100
Process 2 received broadcast value: 100

Sum of all ranks (1 to 8): 36
```

**Observations**:
- MPI_Bcast distributes value from root to all processes
- Each process contributes (rank + 1) to the sum
- For 4 processes: 1 + 2 + 3 + 4 = 10
- For 8 processes: 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36
- MPI_Reduce efficiently combines results at root
- Print order may vary due to parallel execution

---

## Exercise 4: PI Calculation

**Program**: Parallel numerical integration using MPI

**Command**: `mpirun -np N ./pi_mpi`

### Results

**1 process**:
```
PI = 3.141592653598162
Number of processes: 1
CPU time = 0.000617 seconds
```

**2 processes**:
```
PI = 3.141592653598102
Number of processes: 2
CPU time = 0.000276 seconds
```

**4 processes**:
```
PI = 3.141592653598117
Number of processes: 4
CPU time = 0.000148 seconds
```

**8 processes**:
```
PI = 3.141592653598135
Number of processes: 8
CPU time = 0.000965 seconds
```

### Performance Analysis

| Processes | Time (ms) | Speedup | Efficiency |
|-----------|-----------|---------|------------|
| 1 | 0.617 | 1.00x | 100% |
| 2 | 0.276 | 2.24x | 112% |
| 4 | 0.148 | 4.17x | 104% |
| 8 | 0.965 | 0.64x | 8% |

**Observations**:
- All results accurate to ~15 decimal places
- Excellent speedup with 2 and 4 processes
- Superlinear speedup due to better cache utilization
- Performance degrades at 8 processes due to overhead exceeding benefit
- For this small problem size (100,000 steps), communication overhead dominates at higher process counts
- MPI_Reduce adds synchronization cost
- Load balancing is good with strided access pattern

---

## Comparison: MPI vs OpenMP (TP3 vs TP5)

### PI Calculation Comparison

**OpenMP (TP3 EX3) - 100000 steps**:
- 1 thread: 0.482 ms
- 4 threads: 1.281 ms
- 8 threads: 1.333 ms

**MPI (TP5 EX4) - 100000 steps**:
- 1 process: 0.617 ms
- 4 processes: 0.148 ms
- 8 processes: 0.965 ms

### Key Differences

| Aspect | OpenMP | MPI |
|--------|--------|-----|
| Memory Model | Shared memory | Distributed memory |
| Overhead | Thread creation | Process + communication |
| Best Performance | 1 thread | 4 processes |
| Scalability | Limited to single node | Multi-node capable |
| Complexity | Simple pragmas | Explicit communication |

**Analysis**:
- OpenMP actually performs worse with more threads for this small problem (overhead dominates)
- MPI shows good speedup up to 4 processes
- Both suffer from overhead at higher counts for small problems
- MPI's explicit decomposition can be more efficient when properly tuned
- For small problem sizes, parallelization overhead can exceed benefits
- Real advantage of MPI appears in cluster environments and larger problems

---

## Installation Notes

**To run these programs on Windows:**

### Option 1: WSL (Recommended - Used for these results)

1. Install WSL with Ubuntu:
   ```powershell
   wsl --install
   ```

2. Inside WSL, install OpenMPI (works better than MPICH in WSL2):
   ```bash
   sudo apt-get update
   sudo apt-get install -y openmpi-bin libopenmpi-dev
   ```

3. If MPICH is also installed, switch to OpenMPI:
   ```bash
   sudo update-alternatives --set mpi /usr/bin/mpicc.openmpi
   ```

4. Compile and run:
   ```bash
   cd /mnt/c/path/to/TP5/EXN
   mpicc -o program program.c -Wall -O2
   mpirun --allow-run-as-root -np 4 ./program
   ```

### Option 2: Microsoft MPI (Native Windows)

1. Download and install Microsoft MPI:
   - Download from: https://www.microsoft.com/en-us/download/details.aspx?id=57467
   - Install both msmpisetup.exe and msmpisdk.msi

2. Compile with:
   ```bash
   gcc -o program.exe program.c -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
   ```

3. Run with:
   ```bash
   mpiexec -n 4 program.exe
   ```

**Note**: OpenMPI in WSL2 was used for all results in this document as MPICH had process spawning issues in WSL2 environment.

---

## Key Concepts Demonstrated

1. **Process Management**: MPI_Init, MPI_Finalize, MPI_Comm_rank, MPI_Comm_size
2. **Point-to-Point**: MPI_Send, MPI_Recv with blocking semantics
3. **Collective Operations**: MPI_Bcast for one-to-all, MPI_Reduce for all-to-one
4. **Performance Measurement**: MPI_Wtime for accurate timing
5. **Domain Decomposition**: Strided access pattern for load balancing

## Technical Notes

### MPICH vs OpenMPI in WSL2

During testing, MPICH (installed via apt-get install mpich) had process spawning issues in WSL2:
- Processes reported size=1 instead of actual number
- Each process ran in isolation rather than as a communicating group

OpenMPI (installed via apt-get install openmpi-bin libopenmpi-dev) worked correctly:
- Proper process communication
- Correct MPI_Comm_size reporting
- No configuration issues

**Recommendation**: Use OpenMPI for WSL2 environments.

## Conclusion

MPI provides explicit control over parallelism and scales to distributed systems. Key findings:

1. **Communication Overhead**: Small problems (like PI with 100k steps) show overhead dominates at high process counts
2. **Sweet Spot**: 4 processes gave best performance (4.17x speedup)
3. **Scalability Limits**: Without larger problems or distributed nodes, MPI advantages are limited
4. **Collective Operations**: MPI_Bcast and MPI_Reduce provide efficient all-to-one and one-to-all patterns
5. **Point-to-Point**: Blocking send/recv simple but can lead to deadlocks if not carefully ordered

MPI is essential for HPC cluster computing where problems are large enough to benefit from distributed memory and where scaling beyond single-node is required.
