/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/19 00:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <dirent.h>
#include <stdlib.h>

static int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (*(pattern + 1) == '\0')
			return (1);
		while (*str)
		{
			if (match_pattern(pattern + 1, str))
				return (1);
			str++;
		}
		return (match_pattern(pattern + 1, str));
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

static int	has_wildcard(const char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

static int	count_matches(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' || pattern[0] == '.')
		{
			if (match_pattern(pattern, entry->d_name))
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static char	**get_matches(const char *pattern, int *match_count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	*match_count = count_matches(pattern);
	if (*match_count == 0)
		return (NULL);
	matches = malloc(sizeof(char *) * (*match_count + 1));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(matches), NULL);
	i = 0;
	entry = readdir(dir);
	while (entry && i < *match_count)
	{
		if (entry->d_name[0] != '.' || pattern[0] == '.')
		{
			if (match_pattern(pattern, entry->d_name))
				matches[i++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	matches[i] = NULL;
	closedir(dir);
	return (matches);
}

static int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

static char	**expand_single_wildcard(char **argv, int pos, int *new_argc)
{
	char	**matches;
	char	**new_argv;
	int		match_count;
	int		argc;
	int		i;
	int		j;

	matches = get_matches(argv[pos], &match_count);
	if (!matches)
	{
		*new_argc = count_argv(argv);
		return (argv);
	}
	argc = count_argv(argv);
	new_argv = malloc(sizeof(char *) * (argc + match_count));
	if (!new_argv)
		return (*new_argc = argc, argv);
	i = -1;
	while (++i < pos)
		new_argv[i] = argv[i];
	j = -1;
	while (++j < match_count)
		new_argv[i + j] = matches[j];
	while (argv[pos + 1])
		new_argv[i + j++] = argv[++pos];
	new_argv[i + j] = NULL;
	free(argv[pos - (j - match_count)]);
	free(argv);
	free(matches);
	*new_argc = i + j;
	return (new_argv);
}

static int	is_quoted(const char *str)
{
	return (str[0] == '\x01' || str[0] == '\x02');
}

static void	strip_quote_markers(t_cmd *cmd)
{
	int		i;
	char	*stripped;

	i = 0;
	while (cmd->argv[i])
	{
		if (is_quoted(cmd->argv[i]))
		{
			stripped = ft_strdup(cmd->argv[i] + 1);
			free(cmd->argv[i]);
			cmd->argv[i] = stripped;
		}
		i++;
	}
}

void	expand_command_wildcards(t_cmd *cmd, t_exec_context *ctx)
{
	int	i;
	int	argc;

	(void)ctx;
	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		if (!is_quoted(cmd->argv[i]) && has_wildcard(cmd->argv[i]))
		{
			cmd->argv = expand_single_wildcard(cmd->argv, i, &argc);
			if (!cmd->argv)
				return ;
		}
		i++;
	}
	strip_quote_markers(cmd);
}
