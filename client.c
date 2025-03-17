/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:49 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/17 03:07:53 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
        usleep(600);
        bit--;
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        printf("Usage: ./client [PID] [string]\n");
        return (1);
    }
    int pid = atoi(av[1]);
    if (pid <= 0)
    {
        printf("Invalid PID\n");
        return (1);
    }
    int i = 0;
    while (av[2][i])
    {
        send_char(pid, av[2][i]);
        i++;
    }
    send_char(pid, '\0');
    return (0);
}
