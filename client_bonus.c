/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:49 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/20 01:30:49 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	g_pid;

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

void	connection(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1 && info->si_pid == g_pid)
		ft_putstr("Done , all bytes received successfully");
}

int	main(int ac, char **av)
{
	int					i;
	struct sigaction	client;

	if (ac != 3)
		print_error("Usage: ./client [PID] [string]\n");
	if (!validation_pid(av[1]))
		print_error("Invalid PID\n");
	g_pid = ft_atoi(av[1]);
	if (g_pid == -1 || g_pid == 0)
		print_error("Invalid PID!\n");
	client.sa_sigaction = connection;
	client.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR2, &client, 0) == -1)
		print_error("sigaction filed");
	if (sigaction(SIGUSR1, &client, 0) == -1)
		print_error("sigaction filed");
	i = 0;
	while (av[2][i])
	{
		send_char(g_pid, av[2][i]);
		i++;
	}
	send_char(g_pid, '\0');
	return (0);
}
