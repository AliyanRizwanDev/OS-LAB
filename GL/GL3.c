#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_SZIE 20

char* take_input(char* array){
	if(array==NULL){
		printf("Could not allocate enough memory.\n");
		exit(1);
	}
	int i=1;	
	array[0] = '\0';
	for(char c=getchar(); c!='\n' && c!=EOF; c=getchar()){
		i++;
		array = realloc(array, i*sizeof(char));
		if(array == NULL){
			printf("Could not allocate enough memory.\n");
			exit(1);
		}
		int length = strlen(array);
		array[length] = c;
		array[length + 1] = '\0';
	}
	return array;
}

char* replace_string(char* new_string, char* original_string, char* cut_string, char* paste_string){
	int i=0, j, k=0;
	while(original_string[i] != '\0'){
		for(j=0; cut_string[j]!='\0'; j++){
			if(original_string[i+j] != cut_string[j]){
				break;
			}
		}
		if(cut_string[j]=='\0' && j>0){
			i += j;
			for(j=0; paste_string[j]!='\0'; j++){
				new_string[k++] = paste_string[j];
			}
		}
		else{
			new_string[k++] = original_string[i++];
		}
	}
	new_string[k] = '\0';
	return new_string;
}

int main(int argc, char **argv){
	if(argc<2 || argc>2){
		printf("Only one argument is required. \n");
		exit(1);
	}
	char* original_string = argv[1];
	char* new_string = (char*) malloc(strlen(original_string) + DEFAULT_SZIE);
	char* cut_string = (char*) malloc(sizeof(char));
	char* paste_string = (char*) malloc(sizeof(char));
	
	if(new_string==NULL){
		printf("Could not allocate enough memory.\n");
		exit(1);
	}
	new_string[0] = '\0';
	
	printf("Substring to be cut: ");
	cut_string = take_input(cut_string);
	//printf("Cut String is: %s \n", cut_string);
	
	printf("Substring to be pasted: ");
	paste_string = take_input(paste_string);
	//printf("Pasted String is: %s \n", paste_string);

	new_string = replace_string(new_string, original_string, cut_string, paste_string);

	printf("New String is: %s \n", new_string);

	
	return 0;
}
