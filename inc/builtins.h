/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:19:41 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/11 11:11:35 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include "enviroment.h"
# include "global.h"
# include "utils.h"

# define EXPORT_ERR -1

/* ******************************** BUILTINS ******************************** */
void	ft_echo(char **args);							// juanizado
int 	ft_cd(char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(char **args);	// 2 Checking
int		set_vble(char *vble, char *equal_sign);
void	ft_unset(char **args);	// 3 Done it
void	ft_env(void);					// 3 Done it

#endif
