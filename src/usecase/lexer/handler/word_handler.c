/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:17:02 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:29:14 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"
#include "usecase/lexer/token_type_handler.h"
#include "utils/libft_custom.h"

int	is_word(char c)
{
	return (!ft_isspace(c) && !is_single_quote(c) && !is_double_quote(c)
		&& !is_pipe(c) && !is_redirect_input_or_heredoc(c)
		&& !is_redirect_output_or_append(c) && !is_ampersand(c)
		&& !is_semicolon(c) && !is_lparen(c) && !is_rparen(c));
}

static int	skip_quoted(const char *input, t_lexer_state *st, char quote)
{
	st->index++;
	st->column++;
	while (input[st->index] && input[st->index] != quote)
	{
		if (input[st->index] == '\n')
			return (-1);
		st->index++;
		st->column++;
	}
	if (input[st->index] != quote)
		return (-1);
	st->index++;
	st->column++;
	return (0);
}

static int	handle_quoted_part(const char *input, t_lexer_state *st)
{
	if (is_single_quote(input[st->index]))
		return (skip_quoted(input, st, '\''));
	if (is_double_quote(input[st->index]))
		return (skip_quoted(input, st, '"'));
	return (1);
}

static int	process_word_char(const char *input, t_lexer_state *st, int *aeq)
{
	int	qr;

	if (input[st->index] == '=')
		*aeq = 1;
	else if (*aeq && (is_single_quote(input[st->index])
			|| is_double_quote(input[st->index])))
	{
		qr = handle_quoted_part(input, st);
		if (qr <= 0)
			return (qr);
	}
	st->index++;
	return (1);
}

int	handle_word_or_assignment(const char *input, t_lexer_state *st,
		t_token_stream *stream)
{
	int	start;
	int	after_equal;

	start = st->index;
	st->start_index = start;
	after_equal = 0;
	while (input[st->index] && (is_word(input[st->index]) || after_equal))
	{
		if (!is_word(input[st->index]) && !after_equal)
			break ;
		if (process_word_char(input, st, &after_equal) <= 0)
			break ;
	}
	add_token(stream, create_token(TOKEN_WORD, &input[start], st->index - start,
			st));
	st->column += (st->index - start);
	return (EXIT_SUCCESS);
}
