#include "../pipex.h"

int main()
{
	int	pipe_fd[2];
	int ret;
	int fd;

	pipe(pipe_fd);
	
	int pid_1;
	int pid_2;

	printf("pid_1 = %d\n", getpid());
//	sleep(1000);

	pid_1 = fork();
	if (pid_1 == 0)
	{

//		write(fd,  "lol", 3);
		fd = open("infile", O_RDONLY);
		printf("pid_1 = %d\n", getpid());
//		dup2(fd, 0);
//		dup2(pipe_fd[1], 1);

		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		
		execl("grep", "grep", "aboba", NULL);
		sleep(100);
			
	}
//
//	fd = open("outfile", O_WRONLY | O_APPEND);
//	dup2(fd, 1);
//	pid_2 = fork();
//	if (pid_2 == 0)
//	{
////		write(fd,  "lol", 3);
//		dup2(pipe_fd[0], 0);
//
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		printf("pid_1 = %d", getpid());
////		sleep(1000);
//		execl("wc", "wc", "-l", NULL);
//	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_1, NULL, 0);
//	waitpid(pid_2, NULL, 0);
}

