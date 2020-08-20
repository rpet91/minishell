/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/20 13:46:33 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	is_builtin(t_command *command, t_vars *vars, int i)
{
	(void)i;
	if (!command->args[0])
		command->err = ERROR;
	else if (ft_strncmp(command->args[0], "echo", ft_strlen("echo")) == 0)
		vars->ret = (echo_func(command)); // all deze funcites 0 laten returen als het goed gaat
	// else if (ft_strncmp(command->args[0], "cd", ft_strlen("cd")) == 0)
	// 	vars->ret = (cd_func(command));
	// else if (ft_strncmp(command->args[0], "pwd", ft_strlen("pwd")) == 0)
	// 	vars->ret = (pwd_func(command));
	// else if (ft_strncmp(command->args[0], "export", ft_strlen("export")) == 0)
	// 	vars->ret = (export_func(command));
	// else if (ft_strncmp(command->args[0], "unset", ft_strlen("unset")) == 0)
	// 	vars->ret = (unset_func(command));
	// else if (ft_strncmp(command->args[0], "env", ft_strlen("env")) == 0)
	// 	vars->ret = (env_func(command));
	// else if (ft_strncmp(command->args[0], "exit", ft_strlen("exit")) == 0)
	// 	vars->ret = (exit_func(command));
	return (0);
}

void		kill_control_c(int signal)
{
	printf("signal: [%i]\n", signal);
}

void 		kill_control_slash()
{
	
}

int			main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_list		*list;
	t_list		*command_list;
	t_vars		vars;

	(void)argv;
	(void)argc;
	i = 1;
	init_envv(env, &vars);
	vars.ret = 0;
	while (i)
	{
		command_prompt();
		signal(SIGINT, kill_control_c); // deze zo afmaken
		//signal(SIGINT, kill_control_slash); // deze zo afmaken
		i = get_next_line(0, &line);
		if (i == -1)
			ft_error("Something went wrong reading the line\n");
		list = lexer_line(line);
		if (!list && *line && *line != ' ' && *line != '\t')
			str_error("Something went wrong during the lexer\n");
		if (!check_valid_meta(list))
		{
			ft_putstr_fd("Syntax error near unexpected token\n", 1);
			continue ;
		}
		print_list(list); //lijst na de lexer
		while (list)
		{
		//	printf("begin command: [%s]\n", list->content);
			expand_func(list, &vars);
		//	printf("test na expand\n");
			command_list = parse_line(&list);
			if (!command_list)
				break ;
		//	printf("test na parse line\n");
			iterate_command(command_list, env, &vars);
			if (((t_command*)command_list->content)->err == ERROR)
				break ;
		//	printf("test na iterate command\n");
		}
	}
	return (0);
}
