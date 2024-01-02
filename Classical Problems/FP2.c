#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/file.h>
sem_t s;

void *f3(){printf("\n 3");}
void f1(){
printf("\n 1");
sem_post(&s);
return;
}
void f2(){
printf("\n 2");
sem_post(&s);
return;
}
void F0(int *id){
int i=(*(int*)id);
sem_wait(&s);
//while(s<=0){
if (i==1){
f1();
}
else if(i==2){
f2();
}
else{
//return;
}
//}
}

int main(){
sem_init(&s,0,1);
pthread_t t[2];
pthread_t t3;
int id[2]={1,2};
pthread_create(&t3,NULL,f3,NULL);
pthread_join(t3,NULL);
for(int i=1; i<3;i++){
pthread_create(&t[i],NULL,F0,&id[i]);
}
for(int i=1; i<3;i++){
pthread_join(t[i],NULL);
}


return 0;
}
