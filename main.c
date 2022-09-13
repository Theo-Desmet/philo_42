/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/13 13:39:41 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		data->philo[i]->data = data;
		i++;
	}
	return (data->philo);
}

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
	return (1);
}

t_data	*ft_init(t_data *data, int argc, char ** argv)
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
	ft_init_mutex(data);//sdf
	data->philo = malloc(data->args->nb_philo * sizeof(t_philo));
	if (!data->philo)
		return (NULL);
	return (data);
}
int	ft_start(t_data *data)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&data->m_start);
	while (i < data->args->nb_philo)
	{
		pthread_create(&(data->philo[i]->philo), NULL, &ft_routine, data->philo[i]);
		pthread_detach(data->philo[i]->philo);
		i++;
	}
	data->init_time = ft_get_time();
	pthread_mutex_unlock(&data->m_start);
}
int	main(int argc, char **argv)
{
	t_data	*data;

	if (!ft_check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_init(data, argc, argv);
	data->philo = ft_init_philo(data);
	if (!data->philo)
		return (0);
	ft_start(data);
	while (1)
		sleep(1);
}
