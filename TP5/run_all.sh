#!/bin/bash
# Run this script in WSL to compile and execute all TP5 exercises

echo "========================================"
echo "TP5 - MPI Exercises"
echo "========================================"
echo ""

# Check if mpicc is installed
if ! command -v mpicc &> /dev/null; then
    echo "Installing MPICH..."
    sudo apt-get update
    sudo apt-get install -y mpich
fi

# Get the Windows path converted to WSL path
BASEDIR="/mnt/c/Users/hanir/Desktop/S4/Parallel_computing/Parallel_Computing_TPs/Assignments_DC_CI2_2026_ELHANI/TP5"

cd "$BASEDIR"

echo "========================================"
echo "Exercise 1: Hello World"
echo "========================================"
cd EX1
mpicc -o hello_world Hello_world.c -Wall -O2
echo "Running with 4 processes:"
mpirun -np 4 ./hello_world
echo ""
echo "Running with 2 processes:"
mpirun -np 2 ./hello_world
echo ""

echo "========================================"
echo "Exercise 2: Ping-Pong Communication"
echo "========================================"
cd ../EX2
mpicc -o ping_pong ping_pong.c -Wall -O2
echo "Running with 2 processes:"
mpirun -np 2 ./ping_pong
echo ""
echo "Running with 4 processes:"
mpirun -np 4 ./ping_pong
echo ""

echo "========================================"
echo "Exercise 3: Collective Operations"
echo "========================================"
cd ../EX3
mpicc -o collective collective.c -Wall -O2
echo "Running with 4 processes:"
mpirun -np 4 ./collective
echo ""
echo "Running with 8 processes:"
mpirun -np 8 ./collective
echo ""

echo "========================================"
echo "Exercise 4: PI Calculation"
echo "========================================"
cd ../EX4
mpicc -o pi_mpi pi_mpi.c -Wall -O2
echo "Running with 1 process:"
mpirun -np 1 ./pi_mpi
echo ""
echo "Running with 2 processes:"
mpirun -np 2 ./pi_mpi
echo ""
echo "Running with 4 processes:"
mpirun -np 4 ./pi_mpi
echo ""
echo "Running with 8 processes:"
mpirun -np 8 ./pi_mpi
echo ""

echo "========================================"
echo "All exercises completed!"
echo "========================================"
