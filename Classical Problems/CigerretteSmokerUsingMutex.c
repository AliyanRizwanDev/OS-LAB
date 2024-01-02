#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#define NUM_SMOKERS 3

int table_has_ingredient = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t table_ready = PTHREAD_COND_INITIALIZER;

void *agent(void *arg)
{
    while(1) {
        pthread_mutex_lock(&mutex);
        while(table_has_ingredient)
            pthread_cond_wait(&table_ready, &mutex);

        int ingredient = rand() % 3;
        table_has_ingredient = ingredient + 1;
        printf("Agent puts ingredient %d on the table.\n", ingredient);

        pthread_cond_broadcast(&table_ready);
        pthread_mutex_unlock(&mutex);
    }
}

void *smoker(void *arg)
{
    int id = *(int*) arg;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(table_has_ingredient != id + 1)
            pthread_cond_wait(&table_ready, &mutex);

        printf("Smoker %d takes the ingredients from the table and makes a cigarette.\n", id);
        table_has_ingredient = 0;

        pthread_cond_signal(&table_ready);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);
    }
}

int main()
{
    pthread_t threads[NUM_SMOKERS + 1];
    int ids[NUM_SMOKERS];

    pthread_create(&threads[0], NULL, agent, NULL);

    for (int i = 0; i < NUM_SMOKERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i+1], NULL, smoker, &ids[i]);
    }

    for (int i = 0; i < NUM_SMOKERS + 1; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

