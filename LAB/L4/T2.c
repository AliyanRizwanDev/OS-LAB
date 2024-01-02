#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<wait.h>
int main()
{
    if(!fork()) // create A
    {
        if(!fork()) // create B
        if(!fork()) // creates D
        if(!fork()) // creates H
        if(!fork()) // creates I
        printf("I am I from H\n");
        else
        {
            wait(NULL);
            printf("I am H from D\n");
        }
        else
        {
            wait(NULL);
            printf("I am D from B\n");
        }
        else
        {
            wait(NULL);
            if(!fork()) //creates E
            printf("I am E from B\n");
            else
            {
                wait(NULL);
                if(!fork()) // creates F
                printf("I am F from B\n");
                else
                {
                    wait(NULL);
                    printf("I am B from A\n");
                }
            }
        }
        else
        {
            wait(NULL);
            if(!fork()) //create C
            if(!fork()) //creates G
            printf("I am G from C\n");
            else
            {
                wait(NULL);
                printf("I am C from A\n");
            }
            else
            {
                wait(NULL);
                printf("I am A\n");
            }
        }
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
