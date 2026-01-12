/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 00:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/builtin/builtin_commands.h"
#include "usecase/executor/executor.h"
#include <unistd.h>

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
