/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 08:38:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/28 10:05:11 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->args->nb_philo);
	if (!data->m_fork)
		return (0);
	while (i < data->args->nb_philo)
	{
		pthread_mutex_init(&data->m_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	return (1);
}

t_philo	**ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (NULL);
		data->philo[i]->he_do = 0;
		data->philo[i]->thr_id = i + 1;
		data->philo[i]->nb_iter = data->args->iter;
		data->philo[i]->args = data->args;
		data->philo[i]->data = data;
		i++;
	}
	return (data->philo);
}

t_data	*ft_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->args = ft_get_args(data, argc, argv);
	if (!data->args)
		return (NULL);
	data->dead = 0;
	data->fork = malloc(data->args->nb_philo * sizeof(int));
	if (!data->fork)
		return (NULL);
	while (i < data->args->nb_philo)
	{
		data->fork[i] = 1;
		i++;
	}
	if (!ft_init_mutex(data))
		return (NULL);
	data->philo = malloc(data->args->nb_philo * sizeof(t_philo));
	if (!data->philo)
		return (NULL);
	data->philo = ft_init_philo(data);
	if (!data->philo)
		return (0);
	return (data);
}
