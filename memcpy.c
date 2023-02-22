#include "shell.h"
/**
 * _memcpy -function copies n bytes from memory area src to memory area dest
 * @src: copied from
 * @dest: copy to
 * @n: number of byte
 * Return: dest
 */
char *_memcpy(char *dest, char *src, size_t n)
{
	size_t i, j, len;

	for (j = 0; src[j] != '\0'; j++)
		len++;
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
		if (i == n && i == len)
			dest[i] = '\0';
	}
	return (dest);
}

