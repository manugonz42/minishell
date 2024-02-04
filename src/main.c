/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:19:36 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/30 13:12:49 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

t_global	*init_global(char **envp)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	if (!global)
		malloc_error();
	g_exit_status = 0;
	global->env = create_env_list(envp);
	return (global);
}

int	main(int argc, char const *argv[], char **env)
{
	t_global	*gb;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	gb = init_global(env);
	print_minichell();
	listen(gb);
	return (0);
}
