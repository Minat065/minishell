/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <dirent.h>
#include <stdlib.h>

int	match_pattern(const char *pattern, const char *str)
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

int	has_wildcard(const char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

int	count_matches(const char *pattern)
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

static char	**alloc_and_open(const char *pattern, int *mc, DIR **dir)
{
	char	**matches;

	*mc = count_matches(pattern);
	if (*mc == 0)
		return (NULL);
	matches = malloc(sizeof(char *) * (*mc + 1));
	if (!matches)
		return (NULL);
	*dir = opendir(".");
	if (!*dir)
		return (free(matches), NULL);
	return (matches);
}

char	**get_matches(const char *pattern, int *match_count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = alloc_and_open(pattern, match_count, &dir);
	if (!matches)
		return (NULL);
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
