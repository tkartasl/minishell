/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:36:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/01 14:15:18 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cpy_double_quote(char **str, char *expanded_str)
{
	char	*temp;
	
	
	temp = ft_strndup((*str), 1);
	if (temp == 0)
		return (0);
	*str += 1;
	expanded_str = ft_strjoin_free(expanded_str, temp);
	if (expanded_str == 0)
		return (0);
	free(temp);
	return (expanded_str);
}

int	count_env_variables(char *str)
{
	char	*temp;
	int		env_count;
	int		flag;

	flag = 0;
	temp = str;
	env_count = 0;
	while (*temp != 0)
	{
		if (*temp == '"')
			flag++;
		if (*temp == '\'' && flag % 2 == 0)
			temp = skip_quotes(temp, *temp);
		if (*temp == '$')
			env_count++;
		temp++;
	}
	return (env_count);
}

int	word_count(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	temp = str;
	while (*temp != 0)
	{
		if (*temp != ' ' && *temp != 0)
			count++;
		while (*temp != ' ' && *temp != 0)
			temp++;
		if (*temp != 0)
			temp++;
	}
	return (count);
}

static int	insert_arg(t_cmd_args **cmd_arg, char *temp_arg, int idx)
{
	char	**new_args;
	int		j;
	int		i;

	i = 0;	
	j = 0;
	while (cmd_arg[idx]->args[j] != 0)
		j++;
	new_args = malloc((j + 1) * sizeof(char *));
	if (new_args == 0)
		return (0);
	j = 0;
	new_args[j] = temp_arg;
	j++;
	while (cmd_arg[idx]->args[i] != 0)
	{
		new_args[j] = cmd_arg[idx]->args[i];
		i++;
		j++;
	}
	ft_free_pointer_array(cmd_arg[idx]->args);
	cmd_arg[idx]->args = new_args;
	return (1);
}

int	split_cmd(t_cmd_args **cmd_arg, int i)
{
	int		len;		
	char	*temp;
	char	*temp_args;

	temp_args = 0;
	temp = 0;
	len = 0;
	while (cmd_arg[i]->cmd[len] != ' ' && cmd_arg[i]->cmd[len] != 0)
		len++;
	if (cmd_arg[i]->cmd[len] == ' ')
		temp = ft_strndup(cmd_arg[i]->cmd, len);
	if (temp == 0)
		return (0);
	len++;
	temp_args = ft_strdup(&cmd_arg[i]->cmd[len]);
	if (temp_args == 0)
		return (0);
	if (insert_arg(cmd_arg, temp_args, i) == 0)
		return (0);
	free(cmd_arg[i]->cmd);
	cmd_arg[i]->cmd = temp;
	return (1);
}
