/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:38 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/11 10:15:54 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 char	*expand_all_env(char *old, char *expanded_str, int i, t_env **env)
{
	int		flag;
	char	*str;

	str = old;
	flag = 0;
	while (*str != 0)
	{
		i = 0;
		if (*str == '"')
		{
			flag++;
			expanded_str = cpy_double_quote(&str, expanded_str);
		}
		if (*str == '\'' && flag % 2 == 0)
			expanded_str = cpy_quote_to_quote(str, expanded_str, &i);
		else if (*str == '$')
			expanded_str = cpy_expanded(str, expanded_str, &i, env);
		else		
			expanded_str = cpy_line(str, expanded_str, &i, &flag);
		if (expanded_str == 0)
			return (0);
		str = str + i;
	}
	free(old);
	return (expanded_str);
}

static int	expand_filename(t_redir **redir, t_env **env, int i, int *flag)
{
	t_redir	*new;
	char	*expanded;

	new = *redir;
	while (new != 0)
	{
		if (new->filename[0] == '$')
			if (ft_get_env(&new->filename[1], env) == 0)
				print_error_filename(&new->filename[0], flag);
		if (count_env_variables(new->filename) > 0 && *flag == 0)
		{
			expanded = ft_strdup("");
			if (expanded == 0)
				return (0);
			new->filename = expand_all_env(new->filename, expanded, i, env);
			if (new->filename == 0)
			{
				free(expanded);
				return (0);
			}
		}
		new = new->next;
	}
	return (1);
}

static int	expand_command(t_cmd_args **cmd_arg, t_env **env, int i)
{	
	int	flag;
	int	len;
	
	len = 0;
	while (cmd_arg[i] != 0)
	{
		flag = 0;
		if (cmd_arg[i]->cmd[0] == '$')
			flag++;
		cmd_arg[i]->cmd = count_expand_cmd(cmd_arg[i]->cmd, i, env);
		if (cmd_arg[i]->cmd == 0)
			return (0);
		if (flag > 0 && word_count(cmd_arg[i]->cmd) > 1)
		{
			if (split_cmd(cmd_arg, i, len) == 0)
				return (0);
		}
		i++;
	}	
	return (1);
}

static int	expand_arguments(t_cmd_args **arr, t_env **env, char *str, int i)
{
	int		j;
	
	i = -1;
	j = 0;
	while (arr[++i] != 0)
	{
		while (arr[i]->args[j] != 0)
		{
			if (count_env_variables(arr[i]->args[j]) > 0)
			{
				str = ft_strdup("");
				if (str == 0)
					return (0);
				arr[i]->args[j] = expand_all_env(arr[i]->args[j], str, i, env);
				if (arr[i]->args[j] == 0)
				{
					free(str);	
					return (0);
				}
			}
			j++;
		}
		j = 0;
	}
	return (1);
}

int	get_envs(t_cmd_args **cmd_arg, t_env **env_table, int *flag)
{
	char	*arg;
	int		i;

	i = 0;
	arg = 0;
	if (expand_command(cmd_arg, env_table, i) == 0)
		return (0);
	if (expand_arguments(cmd_arg, env_table, arg, i) == 0)
		return (0);
	if (expand_filename((*cmd_arg)->head_redir, env_table, i, flag) == 0)
		return (0);
	if (*flag == 1)
		return (0);
	return (1);
}
