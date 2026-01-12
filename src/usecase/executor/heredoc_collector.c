/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:10 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include "libft.h"
#include <stdlib.h>

char	*collect_heredoc_content(const char *delimiter);

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
