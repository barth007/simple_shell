#include "shell.h"
/**
	*unget_char - returns the last character from an input
	*@src: the string to check
**/
void unget_char(struct source_s *src)
{
	if (src->curpos < 0)
	{
		return;
	}
	src->curpos--;
}
/**
	*next_char - returns next character of an input and update the src
	*@src: update the src argument
	*Return: the next character
**/
char next_char(struct source_s *src)
{
	char c1;

	c1 = 0;
	if (!src || !src->buffer)
	{
		perror("Error");
	}
	if (src->curpos == INIT_SRC_POS)
	{
		src->curpos  = -1;
	}
	else
	{
		c1 = src->buffer[src->curpos];
	}
	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}
	return (src->buffer[src->curpos]);
}
/**
	*peek_char - returns the next character input but does not update
	*@src: input argument
	*Return: next char
**/
char peek_char(struct source_s *src)
{
	long pos;

	pos = src->curpos;
	if (!src || !src->buffer)
	{
		perror("Error");
	}
	if (pos == INIT_SRC_POS)
	{
		pos++;
	}
	pos++;
	if (pos >= src->bufsize)
	{
		return (EOF);
	}
	return (src->buffer[pos]);
}
/**
 *skip_white_spaces - skips all white spaces
 *@src: input to check
**/
void skip_white_spaces(struct source_s *src)
{
	char c;

	if (!src || !src->buffer)
	{
		return;
	}
	while (((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
	}
}
