#include "shell.h"
/**
 *search_path - searches for a file in Path
 *@file: file to be searched
 *Return: pointer to a char
**/
char *search_path(char *file)
{
	char *PATH;
	char *p;
	char *p2;
	int plen;
	int alen;
	struct stat st;

	PATH = getenv("PATH");
	p = PATH;
	while (p && *p)
	{
	p2 = p;
		while (*p2 && *p2 != ':')
		{
			p2++;
		}
		plen = p2 - p;
		if (!plen)
		{
			plen = 1;
		}
		alen = strlen(file);
		char path[plen + 1 + alen +1];
		strncpy(path, p, p2 - p);
		path[p2 - p] = '\0';
		if (p2[-1] != '/')
		{
			strcat(path, "/");
		}
		strcat(path, file);
		if (stat(path, &st) == 0)
		{
			if (!S_ISREG(st.st_mode))
			{
				errno = ENOENT;
				p = p2;
				if (*p2 == ':')
				{
					p++;
				}
				continue;
			}
			p = malloc(strlen(path) + 1);
			if (!p)
			{
				return (NULL);
			}
			strcpy(p, path);
			return (p);
		}
		else    /* file not found */
		{
			p = p2;
			if (*p2 == ':')
			{
				p++;
			}
		}
	}
	errno = ENOENT;
	return (NULL);
}
/**
 *do_exec_cmd - it's execute the command found on the path
 *@argc:length of array
 *@argv: an array
 *Return: an integer
**/
int do_exec_cmd(int argc, char **argv)
{
	char *path;

	if (strchr(argv[0], '/'))
	{
		execv(argv[0], argv);
	}
	else
	{
		path = search_path(argv[0]);
	if (!path)
	{
		return (0);
	}
	execv(path, argv);
	free(path);
	}
	return (0);
}
/**
 *free_argv - frees up memory
 *@argc: length of array
 *@argv: array of argument
**/
static inline void free_argv(int argc, char **argv)
{
	if (!argc)
	{
		return;
	}
	while (argc--)
	{
		free(argv[argc]);
	}
}
/**
 *do_simple_command - It takes the command's AST and converts it
 *to an arguments list
 *@node: the pointer to the node
 *Return: integer
**/
int do_simple_command(struct node_s *node)
{
	pid_t child_pid;
	struct node_s *child;
	int argc, status;
	long max_args;
	char *str;

	if (!node)
	{
		return (0);
	}
	child = node->first_child;
	if (!child)
	{
		return (0);
	}
	argc = 0;
	max_args = 255;
	char *argv[max_args + 1];
	while (child)
	{
		str = child->val.str;
		argv[argc] = malloc(strlen(str) + 1);
		if (!argv[argc])
		{
			free_argv(argc, argv);
			return (0);
		}
		strcpy(argv[argc], str);
		if (++argc >= max_args)
		{
			break;
		}
		child = child->next_sibling;
	}
	argv[argc] = NULL;
	child_pid = fork();
	if (child_pid == 0)
	{
		do_exec_cmd(argc, argv);
		fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
		if (errno == ENOEXEC)
		{
			exit(126);
		}
		else if (errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid < 0)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		return (0);
	}
	status = 0;
	waitpid(child_pid, &status, 0);
	free_argv(argc, argv);
	return (1);
}
