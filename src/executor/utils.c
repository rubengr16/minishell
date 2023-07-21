#include "executor.h"

int	count_cmds(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	i = 0;
	aux = cmd;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

char	*verify_commands(char **path, char *cmd)
{
	char	*commnd;
	int		i;
	int		flag;
	char	*aux;

	i = 0;
	flag = 0;
	if (cmd[0] == '.')
		return(cmd);
	while (path[i] && !flag)
	{
		aux = ft_strjoin("/", cmd);
		commnd = ft_strjoin(path[i], aux);
		if (access(commnd,F_OK | X_OK) == 0)
			flag++;
		else
			free(commnd);
		i++;
	}
	if (!flag)
		commnd = NULL;
	free(aux);
	return (commnd);
}
