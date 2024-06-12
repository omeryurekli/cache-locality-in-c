# Cache-Friendly Matrix Multiplication

This project demonstrates the performance benefits of transforming an algorithm to be cache-friendly. The algorithm in question is simple matrix multiplication for square matrices, comparing the standard method with a cache-optimized method that transposes the second matrix before multiplication.

## Overview

Matrix multiplication is a fundamental operation in many scientific and engineering applications. This project explores how making an algorithm cache-friendly can significantly improve performance. The cache-friendly version of the algorithm first transposes the second matrix and then performs a modified multiplication, which is more efficient in terms of memory access patterns.

## Files

- **pa5.c**: The main C source code file that implements both standard and cache-friendly matrix multiplication.

## Details

### Functions

- **`void init(const int dim, int * const m)`**: Initializes a square matrix with random integers in the range [0, 20).
- **`void multiply(const int dim, const int * const a, int * const b, int * const c)`**: Performs standard matrix multiplication.
- **`void transpose(const int dim, int * const m)`**: Transposes a square matrix in place.
- **`void multiply_transpose(const int dim, const int * const a, const int * const b_t, int * const c)`**: Multiplies a matrix with the transpose of another matrix.
- **`void transpose_and_multiply(const int dim, const int * const a, int * const b, int * const c)`**: Transposes the second matrix and then multiplies it.
- **`struct timeval run_and_time(void (* mult_func)(const int, const int * const, int * const, int * const), const int dim, const int * const a, int * const b, int * const c)`**: Times the given multiplication function.
- **`int verify(const int dim, const int * const c1, const int * const c2)`**: Verifies if two matrices are identical.
- **`void run_test(const int dim)`**: Runs tests comparing standard and cache-friendly multiplication.
- **`void print(const int dim, const int * const m)`**: Prints a square matrix.
- **`int main()`**: Runs tests for matrix dimensions from \(2^3\) to \(2^{10}\).

## Usage

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/cache-friendly-matrix-multiplication.git
    ```
2. Navigate to the project directory:
    ```bash
    cd cache-friendly-matrix-multiplication
    ```
3. Compile the `pa5.c` file:
    ```bash
    gcc -o pa5 pa5.c
    ```
4. Run the executable:
    ```bash
    ./pa5
    ```

### Sample Output

The program will output the results of both standard and cache-friendly matrix multiplication, including the time taken for each method. The results will show the performance improvement achieved by using the cache-friendly algorithm.

### Example

