/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:48 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:11:04 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_pack(t_pack **pack, t_global *gb, int start, int end)
{
	*pack = (t_pack *)malloc(sizeof(t_pack));
	if (!(*pack))
		malloc_error();
	(*pack)->raw_str = ft_substr(gb->line, start, end - start);
	if (!(*pack)->raw_str)
		malloc_error();
	(*pack)->token = NULL;
	(*pack)->cmd = NULL;
	(*pack)->infile = 0;
	(*pack)->infile_name = NULL;
	(*pack)->outfile = 0;
	(*pack)->outfile_name = NULL;
	(*pack)->ispipein = 0;
	(*pack)->ispipeout = 0;
	(*pack)->here_doc = 0;
	return (0);
}

void	handle_pipe_case(t_global *gb, int *k, int *n, int i)
{
	initialize_pack(&gb->packs[*k], gb, *n, i);
	*n = i + 1;
	(*k)++;
}

int	divide_in_packs(t_global *gb)
{
	int			i;
	int			n;
	int			k;
	t_e_quote	quote;

	k = 0;
	i = -1;
	n = 0;
	quote = NO_QUOTE;
	gb->packs = (t_pack **)malloc(sizeof(t_pack *) * (gb->n_of_packs + 1));
	if (!gb->packs)
		malloc_error();
	gb->packs[0] = NULL;
	while (gb->line[++i])
	{
		quote_status(gb->line[i], &quote);
		if (gb->line[i] == '|' && quote == NO_QUOTE)
		{
			if (next_token(gb->line, i + 1) == '|')
				return (2);
			handle_pipe_case(gb, &k, &n, i);
		}
	}
	gb->packs[k + 1] = NULL;
	return (initialize_pack(&gb->packs[k], gb, n, i));
}
