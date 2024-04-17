/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:30:07 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/15 10:31:12 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_lstclear(t_redir **lst, void (*del)(void *))
{
	t_redir	*temp;
	t_redir	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	temp = NULL;
	while (current != 0)
	{
		temp = current->next;
		del(current->filename);
		free(current);
		current = temp;
	}
	*lst = NULL;
}

void	redir_lstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;
	t_redir	*last;

	last = NULL;
	if (!lst || !new)
		return ;
	if ((*lst) == 0)
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current != 0)
	{
		last = current;
		current = current->next;
	}
	last->next = new;
}

t_redir	*redir_lstnew(char *filename, char redir, int index)
{
	t_redir	*new;

	new = NULL;
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == 0)
		return (0);
	new->filename = filename;
	new->arrow = redir;
	new->index = index;
	new->flag = 0;
	new->fd = 0;
	new->next = NULL;
	new->original_input = dup(0);
	new->original_output = dup(1);
	return (new);
}

int	build_list(t_redir **head, char *lim, int index)
{
	t_redir	*new;

	new = redir_lstnew(lim, 0, index);
	if (new == 0)
		return (-1);
	redir_lstadd_back(head, new);
	return (0);
}
