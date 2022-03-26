#include "pipex.h"

void	free_all(t_vars *vars)
{
//	if (vars->cmd)
//		free(vars->cmd);
//	if (vars->flag_to_cmd)
//		free(vars->flag_to_cmd);
//	if (vars->path_to_cmd)
//		free(vars->path_to_cmd);
////	if (vars->cmd_argv)
////	{
////		vars->counter = 0;
////		while (vars->cmd_argv[vars->counter])
////			free(vars->cmd_argv[vars->counter++]);
////		free(vars->cmd_argv);
////	}
//	if (vars->path_var)
//	{
//		vars->counter = 0;
//		while (vars->path_var[vars->counter])
//			free(vars->path_var[vars->counter++]);
//		free(vars->path_var);
//	}
	if (ft_strcmp_ppx(vars->infile, "here_doc") && vars->infile)
		unlink("here_doc");
//
//	char	**cmd_argv;
//
//
//
//	char	**path_var;
//
//
//
//	char	*infile;
//	char	*outfile;
//	char	**env_ptr;

}

void	print_error_and_free(char *str, t_vars *vars)
{
	free_all(vars);
	write(2, str, ft_strlen(str));
	exit (0);
}

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
		print_error_and_free("env is null\n", vars);
	vars->env_ptr = env;
	if (!find_path_var(env, vars))
		print_error_and_free("no var path in **env\n", vars);
	vars->cmd_number = argc - 3 - vars->here_doc_flag;
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


void	cmd_parser(t_vars *vars, char *argv_str, int cmd_flag) //mb flag na commad 1 and cmd 2
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
}




void	filename_parser(int argc, char **argv, t_vars *vars)
{
	vars->infile = argv[1];
	vars->outfile = argv[argc - 1];
	if (access(vars->infile, R_OK | F_OK) == -1)
		print_error_and_free("infile doesn't exist\n", vars);
}

void	heredoc_parser(int argc, char **argv, t_vars *vars)
{
	char	*line;
	int		fd;
	char	*limiter;

	vars->here_doc_flag = 1;
	fd = open("here_doc", O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		print_error_and_free("here_doc error: can't open file\n", vars);
	vars->infile = "here_doc"; //malloc and free at the end
	if (!vars->infile) //can be deleted while norm
		print_error_and_free("here_doc error: can't malloc\n", vars);
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			print_error_and_free("here_doc error: gnl is null\n", vars); //check if nothing written
		if (ft_strcmp_ppx(line, limiter) == 1)
		{
			close(fd);
			free(line);
			free(limiter);
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			print_error_and_free("here_doc error: can't write", vars);
		free(line);
	}
}
