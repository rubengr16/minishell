#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

void discover_leaks()
{
	system("leaks minishell");
}

int	main(/*int argc, char **argv, char **env*/)
{
	char	*line;
	t_token_list	*list;

	line = readline("minishell> ");
	list = tokenize(&line);
	print_list(list);
	delete_list(list);
	atexit(discover_leaks);
}
