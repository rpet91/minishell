/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 09:19:48 by rpet          #+#    #+#                 */
/*   Updated: 2020/08/20 10:58:20 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		Looks for a metachar.
*/

int		check_metachar(char *line)
{
	if (*line == '>' && *line + 1 == '>')
		return (1);
	if (ft_strchr(";|><", *line))
		return (1);
	return (0);
}

/*
**		Adds a token to the list.
*/

int		add_token_to_list(t_lexer *lexer, t_list **list)
{
	char	*token;
	t_list	*element;

	token = ft_substr(lexer->token_str, 0, lexer->token_len);
	if (!token)
		return (0);
	element = ft_lstnew(token);
	if (!element)
	{
		free(token);
		return (0);
	}
	ft_lstadd_back(list, element);
	return (1);
}

/*
**		Checks where to split for tokens.
*/

int		lexer_loop(char *line, t_lexer *lexer, t_list **list)
{
	if (*line == '\'' && lexer->quote != DOUBLE_QUOTE)
		found_single_quote(line, lexer);
	if (*line == '\"' && lexer->quote != SINGLE_QUOTE)
		found_double_quote(line, lexer);
	if (lexer->token == NOT_ACTIVE)
		outside_token(line, lexer);
	else if (lexer->token == ACTIVE && lexer->quote == NO_QUOTE)
	{
		if (!in_active_token(line, lexer, list))
			return (0);
	}
	else if (lexer->token == METACHAR && lexer->quote == NO_QUOTE)
	{
		if (!in_metachar_token(line, lexer, list))
			return (0);
	}
	if (lexer->token != NOT_ACTIVE)
		lexer->token_len++;
	return (1);
}

/*
**		Initializes the lexer.
*/

void	init_lexer(t_lexer *lexer)
{
	lexer->token_len = 0;
	lexer->token_str = NULL;
	lexer->quote = NO_QUOTE;
	lexer->token = NOT_ACTIVE;
}

/*
**		Calls the loop for the lexer.
*/

t_list	*lexer_line(char *line)
{
	t_lexer		lexer;
	t_list		*list;

	init_lexer(&lexer);
	list = NULL;
	while (*line)
	{
		if (!lexer_loop(line, &lexer, &list))
			return (NULL);
		line++;
	}
	if (lexer.token != NOT_ACTIVE && !add_token_to_list(&lexer, &list))
		return (NULL);
	return (list);
}
