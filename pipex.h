#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
typedef struct s_vars
{
	char	*cmd;
	char	*flag_to_cmd;
	char	*path_to_cmd; //mb change to unnamed cmd because these commands are subsequent so one var to both commands
	char	**cmd_argv;
	char	**path_var;
	int		pid;
	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	char	**env_ptr;
	
}				t_vars;

#endif
