/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:34:34 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/15 23:36:39 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "enviroment.h"

void	sig_normal(int sig);
void	sig_exec(int sig);
void	sig_here_doc(int sig);

#endif
