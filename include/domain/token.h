/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:09:07 by tatsato           #+#    #+#             */
/*   Updated: 2025/10/26 23:49:02 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "assignment.h"
# include "token_types.h"

typedef struct s_redirect
{
	t_redirect_type	redirect_type;
}					t_redirect;

typedef union u_value
{
	char			*word;
	t_assignment	assignment;
	t_redirect		redirect;
}					t_value;

/* トークン構造体 */
typedef struct s_token
{
	t_token_type	type;
	int				length;
	t_value			value;
	int				line_number;
	int				column;
	struct s_token	*next;
}					t_token;

/* トークンリスト管理構造体 */
typedef struct s_token_stream
{
	t_token			*head;
	t_token			*current;
	int				count;
	char			*error_message;
	int				error_line;
	int				error_column;
}					t_token_stream;

typedef struct s_lexer_state
{
	int				index;
	int				line;
	int				column;
}					t_lexer_state;

#endif
