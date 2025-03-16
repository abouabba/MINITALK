#include "minitalk.h"

void send_string(char *str)
{
	int i = 0;
	while (str[i])
	{
		int j = 7;
		while (j >= 0)
		{
			if (1 & (str[i] >> j))
				kill(pid , siguser1);
			else
				kill(pid , siguser2);
			j--;
		}
		i++;
	}
}

int main (int ac, char **av)
{
	if (ac == 3)
	{
		print_binary(av[1]);
	}
	return (0);
}
