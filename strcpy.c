#include "shell.h"
/**
 * char *_strcpy - function copies the string pointed to by src
 * includeing the terminating null byte (\0), to the buffer
 * pointed to by dest.
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int k;

	for (k = 0; src[k] != '\0'; k++)
	{
		dest[k] = src[k];
	}
	dest[k] = '\0';
	return (dest);
}

