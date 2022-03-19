#include "pipex.h"

void	print_error(char *str)
{
	perror(str);
	exit (0);
}

void	filename_parser(int argc, char **argv, t_vars *vars)
{
	vars->infile = argv[1];
	vars->outfile = argv[argc - 1];
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

void	env_parser(char **env, t_vars *vars)
{
	int	i;

	i = 0;
	if (!env)
		print_error("env is null\n");
	vars->env_ptr = env; //malloc nado?
	if (!find_path_var(env, vars)) //here I initialized PATH variable
		print_error("no var path in **env\n"); //and check on absence
}

void	cmd_parser(char *argv_str, t_vars *vars) //mb flag na commad 1 and cmd 2
{
	char	buf_str[10000]; //mb echo "100000000 symbols" so change way mb
	int		i;

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
	vars->flag_to_cmd = ft_strdup(buf_str);
//	printf("cmd = %s\n", vars->cmd);
//	printf("flag_to_cmd = %s\n", vars->flag_to_cmd);
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
	print_error("command haven't found\n");
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

	fd = open(vars->infile, O_RDONLY);
	
	if (fd == -1)
		print_error("open error: child_1\n"); //mb should exit and in the main process
	printf("fd = %d\n", fd);
//	 pochemu imenno takoy poryadok argumentov?
	printf("fd_pipe_0 = %d\n", vars->pipe_fd[0]);
	printf("fd_pipe_1 = %d\n", vars->pipe_fd[1]);
	close(vars->pipe_fd[0]);
	
	ret = dup2(1, vars->pipe_fd[1]);
	printf("ret = %d\n", ret);
//	if ( < 0)
//		print_error("dup2 error: child\n");
	
	printf("before exec!\n");

//	close(vars->pipe_fd[1]);


//	compose_argv_to_child(vars); //make argv to cmd
//	ret = execve("/bin/ls", vars->cmd_argv, vars->env_ptr);
//	free_child();
	exit (1);
	if (ret == -1)
		print_error("execv error: child_1\n"); //and free child args
}

void	process_part(t_vars *vars)
{
	if (pipe(vars->pipe_fd) == -1)
		print_error("pipe error\n");
	
	vars->pid = fork();
	if (vars->pid == -1)
		print_error("fork error\n");
	else if (vars->pid != 0)
		wait(NULL);
	else
		child_1_actions(vars);
//
//	if (dup2(vars->pipe_fd[0], 0) == -1)
//		print_error("dup2 error: parent\n");
//
//	close(vars->pipe_fd[0]);
//	close(vars->pipe_fd[1]);
	
	
}


int main(int argc, char **argv, char **env)
{
	t_vars	vars; //need to set NULL when init

//	if (argc != 5)
//		print_error("problem with argc\n");
	
	env_parser(env, &vars);
//	printf("PATH = %s\n", *vars.path_var);
	cmd_parser(argv[2], &vars);
	filename_parser(argc, argv, &vars);
	compose_path_and_find_cmd(&vars); //mb first command should be passed
	process_part(&vars);
//
	
}
