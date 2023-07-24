/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:20:09 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 09:40:21 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stdio.h>
# include <signal.h>
# include "global.h"
# include "lexer.h"
# include "utils.h"

/* ***************************** ENVIROMENT ****************************** */
char	**create_my_env(char **envp);
void	delete_env_vbles(void);
int		get_pos_vble(char *name);
char	*get_env(char *name);

#endif
