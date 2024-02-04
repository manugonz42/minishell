/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:39:03 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/31 15:49:49 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n>>", STDOUT_FILENO);
	}
}

void	signal_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	child_sig(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
