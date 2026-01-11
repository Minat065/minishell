/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/01 17:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../domain/token_types.h"

typedef struct s_cmd			t_cmd;
typedef struct s_cmd_redirect	t_cmd_redirect;
typedef struct s_pipeline		t_pipeline;

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
	t_cmd_redirect	*redirects;
	t_cmd			*next;
};

struct s_cmd_redirect
{
	t_redirect_type	type;
	char			*file;
	int				fd;
	char			*heredoc_content;
	t_cmd_redirect	*next;
};

struct s_pipeline
{
	t_cmd		*cmds;
	t_pipeline	*group;
	t_pipeline	*next;
	int			connector;
};

void	free_pipeline(t_pipeline *pipeline);
void	free_cmd(t_cmd *cmd);
void	free_redirect(t_cmd_redirect *redirect);

#endif
