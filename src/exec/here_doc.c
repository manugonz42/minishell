/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:40:43 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:15:59 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_here_var_builder(t_token_builder *tb, char *s, t_global *gb)
{
	tb->t_pos = 0;
	tb->r_pos = 0;
	tb->raw = s;
	tb->token = (char *)malloc(sizeof(char) * (here_size(s, 0, gb) + 1));
	if (tb->token == NULL)
		malloc_error();
}

void	expand_here_var(t_token_builder *tb, t_global *gb)
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
	save_with_spaces(tb, var_value);
	tb->r_pos += ft_strlen(var_name);
	free(var_name);
}

char	*parse_here(char *rt, t_global *gb)
{
	t_token_builder	*tb;
	char			*ret;

	tb = malloc(sizeof(t_token_builder));
	if (!tb)
		malloc_error();
	init_here_var_builder(tb, rt, gb);
	while (tb->raw[tb->r_pos])
	{
		if (rt[tb->r_pos] == '$' && rt[tb->r_pos + 1] && \
			(is_valid_var_name_char(rt[tb->r_pos + 1]) \
			|| rt[tb->r_pos + 1] == '?'))
			expand_here_var(tb, gb);
		else
			tb->token[tb->t_pos++] = rt[tb->r_pos];
		tb->r_pos++;
	}
	tb->token[tb->t_pos] = '\0';
	ret = tb->token;
	free(tb);
	return (ret);
}

void	write_pipe(int fd, char *parsed)
{
	if (write(fd, parsed, ft_strlen(parsed)) == -1)
		perror("write");
	if (write(fd, "\n", 1) == -1)
		perror("write");
	free(parsed);
}

int	here_doc(t_pack *pack, char *limiter, t_global *gb)
{
	char	*rt;
	char	*parsed;

	signal(SIGINT, signal_handler);
	if (pipe(pack->pipein) < 0)
		perror_exit("pipe");
	while (1)
	{
		rt = readline("here doc >>");
		if (!rt || g_exit_status == 130 || \
			(ft_strncmp(rt, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(rt) == ft_strlen(limiter)))
		{
			if (close(pack->pipein[1]) < 0)
				perror("close");
			break ;
		}
		parsed = parse_here(rt, gb);
		write_pipe(pack->pipein[1], parsed);
		free (rt);
	}
	free(rt);
	signal(SIGINT, SIG_IGN);
	return (0);
}
