/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:16 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/31 15:49:43 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dad_process(t_pack *pack)
{
	if (pack->ispipein == 1)
	{
		if (close(pack->pipein[0]) == -1)
			perror("close");
	}
	if (pack->ispipeout == 1)
	{
		if (close(pack->pipeout[1]) == -1)
			perror("close");
	}
	return (0);
}

void	wait_child(int pid)
{
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGINT)
			g_exit_status = 130;
		else if (WTERMSIG(g_exit_status) == SIGQUIT)
			g_exit_status = 131;
	}
	while (waitpid(-1, NULL, WUNTRACED) > 0)
		continue ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	process_pack(t_pack *pack, t_global *gb)
{
	if (pack->ispipeout > 0)
		if (pipe(pack->pipeout) == -1)
			perror_exit("pipe");
	pack->pid = 1;
	if (is_able_2_fork(pack))
		pack->pid = fork();
	else
		is_builtin(pack->cmd, gb);
	if (pack->pid == -1)
		perror_exit("fork");
	else if (pack->pid == 0)
	{
		if (pack->ispipeout && close(pack->pipeout[0]) < 0)
			perror("close");
		exec_cmd(pack, gb);
	}
	else if (pack->pid > 0)
		dad_process(pack);
	signal(SIGINT, signal_handler);
	if (close_files(pack) == -1)
		return (-1);
	return (0);
}

int	process_packs(t_global *gb)
{
	int		i;

	i = 0;
	while (gb->packs[i])
	{
		process_pack(gb->packs[i], gb);
		if (gb->packs[i]->ispipeout == 1 && (gb->packs[i + 1]->here_doc != 1
				|| gb->packs[i + 1]->infile_name))
			create_next_pipe(gb->packs[i], gb->packs[i + 1]);
		i++;
	}
	i = gb->n_of_packs;
	while (i)
	{
		wait_child(gb->packs[i - 1]->pid);
		i--;
	}
	return (0);
}

int	listen(t_global *gb)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		gb->line = readline("Minishell>> ");
		if (gb->line == NULL)
			break ;
		if (!pars(gb))
		{
			free_packs(gb);
			continue ;
		}
		add_history(gb->line);
		signal(SIGINT, SIG_IGN);
		process_packs(gb);
		free_packs(gb);
	}
	free_all(gb);
	return (0);
}
