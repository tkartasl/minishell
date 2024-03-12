/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:39 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/12 09:47:02 by tkartasl         ###   ########.fr       */
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