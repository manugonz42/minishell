/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:32:02 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/31 15:51:08 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(char *cmd, char *err, char *option, char flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (option)
	{
		ft_putstr_fd(option, 2);
		ft_putstr_fd(": ", 2);
	}
	if (flag)
	{
		ft_putchar_fd(flag, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	perror_exit(char *function)
{
	perror(function);
	exit(1);
}

int	unclosed_quote_error(void)
{
	ft_putstr_fd("minishell: sintax: unclosed quote\n", 2);
	g_exit_status = 1;
	return (0);
}

int	newline_error(t_global *gb)
{
	ft_putstr_fd("minishell: syntax error near" \
		"unexpected token `newline'\n", 2);
	free_packs(gb);
	g_exit_status = 2;
	return (2);
}

int	unexpected_token_error(char *token, t_global *gb)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	free_packs(gb);
	g_exit_status = 2;
	return (0);
}
