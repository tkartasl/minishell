/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:30:04 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/12 13:43:25 by vsavolai         ###   ########.fr       */
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
    if (cmd == NULL)
    {
        printf("minishell: error allocating memory\n");
        return (NULL);
    }
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

void    check_path(char *cmd_path)
{
    DIR *dir;
    int len;

    len = ft_strlen(cmd_path);
    if (ft_strnstr(cmd_path, "/.brew/bin/", ft_strlen(cmd_path)) != NULL)
        pipe_error(2, NULL, NULL);
    dir = opendir(cmd_path);
    if (dir != NULL)
    {
        closedir(dir);
        file_error(2, cmd_path);	
    }
    if (cmd_path[len - 1] == '/' && cmd_path[0] == '/')
        file_error(3, cmd_path);
    if (ft_strnstr(cmd_path, "/bin", len) != NULL)
        if (access(cmd_path, X_OK) == -1)
            file_error(1, cmd_path);
}

void    run_cmd_pipe(char **cmd, char **envp, t_env **env_t, t_cmd_args *ca)
{
    char    **split_path;
    char    *cmd_path;
    char    *path;
    int     flag;
    
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
        if (ft_strchr(cmd_path, '/') != NULL)
            check_path(cmd_path);
        ft_free_pointer_array(split_path);
        if (execve(cmd_path, cmd, envp) == -1)
            pipe_error_cmd(cmd[0], cmd);
    }
}

void pipe_init(int flag, char **envp, t_cmd_args *cmd_arg, t_env **env_t)
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
    if (check_flag(flag, cmd) == -1)
        return ;
    if (pid == 0)
	{
        close(pipe_fd[0]);
        if (flag == 1)
		    dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
		run_cmd_pipe(cmd, envp, env_t, cmd_arg);
	}
        waitpid(pid, &flag, 0);
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);
        change_cmd_status(env_t, flag);
}

void    run_pipes(t_cmd_args **cmd_arg, int pipe_count, char **en, t_env **et)
{
    int         i;
    int         fd1;
    int         fd2;
    int         redir_flag;
    
    i = -1;
    fd1 = 0;
    while(++i < pipe_count)
    {
        close(fd2);
        fd2 = dup(1);
        redir_flag = 0;
        if (check_in_redir(cmd_arg[i]->head_redir, i, fd1) == -1)
            continue ;
        if (check_out_redir(cmd_arg[i]->head_redir, i, fd2, &redir_flag) == -1)
            continue ;
        if ((i + 1) == pipe_count || redir_flag == 1)
            pipe_init(0, en, cmd_arg[i], et);
        else
            pipe_init(1, en, cmd_arg[i], et);
        if (redir_flag == 1)    
            dup2(fd2, 1);
    }
    close(fd2);

}
