/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/17 15:29:35 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_cmd_args *ca, t_env **et, int c, int flag)
{
	char	*filename;

	if (c == 0 && ca->head_hdocs[0] != 0 && ft_strncmp(ca->cmd, "cat", 5) != 0)
	{
		flag = check_h_docs(ca->head_hdocs[0], 0, &filename);
		if (flag > 0)
			close(flag);
	}
	if (c == 0 && ft_strncmp(ca->cmd, "echo", 5) == 0)
		if (ca->head_redir[0] != NULL)
			return (0);
	if (ft_strncmp(ca->cmd, "export", 7) == 0)
		export(ca, et, &flag, -1);
	else if (ft_strncmp(ca->cmd, "pwd", 4) == 0)
		pwd(&flag, et);
	else if (ft_strncmp(ca->cmd, "echo", 5) == 0)
		echo(ca->args, 1, &flag, et);
	else if (ft_strncmp(ca->cmd, "unset", 6) == 0)
		unset(ca, et, &flag);
	else if (ft_strncmp(ca->cmd, "env", 4) == 0)
		env(et, &flag);
	else if (ft_strncmp(ca->cmd, "cd", 3) == 0)
		cd(ca, et, &flag);
	return (flag);
}

int	find_correct_index(t_env **env)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (env[i] != NULL && env[i] != (t_env *)(DELETED_NODE))
			return (i);
		i++;
	}
	return (-1);
}

int	check_cmd_syntax(t_cmd_args **cmd_args, t_env **env_table)
{
	int	flag;

	flag = 0;
	if (get_envs(cmd_args, env_table, &flag) == 0)
	{
		if (flag == 1)
			return (-2);
		return (-1);
	}
	if (remove_cmd_quotes(cmd_args) == -1)
		return (-1);
	if (remove_arg_quotes(cmd_args) == -1)
		return (-1);
	if (remove_file_quotes((*cmd_args)->head_hdocs) == -1)
		return (-1);
	if (remove_file_quotes((*cmd_args)->head_redir) == -1)
		return (-1);
	return (0);
}

void	close_original_fds(t_cmd_args **cmd_args, int i)
{
	t_redir	*temp;

	while (cmd_args[i] != NULL)
	{
		temp = cmd_args[i]->head_redir[0];
		while (temp != NULL)
		{
			if ((temp)->original_input)
				close((temp)->original_input);
			if ((temp)->original_output)
				close((temp)->original_output);
			temp = temp->next;
		}
		temp = cmd_args[i]->head_hdocs[0];
		while (temp != NULL)
		{
			if ((temp)->original_input)
				close((temp)->original_input);
			if ((temp)->original_output)
				close((temp)->original_output);
			temp = temp->next;
		}
		i++;
	}
}

void	check_cmds(t_cmd_args **ca, t_env **env_table)
{
	int	flag;
	int	fd1;
	int	fd2;

	fd1 = dup(0);
	fd2 = dup(1);
	flag = check_cmd_syntax(ca, env_table);
	if (flag < 0)
	{
		print_error(ca, flag);
		return ;
	}
	if ((*ca)->pipe_count == 1 && (ft_strncmp((*ca)->cmd, "exit", 5) == 0))
		ft_exit(env_table, ca, flag);
	if ((*ca)->pipe_count == 1)
		flag = check_builtins(ca[0], env_table, 0, 0);
	dup2(fd1, 0);
	dup2(fd2, 1);
	close(fd1);
	close(fd2);
	if (flag == 0)
		run_commands(ca, (*ca)->pipe_count, env_table);
	close_original_fds(ca, 0);
	free_struct_array(ca);
}
