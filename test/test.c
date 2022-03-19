#include "../pipex.h"

int main()
{
	int	pipe_fd[2];
	int ret;
	int fd;

	pipe(pipe_fd);
	
	int pid_1;
	int pid_2;
	fd = open("infile", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	pid_1 = fork();
	if (pid_1 == 0)
	{
		
//		write(fd,  "lol", 3);
		printf("pid_1_child = %d\n", getpid());
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
//		close(fd);
//		sleep(1000);
		if (execl("/usr/bin/grep", "grep", "lol", NULL) == -1)
		{
			printf("aboba1\n");
			exit(1);
			
		}
		
		
	}
//	sleep(100);
	fd = open("outfile", O_WRONLY | O_APPEND);
	dup2(fd, 1);
	pid_2 = fork();
	if (pid_2 == 0)
	{
//		write(fd,  "lol", 3);
		printf("pid_2_child = %d\n", getpid());
		dup2(pipe_fd[0], 0);
		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
//		sleep(1000);
//		close(fd);
//		sleep(1000);
		if (execl("/usr/bin/wc", "wc", "-l", NULL) == -1)
		{
			printf("aboba2\n");
			exit(1);
			
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
//	if (pid_1 != 0)
//		printf("pid_1 = %d\n", pid_1);
//	if (pid_1 != 0)
//		printf("pid_1 = %d\n", pid_2);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
} 
