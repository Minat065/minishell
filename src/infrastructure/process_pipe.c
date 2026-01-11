/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/process_interface.h"
#include <unistd.h>

t_process_result	process_create_pipe(t_pipe_info *pipe_info)
{
	int	pipefd[2];

	if (!pipe_info)
		return (PROCESS_ERROR_PIPE);
	if (pipe(pipefd) == -1)
		return (PROCESS_ERROR_PIPE);
	pipe_info->read_fd = pipefd[0];
	pipe_info->write_fd = pipefd[1];
	return (PROCESS_SUCCESS);
}

t_process_result	process_close_pipe(t_pipe_info *pipe_info)
{
	if (!pipe_info)
		return (PROCESS_ERROR_PIPE);
	if (pipe_info->read_fd >= 0)
		close(pipe_info->read_fd);
	if (pipe_info->write_fd >= 0)
		close(pipe_info->write_fd);
	pipe_info->read_fd = -1;
	pipe_info->write_fd = -1;
	return (PROCESS_SUCCESS);
}

t_process_result	process_duplicate_fd(int old_fd, int new_fd)
{
	if (old_fd < 0 || new_fd < 0)
		return (PROCESS_ERROR_DUP);
	if (dup2(old_fd, new_fd) == -1)
		return (PROCESS_ERROR_DUP);
	return (PROCESS_SUCCESS);
}

t_process_result	process_close_fd(int fd)
{
	if (fd < 0)
		return (PROCESS_SUCCESS);
	if (close(fd) == -1)
		return (PROCESS_ERROR_DUP);
	return (PROCESS_SUCCESS);
}
