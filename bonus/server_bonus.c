/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:23 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/19 15:19:08 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	unicode_handler(unsigned char c)
{
	if (c < 0x80)
		return (1);
	else if ((c & 0xe0) == 0xc0)
		return (2);
	else if ((c & 0xf0) == 0xe0)
		return (3);
	else if ((c & 0xf8) == 0xf0)
		return (4);
	return (0);
}

int	check_bytes(int *counter, unsigned char *c, int pid, int *bit)
{
	static unsigned char unicode[8];
	static int	bytes_num;

	if (++(*counter) == 8)
	{
		if (*bit == 0)
			bytes_num = unicode_handler(*c);
		unicode[(*bit)++] = *c;
		if (--bytes_num == 0)
		{
			unicode[*bit] = '\0';
			ft_putstr((char *)unicode);
			*bit = 0;
		}
		if (*c == '\0')
		{
			kill(pid, SIGUSR1);
			ft_putstr("\n");
		}
		*counter = 0;
		*c = 0;
	}
	return (0);
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	static int				bit;
	static unsigned char	c;
	static int				pid;
	static int				counter;

	(void)context;
	if (pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		counter = 0;
		bit = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c |= (0x80 >> counter);
	check_bytes(&counter, &c, pid, &bit);
}

int	main(void)
{
	struct sigaction	sa;

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
