/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:11:20 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/06 09:24:40 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_philo
{
	int	he_do;
	int	thr_id;
	int	lst_eat;
	pthread_t	philo;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t fork;
	pthread_mutex_t dead;
	pthread_mutex_t time;
	pthread_mutex_t print;
}	t_mutex;

typedef struct s_args
{
	int	nb_philo;
	int	time_live;
	int	time_eat;
	int	time_sleep;
	int	iter;
}	t_args;

typedef struct s_time
{
	pthread_t	monitoring;
	long long	init_time;
	long long	philo_time;
}	t_time;

typedef struct s_data
{
	t_philo		**philo;
	t_args		*args;
	t_mutex		*mutex;
	t_time		*time;
	int		*fork;
	int		dead;
	int		time_think;
	int		nb_service;
}	t_data;

#endif
