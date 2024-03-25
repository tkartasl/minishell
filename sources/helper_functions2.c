/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:39 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/25 14:17:53 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_quotes(char *str, char quote)
{
	char	*temp;

	str++;
	temp = str;
	while (*str != 0 && *str != quote)
		str++;
	if (*str == 0)
		return (temp);
	str++;
	return (str);
}

static char	*skip_word(char *str, char quote)
{
	while(*str != 0 && *str != ' ' && *str != '<' 
		&& *str != '>' && *str != '\'' && *str != '"')
	{
		if (ft_isdigit(*str) == 1 && *(str - 1) == ' ')
	    {
			while (*str != 0 && ft_isdigit(*str) == 1)
				str++;
			if (*str == '<' || *str == '>')
				return (str);
			else
				str--;
		}
		str++;
	}
	if (*str == '\'' || *str == '"')
	{
		quote = *str;
		str++;
		while (*str != quote && *str != 0)
			str++;
		if (*str == quote)
			str++;	
	}
	return (str);
}

char    *skip_arg(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
    if (*str == '\'' || *str == '"')
    {
        i = get_cmd_len(str, *str);
		str = str + i;
        return (str);
    }
    else
		str = skip_word(str, quote);
	return (str);
}

static int	loop_over_arg(char *s, char quote, int len)
{
	while(s[len] != ' ' && s[len] != 0 && s[len] != '\''
		&& s[len] != '"' && s[len] != '>' && s[len] != '<')
	{
		if (ft_isdigit(s[len]) == 1 && s[len - 1] == ' ')
	    {
			while (s[len] != 0 && ft_isdigit(s[len]) == 1)
				len++;
			if (s[len] == '<' || s[len] == '>')
				return (0);
			else
				len--;
		}
		len++;
	}
	if (s[len] == '\'' || s[len] == '"')
	{
		quote = s[len];
		len++;
		while (s[len] != quote && s[len] != 0)
			len++;
	}
	if (s[len] == quote)
		len++;
	return (len);
}

int get_arg_len(char *str)
{
    char    quote;
    int     len;

    quote = *str;
    len = 0;
    if (str[len] == '\'' || str[len] == '"')
		len = get_cmd_len(str, *str);
    else
		len = loop_over_arg(str, quote, len);
	return (len);
}
