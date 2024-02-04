/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:47:07 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/31 15:44:47 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_able_2_fork(t_pack *pack)
{
	t_cmd	*cmd;

	cmd = pack->cmd;
	if (!cmd)
		return (0);
	if (!is_built(cmd->cmd[0]))
		return (1);
	if (is_built(pack->cmd->cmd[0]))
	{
		if (pack->ispipein || pack->ispipeout)
			return (1);
		if (pack->infile_name || pack->outfile_name)
			return (1);
	}
	return (0);
}

void	check_exec_errs(t_pack *pack)
{
	if (access(pack->cmd->cmd[0], X_OK) == -1 \
			&& !access(pack->cmd->cmd[0], F_OK))
	{
		print_error(pack->cmd->cmd[0], ERR_PERM_DENIED, NULL, 0);
		exit (126);
	}
	else if (ft_is_in_str(pack->cmd->cmd[0], '/') != -1 && \
		access(pack->cmd->cmd[0], F_OK) == -1)
		print_error(pack->cmd->cmd[0], ERR_NO_FILE_DIR, NULL, 0);
	else
		print_error(pack->cmd->cmd[0], ERR_CMD_NOT_FOUND, NULL, 0);
	exit(127);
}

void	exec_cmd(t_pack *pack, t_global *gb)
{
	char	**environ;

	if (pack->infile == -1 || pack->outfile == -1)
		exit (EXIT_FAILURE);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pack->cmd->path == NULL && !is_built(pack->cmd->cmd[0]))
		check_exec_errs(pack);
	if (chdir(pack->cmd->path) > -1)
	{
		printf("entra aqui \n");
		print_error(pack->cmd->cmd[0], ERR_IS_DIR, NULL, 0);
		exit(126);
	}
	redir_out(pack);
	redir_in(pack);
	if (is_builtin(pack->cmd, gb) != -1)
		exit(g_exit_status);
	environ = env_to_array(gb->env);
	execve(pack->cmd->path, pack->cmd->cmd, environ);
	printf("minishell: %s: %s\n", pack->cmd->cmd[0], strerror(errno));
	exit (126);
}
