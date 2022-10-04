/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:32:50 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/04 09:23:14 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_free_mutex(t_data *data, int err)
{
	int	i;

	i = 0;
	if (!data->m_fork)
		return ;
	while ((void *)(&data->m_fork[i]) != NULL && i < data->args->nb_philo)
	{
		pthread_mutex_destroy(&data->m_fork[i]);
		i++;
	}
	free(data->m_fork);
	if (err == 1)
		pthread_mutex_destroy(&data->m_print);
	if (err > 1)
		pthread_mutex_destroy(&data->m_dead);
}

void	ft_free_philo(t_data *data)
{
	int	i;

	i = 0;
	if (!data->philo)
		return ;
	while (i < data->args->nb_philo)
	{
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
}

void	ft_free_data(t_data *data)
{
	ft_free_mutex(data, 2);
	ft_free_philo(data);
	if (data->args)
		free(data->args);
	if (data->fork)
		free(data->fork);
	free(data);
}
