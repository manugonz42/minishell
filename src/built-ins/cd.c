/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:36:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:11:31 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_pars(char **dir, t_env *env)
{
	t_env	*node;

	if (!*dir || ft_strncmp(*dir, "~\0", 2) == 0
		|| ft_strncmp(*dir, "--\0", 3) == 0)
	{
		node = env_node_searcher("HOME", env);
		*dir = NULL;
		if (node)
			*dir = node->value;
		if (!*dir)
			return (print_error("cd", ERR_HOME_NOT_SET, NULL, 0), -1);
	}
	else if (ft_strncmp(*dir, "-\0", 2) == 0)
	{
		node = env_node_searcher("OLDPWD", env);
		*dir = NULL;
		if (node)
			*dir = node->value;
		if (!*dir)
			return (print_error("cd", ERR_OLDPWD_NOT_SET, NULL, 0), -1);
		else
			printf("%s\n", *dir);
	}
	return (0);
}

int	ft_cd(char *dir, t_env *env)
{
	char	current_dir[1024];
	char	*oldpwd;

	if (cd_pars(&dir, env) == -1)
		return (1);
	getcwd(current_dir, sizeof(current_dir));
	if (chdir(dir) == -1)
		return (print_error("cd", strerror(errno), dir, 0), 1);
	oldpwd = ft_strdup(current_dir);
	if (!oldpwd)
		malloc_error();
	if (oldpwd)
		export_var(ft_strdup("OLDPWD"), oldpwd, &env);
	return (0);
}

int	ft_pwd(void)
{
	char	current_dir[1024];

	getcwd(current_dir, sizeof(current_dir));
	printf("%s\n", current_dir);
	return (0);
}
