#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	line = readline("rs> ");
	printf("%s", line);
}
