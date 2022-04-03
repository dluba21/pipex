#include "../pipex.h"

void	free_child(t_vars *vars)
{
	int	i;

	if (vars->path_to_cmd)
	{
		free(vars->path_to_cmd);
		vars->path_to_cmd = NULL;
	}
	free_path_var(vars);
	if (vars->cmd_argv)
	{
		i = 0;
		while (vars->cmd_argv[i])
			free(vars->cmd_argv[i++]);
		free(vars->cmd_argv);
		vars->cmd_argv = NULL;
	}
}

void	free_path_var(t_vars *vars)
{
	int	i;

	if (vars->path_var)
	{
		i = 0;
		while (vars->path_var[i])
			free(vars->path_var[i++]);
		free(vars->path_var);
		vars->path_var = NULL;
	}
}

void	print_error_free_child(char *str, t_vars *vars)
{
	free_child(vars);
	write(2, str, ft_strlen(str));
	exit(0);
}

void	print_error(char *str, t_vars *vars)
{
	free_path_var(vars);
	write(2, str, ft_strlen(str));
	if (vars->here_doc_flag == 1)
		unlink("here_doc");
	exit (0);
}
