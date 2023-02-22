#include "shell.h"
/**
 *read_input - read input from stdinput
 *Return: return ptr to char
**/
char *read_input()
{
	char *ptr, *line, *new_ptr;
	size_t ptrlen, bufsize,  buflen;

	ptrlen = 0;
	line = NULL;
	ptr = NULL;
	while ((buflen = getline(&line, &bufsize, stdin)) != -1)
	{
		if (ptr == NULL)
			ptr = malloc(buflen + 1);
		else
		{
			new_ptr = malloc(ptrlen + buflen + 1);
			if (new_ptr == NULL)
			{
				free(ptr);
				ptr = NULL;
				break;
			}
			_memcpy(new_ptr, ptr, ptrlen);
			free(ptr);
			ptr = new_ptr;
		}
		_memcpy(ptr + ptrlen, line, buflen);
		ptrlen += buflen;
		if (line[buflen - 1] == '\n')
		{
			if (buflen == 1 || line[buflen - 2] != '\\')
			{
				free(line);
				return (ptr);
			}
			ptr[ptrlen - 2] = '\0';
			ptrlen -= 2;
			main_prompt2();
		}
	}
	if (line)
		free(line);
	return (ptr);
}
/**
 *parse_and_execute - parse into the input and execute command
 *@src: argument from source_s data type
 *Return: always int
**/
int parse_and_execute(struct source_s *src)
{
	struct token_s *tok;
	struct node_s *cmd;

	skip_white_spaces(src);
	tok = tokenize(src);
	if (tok == &eof_token)
	{
		return (0);
	}
	while (tok && tok != &eof_token)
	{
		cmd = parse_simple_command(tok);
		if (!cmd)
		{
			break;
		}
		do_simple_command(cmd);
		free_node_tree(cmd);
		tok = tokenize(src);
	}
	return (1);
}
