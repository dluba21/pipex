#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "libft/libft.h"
typedef struct s_vars
{
	int		pid;
	char	*cmd;
	char	*flag_to_cmd;
	char	*path_to_cmd; //mb change to unnamed cmd because these commands are subsequent so one var to both commands
	char	**cmd_argv;
	
	

	char	**path_var;



	char	*infile;
	char	*outfile;
	char	**env_ptr;
	
	int		here_doc_flag;
	int		cmd_number;
	int		cmd_counter;
	int		pipes_fd[OPEN_MAX];
	int		counter;
}				t_vars;

void	print_error(char *str);
int ft_strncmp_ppx(char *str_1, char *str_2, int n);
void	env_parser(char **env, t_vars *vars);
int find_path_var(char **env, t_vars *vars);
void	cmd_parser(t_vars *vars, char *argv_str, int cmd_flag);
void	filename_parser(int argc, char **argv, t_vars *vars);

#endif
