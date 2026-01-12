/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:27:15 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	process_heredoc_line(int pipefd, char *line, const char *delimiter)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strlen(line) == delimiter_len && ft_strncmp(line, delimiter,
			delimiter_len) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd, line, ft_strlen(line));
	write(pipefd, "\n", 1);
	free(line);
	return (0);
}

static void	heredoc_child_process(int pipefd_write, const char *delimiter)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (process_heredoc_line(pipefd_write, line, delimiter))
			break ;
		line = readline("> ");
	}
	close(pipefd_write);
	exit(0);
}

static int	setup_heredoc_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed for heredoc");
		return (-1);
	}
	return (0);
}

static int	handle_heredoc_parent(int *pipefd, pid_t pid)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed for heredoc");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int	handle_heredoc_redirect(const char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (!delimiter)
	{
		printf("minishell: syntax error: missing delimiter\n");
		return (-1);
	}
	if (setup_heredoc_pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		heredoc_child_process(pipefd[1], delimiter);
	else if (pid > 0)
		return (handle_heredoc_parent(pipefd, pid));
	perror("fork failed for heredoc");
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}
