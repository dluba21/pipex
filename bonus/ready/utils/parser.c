/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:36 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:38:53 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp_ppx(char *str_1, char *str_2, int n)
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

void	env_parser(char **env, t_vars *vars)
{
	int	i;

	i = 0;
	if (!env)
		print_error("env is null\n");
	vars->env_ptr = env;
	if (!find_path_var(env, vars))
		print_error("no var path in **env\n");
}

int	find_path_var(char **env, t_vars *vars)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp_ppx("PATH=", env[i], 5) == 1)
		{
			vars->path_var = ft_split(env[i] + 5, ':');
			if (!vars->path_var)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cmd_and_argv_parser(t_vars *vars, char *argv_str, int cmd_flag)
{
	char	**buf_str;

	buf_str = ft_split_ppx(argv_str, ' ');
	if (!buf_str && cmd_flag == 1)
		print_child_error("can't malloc\n", vars, 1);
	else if (!buf_str && cmd_flag == 2)
		print_child_error("can't malloc\n", vars, 2);
	if (cmd_flag == 1)
		vars->cmd_1 = *buf_str;
	else
		vars->cmd_2 = *buf_str;
	if (cmd_flag == 1)
		vars->argv_to_cmd_1 = buf_str;
	else
		vars->argv_to_cmd_2 = buf_str;
}

void	filename_parser(char **argv, t_vars *vars)
{
	if (access(argv[1], R_OK | F_OK) == -1)
		print_error("infile doesn't exist\n");
	vars->in_fd = open(argv[1], O_RDONLY);
	vars->out_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (vars->in_fd < 0 || vars->out_fd < 0)
		print_error("error: can't open");
}
