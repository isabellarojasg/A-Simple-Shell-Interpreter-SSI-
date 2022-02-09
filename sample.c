#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
char * host_name();
void add_path();

int main(){

	char * prompt= host_name();
	
	int bailout = 0;
	while (!bailout) {

		add_path(prompt);


		char line[1024];
		char* args[1024];
		printf("%s", prompt);
		fgets(line,1024,stdin);
		
		args[0]=strtok(line," \n");//split string by space or '\n' (IMPORTANT) there will be error without '\n'
    	
		//printf("Output 1: %s, %s \n",args[0],args[1]);
    	
		int i=0;
    	while(args[i]!=NULL){//make sure that args has a NULL pointer at the end
       		args[i+1]=strtok(NULL," \n");
        	i++;
        }
    	for(int j=0; j<i; j++){
        	//printf("Output 2: %s \n",args[j]);
		}

		Pid_t pid;
		pid = fork();

		if (pid < 0){
			fprintf(stderr, "Fork Failed");
		}
		if(p==0){
			execvp(argv[0],argv);
			printf("ERROR\n");
		}












		

		//char* reply = readline(prompt);
		
		//if (!strcmp(reply, "bye")) {
		//	bailout = 1;
		//} else {
		//	printf("\nYou said: %s\n\n", reply);
	//	}
	
	//	free(reply);
		//free(prompt);
	}
	printf("Bye Bye\n");
	free(prompt);

}

void add_path(char * prompt){

	char path[1024];
	if(getcwd(path, sizeof(path)) != NULL){
		//printf("directory %s", path);
	} else{
		printf("error");
	}

	char* x;
	for (x = prompt; *x != ':'; x++){
		//printf("%c" , *x);
	}
	*x = ':'; x++;
	*x = ' '; x++;


	char *p;
	for (p = path; *p != '\0'; p ++, x++){
		*x= *p;
	}
	*x = '>'; x++;
	*x = ' '; x++;
	*x = '\0';

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
	*x= ':'; x++;
	*x= ' '; x++;
	*x = '\0';

	return prompt;

}
