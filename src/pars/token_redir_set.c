/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:08:54 by manugonz          #+#    #+#             */
/*   Updated: 2024/01/28 13:32:05 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_out_redir(t_pack *pack, t_token *token, t_global *gb)
{
	if (token && token->type != ARG)
		return (unexpected_token_error(token->str, gb));
	pack->outfile_name = token->str;
	if (pack->outfile)
		if (close(pack->outfile) == -1)
			perror("close");
	pack->outfile = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pack->outfile < 0)
	{
		printf("minishell: %s: %s\n", token->str, strerror(errno));
		g_exit_status = 1;
		return (3);
	}
	return (1);
}

int	set_out_append(t_pack *pack, t_token *token, t_global *gb)
{
	if (token && token->type != ARG)
		return (unexpected_token_error(token->str, gb));
	pack->outfile_name = token->str;
	if (pack->outfile)
		if (close(pack->outfile) == -1)
			perror("close");
	pack->outfile = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pack->outfile < 0)
	{
		printf("minishell: %s: %s\n", token->str, strerror(errno));
		g_exit_status = 1;
		return (3);
	}
	return (1);
}

int	set_here_doc(t_pack *pack, t_token *token, t_global *gb)
{
	if (token == NULL)
		return (newline_error(gb));
	if (token->type != ARG)
		return (unexpected_token_error(token->str, gb));
	token->type = LIMITOR;
	pack->ispipein = 1;
	pack->here_doc = 1;
	if (pack->infile > 0)
	{
		if (close(pack->infile) == -1)
			perror("close");
		pack->infile = 0;
		pack->infile_name = NULL;
	}
	here_doc(pack, token->str, gb);
	return (1);
}

int	set_in_redir(t_pack *pack, t_token *token, t_global *gb)
{
	if (token->type != ARG)
		return (unexpected_token_error(token->str, gb));
	pack->infile_name = token->str;
	if (pack->infile > 0)
		if (close(pack->infile) == -1)
			perror("close");
	pack->infile = open(token->str, O_RDONLY);
	if (pack->infile < 0)
	{
		printf("minishell: %s: %s\n", token->str, strerror(errno));
		g_exit_status = 1;
		return (3);
	}
	return (1);
}
