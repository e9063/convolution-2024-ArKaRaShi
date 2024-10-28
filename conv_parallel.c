#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int* get_input(int size) {
    int* ptr = (int*) malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        scanf("%d", &ptr[i]);
    }
    return ptr;
}

void display_array(int* ptr, int size) {
    for (size_t i = 0; i < size; i++) {   
        printf("%d\n", ptr[i]);
    }
    // printf("\n");
}

int* convolution(int* ptr_A, int* ptr_F, int size_A, int size_F, int total_threads) { 
    int window_size = size_F;
    int result_size = size_A - size_F + 1;
    int* result = (int*) malloc(sizeof(int) * result_size);
    int* ptr_FF = (int*) malloc(sizeof(int) * size_F);

    for (size_t i = 0; i < size_F; i++) {
        ptr_FF[i] = ptr_F[size_F - 1 - i];
    }

    omp_set_num_threads(total_threads);
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < result_size; i++) {
        int summation = 0;
        for (size_t j = 0; j < window_size; j++) {
            summation += ptr_A[i + j] * ptr_FF[j];
        }
        result[i] = summation;
    }
    
    free(ptr_FF);
    return result;
}


int main() {
    int nA, nF;
    scanf("%d %d", &nA, &nF);
    
    int* A = get_input(nA);
    int* F = get_input(nF);
    int* R;
  
    // sequential
    double start_time, end_time;
    start_time = omp_get_wtime();
    R = convolution(A, F, nA, nF, 1);
    // display_array(R, nA - nF + 1);
    end_time = omp_get_wtime();
    free(R);
 
    double sequential_time = end_time - start_time;
    printf("Sequential Time: %f seconds\n", sequential_time);

    // parallel 4 threads
    start_time = omp_get_wtime();
    R = convolution(A, F, nA, nF, 4);
    // display_array(R, nA - nF + 1);
    end_time = omp_get_wtime();
    free(R);

    double parallel_4_threads_time = end_time - start_time;
    printf("Parallel 4 threads Time: %f seconds\n", parallel_4_threads_time);

    double speedup_4_threads = sequential_time / parallel_4_threads_time;
    printf("Speedup: %f\n", speedup_4_threads);

    // parallel 8 threads
    start_time = omp_get_wtime();
    R = convolution(A, F, nA, nF, 8);
    // display_array(R, nA - nF + 1);
    end_time = omp_get_wtime();
    free(R);

    double parallel_8_threads_time = end_time - start_time;
    printf("Parallel 8 threads Time: %f seconds\n", parallel_8_threads_time);

    double speedup_8_threads = sequential_time / parallel_8_threads_time;
    printf("Speedup: %f\n", speedup_8_threads);

    free(A);
    free(F);
    return 0;
}