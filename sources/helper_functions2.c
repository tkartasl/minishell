/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:39 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/07 08:36:19 by tkartasl         ###   ########.fr       */
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

/*char	*skip_arg(char *str)
{
	while (*str != ' ' && *str != 0 && *str != '<' && *str != '>')
    {
        if (*str == '\'' || *str == '\"'))
		{
			while (*str == '\'' || *str == '\"')
				str++;
			
		}
			
	
}*/