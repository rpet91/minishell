/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_valid_meta.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 13:14:43 by rpet          #+#    #+#                 */
/*   Updated: 2020/08/13 13:42:11 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_valid_meta(t_list *list)
{
	while (list)
	{
		if (check_metachar(list->content))
		{
			if (ft_strlen(list->content) > 2)
				return (0);
		}
		list = list->next;
	}
	return (1);
}
