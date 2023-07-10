#include "executtor.h"

int	count_commands(t_cmd **cmd)
{
	t_cmd	*aux = *cmd;
	int		i;

	i = 0;
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
	while (path[i] && !flag)
	{
		aux = ft_strjoin("/", cmd);
		commnd = ft_strjoin(path[i], aux);
		if (access(commnd, X_OK) == 0)
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