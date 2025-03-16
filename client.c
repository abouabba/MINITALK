#include "minitalk.h"

void print_binary(char *str)
{
	int i = 0;
	while (str[i])
	{
		int j = 7;
		while (j >= 0)
		{
			printf ("%d", (str[i] >> j) & 1);
			j--;
		}
		printf (" ");
		i++;
	}
	printf ("\n");
}

int main (int ac, char **av)
{
	if (ac == 2)
	{
		print_binary(av[1]);
	}
	return (0);
}