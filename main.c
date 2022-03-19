#include "pipex.h"

void	print_error(char *str)
{
	perror(str);
	exit (0);
}









void compose_path_and_find_cmd(t_vars *vars) //change to no matter what num of cmd
{
	char	*cmd_temp;
	char	*temp;

	if (access(vars->cmd, X_OK | F_OK) != -1)
	{
		printf("argv[2] is the path\n");
		vars->path_to_cmd = vars->cmd;
		return ;
	}
	while (*vars->path_var)
	{
		temp = ft_strdup("/");
		cmd_temp = ft_strjoin(*vars->path_var, temp); //can free strdup at ft_strjoin
		free(temp);
		cmd_temp = ft_strjoin(cmd_temp, vars->cmd);
		if (access(cmd_temp, X_OK | F_OK) != -1)
		{
			vars->path_to_cmd = cmd_temp;
//			printf("found  cmd!\n");
			return ;
		}
		free(cmd_temp);
		vars->path_var++;
	}
	print_error("error: command hasn't been found\n");
}

void compose_argv_to_child(t_vars *vars)
{
	char	**cmd_args;
	int		cmd_args_size;

	cmd_args_size = 1;
	if (vars->flag_to_cmd) //mb more than one argument in flag
		cmd_args_size = 2;
	cmd_args = (char **)malloc(sizeof(char *) * cmd_args_size + 1);
//	printf("cmdargs[0] = %s\n", cmd_args[0]);
	if (!cmd_args)
		print_error("malloc error: cmd_argv\n");

	cmd_args[0] = vars->cmd; //path of cmd or name of cmd?
	
	cmd_args[cmd_args_size] = NULL;
	if (cmd_args_size == 2)
		cmd_args[1] = vars->flag_to_cmd;
	vars->cmd_argv = cmd_args;
	while(*vars->cmd_argv)
		printf("argv: %s\n", *vars->cmd_argv++);
		
}
void child_1_actions(t_vars *vars)
{
	int	fd;
	int	ret;

	cmd_parser(vars->argv_ptr[2], vars);
	fd = open(vars->infile, O_RDONLY);
	if (fd == -1)
		print_error("open error: child_1\n"); //mb should exit and in the main process


	if (dup2(vars->pipe_fd[1], 1) < 0 || dup2(fd, 0) < 0)
		print_error("dup2 error: child1\n");
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(fd);


	compose_argv_to_child(vars); //make argv to cmd
//	free_child();
	if (execve(vars->path_to_cmd, vars->cmd, vars->env_ptr) == -1)
	{
		print_error("execv error: child_1\n"); //and free child args
	}
}

void child_2_actions(t_vars *vars)
{
	int	fd;
	int	ret;

	cmd_parser(vars->argv_ptr[4], vars);
	fd = open(vars->outfile, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		print_error("open error: child_2\n"); //mb should exit and in the main process
	printf("fd = %d\n", fd);
	
	if (dup2(vars->pipe_fd[0], 0) < 0 || dup2(fd, 1) < 0)
		print_error("dup2 error: child1\n");
	
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(fd);
	
	compose_argv_to_child(vars);
	if (execve(vars->path_to_cmd, vars->cmd, vars->env_ptr) == -1)
	{
		print_error("execv error: child_2\n"); //and free child args
	}


}

void	process_part(t_vars *vars)
{
	if (pipe(vars->pipe_fd) == -1)
		print_error("pipe error\n");
	vars->pid_1 = fork();
	if (vars->pid_1 == -1)
		print_error("fork error\n");
	else
		child_1_actions(vars);
	vars->pid_2 = fork();
	if (vars->pid_2 == -1)
		print_error("fork error\n");
	else
		child_2_actions(vars);



	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	waitpid(vars->pid_1, NULL, 0);
	waitpid(vars->pid_2, NULL, 0);
	
}


int main(int argc, char **argv, char **env)
{
	t_vars	vars; //need to set NULL when init

//	if (argc != 5)
//		print_error("problem with argc\n");
	vars.argv_ptr = argv;
	env_parser(env, &vars);
//	printf("PATH = %s\n", *vars.path_var);
	filename_parser(argc, argv, &vars);
	compose_path_and_find_cmd(&vars); //mb first command should be passed
	printf("%s\n", vars.infile);
//	process_part(&vars);
//
	
}
