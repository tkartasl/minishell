/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:01 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/01 12:53:15 by tkartasl         ###   ########.fr       */
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
	ft_free_pointer_array(cmd_line);
	redir_lstclear(hdoc, &free);
	redir_lstclear(redir, &free);
	printf("Malloc failure");
}

void free_struct_array(t_cmd_args **arr)
{
	int	i;

	i = 0;
	while(arr[i] != 0)
	{
		list_build_error(arr[i]->head_hdocs, arr[i]->head_redir, arr[i]->args);
		free(arr[i]->cmd);
		i++;
	}
	free(arr);
	arr = 0;
}