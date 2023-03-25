#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define M 1000
#define N 1000
#define K 1000

int A[M][K];
int B[K][N];
int C[M][N];

int main() {
// Initialize matrices A and B
for (int i = 0; i < M; i++) {
for (int j = 0; j < K; j++) {
A[i][j] = rand() % 10;
  
}
}
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < N; j++) {
        B[i][j] = rand() % 10;
    }
}

// Measure time taken by sequential algorithm
struct timeval start_time, end_time;
gettimeofday(&start_time, NULL);

for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < K; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}

gettimeofday(&end_time, NULL);
double seq_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

printf("Sequential algorithm took %f seconds\n", seq_time);

// Measure time taken by parallel algorithm
gettimeofday(&start_time, NULL);

#pragma omp parallel for
for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < K; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}

gettimeofday(&end_time, NULL);
double par_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

printf("Parallel algorithm took %f seconds\n", par_time);

// Compute performance metrics
double speedup = seq_time / par_time;
double efficiency = speedup / omp_get_max_threads();
printf("Speedup factor: %f\n", speedup);
printf("Efficiency: %f\n", efficiency);

return 0;
