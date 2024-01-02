#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
    int read_count = 0; 
    int write_count = 0; 
    int waiting_readers = 0; 
    int waiting_writers = 0; 
    int resource = 0; 
    int id = 1; 
    int max_readers = 5; 
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t reader_queue = PTHREAD_COND_INITIALIZER; 
    pthread_cond_t writer_queue = PTHREAD_COND_INITIALIZER; 
}


void* reader(void* arg)
{
int thread_id = id++; 
pthread_mutex_lock(&mutex);
waiting_readers++;
while(write_count > 0 || read_count >= max_readers) 
{ 
pthread_cond_wait(&reader_queue, &mutex);
}
waiting_readers--;
read_count++;
pthread_mutex_unlock(&mutex);
printf("Reader %d is reading resource %d\n", thread_id, resource);
sleep(1); 
pthread_mutex_lock(&mutex);
read_count--;
if(read_count == 0)
{ 
pthread_cond_signal(&writer_queue);
}
else if(waiting_writers > 0 && read_count + waiting_readers < max_readers) { 
pthread_cond_broadcast(&reader_queue);
}
pthread_mutex_unlock(&mutex);
pthread_exit(0);
}

void* writer(void* arg)
{
int thread_id = id++; 
pthread_mutex_lock(&mutex);
waiting_writers++;
while(write_count > 0 || read_count > 0) 
{ 
pthread_cond_wait(&writer_queue, &mutex);
}
waiting_writers--;
write_count++;
pthread_mutex_unlock(&mutex);
printf("Writer %d is writing to resource %d\n", thread_id, resource);
sleep(1); 
pthread_mutex_lock(&mutex);
write_count--;
if(waiting_writers > 0) 
{ 
pthread_cond_signal(&writer_queue);
}
else if(waiting_readers > 0)
{
pthread_cond_broadcast(&reader_queue);
}