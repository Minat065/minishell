/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:27:11 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 11:24:26 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/parser/parser_internal.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

int					should_stop_parsing(t_token *token);

static t_pipeline	*parse_group_content(t_token_stream *tokens,
		t_parse_result *result)
{
	t_pipeline	*first_pipeline;
	t_pipeline	*current_pipeline;
	t_pipeline	*new_pipeline;

	first_pipeline = NULL;
	current_pipeline = NULL;
	while (!should_stop_parsing(tokens->current))
	{
		new_pipeline = create_and_parse_pipeline(tokens, result);
		if (!new_pipeline)
		{
			free_pipeline(first_pipeline);
			return (NULL);
		}
		add_pipeline_to_list(&first_pipeline, &current_pipeline, new_pipeline);
		if (!handle_operator(tokens, current_pipeline, result))
		{
			free_pipeline(first_pipeline);
			return (NULL);
		}
	}
	return (first_pipeline);
}

static t_pipeline	*parse_grouped_pipeline(t_token_stream *tokens,
		t_parse_result *result)
{
	t_pipeline	*new_pipeline;
	t_pipeline	*group_content;

	tokens->current = tokens->current->next;
	new_pipeline = create_pipeline();
	if (!new_pipeline)
		return (NULL);
	group_content = parse_group_content(tokens, result);
	if (!group_content && result->error_msg)
	{
		free_pipeline(new_pipeline);
		return (NULL);
	}
	if (!tokens->current || tokens->current->type != TOKEN_RPAREN)
	{
		result->error_msg = ft_strdup("syntax error: unmatched parenthesis");
		free_pipeline(group_content);
		free_pipeline(new_pipeline);
		return (NULL);
	}
	tokens->current = tokens->current->next;
	new_pipeline->group = group_content;
	return (new_pipeline);
}

t_pipeline	*create_and_parse_pipeline(t_token_stream *tokens,
		t_parse_result *result)
{
	t_pipeline	*new_pipeline;
	t_cmd		*cmds;

	if (tokens->current && tokens->current->type == TOKEN_LPAREN)
		return (parse_grouped_pipeline(tokens, result));
	new_pipeline = create_pipeline();
	if (!new_pipeline)
		return (NULL);
	cmds = parse_pipeline(tokens, result);
	if (!cmds)
	{
		free_pipeline(new_pipeline);
		return (NULL);
	}
	new_pipeline->cmds = cmds;
	return (new_pipeline);
}

t_parse_result	*parse_main_loop(t_token_stream *tokens, t_parse_result *result)
{
	t_pipeline	*first_pipeline;
	t_pipeline	*current_pipeline;
	t_pipeline	*new_pipeline;

	first_pipeline = NULL;
	current_pipeline = NULL;
	while (tokens->current && tokens->current->type != TOKEN_EOF)
	{
		new_pipeline = create_and_parse_pipeline(tokens, result);
		if (!new_pipeline)
		{
			if (!handle_parse_error(result, first_pipeline))
				return (NULL);
			return (result);
		}
		add_pipeline_to_list(&first_pipeline, &current_pipeline, new_pipeline);
		if (!handle_operator(tokens, current_pipeline, result))
		{
			free_pipeline(first_pipeline);
			result->ast = NULL;
			return (result);
		}
	}
	result->ast = first_pipeline;
	return (result);
}

t_parse_result	*parse(t_token_stream *tokens)
{
	t_parse_result	*result;

	if (!tokens || !tokens->head)
		return (NULL);
	result = create_parse_result();
	if (!result)
		return (NULL);
	tokens->current = tokens->head;
	return (parse_main_loop(tokens, result));
}
