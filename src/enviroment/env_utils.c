#include "enviroment.h"

char	*cd_aux(char **my_envp, char **args, int *free_flag)
{
	char	*result;

	*free_flag = 0;
	if (args[1][0] == '~' && args[1][1] == '\0')
		result = get_env(my_envp, "HOME");
	else if (args[1][0] == '~' && args[1][1] == '/')
	{
		result = ft_strjoin(get_env(my_envp, "HOME"), (args[1] + 1));
		if (!result)
			return(NULL);
		*free_flag = 1;
	}
	else
		result = args[1];
	return (result);
}
