/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:07:22 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/28 10:07:43 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include "struct.h"

/*		init.c		*/
t_data		*ft_init(t_data *data, int argc, char **argv);
int			ft_init_mutex(t_data *data);
t_philo		**ft_init_philo(t_data *data);

/*		args.c		*/
int			ft_check_args(int argc, char **argv);
t_args		*ft_get_args(t_data *data, int argc, char **argv);
int			ft_check_is_signed_int(int argc, char **argv);
int			ft_check_digit(char *str);
int			ft_is_int(const char *nptr);

/*		clock.c		*/
long long	ft_update_time(long long init_time);
long long	ft_get_time(void);

/*		routine.c	*/
void		*ft_routine(void *arg);
int			ft_sleep(t_philo *philo);
int			ft_eat(t_philo *philo);

/*		philo_utils.c	*/
int			ft_is_dead(t_philo *philo);
int			ft_check_dead(t_philo *philo, int act);
int			ft_usleep(t_philo *philo, long long init_time, int ms);
int			ft_print(t_philo *philo, char *str, int act);

/*		fork.c		*/
void		ft_free_fork(t_philo *philo);
int			ft_choose_fork(t_philo *philo, int nb_fork);
int			ft_take_fork(t_philo *philo, int nb_fork);

/*		utils.c		*/
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
int			ft_strlen(char *s);
#endif
