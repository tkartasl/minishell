/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:32:19 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/22 12:06:28 by vsavolai         ###   ########.fr       */
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

int	init_pipe_vars(int *i, int *fd1, int **process_ids, int pc)
{
	*process_ids = ft_calloc(pc + 1, sizeof(int));
	if (process_ids == NULL)
		return (-1);
	*i = -1;
	*fd1 = 0;
	return (0);
}

void	wait_children(int *process_ids, int fd2, t_env **et)
{
	int	i;
	int	status;

	i = 0;
	while (process_ids[i])
	{
		waitpid(process_ids[i], &status, 0);
		i++;
	}
	free(process_ids);
	if (ft_get_env("PATH", et) == NULL)
		change_cmd_status(et, 32512);
	else
		change_cmd_status(et, status);
	close(fd2);
}

void	null_cmd_hdoc(t_cmd_args *ca, int *flag)
{
	char	*filename;
	t_redir	*temp;

	temp = *ca->head_hdocs;
	while (temp)
	{
		*flag = check_h_docs(temp, 0, &filename);
		if (flag > 0)
			close(*flag);
		temp = temp->next;
	}
}

int	redir_fail(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		pipe_error(4, NULL, NULL);
		return (-1);
	}
	if (pid == 0)
		exit(1);
	return (pid);
}
