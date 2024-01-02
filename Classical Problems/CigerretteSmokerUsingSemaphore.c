#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<unistd.h>
#define NUM_SMOKERS 3

sem_t table_mutex;
sem_t tobacco;
sem_t paper;
sem_t matches;

void *agent(void *arg) {
    while (1) {
        // Wait for table to be empty
        sem_wait(&table_mutex);
        
        // Put two random ingredients on the table
        int ingredient1 = rand() % 3;
        int ingredient2 = rand() % 3;
        
        while (ingredient2 == ingredient1) {
            ingredient2 = rand() % 3;
        }
        
        if (ingredient1 == 0 && ingredient2 == 1) {
            sem_post(&matches);
        }
        else if (ingredient1 == 0 && ingredient2 == 2) {
            sem_post(&paper);
        }
        else {
            sem_post(&tobacco);
        }
        
        // Signal that table is ready
        sem_post(&table_mutex);
    }
}

void *smoker(void *arg) {
    int id = *(int*)arg;
    sem_t *my_ingredient1;
    sem_t *my_ingredient2;
    
    if (id == 0) {
        my_ingredient1 = &paper;
        my_ingredient2 = &matches;
    }
    else if (id == 1) {
        my_ingredient1 = &tobacco;
        my_ingredient2 = &matches;
    }
    else {
        my_ingredient1 = &paper;
        my_ingredient2 = &tobacco;
    }
    
    while (1) {
        // Wait for table to be empty
        sem_wait(&table_mutex);
        
        if (sem_trywait(my_ingredient1) == 0) {
            if (sem_trywait(my_ingredient2) == 0) {
                printf("Smoker %d is smoking\n", id);
                sem_post(&table_mutex);
                // Smoke for a random amount of time
                usleep((rand() % 500) * 1000);
                sem_post(my_ingredient1);
                sem_post(my_ingredient2);
            } else {
                sem_post(my_ingredient1);
            }
        }
        else if (sem_trywait(my_ingredient2) == 0) {
            sem_post(my_ingredient2);
        }
        
        // Signal that table is ready
        sem_post(&table_mutex);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&table_mutex, 0, 1);
    sem_init(&tobacco, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&matches, 0, 0);
    
    // Initialize random seed
    srand(time(NULL));
    
    // Create threads for agent and smokers
    pthread_t agent_thread;
    pthread_t smoker_threads[NUM_SMOKERS];
    int smoker_ids[NUM_SMOKERS];
    for (int i = 0; i < NUM_SMOKERS; i++) {
        smoker_ids[i] = i;
    }
    
    pthread_create(&agent_thread, NULL, agent, NULL);
    for (int i = 0; i < NUM_SMOKERS; i++) {
        pthread_create(&smoker_threads[i], NULL, smoker, &smoker_ids[i]);
    }
    
    // Wait for threads to finish
    pthread_join(agent_thread, NULL);
    for (int i = 0; i < NUM_SMOKERS; i++) {
pthread_join(smoker_threads[i], NULL);
}
// Destroy semaphores
sem_destroy(&table_mutex);
sem_destroy(&tobacco);
sem_destroy(&paper);
sem_destroy(&matches);

return 0;
}
