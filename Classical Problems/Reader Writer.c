#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int shared_resource = 0;
int reader_count = 0;

pthread_mutex_t mutex;
sem_t resource_sem, reader_sem;

void *writer(void *arg) {
    int item;
    while (1) {
        // generate random item to write
        item = rand() % 100;

        // wait for exclusive access to the shared resource
        sem_wait(&resource_sem);

        // write to the shared resource
        shared_resource = item;

        // signal that the resource is available
        sem_post(&resource_sem);

        printf("Wrote item %d\n", item);
        sleep(rand() % 3);
    }
}

void *reader(void *arg) {
    while (1) {
        // acquire the reader count mutex to update the count
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) {
            // if this is the first reader, wait for exclusive access to the resource
            sem_wait(&resource_sem);
        }
        pthread_mutex_unlock(&mutex);

        // read from the shared resource
        printf("Read item %d\n", shared_resource);

        // release the reader count mutex to update the count
        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            // if this is the last reader, signal that the resource is available
            sem_post(&resource_sem);
        }
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);
    }
}

int main() {
    pthread_t writer_tid, reader_tid;

    // initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&resource_sem, 0, 1);
    sem_init(&reader_sem, 0, 1);

    // create writer and reader threads
    pthread_create(&writer_tid, NULL, writer, NULL);
    pthread_create(&reader_tid, NULL, reader, NULL);

    // wait for threads to finish
    pthread_join(writer_tid, NULL);
    pthread_join(reader_tid, NULL);

    // destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&resource_sem);
    sem_destroy(&reader_sem);

    return 0;
}
