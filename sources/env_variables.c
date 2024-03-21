/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:38 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/21 12:50:47 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_all_env(char *old_str, char *expanded_str, int i)
{
	int		flag;
	char	*str;

	str = old_str;
	flag = 0;
	while (*str != 0)
	{
		i = 0;
		if (*str == '"')
		{
			flag++;
			str++;
		}
		if (*str == '\'' && flag % 2 == 0)
			expanded_str = cpy_quote_to_quote(str, expanded_str, &i);
		else if (*str == '$')
			expanded_str = cpy_expanded(str, expanded_str, &i);
		else
			expanded_str = cpy_line(str, expanded_str, &i, &flag);
		if (expanded_str == 0)
			return (0);
		str = str + i;
	}
	free(old_str);
	return (expanded_str);
}

static int	expand_filename(t_redir **redir)
{
	t_redir	*new;
	char	*expanded_str;
	int 	i;

	i = 0;
	expanded_str = ft_strdup("");
	if (expanded_str == 0)
		return (0);
	new = *redir;
	while (new != 0)
	{
		if (count_env_variables(new->filename) > 0)
			new->filename = expand_all_env(new->filename, expanded_str, i);
		if (new->filename == 0)
			return (0);
		new = new->next;
	}
	return (1);
}

static int	expand_command(t_cmd_args **cmd_arg, char *str)
{
	int	i;	
	int	flag;

	i = 0;
	while (cmd_arg[i] != 0)
	{
		flag = 0;
		if (cmd_arg[i]->cmd[0] == '$')
			flag++;
		if (count_env_variables(cmd_arg[i]->cmd) > 0)
			(cmd_arg[i]->cmd = expand_all_env(cmd_arg[i]->cmd, str, i));
		if (cmd_arg[i]->cmd == 0)
			return (0);
	
		if (flag > 0 && word_count(cmd_arg[i]->cmd) > 1)
		{
			if (split_cmd(cmd_arg, i) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	expand_arguments(t_cmd_args ** arr)
{
	int		i;
	int		j;
	char	*s;
	
	i = 0;
	j = 0;
	s = ft_strdup("");
	if (s == 0)
		return (0);
	while (arr[i] != 0)
	{
		while (arr[i]->args[j] != 0)
		{
			if (count_env_variables(arr[i]->args[j]) > 0)
				(arr[i]->args[j] = expand_all_env(arr[i]->args[j], s, i));
			if (arr[i]->args[j] == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_envs(t_cmd_args **cmd_arg)
{
	char	*expanded_str;
	
	expanded_str = ft_strdup("");
	if (expanded_str == 0)
		return (0);
	if (expand_command(cmd_arg, expanded_str) == 0)
		return (0);
	if (expand_arguments(cmd_arg) == 0)
		return (0);
	if (expand_filename((*cmd_arg)->head_redir) == 0)
		return (0);
	return (1);
}