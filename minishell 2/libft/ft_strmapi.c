/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:08:12 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/02 21:20:46 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	mapi = (char *)malloc(sizeof(char ) * ft_strlen(s) + 1);
	if (!mapi)
		return (NULL);
	while (i < ft_strlen(s))
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}

// char	ft_test(unsigned int i, char s)
// {
// 	return (s + i);
// }

// #include<stdio.h>
// int main()
// {
//     char	s[] = "hello";
// 	   char	*b;
// 	   b = ft_strmapi(s, &ft_test);
//     printf("%s\n", b);
// }
