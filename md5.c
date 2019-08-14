#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void make_md5_digest(int fd, char *name);

int main(int ac, char** av)
{
	int fd;
	int i;

	i = 2;
	if (ac == 1)
		write(1, "usage: ft_ssl command [command opts] [command args]\n", 52);
	else if (strcmp(av[1], "md5") == 0)
	{
		while(av[i] != NULL)
		{
			fd = open(av[i], O_RDONLY);
			make_md5_digest(fd, av[2]);
			i++;
		}
	}
	else
	{
		write(1, "ft_ssl: Error: '", 16);
		write(1, av[1], strlen(av[1]));
		write(1, "' is an invalid command.", 24);
		write(1, "\nStandard commands:\n\nMessage Digest commands:", 45);
		write(1, "\nmd5\nsha256\n\nCipher commands:\n", 30);
	}

}

void make_md5_digest(int fd, char *name)
{
	char *buf;
	buf = (char*)malloc(512);
	while (1)
	{
		bzero(buf, 512);
		if (read(fd, buf, 512) != 0)
			printf("i read this: %s\n" ,buf);
		else
			break;
	}
	free(buf);
}
