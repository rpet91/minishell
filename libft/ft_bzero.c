/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:03:16 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/12 08:46:18 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = s;
	i = 0;
	while (n > i)
	{
		c[i] = 0;
		i++;
	}
}
