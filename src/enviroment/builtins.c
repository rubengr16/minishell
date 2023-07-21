# include "enviroment.h"

void	ft_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 0;
	if (ft_strncmp(args[1], "-n\0", 3) == 0)
		new_line = 1;
	i = new_line + 1;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!new_line)
		printf("\n");
}

void	ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	free(dir);
}

void	ft_unset(t_enviroment *my_env, char **args)
{
	t_variable	*aux;
	t_variable	*pre;
	t_variable	*delete;

	aux = my_env->head;
	pre = NULL;
	while (aux)
	{
		if (is_equals(aux->name, args))
		{
			if (pre)
				pre->next = aux->next;
			else
				my_env->head = aux->next;
			delete = aux;
			aux = aux->next;
			delete_node(delete);
		}
		else
		{
			pre = aux;
			aux = aux->next;
		}
	}
}

void	ft_cd(t_enviroment *my_env, char **args)
{
	char	*complete_path;
	int		free_flag;

	if (!args[1])
	{
		if (chdir(get_env(my_env, "HOME")) != 0)
			write(2, "cd: HOME not set\n", 17);	// Puede estar modificado la variable HOME y mostrar el error de no se encuentra directorio
	}
	else if (args[2])
		write(2, "cd: too many arguments\n", 23);
	else{
		complete_path = cd_aux(my_env, args, &free_flag);
		if (chdir(complete_path) != 0)
			printf("cd: %s: No such file or directory\n", args[1]);
		if (free_flag)
			free(complete_path);
	}
}

void	ft_export(t_enviroment *my_env, char **args)
{
	int	i;
	t_variable	*new_var;

	i = 0;
	while (args[i])
	{
		if (check_splitable(args[i]))
		{
			new_var = malloc(sizeof(t_variable));

			mini_split(args[i], new_var);
			if (!new_var)
			{
				write(2, "Error: Out of memory\n", 21);
				return ;
			}
			new_var->next = NULL;
			my_env->tail->next = new_var;
			my_env->tail = new_var;
		}
		i++;
	}
}
