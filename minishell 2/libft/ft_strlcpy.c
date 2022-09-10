/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:20:19 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/04 20:02:20 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && (i < dstsize - 1))
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
	
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(src);
// 	i = 0;
// 	if (dstsize == 0)
// 		return (len);
// 	while (src[i] && i < (dstsize - 1))
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (len);
// }

// #include<stdio.h>
// int main()
// {
// 	char a[]="hello world";
// 	char b[]="salut";
// 	printf("%zu\n", ft_strlcpy(a,b,13));
// }
