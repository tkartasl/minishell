/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:14:19 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/03 14:23:36 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <termios.h>

# define NAME_MAX 255
# define PATH_MAX 1024
# define TABLE_SIZE 64
# define DELETED_NODE (t_env *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct s_redir
{
	char			arrow;
	char			*filename;
	int				index;
	int				fd;
	int				flag;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd_args
{
	t_redir		**head_redir;
	t_redir		**head_hdocs;
	char		*cmd;
	char		**args;
	int			pipe_count;
}				t_cmd_args;

typedef struct s_env 
{
    char    *name;
    char    *value;
}			t_env;

void		parse_line(char	*line, t_env **env_table);
char    	*find_redir(char *str);
int			get_len(char *str);
char		*find_limiter(char *str);
int			build_list(t_redir **head, char *lim, int index);
t_cmd_args	**get_array(t_redir **redir, t_redir **hdoc, char **line, int pipe);
char		**parse_arguments(char *line, char *line2);
char		*skip_redirs(char *cmd_line);
void		syntax_error(char **cmd_line);
int			check_syntax(char **cmd_lines, int pipe_count);
void		list_build_error(t_redir **hdoc, t_redir **redir, char **cmd);
void		redir_lstclear(t_redir **lst, void (*del)(void *));
void		free_struct_array(t_cmd_args **arr);
int			get_pipe_count(char **cmd_lines);
void        run_pipes(t_cmd_args **cmd_args, int pipe_count, char **envp, t_env **env_table);
int			get_cmd_len(char *str, char quote);
char		*skip_quotes(char *str, char quote);
char		**ft_split_remix(char *s, char c);
int         check_pipe_repetition(char *line);
void        run_commands(t_cmd_args **cmd_args, int pipe_count, t_env **env_table);
char		*skip_arg(char *str);
int         get_arg_len(char *str);
int         check_in_redir(t_redir **head_redir, int i, int fd1);
int         check_out_redir(t_redir **head_redir, int i, int fd2, int *fl);
char		*check_if_digit(char *str, t_redir **redir);
void		put_fd_lst(char *line, t_redir **new);
int			get_envs(t_cmd_args **cmd_arg, t_env **env_table);
char		*cpy_expanded(char *str, char *expanded_str, int *i, t_env **env);
char		*cpy_line(char *str, char *expanded_str, int *i, int *flag);
char		*cpy_quote_to_quote(char *str, char *expanded_str, int *i);
char		*cpy_double_quote(char **str, char *expanded_str);
int			split_cmd(t_cmd_args **cmd_arg, int i);
int			word_count(char *str);
int			count_env_variables(char *str);
int         create_envs(char **envp, t_env **env_table);
int         hash(char *name);
int         table_insert(t_env *env, t_env **env_table);
t_env       *search_table(char *name, t_env **env_t);
int         table_delete(char *name, t_env **env_table);
int         get_value(t_env *env, char *envp, t_env **env_table);
char        **get_env_list(t_env **env_table);
char        *ft_get_env(char *name, t_env **env_table);
void        check_cmds(t_cmd_args **cmd_args, t_env **env_table);
int         remove_arg_quotes(t_cmd_args **cmd_args);
int         remove_cmd_quotes(t_cmd_args **cmd_args);
int         remove_file_quotes(t_redir **redirs);
char        *clean_arg(char *arg);
int         check_h_docs(t_redir *head_redir, int i, int fd1, char **filename);
void        free_env_table(t_env **env_table);
void        export(t_cmd_args *cmd_args, t_env **env_table, int *flag);
void        pwd(int *flag);
void        echo(char **args, int fd, int *flag);
void        unset(t_cmd_args *c_a, t_env **env_table, int *flag);
void        cd(t_cmd_args *cmd_args, t_env **env_table, int *flag);
void        env(t_env **env_table, int *flag);
void        export_env(t_env **env_table, int *flag);
void        pipe_error(int error_nbr, char *cmd);
int         check_builtins(t_cmd_args *cmd_args, t_env **env_table, int call);
void		signals_before_rl(void);
void		signals_after_rl(void);

#endif