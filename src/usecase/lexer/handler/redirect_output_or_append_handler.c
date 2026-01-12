/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output_or_append_handler.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:17:02 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:29:05 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/lexer/token_creator.h"
#include "usecase/lexer/token_manager.h"
#include "usecase/lexer/token_type_handler.h"
#include "utils/libft_custom.h"

/**
 * always return 1
 * @param c
 */
int	is_redirect_output_or_append(char c)
{
	return (c == '>');
}

int	handle_redirect_output_or_append(const char *input, t_lexer_state *st,
		t_token_stream *stream)
{
	int	start;

	start = st->index;
	st->start_index = start;
	st->index++;
	if (input[st->index] == '>')
		st->index++;
	add_token(stream, create_token(TOKEN_REDIRECT, input + start, st->index
			- start, st));
	return (EXIT_SUCCESS);
}
