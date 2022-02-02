#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
char * host_name();
//char* prompt;

int main(){

	char * prompt= host_name();


	int bailout = 0;
	while (!bailout) {

	/*
		char line[1024];
		char* args[1024];
		fgets(line,1024,stdin);
		
		args[0]=strtok(line," \n");//split string by space or '\n' (IMPORTANT) there will be error without '\n'
    	
		printf("Output 1: %s, %s \n",args[0],args[1]);
    	
		int i=0;
    	while(args[i]!=NULL){//make sure that args has a NULL pointer at the end
       		args[i+1]=strtok(NULL," \n");
        	i++;
        }
    	for(int j=0; j<i; j++){
        	printf("Output 2: %s \n",args[j]);
		}
		*/
		

		char* reply = readline(prompt);
		
		if (!strcmp(reply, "bye")) {
			bailout = 1;
		} else {
			printf("\nYou said: %s\n\n", reply);
		}
	
		free(reply);
		
	}
	printf("Bye Bye\n");
	free(prompt);
}

char * host_name(){

	char host_name[1024];
	char *user_name;
	user_name = getlogin();
	gethostname(host_name, 1024);

	int size_of_host = 0;

	int i = 0;
	while (host_name[i] != '\0' ){
		size_of_host +=1;
		i ++;
	}

	int size_of_user = strlen(user_name);

	char* t;
	char* host = host_name;
	char* x;
	char* prompt = (char *)malloc(sizeof(char));
	for (t = user_name, x = prompt; *t != '\0'; t++, x++){
		*x = *t;
	}
	*x= '@';
	x++;
	for (t = host; *t != '\0'; t++, x++){
		*x = *t;
	}
	*x= '>'; x++;
	*x= ' '; x++;
	*x = '\0';

	return prompt;

}
