/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:41 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:39:35 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_vars
{
	int		pid_1;
	char	*cmd_1;
	char	*path_to_cmd_1;
	char	**argv_to_cmd_1;
	int		pid_2;
	char	*cmd_2;
	char	*path_to_cmd_2;
	char	**argv_to_cmd_2;
	char	**argv;
	char	**path_var;
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	char	**env_ptr;
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

void	print_error(char *str);
void	print_parent_error(char *str, t_vars *vars);
void	print_child_error(char *str, t_vars *vars, int cmd_flag);
void	free_path_var(t_vars *vars);
void	free_child(t_vars *vars, int cmd_flag);
int		ft_strncmp_ppx(char *str_1, char *str_2, int n);
void	env_parser(char **env, t_vars *vars);
int		find_path_var(char **env, t_vars *vars);
void	cmd_and_argv_parser(t_vars *vars, char *argv_str, int cmd_flag);
void	filename_parser(char **argv, t_vars *vars);
char	**ft_split_ppx(char *str, char c);
void	word_counter_ppx(char *str, char c, t_split *s);
void	process_part(t_vars *vars);
void	init_vars(t_vars *vars, char **argv);

#endif
