/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:15:07 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/lexer/token_printer.h"
#include "libft.h"

static void	print_redirect_token(t_token *token)
{
	if (token->value.redirect.redirect_type == REDIRECT_INPUT)
		ft_printf("REDIRECT IN: <\n");
	else if (token->value.redirect.redirect_type == REDIRECT_OUTPUT)
		ft_printf("REDIRECT OUT: >\n");
	else if (token->value.redirect.redirect_type == REDIRECT_HEREDOC)
		ft_printf("HEREDOC: <<\n");
	else if (token->value.redirect.redirect_type == REDIRECT_APPEND)
		ft_printf("APPEND: >>\n");
}

static void	print_single_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
		ft_printf("WORD: %s\n", token->value.word);
	else if (token->type == TOKEN_PIPE)
		ft_printf("PIPE: %s\n", "|");
	else if (token->type == TOKEN_EOF)
		ft_printf("EOF\n");
	else if (token->type == TOKEN_REDIRECT)
		print_redirect_token(token);
	else if (token->type == TOKEN_ASSIGNMENT)
		ft_printf("ASSIGNMENT: %s=%s\n", token->value.assignment.name,
			token->value.assignment.value);
	else if (token->type == TOKEN_ERROR)
		ft_printf("ERROR: %s\n", token->value.word);
	else
		ft_printf("UNKNOWN\n");
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		print_single_token(token);
		token = token->next;
	}
}
