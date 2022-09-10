/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:15:38 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 01:28:50 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

// #include <stdio.h>
// int main()
// {
// 	char a[] = "oumaimato";
// 	printf("%s\n",ft_strrchr("oumaimato",'m'));
// 	printf("%s",strrchr("oumaimato",'m'));
// }
