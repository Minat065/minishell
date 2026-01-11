/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/01 17:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERFACE_H
# define PARSER_INTERFACE_H

# include "../../domain/command.h"
# include "../../domain/token.h"

typedef struct s_parse_result	t_parse_result;

struct s_parse_result
{
	t_pipeline	*ast;
	char		*error_msg;
	int			error_line;
	int			error_column;
};

t_parse_result	*parse(t_token_stream *tokens);
void			free_parse_result(t_parse_result *result);

#endif
