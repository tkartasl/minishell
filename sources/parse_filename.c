/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/18 14:16:07 by tkartasl         ###   ########.fr       */
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
		if ((*str == '>' && *(str + 1) == '>') ||
            (*str == '<' && *(str + 1) == '<'))
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

char	*check_if_digit(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	while (str[i] != 0 && str[i] != '<' && str[i] != '>' && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '<' || str[i] == '>')
	{
		temp = ft_strndup(str, i);
		if (temp == 0)
			return (0);

		return (&str[i]);
	}
	else
		return (str);
}
