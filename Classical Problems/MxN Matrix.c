#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the size of the matrices
int M, N;

// Define the number of worker threads
#define NUM_THREADS 4

// Define the matrices
int A[100][100];
int B[100][100];
int C[100][100];

// Define a struct to hold thread arguments
typedef struct {
    int start;
    int end;
} thread_args;

// Define the worker thread function
void *worker_thread(void *arg) {
    // Extract the thread arguments
    thread_args *args = (thread_args *)arg;
    int start = args->start;
    int end = args->end;

    // Divide elements of matrix A by corresponding elements of matrix B
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] / B[i][j];
        }
    }

    // Exit the thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Get the size of the matrices from command-line arguments
    if (argc != 3) {
        printf("Usage: %s M N\n", argv[0]);
        exit(1);
    }
    M = atoi(argv[1]);
    N = atoi(argv[2]);

    // Initialize the matrices
    srand(time(NULL));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10 + 1;  // Generate a random integer between 1 and 10
            B[i][j] = rand() % 10 + 1;  // Generate a random integer between 1 and 10
        }
    }

    // Create the worker threads
    pthread_t threads[NUM_THREADS];
    thread_args args[NUM_THREADS];
    int rows_per_thread = M / NUM_THREADS;
    int remaining_rows = M % NUM_THREADS;
    int start = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = start;
        start += rows_per_thread;
        if (i < remaining_rows) {
            start++;
        }
        args[i].end = start;
        pthread_create(&threads[i], NULL, worker_thread, &args[i]);
    }

    // Wait for the worker threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the resultant matrix
    printf("Resultant matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
