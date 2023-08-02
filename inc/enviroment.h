/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:20:09 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/02 18:05:35 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include "global.h"
# include "lexer.h"
# include "utils.h"

/* ***************************** ENVIROMENT ****************************** */
char	**create_my_env(char **envp);
void	delete_env_vbles(void);
int		get_pos_vble(char *name);
char	*get_env(char *name);

#endif
