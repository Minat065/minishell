/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/19 00:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"

int	is_lparen(char c)
{
	return (c == '(');
}

int	is_rparen(char c)
{
	return (c == ')');
}

int	handle_lparen(const char *input, t_lexer_state *st, t_token_stream *stream)
{
	st->start_index = st->index;
	add_token(stream, create_token(TOKEN_LPAREN, &input[st->index], 1, st));
	st->index++;
	st->column++;
	return (0);
}

int	handle_rparen(const char *input, t_lexer_state *st, t_token_stream *stream)
{
	st->start_index = st->index;
	add_token(stream, create_token(TOKEN_RPAREN, &input[st->index], 1, st));
	st->index++;
	st->column++;
	return (0);
}
