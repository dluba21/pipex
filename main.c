#include "pipex.h"

char *compose_path_and_find_cmd(t_vars *vars, char *cmd) //change to no matter what num of cmd
{
	char	*temp_1;
	char	*temp_2;

	if (access(cmd, X_OK | F_OK) != -1)
	{
		printf("argv[i] is the path\n");
		return (cmd);
	}
	while (*vars->path_var)
	{
		temp_1 = ft_strdup("/");
		temp_2 = ft_strjoin(*vars->path_var, temp_1); //can free strdup at ft_strjoin
		free(temp_1);
		temp_2 = ft_strjoin(temp_2, cmd);
		if (access(temp_2, X_OK | F_OK) != -1)
			return (temp_2);
		free(temp_2);
		vars->path_var++;
	}
	print_error("error: command hasn't been found\n");
	return (NULL);
}

char **compose_argv_to_child(t_vars *vars, char *cmd, char *flag_to_cmd)
{
	char	**cmd_args;
	int		cmd_args_size;

	cmd_args_size = 1;
	if (flag_to_cmd != NULL) //mb more than one argument in flag
		cmd_args_size = 2;
	cmd_args = (char **)malloc(sizeof(char *) * cmd_args_size + 1);
//	printf("cmdargs[0] = %s\n", cmd_args[0]);
	if (!cmd_args)
		print_error("malloc error: cmd_argv\n");

	cmd_args[0] = cmd; //path of cmd or name of cmd?
	
	cmd_args[cmd_args_size] = NULL;
	if (cmd_args_size == 2)
		cmd_args[1] = flag_to_cmd;
	return (cmd_args);
		
}
void child_1_actions(t_vars *vars)
{
	int	fd;
	int	ret;

	fd = open(vars->infile, O_RDONLY);
	if (fd == -1)
		print_error("open error: child_1\n"); //mb should exit and in the main process

	if (dup2(vars->pipe_fd[1], 1) < 0 || dup2(fd, 0) < 0)
		print_error("dup2 error: child1\n");
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(fd);
	if (execve(vars->path_to_cmd_1, vars->cmd_argv_1, vars->env_ptr) == -1)
	{
		
		print_error("execv error: child_1\n"); //and free child args
	}

}

void child_2_actions(t_vars *vars)
{
	int	fd;
	int	ret;

	fd = open(vars->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error("open error: child_2\n"); //mb should exit and in the main proces


	if (dup2(vars->pipe_fd[0], 0) < 0 || dup2(fd, 1) < 0)
		print_error("dup2 error: child1\n");

	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(fd);

	
	if (execve(vars->path_to_cmd_2, vars->cmd_argv_2, vars->env_ptr) == -1)
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
	else if (vars->pid_1 == 0)
		child_1_actions(vars);
	vars->pid_2 = fork();
	if (vars->pid_2 == -1)
		print_error("fork error\n");
	else if (vars->pid_2 == 0)
		child_2_actions(vars);



	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	waitpid(vars->pid_1, NULL, 0);
	waitpid(vars->pid_2, NULL, 0);
}

void init_vars(t_vars *vars)
{
	vars->cmd_1 = NULL;
	vars->flag_to_cmd_1 = NULL;
	vars->path_to_cmd_1 = NULL; //mb change to unnamed cmd because these commands are subsequent so one var to both commands
	vars->cmd_argv_1 = NULL;
	
	vars->cmd_2 = NULL;
	vars->flag_to_cmd_2 = NULL;
	vars->path_to_cmd_2 = NULL;
	vars->cmd_argv_2 = NULL;
	

	vars->path_var = NULL;


	vars->infile = NULL;
	vars->outfile = NULL;
	vars->env_ptr = NULL;
}

int main(int argc, char **argv, char **env)
{
	t_vars	vars; //need to set NULL when init

	init_vars(&vars);
	if (argc != 5)
		print_error("problem with argc\n");
	env_parser(env, &vars);
//	printf("PATH = %s\n", *vars.path_var);
	filename_parser(argc, argv, &vars);
	cmd_parser(&vars, argv[2], 1);
	cmd_parser(&vars, argv[3], 2);
	vars.path_to_cmd_1 = compose_path_and_find_cmd(&vars, vars.cmd_1); //mb first command
	vars.cmd_argv_1 = compose_argv_to_child(&vars, vars.cmd_1, vars.flag_to_cmd_1);
	vars.cmd_argv_2 = compose_argv_to_child(&vars, vars.cmd_2, vars.flag_to_cmd_2);
	vars.path_to_cmd_2 = compose_path_and_find_cmd(&vars, vars.cmd_2); //mb first commandshould be passed
//	printf("infile = %s\n", vars.infile);
//	printf("outfile = %s\n", vars.outfile);
//	printf("cmd_1 = %s\n", vars.path_to_cmd_1);
//	printf("flags_1 = %s\n", vars.cmd_argv_1[0]);
//	printf("cmd_2 = %s\n", vars.path_to_cmd_2);
//	printf("flags_2 = %s\n", vars.cmd_argv_2[1]);
//
	process_part(&vars);
//
	return (0);
	
}
