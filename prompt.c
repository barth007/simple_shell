#include "shell.h"


ssize_t prompt(char *buffer, char **argv) 
{
    size_t len = 0;
    ssize_t read_byte;
    char *text_prompt;

    text_prompt = "$";
    while (TRUE) {
        printf("%s ", text_prompt);
        read_byte = getline(&buffer, &len, stdin);
        if (read_byte == -1) {
            /*end of file or error occurred*/
	    return (-1);
        }
	if (strstr(buffer, "exit"))
	{
		return (-1);

	}
	tokenize(argv, buffer, read_byte);
    }

   free(buffer);
    return (read_byte);
}

