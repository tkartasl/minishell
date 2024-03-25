/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:25:50 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/25 15:01:07 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int remove_file_quotes(t_redir **redirs)
{
    t_redir *temp;

    temp = *redirs;
    while(temp)
    {
        temp->filename = clean_arg(temp->filename);
        if (temp->filename == NULL)
            return (-1);
        temp = temp->next;
    }
    return (0);
}

void    run_commands(t_cmd_args **cmd_args, int pipe_count, t_env **env_table)
{
    int         original_stdin;
    int         original_stdout;
    char        **envp;

    envp = get_env_list(env_table);
    if (envp == NULL)
    {
        printf("minishell: error allocating memory\n");
        return ;
    }
    original_stdin = dup(0);
    original_stdout = dup(1);
    run_pipes(cmd_args, pipe_count, envp, env_table);
    dup2(original_stdin, 0);
    dup2(original_stdout, 1);
    ft_free_pointer_array(envp);
    if (access("here_doc", F_OK) == 0)
        unlink("./here_doc");
}
