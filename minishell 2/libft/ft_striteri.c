/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:57:29 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:52:22 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// void	ft_test(unsigned int i, char *s)
// {
// 	*s = *s + i;
// }
// #include <stdio.h>
// int main()
// {
// 	char b[] = "hello sunshine";
// 	printf("%s\n", b); 
// 	ft_striteri(b, &ft_test);
// }
