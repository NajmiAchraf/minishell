/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 22:55:47 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 01:19:59 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}
// #include <fcntl.h>
// int main()
// {
// 	int fd;
// 	fd = open("test.txt", O_CREAT | O_RDWR, 777);
// 	ft_putstr_fd("hello sunshine", fd);
// }