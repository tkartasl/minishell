/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:37 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/18 15:26:28 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_table(t_env **env_table)
{
	t_env	*env;
	char	*value;
	char	*old_pwd;

	value = (char *)malloc(256);
	if (getcwd(value, 256) == NULL)
	{
		ft_putstr_fd("minishell: getcwd: path not found\n", 2);
		return (-1);
	}
	env = search_table("PWD", env_table);
	old_pwd = ft_strdup(env->value);
	if (old_pwd == NULL)
	{
		ft_putstr_fd("minishell: error allocating memory\n", 2);
		return (-1);
	}
	free(env->value);
	env->value = value;
	env = search_table("OLDPWD", env_table);
	free(env->value);
	env->value = old_pwd;
	return (1);
}

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

static int	termios_after_rl(void)
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

static void	parse_line(char	*line, t_env **env_table)
{
	char		**cmd_lines;
	int			pipe_count;
	t_redir		*heredocs;
	t_redir		*redirs;
	t_cmd_args	**cmd_args;

	heredocs = 0;
	redirs = 0;
	cmd_lines = split_line(line, env_table, &heredocs, &redirs);
	if (cmd_lines == 0)
		return ;
	pipe_count = get_pipe_count(cmd_lines);
	cmd_args = get_array(&redirs, &heredocs, cmd_lines, pipe_count);
	if (cmd_args == 0)
		return ;
	check_cmds(cmd_args, env_table);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_table[TABLE_SIZE];

	(void)argc;
	(void)argv;
	rl_clear_history();
	if (create_envs(envp, env_table) == -1)
		return (-1);
	while (1)
	{
		termios_before_rl();
		signals_before_rl(0);
		line = readline("minishell >: ");
		if (line != 0 && *line != 0)
			add_history(line);
		termios_after_rl();
		if (line == 0)
			break ;
		signals_after_rl();
		parse_line(line, env_table);
		free(line);
	}
	free_env_table(env_table);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
