#include "pipex.h"

char	*compose_path_and_find_cmd(t_vars *vars, char *cmd, int cmd_flag)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (access(cmd, X_OK | F_OK) != -1)
		return (ft_strdup(cmd));
	while (vars->path_var[i])
	{
		temp = ft_strjoin(vars->path_var[i++], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK | F_OK) != -1)
			return (path);
		free(path);
	}
	if (cmd_flag == 1)
		print_child_error("error: command not found\n", vars, 1);
	else
		print_child_error("error: command not found\n", vars, 2);
	return (NULL);
}

void	child_1_actions(t_vars *vars)
{
	cmd_and_argv_parser(vars, vars->argv[2], 1);
	vars->path_to_cmd_1 = compose_path_and_find_cmd(vars, vars->cmd_1, 1);
	if (dup2(vars->pipe_fd[1], 1) < 0 || dup2(vars->in_fd, 0) < 0)
		print_child_error("dup2 error: child1\n", vars, 1);
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(vars->in_fd);
	if (execve(vars->path_to_cmd_1, vars->argv_to_cmd_1, vars->env_ptr) == -1)
		print_child_error("execv error: child_1\n", vars, 1);
}

void	child_2_actions(t_vars *vars)
{
	cmd_and_argv_parser(vars, vars->argv[3], 2);
	vars->path_to_cmd_2 = compose_path_and_find_cmd(vars, vars->cmd_2, 2);
	if (dup2(vars->pipe_fd[0], 0) < 0 || dup2(vars->out_fd, 1) < 0)
		print_child_error("dup2 error: child2\n", vars, 2);
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	close(vars->out_fd);
	if (execve(vars->path_to_cmd_2, vars->argv_to_cmd_2, vars->env_ptr) == -1)
		print_child_error("execv error: child_2\n", vars, 2);
}

void	process_part(t_vars *vars)
{
	if (pipe(vars->pipe_fd) == -1)
		print_parent_error("pipe error\n", vars);
	vars->pid_1 = fork();
	if (vars->pid_1 == -1)
		print_parent_error("fork error\n", vars);
	else if (vars->pid_1 == 0)
		child_1_actions(vars);
	vars->pid_2 = fork();
	if (vars->pid_2 == -1)
		print_parent_error("fork error\n", vars);
	else if (vars->pid_2 == 0)
		child_2_actions(vars);
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	waitpid(vars->pid_1, NULL, 0);
	waitpid(vars->pid_2, NULL, 0);
}

void	init_vars(t_vars *vars, char **argv)
{
	vars->cmd_1 = NULL;
	vars->path_to_cmd_1 = NULL;
	vars->argv_to_cmd_1 = NULL;
	vars->cmd_2 = NULL;
	vars->path_to_cmd_2 = NULL;
	vars->argv_to_cmd_2 = NULL;
	vars->argv = argv;
	vars->path_var = NULL;
	vars->env_ptr = NULL;
}
