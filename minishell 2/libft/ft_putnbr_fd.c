/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 23:28:20 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/20 13:07:13 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	while (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0 && nb != -2147483648)
	{
		ft_putchar_fd(('-'), fd);
		nb = -1 * nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((nb + '0'), fd);
}
// #include <stdio.h>
// int main()
// {
// 	int a = 4525545;
// 	int fd = creat("test.txt", 0644);
// 	printf("%d\n", ft_putnbr_fd(a,fd));
// }
