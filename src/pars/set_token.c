/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:43 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:18:18 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_t_token_builder(t_token_builder *tb, char *s, t_global *gb)
{
	tb->t_pos = 0;
	tb->r_pos = 0;
	tb->quote = NO_QUOTE;
	tb->raw = s;
	tb->token = (char *)malloc(sizeof(char) * \
		(token_size_without_quotes(s, 0, gb) + 1));
	if (tb->token == NULL)
		malloc_error();
}

char	*clean_token(char *s, t_pack *pack, t_global *gb)
{
	t_token_builder	*tb;
	char			*ret;

	tb = malloc(sizeof(t_token_builder));
	if (!tb)
		malloc_error();
	init_t_token_builder(tb, s, gb);
	while (tb->raw[tb->r_pos])
	{
		if (s[tb->r_pos] == '$' && tb->quote != SINGLE_QUOTE && \
			s[tb->r_pos + 1] && (is_valid_var_name_char(s[tb->r_pos + 1]) \
			|| s[tb->r_pos + 1] == '?'))
			expand_global_var(tb, pack, gb);
		else if (is_single_char(s, tb->r_pos, tb->quote))
			tb->token[tb->t_pos++] = s[tb->r_pos];
		if (tb->quote == NO_QUOTE && is_separator(s[tb->r_pos]))
			break ;
		quote_status(s[tb->r_pos], &tb->quote);
		tb->r_pos++;
	}
	tb->token[tb->t_pos] = '\0';
	ret = tb->token;
	free(tb);
	return (ret);
}

int	save_separator(t_pack *pack, int *i, t_global *gb)
{
	if (separator_error_case_check(pack, i) == 2)
		return (newline_error(gb));
	if (pack->raw_str[*i] == '<')
	{
		if (pack->raw_str[(*i) + 1] && pack->raw_str[(*i) + 1] == '<')
		{
			lst_add_back_token(&pack->token, lst_new_token("<<", HERE_DOC));
			(*i)++;
		}
		else
			lst_add_back_token(&pack->token, lst_new_token("<", IN_REDIR));
	}
	if (pack->raw_str[*i] == '>')
	{
		if (pack->raw_str[(*i) + 1] && pack->raw_str[(*i) + 1] == '>')
		{
			lst_add_back_token(&pack->token, \
				lst_new_token(">>", OUT_APPEND));
			(*i)++;
		}
		else
			lst_add_back_token(&pack->token, lst_new_token(">", OUT_REDIR));
	}
	(*i)++;
	return (-1);
}

int	cross_str(t_pack *pack, int *i, t_global *gb)
{
	char	*tmp;

	skip_spaces(pack->raw_str, i);
	if (!pack->raw_str[*i])
		return (2);
	if (is_redir(pack->raw_str[*i]))
	{
		if (save_separator(pack, i, gb) == 2)
			return (0);
		return (1);
	}
	if (token_size_without_quotes(pack->raw_str, *i, gb) != 0)
	{
		tmp = clean_token(pack->raw_str + *i, pack, gb);
		lst_add_back_token(&pack->token, lst_new_token(tmp, ARG));
		free(tmp);
	}
	else
		lst_add_back_token(&pack->token, lst_new_token("\0", ARG));
	to_next_token(pack->raw_str, i);
	return (1);
}

int	set_tokens(t_global *gb)
{
	int			i;
	int			j;

	j = 0;
	while (j < gb->n_of_packs)
	{
		i = 0;
		while (i < (int)ft_strlen(gb->packs[j]->raw_str))
		{
			if (!cross_str(gb->packs[j], &i, gb))
				return (1);
		}
		j++;
	}
	return (0);
}
