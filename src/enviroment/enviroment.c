#include "enviroment.h"

char	**create_my_env(char **envp)
{
	char			**my_envp;
	unsigned int	i;

	i = 0;
	if (envp)
		while (envp[i])
			i++;
	my_envp = malloc(sizeof(char *) * (i + 1));
	if (!my_envp)
		mini_error(NULL, ALLOC_ERR, NULL);
	while (my_envp && envp[i])
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
			delete_env_vbles(&my_envp);
		i++;
	}
	if (my_envp)
		my_envp[i] = NULL;
	return (my_envp);
}

void	delete_env_vbles(char ***my_envp)
{
	unsigned int	i;

	if (!*my_envp)
		return ;
	i = 0;
	while ((*my_envp)[i])
	{
		free((*my_envp)[i]);
		i++;
	}
	free(*my_envp);
	*my_envp = NULL;
}

char	*get_env(char **my_envp, char *name)
{
	char			*vble;
	unsigned int	i;

	if (!my_envp)
		return (NULL);
	i = 0;
	vble = NULL;
	while (!vble && my_envp[i])
	{
		if (ft_strncmp(my_envp[i], name, (ft_strlen(name) + 1)) == '=')
			vble = ft_strchr(my_envp[i], '=') + 1;
		i++;
	}
	return(vble);
}

void	ft_env(char **my_envp)
{
	unsigned int	i;

	if (!my_envp)
		return ;
	i = 0;
	while (my_envp[i])
	{
		ft_putendl_fd(my_envp[i], STDOUT_FILENO);
		i++;
	}
}
