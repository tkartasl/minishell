/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:43:42 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/15 12:18:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_syntax(char *line)
{
	line++;
	if (*line == '&' || *line == '|')
		return (1);
	if (*line == '<' || *line == '>')
		line++;
	if (*line == '<' || *line == '>' || *line == '|' || *line == '&')
		return (1);
	return (0);
}

int	check_newline(char *line, t_env **env)
{
	while (*line != 0)
	{
		if (*line == '\n')
		{
			syntax_error(0, env, 'X');
			return (1);
		}
		line++;
	}
	return (0);
}
