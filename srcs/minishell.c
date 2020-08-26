/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/26 13:45:20 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

int 	is_builtin(t_command *command, t_vars *vars, int i)
{
	(void)i;
	if (!command->args[0])
		command->err = ERROR;
	else if (ft_strcmp(command->args[0], "echo") == 0)
		vars->ret = (echo_func(command));
	// else if (ft_strcmp(command->args[0], "cd") == 0)
	// 	vars->ret = (cd_func(command));
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		vars->ret = (pwd_func(command));
	// else if (ft_strcmp(command->args[0], "export") == 0)
	// 	vars->ret = (export_func(command));
	// else if (ft_strcmp(command->args[0], "unset") == 0)
	// 	vars->ret = (unset_func(command));
	// else if (ft_strcmp(command->args[0], "env") == 0)
	// 	vars->ret = (env_func(command));
	else if (ft_strcmp(command->args[0], "exit") == 0)
	// 	vars->ret = (exit_func(command));
		exit(0); //hardcore shit zodat ik die terminal uit donder als ik dat wil
	/*else
	{
		ft_putstr_fd(command->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}*/
	return (0);
}

void		kill_ctrl_c(int signal)
{
	(void)signal;
	write(1, "\b\b  \n", 5);
	command_prompt();
}

void 		kill_ctrl_slash(int signal)
{
	(void)signal;
	write(1, "\b\b  \b\b", 6);
}

void		process_list(t_list *list, t_vars vars, char **env)
{
	t_list		*command_list;

	while (list)
	{
		printf("Command: [%s]\n", list->content);
		expand_func(list, &vars);
		command_list = parse_line(&list);
		printf("Cmd list: [%s]\n", command_list->content);
		if (!command_list)
			break ;
		iterate_command(command_list, env, &vars);
		if (((t_command*)command_list->content)->err == ERROR)
			break ;
	}
}

int			main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_list		*list;
	t_vars		vars;

	(void)argv;
	(void)argc;
	i = 1;
	init_envv(env, &vars);
	vars.ret = 0;
	while (i)
	{
		command_prompt();
		signal(SIGINT, kill_ctrl_c);
		signal(SIGQUIT, kill_ctrl_slash);
		if(!get_next_line(0, &line))
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		list = lexer_line(line);
		if (!list && *line && *line != ' ' && *line != '\t')
			str_error("Something went wrong during the lexer\n");
		if (!check_valid_meta(list))
		{
			ft_putstr_fd("Syntax error near unexpected token\n", 1);
			continue ;
		}
		print_list(list); //lijst na de lexer
		process_list(list, vars, env);
		free(line);
	}
	return (0);
}
