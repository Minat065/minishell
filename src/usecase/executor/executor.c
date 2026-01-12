/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/builtin/builtin_commands.h"
#include "usecase/executor/executor.h"
#include "usecase/signal/signal_handler.h"
#include "utils/libft_custom.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* Check if pipeline should be executed based on previous connector */
static int	should_execute_pipeline(t_pipeline *prev, int status)
{
	if (!prev)
		return (1);
	if (prev->connector == CONN_AND && status != EXIT_SUCCESS)
		return (0);
	if (prev->connector == CONN_OR && status == EXIT_SUCCESS)
		return (0);
	return (1);
}

/* Execute a list of pipelines connected by operators (&&, ||, ;) */
int	execute_pipeline_list(t_pipeline *pipelines, t_exec_context *ctx)
{
	t_pipeline	*current;
	t_pipeline	*prev;
	int			status;

	if (!pipelines || !ctx)
		return (EXIT_FAILURE);
	if (collect_heredocs_for_pipeline(pipelines) == -1)
	{
		if (g_signal_received == SIGINT)
		{
			ctx->last_exit_status = 130;
			g_signal_received = 0;
		}
		return (ctx->last_exit_status);
	}
	current = pipelines;
	prev = NULL;
	status = 0;
	while (current && !ctx->should_exit)
	{
		if (should_execute_pipeline(prev, status))
		{
			status = execute_pipeline(current, ctx);
			ctx->last_exit_status = status;
		}
		prev = current;
		current = current->next;
	}
	return (ctx->last_exit_status);
}

/* Execute a single pipeline (commands connected by pipes) */
int	execute_pipeline(t_pipeline *pipeline, t_exec_context *ctx)
{
	if (!pipeline || !ctx)
		return (EXIT_FAILURE);
	if (pipeline->group)
		return (execute_pipeline_list(pipeline->group, ctx));
	if (!pipeline->cmds)
		return (EXIT_FAILURE);
	if (!pipeline->cmds->next)
		return (execute_single_command(pipeline->cmds, ctx));
	else
		return (execute_command_chain(pipeline->cmds, ctx));
}

/* Execute a chain of commands connected by pipes */
int	execute_command_chain(t_cmd *cmds, t_exec_context *ctx)
{
	if (!cmds || !ctx)
		return (EXIT_FAILURE);
	return (execute_pipe_chain_with_service(cmds, ctx));
}

/* Execute a single command */
int	execute_single_command(t_cmd *cmd, t_exec_context *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd || !cmd->argv || !cmd->argv[0] || !ctx)
		return (EXIT_FAILURE);
	expand_command_variables(cmd, ctx);
	expand_command_wildcards(cmd, ctx);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->redirects && setup_redirections_with_service(cmd->redirects,
			ctx->process_service) != 0)
	{
		ctx->process_service->close_fd(saved_stdin);
		ctx->process_service->close_fd(saved_stdout);
		return (EXIT_FAILURE);
	}
	if (is_builtin(cmd->argv[0]))
		status = execute_builtin(cmd, ctx);
	else
		status = execute_external(cmd, ctx);
	restore_redirections_with_service(saved_stdin, saved_stdout,
		ctx->process_service);
	return (status);
}
