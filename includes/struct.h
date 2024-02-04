/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:35:52 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/26 12:46:27 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

typedef struct t_env
{
	struct t_env	*previous;
	char			*key;
	char			*value;
	struct t_env	*next;
}	t_env;

typedef struct s_pack
{
	int		id;
	char	*raw_str;
	pid_t	pid;
	t_cmd	*cmd;
	int		here_doc;
	int		infile;
	char	*infile_name;
	int		outfile;
	char	*outfile_name;
	int		ispipein;
	int		ispipeout;
	int		pipein[2];
	int		pipeout[2];
	int		err;
	t_token	*token;
}	t_pack;

typedef struct s_global
{
	t_env	*env;
	int		fd[2];
	int		n_of_packs;
	char	*line;
	int		last_cmd_status;
	t_pack	**packs;
}	t_global;

struct s_cmd
{
	char	**cmd;
	char	*path;
	int		is_built;
	int		err;
};

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_e_quote;

typedef enum e_token
{
	NON,
	ARG,
	IN_REDIR,
	OUT_REDIR,
	OUT_APPEND,
	HERE_DOC,
	PIPE,
	LIMITOR,
	BUILTIN
}	t_e_token;

struct	s_token
{
	char		*str;
	t_e_token	type;
	t_token		*next;
	t_token		*prev;
	bool		quoted;
};

typedef struct s_token_builder
{
	char		*raw;
	char		*token;
	int			r_pos;
	int			t_pos;
	t_e_quote	quote;
}	t_token_builder;

#endif