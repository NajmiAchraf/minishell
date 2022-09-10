/* #include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int	main(void)
{
	int	p[2];
	int	i = 0;

	pcmd = cmd->pip;
	if(pipe(p) < 0)
		printf("pipe\n");
	if(fork1() == 0){
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, var);
	}
	if(fork1() == 0){
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, var);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	return (0);
}
 */
/* #include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	
	

	int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
	
	if(file_desc < 0)
		printf("Error opening the file\n");

	
	

	int copy_desc = dup(file_desc);

	
	

	write(copy_desc,"This will be output to the file named dup.txt\n", 46);

	write(file_desc,"This will also be output to the file named dup.txt\n", 51);

	return 0;
} */


/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	int fd[2];
	if (pipe(fd) == -1) {
		printf("An error ocurred with opening the pipe\n");
		return 1;
	}
		
	int id = fork();
	if (id == -1) {
		printf("An error ocurred with fork\n");
		return 2;
	}
		
	if (id == 0) {
		
		close(fd[0]);
		dup(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1) {
			printf("An error ocurred with writing to the pipe\n");
			return 3;
		}
		close(fd[1]);
	}
	int id2 = fork();
	if (id2 == -1) {
		printf("An error ocurred with fork\n");
		return 2;
	}

	if (id2 == 0) {

		close(fd[1]);
		dup(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1) {
			printf("An error ocurred with reading from the pipe\n");
			return 4;
		}
		printf("Got from child process %d\n", y);
		
		printf("Result is %d * 3 = %d\n", y, y*3);
		close(fd[0]);
	}
	close(fd[1]);
	close(fd[0]);
	wait(0);
	wait(0);
	return (0);
} */


/* #include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	int fd[2];
	int pid1,pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		char *argv[] = {(char *)"wc", (char *)"-l", NULL};
		execvp(argv[0], argv);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		char *argv[] = {(char *)"ls", (char *)"-l", NULL};
		execvp(argv[0], argv);
	}
	close(fd[1]);
	close(fd[0]);
	wait(NULL);
	wait(NULL);
} */

void runPipedCommands(cmdLine* command, char* userInput) {
	int numPipes = 2; // countPipes(userInput);
	int status;
	int i = 0;
	pid_t pid;

	int pipefds[2*numPipes];

	for(i = 0; i < (numPipes); i++){
		if(pipe(pipefds + i*2) < 0) {
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
	}


	int j = 0;
	while(command) {
		pid = fork();
		if(pid == 0) {

			//if not last command
			if(command->next){
				if(dup2(pipefds[j + 1], 1) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			//if not first command&& j!= 2*numPipes
			if(j != 0 ){
				if(dup2(pipefds[j-2], 0) < 0){
					perror(" dup2");///j-2 0 j+1 1
					exit(EXIT_FAILURE);

				}
			}

			for(i = 0; i < 2*numPipes; i++){
					close(pipefds[i]);
			}

			if( execvp(*command->arguments, command->arguments) < 0 ){
					perror(*command->arguments);
					exit(EXIT_FAILURE);
			}
		} else if(pid < 0){
			perror("error");
			exit(EXIT_FAILURE);
		}

		command = command->next;
		j+=2;
	}
	/**Parent closes the pipes and wait for children*/

	for(i = 0; i < 2 * numPipes; i++){
		close(pipefds[i]);
	}

	for(i = 0; i < numPipes + 1; i++)
		wait(&status);
}

