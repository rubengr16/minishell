/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:19:41 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/02 18:24:13 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "enviroment.h"
# include "global.h"
# include "utils.h"
# include <string.h>

# define EXPORT_ERR -2

/* ******************************** BUILTINS ******************************** */
void	ft_echo(char **args);							// juanizado
int 	ft_cd(char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(char **args);	// 2 Checking
int		set_vble(char *vble, char *equal_sign);
void	ft_unset(char **args);	// 3 Done it
void	ft_env(void);					// 3 Done it

#endif
