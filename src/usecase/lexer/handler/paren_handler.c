/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:28:56 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:28:57 by mokabe           ###   ########.fr       */
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
