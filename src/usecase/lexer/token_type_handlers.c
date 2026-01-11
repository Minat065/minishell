/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:48:08 by tatsato           #+#    #+#             */
/*   Updated: 2025/05/25 18:29:15 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <usecase/lexer/token_type_handler.h>

static void	init_handlers(t_token_handler *h)
{
	h[0].match = ft_isspace;
	h[0].handler.handler_regular = handle_space;
	h[1].match = is_single_quote;
	h[1].handler.handler_regular = handle_single_quote;
	h[2].match = is_double_quote;
	h[2].handler.handler_regular = handle_double_quote;
	h[3].match = is_pipe;
	h[3].handler.handler_regular = handle_pipe;
	h[4].match = is_redirect_input_or_heredoc;
	h[4].handler.handler_regular = handle_redirect_input_or_heredoc;
	h[5].match = is_redirect_output_or_append;
	h[5].handler.handler_regular = handle_redirect_output_or_append;
	h[6].match = is_ampersand;
	h[6].handler.handler_regular = handle_ampersand;
	h[7].match = is_semicolon;
	h[7].handler.handler_regular = handle_semicolon;
	h[8].match = is_lparen;
	h[8].handler.handler_regular = handle_lparen;
	h[9].match = is_rparen;
	h[9].handler.handler_regular = handle_rparen;
	h[10].match = is_word;
	h[10].handler.handler_regular = handle_word_or_assignment;
}

t_token_type_handlers	create_token_handlers(void)
{
	t_token_type_handlers	handlers;

	handlers.token_handler_count = 11;
	handlers.token_handlers = malloc(sizeof(t_token_handler)
			* handlers.token_handler_count);
	if (!handlers.token_handlers)
	{
		handlers.token_handler_count = 0;
		return (handlers);
	}
	init_handlers(handlers.token_handlers);
	return (handlers);
}

void	free_token_handlers(t_token_type_handlers *handlers)
{
	if (handlers->token_handlers)
	{
		free(handlers->token_handlers);
		handlers->token_handlers = NULL;
	}
}

int	dispatch_token_handler(const char *input, t_lexer_state *st,
		t_token_stream *stream, t_token_type_handlers *handlers)
{
	int	i;

	i = 0;
	while (i < handlers->token_handler_count)
	{
		if (handlers->token_handlers[i].match(input[st->index]))
			return (handlers->token_handlers[i].handler.handler_regular(input,
					st, stream));
		i++;
	}
	return (-1);
}
