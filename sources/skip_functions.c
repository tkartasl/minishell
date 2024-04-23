/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:11:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/23 12:15:02 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_word(char *str, char quote)
{
	while (*str != 0 && *str != ' ' && *str != '<'
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

char	*skip_arg(char *str)
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

char	*skip_digit(char *str)
{
	char	*temp;

	temp = str;
	while (*temp != 0 && ft_isdigit(*temp) == 1)
		temp++;
	if (*temp != '<' && *temp != '>')
		return (str);
	else
		return (temp);
}
