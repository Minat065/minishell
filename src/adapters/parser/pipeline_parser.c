/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:27:11 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/26 23:48:39 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/parser/parser_internal.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

/* パースエラーを設定 */
void	set_parse_error(t_parse_result *result, t_token_stream *tokens,
		const char *msg)
{
	result->error_msg = ft_strdup(msg);
	if (tokens->current)
	{
		result->error_line = tokens->current->line_number;
		result->error_column = tokens->current->column;
	}
}

/* 最初のコマンドエラーを処理 */
void	handle_first_cmd_error(t_parse_result *result, t_token_stream *tokens)
{
	if (tokens->current && tokens->current->type == TOKEN_PIPE)
		set_parse_error(result, tokens,
			"syntax error near unexpected token '|'");
	else if (tokens->current && tokens->current->type == TOKEN_REDIRECT)
		set_parse_error(result, tokens,
			"syntax error near unexpected token 'newline'");
}

/* パイプ直後が不正な場合の構文エラー判定 */
static int	check_pipe_syntax_error(t_token_stream *tokens,
		t_parse_result *result)
{
	if (!tokens->current)
	{
		set_parse_error(result, tokens,
			"minishell: syntax error near unexpected token 'newline'");
		return (1);
	}
	if (tokens->current->type == TOKEN_PIPE)
	{
		set_parse_error(result, tokens,
			"minishell: syntax error near unexpected token '|'");
		return (1);
	}
	return (0);
}

/* パイプコマンドを処理 */
int	process_pipe_commands(t_token_stream *tokens, t_parse_result *result,
		t_cmd **current_cmd)
{
	t_cmd	*new_cmd;

	while (tokens->current && tokens->current->type == TOKEN_PIPE)
	{
		tokens->current = tokens->current->next;
		if (check_pipe_syntax_error(tokens, result))
			return (0);
		if (tokens->current->type == TOKEN_OR)
			break ;
		new_cmd = parse_simple_command(tokens);
		if (!new_cmd)
		{
			set_parse_error(result, tokens,
				"minishell: syntax error near unexpected token '|'");
			return (0);
		}
		(*current_cmd)->next = new_cmd;
		*current_cmd = new_cmd;
	}
	return (1);
}

/* パイプラインのパース（複数のコマンドをパイプで接続） */
t_cmd	*parse_pipeline(t_token_stream *tokens, t_parse_result *result)
{
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;

	first_cmd = parse_simple_command(tokens);
	if (!first_cmd)
	{
		handle_first_cmd_error(result, tokens);
		return (NULL);
	}
	current_cmd = first_cmd;
	if (!process_pipe_commands(tokens, result, &current_cmd))
	{
		free_cmd(first_cmd);
		return (NULL);
	}
	return (first_cmd);
}
