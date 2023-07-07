#include "enviroment.h"

int is_equals(char *name, char **args)
{
	int	i;
	int	found;

	i = 1;
	found = 0;
	while (args[i] && !found)
	{
		if (ft_strncmp(name, args[i], (ft_strlen(args[1]) + 1)) == 0)
			found = 1;
		i++;
	}
	return(found);
}

void	delete_node(t_variable *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

char	*cd_aux(t_enviroment *my_env, char **args, int *free_flag)
{
	char	*result;

	*free_flag = 0;
	if (args[1][0] == '~' && args[1][1] == '\0')
		result = get_env(my_env, "HOME");
	else if (args[1][0] == '~' && args[1][1] == '/')
	{
		result = ft_strjoin(get_env(my_env, "HOME"), (args[1] + 1));
		if (!result)
			return(NULL);
		*free_flag = 1;
	}
	else
		result = args[1];
	return (result);
}

int	check_splitable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == '=' && str[i - 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	mini_split(char *variable, t_variable *new_var)
{
	int		i;
	int		n_len;

	n_len = 0;
	i = 0;
	while (variable[n_len] != '=')
		n_len++;
	new_var->name = malloc(sizeof(char) * (n_len + 1));
	if (!new_var->name)
		return ;
	while (i < n_len)
	{
		new_var->name[i] = variable[i];
		i++;
	}
	new_var->name[i] = '\0';
	new_var->value = ft_strdup(variable + (n_len + 1));
	if (!new_var->value && new_var->name)
	{
		free(new_var->name);
		new_var->name = NULL;
	}
}
