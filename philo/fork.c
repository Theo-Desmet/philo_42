/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 08:51:22 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/28 08:54:00 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_take_fork(t_philo *philo, int nb_fork)
{
	int	fork;

	fork = ft_choose_fork(philo, nb_fork);
	if (ft_check_dead(philo, 0))
		return (0);
	pthread_mutex_lock(&philo->data->m_fork[fork]);
	while (!philo->data->fork[fork])
	{
		pthread_mutex_unlock(&philo->data->m_fork[fork]);
		pthread_mutex_lock(&philo->data->m_fork[fork]);
		if (ft_check_dead(philo, 0))
		{
			pthread_mutex_unlock(&philo->data->m_fork[fork]);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->m_fork[fork]);
		usleep(100);
		pthread_mutex_lock(&philo->data->m_fork[fork]);
	}
	philo->data->fork[fork] = 0;
	pthread_mutex_unlock(&philo->data->m_fork[fork]);
	if (ft_check_dead(philo, 0))
		return (0);
	return (1);
}

int	ft_choose_fork(t_philo *philo, int nb_fork)
{
	if (nb_fork == 1)
	{
		if (philo->thr_id - 1 > philo->thr_id % philo->args->nb_philo)
			return (philo->thr_id % philo->args->nb_philo);
		return (philo->thr_id - 1);
	}
	else
	{
		if (philo->thr_id - 1 < philo->thr_id % philo->args->nb_philo)
			return (philo->thr_id % philo->args->nb_philo);
		return (philo->thr_id - 1);
	}
}

void	ft_free_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_fork[philo->thr_id - 1]);
	philo->data->fork[philo->thr_id - 1] = 1;
	pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id - 1]);
	pthread_mutex_lock(&philo->data->m_fork[philo->thr_id
		% philo->args->nb_philo]);
	philo->data->fork[philo->thr_id % philo->args->nb_philo] = 1;
	pthread_mutex_unlock(&philo->data->m_fork[philo->thr_id
		% philo->args->nb_philo]);
}
