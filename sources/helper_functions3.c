/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:29:54 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/09 15:39:57 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_last_char(char *temp)
{
	int	i;
	
	i = 1;
	while(temp[i] != 0 && ft_strchr(" \"'$?/", temp[i]) == 0)
		i++;
	if (temp[i] != ' ' && temp[i] != 0)
		return (1);
	return (0);
}

char	*check_null_cmd(char *line, t_env **env)
{
	char	*temp;	
	char	*newline;

	newline = 0;
	temp = line;
	temp = ft_skip_whitespace(temp);
	if (*temp == '$')
	{
		if (check_last_char(temp) > 0)
			return (line);
		if (ft_get_env(&temp[1], env) == 0)
		{
			temp++;
			while (*temp != 0 && ft_strchr(" \"'$?/", *temp) == 0)
				temp++;
			newline = ft_strndup(temp, ft_strlen(temp));
			if (newline == 0)
				return (0);
			free(line);
			return (newline);
		}
	}
	return (line);
}
