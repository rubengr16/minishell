/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:19:41 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/23 20:42:28 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "enviroment.h"
# include "utils.h"

/* ***************************** BUILTINS ****************************** */
void	ft_echo(char **args);							// 3 Done it
void	ft_cd(char **my_envp, char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(char ***my_env, char **args);	// 2 Checking
void	ft_unset(char ***my_env, char **args);	// 3 Done it
void	ft_env(char **my_envp);					// 3 Done it

#endif
