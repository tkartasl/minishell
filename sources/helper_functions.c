/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:16 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_len(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != 0 && str[i] != '<' && str[i] != '>')
		i++;
	return (i);	
}

char	*skip_redirs(char *cmd_line)
{
	if (*cmd_line == '>' && (*(cmd_line + 1) == '>'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' && (*(cmd_line + 1) == '<'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' || *cmd_line == '>')
		cmd_line++;
	cmd_line = ft_skip_whitespace(cmd_line);
	return (cmd_line);
}
