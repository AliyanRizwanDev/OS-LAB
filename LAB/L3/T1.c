#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char** argv)
{
	int fd[2]={0,1};
	pipe(fd);
	
	char* arr = (char*)malloc(20*sizeof(char));
	
	arr=argv[1];
	write(fd[1],arr,sizeof(arr));
	read(fd[0],arr,sizeof(arr));
	
	printf("Array output: %s",arr);
	

	return 0;
}
