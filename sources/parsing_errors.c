/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:01 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/04 12:06:22 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char **cmd_line)
{
    ft_free_pointer_array(cmd_line);
    printf("minishell: syntax error near unexpected token\n");
}

void	list_build_error(t_redir **hdoc, t_redir **redir, char **cmd_line)
{
	if (cmd_line != 0)
		ft_free_pointer_array(cmd_line);
	redir_lstclear(hdoc, &free);
	redir_lstclear(redir, &free);
	//printf("Malloc failure\n");
}

void free_struct_array(t_cmd_args **arr)
{
	int	i;

	i = 0;
	while(arr[i] != 0)
	{
		list_build_error(arr[i]->head_hdocs, arr[i]->head_redir, arr[i]->args);
		if (arr[i]->cmd != 0)
			free(arr[i]->cmd);
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