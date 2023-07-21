# include "enviroment.h"

void	ft_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 0;
	if (!ft_strncmp(args[1], "-n\0", 3))
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

void	ft_cd(char **my_envp, char **args)
{
	char	*complete_path;
	int		free_flag;

	if (!args[1])
	{
		if (chdir(get_env(my_envp, "HOME")))
			write(2, "cd: HOME not set\n", 17);	// Puede estar modificado la variable HOME y mostrar el error de no se encuentra directorio
	}
	else if (args[2])
		write(2, "cd: too many arguments\n", 23);
	else{
		complete_path = cd_aux(my_envp, args, &free_flag);
		if (chdir(complete_path))
			printf("cd: %s: No such file or directory\n", args[1]);
		if (free_flag)
			free(complete_path);
	}
}

char **ft_delete_vble(unsigned int skip_pos)
{

}

void	ft_unset(char ***my_envp, char **args)
{
	char			**aux;
	unsigned int	i;
	unsigned int	j;

	if (!*my_envp && len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	aux = *my_envp;
	while (aux && args[i])
	{
		j = 0;
		while ((*my_envp)[j] 
			&& (ft_strncmp((*my_envp)[j], args[i], ft_strlen(args[i])) == '='))
			j++;
		if ((*my_envp)[j])
		{

		}
		i++;
	}
}

void	ft_export(char ***my_envp, char **args)
{
	char	**aux;
	char	vble_cpy;
	int		i;

	if (len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	aux = *my_envp;
	while (aux && args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			vble_cpy = ft_strdup(args[i]);
			aux = add_to_char_double_ptr(my_envp, vble_cpy);
		}
		i++;
	}
}
