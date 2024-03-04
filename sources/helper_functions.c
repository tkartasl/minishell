/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/04 14:13:10 by tkartasl         ###   ########.fr       */
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

char	*skip_quotes(char *str, char quote)
{
	char	*temp;

	temp = str;
	str++;
	while (*str != 0 && *str != quote)
		str++;
	if (*str == 0)
		return (temp);
	str++;
	return (str);
}

int	get_quotes_len(char *str, char quote)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != 0 && str[i] != quote)
		i++;
	if (str[i] == 0)
		return (0);
	i++;
	return (i);
}