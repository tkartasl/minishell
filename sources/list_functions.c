#include "minishell.h"

void	ft_lstadd_back(t_redir **lst, t_redir *new)
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

t_redir	*ft_lstnew(void *content)
{
	t_redir	*new;

	new = NULL;
	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == 0)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
