#include "shell.h"
/**
 *_strlen - return the total length of a stress
 *@s: the string to check for it's length
 *Return: the length of the string
**/
size_t _strlen(const char *s)
{
	size_t length;
	size_t i;

	length = 0;
	i = 0;
	while(s[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}
