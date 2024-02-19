/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:38:23 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/19 12:41:55 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NAME_MAX 255
# define PATH_MAX 1024
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_redir
{
	char	*arrow;
	char	*filename;
	int		index;
	t_redir	*next;
}				t_redir;

typedef struct s_heredoc
{
	char		*filename;
	int			index;
	t_heredoc	*next;
}				t_heredoc;

typedef struct s_cmd_args
{
	t_heredoc	*head;
	t_redir		*head;
	char		*cmd;
	char		**args;	
}				t_cmd_args;

#endif