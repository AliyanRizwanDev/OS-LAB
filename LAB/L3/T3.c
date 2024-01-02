#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#include<string.h>
int main() {

int fd[2];
char arr[100];
pipe(fd);
if(fork() == 0) {

int n = read(0, arr, 100);
close(fd[0]);
int nn = write(fd[1], arr, n+1);
close(fd[1]);
wait(NULL);
}

else {
char buff[100];
close(fd[1]);
int nnn = 0 ; read(fd[0], buff, 100);
close(fd[0]);
write(1, buff, nnn+1);
}
}
