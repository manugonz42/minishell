/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:55 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:10:02 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_unclosed_quote(char *s)
{
	int			i;
	t_e_quote	quote;

	i = 0;
	quote = NO_QUOTE;
	while (s[i])
	{
		if (s[i] == '\'' && quote == NO_QUOTE)
			quote = SINGLE_QUOTE;
		else if (s[i] == '\'' && quote == SINGLE_QUOTE)
			quote = NO_QUOTE;
		else if (s[i] == '"' && quote == NO_QUOTE)
			quote = DOUBLE_QUOTE;
		else if (s[i] == '"' && quote == DOUBLE_QUOTE)
			quote = NO_QUOTE;
		i++;
	}
	if (quote != NO_QUOTE)
		return (1);
	return (0);
}

void	set_pipe_case(t_global *gb)
{
	int	i;
	int	size;

	i = 0;
	size = count_packs(gb);
	while (i < size)
	{
		if (i == 0)
			gb->packs[i]->ispipein = 0;
		else
			gb->packs[i]->ispipein = 1;
		if (i == size - 1)
			gb->packs[i]->ispipeout = 0;
		else
			gb->packs[i]->ispipeout = 1;
		i++;
	}
}

int	check_empty_pack(t_global *gb)
{
	int	i;

	i = 0;
	while (i < gb->n_of_packs)
	{
		if (is_empty_line(gb->packs[i]->raw_str))
			return (newline_error(gb));
		i++;
	}
	return (0);
}

int	pars(t_global *gb)
{
	if (check_unclosed_quote(gb->line))
		return (unclosed_quote_error());
	gb->n_of_packs = count_packs(gb);
	if (gb->n_of_packs == 0)
		return (0);
	if (divide_in_packs(gb))
		return (unexpected_token_error("|", gb));
	if (check_empty_pack(gb))
		return (0);
	set_pipe_case(gb);
	if (set_tokens(gb))
		return (0);
	if (gb->packs[0] == NULL)
		return (0);
	if (init_tokens(gb))
		return (0);
	return (1);
}
