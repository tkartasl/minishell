/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:25:50 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/15 15:37:07 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd(t_cmd_args *cmd_args)
{
	int		i;
	int		j;
	char	**cmd;

	i = 1;
	j = 0;
	while (cmd_args->args[j] != 0)
	{
		i++;
		j++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (cmd == NULL)
	{
		ft_putstr_fd("minishell: error allocating memory\n", 2);
		return (NULL);
	}
	cmd[0] = cmd_args->cmd;
	i = 1;
	j = 0;
	while (cmd_args->args[j] != 0)
		cmd[i++] = cmd_args->args[j++];
	cmd[i] = 0;
	return (cmd);
}

void	close_fds_parent(int *pipe_fd, t_env **env_t, int flag)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	change_cmd_status(env_t, flag);
}

int	remove_file_quotes(t_redir **redirs)
{
	t_redir	*temp;

	temp = *redirs;
	while (temp)
	{
		temp->filename = clean_arg(temp->filename);
		if (temp->filename == NULL)
			return (-1);
		temp = temp->next;
	}
	return (0);
}

void	run_commands(t_cmd_args **cmd_args, int pipe_count, t_env **env_t)
{
	int		original_stdin;
	int		original_stdout;
	char	**envp;

	envp = get_env_list(env_t);
	if (envp == NULL)
	{
		ft_putstr_fd("minishell: error allocating memory\n", 2);
		return ;
	}
	original_stdin = dup(0);
	original_stdout = dup(1);
	run_pipes(cmd_args, pipe_count, envp, env_t);
	dup2(original_stdin, 0);
	dup2(original_stdout, 1);
	close(original_stdin);
	close(original_stdout);
	ft_free_pointer_array(envp);
}
