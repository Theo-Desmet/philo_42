/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:11:20 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/13 13:39:15 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_args
{
	int	nb_philo;
	int	time_live;
	int	time_eat;
	int	time_sleep;
	int	iter;
}	t_args;

typedef struct s_philo
{
	int	death;
	int	he_do;
	int	thr_id;
	long long	lst_eat;
	pthread_t	philo;
	struct s_data	*data;
}	t_philo;

typedef struct s_time
{
	pthread_t	monitoring;
	long long	init_time;
}	t_time;

typedef struct s_data
{
	t_philo		**philo;
	t_args		*args;
	t_time		*time;
	int		*fork;
	int		dead;
	int		nb_service;
	long long	init_time;
	pthread_mutex_t *m_fork;
	pthread_mutex_t m_print;
	pthread_mutex_t m_start;
}	t_data;

#endif
