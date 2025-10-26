/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:15:51 by tatsato           #+#    #+#             */
/*   Updated: 2025/10/26 23:51:02 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"

int	is_pipe(char c)
{
	return (c == '|');
}

int	handle_pipe(const char *input, t_lexer_state *st, t_token_stream *stream)
{
	if (input[st->index + 1] == '|')
	{
		add_token(stream, create_token(TOKEN_OR, &input[st->index], 2, st));
		st->index += 2;
		st->column += 2;
	}
	else
	{
		add_token(stream, create_token(TOKEN_PIPE, &input[st->index], 1, st));
		st->index++;
		st->column++;
	}
	return (0);
}
