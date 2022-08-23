/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:11:20 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/23 13:38:20 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_philo
{
	int	*is_eat;
	int	*is_sleep;//peut etre remplacer par un seul
	int	*is_think;
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
	t_args		*args;
	t_mutex		*mutex;
	t_philo		*philo;
	t_time		*time;
	pthread_t	*philos;
	int		*fork;
	int		dead;
	int		time_think;
	int		nb_service;
}	t_data;

#endif
