/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:33:51 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/23 18:28:44 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftplus.h"

char	*my_strjoin(char*s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	len = ft_strlen((char *) s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (dest);
}

// #include<stdio.h>
// int main()
// {
// 	printf("%s\n", ft_strjoin("hello","world"));
// }