/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:17:35 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:20:30 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_join_path(char *path, char *cmd)
{
	char	*aux;
	char	*ret;

	aux = ft_strjoin(path, "/");
	ret = ft_strjoin(aux, cmd);
	free(aux);
	return (ret);
}

void	alloc_command(t_pack *pack)
{
	pack->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pack->cmd)
		malloc_error();
	pack->cmd->cmd = (char **)malloc(sizeof(char *) * \
		(command_size(pack->token) + 1));
	if (!pack->cmd->cmd)
		malloc_error();
}

void	fill_command(t_pack *pack)
{
	int		i;
	t_token	*token;

	i = 0;
	token = pack->token;
	while (token)
	{
		if (token->type == ARG)
			if (!token->prev || token->prev->type == ARG || \
				token->prev->type == LIMITOR)
				pack->cmd->cmd[i++] = token->str;
		token = token->next;
	}
}

void	set_command_case(t_pack *pack, t_global *gb)
{
	if (is_built(pack->cmd->cmd[0]) == 1)
	{
		pack->cmd->is_built = 1;
		pack->cmd->path = NULL;
	}
	else
		pack->cmd->path = check_cmd_path(pack->cmd->cmd[0], \
			get_paths_from_env(gb->env));
}

void	set_command(t_pack *pack, t_global *gb)
{
	int		i;
	t_token	*token;

	i = 0;
	token = pack->token;
	if (check_no_command(pack) == 0)
		return ;
	alloc_command(pack);
	while (token)
	{
		if (token->type == ARG)
			if (!token->prev || token->prev->type == ARG || \
				token->prev->type == LIMITOR)
				pack->cmd->cmd[i++] = token->str;
		token = token->next;
	}
	pack->cmd->is_built = 0;
	set_command_case(pack, gb);
	pack->cmd->cmd[i] = NULL;
}
