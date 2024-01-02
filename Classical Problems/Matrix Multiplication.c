#include stdio.h
#include stdlib.h
#include pthread.h

#define MAX_M 100
#define MAX_N 100

int M, N;
int A[MAX_M][MAX_N];
int B[MAX_M][MAX_N];
int C[MAX_M][MAX_N];
pthread_t threads[MAX_M];

void divide_rows(void arg) {
    int row = ((int) arg);
    for (int j = 0; j  N; j++) {
        C[row][j] = A[row][j]  B[row][j];
    }
    pthread_exit(NULL);
}

int main(int argc, char argv[]) {
    if (argc != 3) {
        printf(Usage .program M Nn);
        return 1;
    }

     Parse command line arguments
    M = atoi(argv[1]);
    N = atoi(argv[2]);

     Initialize matrices A and B with random values
    for (int i = 0; i  M; i++) {
        for (int j = 0; j  N; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
        }
    }

     Create threads to divide rows
    for (int i = 0; i  M; i++) {
        int row_ptr = malloc(sizeof(int));
        row_ptr = i;
        pthread_create(&threads[i], NULL, divide_rows, row_ptr);
    }

     Wait for all threads to complete
    for (int i = 0; i  M; i++) {
        pthread_join(threads[i], NULL);
    }

     Display the resultant matrix C
    printf(Resultant matrix Cn);
    for (int i = 0; i  M; i++) {
        for (int j = 0; j  N; j++) {
            printf(%d , C[i][j]);
        }
        printf(n);
    }

    return 0;
}
