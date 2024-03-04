#include <stdio.h>
#include <stdlib.h>

typedef struct s_redir
{
	char			arrow;
	char			*filename;
	int				index;
	struct s_redir	*next;
}				t_redir;

void	ft_free(void *filename)
{
	free(filename);
}

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


char	*ft_strndup(const char *s1, int len)
{
	int		n;
	char	*p;

	n = 0;
	p = malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (n < len && s1[n] != 0)
	{
		p[n] = s1[n];
		n++;
	}
	p[n] = 0;
	return (p);
}

char	*ft_skip_whitespace(char *str)
{
	while (*str != 0 && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	return (str);
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

char	*find_limiter(char *str)
{
    while (*str != 0)
    {    
        if (*str == '<' && *(str + 1) == '<')
        {    
            str = str + 2;
            str = ft_skip_whitespace(str);
				return (str); 
        }
        str++;
    }
    return (str);
}

char    *find_redir(char *str)
{
    while (*str != 0)
    {
		if (*str == '<' && *(str +1) == '<')
			str = str + 2;
		if (*str == '>' && *(str + 1) == '>')
        {
            str = str + 2;
            str = ft_skip_whitespace(str);
			if (*str == '|' || *str == '&' || *str == 0)
				printf("syntax error");
            return (str); 
        }
		else if (*str == '<' || *str == '>')
        {
            str = str + 1;
            str = ft_skip_whitespace(str);
			if (*str == '|' || *str == '&' || *str == 0)
				printf("syntax error");
			return (str); 
        }
		str++;
    }
    return (str);
}

int	get_len_check_error(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != 0 && str[i] != '<' && str[i] != '>')
		i++;
	if (str[i] == '<' || str[i] == '>')
		printf("error");
	return (i);	
}

void	build_list(t_redir **heredocs, char *lim, int index)
{
	t_redir	*new;

	new = redir_lstnew(lim, 0, index);
	if (new == 0)
		printf("Error\n");
	redir_lstadd_back(heredocs, new);
}

void	get_redirs(t_redir **redirs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*file;
	char	*temp;

	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_redir(temp);
			if (*temp != 0)
			{
				len = get_len_check_error(temp);
				file = ft_strndup(temp, len);
				if (file == 0)
					printf("Error\n");
				build_list(redirs, file, i);
			}	
		}
		i++;
	}
}

void	get_heredocs(t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;
	char	*temp;

	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_limiter(temp);
			if (*temp != 0)
			{
				len = get_len_check_error(temp);
				lim = ft_strndup(temp, len);
				if (lim == 0)
					printf("Error\n");
				build_list(heredocs, lim, i);
			}	
		}
		i++;
	}
}

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int 		i;
    int 		j;
    t_redir    *new;

    new = *redirs;
    i =    0;
    while(i < 4)
    {
        j = 0;
        while(cmd_lines[i][j] != '\0')
        {
			if (cmd_lines[i][j] == '<' && cmd_lines[i][j +1] == '<')
				j = j + 2;
            if (cmd_lines[i][j] == '<')
			{
                new->arrow = '<';
                new = new->next;
            }
            else if (cmd_lines[i][j] == '>')
            {
                if (cmd_lines[i][j + 1] == '>')
                {
                    new->arrow = '!';
                    j++;
                }
                else
                    new->arrow = '>';
                new = new->next;
            }
            j++;
        }
        i++;
    }
}

int main()
{
	//char	*test[5]= {"<infile.txt grep moi", "wc -l>out,txt", "<<moi wc -w", "echo>outfile.txt", NULL};
	//t_redir	*heredocs;
	//t_redir *redirs;
	//t_redir *temp;
	ft_strndup(0, 0);
	//redirs = NULL;
	//heredocs = NULL;
	//get_heredocs(&redirs, test);
	//get_redirs(&redirs, test);
	//add_redirs(&redirs, test);
	//temp = redirs;
	//printf("%s\n", test[0]);
	/*while (heredocs != 0)
	{
		printf("%s\n", heredocs->filename);
		printf("%c\n", heredocs->arrow);
		printf("%i\n", heredocs->index);
		heredocs = heredocs->next;
	}
	printf("\n");*/
	//build_list(&redirs, "moi", 0);
	/*while (redirs != 0)
	{
		printf("%s\n", redirs->filename);
		printf("%c\n", redirs->arrow);
		printf("%i\n", redirs->index);
		printf("%p\n", redirs->next);
		redirs = redirs->next;
	}*/
	//redir_lstclear(&temp, &free);
	//printf("%p\n", redirs->filename);
	return (0);
}