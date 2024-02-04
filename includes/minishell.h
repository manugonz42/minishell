/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:15:37 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 17:04:01 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NC			"\033[0m"
# define LRED		"\033[0;31m"
# define LREDB		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define LGREEN		"\033[1;92m"
# define PINK		"\033[1;95m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define LBLUE		"\033[1;36m"

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line_bonus.h"
# include "pars.h"
# include "error.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <unistd.h>

extern int	g_exit_status;

/*BUILTINS*/
// cd
int			cd_pars(char **dir, t_env *env);
int			ft_cd(char *dir, t_env *env);
int			ft_pwd(void);

// echo
int			verify_nl(char **cmd);
void		print_home_case(char **cmd, int *i, t_global *global);
int			ft_echo(char **cmd, t_global *global);

// exit
int			is_int_value(char *value);
int			exit_builtin(t_cmd *cmd, t_global *gb);

// export
int			print_export(t_env *env);
int			export_var(char *key, char *value, t_env **env);
int			is_valid_identifier(char *cmd);
char		**ft_export_split(char *cmd);
int			ft_export(char **cmd, t_env **env);

// switch
int			is_built(char *cmd);
int			is_builtin(t_cmd *cmd, t_global *gb);

// unset
void		free_node(t_env *node);
int			no_prev_node_case(t_env *node);
int			is_valid_unset_identifier(char *cmd);
void		unset_var(char *key, t_env **env);
int			ft_unset(char **cmd, t_env **env);

/*ENV*/

// env_functions
t_env		*env_head(t_env *env);
int			env_lst_size(t_env *env);
char		**env_to_array(t_env *env);
char		**get_paths_from_env(t_env *env);
t_env		*env_node_searcher(char *key, t_env *env);

// env_list
t_env		*create_node(char *key, char *value, t_env **prev);
t_env		*lst_last(t_env *lst);
void		node_add_back(t_env **list, t_env *node);
t_env		*create_env_list(char **env);
int			print_env_list(t_env *env);

int			is_valid_var_name_char(char c);

/*EXEC*/

// exec
int			is_able_2_fork(t_pack *pack);
void		exec_cmd(t_pack *pack, t_global *gb);

// files
int			close_files(t_pack *pack);

// functions
int			dad_process(t_pack *pack);
void		wait_child(int pid);
int			process_pack(t_pack *pack, t_global *gb);
int			process_packs(t_global *gb);
int			listen(t_global *gb);

// here_doc_utils
void		process_val_here(char *s, int i, int *r, t_global *gb);
int			here_size(char *s, int i, t_global *gb);

// here_doc
void		init_here_var_builder(t_token_builder *tb, char *s, t_global *gb);
void		expand_here_var(t_token_builder *tb, t_global *gb);
char		*parse_here(char *rt, t_global *gb);
int			here_doc(t_pack *pack, char *limiter, t_global *gb);

// redir
int			redir_in(t_pack *pack);
int			redir_out(t_pack *pack);
int			create_next_pipe(t_pack *current_pack, t_pack *next_pack);

// signal
void		signal_handler(int sig);
void		child_sig(int sig);
void		here_sig(int sig);

/* PRINT FUNCTIONS*/

int			print_minichell(void);
int			print_color(char *msg, char *color);
int			print_pack(t_pack *pack);
int			print_err_msg(char *msg, char *cmd);
int			print_packs(t_global *gb);

/* PRINT FUNCTIONS*/
int			is_empty_line(char *line);

/* MAIN */
t_global	*init_global(char **envp);
int			main(int argc, char const *argv[], char **env);

#endif