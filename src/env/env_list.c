/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:34:48 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/27 12:53:32 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_node(char *key, char *value, t_env **prev)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		exit (1);
	}
	node->previous = *prev;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*lst_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	node_add_back(t_env **list, t_env *node)
{
	t_env	*aux;

	if (!node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	aux = lst_last(*list);
	aux->next = node;
	node->previous = aux;
}

t_env	*create_env_list(char **env)
{
	int		i;
	t_env	*node;
	t_env	*prev;
	t_env	*list;
	char	**split_result;

	i = 0;
	prev = NULL;
	list = NULL;
	while (env && env[i])
	{
		split_result = ft_split(env[i], '=');
		node = create_node(ft_strdup(split_result[0]), \
			ft_strdup(split_result[1]), &prev);
		prev = node;
		node_add_back(&list, node);
		if (env[i + 1] && i > 0)
			list = list->next;
		ft_free_matrix(split_result);
		i++;
	}
	while (list && list->previous)
		list = list->previous;
	return (list);
}

int	print_env_list(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (0);
}
