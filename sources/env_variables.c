/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:38 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/13 14:11:21 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_variable(char *str, char *temp, int len_var, int len_cmd)
{
	char	*expanded_var;
	char	*new_cmd;
	char    *env_var;
	char	*cmd;

	env_var = strndup(temp, len_var);
	if (env_var == 0)
		return (0);
	cmd = strndup(str, len_cmd);
	if (cmd == 0)
		return (0);
	expanded_var = getenv(env_var);
	new_cmd = ft_strjoin_free(cmd, expanded_var);
	free(env_var);
	return (new_cmd);
}

char	*check_env_variable(char *str)
{
	char	*temp;
	int		len_var;
	int		len_cmd;

	len_var = 0;
	len_cmd = 0;
	temp = str;
	while (*temp != 0)
	{
		if (*temp == '$')
		{
			temp++;
			while (temp[len_var] != 0 && temp[len_var] != ' ')
				len_var++;
			temp = expand_env_variable(str, temp, len_var, len_cmd);
			if (temp == 0)
				return (0);
			free(str);
			return (temp);
		}
		len_cmd++;
		temp++;
	}
	return (str);
}
