/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:22 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 15:50:52 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	handle_heredoc_redirect_with_service(const char *delimiter,
		t_process_service *proc_service)
{
	(void)proc_service;
	return (handle_heredoc_redirect(delimiter));
}

int	handle_heredoc_with_content(const char *content)
{
	int	pipefd[2];

	if (!content)
	{
		ft_printf("minishell: heredoc: missing content\n");
		return (-1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed for heredoc");
		return (-1);
	}
	write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed for heredoc");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int			collect_heredocs_for_cmd(t_cmd *cmd);

static int	collect_heredocs_for_cmd_chain(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (collect_heredocs_for_cmd(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	collect_heredocs_for_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*current;

	if (!pipeline)
		return (0);
	current = pipeline;
	while (current)
	{
		if (current->group)
		{
			if (collect_heredocs_for_pipeline(current->group) == -1)
				return (-1);
		}
		if (current->cmds)
		{
			if (collect_heredocs_for_cmd_chain(current->cmds) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
