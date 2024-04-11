/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:01 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/11 10:02:52 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char **cmd_line, t_env **env)
{
	(*env)->status = 258;
    ft_free_pointer_array(cmd_line);
    ft_putendl_fd("minishell: syntax error near unexpected token", 2);
}

void	list_free(t_redir **hdoc, t_redir **redir, char **line, int flag)
{
	if (flag == 1)
		ft_putendl_fd("minishell: error allocating memory", 2);
	if (line != 0)
		ft_free_pointer_array(line);
	redir_lstclear(hdoc, &free);
	redir_lstclear(redir, &free);
}

void free_struct_array(t_cmd_args **arr)
{
	int	i;

	i = 0;
	while(arr[i] != 0)
	{
		list_free(arr[i]->head_hdocs, arr[i]->head_redir, arr[i]->args, 0);
		if (arr[i]->cmd != 0)
			free(arr[i]->cmd);
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = 0;
}

void	free_env_table(t_env **env_table)
{
	int	i;

	i = 0;
	while(i < TABLE_SIZE)
	{
		if (env_table[i] != NULL && env_table[i] != DELETED_NODE)
		{
			free(env_table[i]->name);
			free(env_table[i]->value);
			free(env_table[i]);
		}
		i++;
	}
}
