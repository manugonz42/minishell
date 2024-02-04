/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:36:11 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:12:50 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_export(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (0);
}

int	export_var(char *key, char *value, t_env **env)
{
	t_env	*node;

	if (key && !value)
	{
		free(key);
		free(value);
		return (0);
	}
	node = env_node_searcher(key, *env);
	if (!node)
	{
		node = create_node(key, value, env);
		node_add_back(env, node);
	}
	else
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	return (0);
}

int	is_valid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-')
		return (print_error("export", ERR_INVALID_OPTION, NULL, cmd[1]), 0);
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (print_error("export", ERR_NOT_VALID_IDENT, cmd, 0), 0);
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (print_error("export", ERR_NOT_VALID_IDENT, cmd, 0), 0);
		i++;
	}
	if (cmd[i] != '=')
		return (0);
	return (1);
}

char	**ft_export_split(char *cmd)
{
	char	**data;
	int		i;

	data = malloc(sizeof(char *) * 3);
	if (!data)
		malloc_error();
	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	data[0] = ft_substr(cmd, 0, i);
	if (!data[0])
		malloc_error();
	i++;
	data[1] = ft_substr(cmd, i, ft_strlen(cmd) - i);
	if (!data[1])
		malloc_error();
	data[2] = NULL;
	return (data);
}

int	ft_export(char **cmd, t_env **env)
{
	int		i;
	char	**data;
	int		rt;

	rt = 0;
	i = 1;
	if (!cmd[i])
		return (print_export(*env), 0);
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
			rt = 1;
		else
		{
			data = ft_export_split(cmd[i]);
			export_var(data[0], data[1], env);
			free(data);
		}
		i++;
	}
	return (rt);
}
