/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
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
