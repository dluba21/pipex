#include "../pipex.h"

int	find_path_var(char **env, t_vars *vars)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp_ppx("PATH=", env[i], 5) == 1)
		{
			vars->path_var = ft_split(env[i] + 5, ':');
			if (!vars->path_var)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cmd_and_argv_parser(t_vars *vars, char *argv_str)
{
	char	**buf_str;

	buf_str = ft_split_ppx(argv_str, ' ');
	if (!buf_str)
		print_error_free_child("can't malloc\n", vars);
	vars->cmd = *buf_str;
	vars->cmd_argv = buf_str;
}

void	filename_parser(int argc, char **argv, t_vars *vars)
{
	if (!vars->here_doc_flag)
	{
		if (access(argv[1], R_OK | F_OK) == -1)
			print_error("infile doesn't exist\n", vars);
		vars->in_fd = open(argv[1], O_RDONLY);
	}
	if (vars->here_doc_flag == 1)
		vars->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		vars->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (vars->in_fd < 0 || vars->out_fd < 0)
		print_error("error: can't open", vars);
}

int	heredoc_p2(t_vars *vars)
{
	int	fd;

	vars->here_doc_flag = 1;
	fd = open("here_doc", O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		print_error("here_doc error: can't open file\n", vars);
	return (fd);
}

void	heredoc_parser(char **argv, t_vars *vars)
{
	char	*line;
	int		fd;
	char	*limiter;

	vars->in_fd = heredoc_p2(vars);
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			print_error("here_doc error: gnl is null\n", vars);
		if (ft_strcmp_ppx(line, limiter) == 1)
		{
			free(line);
			free(limiter);
			return ;
		}
		if (write(vars->in_fd, line, ft_strlen(line)) == -1)
			print_error("here_doc error: can't write", vars);
		free(line);
	}
}
