/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:30:38 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:30:39 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "interfaces/output_interface.h"
#include "interfaces/process_interface.h"
#include "usecase/env/env_manager.h"
#include "usecase/executor/executor.h"
#include "usecase/signal/signal_handler.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int			handle_line(char *line, t_exec_context *ctx);

static int	handle_sigint(t_exec_context *exec_ctx)
{
	exec_ctx->last_exit_status = 130;
	g_signal_received = 0;
	return (1);
}

int	shell_loop(t_exec_context *exec_ctx)
{
	char	*line;

	while (1)
	{
		g_signal_received = 0;
		line = readline("minishell> ");
		if (g_signal_received == SIGINT)
		{
			if (handle_sigint(exec_ctx))
				continue ;
		}
		if (!handle_line(line, exec_ctx))
			break ;
	}
	return (exec_ctx->exit_code);
}

static void	cleanup_all(t_exec_context *ctx, t_env_var *env, void **svc)
{
	free_exec_context(ctx);
	if (env)
		env_free(env);
	destroy_io_service(svc[0]);
	destroy_output_service(svc[1]);
	destroy_process_service(svc[2]);
}

static int	init_services(void **services)
{
	services[0] = create_io_service();
	services[1] = create_output_service();
	services[2] = create_process_service();
	if (!services[0] || !services[1] || !services[2])
		return (0);
	return (1);
}

int	init_and_run(char **envp)
{
	t_env_var		*env;
	t_exec_context	*ctx;
	void			*svc[3];
	int				code;

	if (!init_services(svc))
		return (cleanup_all(NULL, NULL, svc), EXIT_FAILURE);
	env = NULL;
	if (envp)
		env = env_create_from_envp(envp);
	ctx = create_exec_context(&env, svc[0], svc[1], svc[2]);
	if (!ctx)
		return (cleanup_all(NULL, env, svc), EXIT_FAILURE);
	setup_signal_handlers();
	code = shell_loop(ctx);
	cleanup_all(ctx, env, svc);
	return (code);
}
