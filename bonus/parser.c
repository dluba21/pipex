#include "pipex.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (0);
}

int ft_strncmp_ppx(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str_1[i] != str_2[i])
			return (-1);
		i++;
	}
	return (1);
}

int	ft_strcmp_ppx(char *str_1, char *str_2)
{
	int	i;

	i = 0;
	if (ft_strlen(str_1) != ft_strlen(str_2))
		return (-1);
	while (str_1[i])
	{
		if (str_1[i] != str_2[i])
			return (-1);
		i++;
	}
	return (1);
}

void	env_argc_parser(char **env, int argc, t_vars *vars) //good
{
	int	i;

	i = 0;
	if (!env)
		print_error("env is null\n");
	vars->env_ptr = env;
	if (!find_path_var(env, vars)) //here I initialized PATH variable
		print_error("no var path in **env\n"); //and check on absence
	vars->cmd_number = argc - 2 - vars->here_doc_flag;
}

int find_path_var(char **env, t_vars *vars)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp_ppx("PATH=", env[i], 5) == 1)
		{
			vars->path_var = ft_split(env[i] + 5, ':'); //rewrite split to NULL as parameter
			if (!vars->path_var)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}


void	cmd_parser(t_vars *vars, char *argv_str) //mb flag na commad 1 and cmd 2
{
	char	buf_str[10000]; //mb echo "100000000 symbols" so change way mb
	int		i;
	char	ret_str;

	i = 0;
	while (*argv_str != ' ' && *argv_str != '\t' && *argv_str)
		buf_str[i++] = *argv_str++;
	buf_str[i] = 0;
		vars->cmd = ft_strdup(buf_str);
	while (*argv_str == ' ' || *argv_str == '\t')
		argv_str++;
	
	i = 0;
	while (*argv_str)
		buf_str[i++] = *argv_str++; //can be spaces in path... "/ "
	buf_str[i] = 0;
	if (i == 0)
		return ;
		vars->flag_to_cmd = ft_strdup(buf_str);
//	printf("cmd = %s\n", vars->cmd);
//	printf("flag_to_cmd = %s\n", vars->flag_to_cmd);
}




void	filename_parser(int argc, char **argv, t_vars *vars)
{
	vars->infile = argv[1];
	vars->outfile = argv[argc - 1];
	if (access(vars->infile, R_OK | F_OK) == -1)
		print_error("infile doesn't exist\n");
}

void	heredoc_parser(int argc, char **argv, t_vars *vars)
{
	char	*line;
	int		fd;

	vars->here_doc_flag = 1;
	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd < 0)
		print_error("here_doc error: can't open file\n");
	vars->infile = ft_strdup(here_doc);
	if (!vars->infile) //can be deleted while norm
		print_error("here_doc error: can't malloc\n");
	while (1)
	{
		line = getnextline(0);
		if (!line)
			print_error("here_doc error: gnl is null\n"); //check if nothing written
		if (ft_strcmp_ppx(line, argv[2]) == 1)
		{
			close(fd);
			free(line);
			return ;
		}
		if (write(fd, line, sizeof(line)) == -1)
			print_error("here_doc error: can't write");
		free(line);
	}
}
