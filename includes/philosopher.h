/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:07:22 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/05 15:01:22 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include "struct.h"

int		ft_check_args(int argc, char **argv);
t_args	*ft_get_args(t_data *data, int argc, char **argv);

int		ft_strlen(char *s);
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

int		ft_calc_service(t_data *data);
int		ft_calc_time_to_think(t_data *data);

void	*ft_update_time(void *arg);
long long	ft_get_time(void);


#endif
