/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:55 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/30 13:04:40 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*El export recibiria directamente cmd->cmd[1] y dentro de export.c habria
que hacer el parseo de la string para dividir lla variable del valor
*/

int	is_built(char *cmd)
{
	if (ft_strncmp(cmd, "echo\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	return (0);
}

int	is_builtin(t_cmd *cmd, t_global *gb)
{
	int		rt;

	rt = -1;
	if (!cmd || !cmd->cmd)
		return (rt);
	if (ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		rt = ft_echo(cmd->cmd, gb);
	else if (ft_strncmp(cmd->cmd[0], "env\0", 4) == 0)
		rt = print_env_list(gb->env);
	else if (ft_strncmp(cmd->cmd[0], "pwd\0", 4) == 0)
		rt = ft_pwd();
	if (ft_strncmp(cmd->cmd[0], "cd\0", 3) == 0)
		rt = ft_cd(cmd->cmd[1], gb->env);
	else if (ft_strncmp(cmd->cmd[0], "export\0", 6) == 0)
		rt = ft_export(cmd->cmd, &(gb->env));
	else if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		rt = ft_unset(cmd->cmd, &(gb->env));
	else if (ft_strncmp(cmd->cmd[0], "exit\0", 5) == 0)
		rt = exit_builtin(cmd, gb);
	g_exit_status = rt;
	return (rt);
}
