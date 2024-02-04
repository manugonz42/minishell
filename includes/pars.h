/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:35:47 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/29 12:52:04 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H
# include "struct.h"	
# include <sys/wait.h>

//temp
void		print_token_type(t_token *token);
void		print_command(t_cmd *cmd);
void		print_tokens(t_token *token);

// command_utils
int			command_size(t_token *token);
int			is_valid_path(char *str);
char		*check_cmd_path(char *cmd, char **paths);
int			cmd_path_checks(char *cmd, char **paths);
int			check_no_command(t_pack *pack);

// error
int			print_error(char *cmd, char *err, char *option, char flag);
int			perror_exit(char *function);
int			unclosed_quote_error(void);
int			newline_error(t_global *gb);
int			unexpected_token_error(char *token, t_global *gb);

// exit
void		free_all(t_global *gb);
void		malloc_error(void);

//free_things
void		close_fds(t_global *gb, int i);
void		free_packs(t_global *gb);
void		free_command(t_cmd *cmd);
void		free_env_list(t_env *env);

// init_tokens
int			init_token(t_pack *pack, t_token *token, t_global *gb);
int			init_tokens(t_global *gb);

// pars_utils_is
int			is_separator(char c);
int			is_redir(char c);
int			is_valid_var_name_char(char c);
int			is_single_char(char *s, int i, t_e_quote quote);
int			is_empty_line(char *line);

// pars_utils
void		skip_spaces(char *line, int *i);
char		next_token(char *line, int i);
int			token_size_without_quotes(char *s, int i, t_global *gb);
void		quote_status(char c, t_e_quote *quote);
int			count_packs(t_global *gb);

// pars.c
int			check_unclosed_quote(char *s);
void		set_pipe_case(t_global *gb);
int			check_empty_pack(t_global *gb);
int			pars(t_global *gb);

// set_command
char		*ft_join_path(char *path, char *cmd);
void		alloc_command(t_pack *pack);
void		fill_command(t_pack *pack);
void		set_command(t_pack *pack, t_global *gb);

// set_pack
int			initialize_pack(t_pack **pack, t_global *gb, int start, int end);
void		handle_pipe_case(t_global *gb, int *k, int *n, int i);
int			divide_in_packs(t_global *gb);

// set_token
void		init_t_token_builder(t_token_builder *tb, char *s, t_global *gb);
char		*clean_token(char *s, t_pack *pack, t_global *gb);
int			save_separator(t_pack *pack, int *i, t_global *gb);
int			cross_str(t_pack *pack, int *i, t_global *gb);
int			set_tokens(t_global *gb);

// token_list_del
t_token		*lst_delone_token(t_token *lst);
t_token		*lst_clear_token(t_token *lst);

// token_list
t_e_token	set_token_type(char *str);
t_token		*lst_new_token(char *str, t_e_token type);
t_token		*lst_last_token(t_token *token);
t_token		*lst_add_back_token(t_token **token, t_token *new);
t_token		*lst_add_front_token(t_token **token, t_token *new);

// token_redir_list
int			set_out_redir(t_pack *pack, t_token *token, t_global *gb);
int			set_out_append(t_pack *pack, t_token *token, t_global *gb);
int			set_here_doc(t_pack *pack, t_token *token, t_global *gb);
int			set_in_redir(t_pack *pack, t_token *token, t_global *gb);

// token_utils
char		*get_key(char *line);
void		to_next_token(char *s, int *i);
int			separator_error_case_check(t_pack *pack, int *i);

// var_expand
void		process_val_pack(char *s, int i, int *r, t_global *gb);
void		expand_exit_status(t_token_builder *tb);
void		save_without_spc(t_token_builder *tb, char *var_value);
void		save_with_spaces(t_token_builder *tb, char *var_value);
void		expand_global_var(t_token_builder *tb, t_pack *pack, t_global *gb);

#endif
