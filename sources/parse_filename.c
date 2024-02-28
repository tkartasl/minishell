/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/28 13:38:10 by tkartasl         ###   ########.fr       */
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
			if (*str == '|' || *str == '&' || *str == 0
				|| *str == '>' || *str == '<')
				printf("syntax error");
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
		if (*str == '<' && *(str + 1) == '>')
			printf("syntax error");
		if (*str == '>' && *(str + 1) == '<')
			printf("syntax error");
		if (*str == '<' && *(str + 1) == '<')
			str = str + 2;
		if (*str == '>' && *(str + 1) == '>')
        {
            str = str + 2;
            str = ft_skip_whitespace(str);
			check_syntax_error(str);
            return (str); 
        }
		else if (*str == '<' || *str == '>')
        {
            str = str + 1;
            str = ft_skip_whitespace(str);
			check_syntax_error(str);
            return (str); 
        }
		str++;
    }
    return (str);
}

