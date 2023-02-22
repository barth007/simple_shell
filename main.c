#include "shell.h"
/**
 *main - entry point
 *@argc: argument count to array
 *@argv: array
 *Return: 0 for success
**/

int main(int argc, char *argv[])
{
	(void) argc;
	(void)argv;
	char *cmd;
	struct source_s src;

	do {
		main_prompt();
		cmd = read_input();
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}
		if (strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			src.buffer = cmd;
			src.bufsize = strlen(cmd);
			src.curpos = INIT_SRC_POS;
			parse_and_execute(&src);
			free(cmd);
		}
	} while (TRUE);

	exit(EXIT_SUCCESS);
}
