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
