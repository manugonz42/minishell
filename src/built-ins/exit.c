/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:34:11 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 13:05:39 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_int_value(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_cmd *cmd, t_global *gb)
{
	int		rt;

	rt = 0;
	if (!cmd->cmd[1])
		rt = 0;
	else if (!is_int_value(cmd->cmd[1]))
		return (print_error("exit", ERR_NUMERIC_ARG, cmd->cmd[1], 0), 2);
	else if (cmd->cmd[2])
	{
		print_error("exit", ERR_TOO_MANY_ARGS, NULL, 0);
		if (g_exit_status == 0)
			g_exit_status = 1;
		rt = g_exit_status;
		return (rt);
	}
	else
	{
		if (cmd->cmd[1])
			rt = ft_atoi(cmd->cmd[1]);
		if (rt < 0 || rt > 256)
			rt = rt % 256;
	}
	g_exit_status = rt;
	free_all(gb);
	return (rt);
}
