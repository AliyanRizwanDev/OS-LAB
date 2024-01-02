#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])

{
    int pipe_Descriptor[2]; 

    pid_t pID; 

    pipe(pipe_Descriptor);
    pID = fork(); 
    if (pID == 0)
    {

       
        int n, args[100], args_Sum = 0;
        read(pipe_Descriptor[0], &n, sizeof(n)); 
        int i;
        for (i = 0; i < n; i++) 
        {
            int y;
            read(pipe_Descriptor[0], &y, sizeof(y)); 
            args[i] = y; 
        }
        for (i = 0; i < (n); ++i)
        {
            args_Sum += args[i]; 
        }
        write(pipe_Descriptor[1], &args_Sum, sizeof(args_Sum)); 
        exit(0); 
    }
    else
    {
        int args[100], args_Sum; 
        int i;
        // int n=*(argv[1])-'0';
        if (argc < 2)
        {
            printf("Enter number of elements and values: \n");
            return 0;
        }
        int n = atoi(argv[1]); 
        for (i = 0; i < (n); i++)
        {
            args[i] = atoi(argv[i + 2]); 
        }

        write(pipe_Descriptor[1], &n, sizeof(n)); 

        for (i = 0; i < n; i++)
        {
            int x = args[i];

            write(pipe_Descriptor[1], &x, sizeof(x)); 
        }
        wait(NULL);

        read(pipe_Descriptor[0], &args_Sum, sizeof(args_Sum));

        printf("Sum = %d \n", args_Sum);
    }
return 0;
}
