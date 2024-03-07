/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/07 09:31:34 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *str)
{
	int	i;
	int	temp;

	temp = 0;
	i = 0;
	while (str[i] != ' ' && str[i] != 0 && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"' || str[i] == '\'')
			temp = get_quotes_len(&str[i], str[i]);
		if (temp != 0)
			return (i + temp);
		i++;
	}
	return (i);	
}

char	*skip_redirs(char *cmd_line)
{
	if (*cmd_line == '>' && (*(cmd_line + 1) == '>'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' && (*(cmd_line + 1) == '<'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' || *cmd_line == '>')
		cmd_line++;
	cmd_line = ft_skip_whitespace(cmd_line);
	return (cmd_line);
}

int	get_pipe_count(char **cmd_lines)
{
	int	i;

	i = 0;
	while(cmd_lines[i] != 0)
		i++;
	return (i);
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

int	get_quotes_len(char *s, char quote)
{
	int		i;
	int		temp;

	temp = 0;
	i = 0;
	i++;
	while (s[i] == '\'' || s[i] == '\"')
		i++;
	temp = i;
	if (s[i] == ' ')
	{
		while (s[i] != 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
			|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'))
			i++;
	}
	if (s[i] == '\'' || s[i] == '\"')
		return (i);
	i = temp;
	while (s[i] != 0 && s[i] != quote)
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i] != ' ' && s[i] != 0)
		i++;
	return (i);
}
