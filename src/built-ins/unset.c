/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:16:57 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:02:49 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

int	no_prev_node_case(t_env *node)
{
	t_env	*next;

	if (node->next == NULL)
		return (free_node(node), 0);
	next = node->next;
	next->previous = NULL;
	free_node(node);
	return (0);
}

int	is_valid_unset_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (print_error("unset", ERR_NOT_VALID_IDENT, cmd, 0), 0);
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (print_error("unset", ERR_NOT_VALID_IDENT, cmd, 0), 0);
		i++;
	}
	return (1);
}

void	unset_var(char *key, t_env **env)
{
	t_env	*node;

	node = env_node_searcher(key, *env);
	if (!node)
		return ;
	if (node->previous)
		node->previous->next = node->next;
	else
		*env = node->next;
	if (node->next)
		node->next->previous = node->previous;
	free_node(node);
}

int	ft_unset(char **cmd, t_env **env)
{
	int		i;
	int		rt;

	rt = 0;
	i = 1;
	if (!cmd || !cmd[i] || !env)
		return (0);
	if (cmd[1][0] == '-' && cmd[1][1])
	{
		print_error(cmd[0], ERR_INVALID_OPTION, NULL, cmd[1][1]);
		i++;
	}
	while (cmd[i])
	{
		if (!is_valid_unset_identifier(cmd[i]))
			rt = 1;
		else
			unset_var(cmd[i], env);
		i++;
	}
	return (rt);
}
