/*
PA5: Cache Locality
 This program compares a cache-friendly algorithm to a non cache-friendly one for matrix multiplication
Author: Omer Yurekli :yureklio@bc.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MIN_DIM_POWER 3
#define MAX_DIM_POWER 10
#define MAX_VALUE 20
#define FALSE 0
#define TRUE 1

void init(const int dim, int * const m) {
    for (int i = 0; i < dim * dim; ++i) {
        m[i] = rand() % MAX_VALUE;
    }
}

void multiply(const int dim, const int * const a, int * const b, int * const c){
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            c[i * dim + j] = 0;
            for (int k = 0; k < dim; ++k) {
                c[i * dim + j] += a[i * dim + k] * b[k * dim + j];
            }
        }
    }
}
    
void transpose(const int dim, int * const m) {
    for (int i = 0; i < dim; ++i) {
        for (int j = i + 1; j < dim; ++j) {
            int temp = m[i * dim + j];
            m[i * dim + j] = m[j * dim + i];
            m[j * dim + i] = temp;
        }
    }
}
    
void multiply_transpose(const int dim, const int * const a, const int * const b_t, int * const c) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            int sum = 0;
            for (int k = 0; k < dim; ++k) {
                sum += a[i * dim + k] * b_t[j * dim + k];
            }
            c[i * dim + j] = sum;
        }
    }
}

void transpose_and_multiply(const int dim, const int * const a, int * const b, int * const c) {
    transpose(dim, b);
    multiply_transpose(dim, a, b, c);
}

struct timeval run_and_time(
    void (* mult_func)(const int, const int * const, int * const, int * const),
    const int dim,
    const int * const a,
    int * const b,
    int * const c
) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mult_func(dim, a, b, c);
    gettimeofday(&end, NULL);
    struct timeval result;
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_usec = end.tv_usec - start.tv_usec;
    if (result.tv_usec < 0) {
        result.tv_sec--;
        result.tv_usec += 1000000;
    }
    return result;
}
    
int verify(const int dim, const int * const c1, const int * const c2) {
    for (int i = 0; i < dim * dim; ++i) {
        if (c1[i] != c2[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

void run_test(const int dim) {
    int *a = calloc(dim * dim, sizeof(int));
    int *b = calloc(dim * dim, sizeof(int));
    int *c1 = calloc(dim * dim, sizeof(int));
    int *c2 = calloc(dim * dim, sizeof(int));
    init(dim, a);
    init(dim, b);
    struct timeval time_multiply = run_and_time(&multiply, dim, a, b, c1);
    struct timeval time_transpose_multiply = run_and_time(&transpose_and_multiply, dim, a, b, c2);
    if (verify(dim, c1, c2)) {
        printf("Results agree.\n");
    } else {
        printf("Error: Results don't agree.");
    }
    printf("Standard multiplication: %ld seconds, %ld microseconds\n", (long)time_multiply.tv_sec, (long)time_multiply.tv_usec);
    printf("Multiplication with transpose: %ld seconds, %ld microseconds\n", (long)time_transpose_multiply.tv_sec, (long)time_transpose_multiply.tv_usec);
    free(a);
    free(b);
    free(c1);
    free(c2);
}

void print(const int dim, const int * const m) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            printf("%d ", m[i * dim + j]);
        }
        printf("\n");
    }
}

int main() {
    for (int power = MIN_DIM_POWER; power <= MAX_DIM_POWER; ++power) {
        int dim = 1 << power;
        printf("Currently running the test for dimension: %d\n", dim);
        run_test(dim);
    }
    return EXIT_SUCCESS;
}

