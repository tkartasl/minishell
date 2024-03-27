/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:36 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/26 12:11:02 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset()
{

	
}

void	env()
{

	
}

void	exit(char *status, t_env **env_table, t_cmd_args **cmd_args);
{
	char	*temp;
	int		i;

	i = 0;
	temp = status;
	while (*temp != 0 && ft_isdigit(*temp) == 1)
		temp++;
	if (*temp == 0)
		i = ft_atoi(status);
	

	exit(i);
}