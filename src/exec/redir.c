/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:03:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/28 12:32:47 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_in(t_pack *pack)
{
	if (pack->infile > 0)
	{
		if (dup2(pack->infile, STDIN_FILENO) < 0)
			perror("dup2");
		if (close(pack->infile) < 0)
			perror("close");
		return (0);
	}
	else if (pack->ispipein == 1)
	{
		if (dup2(pack->pipein[0], STDIN_FILENO) < 0)
			perror("dup2");
		if (close(pack->pipein[0]) < 0)
			perror("close");
		return (0);
	}
	return (-1);
}

int	redir_out(t_pack *pack)
{
	if (pack->outfile > 0)
	{
		if (pack->outfile_name == NULL)
			return (-1);
		if (dup2(pack->outfile, STDOUT_FILENO) < 0)
			perror("dup2");
		if (close(pack->outfile) < 0)
			perror("close");
		return (0);
	}
	else if (pack->ispipeout == 1)
	{
		if (dup2(pack->pipeout[1], STDOUT_FILENO) < 0)
			perror("dup2");
		if (close(pack->pipeout[1]) < 0)
			perror("close");
		return (0);
	}
	return (-1);
}

int	create_next_pipe(t_pack *current_pack, t_pack *next_pack)
{
	if (next_pack->ispipein == 1)
	{
		if (pipe(next_pack->pipein) == -1)
			perror("pipe");
		if (current_pack->ispipeout)
			if (dup2(current_pack->pipeout[0], next_pack->pipein[0]) == -1)
				perror("dup2");
		if (close(next_pack->pipein[1]) == -1)
			perror("close");
		if (current_pack->ispipeout)
			if (close(current_pack->pipeout[0]) == -1)
				perror("close");
	}
	return (0);
}
