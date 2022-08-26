#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int	main(void)
{
	int p[2];
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

#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
  
int main()
{
    // open() returns a file descriptor file_desc to a 
    // the file "dup.txt" here"
  
    int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
      
    if(file_desc < 0)
        printf("Error opening the file\n");
      
    // dup() will create the copy of file_desc as the copy_desc
    // then both can be used interchangeably.
  
    int copy_desc = dup(file_desc);
          
    // write() will write the given string into the file
    // referred by the file descriptors
  
    write(copy_desc,"This will be output to the file named dup.txt\n", 46);
          
    write(file_desc,"This will also be output to the file named dup.txt\n", 51);
      
    return 0;
}