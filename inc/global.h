/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 08:59:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 11:29:43 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct s_global
{
	char	**envp;
	int		my_errno;
}	t_global;

extern t_global g_sigenv;

#endif
