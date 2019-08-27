#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct		Table
{
	unsigned int	sin;	/* integer part of 2^32 times abs(sin(i)) */
	unsigned char	word;	/* index of which word to use out of 32 */
	unsigned char	rotate;	/* amount to rotate left by */
}					Table;

Table tab[] =
{
	/* round 1 */
	{ 0xd76aa478, 0, 7},
	{ 0xe8c7b756, 1, 12},
	{ 0x242070db, 2, 17},
	{ 0xc1bdceee, 3, 22},
	{ 0xf57c0faf, 4, 7},
	{ 0x4787c62a, 5, 12},
	{ 0xa8304613, 6, 17},
	{ 0xfd469501, 7, 22},
	{ 0x698098d8, 8, 7},
	{ 0x8b44f7af, 9, 12},
	{ 0xffff5bb1, 10, 17},
	{ 0x895cd7be, 11, 22},
	{ 0x6b901122, 12, 7},
	{ 0xfd987193, 13, 12},
	{ 0xa679438e, 14, 17},
	{ 0x49b40821, 15, 22},

	/* round 2 */
	{ 0xf61e2562, 1, 5},
	{ 0xc040b340, 6, 9},
	{ 0x265e5a51, 11, 14},
	{ 0xe9b6c7aa, 0, 20},
	{ 0xd62f105d, 5, 5},
	{  0x02441453, 10, 9},
	{ 0xd8a1e681, 15, 14},
	{ 0xe7d3fbc8, 4, 20},
	{ 0x21e1cde6, 9, 5},
	{ 0xc33707d6, 14, 9},
	{ 0xf4d50d87, 3, 14},
	{ 0x455a14ed, 8, 20},
	{ 0xa9e3e905, 13, 5},
	{ 0xfcefa3f8, 2, 9},
	{ 0x676f02d9, 7, 14},
	{ 0x8d2a4c8a, 12, 20},

	/* round 3 */
	{ 0xfffa3942, 5, 4},
	{ 0x8771f681, 8, 11},
	{ 0x6d9d6122, 11, 16},
	{ 0xfde5380c, 14, 23},
	{ 0xa4beea44, 1, 4},
	{ 0x4bdecfa9, 4, 11},
	{ 0xf6bb4b60, 7, 16},
	{ 0xbebfbc70, 10, 23},
	{ 0x289b7ec6, 13, 4},
	{ 0xeaa127fa, 0, 11},
	{ 0xd4ef3085, 3, 16},
	{  0x4881d05, 6, 23},
	{ 0xd9d4d039, 9, 4},
	{ 0xe6db99e5, 12, 11},
	{ 0x1fa27cf8, 15, 16},
	{ 0xc4ac5665, 2, 23},

	/* round 4 */
	{ 0xf4292244, 0, 6},
	{ 0x432aff97, 7, 10},
	{ 0xab9423a7, 14, 15},
	{ 0xfc93a039, 5, 21},
	{ 0x655b59c3, 12, 6},
	{ 0x8f0ccc92, 3, 10},
	{ 0xffeff47d, 10, 15},
	{ 0x85845dd1, 1, 21},
	{ 0x6fa87e4f, 8, 6},
	{ 0xfe2ce6e0, 15, 10},
	{ 0xa3014314, 6, 15},
	{ 0x4e0811a1, 13, 21},
	{ 0xf7537e82, 4, 6},
	{ 0xbd3af235, 11, 10},
	{ 0x2ad7d2bb, 2, 15},
	{ 0xeb86d391, 9, 21},
};

typedef struct		MD5state
{
	unsigned int 	state[4]; 	/*the 128 bit digest that will have 64 operations done to get hash */
	unsigned long	l;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;

}					MD5state;

void 		get_words(int fd, char *name);
MD5state* 	md5(unsigned char* buf, MD5state *s);
MD5state* 	algo_operations(MD5state *s, int i, unsigned *x, Table *t);
void 		decode(unsigned int *output, unsigned char *input, unsigned int len);
void 		encode(unsigned char *output, unsigned int *input, unsigned int len);


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
			get_words(fd, av[2]);
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

void get_words(int fd, char *name)
{
	unsigned char *buf;
	unsigned int i;
	MD5state *s;

	s->l = 0;
	s->state[0] = 0x67452301;
	s->state[1] = 0xefcdab89;
	s->state[2] = 0x98badcfe;
	s->state[3] = 0x10325476;
	buf = (unsigned char*)malloc(1024);
	while (1)
	{
		// printf("i read this: %s\n" ,buf);
		bzero(buf, 1024);
		if ((i = read(fd, buf, 512)) != 0)
			i = i;
		// else
		// {
		// 	printf("total size is %lu\n", s->l);
		// 	break;
		// }
		s->l += i;
		if (i == 0 || (i & 63) != 0)
		{
			buf[i] = 0x80;
			printf("i %u buf[i]=%#10x",i, buf[i]);
			// add padding
			// md5
			break;
		}
		else
		{
			printf("my i was %u\n", i);
			md5(buf, s);
		}
	}
}
MD5state* 	md5(unsigned char* buf, MD5state *s)
{
	int i;
	unsigned int tmp;
	unsigned int x[16];	//16 32-bit words

	i = 0;
	decode(x, buf, 64); //(buf to x) 8bit x 64 chars to 16bit x 32 ints
	s->a = s->state[0];
	s->b = s->state[1];
	s->c = s->state[2];
	s->d = s->state[3];
	while (i < 64)
	{
		s = algo_operations(s, i++, x);
		tmp = a;
		s->a = d;
		s->d = c;
		s->c = b;
		s->b = tmp;
	}
	s->state[0] += a;
	s->state[1] += b;
	s->state[2] += c;
	s->state[3] += d;
	return s;
}

MD5state* 	algo_operations(MD5state *s, int i, unsigned int *x)
{
	Table *t;

	if (i>>4 == 0)//bitwise operations depending on i
		s->a += (s->b & s->c) | (~(s->b) & s->d);
	if (i>>4 == 1)
		s->a += (s->b & s->d) | (s->c & ~(s->d));
	if (i>>4 == 2)
		s->a += s->b ^ s->c ^ s->d;
	if (i>>4 == 3)
		s->a += s->c ^ (s->b | ~(s->d));
	t = tab + i;	//change table values each operation
	s->a += x[t->word] + t->sin; //modular addition of the word and sin
	s->a = (a << t->rot) | (a >> (32 - t->rot)); // circulatory rotation by table ammount
	s->a += b; // modular addtion of a and b
	return s;
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






























































	// free(buf);

