/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:30:04 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/27 08:45:19 by vsavolai         ###   ########.fr       */
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
    while(split_path[i] != 0)
    {
        temp_path = ft_strjoin(split_path[i], "/");
        final_path = ft_strjoin(temp_path, cmd);
        free(temp_path);
        if (access(final_path, F_OK | X_OK) == 0)
            return (final_path);
        free(final_path);
        i++;
    }
    return (cmd);
}

void    run_cmd_pipe(char **cmd, char **envp, t_env **env_table)
{
    char    **split_path;
    char    *cmd_path;
    char    *path;

    path = ft_get_env("PATH", env_table);
    split_path = ft_split(path, ':');
    cmd_path = find_path(cmd[0], split_path);
    ft_free_pointer_array(split_path);
    if (execve(cmd_path, cmd, envp) == -1)
    {
        write(2, "wrong command\n", 14);
        //printf("minishell: command not found: %s\n", cmd[0]);
        exit(1);
    }
}

void    pipe_init(char **cmd, char **envp, int flag, t_env **env_table)
{
    pid_t   pid;
    int     pipe_fd[2];

    if(pipe(pipe_fd) == -1)
    {
        printf("minishell: pipe failure\n");
        return ;
    }  
    pid = fork();
	if (pid == -1)
    {
        printf("minishell: fork failure\n");
        return ;
    }
    if (pid == 0)
	{
        close(pipe_fd[0]);
        if (flag == 1)
		    dup2(pipe_fd[1], 1);
		run_cmd_pipe(cmd, envp, env_table);
	}
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
    }
    waitpid(pid, NULL, 0);
}

void    run_pipes(t_cmd_args **cmd_arg, int pipe_count, char **en, t_env **et)
{
    int         i;
    int         fd1;
    int         fd2;
    char        **cmd;
    
    i = 0;
    fd1 = 0;
    fd2 = 0;
    while(i < pipe_count)
    {
        check_in_redir(cmd_arg[i]->head_redir, i, fd1);
        check_out_redir(cmd_arg[i]->head_redir, i, fd2);
        cmd = get_cmd(cmd_arg[i]);
        if ((i + 1) == pipe_count)
            pipe_init(cmd, en, 0, et);
        else
            pipe_init(cmd, en, 1, et);
        free(cmd);
        i++;
    }
}
