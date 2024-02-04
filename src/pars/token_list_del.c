/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:34:52 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/28 12:57:19 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lst_delone_token(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst->next;
	free(lst->str);
	free(lst);
	return (tmp);
}

t_token	*lst_clear_token(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		tmp = lst->next;
		free(lst->str);
		lst->str = NULL;
		free(lst);
		lst = tmp;
	}
	return (NULL);
}
