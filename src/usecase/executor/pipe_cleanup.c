/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:44 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:27:45 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include <unistd.h>

void	cleanup_pipes_with_service(int *pipefd, int cmd_count,
		t_process_service *proc_service)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		proc_service->close_fd(pipefd[i * 2]);
		proc_service->close_fd(pipefd[i * 2 + 1]);
		i++;
	}
}

void	cleanup_pipes(int *pipefd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipefd[i * 2]);
		close(pipefd[i * 2 + 1]);
		i++;
	}
}
