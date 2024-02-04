/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:35:55 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/27 12:59:00 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_head(t_env *env)
{
	while (env->previous)
		env = env->previous;
	return (env);
}

int	env_lst_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*aux;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (env_lst_size(env) + 1));
	if (!arr)
	{
		perror("malloc");
		exit(1);
	}
	while (env)
	{
		arr[i] = ft_strdup(env->key);
		aux = ft_strjoin("=", env->value);
		arr[i] = ft_strjoin(arr[i], aux);
		free(aux);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**get_paths_from_env(t_env *env)
{
	char	**paths;
	t_env	*node;

	node = env_node_searcher("PATH", env);
	if (!node)
		return (NULL);
	paths = ft_split(node->value, ':');
	return (paths);
}

t_env	*env_node_searcher(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
