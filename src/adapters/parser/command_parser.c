/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:27:11 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/14 22:16:26 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/adapters/parser/parser_internal.h"
#include "../../../src/utils/libft/libft.h"
#include <stdlib.h>

static char	*concat_strings(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

int	add_word_to_cmd(t_cmd *cmd, t_token_stream *tokens, int *argc)
{
	if (!tokens->current->space_before && *argc > 0)
	{
		cmd->argv[*argc - 1] = concat_strings(cmd->argv[*argc - 1],
				tokens->current->value.word);
		if (!cmd->argv[*argc - 1])
			return (0);
	}
	else
	{
		cmd->argv = extend_argv(cmd->argv, *argc);
		if (!cmd->argv)
			return (0);
		cmd->argv[*argc] = ft_strdup(tokens->current->value.word);
		if (!cmd->argv[*argc])
			return (0);
		(*argc)++;
	}
	tokens->current = tokens->current->next;
	return (1);
}

int	add_redirect_to_cmd(t_cmd *cmd, t_token_stream *tokens,
		t_cmd_redirect **last_redirect)
{
	t_cmd_redirect	*new_redirect;

	new_redirect = parse_redirection(tokens);
	if (!new_redirect)
		return (0);
	if (!cmd->redirects)
	{
		cmd->redirects = new_redirect;
		*last_redirect = new_redirect;
	}
	else
	{
		(*last_redirect)->next = new_redirect;
		*last_redirect = new_redirect;
	}
	return (1);
}

int	process_command_tokens(t_cmd *cmd, t_token_stream *tokens, int *argc,
		t_cmd_redirect **last_redirect)
{
	while (tokens->current && tokens->current->type != TOKEN_PIPE
		&& tokens->current->type != TOKEN_EOF)
	{
		if (tokens->current->type == TOKEN_WORD)
		{
			if (!add_word_to_cmd(cmd, tokens, argc))
				return (0);
		}
		else if (tokens->current->type == TOKEN_REDIRECT)
		{
			if (!add_redirect_to_cmd(cmd, tokens, last_redirect))
				return (0);
		}
		else
			break ;
	}
	return (1);
}

t_cmd	*parse_simple_command(t_token_stream *tokens)
{
	t_cmd			*cmd;
	t_cmd_redirect	*last_redirect;
	int				argc;

	cmd = init_simple_command();
	if (!cmd)
		return (NULL);
	last_redirect = NULL;
	argc = 0;
	if (!process_command_tokens(cmd, tokens, &argc, &last_redirect))
	{
		free_cmd(cmd);
		return (NULL);
	}
	if (argc == 0)
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}
