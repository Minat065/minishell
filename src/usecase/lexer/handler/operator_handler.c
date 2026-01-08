/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"
#include "utils/libft_custom.h"

int	is_ampersand(char c)
{
	return (c == '&');
}

int	is_semicolon(char c)
{
	return (c == ';');
}

int	handle_ampersand(const char *input, t_lexer_state *st, t_token_stream *stream)
{
	if (input[st->index + 1] == '&')
	{
		add_token(stream, create_token(TOKEN_OPERATOR, &input[st->index], 2, st));
		st->index += 2;
		st->column += 2;
	}
	else
	{
		stream->error_message = ft_strdup("syntax error near unexpected token `&'");
		stream->error_line = st->line;
		stream->error_column = st->column;
		return (-1);
	}
	return (0);
}

int	handle_semicolon(const char *input, t_lexer_state *st, t_token_stream *stream)
{
	add_token(stream, create_token(TOKEN_OPERATOR, &input[st->index], 1, st));
	st->index++;
	st->column++;
	return (0);
}
