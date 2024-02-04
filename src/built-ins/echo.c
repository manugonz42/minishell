/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:57:52 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:02:20 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_nl(char **cmd)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	r = 0;
	while (cmd[i] && ft_strlen(cmd[i]) > 1)
	{
		j = 0;
		if (cmd[i][j] == '-' && cmd[i][1] == 'n')
		{
			j++;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				r++;
			else
				return (r);
		}
		else
			return (r);
		i++;
	}
	return (r);
}

void	print_home_case(char **cmd, int *i, t_global *global)
{
	printf("%s", env_node_searcher("HOME", global->env)->value);
	if (cmd[*i + 1] != NULL)
		printf(" ");
	(*i)++;
}

int	ft_echo(char **cmd, t_global *global)
{
	int		i;
	int		n;

	n = 0;
	cmd++;
	i = verify_nl(cmd);
	if (i > 0)
		n++;
	while (cmd[i] != NULL)
	{
		if (!ft_strncmp(cmd[i], "~\0", 2))
		{
			print_home_case(cmd, &i, global);
			continue ;
		}
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
