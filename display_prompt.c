#include "shell.h"

void main_prompt(void)
{
	fprintf(stderr, "$ ");
}
void error_prompt(void)
{
	fprintf(stderr, ": ");
}
