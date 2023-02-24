#include "shell.h"
/**
 * *_memset - function fills the first n bytes of the memory
 * area pointed to by s with the constant byte b
 *
 * @s: pointer to the memory area
 * @b: constant integer  chararcter to be filled
 * @n: number of bytes
 */

void *_memset(void *s, int b, ssize_t n)
{
	ssize_t i;

	for (i = 0; i < n; i++)
	{
		s = &b;
	}
}


