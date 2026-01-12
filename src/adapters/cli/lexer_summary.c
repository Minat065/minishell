/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_summary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/cli/debug_output.h"
#include "domain/token.h"
#include "libft.h"

static int	count_total_tokens(t_token_stream *stream)
{
	int		token_count;
	t_token	*current;

	token_count = 0;
	current = stream->head;
	while (current && current->type != TOKEN_EOF)
	{
		token_count++;
		current = current->next;
	}
	return (token_count);
}

static void	print_error_info(t_token_stream *stream, int token_count)
{
	(void)stream;
	(void)token_count;
}

void	print_lexer_summary(t_token_stream *stream)
{
	int	token_count;

	token_count = count_total_tokens(stream);
	if (stream->error_message)
		print_error_info(stream, token_count);
	(void)token_count;
}
