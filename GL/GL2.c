#include <pthread.h>
#include<stdio.h>
#include <semaphore.h>
#include<unistd.h>
pthread_t c_threads[6], h_threads[12], o_threads[6], make_thread;
int c_count = 0, h_count = 0, o_count = 0;
sem_t c_sem, h_sem, o_sem, make_sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* cReady(void* arg) {
    sem_wait(&c_sem);
    pthread_mutex_lock(&mutex);
    c_count++;
    if (c_count >= 6 && h_count >= 12 && o_count >= 6) {
        sem_post(&make_sem);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&c_sem);
    return NULL;
}

void* hReady(void* arg) {
    sem_wait(&h_sem);
    pthread_mutex_lock(&mutex);
    h_count++;
    if (c_count >= 6 && h_count >= 12 && o_count >= 6) {
        sem_post(&make_sem);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&h_sem);
    return NULL;
}

void* oReady(void* arg) {
    sem_wait(&o_sem);
    pthread_mutex_lock(&mutex);
    o_count++;
    if (c_count >= 6 && h_count >= 12 && o_count >= 6) {
        sem_post(&make_sem);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&o_sem);
    return NULL;
}

void* makeGlucose(void* arg) {
    while (1) {
        sem_wait(&make_sem);
        pthread_mutex_lock(&mutex);
        if (c_count >= 6 && h_count >= 12 && o_count >= 6) {
            c_count -= 6;
            h_count -= 12;
            o_count -= 6;
            // Perform glucose reaction
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    sem_init(&c_sem, 0, 1);
    sem_init(&h_sem, 0, 1);
    sem_init(&o_sem, 0, 1);
    sem_init(&make_sem, 0, 0);

    pthread_create(&make_thread, NULL, makeGlucose, NULL);
    for(int i=0;i<6;i++){
    	 pthread_create(&c_threads[i], NULL, cReady, NULL);
	}
   
    for(int i=0;i<12;i++){
    	pthread_create(&h_threads[i], NULL, hReady, NULL);
	}
    for(int i=0;i<6;i++){
    	pthread_create(&o_threads[i], NULL, hReady, NULL);
	}
	

	pthread_create(&make_threads, NULL, make_thread, NULL);


 for(int i=0;i<6;i++)
    pthread_join(&c_threads[i], NULL);

for(int i=0;i<12;i++)
    pthread_join(&h_threads[i], NULL);

 for(int i=0;i<6;i++)
    pthread_join(&0_threads[i], NULL);

    pthread_join(&make_thread, NULL);

    sem_destroy(&c_sem);
    sem_destroy(&h_sem);
    sem_destroy(&o_sem);
    sem_destroy(&make_thread);

}
