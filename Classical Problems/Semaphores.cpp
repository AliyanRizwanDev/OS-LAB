#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;

void* print_one(void* arg) {
    sem_wait(&sem1);
    printf("1 ");
    sem_post(&sem2);
    return NULL;
}

void* print_two(void* arg) {
    sem_wait(&sem2);
    printf("2 ");
    //sem_post(&sem1);
    return NULL;
}

void* print_three(void* arg) {
    printf("3 ");
    sem_post(&sem1);
    return NULL;
}

int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, print_one, NULL);
    pthread_create(&thread2, NULL, print_two, NULL);
    pthread_create(&thread3, NULL, print_three, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

