#include "pipex.h"

void init_vars(t_vars *vars)
{
	vars->cmd = NULL;
	vars->flag_to_cmd = NULL;
	vars->path_to_cmd = NULL; //mb change to unnamed cmd because these commands are subsequent so one var to both commands
	vars->cmd_argv = NULL;
	
	vars->cmd_2 = NULL;
	vars->flag_to_cmd_2 = NULL;
	vars->path_to_cmd_2 = NULL;
	vars->cmd_argv_2 = NULL;
	

	vars->path_var = NULL;


	vars->infile = NULL;
	vars->outfile = NULL;
	vars->env_ptr = NULL;
	
	vars->here_doc_flag = 0;
}

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


void pipes_creating(t_vars *vars)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (i < vars->cmd_number * 2) //(cmd_number - 1) * 2
	{
		if (pipe(pipe_fd) < 0) //add_ro_array
			print_error("pipe error\n");
		vars->pipes_fd[i++] = pipe_fd[0];
		vars->pipes_fd[i++] = pipe_fd[1];
	}
}


void first_child(t_vars *vars, char **argv)
{
	int	fd;

	vars->cmd_counter = 2 + here_doc_flag;
	cmd_parser(vars, argv[vars->cmd_counter++], 1);
	vars.path_to_cmd = compose_path_and_find_cmd(&vars, vars.cmd); //mb first command
	vars.cmd_argv = compose_argv_to_child(&vars, vars.cmd, vars.flag_to_cmd);
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n"); //and free all
	if (vars->pid == 0)
	{
		fd = open(vars->infile, O_RDONLY);
		if (fd == -1)
			print_error("open error: child1\n");
			//unlink(heredoc); add to print_error
		if (dup2(vars->pipes_fd[1], 1) < 0 || dup2(fd, 0) < 0)
			print_error("dup2 error: child1\n");
		close(vars->pipes_fd[0]);
		close(vars->pipes_fd[1]);
		close(fd);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error("execv error: child_1\n"); //and free child args
	}
}

void middle_child(t_vars *vars, char **argv)
{
	cmd_parser(vars, argv[vars->cmd_counter++], 1);
	vars.path_to_cmd = compose_path_and_find_cmd(&vars, vars.cmd);
	vars.cmd_argv = compose_argv_to_child(&vars, vars.cmd, vars.flag_to_cmd);
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n"); //and free all
	if (vars->pid == 0)
	{
		if (dup2(vars->pipes_fd[vars->(counter - 1) * 2], 1) < 0 \
			|| dup2(vars->pipes_fd[vars->counter * 2 + 1], 0) < 0)
			print_error("dup2 error: child_mid\n");
		close(vars->pipes_fd[vars->(counter - 1) * 2]);
		close(vars->pipes_fd[vars->counter * 2 + 1]);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error("execv error: child_mid\n"); //and free child args
	}
}


void end_child(t_vars *vars, char **argv)
{
	int	fd;

	cmd_parser(vars, argv[vars->cmd_counter++], 1);
	vars.path_to_cmd = compose_path_and_find_cmd(&vars, vars.cmd); //mb first command
	vars.cmd_argv = compose_argv_to_child(&vars, vars.cmd, vars.flag_to_cmd);
	vars->pid = fork();
	if (vars->pid < 0)
		print_error("fork error\n"); //and free all
	if (vars->pid == 0)
	{
		fd = open(vars->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			print_error("open error: end_child\n");
			//unlink(heredoc); add to print_error
		if (dup2(vars->fd, 1) < 0 || dup2(vars->pipes_fd[(vars->counter - 1) * 2], 0) < 0)
			print_error("dup2 error: end_child\n");
		close(vars->pipes_fd[(vars->counter - 1) * 2]);
		close(vars->pipes_fd[vars->counter * 2 + 1]);
		close(fd);
		if (execve(vars->path_to_cmd, vars->cmd_argv, vars->env_ptr) == -1)
			print_error("execv error: end_child\n"); //and free child args
	}
}



void	process_part(t_vars *vars, argv)
{
//	vars->pipes_fd = ft_bzero(); //malloc
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
	while(vars->counter < vars->cmd_number * 2) //close all pipes
	{
		close(vars->pipes_fd[vars->counter++]);
		close(vars->pipes_fd[vars->counter++]);
	}
	
	while (vars->cmd_counter-- >= 0) //wait for all processes
		waitpid(-1, 0, NULL);
}





int main(int argc, char **argv, char **env)
{
	t_vars	vars; //need to set NULL when init

	init_vars(&vars);
	if (argc < 5)
		print_error("problem with argc\n");
	if (ft_strcmp_ppx("here_doc", argv[1]) == 1)
		heredoc_parser(argc, argv, vars);
	env_parser(env, &vars);
	filename_parser(argc, argv, &vars);
	process_part(&vars, argv);

	return (0);
	
}
