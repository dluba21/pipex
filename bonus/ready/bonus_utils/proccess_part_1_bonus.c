#include "../pipex.h"

void	first_child(t_vars *vars, char **argv)
{
	vars->cmd_counter = 2 + vars->here_doc_flag;
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n", vars);
	if (vars->pid == 0)
	{
		cmd_and_argv_parser(vars, argv[vars->cmd_counter]);
		vars->path_to_cmd = compose_path_and_find_cmd(vars, vars->cmd);
		if (dup2(vars->pipes_fd[1], 1) < 0 || dup2(vars->in_fd, 0) < 0)
			print_error_free_child("dup2 error: child1\n", vars);
		vars->counter = 0;
		while (vars->counter < (vars->cmd_number - 1) * 2)
			close(vars->pipes_fd[vars->counter++]);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error_free_child("execv error: child_1\n", vars);
	}
	vars->cmd_counter++;
}

void	middle_child(t_vars *vars, char **argv)
{
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n", vars);
	if (vars->pid == 0)
	{
		cmd_and_argv_parser(vars, argv[vars->cmd_counter]);
		vars->path_to_cmd = compose_path_and_find_cmd(vars, vars->cmd);
		if (dup2(vars->pipes_fd[(vars->counter - 1) * 2], 0) < 0 \
			|| dup2(vars->pipes_fd[vars->counter * 2 + 1], 1) < 0)
			print_error_free_child("dup2 error: child_mid\n", vars);
		vars->counter = 0;
		while (vars->counter < (vars->cmd_number - 1) * 2)
			close(vars->pipes_fd[vars->counter++]);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error_free_child("execv error: child_mid\n", vars);
	}
	vars->cmd_counter++;
}

void	end_child(t_vars *vars, char **argv)
{
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n", vars);
	if (vars->pid == 0)
	{
		cmd_and_argv_parser(vars, argv[vars->cmd_counter]);
		vars->path_to_cmd = compose_path_and_find_cmd(vars, vars->cmd);
		if (dup2(vars->out_fd, 1) < 0 || \
			dup2(vars->pipes_fd[(vars->counter - 1) * 2], 0) < 0)
			print_error_free_child("dup2 error: end_child\n", vars);
		vars->counter = 0;
		while (vars->counter < (vars->cmd_number - 1) * 2)
			close(vars->pipes_fd[vars->counter++]);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error_free_child("execv error: end_child\n", vars);
	}
	vars->cmd_counter++;
}

void	process_part(t_vars *vars, char **argv)
{
	pipes_creating(vars);
	while (vars->counter < vars->cmd_number)
	{
		if (vars->counter == 0)
			first_child(vars, argv);
		else if (vars->counter == vars->cmd_number - 1)
			end_child(vars, argv);
		else
			middle_child(vars, argv);
		vars->counter++;
	}
	vars->counter = 0;
	while (vars->counter < (vars->cmd_number - 1) * 2)
	{
		close(vars->pipes_fd[vars->counter++]);
		close(vars->pipes_fd[vars->counter++]);
	}
	while (vars->cmd_number-- > 0)
		waitpid(-1, NULL, 0);
}
