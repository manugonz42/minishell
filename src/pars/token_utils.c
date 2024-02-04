/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:09:08 by manugonz          #+#    #+#             */
/*   Updated: 2024/01/29 12:14:35 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *line)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (line[i] && !is_separator(line[i]) && is_valid_var_name_char(line[i]))
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		malloc_error();
	while (j < i)
	{
		key[j] = line[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

void	to_next_token(char *s, int *i)
{
	t_e_quote	quote;

	quote = NO_QUOTE;
	while (s[*i])
	{
		quote_status(s[*i], &quote);
		if (is_separator(s[*i]) && quote == NO_QUOTE)
			break ;
		(*i)++;
	}
}

int	separator_error_case_check(t_pack *pack, int *i)
{
	if (is_redir(pack->raw_str[*i]) && pack->raw_str[*i] \
		== pack->raw_str[*i + 1] && \
	(!pack->raw_str[*i + 2] || !next_token(pack->raw_str, *i + 2)))
		return (2);
	if (!next_token(pack->raw_str, *i + 1) || \
		next_token(pack->raw_str, *i) == '\n')
		return (2);
	return (0);
}
