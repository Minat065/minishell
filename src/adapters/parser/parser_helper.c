/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/parser/parser_internal.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_OPERATOR || type == TOKEN_OR);
}

int	handle_operator(t_token_stream *tokens, t_pipeline *pipeline,
		t_parse_result *result)
{
	if (!tokens->current || !is_operator_token(tokens->current->type))
		return (1);
	pipeline->connector = get_connector_type(tokens->current->value.word);
	tokens->current = tokens->current->next;
	if (!tokens->current || tokens->current->type == TOKEN_EOF)
	{
		result->error_msg = ft_strdup("syntax error: unexpected end");
		return (0);
	}
	return (1);
}

int	add_pipeline_to_list(t_pipeline **first, t_pipeline **current,
		t_pipeline *new_pipeline)
{
	if (!*first)
	{
		*first = new_pipeline;
		*current = new_pipeline;
	}
	else
	{
		(*current)->next = new_pipeline;
		*current = new_pipeline;
	}
	return (1);
}

int	should_stop_parsing(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == TOKEN_EOF || token->type == TOKEN_RPAREN)
		return (1);
	return (0);
}
