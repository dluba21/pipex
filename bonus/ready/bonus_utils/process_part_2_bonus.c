#include "pipex_bonus.h"

void	init_vars(t_vars *vars)
{
	vars->cmd = NULL;
	vars->path_to_cmd = NULL;
	vars->cmd_argv = NULL;
	vars->infile = NULL;
	vars->outfile = NULL;
	vars->env_ptr = NULL;
	vars->counter = 0;
	vars->in_fd = 0;
	vars->out_fd = 0;
}

char	*compose_path_and_find_cmd(t_vars *vars, char *cmd)
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
	print_error_free_child("error: command not found\n", vars);
	return (NULL);
}

void	pipes_creating(t_vars *vars)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (i < (vars->cmd_number - 1) * 2)
	{
		if (pipe(pipe_fd) < 0)
			print_error("pipe error\n", vars);
		vars->pipes_fd[i++] = pipe_fd[0];
		vars->pipes_fd[i++] = pipe_fd[1];
	}
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	init_vars(&vars);
	if (argc < 5)
		print_error("problem with argc\n", &vars);
	if (ft_strcmp_ppx("here_doc", argv[1]) == 1)
		heredoc_parser(argv, &vars);
	filename_parser(argc, argv, &vars);
	env_argc_parser(env, argc, &vars);
	process_part(&vars, argv);
	if (vars.here_doc_flag == 1)
		unlink("here_doc");
	free_path_var(&vars);
	return (0);
}
