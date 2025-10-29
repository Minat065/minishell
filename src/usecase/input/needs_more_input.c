/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs_more_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:59:34 by mokabe            #+#    #+#             */
/*   Updated: 2025/10/29 22:59:38 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft_custom.h"
#include <stdbool.h>

typedef enum e_qstate
{
	Q_NONE,
	Q_SQUOTE,
	Q_DQUOTE
}				t_qstate;

static t_qstate	update_state(t_qstate st, char c, bool *esc)
{
	if (st == Q_SQUOTE && c == '\'')
		return (Q_NONE);
	if (st == Q_DQUOTE)
	{
		if (*esc)
			*esc = false;
		else if (c == '\\')
			*esc = true;
		else if (c == '"')
			return (Q_NONE);
		return (Q_DQUOTE);
	}
	if (c == '\'')
		return (Q_SQUOTE);
	if (c == '"')
		return (Q_DQUOTE);
	return (Q_NONE);
}

bool	needs_more_input(const char *s, t_qstate *state, bool *line_cont)
{
	size_t		i;
	size_t		len;
	bool		esc;
	t_qstate	st;

	st = Q_NONE;
	esc = false;
	i = 0;
	while (s[i])
	{
		st = update_state(st, s[i], &esc);
		i++;
	}
	len = ft_strlen(s);
	if (state)
		*state = st;
	if (line_cont)
		*line_cont = (len > 0 && s[len - 1] == '\\');
	return (st != Q_NONE || (len > 0 && s[len - 1] == '\\'));
}
