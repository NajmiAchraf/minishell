/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 02:22:15 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/24 00:44:07 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word(char const *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c))
		{
			counter++;
			while (str[i] && str[i] != c)
				i++;
			while (str[i] && str[i] == c)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		size;
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	size = ft_word(s, c);
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	while (s[i] && j < size)
	{
		while (s[i] && s[i] == c)
			i++;
		index = i;
		while (s[i] != c && s[i])
		i++;
		split[j++] = ft_substr(s, index, i - index);
	}
	split[j] = NULL;
	return (split);
}
// #include<stdio.h>
// int main()
// {
// 	char  **split;
// 	split = ft_split(0,'\t');
// 	printf("%s\n", split[0]);
// }
