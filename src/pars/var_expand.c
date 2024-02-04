/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:08 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 17:18:13 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_val_pack(char *s, int i, int *r, t_global *gb)
{
	char	*key;

	if (!is_valid_var_name_char(s[i + 1]))
		(*r)++;
	else if (s[i + 1] == '?')
	{
		key = ft_itoa(g_exit_status);
		if (!key)
			malloc_error();
		(*r) += ft_strlen(key);
		free(key);
	}
	else
	{
		key = get_key(s + i + 1);
		if (env_node_searcher(key, gb->env))
			(*r) += ft_strlen(env_node_searcher(key, gb->env)->value);
		free(key);
	}
}

void	expand_exit_status(t_token_builder *tb)
{
	char	*key;
	int		j;

	j = 0;
	key = ft_itoa(g_exit_status);
	if (!key)
		malloc_error();
	while (key[j])
	{
		tb->token[tb->t_pos] = key[j];
		tb->t_pos++;
		j++;
	}
	tb->r_pos += 1;
	free(key);
}

void	save_without_spc(t_token_builder *tb, char *var_value)
{
	int	i;

	i = 0;
	while (var_value[i])
	{
		skip_spaces(var_value, &i);
		if (!var_value[i])
			return ;
		tb->token[tb->t_pos] = var_value[i];
		i++;
		tb->t_pos++;
		if ((var_value[i] == ' ' || var_value[i] == '\t') && \
		next_token(var_value, i))
		{
			tb->token[tb->t_pos] = ' ';
			tb->t_pos++;
		}
	}
}

void	save_with_spaces(t_token_builder *tb, char *var_value)
{
	int	j;

	j = 0;
	while (var_value[j])
	{
		tb->token[tb->t_pos] = var_value[j];
		tb->t_pos++;
		j++;
	}
}

void	expand_global_var(t_token_builder *tb, t_pack *pack, t_global *gb)
{
	char	*var_name;
	char	*var_value;

	if (tb->raw[tb->r_pos + 1] == '?')
		return (expand_exit_status(tb));
	var_name = get_key(tb->raw + tb->r_pos + 1);
	if (env_node_searcher(var_name, gb->env))
		var_value = env_node_searcher(var_name, gb->env)->value;
	else
		var_value = "";
	if (pack->token && pack->token->str && tb->quote == NO_QUOTE && \
		!ft_strncmp(pack->token->str, "echo\0", 5))
		save_without_spc(tb, var_value);
	else
		save_with_spaces(tb, var_value);
	tb->r_pos += ft_strlen(var_name);
	free(var_name);
}
