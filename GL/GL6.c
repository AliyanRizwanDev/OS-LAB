#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    int pid;
    pid = fork();

    if (pid > 0)
    {
        wait(NULL);
        int pid2 = fork();
        if (pid2 > 0)
        {
            wait(NULL);
            int pid3 = fork();

            if (pid3 > 0)
            {

                wait(NULL);
                printf("A Child(B) id %d\n", getpid());
                printf("B Parent(A) id %d\n", getppid());
                printf("\n\n");

                int pid4 = fork();
                if (pid4 > 0)
                {
                    wait(NULL);
                    printf("A Child2(C) id %d\n", getpid());
                    printf("C Parent(A) id %d\n", getppid());
                    printf("\n\n");
                }
                else if (pid4 == 0)
                {
                    printf("C Child(G) id %d\n", getpid());
                    printf("G Parent(C) id %d\n", getppid());
                    printf("\n\n");
                }
            }
            else if (pid3 == 0)
            {
                printf("B Child1(D) id %d\n", getpid());
                printf("D Parent(B) id %d\n", getppid());
                printf("\n\n");
            }
        }
        else if (pid2 == 0)
        {
            printf("B Child2(E) id %d\n", getpid());
            printf("E Parent(B) id %d\n", getppid());
            printf("\n\n");
        }
    }
    else if (pid == 0)
    {
        printf("B Child3(F) id %d\n", getpid());
        printf("F Parent(B) id %d\n", getppid());
        printf("\n\n");
        int pid4 = fork();
        if (pid4 > 0)
        {
            wait(NULL);
        }
        else if (pid == 0)
        {
            printf("D Child(H) id %d\n", getpid());
            printf("H Parent(D) id %d\n", getppid());
            printf("\n\n");
            int pid5 = fork();
            if (pid5 > 0)
            {
                wait(NULL);
            }
            else if (pid == 0)
            {
                printf("H Child(I) id %d\n", getpid());
                printf("I Parent(H) id %d\n", getppid());
                printf("\n\n");
            }
        }
    }

    return 0;
}
