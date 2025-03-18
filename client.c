/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:49 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/18 12:58:36 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;

	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

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
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(200);
        usleep(200);
        bit--;
    }
}

int main(int ac, char **av)
{
    int i;

    if (ac != 3)
    {
        printf("Usage: ./client [PID] [string]\n");
        return (1);
    }
    if (!validation_pid(av[1]))
	{
		printf("incorecte PID\n");
		return (1);
	}
    int pid = ft_atoi(av[1]);
    i = 0;
    while (av[2][i])
    {
        send_char(pid, av[2][i]);
        i++;
    }
    send_char(pid, '\0');
    return (0);
}
