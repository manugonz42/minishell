/* ************************************************************************** */
/*													                        */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:16 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/21 13:06:04 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_error(void)
{
	perror("malloc");
	exit(1);
}

void	free_all(t_global *gb)
{
	free_packs(gb);
	free_env_list(gb->env);
	free(gb);
	exit(g_exit_status);
}
