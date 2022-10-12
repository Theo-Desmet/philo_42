/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 08:54:32 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/12 09:47:48 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_print(t_philo *philo, char *str, int act)
{
	long long	time;

	if (ft_check_dead(philo, act))
		return (0);
	time = ft_update_time(philo->data->init_time);
	pthread_mutex_lock(&philo->data->m_print);
	if (time > philo->lst_eat + philo->args->time_live)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return (ft_is_dead(philo), 1);
	}
	time = ft_update_time(philo->data->init_time);
	printf("%lld\t%d%s\n", time, philo->thr_id, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	ft_usleep(t_philo *philo, long long init_time, int ms)
{
	long long	end;
	long long	time;

	time = ft_update_time(init_time);
	end = time + ms;
	while (time < end)
	{
		if (ft_check_dead(philo, 0))
			return (0);
		usleep(500);
		time = ft_update_time(init_time);
	}
	return (1);
}

int	ft_check_dead(t_philo *philo, int act)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	time = ft_update_time(philo->data->init_time);
	if (act == 0 && time > philo->lst_eat + philo->args->time_live)
		return (ft_is_dead(philo), 1);
	return (0);
}

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	while (ft_update_time(philo->data->init_time)
		< philo->args->time_live + philo->lst_eat)
		usleep(100);
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->m_dead);
	usleep (5000);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld\t%d is dead\n",
		ft_update_time(philo->data->init_time), philo->thr_id);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}
