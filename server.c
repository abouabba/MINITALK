/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:23 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/18 13:47:36 by abouabba         ###   ########.fr       */
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
		c |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID : ");
	ft_putnbr(getpid());
	write (1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		print_error("Error: sigaction failed!");
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
		print_error("Error: sigaction failed!");
	while (1)
		pause();
	return (0);
}
