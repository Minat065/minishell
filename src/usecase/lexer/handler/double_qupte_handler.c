/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_qupte_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:15:11 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:28:41 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

int	is_double_quote(char c)
{
	return (c == '\"');
}

static int	set_dquote_error(t_token_stream *stream, t_lexer_state *st)
{
	stream->error_message = ft_strdup("Unclosed double quote");
	stream->error_line = st->line;
	stream->error_column = st->column;
	return (-1);
}

static void	add_dquote_token(t_token_stream *stream, const char *input,
		int start, t_lexer_state *st)
{
	char	*quoted;
	char	*marked;

	st->index++;
	st->column++;
	quoted = ft_strndup(&input[start], st->index - start - 1);
	marked = ft_strjoin("\x02", quoted);
	free(quoted);
	add_token(stream, create_token(TOKEN_WORD, marked, ft_strlen(marked), st));
	free(marked);
}

int	handle_double_quote(const char *input, t_lexer_state *st,
		t_token_stream *stream)
{
	int	content_start;

	st->start_index = st->index;
	st->index++;
	st->column++;
	content_start = st->index;
	while (input[st->index])
	{
		if (input[st->index] == '\n' || input[st->index] == '"')
			break ;
		st->index++;
		st->column++;
	}
	if (input[st->index] != '"')
		return (set_dquote_error(stream, st));
	add_dquote_token(stream, input, content_start, st);
	return (0);
}
