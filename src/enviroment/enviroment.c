#include "enviroment.h"

void	create_env_aux(t_enviroment *my_env, t_variable *new_var, int i)
{
	if (i == 0)
	{
		my_env->head = new_var;
		my_env->tail = new_var;
	}
	else
	{
		my_env->tail->next = new_var;
		my_env->tail = new_var;
	}
	my_env->tail->next = NULL;

}

int	create_env_list(char **envp, t_enviroment *my_env)
{
	t_variable	*new_var;
	int			i;

	i = 0;
	while (envp[i])
	{
		new_var = malloc(sizeof(t_variable));
		if (!new_var)
			return (1);
		mini_split(envp[i], new_var);
		if (!new_var->name && !new_var->value)
		{
			free(new_var);
			return (1);
		}
		create_env_aux(my_env, new_var, i);
		i++;
	}
	return (0);
}

void	delete_env_variables(t_enviroment *my_env)
{
	t_variable	*aux;

	if (!my_env)
		return ;
	aux = my_env->head;
	while (my_env->head)
	{
		my_env->head = aux->next;
		if (aux->name)
			free(aux->name);
		if (aux->value)
			free(aux->value);
		free(aux);
		aux = my_env->head;
	}
	free(my_env);
}

char	*get_env(t_enviroment *my_env, char *name)
{
	t_variable	*aux;

	aux = my_env->head;
	while (aux)
	{
		if (ft_strncmp(aux->name, name, (ft_strlen(name) + 1)) == 0)
			break;
		aux = aux->next;
	}
	if (!aux)
		return (NULL);
	return(aux->value);
}

void	ft_env(t_enviroment *my_env)
{
	t_variable	*aux;

	aux = my_env->head;
	while (aux)
	{
		printf("%s=%s\n", aux->name, aux->value);
		aux = aux->next;
	}
}
