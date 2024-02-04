/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils_is.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:31 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/11 15:34:32 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_valid_var_name_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	is_single_char(char *s, int i, t_e_quote quote)
{
	int	r;

	r = 0;
	if (s[i] == '\'' || s[i] == '"')
	{
		if ((quote == DOUBLE_QUOTE && s[i] == '\'') || \
			(quote == SINGLE_QUOTE && s[i] == '"'))
			r++;
	}
	else if (is_separator(s[i]) && quote != NO_QUOTE)
		r++;
	else if (!is_separator(s[i]))
		r++;
	return (r);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] > 8 && line[i] < 14) || line[i] == ' '))
	{
		if ((line[i] <= 8 || line[i] >= 14) && line[i] != ' ')
			break ;
		i++;
	}
	return (line[i] == '\0');
}
