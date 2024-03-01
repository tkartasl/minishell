/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:37 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/01 08:46:53 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_signum;

#include "minishell.h"

void sig_handler(int signum)
{
	if (signum == SIGINT)
	g_signum = signum;
	rl_on_new_line();
	if (signum == SIGQUIT)
		return ;
}

int main()
{
	struct sigaction	act;
	char				*line;
	
	line = 0;
	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = &sig_handler;
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		exit(1);
	if (sigaction(SIGINT, &act, NULL) < 0)
		exit(1);
	while (1)
	{
		line = readline("minishell >: ");
		if (line != 0 && *line != 0)
			add_history(line);
		parse_line(line);
		free(line);
	}
	return (0);
}
