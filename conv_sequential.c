#include <stdio.h>
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

int* convolution(int* ptr_A, int* ptr_F, int size_A, int size_F) { 
    int window_size = size_F;
    int result_size = size_A - size_F + 1;
    int* result = (int*) malloc(sizeof(int) * result_size);
    int* ptr_FF = (int*) malloc(sizeof(int) * size_F);

    // reverse F
    for (size_t i = 0; i < size_F; i++) {
        ptr_FF[i] = ptr_F[size_F - 1 - i];
    }

    // calculate convolution
    for (size_t i = 0; i < result_size; i++) {
        int summation = 0;
        for (size_t j = 0; j < window_size; j++) {
            summation += ptr_A[i + j] * ptr_FF[j];
        }
        result[i] = summation;
    }
    return result;
}


int main() {
    int nA, nF;
    scanf("%d %d", &nA, &nF);
    
    int* A = get_input(nA);
    int* F = get_input(nF);
    int* R = convolution(A, F, nA, nF);
    display_array(R, nA - nF + 1);

    free(A);
    free(F);
    free(R);
    return 0;
}