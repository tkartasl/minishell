/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:37 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/03 16:27:44 by vsavolai         ###   ########.fr       */
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

int check_exit(char *line)
{
    if (ft_strncmp(line, "exit", 5) == 0)
    {
        free(line);
        printf("exit\n");
        return (0);
    }
    else if (ft_strncmp(line, "zsh", 4) == 0)
    {
        free(line);
        return (0);
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	char				*line;
	
    argc = 0;
    argv[0] = "avc";

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
        if (check_exit(line) == 0)
            break;
		parse_line(line, envp);
		free(line);
	}
	return (0);
}
