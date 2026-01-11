/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_chain_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include <stdlib.h>
#include <unistd.h>

int	setup_pipe_resources_with_service(t_cmd *cmds, int **pipefd,
		pid_t **pids, t_process_service *proc_service)
{
	int	cmd_count;

	cmd_count = allocate_pipe_resources(cmds, pipefd, pids);
	if (cmd_count == -1 || create_pipes_with_service(*pipefd, cmd_count,
			proc_service) == -1)
	{
		free(*pipefd);
		free(*pids);
		return (-1);
	}
	return (cmd_count);
}

int	setup_pipe_resources(t_cmd *cmds, int **pipefd, pid_t **pids)
{
	int	cmd_count;

	cmd_count = allocate_pipe_resources(cmds, pipefd, pids);
	if (cmd_count == -1 || create_pipes(*pipefd, cmd_count) == -1)
	{
		free(*pipefd);
		free(*pids);
		return (-1);
	}
	return (cmd_count);
}

void	cleanup_and_free_resources(int *pipefd, pid_t *pids, int cmd_count)
{
	cleanup_pipes(pipefd, cmd_count);
	free(pipefd);
	free(pids);
}

int	finalize_pipe_execution_with_service(int *pipefd, pid_t *pids,
		int cmd_count, t_process_service *proc_service)
{
	cleanup_pipes_with_service(pipefd, cmd_count, proc_service);
	cmd_count = wait_for_children_with_service(pids, cmd_count, proc_service);
	free(pipefd);
	free(pids);
	return (cmd_count);
}

int	finalize_pipe_execution(int *pipefd, pid_t *pids, int cmd_count)
{
	cleanup_pipes(pipefd, cmd_count);
	cmd_count = wait_for_children(pids, cmd_count);
	free(pipefd);
	free(pids);
	return (cmd_count);
}
