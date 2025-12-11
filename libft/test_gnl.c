#include "libft.h"

int	main(void)
{
	int i = 0;
	int fd;
	char *p;

	// fd = open();
	// fd = open("test.txt", O_RDONLY);
	fd = open("gnl_edge_cases.txt", O_RDONLY);
	// fd = open("empty.txt", O_RDONLY);
	// fd = open("newline.txt", O_RDONLY);
	while (1)
	{
		p = get_next_line(fd);
		if (!p)
			break ;
		printf("Line %d: '%s'", i + 1, p);
		free(p);
		i++;
	}
}