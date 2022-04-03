#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_vars
{
	int		pid;
	char	*cmd;
	char	**cmd_argv;
	char	*path_to_cmd;
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

typedef struct s_split
{
	char	**big_str;
	int		k;
	int		word_counter;
	int		len;
	char	*str;
	char	c;
	int		i;
	int		j;
}				t_split;

void	word_counter_ppx(char *str, char c, t_split *s);
void	print_error_free_child(char *str, t_vars *vars);
void	print_error(char *str, t_vars *vars);
void	free_path_var(t_vars *vars);
void	free_child(t_vars *vars);
int		ft_strncmp_ppx(char *str_1, char *str_2, int n);
int		ft_strcmp_ppx(char *str_1, char *str_2);
void	env_argc_parser(char **env, int argc, t_vars *vars);
char	**ft_split_ppx(char *str, char c);
int		find_path_var(char **env, t_vars *vars);
void	cmd_and_argv_parser(t_vars *vars, char *argv_str);
void	filename_parser(int argc, char **argv, t_vars *vars);
void	heredoc_parser(char **argv, t_vars *vars);
void	init_vars(t_vars *vars);
char	*compose_path_and_find_cmd(t_vars *vars, char *cmd);
void	pipes_creating(t_vars *vars);
void	process_part(t_vars *vars, char **argv);
void	first_child(t_vars *vars, char **argv);
void	middle_child(t_vars *vars, char **argv);
void	end_child(t_vars *vars, char **argv);

#endif
