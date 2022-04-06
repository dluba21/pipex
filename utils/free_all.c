/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:30 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:39:01 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (0);
}

void	free_path_var(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->path_var)
	{
		while (vars->path_var[i])
			free(vars->path_var[i++]);
		free(vars->path_var);
	}
}

void	free_child(t_vars *vars, int cmd_flag)
{
	int	i;

	i = 0;
	if (cmd_flag == 1 && vars->argv_to_cmd_1)
	{
		while (vars->argv_to_cmd_1[i])
			free(vars->argv_to_cmd_1[i++]);
		free(vars->argv_to_cmd_1);
	}
	else if (cmd_flag == 2 && vars->argv_to_cmd_2)
	{
		while (vars->argv_to_cmd_2[i])
			free(vars->argv_to_cmd_2[i++]);
		free(vars->argv_to_cmd_2);
	}
	if (cmd_flag == 1 && vars->path_to_cmd_1)
		free(vars->path_to_cmd_1);
	else if (cmd_flag == 2 && vars->path_to_cmd_2)
		free(vars->path_to_cmd_2);
	free_path_var(vars);
}

void	print_parent_error(char *str, t_vars *vars)
{
	free_path_var(vars);
	print_error(str);
}

void	print_child_error(char *str, t_vars *vars, int cmd_flag)
{
	if (cmd_flag == 1)
		free_child(vars, 1);
	if (cmd_flag == 2)
		free_child(vars, 2);
	print_error(str);
}
