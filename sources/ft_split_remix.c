/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_remix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:27:48 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/15 10:17:03 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_arrsize(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
		{
			if (*s == '\'' || *s == '"')
				s = skip_quotes(s, *s);
			s++;
		}
	}
	return (i);
}

static int	split_quotes(char *s, int j)
{
	int	tmp;

	tmp = j;
	if (s[j] == '\'')
	{
		j++;
		while (s[j] != '\'' && s[j] && s[j])
		{
			j++;
		}
	}
	else if (s[j] == '"')
	{
		j++;
		while (s[j] != '"' && s[j] && s[j])
			j++;
	}
	if (s[j] == 0)
		return (tmp);
	return (j - tmp);
}

static int	ft_get_length(char *s, int i, char c)
{
	int	tmp;

	tmp = i;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i += split_quotes(s, i) + 1;
		}
		else
			i++;
	}
	return (i - tmp);
}

static int	ft_fillarr(char **arr, char *s, char c, int k)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			j = ft_get_length(s, i, c);
			arr[k] = ft_substr(s, i, j);
			if (arr[k] == 0)
			{
				ft_free_pointer_array(arr);
				return (-1);
			}
			k++;
			i += j;
		}
		else
			i++;
	}
	return (k);
}

char	**ft_split_remix(char *s, char c)
{
	char	**arr;
	int		k;

	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (ft_arrsize(s, c) + 1));
	if (arr == 0)
		return (0);
	k = 0;
	k = ft_fillarr(arr, s, c, k);
	if (k == -1)
		return (0);
	else
		arr[k] = 0;
	return (arr);
}
