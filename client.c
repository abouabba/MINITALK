/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:42:48 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/20 09:42:49 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

	bit = 0;
	while (bit < 8)
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
		bit++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac != 3)
		print_error("Usage: ./client [PID] [string]\n");
	if (!validation_pid(av[1]))
		print_error("Invalid PID\n");
	pid = ft_atoi(av[1]);
	if (pid == -1 || pid == 0)
		print_error("Invalid PID!\n");
	while (av[2][i])
	{
		send_char(pid, av[2][i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
