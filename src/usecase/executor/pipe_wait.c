/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:28:01 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:28:03 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "usecase/signal/signal_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	wait_for_children_with_service(pid_t *pids, int cmd_count,
		t_process_service *proc_service)
{
	int	i;
	int	status;
	int	last_status;

	last_status = EXIT_SUCCESS;
	i = 0;
	while (i < cmd_count)
	{
		if (proc_service->wait_proc(pids[i], &status) != PROCESS_SUCCESS)
		{
			perror("wait failed for child process");
			return (EXIT_FAILURE);
		}
		if (i == cmd_count - 1)
			last_status = status;
		i++;
	}
	return (last_status);
}

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		if (WTERMSIG(status) == SIGQUIT)
			return (131);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	ignore_signals();
	last_status = EXIT_SUCCESS;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			last_status = get_exit_status(status);
		i++;
	}
	setup_signal_handlers();
	return (last_status);
}
