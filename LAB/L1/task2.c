#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<wait.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

struct thread_args 
    {
       char* fname;
       char* str;
     };


 void* Search_in_File(void* ptr) 
 {
    struct thread_args *args = (struct thread_args *) ptr;
    
    
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	char*fname=args->fname;
	char*str=args->str;
	

	fp = fopen(fname, "r");
	
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	if(fp) {
		fclose(fp);
	}
	free(args);
	
	
	pthread_exit(NULL);

}



int main(int argc, char *argv[]) 
{
	int result;

    struct thread_args *args = malloc (sizeof (struct thread_args));
    args->fname = argv[1];
    args->str = argv[2];

    pthread_t threads[atoi(argv[3])];


	for(int t=0; t<atoi(argv[3]); t++)
	{
        int rc = pthread_create(&threads[t], NULL, &Search_in_File,args);
        if (rc)
        {
             printf("ERROR; return code from pthread_create() is%d\n", rc);
             exit(-1);
        }
    }


	return(0);
}

