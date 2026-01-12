/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:10 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "usecase/signal/signal_handler.h"
#include "utils/libft_custom.h"
#include <readline/readline.h>
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*append_line(char *content, char *line)
{
	char	*temp;
	char	*new_content;
	size_t	content_len;
	size_t	line_len;

	if (!content)
	{
		temp = ft_strjoin(line, "\n");
		return (temp);
	}
	content_len = ft_strlen(content);
	line_len = ft_strlen(line);
	new_content = malloc(content_len + line_len + 2);
	if (!new_content)
	{
		free(content);
		return (NULL);
	}
	ft_strlcpy(new_content, content, content_len + 1);
	ft_strlcpy(new_content + content_len, line, line_len + 1);
	new_content[content_len + line_len] = '\n';
	new_content[content_len + line_len + 1] = '\0';
	free(content);
	return (new_content);
}

static int	check_delimiter_match(char *line, const char *delimiter)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strlen(line) == delimiter_len
		&& ft_strncmp(line, delimiter, delimiter_len) == 0)
		return (1);
	return (0);
}

static char	*read_heredoc_loop(const char *delimiter, char *content)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal_received == SIGINT)
		{
			free(line);
			free(content);
			return (NULL);
		}
		if (!line)
			break ;
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			break ;
		}
		content = append_line(content, line);
		free(line);
		if (!content)
			return (NULL);
	}
	return (content);
}

char	*collect_heredoc_content(const char *delimiter)
{
	char	*content;

	g_signal_received = 0;
	setup_heredoc_signal_handlers();
	content = read_heredoc_loop(delimiter, NULL);
	setup_signal_handlers();
	if (!content)
		return (NULL);
	if (content[0] == '\0')
	{
		free(content);
		content = ft_strdup("");
	}
	return (content);
}
