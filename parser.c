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

void	env_parser(char **env, t_vars *vars) //good
{
	int	i;

	i = 0;
	if (!env)
		print_error("env is null\n");
	vars->env_ptr = env; //malloc nado?
	if (!find_path_var(env, vars)) //here I initialized PATH variable
		print_error("no var path in **env\n"); //and check on absence
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
	if (cmd_flag == 1)
		vars->cmd_1 = ft_strdup(buf_str);
	else
		vars->cmd_2 = ft_strdup(buf_str);
	while (*argv_str == ' ' || *argv_str == '\t')
		argv_str++;
	
	i = 0;
	while (*argv_str)
		buf_str[i++] = *argv_str++; //can be spaces in path... "/ "
	buf_str[i] = 0;
	if (i == 0)
		return ;
	if (cmd_flag == 1)
		vars->flag_to_cmd_1 = ft_strdup(buf_str);
	else
		vars->flag_to_cmd_2 = ft_strdup(buf_str);
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
