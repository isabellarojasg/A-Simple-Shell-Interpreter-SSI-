#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

char * host_name();
void add_path();
void execute_commands(char* args[1024]);
void change_directory(char* args[1024]);
typedef struct bg_pro{
	pid_t pid; 
	char command[1024];
	struct bg_pro* next;
}bg_pro;
void backgroud_prc(char* args[1024]);
bg_pro *root;

int main(){

	char * prompt= host_name();

	
	int bailout = 0;
	while (!bailout) {

		add_path(prompt);

		
		char line[1024];
		char* args[1024];
		printf("%s", prompt);
		fgets(line,1024,stdin);
			
		
		args[0]=strtok(line," \n");
    	
    	
		int i=0;
    	while(args[i]!=NULL){
       		args[i+1]=strtok(NULL," \n");
        	i++;
        }

		if(root != NULL){

			pid_t ter = waitpid(0,NULL,WNOHANG);
			
			if (ter > 0){
				if (root->pid ==ter){
					printf("%i: ",root->pid);
					
					int w=0;
					while(root->command[w]!= '\0'){
						printf("%c",root->command[w]);
						w++;
					}
					
					printf(" has terminated.\n");
					
					
					root = root->next;
				}
			}else{
				bg_pro *cur;


				for (cur = root;cur->next != NULL; cur->next){
					cur = cur->next;
				}
				
					printf("%i: ",cur->pid);
					
					int w=0;
					while(cur->command[w]!= '\0'){
						printf("%c",cur->command[w]);
						w++;
					}
					
					printf(" has terminated\n");
				cur = cur->next;


			}


		}
	
		
		
		
		if (!strcmp(args[0], "exit")){
			bailout = 1;
		} else if (!strcmp(args[0], "cd")){
			change_directory(args);
		}else if (!strcmp(args[0], "bg")){


			backgroud_prc(args);
			
			
		}else if (!strcmp(args[0], "bglist")){
			bg_pro * hi;
			int i = 1;
			for (hi = root; hi->next != NULL; hi = hi->next, i++){
				//printf("%i : %c %i\n",hi->pid,hi->command[0],i);
				printf("%i : ",hi->pid);

				int w=0;
				while(hi->command[w]!= '\0'){
					printf("%c",hi->command[w]);
					w++;
				}

				printf(" %i\n",i);

			}

			printf("%i : ",hi->pid);

				int w=0;
				while(hi->command[w]!= '\0'){
					printf("%c",hi->command[w]);
					w++;
				}

				printf(" %i\n",i);

		printf("Total Backgrounf jobs: %i\n\n",i);


		
		}else{
			execute_commands(args);
		}


	
	}
	printf("Bye Bye\n");
	free(prompt);
	}



void backgroud_prc(char* args[1024]){


	char* new_args[1024];
	
	int size = 0;
	int i = 0;
	while (args[i] != NULL ){
		size +=1;
		i ++;
	}

	int j=1;
	int p=0;
    while(args[j]!=NULL){
       	
		new_args[p] = args[j];
        j++; p++;
    }
	new_args[p]= '\0';

	pid_t pidd; 
	pidd = fork();
	int status;

	if (pidd < 0){
		fprintf(stderr, "Fork Failed");
		exit(-1);
	} else if (pidd==0){
		execvp(new_args[0],new_args);
		printf("ERROR: not an executable command\n");
	}else {

		if(root == NULL){

			waitpid(pidd, NULL, 0);
			
			bg_pro *temp = (bg_pro *)malloc(sizeof(bg_pro));

			int w=0;
			int g=0;
			int h=0;
			for (w = 0; new_args[w] != NULL; w++){
				for (g=0;new_args[w][g]!= '\0'; g++){
						temp->command[h] = new_args[w][g];
				
					h++;
				}

			}
			temp->command[h] = '\0';
			
			temp->pid = pidd;


			root = temp;


		}else{


			waitpid(pidd, NULL, 0);
			
			bg_pro *temp = (bg_pro *)malloc(sizeof(bg_pro));

				int w=0;
			int g=0;
			int h=0;
			for (w = 0; new_args[w] != NULL; w++){
				for (g=0;new_args[w][g]!= '\0'; g++){
					temp->command[h] = new_args[w][g];

					h++;
				}
			}

			temp->command[h] = '\0';
			
					
			temp->pid = pidd;

			bg_pro *curent;

			for (curent = root;curent->next != NULL; curent->next){
			//	printf("THIS SHOULD APPEAR ONCE\n");

				curent = curent->next;
			}
			//printf("this %c \n", root->command[0]);

			
			curent->next = temp;


		}
	}

		

}

void change_directory(char* args[1024]){

	int size = 0;

	int i = 0;
	while (args[i] != NULL ){
		size +=1;
		i ++;
	}
	if( size == 1){		
		
		chdir(getenv("HOME"));

	}else {

		if(!strcmp(args[1], "..")){
			chdir("..");
		}else if(!strcmp(args[1], "~")){
			chdir(getenv("HOME"));
		}else{
			if(chdir(args[1]) != 0)
				perror(args[1]);
		}

			
	}
	
	


}

void execute_commands(char* args[1024]){
		
		pid_t pid;
		pid = fork();

		if (pid < 0){
			fprintf(stderr, "Fork Failed");
			exit(-1);
		} else if (pid==0){
			execvp(args[0],args);
			printf("ERROR\n");
		}else {
			wait(NULL);
		}

}

void add_path(char * prompt){

	char path[1024];
	if(getcwd(path, sizeof(path)) != NULL){
	} else{
		printf("error");
	}
	


	char* x;
	for (x = prompt; *x != ':'; x++){
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
