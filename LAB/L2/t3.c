#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
int fd1[2];
int fd2[2];
int fd3[2];
int fd4[2];

pipe(fd1);
pipe(fd2);
pipe(fd3);
pipe(fd4);

int buff[BUFSIZ+1];
int arr[4],sum=0,min=0;
for(int i=0;i<4;i++)
{
scanf("%d",&arr[i]);
}
int pid1=fork();
int pid2=fork();
if(pid1==0)
{
int sum=0;
close(fd1[1]);
read(fd1[0],buff,BUFSIZ);
close(fd1[0]);
for(int i=0;i<4;i++)
{
sum=sum+arr[i];
}
write(fd3[1],&sum,10);
close(fd3[1]);
if(pid2==0)
{
int min=0;
int loc=0;
close(fd2[1]);
read(fd2[0],buff,BUFSIZ);
close(fd2[0]);
for(int i=0;i<4;i++)
{
if(arr[i]<arr[loc])
{
loc=i;
}
}
min=arr[loc];
write(fd4[1],&min,10);
close(fd4[1]);
}
}
else
{
close(fd1[0]);

write(fd1[1],arr,5);

close(fd1[1]);

close(fd2[0]);

write(fd2[1],arr,5);

close(fd2[1]);

close(fd3[1]);

read(fd3[0],&sum,10);

close(fd3[0]);

printf("\nSum from child2: %d",sum);

close(fd4[1]);

read(fd4[0],&min,10);

close(fd4[0]);

printf("\nSum from child2: %d",min);
}
return 0;
}
