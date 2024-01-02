#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

#define WRITE 1
#define READ 0

int main(){
int fd[2];
int fd2[2];
int a=2;
int status;
int buff[BUFSIZ+1];
pid_t pid;
pipe(fd);
pipe(fd2);
if(fork()){
close(fd[READ]);
write(fd[WRITE], &a,2);
wait(0);

close(fd2[READ]);
read(fd2[WRITE],&a,2);
printf("Double value %d \n",a);
}
else
{
close(fd[write]);

read(fd[READ],&a,2);
printf("input integer %d \n",a);
a=a*2;
close(fd2[READ]);
Write(fd2[WRITE],&a,2);
}
return 0;
}
