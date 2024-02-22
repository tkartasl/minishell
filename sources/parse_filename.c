/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/22 12:21:27 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (*str != 0)
            str++;
    }
    return (str);
}

char	*find_redir(char *str)
{
    while (*str != 0)
    {    
       if (*str == '>' && *(str + 1) == '>')
		{
			str = str + 2;
            str = ft_skip_whitespace(str);
				return (str); 
		}
	   else if (*str == '<' || *str == '>')
        {    
            str = str + 1;
            str = ft_skip_whitespace(str);
				return (str); 
        }
		
        if (*str != 0)
            str++;
    }
    return (str);
}

int	get_len(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != 0)
		i++;
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