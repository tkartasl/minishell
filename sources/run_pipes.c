/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:30:04 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/22 15:54:43 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **split_path)
{
	char	*temp_path;
	char	*final_path;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0 && cmd[0] == '/')
		return (cmd);
	while (split_path[i] != 0)
	{
		temp_path = ft_strjoin(split_path[i], "/");
		if (temp_path == NULL)
			pipe_error(1, NULL, NULL);
		final_path = ft_strjoin(temp_path, cmd);
		if (final_path == NULL)
		{
			free(temp_path);
			pipe_error(1, NULL, NULL);
		}
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (cmd);
}

void	check_path(char *cmd_path)
{
	DIR	*dir;
	int	len;

	len = ft_strlen(cmd_path);
	if (ft_strnstr(cmd_path, "/.brew/bin/", ft_strlen(cmd_path)) != NULL)
		return ;
	dir = opendir(cmd_path);
	if (dir != NULL)
	{
		closedir(dir);
		file_error(2, cmd_path);
	}
	if (access(cmd_path, F_OK) == 0)
		if (access(cmd_path, X_OK) == -1)
			file_error(1, cmd_path);
	if (cmd_path[len - 1] == '/' && cmd_path[0] == '/')
		file_error(3, cmd_path);
}

void	run_cmd_pipe(char **cmd, char **envp, t_env **env_t, t_cmd_args *ca)
{
	char	**split_path;
	char	*cmd_path;
	char	*path;
	int		flag;

	flag = check_builtins(ca, env_t, 1, 0);
	if (flag == 1)
		exit (0);
	else if (flag == 0)
	{
		path = ft_get_env("PATH", env_t);
		if (path == NULL)
			pipe_error(5, cmd[0], NULL);
		split_path = ft_split(path, ':');
		if (split_path == NULL)
			pipe_error(1, NULL, NULL);
		cmd_path = find_path(cmd[0], split_path);
		if (ft_strncmp(cmd_path, "exit", 5) == 0)
			pipe_error(6, cmd_path, cmd);
		if (ft_strchr(cmd_path, '/') != NULL)
			check_path(cmd_path);
		ft_free_pointer_array(split_path);
		if (execve(cmd_path, cmd, envp) == -1)
			pipe_error_cmd(cmd[0], cmd);
	}
}

int	pipe_init(int flag, char **envp, t_cmd_args *cmd_arg, t_env **env_t)
{
	int		pid;
	int		pipe_fd[2];
	char	**cmd;

	cmd = get_cmd(cmd_arg);
	if (pipe(pipe_fd) == -1)
		flag = 3;
	pid = fork();
	if (pid == -1)
		flag = 4;
	if (check_flag(flag, cmd) == -1)
		return (-1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (flag == 1)
			dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		run_cmd_pipe(cmd, envp, env_t, cmd_arg);
	}
	free(cmd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	return (pid);
}

void	run_pipes(t_cmd_args **cmd_arg, int pc, char **en, t_env **et)
{
	int	i;
	int	fd1;
	int	fd2;
	int	rflag;
	int	*process_ids;

	if (init_pipe_vars(&i, &fd1, &process_ids, pc) == -1)
		return ;
	while (++i < pc)
	{
		close(fd2);
		fd2 = dup(1);
		rflag = 0;
		if (check_in_redir(cmd_arg[i]->head_redir, i, fd1) == -1)
			process_ids[i] = redir_fail();
		else if (check_out_redir(cmd_arg[i]->head_redir, i, fd2, &rflag) == -1)
			process_ids[i] = redir_fail();
		else if ((i + 1) == pc || rflag == 1)
			process_ids[i] = pipe_init(0, en, cmd_arg[i], et);
		else
			process_ids[i] = pipe_init(1, en, cmd_arg[i], et);
		if (rflag == 1)
			dup2(fd2, 1);
	}
	wait_children(process_ids, fd2, et);
}
