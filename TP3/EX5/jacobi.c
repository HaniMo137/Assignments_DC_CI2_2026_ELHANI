#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000        // Grid size
#define MAX_ITER 1000 // Maximum iterations
#define TOLERANCE 1e-6 // Convergence criterion

void initialize_grid(double **grid, int n) {
    // Initialize boundaries and interior points
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == n-1 || j == 0 || j == n-1) {
                // Boundary conditions
                grid[i][j] = 100.0; 
            } else {
                // Interior points
                grid[i][j] = 0.0;
            }
        }
    }
}

double jacobi_iteration(double **grid, double **new_grid, int n) {
    double max_diff = 0.0;
    
    #pragma omp parallel for collapse(2) reduction(max:max_diff) schedule(static)
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++) {
            // Jacobi update: average of 4 neighbors
            new_grid[i][j] = 0.25 * (grid[i-1][j] + grid[i+1][j] + 
                                     grid[i][j-1] + grid[i][j+1]);
            
            // Track maximum difference for convergence
            double diff = fabs(new_grid[i][j] - grid[i][j]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }
    
    return max_diff;
}

void copy_grid(double **src, double **dst, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    int n = N;
    int max_iterations = MAX_ITER;
    double tolerance = TOLERANCE;
    
    // Parse command-line arguments
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) max_iterations = atoi(argv[2]);
    
    // Allocate grids
    double **grid = (double **)malloc(n * sizeof(double *));
    double **new_grid = (double **)malloc(n * sizeof(double *));
    
    for (int i = 0; i < n; i++) {
        grid[i] = (double *)malloc(n * sizeof(double));
        new_grid[i] = (double *)malloc(n * sizeof(double));
    }
    
    // Initialize
    initialize_grid(grid, n);
    initialize_grid(new_grid, n);
    
    int num_threads = omp_get_max_threads();
    printf("Running Jacobi method with %d threads\n", num_threads);
    printf("Grid size: %dx%d, Max iterations: %d, Tolerance: %.2e\n\n", 
           n, n, max_iterations, tolerance);
    
    // Main iteration loop
    double start_time = omp_get_wtime();
    int iter;
    double max_diff;
    
    for (iter = 0; iter < max_iterations; iter++) {
        max_diff = jacobi_iteration(grid, new_grid, n);
        
        // Copy new values to grid
        copy_grid(new_grid, grid, n);
        
        // Check convergence
        if (max_diff < tolerance) {
            break;
        }
        
        // Print progress every 100 iterations
        if ((iter + 1) % 100 == 0) {
            printf("Iteration %4d: max_diff = %.6e\n", iter + 1, max_diff);
        }
    }
    
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    
    // Print results
    printf("\n=== Results ===\n");
    if (iter < max_iterations) {
        printf("Converged after %d iterations\n", iter + 1);
    } else {
        printf("Did not converge after %d iterations\n", max_iterations);
    }
    printf("Final max difference: %.6e\n", max_diff);
    printf("Execution time: %.6f seconds\n", elapsed_time);
    printf("Iterations per second: %.2f\n", iter / elapsed_time);
    
    // Print a few interior points for verification
    printf("\nSample interior points:\n");
    printf("  grid[%d][%d] = %.6f\n", n/4, n/4, grid[n/4][n/4]);
    printf("  grid[%d][%d] = %.6f\n", n/2, n/2, grid[n/2][n/2]);
    printf("  grid[%d][%d] = %.6f\n", 3*n/4, 3*n/4, grid[3*n/4][3*n/4]);
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(grid[i]);
        free(new_grid[i]);
    }
    free(grid);
    free(new_grid);
    
    return 0;
}
