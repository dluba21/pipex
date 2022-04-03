/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:34 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:38:54 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	init_vars(&vars, argv);
	if (argc != 5)
		print_error("problem with argc\n");
	env_parser(env, &vars);
	filename_parser(argv, &vars);
	process_part(&vars);
	free_path_var(&vars);
	return (0);
}
