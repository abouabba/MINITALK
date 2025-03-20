/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:42:10 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/20 21:58:48 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void	ft_putnbr(int n)
{
	char	*str;

	str = "0123456789";
	if (n > 9)
		ft_putnbr(n / 10);
	write (1, &str[n % 10], 1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n > 2147483647)
			return (-1);
		i++;
	}
	if (n >= 1)
		return (n);
	return (-1);
}

int	print_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
	exit(1);
}
