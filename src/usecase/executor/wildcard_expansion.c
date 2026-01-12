/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:28:23 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:28:24 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

int			has_wildcard(const char *str);
char		**get_matches(const char *pattern, int *match_count);

static int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

static int	is_quoted(const char *str)
{
	return (str[0] == '\x01' || str[0] == '\x02');
}

static char	**build_expanded_argv(char **argv, char **matches, int pos, int mc)
{
	char	**new_argv;
	int		argc;
	int		i;
	int		j;

	argc = count_argv(argv);
	new_argv = malloc(sizeof(char *) * (argc + mc));
	if (!new_argv)
		return (NULL);
	i = -1;
	while (++i < pos)
		new_argv[i] = argv[i];
	j = -1;
	while (++j < mc)
		new_argv[i + j] = matches[j];
	while (argv[pos + 1])
		new_argv[i + j++] = argv[++pos];
	new_argv[i + j] = NULL;
	return (new_argv);
}

static char	**expand_single_wildcard(char **argv, int pos, int *new_argc)
{
	char	**matches;
	char	**new_argv;
	int		match_count;
	int		argc;

	matches = get_matches(argv[pos], &match_count);
	if (!matches)
	{
		*new_argc = count_argv(argv);
		return (argv);
	}
	argc = count_argv(argv);
	new_argv = build_expanded_argv(argv, matches, pos, match_count);
	if (!new_argv)
		return (*new_argc = argc, argv);
	free(argv[pos]);
	free(argv);
	free(matches);
	*new_argc = argc + match_count - 1;
	return (new_argv);
}

void	expand_command_wildcards(t_cmd *cmd, t_exec_context *ctx)
{
	int		i;
	int		argc;
	char	*stripped;

	(void)ctx;
	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		if (!is_quoted(cmd->argv[i]) && has_wildcard(cmd->argv[i]))
			cmd->argv = expand_single_wildcard(cmd->argv, i, &argc);
		if (!cmd->argv)
			return ;
		if (is_quoted(cmd->argv[i]))
		{
			stripped = ft_strdup(cmd->argv[i] + 1);
			free(cmd->argv[i]);
			cmd->argv[i] = stripped;
		}
		i++;
	}
}
