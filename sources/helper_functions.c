/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/12 14:21:45 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != 0 && str[i] != '<' && str[i] != '>')
		i++;
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

static int	loop_over_cmd(char *s, char quote, int i)
{
	while (s[i] != 0)
		{
			while (s[i] != quote && s[i] != 0)
				i++;
			if (s[i] == 0 || (s[i] == quote && s[++i] == ' '))
				break ;
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i];
				while (s[i] != quote && s[i] != 0)
					i++;
			}
			else
			{
				while (s[i] != ' ' && s[i] != 0 && s[i] != '\'' && s[i] != '\"')
					i++;
			}
			if (s[i] != 0)
				i++;
		}
	return (i);
}

int	get_cmd_len(char *s, char quote)
{
	int		i;

	i = 0;
	while (s[i] == quote)
		i++;
	if (s[i] == ' ' && i % 2 == 0)
		return (i);
	else if (i % 2 == 0)
	{
		while (s[i] != ' ' && s[i] != 0)
			i++;
		return (i);
	}
	else
		i = loop_over_cmd(s, quote, i);
	return (i);
}


