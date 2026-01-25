#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Amdahl's Law: Calculate maximum speedup
// S(p) = 1 / (f + (1-f)/p)
// where f is the sequential fraction and p is the number of processors

double amdahl_speedup(double f, int p) {
    return 1.0 / (f + (1.0 - f) / (double)p);
}

// Gustafson's Law: Calculate scaled speedup
// S(p) = f + p * (1-f)
double gustafson_speedup(double f, int p) {
    return f + (double)p * (1.0 - f);
}

void print_table(const char *title, double (*speedup_func)(double, int)) {
    int processors[] = {1, 2, 4, 8, 16, 32, 64, 128};
    double fractions[] = {0.01, 0.05, 0.10, 0.25, 0.50};
    
    printf("\n%s\n", title);
    printf("========================================\n");
    printf("%-10s", "f \\ p");
    for (int i = 0; i < 8; i++) {
        printf("%8d", processors[i]);
    }
    printf("\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%-10.2f", fractions[i]);
        for (int j = 0; j < 8; j++) {
            double speedup = speedup_func(fractions[i], processors[j]);
            printf("%8.2f", speedup);
        }
        printf("\n");
    }
}

void analyze_efficiency(void) {
    printf("\n\nEfficiency Analysis (Amdahl's Law)\n");
    printf("========================================\n");
    printf("Efficiency = Speedup / Number of Processors\n\n");
    
    int processors[] = {1, 2, 4, 8, 16, 32, 64};
    double fractions[] = {0.01, 0.10, 0.25, 0.50};
    
    printf("%-10s", "f \\ p");
    for (int i = 0; i < 7; i++) {
        printf("%8d", processors[i]);
    }
    printf("\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 4; i++) {
        printf("%-10.2f", fractions[i]);
        for (int j = 0; j < 7; j++) {
            double speedup = amdahl_speedup(fractions[i], processors[j]);
            double efficiency = speedup / (double)processors[j] * 100.0;
            printf("%7.1f%%", efficiency);
        }
        printf("\n");
    }
}

void plot_speedup_curves(void) {
    printf("\n\nSpeedup vs Number of Processors\n");
    printf("========================================\n");
    
    double fractions[] = {0.01, 0.05, 0.10, 0.25, 0.50};
    int max_p = 128;
    
    printf("\nFor different sequential fractions (f):\n");
    for (int i = 0; i < 5; i++) {
        double f = fractions[i];
        printf("\nf = %.2f:\n", f);
        printf("  p=%d: Speedup=%.2f, Max theoretical=%.2f\n", 
               1, amdahl_speedup(f, 1), 1.0 / f);
        printf("  p=%d: Speedup=%.2f\n", 2, amdahl_speedup(f, 2));
        printf("  p=%d: Speedup=%.2f\n", 8, amdahl_speedup(f, 8));
        printf("  p=%d: Speedup=%.2f\n", 32, amdahl_speedup(f, 32));
        printf("  p=%d: Speedup=%.2f\n", max_p, amdahl_speedup(f, max_p));
    }
}

void practical_example(void) {
    printf("\n\nPractical Example\n");
    printf("========================================\n");
    
    // Example: A program with 95% parallelizable code
    double f = 0.05;  // 5% sequential
    
    printf("Scenario: Program with 5%% sequential fraction\n");
    printf("  95%% of the code can be parallelized\n");
    printf("  5%% must run sequentially\n\n");
    
    printf("Performance predictions:\n");
    int processors[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    
    for (int i = 0; i < 11; i++) {
        int p = processors[i];
        double speedup = amdahl_speedup(f, p);
        double efficiency = speedup / (double)p * 100.0;
        
        printf("  %4d processors: Speedup = %6.2f, Efficiency = %5.1f%%\n", 
               p, speedup, efficiency);
    }
    
    printf("\nObservations:\n");
    printf("  - Maximum theoretical speedup: %.2f\n", 1.0 / f);
    printf("  - Beyond %d processors, speedup becomes marginal\n", 32);
    printf("  - Efficiency drops below 50%% at %d processors\n", 
           (int)(1.0 / (2.0 * f) + 0.5));
}

int main(void) {
    printf("=================================================\n");
    printf("Exercise 3: Sequential Fraction and Scaling\n");
    printf("=================================================\n");
    
    // Amdahl's Law analysis
    print_table("Amdahl's Law Speedup Table", amdahl_speedup);
    
    // Gustafson's Law analysis
    print_table("\nGustafson's Law Speedup Table", gustafson_speedup);
    
    // Efficiency analysis
    analyze_efficiency();
    
    // Speedup curves
    plot_speedup_curves();
    
    // Practical example
    practical_example();
    
    printf("\n\nKey Insights:\n");
    printf("========================================\n");
    printf("1. Amdahl's Law shows that even small sequential fractions\n");
    printf("   severely limit maximum speedup.\n\n");
    printf("2. With f=0.05 (5%% sequential), maximum speedup is only 20x,\n");
    printf("   regardless of the number of processors.\n\n");
    printf("3. Efficiency decreases as the number of processors increases,\n");
    printf("   due to the fixed sequential portion.\n\n");
    printf("4. Gustafson's Law provides a more optimistic view by assuming\n");
    printf("   the problem size scales with the number of processors.\n\n");
    
    return 0;
}
