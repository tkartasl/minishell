/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:30:04 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/18 13:48:23 by vsavolai         ###   ########.fr       */
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

void    run_cmd_pipe(char **cmd, char **envp)
{
    char    **split_path;
    char    *cmd_path;
    char    *path;

    path = ft_strdup(getenv("PATH"));
    split_path = ft_split(path, ':');
    cmd_path = find_path(cmd[0], split_path);
    ft_free_pointer_array(split_path);
    
    if (execve(cmd_path, cmd, envp) == -1)
    {
        printf("minishell: command not found: %s\n", cmd[0]);
        exit(1);
    }
    
}

void    pipe_init(char **cmd, char **envp, int flag)
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
		run_cmd_pipe(cmd, envp);
	}
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
    }
    waitpid(pid, NULL, 0);
}

void    run_pipes(t_cmd_args **cmd_args, int pipe_count, char **envp)
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
        check_in_redir(cmd_args[i]->head_redir, i, fd1);
        check_out_redir(cmd_args[i]->head_redir, i, fd2);
        cmd = get_cmd(cmd_args[i]);
        if ((i + 1) == pipe_count)
            pipe_init(cmd, envp, 0);
        else
            pipe_init(cmd, envp, 1);
        free(cmd);
        i++;
    }
}
