/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/05 16:22:25 by tdesmet          ###   ########.fr       */
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
		pthread_create(&(data->philo[i]->philo), NULL, ft_update_time, data->time);//sdf
		i++;
	}
	return (data->philo);
}

t_time	*ft_init_time(t_data *data)
{
	data->time = malloc(sizeof(t_time));
	if (!data->mutex)
		return (NULL);
	pthread_create(&(data->time->monitoring), NULL
			, ft_update_time, data->time);
	data->time->init_time = 0;
	data->time->philo_time = 0;
	return (data->time);
}

t_mutex	*ft_init_mutex(t_data *data)
{
	data->mutex = malloc(sizeof(t_mutex));
	if (!data->mutex)
		return (NULL);
	if (pthread_mutex_init(&data->mutex->fork, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->mutex->dead, NULL) != 0)
		return (NULL);
	return (data->mutex);
}

t_data	*ft_init(t_data *data, int argc, char ** argv)
{
	data->args = ft_get_args(data, argc, argv);
	if (!data->args)
		return (NULL);
	data->mutex = ft_init_mutex(data);
	if (!data->mutex)
		return (NULL);
	data->time = ft_init_time(data);
	if (!data->time)
		return (NULL);
	data->dead = 0;
	data->philo = malloc(data->args->nb_philo * sizeof(t_philo));
	if (!data->philo)
		return (NULL);
	data->philo = ft_init_philo(data);
	if (!data->philo)
		return (NULL);
	return (data);
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
	//data->time_think = ft_calc_time_to_think(data);	
	//data->nb_service = ft_calc_service(data);	
	data->time->init_time = ft_get_time();
	pthread_join(data->time->monitoring, NULL);
}
