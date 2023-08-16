/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:19:41 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 15:21:40 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include "enviroment.h"
# include "global.h"
# include "utils.h"

# define CMD 0
# define ARG_1 1

/* ******************************** BUILTINS ******************************** */
void	ft_echo(char **args);							// juanizado
void	ft_cd(char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(char **args);	// 2 Checking
void	ft_unset(char **args);	// 3 Done it
void	ft_env(void);					// 3 Done it
void	ft_exit(char **args, int is_child);

int		set_vble(char *vble, char *equal_sign);

#endif
