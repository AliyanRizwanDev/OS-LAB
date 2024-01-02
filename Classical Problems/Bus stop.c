#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PASSENGERS 10

int num_passengers = 0;
int bus_arrived = 0;
sem_t bus;
sem_t mutex;

void *passenger(void *arg) {
    int id = *((int *) arg);
    printf("Passenger %d arrived at the bus stop.\n", id);
    sem_wait(&mutex);
    num_passengers++;
    sem_post(&mutex);
    sem_wait(&bus);
    printf("Passenger %d boarded the bus.\n", id);
    sem_wait(&mutex);
    num_passengers--;
    sem_post(&mutex);
    if (num_passengers == 0) {
        sem_post(&bus);
    }
    return NULL;
}

void *bus_driver(void *arg) {
    printf("The bus has arrived at the bus stop.\n");
    sem_wait(&mutex);
    bus_arrived = 1;
    sem_post(&mutex);
    sem_post(&bus);
    sem_wait(&bus);
    printf("All passengers have boarded. The bus is departing.\n");
    sem_wait(&mutex);
    bus_arrived = 0;
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t passengers[MAX_PASSENGERS];
    pthread_t bus;
    int ids[MAX_PASSENGERS];
    sem_init(&mutex, 0, 1);
    sem_init(&bus, 0, 0);
    for (int i = 0; i < MAX_PASSENGERS; i++) {
        ids[i] = i;
        pthread_create(&passengers[i], NULL, passenger, &ids[i]);
    }
    pthread_create(&bus, NULL, bus_driver, NULL);
    pthread_join(bus, NULL);
    for (int i = 0; i < MAX_PASSENGERS; i++) {
        pthread_join(passengers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&bus);
    return 0;
}
