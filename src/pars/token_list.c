/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:55 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:15:42 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_e_token	set_token_type(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (OUT_APPEND);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (IN_REDIR);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (OUT_REDIR);
	else
		return (ARG);
}

t_token	*lst_new_token(char *str, t_e_token type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		malloc_error();
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*lst_last_token(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

t_token	*lst_add_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return (NULL);
	if (!(*lst))
	{
		*lst = new;
		(*lst)->prev = NULL;
		return (*lst);
	}
	last = lst_last_token(*lst);
	last->next = new;
	last->next->prev = last;
	return (*lst);
}

t_token	*lst_add_front_token(t_token **lst, t_token *new)
{
	if (!new)
		return (NULL);
	new->next = *lst;
	*lst = new;
	return (*lst);
}
