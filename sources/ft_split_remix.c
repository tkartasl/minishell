/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_remix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:27:48 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/04 17:28:31 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *skip_quotes(char *str, char quote)
{
    char    *temp;

    temp = str;
    str++;
    while (*str != 0 && *str != quote)
        str++;
    if (*str == 0)
        return (temp);
    str++;
    return (str);
}

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

static	void	ft_free(char **arr, int k)
{
	while (k >= 0)
	{
		free(arr[k]);
		k--;
	}
	free(arr);
}

int split_quotes(char *s, int j)
{
    int tmp;

    tmp = j;
    if (s[j] == '\'')
    {
        j++;
        while(s[j] != '\'' && s[j] && s[j])
        {   
            j++;
        }
    }
    else if (s[j] == '"')
    {
        j++;
        while(s[j] != '"' && s[j] && s[j])
            j++;
    }
    if (s[j] == 0)
        return(tmp);
    return (j - tmp);
}

static int	ft_get_lenght(char *s, int i, char c)
{
    int tmp;

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
			j = ft_get_lenght(s, i, c);
			arr[k] = ft_substr(s, i, j);
			if (arr[k] == 0)
			{
				ft_free(arr, k);
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
/*
int main()
{
    char s[] = "echo mo '|' | echo moi | moi \"|\" | moi -l";
    char **r;

    r = ft_split_remix(s, '|');
    int i = 0;
    while(r[i] != 0)
    {
        printf("%s\n", r[i]);
        i++;
    }

}*/