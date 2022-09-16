/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:02:03 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/16 08:55:06 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_is_dead(t_philo *philo)
{
	int	time;
	int	i;

	pthread_mutex_lock(&philo->data->m_dead);
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->m_dead);
	//while (ft_update_time(philo->data->init_time) < philo->lst_eat + philo->data->args->time_live)
	//	usleep(100);
	usleep(8000);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%d\t%d is dead\n", time, philo->thr_id);
	pthread_mutex_lock(&philo->data->m_dead);
	philo->data->dead = 2;
	pthread_mutex_unlock(&philo->data->m_dead);
	return ;
}

int	ft_check_dead(t_philo *philo)
{
//	pthread_mutex_lock(&philo->data->m_dead);
//	if (philo->data->dead == 1)
//	{
//		pthread_mutex_unlock(&philo->data->m_dead);
//		return (0);
//	}
//	pthread_mutex_unlock(&philo->data->m_dead);
	return (1);
}

int	ft_usleep(t_philo *philo, long long init_time, int ms)
{
	int	end;

	end = ft_update_time(init_time) + ms;
	if (end > philo->lst_eat + philo->data->args->time_live)
		return (ft_is_dead(philo), 0);
	while (ft_update_time(init_time) < end)
	{
		if (!ft_check_dead(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

int	ft_take_fork (t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	while (!philo->data->fork[fork])
	{
		pthread_mutex_unlock(&philo->data->m_fork[fork]);
		if (!ft_check_dead(philo))
			return (0);
		usleep(50);
		pthread_mutex_lock(&philo->data->m_fork[fork]);
	}
	philo->data->fork[fork] = 0;
	pthread_mutex_unlock(&philo->data->m_fork[fork]);
	return (1);
}

void	ft_free_fork (t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	philo->data->fork[fork] = 1;
	pthread_mutex_unlock(&philo->data->m_fork[fork]);
}

int	ft_print(t_philo *philo, char *str)
{
	long long	time;

	time = ft_update_time(philo->data->init_time);
	if (!ft_check_dead(philo))
		return (0);
	if (time > philo->lst_eat + philo->data->args->time_live)
		return (ft_is_dead(philo), 0);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld\t%d%s\n", time, philo->thr_id, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (!ft_take_fork(philo, philo->thr_id - 1))
		return (0);
	if (!ft_print(philo, " has taken a fork"))
		return (0);
	if (!ft_take_fork(philo, philo->thr_id % philo->data->args->nb_philo))
		return (0);
	if (!ft_print(philo, " has taken a fork"))
		return (0);
	if (!ft_print(philo, " is eating"))
		return (0);
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (!ft_usleep(philo, philo->data->init_time, philo->data->args->time_eat))
		return (0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	ft_free_fork(philo, philo->thr_id - 1);
	ft_free_fork(philo, philo->thr_id % philo->data->args->nb_philo);
	if (!ft_print(philo, " is sleeping"))
		return (0);
	if (!ft_usleep(philo, philo->data->init_time, philo->data->args->time_sleep))
		return (0);
	if (!ft_print(philo, " is thinking"))
		return (0);
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*) arg;
	philo->lst_eat = 0;
	pthread_mutex_lock(&philo->data->m_start);
	pthread_mutex_unlock(&philo->data->m_start);
	if (philo->thr_id % 2 == 0)
		ft_usleep(philo, philo->data->init_time, philo->data->args->time_eat / 2);
	while (1)
	{
		if (!ft_eat(philo) || !ft_sleep(philo))
			return (0);
	}
}
