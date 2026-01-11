/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_service.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 22:09:21 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/process_interface.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static t_process_result	impl_fork_process(pid_t *pid)
{
	if (!pid)
		return (PROCESS_ERROR_FORK);
	*pid = fork();
	if (*pid == -1)
		return (PROCESS_ERROR_FORK);
	return (PROCESS_SUCCESS);
}

static t_process_result	impl_exec_command(const char *path, char **argv,
		char **envp)
{
	if (!path || !argv)
		return (PROCESS_ERROR_EXEC);
	if (execve(path, argv, envp) == -1)
		return (PROCESS_ERROR_EXEC);
	return (PROCESS_SUCCESS);
}

static t_process_result	impl_wait_process(pid_t pid, int *exit_status)
{
	int	status;

	if (pid <= 0)
		return (PROCESS_ERROR_WAIT);
	if (waitpid(pid, &status, 0) == -1)
		return (PROCESS_ERROR_WAIT);
	if (exit_status)
	{
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_status = 128 + WTERMSIG(status);
		else
			*exit_status = 1;
	}
	return (PROCESS_SUCCESS);
}

static t_process_result	impl_wait_all(pid_t *pids, int count, int *statuses)
{
	int	i;
	int	status;

	if (!pids || count <= 0)
		return (PROCESS_ERROR_WAIT);
	i = 0;
	while (i < count)
	{
		if (impl_wait_process(pids[i], &status) != PROCESS_SUCCESS)
			return (PROCESS_ERROR_WAIT);
		if (statuses)
			statuses[i] = status;
		i++;
	}
	return (PROCESS_SUCCESS);
}

t_process_service	*create_process_service(void)
{
	t_process_service	*service;

	service = malloc(sizeof(t_process_service));
	if (!service)
		return (NULL);
	service->fork_proc = impl_fork_process;
	service->exec_cmd = impl_exec_command;
	service->wait_proc = impl_wait_process;
	service->wait_all = impl_wait_all;
	service->create_pipe = process_create_pipe;
	service->close_pipe = process_close_pipe;
	service->dup_fd = process_duplicate_fd;
	service->close_fd = process_close_fd;
	service->is_running = process_is_running;
	service->get_err_msg = process_get_error_message;
	return (service);
}

void	destroy_process_service(t_process_service *service)
{
	if (service)
		free(service);
}
