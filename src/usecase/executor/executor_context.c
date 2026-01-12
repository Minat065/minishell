/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_context.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:26:47 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:26:48 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include <stdlib.h>

/* Create execution context */
t_exec_context	*create_exec_context(t_env_var **env, t_io_service *io,
		t_output_service *out, t_process_service *proc)
{
	t_exec_context	*ctx;

	ctx = malloc(sizeof(t_exec_context));
	if (!ctx)
		return (NULL);
	ctx->env = env;
	ctx->io_service = io;
	ctx->output_service = out;
	ctx->process_service = proc;
	ctx->last_exit_status = 0;
	ctx->should_exit = 0;
	ctx->exit_code = 0;
	return (ctx);
}

/* Free execution context */
void	free_exec_context(t_exec_context *ctx)
{
	if (ctx)
		free(ctx);
}
