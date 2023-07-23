/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:20:09 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 01:03:25 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "lexer.h"
# include "utils.h"
# include <stdio.h>
# include <signal.h>

/* ***************************** ENVIROMENT ****************************** */
char	**create_my_env(char **envp);
void	delete_env_vbles(char ***my_envp);
int		get_pos_vble(char **my_envp, char *name);
char	*get_env(char **my_envp, char *name);

#endif
