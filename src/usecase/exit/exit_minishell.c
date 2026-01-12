/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:42:06 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:28:36 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/env/env_manager.h"
#include "usecase/lexer/token_manager.h"
#include <stdlib.h>

void	exit_minishell(int exit_code, t_token_stream *stream, t_env_var *env)
{
	if (stream)
		free_tokens(stream);
	if (env)
		env_free(env);
	exit(exit_code);
}
