/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:45:11 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:14:09 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_val_here(char *s, int i, int *r, t_global *gb)
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

int	here_size(char *s, int i, t_global *gb)
{
	int			r;	

	r = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
			process_val_pack(s, i, &r, gb);
		else
			r++;
		i++;
	}
	return (r);
}
