#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
typedef struct s_vars
{
	int		pid_1;
	char	*cmd_1;
	char	*flag_to_cmd_1;
	char	*path_to_cmd_1; //mb change to unnamed cmd because these commands are subsequent so one var to both commands
	char	**cmd_argv_1;
	
	int		pid_2;
	char	*cmd_2;
	char	*flag_to_cmd_2;
	char	*path_to_cmd_2;
	char	**cmd_argv_2;
	

	char	**path_var;


	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	char	**env_ptr;
	
}				t_vars;

void	print_error(char *str);
int ft_strncmp_ppx(char *str_1, char *str_2, int n);
void	env_parser(char **env, t_vars *vars);
int find_path_var(char **env, t_vars *vars);
void	cmd_parser(t_vars *vars, char *argv_str, int cmd_flag);
void	filename_parser(int argc, char **argv, t_vars *vars);

#endif
