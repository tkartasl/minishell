/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/04 10:57:55 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
char	*find_limiter(char *str)
{
    while (*str != 0)
    {   
		if (*str == '\'' || *str == '\"')
			str = skip_quotes(str, *str);
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
		if (*str == '\'' || *str == '\"')
			str = skip_quotes(str, *str);
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

