/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:37 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/12 12:27:52 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signum)
{
	
	if (signum == SIGINT)
	{	
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
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
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;
	char				*line;
	struct termios		raw;

    (void)argc;
    (void)argv;
	if (tcgetattr(STDIN_FILENO, &raw) < 0)
		return (0);
	raw.c_lflag = (ECHO);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0)
		return (0);
	line = 0; 
	ft_memset(&act_sigint, 0, sizeof(struct sigaction));
	ft_memset(&act_sigquit, 0, sizeof(struct sigaction));
	act_sigint.sa_handler = &sig_handler;
	act_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act_sigquit, NULL) < 0)
		exit(1);
	if (sigaction(SIGINT, &act_sigint, NULL) < 0)
		exit(1);
	while (1)
	{
		line = readline("minishell >: ");
		if (line != 0 && *line != 0)
			add_history(line);
		if (line == 0)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		parse_line(line, envp);
		free(line);
	}
		return (0);
}
