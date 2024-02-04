/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:49:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/27 13:04:19 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_files(t_pack *pack)
{
	if (pack->infile > 0)
	{
		if (close(pack->infile) == -1)
			return (perror("close"), -1);
		else
			pack->infile = 0;
	}
	if (pack->outfile > 0)
	{
		if (close(pack->outfile) == -1)
			return (perror("close"), -1);
		else
			pack->outfile = 0;
	}
	return (0);
}
