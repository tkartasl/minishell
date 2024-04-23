/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:39 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/23 12:15:10 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_over_arg(char *s, char quote, int len)
{
	while (s[len] != ' ' && s[len] != 0 && s[len] != '\''
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

int	get_arg_len(char *str)
{
	char	quote;
	int		len;

	quote = *str;
	len = 0;
	if (str[len] == '\'' || str[len] == '"')
		len = get_cmd_len(str, *str);
	else
		len = loop_over_arg(str, quote, len);
	return (len);
}
