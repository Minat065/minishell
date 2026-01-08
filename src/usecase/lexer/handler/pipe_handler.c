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
	int	start;

	start = st->index;
	if (input[st->index + 1] == '|')
	{
		st->index += 2;
		st->column += 2;
		add_token(stream, create_token(TOKEN_OR, &input[start], 2, start, st));
	}
	else
	{
		st->index++;
		st->column++;
		add_token(stream, create_token(TOKEN_PIPE, &input[start], 1, start, st));
	}
	return (0);
}
