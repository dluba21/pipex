/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:08 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:39:11 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	ft_strcmp_ppx(char *str_1, char *str_2)
{
	int	i;

	i = 0;
	if (ft_strlen(str_1) != ft_strlen(str_2))
		return (-1);
	while (str_1[i])
	{
		if (str_1[i] != str_2[i])
			return (-1);
		i++;
	}
	return (1);
}

void	env_argc_parser(char **env, int argc, t_vars *vars)
{
	if (!env)
		print_error("env is null\n", vars);
	vars->env_ptr = env;
	if (!find_path_var(env, vars))
		print_error("no var path in **env\n", vars);
	vars->cmd_number = argc - 3 - vars->here_doc_flag;
}
