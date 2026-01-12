/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:17:10 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 14:50:28 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/cli/debug_output.h"
#include "adapters/cli/output_utils.h"
#include "adapters/cli/parser_output.h"
#include "adapters/parser/parser_interface.h"
#include "domain/command.h"
#include "domain/token.h"
#include "interfaces/io_interface.h"
#include "interfaces/output_interface.h"
#include "interfaces/process_interface.h"
#include "usecase/builtin/builtin_commands.h"
#include "usecase/env/env_manager.h"
#include "usecase/executor/executor.h"
#include "usecase/lexer/lexer.h"
#include "usecase/lexer/token_manager.h"
#include "usecase/lexer/token_printer.h"
#include "usecase/signal/signal_handler.h"
#include "utils/libft_custom.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			shell_loop(t_exec_context *exec_ctx);
int			init_and_run(char **envp);

static void	process_parsed_result(t_parse_result *result, t_exec_context *ctx,
		t_token_stream *stream)
{
	if (result && result->error_msg)
	{
		print_parse_result(result);
		ctx->last_exit_status = 2;
	}
	else if (result && !result->error_msg && result->ast)
		execute_pipeline_list(result->ast, ctx);
	if (result)
		free_parse_result(result);
	free_tokens(stream);
}

static void	process_input_line(char *line, t_exec_context *exec_ctx)
{
	t_token_stream	*stream;
	t_parse_result	*result;

	stream = lexer(line);
	if (stream->error_message)
	{
		ft_putendl_fd(stream->error_message, STDERR_FILENO);
		exec_ctx->last_exit_status = 258;
		free_tokens(stream);
		return ;
	}
	result = parse(stream);
	process_parsed_result(result, exec_ctx, stream);
}

int	handle_line(char *line, t_exec_context *ctx)

{
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	if (g_signal_received == SIGINT && *line == '\0')
	{
		ctx->last_exit_status = 130;
		g_signal_received = 0;
	}
	if (*line)
		add_history(line);
	process_input_line(line, ctx);
	free(line);
	if (ctx->should_exit)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (init_and_run(envp));
}
