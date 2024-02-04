/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:17:21 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:19:52 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_token(t_pack *pack, t_token *token, t_global *gb)
{
	t_e_token	type;
	int			r;

	r = 1;
	type = token->type;
	if (type == OUT_REDIR)
		r = set_out_redir(pack, token->next, gb);
	if (type == OUT_APPEND)
		r = set_out_append(pack, token->next, gb);
	if (type == HERE_DOC)
		r = set_here_doc(pack, token->next, gb);
	if (type == IN_REDIR)
		r = set_in_redir(pack, token->next, gb);
	return (r);
}

int	init_tokens(t_global *gb)
{
	int			i;
	int			r;
	t_token		*token;

	i = 0;
	while (i < gb->n_of_packs)
	{
		token = gb->packs[i]->token;
		while (token)
		{
			r = init_token(gb->packs[i], token, gb);
			if (r == 3)
				break ;
			else if (r != 1)
				return (1);
			token = token->next;
		}
		set_command(gb->packs[i], gb);
		i++;
	}
	return (0);
}
