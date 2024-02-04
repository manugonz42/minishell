/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:45:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 13:37:17 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_minichell(void)
{
	ft_putchar_fd('\n', 1);
	print_color("    _   .-')                 .-') _                 \
	('-. .-.   ('-.                      \n", YELLOW);
	print_color("   ( '.( OO )_              ( OO ) )                \
	( OO )  / _(  OO)                     \n", YELLOW);
	print_color("   ,--.   ,--.) ,-.-') ,--./ ,--,' ,-.-') \
  .-----. ,--. ,--.(,------.,--.      ,--.       \n", YELLOW);
	print_color("   |   `.'   |  |  |OO)|   \\ |  |\\ |  |OO) '  .--./\
 |  | |  | |  .---'|  |.-')  |  |.-')   \n", YELLOW);
	print_color("   |         |  |  |  \\|    \\|  | )|  |  \\ |  |('-.\
 |   .|  | |  |    |  | OO ) |  | OO )  \n", YELLOW);
	print_color("   |  |'.'|  |  |  |(_/|  .     |/ |  |(_//_) |OO  )| \
 	    |(|  '--. |  |`-' | |  |`-' |  \n", YELLOW);
	print_color("   |  |   |  | ,|  |_.'|  |\\    | ,|  |_.'||  |`-'| |\
  .-.  | |  .--'(|  '---.'(|  '---.'  \n", YELLOW);
	print_color("   |  |   |  |(_|  |   |  | \\   |(_|  |  (_'  '--'\\ |\
  | |  | |  `---.|      |  |      |   \n", YELLOW);
	print_color("   `--'   `--'  `--'   `--'  `--'  `--'     `-----' `--'\
 `--' `------'`------'  `------'   \n", YELLOW);
	return (0);
}

int	print_color(char *msg, char *color)
{
	char	*str;

	str = ft_strjoin(color, msg);
	msg = ft_strjoin(str, NC);
	ft_putstr_fd(msg, 0);
	free(str);
	free(msg);
	return (0);
}

int	print_err_msg(char *msg, char *cmd)
{
	ft_putstr_fd(cmd, 0);
	ft_putstr_fd(":", 0);
	ft_putstr_fd(msg, 0);
	ft_putchar_fd('\n', 0);
	return (0);
}

void	print_token_type(t_token *token)
{
	if (token->type == PIPE)
		printf(NC"PIPE\n");
	else if (token->type == IN_REDIR)
		printf("IN_REDIR\n");
	else if (token->type == OUT_REDIR)
		printf("OUT_REDIR\n");
	else if (token->type == OUT_APPEND)
		printf("OUT_APPEND\n");
	else if (token->type == HERE_DOC)
		printf("HERE_DOC\n");
	else if (token->type == ARG)
		printf("ARG\n");
	else
		printf("NON\n");
}
