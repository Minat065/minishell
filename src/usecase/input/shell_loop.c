/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:00:36 by mokabe            #+#    #+#             */
/*   Updated: 2025/10/29 23:27:57 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_multiline.h"
#include "usecase/executor/executor.h"
#include "usecase/signal/signal_handler.h"
#include "utils/libft_custom.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void		process_input_line(char *line, t_exec_context *ctx);

static int	handle_input(t_exec_context *ctx, char *line)
{
	char	*full;
	int		ps2_status;

	ps2_status = ctx->last_exit_status;
	full = read_multiline(line, &ps2_status);
	if (!full)
	{
		ctx->last_exit_status = ps2_status;
		return (0);
	}
	if (*full)
		add_history(full);
	process_input_line(full, ctx);
	free(full);
	return (ctx->should_exit);
}

static void	print_exit(void)
{
	ft_putstr_fd("exit\n", 1);
}

int	shell_loop(t_exec_context *ctx)
{
	char	*line;

	while (1)
	{
		g_signal_received = 0;
		line = readline("minishell> ");
		if (!line)
			return (print_exit(), ctx->exit_code);
		if (g_signal_received == SIGINT)
			ctx->last_exit_status = 130;
		else if (*line && handle_input(ctx, line))
			return (free(line), ctx->exit_code);
		free(line);
	}
}
