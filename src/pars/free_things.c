/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:34:49 by manugonz          #+#    #+#             */
/*   Updated: 2024/01/28 14:17:41 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_global *gb, int i)
{
	if (gb->packs[i]->infile > 0)
	{
		if (close(gb->packs[i]->infile) == -1)
			perror("close");
		gb->packs[i]->infile = 0;
	}
	if (gb->packs[i]->outfile > 0)
	{
		if (close(gb->packs[i]->outfile) == -1)
			perror("close");
		gb->packs[i]->outfile = 0;
	}
}

void	free_packs(t_global *gb)
{
	int	i;

	i = 0;
	if (gb->line)
	{
		free (gb->line);
		gb->line = NULL;
	}
	if (!gb->packs)
		return ;
	while (gb->packs[i])
	{
		if (gb->packs[i]->raw_str)
			free(gb->packs[i]->raw_str);
		if (gb->packs[i]->token)
			lst_clear_token(gb->packs[i]->token);
		if (gb->packs[i]->cmd)
			free_command(gb->packs[i]->cmd);
		close_fds(gb, i);
		free(gb->packs[i]);
		i++;
	}
	free(gb->packs);
	gb->packs = NULL;
}

void	free_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->cmd)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;
	if (!env)
		return ;
	env = env_head(env);
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
