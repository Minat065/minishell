/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/01 17:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "domain/token.h"

typedef struct s_cmd			t_cmd;
typedef struct s_redirect_list	t_redirect_list;
typedef struct s_pipeline		t_pipeline;
typedef struct s_parse_result	t_parse_result;

typedef enum e_connector
{
	CONN_NONE = 0,
	CONN_AND,
	CONN_OR,
	CONN_SEMICOLON
}	t_connector;

struct s_cmd
{
	char			**argv;
	t_redirect_list	*redirects;
	t_cmd			*next;
};

struct s_redirect_list
{
	t_redirect_type	type;
	char			*file;
	int				fd;
	t_redirect_list	*next;
};

struct s_pipeline
{
	t_cmd		*cmds;
	t_pipeline	*next;
	int			connector;
};

struct s_parse_result
{
	t_pipeline	*ast;
	char		*error_msg;
	int			error_line;
	int			error_column;
};

t_parse_result	*parse(t_token_stream *tokens);
void			free_parse_result(t_parse_result *result);
void			free_pipeline(t_pipeline *pipeline);
void			free_cmd(t_cmd *cmd);
void			free_redirect(t_redirect_list *redirect);

#endif
