/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:29:04 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/06 10:22:22 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_of_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

// int	my_strlcpy(char *dst, char *src, int dstsize)
// {
	
// 	int	len;
// 	int	i;

// 	len = len_of_str(src);
// 	i = 0;
// 	if (!dst || !src)
// 		return (0);
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

// char	*ft_strdup(char	*s1)
// {
// 	char	*ptr;
// 	int		len;

// 	if (!s1)
// 		return (NULL);
// 	len = len_of_str(s1);
// 	ptr = (char *) malloc ((len + 1) * sizeof(char));
// 	if (!ptr)
// 		return (0);
// 	my_strlcpy(ptr, s1, len + 1);
// 	return (ptr);
// }

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		i;

	if (!s1)
		return (0);
	dup = malloc(sizeof(char) * (len_of_str(s1) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include<stdio.h>
// int main()
// {
// 	char s[] = "hello world";
// 	char *dup = ft_strdup(s);
// 	printf("%s\n", dup);
// }
