/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_or_heredoc_handler.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:17:02 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:29:03 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"
#include "usecase/lexer/token_type_handler.h"
#include "utils/libft_custom.h"

/**
 * allways return 1
 * @param c
 */
int	is_redirect_input_or_heredoc(char c)
{
	return (c == '<');
}

int	handle_redirect_input_or_heredoc(const char *input, t_lexer_state *st,
		t_token_stream *stream)
{
	int	start;

	start = st->index;
	st->start_index = start;
	st->index++;
	if (input[st->index] == '<')
		st->index++;
	add_token(stream, create_token(TOKEN_REDIRECT, input + start, st->index
			- start, st));
	return (1);
}
