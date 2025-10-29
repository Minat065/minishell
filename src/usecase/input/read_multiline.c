/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_multiline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:00:07 by mokabe            #+#    #+#             */
/*   Updated: 2025/10/29 23:20:16 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/signal/signal_handler.h"
#include "utils/libft_custom.h"
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum e_qstate
{
	Q_NONE,
	Q_SQUOTE,
	Q_DQUOTE
}			t_qstate;

bool		needs_more_input(const char *s, t_qstate *state, bool *line_cont);
char		*join_with_newline_and_strip_bslash(char *a, const char *b,
				int strip_bslash);

static int	handle_eof(t_qstate st, int *exit_status, char *line)
{
	if (st == Q_SQUOTE)
		ft_putstr_fd("unexpected EOF while looking for matching '\\''\n", 2);
	else if (st == Q_DQUOTE)
		ft_putstr_fd("unexpected EOF while looking for matching '\"'\n", 2);
	ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	*exit_status = 2;
	free(line);
	return (1);
}

char	*read_multiline(char *line, int *exit_status)
{
	t_qstate	st;
	bool		cont;
	bool		trail;
	char		*more;
	char		*joined;

	cont = needs_more_input(line, &st, &trail);
	while (cont)
	{
		if (g_signal_received == SIGINT)
			return (free(line), *exit_status = 130, NULL);
		more = readline("> ");
		if (!more && handle_eof(st, exit_status, line))
			return (NULL);
		joined = join_with_newline_and_strip_bslash(line, more, trail);
		free(line);
		free(more);
		line = joined;
		cont = needs_more_input(line, &st, &trail);
	}
	return (line);
}
