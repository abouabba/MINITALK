/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:42:22 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/20 17:05:05 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	static int				bit;
	static unsigned char	c;
	static int				pid;

	(void)context;
	if (pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		bit = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
		print_error("Usage: ./server\n");
	ft_putstr("Server PID : ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		print_error("Error: sigaction failed!");
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
		print_error("Error: sigaction failed!");
	while (1)
		pause();
	return (0);
}
