/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:02:03 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/14 08:55:25 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_eat(t_philo *philo)
{
	if (!ft_take_fork(philo, 1))
		return (0);
	if (!ft_print(philo, " has taken a fork", 0))
		return (0);
	if (!ft_take_fork(philo, 2))
		return (0);
	if (!ft_print(philo, " has taken a fork", 0))
		return (0);
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (!ft_print(philo, " is eating", 0))
		return (0);
	if (!ft_usleep(philo, philo->data->init_time, philo->args->time_eat))
		return (0);
	ft_free_fork(philo);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (!ft_print(philo, " is sleeping", 0))
		return (0);
	if (!ft_usleep(philo, philo->data->init_time, philo->args->time_sleep))
		return (0);
	if (!ft_print(philo, " is thinking", 0))
		return (0);
	if (philo->args->nb_philo % 2 == 1)
		ft_usleep(philo, philo->data->init_time, (philo->args->time_live
            - (philo->args->time_eat + philo->args->time_sleep)) / 2);
	else
		usleep(10);
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->args->nb_philo == 1)
	{
		philo->data->fork[philo->thr_id - 1] = 0;
		printf("0\t1 has taken a fork\n");
		usleep(1000 * philo->args->time_live);
		philo->data->fork[philo->thr_id - 1] = 1;
		printf("%d\t1 is dead\n", philo->args->time_live);
		return (NULL);
	}
	philo->lst_eat = ft_update_time(philo->data->init_time);
	if (philo->thr_id % 2 == 0)
		ft_usleep(philo, philo->data->init_time, 30);
	while (1)
	{
		if (!ft_eat(philo))
			break ;
		if (!--philo->nb_iter)
			break ;
		if (!ft_sleep(philo))
			break ;
	}
	return (NULL);
}
