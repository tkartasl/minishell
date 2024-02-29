/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:17 by vsavolai         ###   ########.fr       */
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
        str++;
    }
    return (str);
}

char    *find_redir(char *str)
{
    while (*str != 0)
    {
		if (*str == '<' && *(str + 1) == '<')
			str = str + 2;
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
		str++;
    }
    return (str);
}

