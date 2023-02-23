#include <stdio.h>
#include <stdlib.h>

void	print_color(int color)
{
	if (color == -1)
		printf("\e[0m ");
	else if (color == 0)
		printf("\e[48;5;154m ");
	else if (color == 1 || color == 9)
		printf("\e[48;5;155m ");
	else if (color == 2 || color == 8)
		printf("\e[48;5;156m ");
	else if (color == 3 || color == 7)
		printf("\e[48;5;157m ");
	else if (color == 4 || color == 6)
		printf("\e[48;5;158m ");
	else if (color == 5)
		printf("\e[48;5;159m ");
}

int	main(int ac, char **av)
{
	int	nb;

	if (ac != 2)
		return (1);
	printf("\e[1A\e[K");
	nb = atoi(av[1]);
	for (int i = 0; i <= 100; i += 2)
	{
		if (i > nb)
			printf("\e[48;5;196m ");
		else
			print_color(((i / 2) + nb) % 10);
	}
	print_color(-1);
	printf("\e[1;%im%i%%\e[0m\n", 32 + (nb < 100), nb);
}
