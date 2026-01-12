/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:19:37 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 18:40:19 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/assignment/assignment_creator.h"
#include "usecase/lexer/token_creator.h"
#include <ctype.h>
#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	add_token(t_token_stream *stream, t_token *token)
{
	if (!stream->head)
	{
		stream->head = token;
		stream->current = token;
	}
	else
	{
		stream->current->next = token;
		stream->current = token;
	}
	stream->count++;
}

static int	has_word_value(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_OPERATOR || type == TOKEN_OR
		|| type == TOKEN_LPAREN || type == TOKEN_RPAREN);
}

void	free_tokens(t_token_stream *stream)
{
	t_token	*cur;
	t_token	*next;

	cur = stream->head;
	while (cur)
	{
		next = cur->next;
		if (has_word_value(cur->type))
			free(cur->value.word);
		else if (cur->type == TOKEN_ASSIGNMENT)
			free_assignment(&cur->value.assignment);
		free(cur);
		cur = next;
	}
	free(stream->error_message);
	free(stream);
}
