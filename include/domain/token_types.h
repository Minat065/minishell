/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:09:07 by tatsato           #+#    #+#             */
/*   Updated: 2025/10/26 23:49:00 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TYPES_H
# define TOKEN_TYPES_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_ASSIGNMENT,
	TOKEN_OPERATOR,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
	TOKEN_EOF,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_ERROR
}	t_token_type;

/* リダイレクトのタイプ */
typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	REDIRECT_OUTPUT_ERROR
}	t_redirect_type;

#endif
