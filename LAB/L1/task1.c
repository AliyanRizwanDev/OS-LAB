#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<wait.h>
#include<pthread.h>
#include<stdlib.h>

 struct thread_args {
       int* first;
       int second;
     };


void* avg (void* ptr)
{
    
    struct thread_args *args = (struct thread_args *) ptr;


double sum=0;
for(int i=0;i<args->second;i++)
    {
       sum=sum+args->first[i];
    }
sum=sum/args->second;
printf("avg is %f \n",sum);
free(args);
}

void* min (void* ptr)
{

    int* number=(int*)ptr;
    int min;
    min = number[0];
    for(int i=0;i<5;i++)
    {
        if (number[i]<min)
        min=number[i];
    }

printf ("minimum element is :%d\n",min);
}

void* max (void* ptr)
{
    int* number = (int*) ptr;
    int* max;
    max = number[0];
    
    for(int i=0;i<5;i++)
    {
        if (number[i]>max)
        max =number[i];
    }
    
printf ("maximum element is :%d \n",max);
}

int main(int argc, int* argv[])
{
    
    int* num=(int*)malloc(sizeof(int));
    int j=0;
    for(int i=1;i<argc;i++)
    {
        num[j]=atoi(argv[i]);
        j++;
    }
    
    int size=argc-1;
    struct thread_args *args = malloc (sizeof (struct thread_args));
    args->first = num;
    args->second = size;

pthread_t pid1,pid2,pid3; 
void* ret1, *ret2, *ret3;

pthread_create(&pid1,NULL,&avg,args);
pthread_join(pid1,&ret1);

pthread_create(&pid2,NULL,&min,&num[0]);
pthread_join(pid2,&ret2);

pthread_create(&pid3,NULL,&max,&num[0]);
pthread_join(pid3,&ret3);


return 0;
}