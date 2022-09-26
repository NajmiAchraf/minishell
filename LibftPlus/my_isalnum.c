/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:11:05 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/25 22:26:53 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftplus.h"

int	my_isalnum(int c)
{
	if (!('0' <= c && c <= '9')
		&& !('A' <= c && c <= 'Z')
		&& !('a' <= c && c <= 'z')
		&& !('$' == c) && !('\'' == c) && !('\"' == c))
	{
		return (0);
	}
	return (1);
}
/*
int	main(void)
{
	int	a;

	a = 0;
	while (a <= 127)
	{
		printf("(%d) (%c)	ft_isalnum => %d	", a, a, ft_isalnum(a));
		printf("isalnum => %d\n", isalnum(a));
		a++;
	}
	return (0);
}
*/
