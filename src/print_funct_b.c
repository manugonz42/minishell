/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funct_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:22:13 by manugonz          #+#    #+#             */
/*   Updated: 2024/01/29 12:08:57 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("command:");
	if (!cmd || !cmd->cmd)
	{
		printf("\n");
		return ;
	}
	while (cmd->cmd[i] != NULL)
	{
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

int	print_packs(t_global *gb)
{
	int		i;

	i = 0;
	ft_putstr_fd("printing packs\n", 1);
	while (i < gb->n_of_packs)
	{
		print_pack(gb->packs[i]);
		i++;
	}
	return (0);
}

void	token_type(t_e_token type)
{
	if (type == NON)
		printf("NON");
	else if (type == ARG)
		printf("ARG, ");
	else if (type == IN_REDIR)
		printf("IN_REDIR, ");
	else if (type == OUT_REDIR)
		printf("OUT_REDIR, ");
	else if (type == OUT_APPEND)
		printf("OUT_APPEND, ");
	else if (type == HERE_DOC)
		printf("HERE_DOC, ");
	else if (type == PIPE)
		printf("PIPE, ");
	else if (type == LIMITOR)
		printf("LIMITOR, ");
	else if (type == BUILTIN)
		printf("BUILTIN, ");
}

void	print_tokens(t_token *token)
{
	printf("tokens:");
	while (token)
	{
		printf(" %s:", token->str);
		token_type(token->type);
		token = token->next;
	}
	printf("\n");
}

int	print_pack(t_pack *pack)
{
	puts("----------------	PACK   ----------------\n");
	printf("id :%d\n", pack->id);
	print_command(pack->cmd);
	print_tokens(pack->token);
	printf("path :%s\n", pack->cmd->path);
	printf("infile (%s): %d\n", pack->infile_name, pack->infile);
	printf("outfile (%s): %d\n", pack->outfile_name, pack->outfile);
	printf("ispipein: %d\n", pack->ispipein);
	printf("ispipeout: %d\n", pack->ispipeout);
	printf("Err: %d\n", pack->err);
	puts("--------------------------------------------\n");
	return (0);
}
