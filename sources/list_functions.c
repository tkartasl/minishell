#include "minishell.h"

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
	new->next = NULL;
	return (new);
}

void	build_list(t_redir **heredocs, char *lim, int index)
{
	t_redir	*new;

	new = redir_lstnew(lim, 0, index);
	if (new == 0)
		printf("Error\n");
	redir_lstadd_back(heredocs, new);
}