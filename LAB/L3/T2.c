#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<wait.h>
#include<pthread.h>
#include<stdlib.h>
void* add (void* ptr)
{
int* avg = (int*) ptr;
int size=5;
double sum=0;
for(int i=0;i<5;i++)
    {
       sum=sum+num[i];
    }
sum=sum/size;
printf("avg is %f \n",sum);

}

void* min (void* ptr)
{
    int* number = (int*) ptr;
    
    int* min;
    min = number[0];
for(int i=0;i<5;i++)
{
if (number[i]<min)
min =number[i];
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
pthread_t pid1,pid2,pid3,pid4,pid5; 
void* ret1, *ret2, *ret3,*ret4,*ret5;
int number[] = {10,20,30,5,15,30};

pthread_create(&pid1,NULL,&add,(void*)&avg[0]);
pthread_join(pid1,&ret1);

pthread_create(&pid2,NULL,&min,(void*)&num[0]);
pthread_join(pid2,&ret2);

pthread_create(&pid3,NULL,&max,(void*)&num[0]);
pthread_join(pid3,&ret3);


return 0;
}
