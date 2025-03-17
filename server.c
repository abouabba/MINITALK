/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:51:23 by abouabba          #+#    #+#             */
/*   Updated: 2025/03/17 06:52:05 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    signal_handler(int sig)
{
    static int bit = 0;
    static char c = 0;

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

int main()
{
    printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    while (1)
        pause();
    return (0);
}
