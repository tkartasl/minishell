/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:30:04 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/03 10:56:46 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **get_cmd(t_cmd_args *cmd_args)
{
    int     i;
    int     j;
    char    **cmd;

    i = 1;
    j = 0;
    while(cmd_args->args[j] != 0)
    {
        i++;
        j++;
    }
    cmd = malloc(sizeof(char *) * (i + 1));
    cmd[0] = cmd_args->cmd;
    i = 1;
    j = 0;
    while(cmd_args->args[j] != 0)
        cmd[i++] = cmd_args->args[j++];
    cmd[i] = 0;
    return (cmd);
}

char    *find_path(char *cmd, char **split_path)
{

    char    *temp_path;
    char    *final_path;
    int     i;

    i = 0;
    if (access(cmd, 0) == 0 && cmd[0] == '/')
		return (cmd);
    while(split_path[i] != 0)
    {
        temp_path = ft_strjoin(split_path[i], "/");
        if (temp_path == NULL)
            pipe_error(1, NULL);
        final_path = ft_strjoin(temp_path, cmd);
        if (final_path == NULL)
        {
            free(temp_path);
            pipe_error(1, NULL);
        }
        if (access(final_path, F_OK | X_OK) == 0)
            return (final_path);
        free(final_path);
        i++;
    }
    return (cmd);
}

void    run_cmd_pipe(char **cmd, char **envp, t_env **env_t, t_cmd_args *ca)
{
    char    **split_path;
    char    *cmd_path;
    char    *path;
    int     flag;
    
    flag = check_builtins(ca, env_t, 1);
    if (flag == 1)
        exit (0);
    else if (flag == 0)
    {
        path = ft_get_env("PATH", env_t);
        if (path == NULL)
            pipe_error(5, cmd[0]);
        split_path = ft_split(path, ':');
        if (split_path == NULL)
            pipe_error(1, NULL);
        cmd_path = find_path(cmd[0], split_path);
        ft_free_pointer_array(split_path);
        if (execve(cmd_path, cmd, envp) == -1)
            pipe_error(2, cmd[0]);
    }
}

void    pipe_init(int flag, char **envp, t_cmd_args *cmd_arg, t_env **env_table)
{
    pid_t   pid;
    int     pipe_fd[2];
    char    **cmd;
    
    cmd = get_cmd(cmd_arg);
    if(pipe(pipe_fd) == -1)
        flag = 3;
    pid = fork();
	if (pid == -1)
        flag = 4;
    if (flag == 3 || flag == 4)
    {
        pipe_error(flag, NULL);
        return ;
    }
    if (pid == 0)
	{
        close(pipe_fd[0]);
        if (flag == 1)
		    dup2(pipe_fd[1], 1);
		run_cmd_pipe(cmd, envp, env_table, cmd_arg);
	}
        waitpid(pid, NULL, 0);
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
}

void    run_pipes(t_cmd_args **cmd_arg, int pipe_count, char **en, t_env **et)
{
    int         i;
    int         fd1;
    int         fd2;
    char        **cmd;
    int         redir_flag;
    
    i = 0;
    fd1 = 0;
    while(i < pipe_count)
    {
        fd2 = dup(1);
        redir_flag = 0;
        check_in_redir(cmd_arg[i]->head_redir, i, fd1);
        check_out_redir(cmd_arg[i]->head_redir, i, fd2, &redir_flag);
        cmd = get_cmd(cmd_arg[i]);
        if ((i + 1) == pipe_count || redir_flag == 1)
            pipe_init(0, en, cmd_arg[i], et);
        else
            pipe_init(1, en, cmd_arg[i], et);
        free(cmd);
        if (redir_flag == 1)
            dup2(fd2, 1);
        i++;
    }
}
