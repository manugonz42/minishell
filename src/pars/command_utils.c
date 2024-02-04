/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:08:15 by manugonz          #+#    #+#             */
/*   Updated: 2024/01/29 12:37:08 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_size(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->type == ARG)
			if (!token->prev || token->prev->type == ARG || \
				token->prev->type == LIMITOR)
				i++;
		token = token->next;
	}
	return (i);
}

int	is_valid_path(char *str)
{
	static int	i = 0;

	if ((ft_strncmp(str, ".\0", 2) == 0 || \
		ft_strncmp(str, "..\0", 3) == 0))
	{
		g_exit_status = 126;
		i = 1;
		return (0);
	}
	if (i == 0 && ft_strlen(str) == 0)
	{
		g_exit_status = 127;
		return (0);
	}
	if (i == 1)
		i = 0;
	return (1);
}

int	cmd_path_checks(char *cmd, char **paths)
{
	int	i;

	i = 1;
	if (!paths || !cmd || !is_valid_path(cmd))
	{
		if (paths)
			ft_free_matrix(paths);
		return (0);
	}
	return (i);
}

char	*check_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		i;

	i = -1;
	if (is_valid_path(cmd) && access(cmd, X_OK) == 0)
	{
		if (paths)
			ft_free_matrix(paths);
		return (ft_strdup(cmd));
	}
	if (!cmd_path_checks(cmd, paths))
		return (NULL);
	while (paths[++i] != NULL)
	{
		path = ft_join_path(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (path);
		}
		free(path);
	}
	ft_free_matrix(paths);
	return (NULL);
}

int	check_no_command(t_pack *pack)
{
	t_token	*token;

	token = pack->token;
	while (token)
	{
		if (token->type == ARG && (!token->prev || token->prev->type == ARG || \
				token->prev->type == LIMITOR))
			return (1);
		token = token->next;
	}
	pack->cmd = NULL;
	return (0);
}
