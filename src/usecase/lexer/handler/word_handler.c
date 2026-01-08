/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:17:02 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/01 16:17:31 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft_custom.h"
#include "domain/token.h"
#include "usecase/lexer/token_manager.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_type_handler.h"

/**
 * allways return 1
 * @param c
 */
int	is_word(char c)
{
	return (
		!ft_isspace(c)
		&& !is_single_quote(c)
		&& !is_double_quote(c)
		&& !is_pipe(c)
		&& !is_redirect_input_or_heredoc(c)
		&& !is_redirect_output_or_append(c)
		&& !is_ampersand(c)
		&& !is_semicolon(c)
	);
}

int	validate_assignment_first_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	validate_assignment(char *str)
{
	if (*str == '+')
	{
		if (*(str + 1) == '=')
			return (1);
	}
	return (ft_isalnum(*str) || *str == '_');
}

static int	skip_quoted_content(const char *input, t_lexer_state *st, char quote)
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
	if (input[st->index] == quote)
	{
		st->index++;
		st->column++;
		return (0);
	}
	return (-1);
}

static int	is_word_continue(char c, int after_equal)
{
	if (after_equal && (is_single_quote(c) || is_double_quote(c)))
		return (1);
	return (is_word(c));
}

int	handle_word_or_assignment(const char *input,
		t_lexer_state *st, t_token_stream *stream)
{
	int	start;
	int	after_equal;

	start = st->index;
	after_equal = 0;
	while (input[st->index] && is_word_continue(input[st->index], after_equal))
	{
		if (input[st->index] == '=')
			after_equal = 1;
		else if (after_equal && is_single_quote(input[st->index]))
		{
			if (skip_quoted_content(input, st, '\'') == -1)
				break ;
			continue ;
		}
		else if (after_equal && is_double_quote(input[st->index]))
		{
			if (skip_quoted_content(input, st, '"') == -1)
				break ;
			continue ;
		}
		st->index++;
	}
	add_token(stream, create_token(
			TOKEN_WORD, &input[start], st->index - start, st));
	st->column += (st->index - start);
	return (EXIT_SUCCESS);
}
