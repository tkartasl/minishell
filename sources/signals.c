/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:45:03 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/12 14:30:48 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler_heredoc(int signum)
{
	struct termios	raw;
	
	ft_memset(&raw, 0, sizeof(struct termios));
	if (signum == SIGTSTP)
	{
		tcgetattr(STDIN_FILENO, &raw);
		raw.c_lflag |= (ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
		exit(0);
	}
	if (signum == SIGINT)
		write(1, "\n", 1);
}

void sig_handler_before(int signum)
{
	struct termios	raw;
	
	ft_memset(&raw, 0, sizeof(struct termios));
	if (signum == SIGTSTP)
	{
		tcgetattr(STDIN_FILENO, &raw);
		raw.c_lflag |= (ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
		exit(0);
	}
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void sig_handler_after(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	if (signum == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	signals_before_rl(int flag)
{
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;

	ft_memset(&act_sigint, 0, sizeof(struct sigaction));
	ft_memset(&act_sigquit, 0, sizeof(struct sigaction));
	if (flag == 0)
		act_sigint.sa_handler = &sig_handler_before;
	else
		act_sigint.sa_handler = &sig_handler_heredoc;
	act_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act_sigquit, NULL) < 0)
		return ;
	if (sigaction(SIGINT, &act_sigint, NULL) < 0)
		return ;
	if (sigaction(SIGTSTP, &act_sigint, NULL) < 0)
		return ;
}

void	signals_after_rl(void)
{
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;

	ft_memset(&act_sigint, 0, sizeof(struct sigaction));
	ft_memset(&act_sigquit, 0, sizeof(struct sigaction));
	act_sigint.sa_handler = &sig_handler_after;
	act_sigquit.sa_handler = &sig_handler_after;
	if (sigaction(SIGQUIT, &act_sigquit, NULL) < 0)
		return ;
	if (sigaction(SIGINT, &act_sigint, NULL) < 0)
		return ;
}
