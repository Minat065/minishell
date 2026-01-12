/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:10 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:27:11 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <readline/readline.h>
#include <stdio.h>
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

static char	*collect_heredoc_content(const char *delimiter)
{
	char	*content;
	char	*line;
	size_t	delimiter_len;

	content = NULL;
	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == delimiter_len && ft_strncmp(line, delimiter,
				delimiter_len) == 0)
		{
			free(line);
			break ;
		}
		content = append_line(content, line);
		free(line);
		if (!content)
			return (NULL);
	}
	if (!content)
		content = ft_strdup("");
	return (content);
}

static int	collect_heredoc_for_redirect(t_cmd_redirect *redirect)
{
	if (redirect->type != REDIRECT_HEREDOC)
		return (0);
	if (redirect->heredoc_content)
		return (0);
	redirect->heredoc_content = collect_heredoc_content(redirect->file);
	if (!redirect->heredoc_content)
		return (-1);
	return (0);
}

int	collect_heredocs_for_cmd(t_cmd *cmd)
{
	t_cmd_redirect	*redirect;

	if (!cmd)
		return (0);
	redirect = cmd->redirects;
	while (redirect)
	{
		if (collect_heredoc_for_redirect(redirect) == -1)
			return (-1);
		redirect = redirect->next;
	}
	return (0);
}
