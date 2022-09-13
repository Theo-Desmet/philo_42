/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:02:03 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/13 15:53:07 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_is_dead(t_philo *philo)
{
	int	time;
	int	i;

	if (philo->death == 2)
		return ;
	time = ft_update_time(philo->data->init_time);
	while (i < philo->data->args->nb_philo)
	{
		philo->data->philo[i]->death = 2;
		i++;
	}
	usleep(1000);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%d\t%d is dead\n", time, philo->thr_id);
	pthread_mutex_unlock(&philo->data->m_print);
	return ;
}

int	ft_usleep(t_philo *philo, long long init_time, int ms)
{
	int	end;

	end = ft_update_time(init_time) + ms;
	if (end > philo->lst_eat + philo->data->args->time_eat)
	{
		while (ft_update_time(init_time) < end)
			usleep(80);
		return (ft_is_dead(philo), 0);
	}
	while (ft_update_time(init_time) < end)
		usleep(80);
	return (1);
}


void	ft_take_fork (t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	while (!philo->data->fork[fork])
	{
		pthread_mutex_unlock(&philo->data->m_fork[fork]);
		usleep(10);
		pthread_mutex_lock(&philo->data->m_fork[fork]);
	}
	philo->data->fork[fork] = 0;
	pthread_mutex_unlock(&philo->data->m_fork[fork]);
}

void	ft_free_fork (t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	philo->data->fork[fork] = 1;
	pthread_mutex_unlock(&philo->data->m_fork[fork]);
}

void	ft_putnbr(int nbr)
{
	if (nbr / 10)
		ft_putnbr(nbr / 10);
	ft_putchar((nbr % 10) + '0');
}

int	ft_print(t_philo *philo, char *str)
{
	long long	time;

	time = ft_update_time(philo->data->init_time);
	if (time > philo->lst_eat + philo->data->args->time_eat)
		return (ft_is_dead(philo), 0);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld\t%d%s\n", time, philo->thr_id, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	ft_take_fork(philo, philo->thr_id - 1);
	if (!ft_print(philo, " has taken a fork"))
		return (0);
	ft_take_fork(philo, philo->thr_id % philo->data->args->nb_philo);
	if (!ft_print(philo, " has taken a fork"))
		return (0);
	if (!ft_print(philo, " is eating"))
		return (0);
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (ft_usleep(philo, philo->data->init_time, philo->data->args->time_eat))
		return (0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	ft_free_fork(philo, philo->thr_id - 1);
	ft_free_fork(philo, philo->thr_id % philo->data->args->nb_philo);
	if (!ft_print(philo, " is sleeping"))
		return (0);
	if (ft_usleep(philo, philo->data->init_time, philo->data->args->time_sleep))
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
