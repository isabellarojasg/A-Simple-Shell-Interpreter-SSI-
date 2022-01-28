#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
char * host_name();

int main(){

	char * prompt= host_name();

	int bailout = 0;
	while (!bailout) {

		char* reply = readline(prompt);
		/* Note that readline strips away the final \n */
		/* For Perl junkies, readline automatically chomps the line read */

		//exit\n command
		if (!strcmp(reply, "bye")) {
			bailout = 1;
		} else {
			printf("\nYou said: %s\n\n", reply);
		}
	
		free(reply);
	}
	printf("Bye Bye\n");
}

char * host_name(){

	char host_name[1024];
	char *user_name;
	user_name = getlogin();
	gethostname(host_name, 1024);
	//printf("%s@%s> \n",user_name,host_name);

	//char* prompt;

	int size_of_host = 0;

	int i = 0;
	while (host_name[i] != '\0' ){
		size_of_host +=1;
		i ++;
	}

	int size_of_user = strlen(user_name);

	char *t;
	char *host= host_name;
	char* x;
	char* prompt;
	for (t =  user_name, x = prompt; *t != '\0'; t++, x++){
		*x = *t;
	}
	*x= '@';
	x++;
	for (t =  host; *t != '\0'; t++, x++){
		*x = *t;
	}
	*x= '>'; x++;
	*x= ' '; x++;
	*x = '\0';

	return prompt;

}
