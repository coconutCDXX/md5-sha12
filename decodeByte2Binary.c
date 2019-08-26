#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
void decode(unsigned int *output, unsigned char *input, unsigned int len);
void encode(unsigned char *output, unsigned int *input, unsigned int len);
int main(int ac, char** av)
{
	// unsigned char	*buf, digest[16];
	// unsigned int	i, n, len;
	// unsigned int	x[16];
	//
	// i = 0;
	// int fd;
	// fd = open(av[1], O_RDONLY);
	//
	// buf = (unsigned char*)malloc(512);
	// bzero(buf, 512);
	// while (1)
	// {
	// 	if ((n = read(fd, buf, 512)) != 0)
	// 		printf("i read this: %s\n" ,buf);
	// 	else
	// 		break;
	// }
	//
	// decode(x, buf, 64);
	// printf("the binary in decimal is %d %d %d %d\n", x[0], x[1], x[2], x[3]);
	// encode(digest, x, 16);
	// printf("the decoding is back to %s\n", digest);0
	// free(buf);

	unsigned int a[] = {205,3,111,60,205,3,111,60,205,3,111,60,205,3,111,60};
	char x;
	x = a[3];
	printf("%c\n", x);
	unsigned char test[16];
	int i;
	encode(test, a, 16);
	for(i=0;i<16;i++) printf("%.2X", test[i]);


}
void decode(unsigned int *output, unsigned char *input, unsigned int len)
{
	unsigned char *e;

	for(e = input+len; input < e; input += 4)
	*output++ = input[0] | (input[1] << 8) |
	(input[2] << 16) | (input[3] << 24);
}

void encode(unsigned char *output, unsigned int *input, unsigned int len)
{
	unsigned int x;
	unsigned char *e;

	for(e = output + len; output < e;) {
		x = *input++;
		*output++ = x;
		*output++ = x >> 8;
		*output++ = x >> 16;
		*output++ = x >> 24;
	}
}
