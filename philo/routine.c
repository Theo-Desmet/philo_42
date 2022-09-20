/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:02:03 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/20 16:04:02 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_unlock(t_philo *philo, int i)
{
	if (i == 1)
	{
		pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id - 1]);
		return ;
	}
	else
	{
		pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id % philo->data->args->nb_philo]);
		pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id - 1]);
		return ;
	}
}

int	ft_is_dead(t_philo *philo)
{
	int	time;

	time = ft_update_time(philo->data->init_time);
	if (time + philo->data->args->time_eat < philo->lst_eat + philo->data->args->time_live)
		return (0);
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_dead);
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->m_dead);
	while (time < philo->data->args->time_live + philo->lst_eat)
	{
		usleep(100);
		time = ft_update_time(philo->data->init_time);
	}
	usleep (8000);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%d\t%d is dead\n", time, philo->thr_id);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}

int	ft_usleep(t_philo *philo, long long init_time, int ms)
{
	int	end;

	end = ft_update_time(init_time) + ms;
	if (end - ms + philo->data->args->time_eat > philo->lst_eat + philo->data->args->time_live)
		return (ft_is_dead(philo), 0);
	while (ft_update_time(init_time) < end)
		usleep(100);
	return (1);
}

int	ft_take_fork (t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	while (!philo->data->fork[fork])
	{
		if (ft_is_dead(philo))
			return (0);
	}
	philo->data->fork[fork] = 0;
	if (ft_check_dead(philo))
		return (0);
	return (1);
}

int	ft_free_fork (t_philo *philo)
{
	if (ft_check_dead(philo))
		return (ft_unlock(philo, 2), 0);
	philo->data->fork[philo->thr_id - 1] = 1;
	philo->data->fork[philo->thr_id % philo->data->args->nb_philo] = 1;
	pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id % philo->data->args->nb_philo]);
	pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id - 1]);
	return (1);
}

int	ft_print(t_philo *philo, char *str)
{
	long long	time;

	time = ft_update_time(philo->data->init_time);
	if (ft_check_dead(philo))
		return (0);
	pthread_mutex_lock(&philo->data->m_print);
	if (ft_check_dead(philo))
		return (pthread_mutex_unlock(&philo->data->m_print), 0);
	printf("%lld\t%d%s\n", time, philo->thr_id, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	int	time;

	time = ft_update_time(philo->data->init_time);
	if (!ft_take_fork(philo, philo->thr_id - 1))
		return (ft_unlock(philo, 1),0);
	if (!ft_print(philo, " has taken a fork"))
		return (ft_unlock(philo, 1),0);
	if (!ft_take_fork(philo, philo->thr_id % philo->data->args->nb_philo))
		return (ft_unlock(philo, 2),0);
	if (!ft_print(philo, " has taken a fork"))
		return (ft_unlock(philo, 2),0);
	time = ft_update_time(philo->data->init_time);
	if (!time + philo->data->args->time_eat > philo->lst_eat + philo->data->args->time_live)
		return (ft_is_dead(philo), ft_unlock(philo, 2), 0);
	if (!ft_print(philo, " is eating"))
		return (ft_unlock(philo, 2),0);
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (!ft_usleep(philo, philo->data->init_time, philo->data->args->time_eat))
		return (ft_unlock(philo, 2),0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (!ft_free_fork(philo))
		return (0);
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
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (philo->thr_id % 2 == 0)
		ft_usleep(philo, philo->data->init_time, philo->data->args->time_eat / 4);
	while (1)
	{
		if (!ft_eat(philo) || !ft_sleep(philo))
			break ;
		if (philo->nb_iter > 0)
			philo->nb_iter--;
		if (!philo->nb_iter)
			break ;
	}
	return (NULL);
}
