/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:19:41 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/17 15:26:56 by rgallego         ###   ########.fr       */
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

void	set_vble(char *vble, char *equal_sign);
int		is_valid_vble_name(char *s, unsigned int is_export);
void	export_unset_error(char *cmd, char *identifier);

#endif
