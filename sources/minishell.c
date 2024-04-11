/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:37 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/10 14:30:27 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	termios_before_rl(void)
{
	struct termios	raw;

	ft_memset(&raw, 0, sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, &raw) < 0)
		return (-1);
	raw.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0)
		return (-1);
	return (0);
}

int	termios_after_rl(void)
{
	struct termios	raw;

	ft_memset(&raw, 0, sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, &raw) < 0)
		return (-1);
	raw.c_lflag |= (ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0)
		return (-1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char				*line;
	t_env               *env_table[TABLE_SIZE];
	
    (void)argc;
    (void)argv;
	line = 0;
	rl_clear_history();
	if (create_envs(envp, env_table) == -1)
        return (-1);
	while (1)
	{
		if (termios_before_rl() < 0)
			ft_printf("tcgetattr or tcsetattr function failed\n");
		signals_before_rl(0);
		line = readline("minishell >: ");
		if (line != 0 && *line != 0)
			add_history(line);
		if (termios_after_rl() < 0)
			ft_printf("tcgetattr or tcsetattr function failed\n");
		if (line == 0)
			break;
		signals_after_rl();
		parse_line(line, env_table);
		free(line);
	}
	free_env_table(env_table);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
