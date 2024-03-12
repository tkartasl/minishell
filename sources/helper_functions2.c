/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:39 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/12 10:35:37 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *skip_cmd(char *str)
{
    char    *temp;

    temp = str;
    while (*str != ' ' && *str != 0 && *str != '<' && *str != '>')
    {
        if (*str == '\'' || *str == '\"')
            str = skip_quotes(str, *str);
		if (*str == ' ' || *str == 0 || *str == '<' || *str == '>')
			return (str);
		str++;	
    }
    return (str);
}

char	*skip_quotes(char *str, char quote)
{
	char	*temp;

	str++;
	temp = str;
	while (*str != 0 && *str != quote)
		str++;
	if (*str == 0)
		return (temp);
	str++;
	return (str);
}

char    *skip_arg(char *str)
{
    if (*str == '\'' || *str == '"')
    {
        str = skip_quotes(str, *str);
        if (*(str + 1) != 0 || *(str + 1) != ' ')
        {
            while (*str != 0 && *str != ' ')
                str++;
        }  
        return (str);
    }
    else
    {
        while(*str != ' ' && *str != 0 && *str != '<' && *str != '>')
            str++;
        return (str);
    }
}

int get_arg_len(char *str)
{
    char    quote;
    int     len;

    quote = *str;
    len = 0;
    if (str[len] == '\'' || str[len] == '"')
    {
        len++;
        while(str[len] != quote && str[len] != 0)
            len++;
        if (str[len] == quote)
            len++;
        if (str[len] != 0 || str[len] != ' ')
        {
            while(str[len] != 0 && str[len] != ' ')
                len++;
        }    
        return (len);
    }
    else
    {
        while(str[len] != ' ' && str[len] != 0)
            len++;
        return (len);
    }
}