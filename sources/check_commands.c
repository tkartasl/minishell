/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/12 11:25:23 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_cmd_args *cmd_args, t_env **env_table, int call, int flag)
{
	if (call == 0 && cmd_args->head_hdocs[0] != 0)
	{
		char	*filename;

		flag = check_h_docs(cmd_args->head_hdocs[0], 0, &filename);
		if (flag > 0)
			close(flag);
	}
	if (call == 0 && ft_strncmp(cmd_args->cmd, "echo", 5) == 0)
		if (cmd_args->head_redir[0] != NULL)
			return (0);
	if (ft_strncmp(cmd_args->cmd, "export", 7) == 0)
		export(cmd_args, env_table, &flag, -1);
	else if (ft_strncmp(cmd_args->cmd, "pwd", 4) == 0)
		pwd(&flag, env_table);
	else if (ft_strncmp(cmd_args->cmd, "echo", 5) == 0)
		echo(cmd_args->args, 1, &flag, env_table);
	else if (ft_strncmp(cmd_args->cmd, "unset", 6) == 0)
		unset(cmd_args, env_table, &flag);
	else if (ft_strncmp(cmd_args->cmd, "env", 4) == 0)
		env(env_table, &flag);
	else if (ft_strncmp(cmd_args->cmd, "cd", 3) == 0)
		cd(cmd_args, env_table, &flag);
	return (flag);
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

void	close_original_fds(t_cmd_args **cmd_args)
{
	if (cmd_args[0]->head_redir[0] != NULL)
		close(cmd_args[0]->head_redir[0]->original_input);
	if (cmd_args[0]->head_redir[0] != NULL)
		close(cmd_args[0]->head_redir[0]->original_output);
	if (cmd_args[0]->head_hdocs[0] != NULL)
		close(cmd_args[0]->head_hdocs[0]->original_input);
	if (cmd_args[0]->head_hdocs[0] != NULL)
		close(cmd_args[0]->head_hdocs[0]->original_output);
}

void	check_cmds(t_cmd_args **cmd_args, t_env **env_table)
{
	int	flag;
	int	fd1;
	int	fd2;

	fd1 = dup(0);
	fd2 = dup(1);
	flag = check_cmd_syntax(cmd_args, env_table);
	if (flag < 0)
	{
		print_error(cmd_args, flag);
		return ;
	}
	if ((*cmd_args)->pipe_count == 1)
		flag = check_builtins(cmd_args[0], env_table, 0, 0);
	dup2(fd1, 0);
	dup2(fd2, 1);
	close(fd1);
	close(fd2);
	if (flag == 0)
		run_commands(cmd_args, (*cmd_args)->pipe_count, env_table);
	close_original_fds(cmd_args);
	free_struct_array(cmd_args);
}
