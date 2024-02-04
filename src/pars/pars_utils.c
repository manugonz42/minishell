/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:25 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:10:22 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

char	next_token(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
			return (line[i]);
	}
	return (0);
}

int	token_size_without_quotes(char *s, int i, t_global *gb)
{
	int			r;	
	t_e_quote	quote;

	r = 0;
	quote = NO_QUOTE;
	while (s[i])
	{
		if (s[i] == '$' && quote != SINGLE_QUOTE && s[i + 1])
			process_val_pack(s, i, &r, gb);
		else if (is_single_char(s, i, quote))
			r++;
		else if (quote == NO_QUOTE && is_separator(s[i]))
			break ;
		quote_status(s[i], &quote);
		i++;
	}
	return (r);
}

void	quote_status(char c, t_e_quote *quote)
{
	if (c == '\'' && *quote == NO_QUOTE)
		*quote = SINGLE_QUOTE;
	else if (c == '\'' && *quote == SINGLE_QUOTE)
		*quote = NO_QUOTE;
	else if (c == '"' && *quote == NO_QUOTE)
		*quote = DOUBLE_QUOTE;
	else if (c == '"' && *quote == DOUBLE_QUOTE)
		*quote = NO_QUOTE;
}

int	count_packs(t_global *gb)
{
	int			i;
	int			r;
	t_e_quote	quote;

	quote = NO_QUOTE;
	i = 0;
	r = 0;
	if (gb->line && gb->line[0])
	{
		while (gb->line[i])
		{
			quote_status(gb->line[i], &quote);
			if (gb->line[i] == '|' && quote == NO_QUOTE)
				r++;
			i++;
		}
		if (r == 0 && is_empty_line(gb->line))
			return (0);
		return (r + 1);
	}
	return (0);
}
