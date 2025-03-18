/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:49 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/18 18:04:24 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	validation_pid(char	*pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if ((pid[i] < '0') || (pid[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

void	send_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				print_error("Error in kill\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				print_error("Error in kill\n");
		}
		usleep(200);
		usleep(200);
		bit--;
	}
}
void	ack_handler(int sig)
{
	(void)sig;
}

int	get_utf8_size(unsigned char c)
{
	if ((c & 0x80) == 0)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (-1);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;
	unsigned char	*c;
	int	size;
	int	j;
	struct sigaction	sa;

	i = 0;
	if (ac != 3)
	{
		print_error("Usage: ./client [PID] [string]\n");
		return (1);
	}
	if (!validation_pid(av[1]))
	{
		print_error("Invalid PID\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid == -1 || pid == 0)
		print_error("Invalid PID!\n");
	sa.sa_flags = 0;
	sa.sa_handler = ack_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error("Error: sigaction failed!");
	i = 0;
	while (av[2][i])
	{
		c = (unsigned char *)&av[2][i];
		size = get_utf8_size(*c);
		if (size == -1)
			print_error("Invalid character\n");
		j = 0;
		while (j < size)
		{
			send_char(pid, c[j]);
			j++;
		}
		i += size;
	}
	send_char(pid, '\0');
	return (0);
}
