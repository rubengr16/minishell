/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:09:57 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/26 17:44:40 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * reads the keyboard input in the case of here_doc.
 * INPUT:	t_pipex *pipex, char *fin
 * OUTPUT:	void
 */
static void	read_from_stdin(t_pipex *pipex, char *fin)
{
	char			*str;
	unsigned long	lim_len;

	pipex->fdin = open(fin, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fdin >= 0)
	{
		lim_len = ft_strlen(pipex->limiter);
		str = get_next_line(STDIN_FILENO);
		while (str && ((ft_strlen(str) - 1) != lim_len
				|| ft_strncmp(str, pipex->limiter, lim_len)))
		{
			write(pipex->fdin, str, ft_strlen(str));
			free(str);
			str = get_next_line(STDIN_FILENO);
		}
		free(str);
		close(pipex->fdin);
	}
}

/*
 * if there are 2 or more cmds, manages the files openings either if there
 * is here_doc or not.
 * INPUT:	t_pipex *pipex, char *fin, char *fout
 * OUTPUT:	void
 */
static void	files_mngment(t_pipex *pipex, char *fin, char *fout)
{
	if (pipex->cmds->n_elem < 2)
		error_msg(*pipex, NULL, ERR_ARGC);
	if (pipex->limiter)
		read_from_stdin(pipex, fin);
	pipex->fdin = open(fin, O_RDONLY);
	if (pipex->limiter)
		pipex->fdout = open(fout, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->fdout = open(fout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fdin < 0)
		error_msg(*pipex, fin, ERR_SYS);
	if (pipex->fdout < 0)
		error_msg(*pipex, fout, ERR_SYS);
}

/*
 * receives argv to get the names of the fin, tests is here_doc, divides the
 * given commands into command and flag which are stored in the list. After the
 * storing process, the fin and fout are given to files_mngment.
 * INPUT:	t_pipex *pipex, char **argv
 * OUTPUT:	void
 */
void	preparate_pipex(t_pipex *pipex, char **argv)
{
	char	**aux;
	char	*fin;
	int		i;

	i = 2;
	fin = argv[1];
	if (ft_strlen(fin) == ft_strlen(HERE_DOC)
		&& !ft_strncmp(fin, HERE_DOC, ft_strlen(HERE_DOC)))
	{
		fin = PATH_DOC;
		pipex->limiter = argv[2];
		i++;
	}
	pipex->cmds = cmdlistinit();
	if (!pipex->cmds)
		error_msg(*pipex, "cmdlistinit failed", ERR_SYS);
	while (argv[i] && argv[i + 1])
	{
		aux = ft_split(argv[i], ' ');
		if (!aux)
			error_msg(*pipex, "ft_split failed", ERR_SYS);
		cmdlistpush_cmd(pipex->cmds, aux);
		i++;
	}
	files_mngment(pipex, fin, argv[i]);
}

/*
 * searchs for the correct full path of the command if possible
 * INPUT:	char **set_of_paths, char **path, char *cmd, int *cnt
 * OUTPUT:	void
 */
static char	*try_path(t_pipex pipex, char **set_of_paths, char *cmd)
{
	char	*path;
	int		cnt;

	cnt = 0;
	path = ft_strjoinsep(set_of_paths[cnt], cmd, "/");
	while (set_of_paths[cnt] && path && access(path, F_OK | X_OK))
	{
		free(path);
		cnt++;
		path = ft_strjoinsep(set_of_paths[cnt], cmd, "/");
	}
	if (!set_of_paths[cnt] || !path)
		error_msg(pipex, cmd, ERR_CMD);
	free(cmd);
	return (path);
}

/*
 * receives pipex for setting the cmds and the environment variables in
 * envp. It searchs for the "PATH=" variable, splits all the source paths to
 * give them to try_path in order to test if there is access to the required
 * commmand.
 * INPUT:	t_pipex pipex, char **envp
 * OUTPUT:	void
 */
void	arevalidcmds(t_pipex pipex, char **envp)
{
	t_node	*aux;
	char	**set_of_paths;
	int		cnt;

	cnt = 0;
	while (envp[cnt] && !ft_strnstr(envp[cnt], "PATH=", 5))
		cnt++;
	if (!envp[cnt])
		error_msg(pipex, "Please, provide env variables", ERR_ENVP);
	set_of_paths = ft_split(&envp[cnt][5], ':');
	if (!set_of_paths)
		error_msg(pipex, "ft_split failed", ERR_SYS);
	cnt = pipex.cmds->n_elem;
	while (cnt)
	{
		aux = cmdlistpop(pipex.cmds);
		aux->cmd_flag[CMD] = try_path(pipex, set_of_paths, aux->cmd_flag[CMD]);
		cmdlistpush(pipex.cmds, aux);
		cnt--;
	}
	ft_free_split(set_of_paths);
}
